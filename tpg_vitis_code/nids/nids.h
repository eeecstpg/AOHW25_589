/**
 * File generated with GEGELATI v1.2.0
 * On the 2024-09-10 21:31:40
 * With the CodeGen::TPGVitisGenerationEngine
 * Executable TPG to be used with AMD Vitis Platform.
 */

#ifndef C_0_double_H
#define C_0_double_H

#include <stdlib.h>
#include <hls_stream.h>
#include "hls_math.h"
#include "tpg_definitions.h"

enum vertices {T0, T1, T2, T3, T4, A5, A6, };

static enum vertices root_vertex = T4;

void tpg(hls::stream<input_data_struct, FIFO_DEPTH> &input_fifo, hls::stream<int_t, FIFO_DEPTH> &output_fifo);


#endif
