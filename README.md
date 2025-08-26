# Real-time data stream processing using lightweight Tangled Program Graphs on AMD FPGA.
Our research project is focussed on the hardware acceleration of Tangled Program Graphs (TPG) for real-time stream 
processing using AMD FPGAs.

Our submission for the AMD Open Hardware Competition 2025 demonstrates the application of our TPG accelerators for a 
series of time-series applications including;
- ECG Arrhythmia Classification
- Network Instruction Detection
- DVS Camera Event de-noising

# Project Description
- lightweight accelerators
- targeting complex tasks
- capable of running on lightweight hardware such as the PYNQ making it more accessible
- ultra low-latency
- high throughput
- competitive resource costs compare to DNN

## Hardware Description
- PYNQ board
- Specify FPGA hardware (ZYNQ-7000)

## Running the demo
1. Download TPG IP file
2. Transfer IP to PYNQ board (specify folder on the board) - use network share approach
3. Run Server file on PYNQ
4. Run client file on host machine

# Team Members
| **Team Member**    | **Role**      | **Affiliation**                             |
|--------------------|---------------|---------------------------------------------|
| Jarlath Warner     | PhD Student   | Queen's University Belfast (QUB)            |
| Donavon Clay       | Undergraduate | Massachusetts Institute of Technology (MIT) |
| Katherine McEwan   | Undergraduate | Massachusetts Institute of Technology (MIT) |
| John McAllister    | Supervisor    | Queen's University Belfast (QUB)            |
