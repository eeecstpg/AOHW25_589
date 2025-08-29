#include <iostream>
#include "ecg.h"
#include "math.h"
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <queue>
#include <map>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <ap_fixed.h>
#include "tpg_axis_wrapper.h"

using namespace std;
typedef short result_t;

#define num_beat_samples 51
#define num_classes 2

struct BeatFrame
{
    std::vector<data_t> ecg_beat;     ///< ECG Beat frame
    int label;                        ///< ECG Beat label
};

void create_fifo_token(const data_t input_data[DATA_SIZE], hls::stream<input_data_struct, 1> &fifo_token)
{
	input_data_struct input_data_struct_token;
	input_data_struct_token.value0 = input_data[0];
	input_data_struct_token.value1 = input_data[1];
	input_data_struct_token.value2 = input_data[2];
	input_data_struct_token.value3 = input_data[3];
	input_data_struct_token.value4 = input_data[4];
	input_data_struct_token.value5 = input_data[5];
	input_data_struct_token.value6 = input_data[6];
	input_data_struct_token.value7 = input_data[7];
	input_data_struct_token.value8 = input_data[8];
	input_data_struct_token.value9 = input_data[9];

	input_data_struct_token.value10 = input_data[10];
	input_data_struct_token.value11 = input_data[11];
	input_data_struct_token.value12 = input_data[12];
	input_data_struct_token.value13 = input_data[13];
	input_data_struct_token.value14 = input_data[14];
	input_data_struct_token.value15 = input_data[15];
	input_data_struct_token.value16 = input_data[16];
	input_data_struct_token.value17 = input_data[17];
	input_data_struct_token.value18 = input_data[18];
	input_data_struct_token.value19 = input_data[19];

	input_data_struct_token.value20 = input_data[20];
	input_data_struct_token.value21 = input_data[21];
	input_data_struct_token.value22 = input_data[22];
	input_data_struct_token.value23 = input_data[23];
	input_data_struct_token.value24 = input_data[24];
	input_data_struct_token.value25 = input_data[25];
	input_data_struct_token.value26 = input_data[26];
	input_data_struct_token.value27 = input_data[27];
	input_data_struct_token.value28 = input_data[28];
	input_data_struct_token.value29 = input_data[29];

	input_data_struct_token.value30 = input_data[30];
	input_data_struct_token.value31 = input_data[31];
	input_data_struct_token.value32 = input_data[32];
	input_data_struct_token.value33 = input_data[33];
	input_data_struct_token.value34 = input_data[34];
	input_data_struct_token.value35 = input_data[35];
	input_data_struct_token.value36 = input_data[36];
	input_data_struct_token.value37 = input_data[37];
	input_data_struct_token.value38 = input_data[38];
	input_data_struct_token.value39 = input_data[39];

	input_data_struct_token.value40 = input_data[40];
	input_data_struct_token.value41 = input_data[41];
	input_data_struct_token.value42 = input_data[42];
	input_data_struct_token.value43 = input_data[43];
	input_data_struct_token.value44 = input_data[44];
	input_data_struct_token.value45 = input_data[45];
	input_data_struct_token.value46 = input_data[46];
	input_data_struct_token.value47 = input_data[47];
	input_data_struct_token.value48 = input_data[48];
	input_data_struct_token.value49 = input_data[49];
	input_data_struct_token.value50 = input_data[50];
	fifo_token.write(input_data_struct_token);
}

int getMaxVote(std::vector<int> votes)
{
    std::map<int, int> counters;
    for(auto vote: votes)
    {
        ++counters[vote];
    }

    auto pr = std::max_element(counters.begin(), counters.end(), [](const auto &x, const auto &y) {
        return x.second < y.second;
    });

    return pr->first;
}

std::queue<BeatFrame> read_data()
{
	std::queue<BeatFrame> dataset;

	// file pointer
	ifstream fin;

	// opens an existing csv file or creates a new file.
	fin.open("D:\\vitisECGTestData.csv", ios::out | ios::app);

	if (fin.fail())
	{
	    // file could not be opened
		std::cout << "File could not be opened" << std::endl;
	}

	// read the Data from the file as string vector
	std::vector<string> row;
	string line;

	while (std::getline(fin, line))
	{
		BeatFrame beatFrame;
		size_t fieldCount = 0;

		std::istringstream s(line);
		std::string field;
		while (getline(s, field,','))
		{
			if (fieldCount < num_beat_samples)
			{
				// convert field to double and save to vector
				beatFrame.ecg_beat.push_back(static_cast<data_t>(std::stod(field)));
			}
			else
			{
				// convert field to double and save to vector
				beatFrame.label = std::stoi(field);
			}
			fieldCount++;
		}

		dataset.push(beatFrame);
		fieldCount = 0;
	}
	std::cout << "Number samples: " << dataset.size() << std::endl;
	return dataset;
}

void run_inference(std::queue<BeatFrame> dataset)
{
	size_t buffer_size = 5;

	// create FIFO inference_buffer
	std::queue<BeatFrame> inference_buffer;

	// fill inference_buffer at start
	while (inference_buffer.size() < buffer_size)
	{
		inference_buffer.push(dataset.front());
		dataset.pop();
	}

    std::vector<int> tpg_predictions;
    std::vector<int> frame_labels;
    uint64_t nbPerClass[num_classes] = {0};
    std::vector<std::vector<uint64_t>> classificationTable(num_classes, std::vector<uint64_t>(num_classes, 0));

    // set up AXI stream
	hls::stream<in_axi_t>  in_stream;
	hls::stream<out_axi_t> out_stream;
	ap_uint<32> dbg_in = 0;
	ap_uint<32> dbg_out  = 0;
	bool first_frame = true;

    // run inference phase
	while (!inference_buffer.empty())
	{
		// create copy of current buffer to iterate over
		std::queue<BeatFrame> buffer_copy(inference_buffer);

		// iterate over buffer copy and feed data to TPG and record predictions
		while (!buffer_copy.empty())
		{
			// get next frame
			auto frame = buffer_copy.front();
			auto frame_ecg = frame.ecg_beat;

			// populate AXI stream
			for (int i = 0; i < num_beat_samples; ++i)
			{
				Pack p;
				p.fx = frame_ecg[i];  // `fx` is of type data_t
				in_axi_t beat;
				beat.data = p.ui;           // Packs the raw bits of the fixed-point number
				beat.keep = -1;
				beat.strb = -1;
				beat.last = (i == num_beat_samples  - 1);
				in_stream.write(beat);
			}
			first_frame = false;

			// send to TPG using AXI stream
			tpg_axis_wrapper(in_stream, out_stream);
			out_axi_t res = out_stream.read();

			// get TPG decision
			tpg_predictions.push_back((int)res.data);
			frame_labels.push_back(frame.label);

			// pop from queue
			buffer_copy.pop();
		}

		// get max vote from predictions
		auto prediction = getMaxVote(tpg_predictions);
		auto ground_truth = getMaxVote(frame_labels);

		tpg_predictions = std::vector<int>();
		frame_labels = std::vector<int>();

		// add decided prediction to classification table
		classificationTable.at(ground_truth).at(prediction)++;
		nbPerClass[ground_truth]++;

		// pop frame off and push new frame on
		inference_buffer.pop();
		if (!dataset.empty())
		{
			inference_buffer.push(dataset.front());
			dataset.pop();
		}
	}

	// print header row
	printf("\t");
	for (int i = 0; i < num_classes; i++)
	{
		printf("%d\t", i);
	}
	printf("Nb\n");

	// print results for each class
	for (int i = 0; i < num_classes; i++)
	{
		printf("%d\t", i);
		for (int j = 0; j < num_classes; j++)
		{
			// to avoid NaN
			if (nbPerClass[i] == 0)
			{
				printf("%2.7f\t", 0.0);
			}
			else
			{
				printf("%2.7f\t", 100.0 * (double) classificationTable[i][j] / (double) nbPerClass[i]);
			}

		}
		printf("%d\n", nbPerClass[i]);
	}
}

int main(int argc, char **argv)
{
	// read data
	std::queue<BeatFrame> dataset = read_data();

	// run inference
	run_inference(dataset);
	return 0;
}
