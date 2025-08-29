/**
 * File generated with GEGELATI v1.2.0
 * On the 2025-08-06 17:46:04
 * With the CodeGen::TPGVitisGenerationEngine
 * Executable TPG to be used with AMD Vitis Platform.
 */
#include "tpg_axis_wrapper.h"
#include <hls_stream.h>
#include <ap_int.h>
#include <ap_axi_sdata.h>

#include "dvs.h"
#include "dvs_program.h"

void tpg(hls::stream<input_data_struct, FIFO_DEPTH> &input_fifo, hls::stream<int_t, FIFO_DEPTH> &output_fifo);

// Converts the 32-bit wide AXI stream of values into an input fifo suitable for the tpg classifier. Packages
// N_ELEM values into an input_data_struct necessary for the tpg to process
void unpack_stage(hls::stream<in_axi_t> &axis_in, hls::stream<input_data_struct, FIFO_DEPTH> &input_fifo)
{
#pragma HLS INLINE off
	input_data_struct data;
#pragma HLS aggregate variable=data
	data_t tmp[N_ELEM];
#pragma HLS ARRAY_PARTITION complete variable=tmp dim=1
	Pack p;

	// read in N_ELEM beats from AXI stream
	for (int i = 0; i < N_ELEM; ++i)
	{
#pragma HLS PIPELINE II=1
		in_axi_t pkt = axis_in.read();
		raw_t bits = pkt.data;
		p.ui = bits;
		tmp[i] = p.fx;
		#define UNP(k) data.value##k = tmp[k];
			UNP(0)	UNP(1)	UNP(2)	UNP(3)	UNP(4)
			UNP(5)	UNP(6)	UNP(7)	UNP(8)
		#undef UNP
	}
	input_fifo.write(data);
}

// runs the tpg classifier
void classify_stage(hls::stream<input_data_struct, FIFO_DEPTH> &input_fifo, hls::stream<int_t, FIFO_DEPTH> &output_fifo)
{
#pragma HLS INLINE off
#pragma HLS DATAFLOW
	tpg(input_fifo, output_fifo);
}

// Builds the output axi stream from the classifer output
void pack_stage(hls::stream<int_t> &output_fifo, hls::stream<out_axi_t> &axis_out)
{
#pragma HLS INLINE off
#pragma HLS PIPELINE II=1
	// read classifier output from fifo_out and stream out
	int_t result = output_fifo.read();
	out_axi_t out_pkt;
	out_pkt.data = result;
	out_pkt.last = 1;           // mark end of this packet
	out_pkt.keep = -1;
	out_pkt.strb = out_pkt.keep;
	axis_out.write(out_pkt);
}

// top-level wrapper function
void tpg_axis_wrapper(hls::stream<in_axi_t> &axis_in, hls::stream<out_axi_t> &axis_out)
{
#pragma HLS INTERFACE axis          port=axis_in
#pragma HLS INTERFACE axis          port=axis_out
#pragma HLS INTERFACE ap_ctrl_none  port=return
#pragma HLS DATAFLOW 

	static hls::stream<input_data_struct, FIFO_DEPTH> input_fifo;
	static hls::stream<int_t, FIFO_DEPTH>  output_fifo;
#pragma HLS STREAM variable=input_fifo  depth=FIFO_DEPTH
#pragma HLS STREAM variable=output_fifo depth=FIFO_DEPTH
	unpack_stage(axis_in, input_fifo);
	classify_stage(input_fifo, output_fifo);
	pack_stage(output_fifo, axis_out);
}
