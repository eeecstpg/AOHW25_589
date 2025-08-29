#include <iostream>
#include "dvs.h"
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

#define num_event_features 9
#define num_classes 2

struct EventFrame
{
    std::vector<data_t> dvs_event;    ///< DVS Event
    int label;                        ///< DVS event label
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

std::queue<EventFrame> read_data()
{
	std::queue<EventFrame> dataset;

	// file pointer
	ifstream fin;

	// opens an existing csv file or creates a new file.
	fin.open("D:\\hotel_roc_features_0_02_test.txt", ios::out | ios::app);

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
		EventFrame eventFrame;
		size_t fieldCount = 0;

		std::istringstream s(line);
		std::string field;
		while (getline(s, field, ' '))
		{
			if (fieldCount < num_event_features)
			{
				// convert field to double and save to vector
				eventFrame.dvs_event.push_back(static_cast<data_t>(std::stod(field)));
			}
			else
			{
				// convert field to double and save to vector
				eventFrame.label = std::stoi(field);
			}
			fieldCount++;
		}
		dataset.push(eventFrame);
		fieldCount = 0;
	}
	std::cout << "Number events: " << dataset.size() << std::endl;
	return dataset;
}

void run_inference(std::queue<EventFrame> dataset)
{
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
	for (int i = 0; i < dataset.size(); i++)
	{
		// get next frame
		auto frame = dataset.front();
		auto dvs_event_frame = frame.dvs_event;

		// create FIFO from data
		data_t input_data[DATA_SIZE];
		std::copy(dvs_event_frame.begin(), dvs_event_frame.end(), input_data);
		hls::stream<input_data_struct, FIFO_DEPTH> input_fifo;
		hls::stream<int_t, FIFO_DEPTH> action;
		create_fifo_token(input_data, input_fifo);

		// pass data to TPG
		tpg(input_fifo, action);

		// get TPG decision
		int tpg_prediction = (int)action.read();
		int ground_truth = frame.label;

		// add decided prediction to classification table
		classificationTable.at(ground_truth).at(tpg_prediction)++;
		nbPerClass[ground_truth]++;

		// pop frame off
		if (!dataset.empty())
		{
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
	std::queue<EventFrame> dataset = read_data();

	// run inference
	run_inference(dataset);
	return 0;
}
