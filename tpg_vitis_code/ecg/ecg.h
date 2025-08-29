/**
 * File generated with GEGELATI v1.2.0
 * On the 2024-09-11 15:04:12
 * With the CodeGen::TPGVitisGenerationEngine
 * Executable TPG to be used with AMD Vitis Platform.
 */

#ifndef C_ecg_H
#define C_ecg_H

#include <stdlib.h>
#include <hls_stream.h>
#include "hls_math.h"
#include "tpg_definitions.h"

enum vertices {T0, T1, T2, T3, A4, A5, };

static enum vertices root_vertex = T3;

void tpg(hls::stream<input_data_struct, FIFO_DEPTH> &input_fifo, hls::stream<int_t, FIFO_DEPTH> &output_fifo);


#endif
