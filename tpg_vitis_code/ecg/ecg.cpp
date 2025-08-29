/**
 * File generated with GEGELATI v1.2.0
 * On the 2024-09-11 15:04:12
 * With the CodeGen::TPGVitisGenerationEngine
 * Executable TPG to be used with AMD Vitis Platform.
 */

#include "ecg.h"
#include "ecg_program.h"
#include <limits.h>
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>

#include <float.h>
#include <hls_stream.h>
#include <cmath>
#include <limits>

void team0(hls::stream<team0_actor_data, FIFO_DEPTH> &input_fifo, hls::stream<int_t, FIFO_DEPTH> &successor_actor_output)
{
#pragma HLS INLINE off
#pragma HLS PIPELINE II=1
	team0_actor_data actor_data = input_fifo.read();

	// execute programs
	data_t program_scores[4];
	program_scores[0] = P0(actor_data.value28, actor_data.value16);
	program_scores[1] = P1(actor_data.value7, actor_data.value40, actor_data.value15, actor_data.value24, actor_data.value5, actor_data.value46, actor_data.value4, actor_data.value31, actor_data.value48, actor_data.value37, actor_data.value30, actor_data.value35);
	program_scores[2] = P2(actor_data.value22, actor_data.value36);
	program_scores[3] = P3(actor_data.value14, actor_data.value16, actor_data.value7, actor_data.value17, actor_data.value30);

	// determine best programs
	int_t best_program_id = 0;
	data_t best_program_score = program_scores[0];
	data_t program_score;
	for (int i = 1; i < 4; i++)
	{
#pragma HLS UNROLL factor=3
		program_score = program_scores[i];
		if (program_score >= best_program_score)
		{
			best_program_id = i;
			best_program_score = program_score;
		}
	}

	// populate team output FIFO
	const enum vertices next[4] = {A4, A4, A4, A5, };
	int_t best_program = next[best_program_id];
	successor_actor_output.write(best_program);
}

void team1(hls::stream<team1_actor_data, FIFO_DEPTH> &input_fifo, hls::stream<int_t, FIFO_DEPTH> &successor_actor_output)
{
#pragma HLS INLINE off
#pragma HLS PIPELINE II=1
	team1_actor_data actor_data = input_fifo.read();

	// execute programs
	data_t program_scores[5];
	program_scores[0] = P4(actor_data.value43, actor_data.value36, actor_data.value38, actor_data.value37);
	program_scores[1] = P2(actor_data.value22, actor_data.value36);
	program_scores[2] = P5(actor_data.value45, actor_data.value41, actor_data.value46, actor_data.value17, actor_data.value30);
	program_scores[3] = P2(actor_data.value22, actor_data.value36);
	program_scores[4] = P6(actor_data.value43, actor_data.value36, actor_data.value38, actor_data.value37);

	// determine best programs
	int_t best_program_id = 0;
	data_t best_program_score = program_scores[0];
	data_t program_score;
	for (int i = 1; i < 5; i++)
	{
#pragma HLS UNROLL factor=4
		program_score = program_scores[i];
		if (program_score >= best_program_score)
		{
			best_program_id = i;
			best_program_score = program_score;
		}
	}

	// populate team output FIFO
	const enum vertices next[5] = {A4, A4, T0, A4, A4, };
	int_t best_program = next[best_program_id];
	successor_actor_output.write(best_program);
}

void team2(hls::stream<team2_actor_data, FIFO_DEPTH> &input_fifo, hls::stream<int_t, FIFO_DEPTH> &successor_actor_output)
{
#pragma HLS INLINE off
#pragma HLS PIPELINE II=1
	team2_actor_data actor_data = input_fifo.read();

	// execute programs
	data_t program_scores[4];
	program_scores[0] = P7(actor_data.value11, actor_data.value19, actor_data.value6, actor_data.value49, actor_data.value16, actor_data.value20, actor_data.value13);
	program_scores[1] = P8(actor_data.value22, actor_data.value0);
	program_scores[2] = P9(actor_data.value17, actor_data.value44, actor_data.value5, actor_data.value0, actor_data.value31, actor_data.value21, actor_data.value41, actor_data.value7, actor_data.value22, actor_data.value4, actor_data.value43, actor_data.value37, actor_data.value38);
	program_scores[3] = P10(actor_data.value0, actor_data.value21, actor_data.value43, actor_data.value22, actor_data.value42, actor_data.value3, actor_data.value8, actor_data.value33, actor_data.value29);

	// determine best programs
	int_t best_program_id = 0;
	data_t best_program_score = program_scores[0];
	data_t program_score;
	for (int i = 1; i < 4; i++)
	{
#pragma HLS UNROLL factor=3
		program_score = program_scores[i];
		if (program_score >= best_program_score)
		{
			best_program_id = i;
			best_program_score = program_score;
		}
	}

	// populate team output FIFO
	const enum vertices next[4] = {T1, A4, A5, A4, };
	int_t best_program = next[best_program_id];
	successor_actor_output.write(best_program);
}

void team3(hls::stream<team3_actor_data, FIFO_DEPTH> &input_fifo, hls::stream<int_t, FIFO_DEPTH> &successor_actor_output)
{
#pragma HLS INLINE off
#pragma HLS PIPELINE II=1
	team3_actor_data actor_data = input_fifo.read();

	// execute programs
	data_t program_scores[3];
	program_scores[0] = P11(actor_data.value23, actor_data.value29, actor_data.value33);
	program_scores[1] = P12(actor_data.value16, actor_data.value11, actor_data.value19, actor_data.value49, actor_data.value46, actor_data.value47, actor_data.value42, actor_data.value44, actor_data.value24, actor_data.value40, actor_data.value20, actor_data.value13);
	program_scores[2] = P13(actor_data.value25);

	// determine best programs
	int_t best_program_id = 0;
	data_t best_program_score = program_scores[0];
	data_t program_score;
	for (int i = 1; i < 3; i++)
	{
#pragma HLS UNROLL factor=2
		program_score = program_scores[i];
		if (program_score >= best_program_score)
		{
			best_program_id = i;
			best_program_score = program_score;
		}
	}

	// populate team output FIFO
	const enum vertices next[3] = {A4, T2, A4, };
	int_t best_program = next[best_program_id];
	successor_actor_output.write(best_program);
}

void populate_actor_input_fifos(hls::stream<input_data_struct, FIFO_DEPTH> &input_fifo, hls::stream<team0_actor_data, FIFO_DEPTH> &team0_input_fifo, hls::stream<team1_actor_data, FIFO_DEPTH> &team1_input_fifo, hls::stream<team2_actor_data, FIFO_DEPTH> &team2_input_fifo, hls::stream<team3_actor_data, FIFO_DEPTH> &team3_input_fifo)
{
#pragma HLS INLINE off
#pragma HLS PIPELINE II=1

	// create structs for each actors input
	input_data_struct actor_data_token = input_fifo.read();
	team0_actor_data team0_actor;
	team1_actor_data team1_actor;
	team2_actor_data team2_actor;
	team3_actor_data team3_actor;

	// input data for actor team0
	team0_actor.value28 = actor_data_token.value28;
	team0_actor.value16 = actor_data_token.value16;
	team0_actor.value7 = actor_data_token.value7;
	team0_actor.value40 = actor_data_token.value40;
	team0_actor.value15 = actor_data_token.value15;
	team0_actor.value24 = actor_data_token.value24;
	team0_actor.value5 = actor_data_token.value5;
	team0_actor.value46 = actor_data_token.value46;
	team0_actor.value4 = actor_data_token.value4;
	team0_actor.value31 = actor_data_token.value31;
	team0_actor.value48 = actor_data_token.value48;
	team0_actor.value37 = actor_data_token.value37;
	team0_actor.value30 = actor_data_token.value30;
	team0_actor.value35 = actor_data_token.value35;
	team0_actor.value22 = actor_data_token.value22;
	team0_actor.value36 = actor_data_token.value36;
	team0_actor.value14 = actor_data_token.value14;
	team0_actor.value16 = actor_data_token.value16;
	team0_actor.value7 = actor_data_token.value7;
	team0_actor.value17 = actor_data_token.value17;
	team0_actor.value30 = actor_data_token.value30;

	// input data for actor team1
	team1_actor.value43 = actor_data_token.value43;
	team1_actor.value36 = actor_data_token.value36;
	team1_actor.value38 = actor_data_token.value38;
	team1_actor.value37 = actor_data_token.value37;
	team1_actor.value22 = actor_data_token.value22;
	team1_actor.value36 = actor_data_token.value36;
	team1_actor.value45 = actor_data_token.value45;
	team1_actor.value41 = actor_data_token.value41;
	team1_actor.value46 = actor_data_token.value46;
	team1_actor.value17 = actor_data_token.value17;
	team1_actor.value30 = actor_data_token.value30;
	team1_actor.value22 = actor_data_token.value22;
	team1_actor.value36 = actor_data_token.value36;
	team1_actor.value43 = actor_data_token.value43;
	team1_actor.value36 = actor_data_token.value36;
	team1_actor.value38 = actor_data_token.value38;
	team1_actor.value37 = actor_data_token.value37;

	// input data for actor team2
	team2_actor.value11 = actor_data_token.value11;
	team2_actor.value19 = actor_data_token.value19;
	team2_actor.value6 = actor_data_token.value6;
	team2_actor.value49 = actor_data_token.value49;
	team2_actor.value16 = actor_data_token.value16;
	team2_actor.value20 = actor_data_token.value20;
	team2_actor.value13 = actor_data_token.value13;
	team2_actor.value22 = actor_data_token.value22;
	team2_actor.value0 = actor_data_token.value0;
	team2_actor.value17 = actor_data_token.value17;
	team2_actor.value44 = actor_data_token.value44;
	team2_actor.value5 = actor_data_token.value5;
	team2_actor.value0 = actor_data_token.value0;
	team2_actor.value31 = actor_data_token.value31;
	team2_actor.value21 = actor_data_token.value21;
	team2_actor.value41 = actor_data_token.value41;
	team2_actor.value7 = actor_data_token.value7;
	team2_actor.value22 = actor_data_token.value22;
	team2_actor.value4 = actor_data_token.value4;
	team2_actor.value17 = actor_data_token.value17;
	team2_actor.value43 = actor_data_token.value43;
	team2_actor.value37 = actor_data_token.value37;
	team2_actor.value38 = actor_data_token.value38;
	team2_actor.value0 = actor_data_token.value0;
	team2_actor.value21 = actor_data_token.value21;
	team2_actor.value43 = actor_data_token.value43;
	team2_actor.value22 = actor_data_token.value22;
	team2_actor.value42 = actor_data_token.value42;
	team2_actor.value3 = actor_data_token.value3;
	team2_actor.value8 = actor_data_token.value8;
	team2_actor.value33 = actor_data_token.value33;
	team2_actor.value29 = actor_data_token.value29;

	// input data for actor team3
	team3_actor.value23 = actor_data_token.value23;
	team3_actor.value29 = actor_data_token.value29;
	team3_actor.value33 = actor_data_token.value33;
	team3_actor.value16 = actor_data_token.value16;
	team3_actor.value11 = actor_data_token.value11;
	team3_actor.value19 = actor_data_token.value19;
	team3_actor.value49 = actor_data_token.value49;
	team3_actor.value46 = actor_data_token.value46;
	team3_actor.value47 = actor_data_token.value47;
	team3_actor.value42 = actor_data_token.value42;
	team3_actor.value44 = actor_data_token.value44;
	team3_actor.value11 = actor_data_token.value11;
	team3_actor.value24 = actor_data_token.value24;
	team3_actor.value40 = actor_data_token.value40;
	team3_actor.value20 = actor_data_token.value20;
	team3_actor.value13 = actor_data_token.value13;
	team3_actor.value25 = actor_data_token.value25;

	// write actor FIFOs to relevant streams
	team0_input_fifo.write(team0_actor);
	team1_input_fifo.write(team1_actor);
	team2_input_fifo.write(team2_actor);
	team3_input_fifo.write(team3_actor);
}

void filter_scores(hls::stream<int_t, FIFO_DEPTH> &team0_output_fifo, hls::stream<int_t, FIFO_DEPTH> &team1_output_fifo, hls::stream<int_t, FIFO_DEPTH> &team2_output_fifo, hls::stream<int_t, FIFO_DEPTH> &team3_output_fifo, hls::stream<int_t, FIFO_DEPTH> &tpg_output)
{
#pragma HLS INLINE off
#pragma HLS PIPELINE II=1
	// get the output of each team
	int_t team0_output = team0_output_fifo.read();
	int_t team1_output = team1_output_fifo.read();
	int_t team2_output = team2_output_fifo.read();
	int_t team3_output = team3_output_fifo.read();

	int_t root_decision = team3_output;

	// find the best score
	int_t next_decision_step = root_decision;
	for (int depth = 0; depth <= 5; depth++)
	{
#pragma HLS UNROLL factor=5
		switch (next_decision_step)
		{
			case T0:
				next_decision_step = team0_output;
				break;
			case T1:
				next_decision_step = team1_output;
				break;
			case T2:
				next_decision_step = team2_output;
				break;
			default:
				break;
		}
	}

	// produce token for final score based on decision path
	tpg_output.write((next_decision_step == A4) ? 1 : 0);
}

void tpg(hls::stream<input_data_struct, FIFO_DEPTH> &input_fifo, hls::stream<int_t, FIFO_DEPTH> &output_fifo)
{
#pragma HLS DATAFLOW

	// create FIFOs for each dataflow actor input
	hls::stream<team0_actor_data, FIFO_DEPTH> team0_input_fifo;
	hls::stream<team1_actor_data, FIFO_DEPTH> team1_input_fifo;
	hls::stream<team2_actor_data, FIFO_DEPTH> team2_input_fifo;
	hls::stream<team3_actor_data, FIFO_DEPTH> team3_input_fifo;
	populate_actor_input_fifos(input_fifo, team0_input_fifo, team1_input_fifo, team2_input_fifo, team3_input_fifo);

	// create FIFOs for each dataflow actor output
	hls::stream<int_t, FIFO_DEPTH> team0_output_fifo;
	hls::stream<int_t, FIFO_DEPTH> team1_output_fifo;
	hls::stream<int_t, FIFO_DEPTH> team2_output_fifo;
	hls::stream<int_t, FIFO_DEPTH> team3_output_fifo;

	// execute dataflow actors
	team0(team0_input_fifo, team0_output_fifo);
	team1(team1_input_fifo, team1_output_fifo);
	team2(team2_input_fifo, team2_output_fifo);
	team3(team3_input_fifo, team3_output_fifo);

	// construct TPG decision path
	filter_scores(team0_output_fifo, team1_output_fifo, team2_output_fifo, team3_output_fifo, output_fifo);
};
