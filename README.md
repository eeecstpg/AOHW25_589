# Real-time data stream processing using lightweight Tangled Program Graphs on AMD FPGA.
This repository contains our submission for the AMD Open Hardware Competition 2025 in the form of FPGA accelerated 
Tangled Program Graphs (TPG) for real-time stream processing using the [AMD PYNQ Z2](https://www.amd.com/en/corporate/university-program/aup-boards/pynq-z2.html).

In part to the low computational complexity surrounding TPGs and their ability to adapt to given application tasks, their 
use as a mechanism to derive sophisticated lightweight systems has led to their realisation on embedded microprocessor 
platforms.
Although TPGs demonstrate strong potential for lightweight FPGA accelerators, their original sequential implementation 
failed to exploit the inherent parallelism in its structure. 
This resulted in limited real-time performance and increased resource costs, overall restricting their effective FPGA 
deployment.

To evaluate the effectiveness of our designs at realising lightweight accelerators, we demonstrate their application 
across three complex time-series benchmark tasks: 
- ECG Arrhythmia Classification
- Network Instruction Detection
- DVS Camera Event de-noising

This research enables accurate, high-speed, and high-throughput TPG accelerators, suitable for tackling a diverse range 
of applications and which can efficiently be deployed onto AMD FPGA hardware.


# Project Description
## Hardware Description
![Screenshot of a comment on a GitHub issue showing an image, added in the Markdown, of an Octocat smiling and raising a tentacle.](/images/streaming_methodology.png)
- PYNQ board
  - setup
- Specify FPGA hardware (ZYNQ-7000)

## Design Methodology
*include diagram
- streaming approach
  - ethernet

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
