#!/usr/bin/env python3
"""
TPG Classifier Server over Ethernet

This script runs on a PYNQ board and exposes the TPG classifier as a
simple TCP service over Ethernet. It listens for incoming newline-delimited
feature vectors, quantizes them to fixed-point, feeds them through the PL-
accelerated TPG IP via AXI-DMA, and returns a single integer prediction per
sample back to the client.

Protocol:
    • Client connects on TCP port PORT.
    • Client sends one CSV line of N_FEATURES floats (e.g. "f0,f1,…,f50\n").
    • Server parses, quantizes, DMA-transfers, waits for the PL result.
    • Server replies with "<pred>\n" where pred is the predicted class ID.
    • Repeat until client disconnects.

Configuration (edit constants in the file):
    BITSTREAM    = "tpg_axis/wrapper_working_09_07.xsa" # overlay XSA or .bit file
    PORT         = 6000                                 # TCP port to listen on
    N_FEATURES   = 51                                   # number of input features
    TOTAL_BITS   = 16                                   # ap_fixed total width
    INT_BITS     = 8                                    # ap_fixed integer width
    WINDOW_SIZE  = 5                                    # (optional) sliding-window length

Usage:
    # on the PYNQ board:
    sudo su
    source /etc/profile.d/pynq_venv.sh
    source /etc/profile.d/xrt_setup.sh
    python3 tpg_ethernet.py

    # on the client (PC), connect to 192.168.2.99:6000 and exchange
    # newline-terminated CSV lines for predictions.
    python3 pc_eth_stream.py
"""
import socket
import numpy as np
import time
from pynq import Overlay, allocate

# CONFIGURE THESE
BITSTREAM    = "/home/xilinx/pynq/overlays/tpg/tpg_nids.xsa"
PORT = 6000  # TCP port to listen on
N_FEATURES = 78  # number of input features
TOTAL_BITS = 33  # ap_fixed total width
INT_BITS = 33  # ap_fixed integer width

SCALE_FACTOR = 2 ** (TOTAL_BITS - INT_BITS)
BIT_MASK = (1 << TOTAL_BITS) - 1


def quantize(feat):
    q = (feat * SCALE_FACTOR).astype(np.int32) & BIT_MASK
    return q.astype(np.uint32)

def get_ip_address():
    """Find the IP address of the PYNQ board."""
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    try:
        # This is a trick to get the IP address of the machine
        # The socket connects to a non-existent external address
        # and returns the local IP it would use.
        s.connect(("8.8.8.8", 80))  # Google's public DNS
        ip_address = s.getsockname()[0]
    except Exception:
        # Fallback to localhost if an error occurs
        ip_address = '127.0.0.1'
    finally:
        s.close()
    return ip_address

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
    """Hard reset both channels via register_map; no recursion, no waiting."""
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
    """Ensure RS=1 and channels idle; reset once if they won't go idle."""
    rm = dma.register_map
    # Start if not running
    if not rm.MM2S_DMACR.RS or not rm.S2MM_DMACR.RS:
        dma.sendchannel.start()
        dma.recvchannel.start()
    # Try to reach idle
    if not wait_until_idle(dma, idle_timeout_s):
        dma_force_reset(dma)
        # Try once more to reach idle (don’t recurse)
        wait_until_idle(dma, idle_timeout_s)


def dma_kick_send_only(dma, in_buf, kick_timeout_s=0.25):
    """Your manual 'send once' nudge, safely."""
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
    """Arm RECV→SEND; return True on success, False on timeout."""
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
    """Try once; on timeout do your 'kick' and retry once."""
    if dma_try_pair_with_timeout(dma, in_buf, out_buf, timeout_s):
        return True
    dma_kick_send_only(dma, in_buf)  # manual nudge
    return dma_try_pair_with_timeout(dma, in_buf, out_buf, timeout_s)


def start_server():
    # Load overlay & DMA
    ol = Overlay(BITSTREAM)
    dma = ol.axi_dma_0

    # Allocate buffers
    in_buf = allocate((N_FEATURES,), dtype=np.uint32)
    out_buf = allocate((1,), dtype=np.uint32)

    # After overlay download (once)
    dma_force_reset(dma)  # clean state (no recursion)
    ensure_started_and_idle(dma)
    # Optional prime (mimics your manual nudge)
    in_buf[:] = 0
    dma_pair_with_kick_retry(dma, in_buf, out_buf, timeout_s=0.10)

    # TCP setup
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.bind(("0.0.0.0", PORT))
    sock.listen(1)

    # Get and print the IP address
    pynq_ip = get_ip_address()
    print(f"[PS] Server is running. Connect from client at {pynq_ip}:{PORT}")
    print("[PS] Waiting for client connection...")

    conn, addr = sock.accept()
    print(f"[PS] Connection established with {addr}")

    buffer = ""

    while True:
        data = conn.recv(1024).decode()
        if not data:
            break
        buffer += data
        while "\n" in buffer:
            line, buffer = buffer.split("\n", 1)
            if not line:
                continue
            # parse features
            try:
                all_values = np.array([float(x) for x in line.split(",")])
            except ValueError:
                print(f"[PS] Bad line: {line}")
                continue

            # Extract only the first N_FEATURES columns (ignore labels/extra columns)
            if all_values.shape[0] < N_FEATURES:
                print(f"[PS] Too few features: got {all_values.shape[0]}, need {N_FEATURES}")
                continue

            feats = all_values[:N_FEATURES]  # Take only the first N_FEATURES

            # quantize + DMA
            in_buf[:] = quantize(feats)
            ok = dma_pair_with_kick_retry(dma, in_buf, out_buf, timeout_s=0.10)
            if not ok:
                # skip/log and continue; notebook won’t hang
                continue

            pred = int(out_buf[0])
            # send back
            conn.sendall(f"{pred}\n".encode())

            if pred == 1:
                print(f"[PS] Suspicious Packet - potential malicious activity")

    conn.close()
    sock.close()


if __name__ == "__main__":
    start_server()
