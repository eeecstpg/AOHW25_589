# Real-time data stream processing using lightweight Tangled Program Graphs on AMD FPGA.
This repository contains our submission for the AMD Open Hardware Competition 2025 in the form of FPGA accelerated 
Tangled Program Graphs (TPG) for real-time stream processing using the [AMD PYNQ Z2](https://www.amd.com/en/corporate/university-program/aup-boards/pynq-z2.html).

In part to the low computational complexity surrounding TPGs and their ability to adapt to given application tasks, their 
use as a mechanism to derive sophisticated lightweight classifiers has led to their realisation on embedded microprocessor 
platforms.
Although TPGs demonstrate strong potential for lightweight FPGA accelerators, their original sequential implementation 
fails to exploit the inherent parallelism inherent in its structure. 
Following this, FPGA accelerators which utilised original TPG implementations resulted in limited real-time performance and increased resource costs, overall restricting their effective FPGA 
deployment.

## Project Focus
Our project centred on restructuring TPG structures to better avail of reconfigurable hardware and to utilise a dataflow streaming-based architecture in order to yield high-throughput, low resource-cost accelerators for a variety of common application tasks.
The resulting dataflow architectures can be generated for any given TPG using our synthesis toolkit which expands upon the functionality offered through [Gegelati](https://github.com/gegelati/gegelati).
With our synthesis toolkit, TPGs can be synthesised targeting AMD FPGA hardware, which to date has not been achieved before.

To evaluate the effectiveness of our designs at realising lightweight accelerators, we demonstrate their application 
across three complex time-series benchmark tasks: 
- ECG Arrhythmia Classification
- Network Instruction Detection
- DVS Camera Event de-noising

This research enables accurate, high-speed, and high-throughput TPG accelerators, suitable for tackling a diverse range 
of applications and which can efficiently be deployed onto AMD FPGA hardware.

## Project Structure
```
└── AOHW25_589/
    ├── images/
    │   ├── // images for the repositroy README
    │   └── streaming_methodology.png
    ├── tpg_design_exports/
    │   ├── // .xsa files for each TPG, for each benchmark application
    │   ├── tpg_dvs.xsa   // DVS TPG 
    │   ├── tpg_ecg.xsa   // ECG TPG
    │   └── tpg_nids.xsa  // NIDS TPG
    ├── tpg_server_client_comm/
    │   ├── // python files to initiate client-server communication between a host machine and PYNQ-Z2 board
    │   ├── dvs/
    │   │   ├── dvs_client.py
    │   │   └── dvs_server.py
    │   ├── ecg/
    │   │   ├── ecg_client.py
    │   │   └── ecg_server.py
    │   └── nids/
    │       ├── nids_client.py
    │       └── nids_server.py
    ├── tpg_test_datasets/
    │   ├── // test datasets to run each TPG demo on the PYNQ-Z2 board
    │   ├── dvs_test_data.zip
    │   ├── ecg_test_data.zip
    │   └── nids_test_data.zip
    └── tpg_vitis_code/
        ├── // C++ code for each TPG, for each application, which gets synthesised in Vitis
        ├── dvs/
        │   └── ...
        ├── ecg/
        │   └── ...
        └── nids/
            └── ...
```

# Project Description
To enable fast, real-time processing via our streaming TPG classifiers, we opted to use Ethernet streaming for data transmission.
Through this approach external sensors, such as a Dynamic Vision Sensor (DVS) camera, can communicate quickly with our 
TPG accelerators supporting low-latency, real-time processing.

## Hardware Description
A PYNQ-Z2 board, which uses a Zynq-7000 series FPGA, is used for this demonstration. If you have a new board which requires setup, the setup guide can be 
found [here](https://pynq.readthedocs.io/en/v2.6.1/getting_started/pynq_z2_setup.html).

## Design Methodology
As ethernet streaming is the implemented approach for data transmission, a client-server arrangement is required.
![TPG Streaming Methodology to allow communication with external data sources (e.g., sensors).](/images/streaming_methodology.png)

## Synthesis Toolkit
Our project avails of a custom synthesis toolkit which extends the functionality offered through [Gegelati](https://github.com/gegelati/gegelati).
Once a TPG is trained, corresponding C++ code can be generated to execute the TPG externally from Gegelati.
The generated C++ code is then synthesised using Vitis HLS.
The C++ code generated for this project is included under the directory <span style="color:red">_**tpg_vitis_code/**_</span> within this repository. 


## Demonstration
### Step 1: Copy the chosen TPG design export onto the PYNQ board 
TPG design exports can be found under the directory <span style="color:red">_**tpg_design_exports/**_</span> within this repository.
Additionally, three TPG design exports are available; tpg_ecg.xsa, tpg_nids.xsa or tpg_dvs.xsa. 
1. Open file explorer and navigate to the network fileshare on your PYNQ board by entering <span style="color:green">_**\\\pynq\xilinx\pynq\overlays**_</span> into the address bar.
2. Create a new directory <span style="color:green">_**tpg/**_</span> within this directory.
3. Copy the chosen .xsa file for the relevant TPG into the <span style="color:green">_**\\\pynq\xilinx\pynq\overlays\tpg**_</span> directory. 

### Step 2: Download the required dataset for the application
Test datasets for each TPG can be found under the directory <span style="color:red">_**tpg_test_datasets/**_</span> within this repository.
The TPG accelerators are designed to interface with external sensors, such as DVS cameras, allowing incoming data to be streamed to the accelerator via Ethernet. 
For demonstration purposes, data can alternatively be ingested from a file and streamed over Ethernet.
1. Choose a dataset (in the form of .zip file) from the <span style="color:red">_**tpg_test_datasets/**_</span> directory found on this repository and copy to a local directory on your PC.
2. Unzip the dataset file.

### Step 3: Start the PYNQ Server
To allow the TPG accelerator to receive streaming data over ethernet, we need to start the server to listen for incoming connections to the PYNQ board.
Python files, for each application, can be found under the directory <span style="color:red">_**tpg_server_client_comm/**_</span> 
within this repository which will handle the server client communication setup.

#### Step 3.1: Connect to board through a terminal
The PYNQ-Z2 board can be accessed through a terminal - if the board is connected to a PC via micro-USB - where the terminal can be opened directly in Jupyter or opened from the host machine. 
If a terminal opened on the host PC is the desired approach, a terminal emulator such as [PuTTY](https://www.putty.org/) can be used to open a terminal and connect to the board. 

**_Configuring PuTTY to Connect to the Board_**
1. Identify the COM Port 
   - On Windows, open the Device Manager.
   - Expand the Ports section. 
   - Identify the COM port assigned to the USB Serial Port (e.g., COM4).

**_Configure PuTTY_**
1. Open PuTTY. 
2. In the session settings:
   - Select Serial as the connection type. 
   - Enter the COM port number you identified (e.g., COM4). 
   - Set the baud rate to 115200. 
3. Click Open to start the session.

#### Step 3.2: Copy the server files onto the PYNQ board
1. Open file explorer and navigate to the network fileshare on your PYNQ board by entering <span style="color:green">_**\\\pynq\xilinx**_</span> into the address bar.
2. Create a new directory <span style="color:green">_**tpg_deployments/**_</span> within this directory and navigate to it.
3. Depending on the chosen application, create a corresponding directory within <span style="color:green">_**tpg_deployments/**_</span> (e.g., if using the DVS application, create a directory called <span style="color:green">_**dvs/**_</span>).
4. Copy the <span style="color:orange">_***_server.py**_</span> python file (e.g., <span style="color:orange">_**dvs_server.py**_</span>) into this directory.

#### Step 3.2: Run the server on the PYNQ board
1. Configure PYNQ environment for executing python code by executing the following commands in the terminal:
```
sudo su
```
PYNQ-Z2 password is default to: xilinx
```
source /etc/profile.d/pynq_venv.sh
```
```
source /etc/profile.d/xrt_setup.sh
```
2. Run the python file by executing the command <span style="color:orange">_**python3 dvs_server.py**_</span>.
3. Note the IP address and port number which are outputted to the terminal console. Example:
```
[PS] Server is running. Connect from client at 192.168.1.69:6000
```

### Step 4: Start the Host Client
To stream data to the TPG accelerator, we need to start the client to connect to the PYNQ board to begin data transmission.
Similarly, as above, the necessary Python files for each application can be found under the directory <span style="color:red">_**tpg_server_client_comm/**_</span>.

1. Copy the relevant <span style="color:orange">_***_client.py**_</span> python file (e.g., <span style="color:orange">_**dvs_client.py**_</span>) locally onto your PC.
2. Copy the relevant dataset for the chosen application (e.g., dvs_test_data.txt) to the same directory as the <span style="color:orange">_***_client.py**_</span> python file locally onto your PC.
3. Open a command line terminal (command prompt on windows) and navigate to the directory where the above python and dataset files (from steps 1-2) are found locally on your PC.
4. Adjust the IP address within the <span style="color:orange">_***_client.py**_</span> to point to your boards IP address (the boards IP address is outputted to the PYNQ-Z2 terminal console once the server python file has started). 
5. Run the python file by executing the command <span style="color:orange">_**py dvs_client.py**_</span>.

## Accelerator Costs
### Accuracy Performance
Accuracy costs for the TPG Accelerators for each application task:

| Application | Accuracy (%) | Precision |  Recall |    F1   |
|:-----------:|:------------:|:---------:|:-------:|:-------:|
|     ECG     |     93.30    |  0.91358  | 0.96723 | 0.93964 |
|     NIDS    |     94.83    |  0.94583  | 0.96659 | 0.95610 |
|     DVS     |     95.94    |  0.99913  | 0.94198 | 0.96972 |

### Resource Utilisation
Resource costs for each TPG accelerator wrapped with an AXI Stream interface to facilitate streaming transmission are provided below.

With our TPG accelerators, two variants are available;
1. DSP: Use of DSP slices are allowed
2. FABRIC: Use of DSP slices are not allowed and all computations are done using FPGA fabric

| Application | Variant |    LUT [%]    |    FF [%]    | BRAM [%] |   DSP [%]   |
|:-----------:|:-------:|:-------------:|:------------:|:--------:|:-----------:|
|     ECG     |   DSP   |  1623 [3.05%] | 5001 [4.70%] |  0 [0%]  |  12 [5.45%] |
|             |  FABRIC |  4799 [9.03%] | 5479 [5.15%] |  0 [0%]  |    0 [0%]   |
|     NIDS    |   DSP   |  2641 [4.96%] | 8860 [8.32%] |  0 [0%]  | 24 [10.91%] |
|             |  FABRIC | 6418 [12.06%] | 9744 [9.16%] |  0 [0%]  |    0 [0%]   |
|     DVS     |   DSP   |  1903 [3.58%] | 2793 [2.62%] |  0 [0%]  |  10 [4.55%] |
|             |  FABRIC |  3523 [6.62%] | 3205 [3.01%] |  0 [0%]  |    0 [0%]   |

### Real-time Performance
| Application | Variant | Megasamples/sec | Latency (μs) |
|:-----------:|:-------:|:---------------:|:------------:|
|     ECG     |   DSP   |      1.9528     |    0.5031    |
|             |  FABRIC |      1.8697     |    0.5254    |
|     NIDS    |   DSP   |      1.4425     |    0.6850    |
|             |  FABRIC |      1.1386     |    0.8678    |
|     DVS     |   DSP   |      7.4115     |    0.2069    |
|             |  FABRIC |      6.8658     |    0.2233    |

# Team Members
| **Team Member**    | **Role**      | **Affiliation**                             |
|--------------------|---------------|---------------------------------------------|
| Jarlath Warner     | PhD Student   | Queen's University Belfast (QUB)            |
| Donavon Clay       | Undergraduate | Massachusetts Institute of Technology (MIT) |
| Katherine McEwan   | Undergraduate | Massachusetts Institute of Technology (MIT) |
| John McAllister    | Supervisor    | Queen's University Belfast (QUB)            |
