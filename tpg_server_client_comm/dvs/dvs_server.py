#!/usr/bin/env python3
"""
DVS Event Feature Processing and TPG Classifier Server

This script combines DVS event reception over Ethernet with live feature processing
and TPG classification. It receives DVS events over TCP, processes them in timestamp
batches to extract 9-feature vectors, sends them to the TPG IP via AXI-DMA, and
provides summaries of noise detection results.

Protocol:
    • Client connects on TCP port PORT.
    • Client sends DVS events as "timestamp,x,y,polarity,label\n" lines.
    • Server groups events by timestamp, extracts features, and classifies via TPG.
    • Server prints summary statistics for each timestamp batch.

Configuration:
    BITSTREAM    = "tpg_axis/dvs.xsa"                 # overlay XSA file
    PORT         = 6000                               # TCP port to listen on
    N_FEATURES   = 9                                  # number of input features
    TOTAL_BITS   = 32                                 # ap_fixed total width
    INT_BITS     = 16                                 # ap_fixed integer width
    CAMERA_WIDTH = 346                                # DVS camera width
    CAMERA_HEIGHT = 260                               # DVS camera height
    SEARCH_RADIUS = 0.02                              # feature search radius

Usage:
    # on the PYNQ board:
    sudo su
    source /etc/profile.d/pynq_venv.sh
    source /etc/profile.d/xrt_setup.sh
    python3 dvs_server_feature_processing.py

    # on the client (PC), send DVS events as CSV lines to port 6000

Sample Output:
    [PROCESSING] Batch at timestamp 1.668519 with 13923 events
    === Timestamp 1.668519 Summary ===
    Total events: 13923
    Noise events (pred=0): 981 (7.0%)
    Signal events (pred=1): 12942 (93.0%)
    Noise pixels: [(41, 142), (271, 107), (202, 37), (292, 160), (5, 200)]...
    ========================================
    [PROCESSING] Batch at timestamp 1.670370 with 7593 events

    === Timestamp 1.670370 Summary ===
    Total events: 7593
    Noise events (pred=0): 24 (0.3%)
    Signal events (pred=1): 7569 (99.7%)
    Noise pixels: [(30, 135), (28, 53), (26, 59), (41, 71), (292, 242)]...
    ========================================
"""
import socket
import numpy as np
import time
from pynq import Overlay, allocate
from collections import defaultdict

# CONFIGURE THESE
BITSTREAM = "tpg_axis/dvs.xsa"
PORT = 6000  # TCP port to listen on
N_FEATURES = 9  # number of input features
TOTAL_BITS = 32  # ap_fixed total width
INT_BITS = 16  # ap_fixed integer width
CAMERA_WIDTH = 346  # DVS camera width
CAMERA_HEIGHT = 260  # DVS camera height
SEARCH_RADIUS = 0.02  # feature search radius (seconds)

SCALE_FACTOR = 2 ** (TOTAL_BITS - INT_BITS)
BIT_MASK = (1 << TOTAL_BITS) - 1


def quantize(feat):
    """Quantize floating-point features to fixed-point format for TPG."""
    q = (feat * SCALE_FACTOR).astype(np.int32) & BIT_MASK
    return q.astype(np.uint32)


def wait_until_idle(dma, timeout_s=0.05):
    """Return True if both channels go idle within timeout, else False."""
    t0 = time.perf_counter()
    while True:
        if dma.sendchannel.idle and dma.recvchannel.idle:
            return True
        if time.perf_counter() - t0 > timeout_s:
            return False
        time.sleep(0.001)


def dma_force_reset(dma):
    """Hard reset both channels via register_map - done when channels hang on wait"""
    rm = dma.register_map
    # Assert Reset (self-clearing)
    rm.MM2S_DMACR.Reset = 1
    rm.S2MM_DMACR.Reset = 1
    # Clear sticky status (write-1-to-clear)
    rm.MM2S_DMASR = 0xFFFFFFFF
    rm.S2MM_DMASR = 0xFFFFFFFF
    # Start engines (sync driver state)
    dma.sendchannel.start()
    dma.recvchannel.start()


def ensure_started_and_idle(dma, idle_timeout_s=0.05):
    """Ensure RS=1 and channels idle; reset once if not idle."""
    rm = dma.register_map
    # Start if not running
    if not rm.MM2S_DMACR.RS or not rm.S2MM_DMACR.RS:
        dma.sendchannel.start()
        dma.recvchannel.start()
    # Try to reach idle
    if not wait_until_idle(dma, idle_timeout_s):
        dma_force_reset(dma)
        # Try once more to reach idle (don't recurse)
        wait_until_idle(dma, idle_timeout_s)


def dma_kick_send_only(dma, in_buf, kick_timeout_s=0.25):
    """Nudge the DMA to send only."""
    ensure_started_and_idle(dma, idle_timeout_s=0.02)
    in_buf.flush()
    dma.sendchannel.transfer(in_buf)
    t0 = time.perf_counter()
    while not dma.sendchannel.idle:
        if time.perf_counter() - t0 > kick_timeout_s:
            dma_force_reset(dma)
            break
        time.sleep(0.001)


def dma_try_pair_with_timeout(dma, in_buf, out_buf, timeout_s=0.10):
    """Arm RECV→SEND, do manual wait and timeout; return True on success, False on timeout."""
    ensure_started_and_idle(dma, idle_timeout_s=0.02)

    out_buf.invalidate()
    in_buf.flush()
    dma.recvchannel.transfer(out_buf)  # arm S2MM first
    dma.sendchannel.transfer(in_buf)  # then MM2S

    t0 = time.perf_counter()
    while not dma.recvchannel.idle:
        if time.perf_counter() - t0 > timeout_s:
            dma_force_reset(dma)
            return False
        time.sleep(0.001)

    while not dma.sendchannel.idle:
        if time.perf_counter() - t0 > timeout_s:
            dma_force_reset(dma)
            return False
        time.sleep(0.001)
    return True


def dma_pair_with_kick_retry(dma, in_buf, out_buf, timeout_s=0.10):
    """Try once; on timeout do a kick and retry once."""
    if dma_try_pair_with_timeout(dma, in_buf, out_buf, timeout_s):
        return True
    dma_kick_send_only(dma, in_buf)  # manual nudge
    return dma_try_pair_with_timeout(dma, in_buf, out_buf, timeout_s)


def update_pixel(event_array, val, x, y):
    """Update the event_array with a new event for the pixel at (x,y)."""
    if 0 <= x < CAMERA_WIDTH and 0 <= y < CAMERA_HEIGHT:
        event_array[x, y] = val


def get_event_neighbors(event_array, x, y):
    """Extract 3x3 neighborhood values (including center) around a given pixel location (9 features)."""
    neighbors = []
    for xix in [x-1, x, x+1]:
        for yix in [y-1, y, y+1]:
            if 0 <= xix < CAMERA_WIDTH and 0 <= yix < CAMERA_HEIGHT:
                val = event_array[xix, yix]
            else:
                val = -1.0
            neighbors.append(val)
    return neighbors


def get_features(event_array, timestamp, x, y, radius):
    """Calculate the 9 features for the center pixel at (x,y)."""
    neighbors_list = get_event_neighbors(event_array, x, y)
    features = []
    for neighbor in neighbors_list:
        if neighbor >= 0:
            diff = timestamp - neighbor
            if diff <= radius:
                features.append(diff)
            else:
                features.append(-1.0)
        else:  
            features.append(-1.0)
    return features


def process_timestamp_batch(current_events, past_array, timestamp, radius, dma, in_buf, out_buf):
    """
    Process all events in a timestamp batch and return results.
    
    Returns:
        list of tuples: [(x, y, prediction), ...]
    """
    results = []
    
    # Get list of pixels with events at this timestamp
    event_pixels = [(x, y) for x, y in current_events]
    
    # Process each event pixel
    for x, y in event_pixels:
        # Extract features for this pixel
        features = get_features(past_array, timestamp, x, y, radius)
        
        # Convert features to numpy array
        features_array = np.array(features)
        
        # Quantize features and send to TPG
        in_buf[:] = quantize(features_array)
        ok = dma_pair_with_kick_retry(dma, in_buf, out_buf, timeout_s=0.10)
        
        if ok:
            prediction = int(out_buf[0])
            results.append((x, y, prediction))
        else:
            print(f"[WARNING] DMA timeout for pixel ({x}, {y})")
            results.append((x, y, -1))  # Mark as failed prediction
    
    # Update past_array with current timestamp for all event pixels
    for x, y in event_pixels:
        update_pixel(past_array, timestamp, x, y)
    
    return results


def print_batch_summary(timestamp, results):
    """Print summary statistics for a processed timestamp batch."""
    if not results:
        return
    
    total_events = len(results)
    noise_events = [(x, y) for x, y, pred in results if pred == 0]
    signal_events = [(x, y) for x, y, pred in results if pred == 1]
    failed_events = [(x, y) for x, y, pred in results if pred == -1]
    
    noise_percentage = (len(noise_events) / total_events) * 100 if total_events > 0 else 0
    signal_percentage = (len(signal_events) / total_events) * 100 if total_events > 0 else 0
    
    print(f"\n=== Timestamp {timestamp:.6f} Summary ===")
    print(f"Total events: {total_events}")
    print(f"Noise events (pred=0): {len(noise_events)} ({noise_percentage:.1f}%)")
    print(f"Signal events (pred=1): {len(signal_events)} ({signal_percentage:.1f}%)")
    
    if failed_events:
        print(f"Failed predictions: {len(failed_events)}")

    if noise_events:  # only the first 5 because it can get crowded
        print(f"Noise pixels: {noise_events[:5]}{'...' if len(noise_events) > 5 else ''}")
    
    print("=" * 40)


def start_server():
    """Main server function."""
    # Load overlay & DMA
    print("[INIT] Loading overlay...")
    ol = Overlay(BITSTREAM)
    dma = ol.axi_dma_0

    # Allocate buffers
    in_buf = allocate((N_FEATURES,), dtype=np.uint32)
    out_buf = allocate((1,), dtype=np.uint32)

    # Initialize DMA
    print("[INIT] Initializing DMA...")
    dma_force_reset(dma)
    ensure_started_and_idle(dma)
    
    # Optional prime
    in_buf[:] = 0
    dma_pair_with_kick_retry(dma, in_buf, out_buf, timeout_s=0.10)

    # Initialize DVS processing arrays
    past_array = np.full((CAMERA_WIDTH, CAMERA_HEIGHT), -1.0)
    
    # TCP setup
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    sock.bind(("0.0.0.0", PORT))
    sock.listen(1)
    print(f"[SERVER] Listening on port {PORT}...")
    
    while True:
        try:
            conn, addr = sock.accept()
            print(f"[SERVER] Connection from {addr}")
            
            buffer = ""
            current_timestamp = None
            current_events = set()  # Set of (x, y) tuples for current timestamp
            
            while True:
                data = conn.recv(4096).decode()
                if not data:
                    break
                    
                buffer += data
                
                while "\n" in buffer:
                    line, buffer = buffer.split("\n", 1)
                    line = line.strip()
                    
                    if not line or line.startswith("#"):
                        continue
                    
                    try:
                        # Parse DVS event: timestamp,x,y,polarity
                        parts = line.split(",")
                        if len(parts) < 3:
                            continue
                            
                        timestamp = float(parts[0])
                        x = int(float(parts[1]))
                        y = int(float(parts[2]))
                        
                        # Check bounds
                        if not (0 <= x < CAMERA_WIDTH and 0 <= y < CAMERA_HEIGHT):
                            continue
                        
                        # If this is a new timestamp, process the previous batch
                        if current_timestamp is not None and timestamp != current_timestamp:
                            if current_events:
                                print(f"[PROCESSING] Batch at timestamp {current_timestamp:.6f} with {len(current_events)} events")
                                results = process_timestamp_batch(
                                    current_events, past_array, current_timestamp, 
                                    SEARCH_RADIUS, dma, in_buf, out_buf
                                )
                                print_batch_summary(current_timestamp, results)
                            
                            # Reset for new timestamp
                            current_events.clear()
                        
                        # Update current batch
                        current_timestamp = timestamp
                        current_events.add((x, y))
                        
                    except (ValueError, IndexError) as e:
                        print(f"[ERROR] Bad line: {line} - {e}")
                        continue
            
            # Process final batch if exists
            if current_timestamp is not None and current_events:
                print(f"[PROCESSING] Final batch at timestamp {current_timestamp:.6f} with {len(current_events)} events")
                results = process_timestamp_batch(
                    current_events, past_array, current_timestamp, 
                    SEARCH_RADIUS, dma, in_buf, out_buf
                )
                print_batch_summary(current_timestamp, results)
            
            print(f"[SERVER] Client {addr} disconnected")
            conn.close()
            
        except KeyboardInterrupt:
            print("\n[SERVER] Shutting down...")
            break
        except Exception as e:
            print(f"[ERROR] Server error: {e}")
            if 'conn' in locals():
                conn.close()
    
    sock.close()


if __name__ == "__main__":
    start_server()
