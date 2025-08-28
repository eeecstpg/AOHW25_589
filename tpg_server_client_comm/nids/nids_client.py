#!/usr/bin/env python3
"""
TPG Classifier Client (PC side)

This script runs on your PC and connects to a PYNQ-based TCP server
that hosts an FPGA-accelerated TPG classifier. It streams feature
vectors read from a local CSV file, one newline-terminated CSV line
at a time, and receives back a single integer prediction per sample.
At the end it builds and prints a confusion matrix.

Protocol:
    • Client connects to the server at (HOST, PORT) via TCP.
    • For each sample, it sends “f0,f1,…,fN–1\n”.
    • Server responds with “<pred>\n” (predicted class ID).
    • Client accumulates true vs. pred into a confusion matrix.

Configuration (edit these constants near the top of the file):
    HOST        = "192.168.2.99"            # PYNQ board’s IP address
    PORT        = 6000                      # TCP port matching the server
    N_FEATURES  = 51                        # number of floats per sample
    TEST_CSV    = "vitisECGTestData.csv"    # path to your test data

Usage:
    # Ensure the PYNQ server is running and accessible first
    python3 pc_eth_stream.py

    You’ll see per-sample logs:
        [PC] Sample 0: true=0, pred=1
        …

    And at the end:
        Confusion Matrix (rows=true, cols=pred):
           0   1
         0 50   2
         1  3  45
        Class 0 Accuracy: 88.81%
        Class 1 Accuracy: 95.44%
"""
import socket
import numpy as np

# —— CONFIG —— 
HOST       = "192.168.2.99"    # PYNQ’s IP
PORT       = 6000
N_FEATURES = 78
TEST_CSV   = "nids_test_data.csv"


def print_confusion(cm, classes):
    print("\nConfusion Matrix (rows=true, cols=pred):")
    # header
    print("     " + "  ".join(f"{c:>3}" for c in classes))
    for i, c in enumerate(classes):
        row = "  ".join(f"{cm[i][j]:>3}" for j in range(len(classes)))
        print(f"{c:>3}  {row}")
    # per-class accuracy
    for i, c in enumerate(classes):
        tp = cm[i][i]
        total = sum(cm[i])
        acc = 100 * tp / total if total else 0.0
        print(f"Class {c} Accuracy: {acc:.2f}%")
        

def main():
    # load local test data
    data   = np.loadtxt(TEST_CSV, delimiter=",", dtype=np.float32)
    feats  = data[:, :N_FEATURES]
    labels = data[:, 78].astype(int)

    # determine set of classes
    classes = sorted(set(labels))
    idx = {c:i for i,c in enumerate(classes)}
    # initialize empty confusion matrix
    cm = [[0]*len(classes) for _ in classes]

    # open TCP connection
    sock = socket.create_connection((HOST, PORT))
    f = sock.makefile('rwb', buffering=0)

    for i, (x, y_true) in enumerate(zip(feats, labels)):
        # send CSV line
        line = ",".join(f"{v:.6f}" for v in x) + "\n"
        sock.sendall(line.encode())

        # read back prediction
        resp = f.readline().decode().strip()
        try:
            y_pred = int(resp)
        except ValueError:
            print(f"[PC] Bad reply: {resp!r}")
            continue

        # accumulate into confusion
        cm[idx[y_true]][idx[y_pred]] += 1

        print(f"[PC] Sample {i}: true={y_true}, pred={y_pred}")

    sock.close()

    # print final confusion matrix
    print_confusion(cm, classes)


if __name__ == "__main__":
    main()
