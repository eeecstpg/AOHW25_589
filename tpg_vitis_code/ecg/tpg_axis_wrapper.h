#ifndef TPG_AXIS_WRAPPER_H
#define TPG_AXIS_WRAPPER_H

#include <stdlib.h>
#include <hls_stream.h>
#include "hls_math.h"
#include "tpg_definitions.h"
#include <ap_int.h>
#include <ap_axi_sdata.h>

// stream bit widths - PYNQ default for DMA AXI streams is 32 bits
#define DATA_WIDTH 32
#define OUT_WIDTH 32
#define N_ELEM 51

using raw_t = ap_uint<32>;
struct Pack {
	union {
		raw_t ui;
		data_t fx;
	};
	Pack() : ui(0) {}
};

// AXI4-Stream data types
typedef ap_axiu<DATA_WIDTH,0,0,0> in_axi_t;
typedef ap_axiu<OUT_WIDTH,0,0,0> out_axi_t;

// number of values in a given sample of input data
void tpg_axis_wrapper(hls::stream<in_axi_t> &axis_in, hls::stream<out_axi_t> &axis_out);

#endif //TPG_AXIS_WRAPPER_H
