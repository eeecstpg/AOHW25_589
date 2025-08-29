/**
 * File generated with GEGELATI v1.2.0
 * On the 2025-08-07 16:43:36
 * With the CodeGen::TPGVitisGenerationEngine
 * Executable TPG to be used with AMD Vitis Platform.
 */
#ifndef C_dvs_H
#define C_dvs_H

#include <stdlib.h>
#include <hls_stream.h>
#include "hls_math.h"
#include "tpg_definitions.h"

enum vertices {T0, T1, T2, T3, T4, T5, T6, T7, A8, A9, };

static enum vertices root_vertex = T7;

void tpg(hls::stream<input_data_struct, FIFO_DEPTH> &input_fifo, hls::stream<int_t, FIFO_DEPTH> &output_fifo);


#endif
