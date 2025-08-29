/**
 * File generated with GEGELATI v1.2.0
 * On the 2025-08-06 17:46:04
 * With the CodeGen::TPGVitisGenerationEngine
 * Executable TPG to be used with AMD Vitis Platform.
 */
#ifndef TPG_AXIS_WRAPPER_H
#define TPG_AXIS_WRAPPER_H

#include <hls_stream.h>
#include <ap_int.h>
#include <ap_axi_sdata.h>
#include <stdlib.h>
#include "hls_math.h"
#include "tpg_definitions.h"

// stream bit widths - PYNQ default for DMA AXI streams is 32 bits
#define DATA_WIDTH 32
#define OUT_WIDTH 32
#define N_ELEM 9

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
