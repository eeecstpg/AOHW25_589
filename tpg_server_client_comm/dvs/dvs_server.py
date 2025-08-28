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
from pynq import Overlay, allocate

# CONFIGURE THESE
BITSTREAM    = "/home/xilinx/pynq/overlays/tpg/tpg_dvs.xsa"
PORT         = 6000
N_FEATURES   = 9
WINDOW_SIZE  = 5
TOTAL_BITS   = 13
INT_BITS     = 2

SCALE_FACTOR = 2**(TOTAL_BITS - INT_BITS)
BIT_MASK     = (1 << TOTAL_BITS) - 1

def quantize(feat):
    q = (feat * SCALE_FACTOR).astype(np.int32) & BIT_MASK
    return q.astype(np.uint32)

def get_ip_address():
    """Get the primary IP address of the PYNQ board."""
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    try:
        # Doesn't have to be reachable — just used to find the interface
        s.connect(("8.8.8.8", 80))
        ip = s.getsockname()[0]
    except Exception:
        ip = "127.0.0.1"
    finally:
        s.close()
    return ip

def start_server():
    # Load overlay & DMA
    ol  = Overlay(BITSTREAM)
    dma = ol.axi_dma_0

    # Allocate buffers
    in_buf  = allocate((N_FEATURES,), dtype=np.uint32)
    out_buf = allocate((1,),           dtype=np.uint32)

    # TCP setup
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.bind(("0.0.0.0", PORT))
    sock.listen(1)

    # Print connection info
    ip = get_ip_address()
    print(f"[PS] Server is running. Connect from client at {ip}:{PORT}")
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
                feats = np.array([float(x) for x in line.split(",")])
            except ValueError:
                print(f"[PS] Bad line: {line}")
                continue
            if feats.shape[0] != N_FEATURES:
                print(f"[PS] Wrong length: {feats.shape[0]}")
                continue

            # quantize + DMA
            in_buf[:] = quantize(feats)
            in_buf.flush()
            out_buf.invalidate()
            dma.sendchannel.transfer(in_buf)
            dma.recvchannel.transfer(out_buf)
            dma.sendchannel.wait()
            dma.recvchannel.wait()

            pred = int(out_buf[0])
            # send back
            conn.sendall(f"{pred}\n".encode())
            print(f"[PS] -> pred={pred}")

    conn.close()
    sock.close()

if __name__=="__main__":
    start_server()
