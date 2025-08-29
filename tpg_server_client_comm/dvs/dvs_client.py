#!/usr/bin/env python3
"""
DVS Event TPG Classifier Client (PC side)

This script runs on your PC and connects to a PYNQ-based DVS event processing server.
It streams DVS events read from a local event file, sending them as timestamp,x,y,polarity,label
lines without expecting any responses. This is designed to work with the 
dvs_server.py server.

Protocol:
    • Client connects to the server at (HOST, PORT) via TCP.
    • For each event, it sends "timestamp,x,y,polarity,label\n".
    • No responses expected - server processes events in batches and prints summaries.
    • Minimal flow control: if a send times out, it waits and retries sending that event, with increasing delay

Configuration (edit these constants near the top of the file):
    HOST            = "192.168.2.99"        # PYNQ board's IP address
    PORT            = 6000                  # TCP port matching the server
    EVENT_FILE      = "events.txt"          # path to your DVS event data
    PROGRESS_INTERVAL = 1000                # Print progress every N events

Expected event file format:
    Each line should contain: timestamp x y polarity label
    Lines starting with # are treated as comments and skipped.
    Example:
        0.04133333265781403 90 97 1 1
        0.04133333265781403 207 6 1 1
        0.04133333265781403 45 67 0 0
    
    Fields:
        timestamp: Event timestamp in seconds
        x, y: Pixel coordinates
        polarity: Event polarity (0 or 1)
        label: Ground truth label (1=signal, 0=noise) - not sent to server

Usage:
    # Ensure the PYNQ DVS server is running and accessible first
    python3 dvs_server.py

    You'll see logs like:
        [CLIENT] Connected to 192.168.2.99:6000
        [CLIENT] Sending events from events.txt
        [CLIENT] Sent 1000 events...
        [CLIENT] Sent 2000 events...
        ...
        [CLIENT] Finished sending 25000 events
"""
import socket
import time
import sys

# —— CONFIG —— 
HOST             = "192.168.2.99"    # PYNQ's IP
PORT             = 6000
EVENT_FILE       = "datasets/hotel.txt"
PROGRESS_INTERVAL = 1000              # Print progress every N events


def send_events_file(sock, filename):
    """
    Send events from file to the server with minimal flow control.
    
    Args:
        sock: TCP socket connection
        filename: Path to event file
    """
    print(f"[CLIENT] Sending events from {filename}")
    
    sent_count = 0
    start_time = time.time()
    retry_delay = 0.001  # Start with 1ms delay
    max_retry_delay = 0.1  # Max 100ms delay
    
    try:
        with open(filename, 'r') as f:
            for line_num, line in enumerate(f, 1):
                line = line.strip()
                
                # Skip empty lines and comments
                if not line or line.startswith('#'):
                    continue
                
                try:
                    # Parse event line: timestamp x y polarity label
                    parts = line.split()
                    if len(parts) < 5:
                        print(f"[WARNING] Line {line_num}: insufficient fields - {line}")
                        continue
                    
                    timestamp = float(parts[0])
                    x = parts[1]
                    y = parts[2] 
                    polarity = parts[3]
                    label = parts[4]  # Ground truth label (1=signal, 0=noise)
                    
                    # Send event with minimal retry logic - only retry on actual timeouts
                    event_line = f"{timestamp},{x},{y},{polarity},{label}\n"
                    
                    while True:
                        try:
                            sock.sendall(event_line.encode())
                            sent_count += 1
                            # Success - reset retry delay
                            retry_delay = 0.001
                            break
                            
                        except socket.timeout:
                            print(f"[CLIENT] Send timeout, waiting {retry_delay*1000:.1f}ms before retry...")
                            time.sleep(retry_delay)
                            retry_delay = min(max_retry_delay, retry_delay * 2)  # Exponential backoff
                            continue
                            
                        except (ConnectionResetError, BrokenPipeError):
                            print("[ERROR] Connection lost to server")
                            return False
                    
                    # Progress updates
                    if sent_count % PROGRESS_INTERVAL == 0:
                        elapsed = time.time() - start_time
                        rate = sent_count / elapsed if elapsed > 0 else 0
                        print(f"[CLIENT] Sent {sent_count} events... ({rate:.1f} events/sec)")
                
                except (ValueError, IndexError) as e:
                    print(f"[WARNING] Line {line_num}: parse error - {line} ({e})")
                    continue
                except KeyboardInterrupt:
                    print("\n[CLIENT] Interrupted by user")
                    break
    
    except FileNotFoundError:
        print(f"[ERROR] Event file not found: {filename}")
        return False
    except Exception as e:
        print(f"[ERROR] Error reading file: {e}")
        return False
    
    elapsed = time.time() - start_time
    rate = sent_count / elapsed if elapsed > 0 else 0
    print(f"[CLIENT] Finished sending {sent_count} events in {elapsed:.2f}s ({rate:.1f} events/sec)")
    return True


def main():
    """Main client function."""
    print(f"[CLIENT] DVS Event Feeder Client")
    print(f"[CLIENT] Target: {HOST}:{PORT}")
    print(f"[CLIENT] Event file: {EVENT_FILE}")
    
    try:
        # Connect to server
        print(f"[CLIENT] Connecting to {HOST}:{PORT}...")
        sock = socket.create_connection((HOST, PORT), timeout=10)
        sock.settimeout(5.0)  # Set timeout for send operations
        print(f"[CLIENT] Connected successfully")
        
        # Send events
        success = send_events_file(sock, EVENT_FILE)
        
        if success:
            print("[CLIENT] All events sent successfully")
        else:
            print("[CLIENT] Event sending failed")
        
        # Give server time to process final batch
        print("[CLIENT] Waiting for server to process final batch...")
        time.sleep(2)
        
    except socket.timeout:
        print(f"[ERROR] Connection timeout to {HOST}:{PORT}")
        return 1
    except ConnectionRefusedError:
        print(f"[ERROR] Connection refused by {HOST}:{PORT}")
        print("[ERROR] Make sure the DVS server is running on the PYNQ board")
        return 1
    except Exception as e:
        print(f"[ERROR] Connection error: {e}")
        return 1
    finally:
        if 'sock' in locals():
            sock.close()
            print("[CLIENT] Connection closed")
    
    return 0


if __name__ == "__main__":
    sys.exit(main())
