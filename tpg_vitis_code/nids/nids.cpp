/**
 * File generated with GEGELATI v1.2.0
 * On the 2024-09-10 21:31:40
 * With the CodeGen::TPGVitisGenerationEngine
 * Executable TPG to be used with AMD Vitis Platform.
 */

#include "nids.h"
#include "nids_program.h"
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
	data_t program_scores[5];
	program_scores[0] = P0(actor_data.value13, actor_data.value23, actor_data.value47);
	program_scores[1] = P1(actor_data.value42);
	program_scores[2] = P2(actor_data.value57, actor_data.value8);
	program_scores[3] = P3(actor_data.value49, actor_data.value51, actor_data.value56, actor_data.value3, actor_data.value23, actor_data.value47);
	program_scores[4] = P4(actor_data.value47);

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
	const enum vertices next[5] = {A5, A6, A6, A5, A5, };
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
	program_scores[0] = P5(actor_data.value47);
	program_scores[1] = P6(actor_data.value57, actor_data.value24);
	program_scores[2] = P7(actor_data.value73);
	program_scores[3] = P8(actor_data.value42, actor_data.value21);
	program_scores[4] = P2(actor_data.value57, actor_data.value8);

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
	const enum vertices next[5] = {A5, A6, A5, T0, A6, };
	int_t best_program = next[best_program_id];
	successor_actor_output.write(best_program);
}

void team2(hls::stream<team2_actor_data, FIFO_DEPTH> &input_fifo, hls::stream<int_t, FIFO_DEPTH> &successor_actor_output)
{
#pragma HLS INLINE off
#pragma HLS PIPELINE II=1
	team2_actor_data actor_data = input_fifo.read();

	// execute programs
	data_t program_scores[5];
	program_scores[0] = P9(actor_data.value51, actor_data.value56, actor_data.value3, actor_data.value5, actor_data.value47);
	program_scores[1] = P10(actor_data.value27, actor_data.value41, actor_data.value71, actor_data.value51, actor_data.value36);
	program_scores[2] = P11(actor_data.value73);
	program_scores[3] = P12(actor_data.value56, actor_data.value5, actor_data.value13, actor_data.value62, actor_data.value47);
	program_scores[4] = P10(actor_data.value27, actor_data.value41, actor_data.value71, actor_data.value51, actor_data.value36);

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
	const enum vertices next[5] = {A5, T1, A6, A5, T1, };
	int_t best_program = next[best_program_id];
	successor_actor_output.write(best_program);
}

void team3(hls::stream<team3_actor_data, FIFO_DEPTH> &input_fifo, hls::stream<int_t, FIFO_DEPTH> &successor_actor_output)
{
#pragma HLS INLINE off
#pragma HLS PIPELINE II=1
	team3_actor_data actor_data = input_fifo.read();

	// execute programs
	data_t program_scores[5];
	program_scores[0] = P13(actor_data.value34, actor_data.value1, actor_data.value51, actor_data.value36);
	program_scores[1] = P7(actor_data.value73);
	program_scores[2] = P14(actor_data.value32, actor_data.value20, actor_data.value72, actor_data.value49, actor_data.value77, actor_data.value17, actor_data.value62);
	program_scores[3] = P1(actor_data.value42);
	program_scores[4] = P15(actor_data.value68, actor_data.value1, actor_data.value51, actor_data.value36);

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
	const enum vertices next[5] = {T2, A5, A5, A6, T2, };
	int_t best_program = next[best_program_id];
	successor_actor_output.write(best_program);
}

void team4(hls::stream<team4_actor_data, FIFO_DEPTH> &input_fifo, hls::stream<int_t, FIFO_DEPTH> &successor_actor_output)
{
#pragma HLS INLINE off
#pragma HLS PIPELINE II=1
	team4_actor_data actor_data = input_fifo.read();

	// execute programs
	data_t program_scores[5];
	program_scores[0] = P16(actor_data.value38, actor_data.value53, actor_data.value35, actor_data.value29);
	program_scores[1] = P17(actor_data.value26, actor_data.value69, actor_data.value77);
	program_scores[2] = P18(actor_data.value20, actor_data.value34, actor_data.value11, actor_data.value75, actor_data.value37, actor_data.value35, actor_data.value3, actor_data.value1);
	program_scores[3] = P1(actor_data.value42);
	program_scores[4] = P19(actor_data.value49, actor_data.value1, actor_data.value52);

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
	const enum vertices next[5] = {A6, A6, T2, A6, T3, };
	int_t best_program = next[best_program_id];
	successor_actor_output.write(best_program);
}

void populate_actor_input_fifos(hls::stream<input_data_struct, FIFO_DEPTH> &input_fifo, hls::stream<team0_actor_data, FIFO_DEPTH> &team0_input_fifo, hls::stream<team1_actor_data, FIFO_DEPTH> &team1_input_fifo, hls::stream<team2_actor_data, FIFO_DEPTH> &team2_input_fifo, hls::stream<team3_actor_data, FIFO_DEPTH> &team3_input_fifo, hls::stream<team4_actor_data, FIFO_DEPTH> &team4_input_fifo)
{
#pragma HLS INLINE off
#pragma HLS PIPELINE II=1

	// create structs for each actors input
	input_data_struct actor_data_token = input_fifo.read();
	team0_actor_data team0_actor;
	team1_actor_data team1_actor;
	team2_actor_data team2_actor;
	team3_actor_data team3_actor;
	team4_actor_data team4_actor;

	// input data for actor team0
	team0_actor.value13 = actor_data_token.value13;
	team0_actor.value23 = actor_data_token.value23;
	team0_actor.value47 = actor_data_token.value47;
	team0_actor.value42 = actor_data_token.value42;
	team0_actor.value57 = actor_data_token.value57;
	team0_actor.value8 = actor_data_token.value8;
	team0_actor.value49 = actor_data_token.value49;
	team0_actor.value51 = actor_data_token.value51;
	team0_actor.value56 = actor_data_token.value56;
	team0_actor.value3 = actor_data_token.value3;
	team0_actor.value51 = actor_data_token.value51;
	team0_actor.value23 = actor_data_token.value23;
	team0_actor.value47 = actor_data_token.value47;
	team0_actor.value47 = actor_data_token.value47;

	// input data for actor team1
	team1_actor.value47 = actor_data_token.value47;
	team1_actor.value57 = actor_data_token.value57;
	team1_actor.value24 = actor_data_token.value24;
	team1_actor.value73 = actor_data_token.value73;
	team1_actor.value42 = actor_data_token.value42;
	team1_actor.value21 = actor_data_token.value21;
	team1_actor.value57 = actor_data_token.value57;
	team1_actor.value8 = actor_data_token.value8;

	// input data for actor team2
	team2_actor.value51 = actor_data_token.value51;
	team2_actor.value56 = actor_data_token.value56;
	team2_actor.value3 = actor_data_token.value3;
	team2_actor.value51 = actor_data_token.value51;
	team2_actor.value5 = actor_data_token.value5;
	team2_actor.value47 = actor_data_token.value47;
	team2_actor.value27 = actor_data_token.value27;
	team2_actor.value41 = actor_data_token.value41;
	team2_actor.value71 = actor_data_token.value71;
	team2_actor.value51 = actor_data_token.value51;
	team2_actor.value36 = actor_data_token.value36;
	team2_actor.value73 = actor_data_token.value73;
	team2_actor.value56 = actor_data_token.value56;
	team2_actor.value5 = actor_data_token.value5;
	team2_actor.value13 = actor_data_token.value13;
	team2_actor.value62 = actor_data_token.value62;
	team2_actor.value47 = actor_data_token.value47;
	team2_actor.value27 = actor_data_token.value27;
	team2_actor.value41 = actor_data_token.value41;
	team2_actor.value71 = actor_data_token.value71;
	team2_actor.value51 = actor_data_token.value51;
	team2_actor.value36 = actor_data_token.value36;

	// input data for actor team3
	team3_actor.value34 = actor_data_token.value34;
	team3_actor.value1 = actor_data_token.value1;
	team3_actor.value1 = actor_data_token.value1;
	team3_actor.value51 = actor_data_token.value51;
	team3_actor.value36 = actor_data_token.value36;
	team3_actor.value73 = actor_data_token.value73;
	team3_actor.value32 = actor_data_token.value32;
	team3_actor.value20 = actor_data_token.value20;
	team3_actor.value72 = actor_data_token.value72;
	team3_actor.value49 = actor_data_token.value49;
	team3_actor.value77 = actor_data_token.value77;
	team3_actor.value17 = actor_data_token.value17;
	team3_actor.value62 = actor_data_token.value62;
	team3_actor.value17 = actor_data_token.value17;
	team3_actor.value42 = actor_data_token.value42;
	team3_actor.value68 = actor_data_token.value68;
	team3_actor.value1 = actor_data_token.value1;
	team3_actor.value51 = actor_data_token.value51;
	team3_actor.value36 = actor_data_token.value36;

	// input data for actor team4
	team4_actor.value38 = actor_data_token.value38;
	team4_actor.value53 = actor_data_token.value53;
	team4_actor.value35 = actor_data_token.value35;
	team4_actor.value29 = actor_data_token.value29;
	team4_actor.value26 = actor_data_token.value26;
	team4_actor.value69 = actor_data_token.value69;
	team4_actor.value77 = actor_data_token.value77;
	team4_actor.value20 = actor_data_token.value20;
	team4_actor.value34 = actor_data_token.value34;
	team4_actor.value11 = actor_data_token.value11;
	team4_actor.value75 = actor_data_token.value75;
	team4_actor.value37 = actor_data_token.value37;
	team4_actor.value35 = actor_data_token.value35;
	team4_actor.value3 = actor_data_token.value3;
	team4_actor.value1 = actor_data_token.value1;
	team4_actor.value42 = actor_data_token.value42;
	team4_actor.value49 = actor_data_token.value49;
	team4_actor.value1 = actor_data_token.value1;
	team4_actor.value52 = actor_data_token.value52;

	// write actor FIFOs to relevant streams
	team0_input_fifo.write(team0_actor);
	team1_input_fifo.write(team1_actor);
	team2_input_fifo.write(team2_actor);
	team3_input_fifo.write(team3_actor);
	team4_input_fifo.write(team4_actor);
}

void filter_scores(hls::stream<int_t, FIFO_DEPTH> &team0_output_fifo, hls::stream<int_t, FIFO_DEPTH> &team1_output_fifo, hls::stream<int_t, FIFO_DEPTH> &team2_output_fifo, hls::stream<int_t, FIFO_DEPTH> &team3_output_fifo, hls::stream<int_t, FIFO_DEPTH> &team4_output_fifo, hls::stream<int_t, FIFO_DEPTH> &tpg_output)
{
#pragma HLS INLINE off
#pragma HLS PIPELINE II=1
	// get the output of each team
	int_t team0_output = team0_output_fifo.read();
	int_t team1_output = team1_output_fifo.read();
	int_t team2_output = team2_output_fifo.read();
	int_t team3_output = team3_output_fifo.read();
	int_t team4_output = team4_output_fifo.read();

	int_t root_decision = team4_output;

	// find the best score
	int_t next_decision_step = root_decision;
	for (int depth = 0; depth <= 5+1; depth++)
	{
#pragma HLS UNROLL factor=6
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
			case T3:
				next_decision_step = team3_output;
				break;
			default:
				break;
		}
	}

	// produce token for final score based on decision path
	tpg_output.write((next_decision_step == A5) ? 1 : 0);
}

void tpg(hls::stream<input_data_struct, FIFO_DEPTH> &input_fifo, hls::stream<int_t, FIFO_DEPTH> &output_fifo)
{
#pragma HLS DATAFLOW

	// create FIFOs for each dataflow actor input
	hls::stream<team0_actor_data, FIFO_DEPTH> team0_input_fifo;
	hls::stream<team1_actor_data, FIFO_DEPTH> team1_input_fifo;
	hls::stream<team2_actor_data, FIFO_DEPTH> team2_input_fifo;
	hls::stream<team3_actor_data, FIFO_DEPTH> team3_input_fifo;
	hls::stream<team4_actor_data, FIFO_DEPTH> team4_input_fifo;
	populate_actor_input_fifos(input_fifo, team0_input_fifo, team1_input_fifo, team2_input_fifo, team3_input_fifo, team4_input_fifo);

	// create FIFOs for each dataflow actor output
	hls::stream<int_t, FIFO_DEPTH> team0_output_fifo;
	hls::stream<int_t, FIFO_DEPTH> team1_output_fifo;
	hls::stream<int_t, FIFO_DEPTH> team2_output_fifo;
	hls::stream<int_t, FIFO_DEPTH> team3_output_fifo;
	hls::stream<int_t, FIFO_DEPTH> team4_output_fifo;

	// execute dataflow actors
	team0(team0_input_fifo, team0_output_fifo);
	team1(team1_input_fifo, team1_output_fifo);
	team2(team2_input_fifo, team2_output_fifo);
	team3(team3_input_fifo, team3_output_fifo);
	team4(team4_input_fifo, team4_output_fifo);

	// construct TPG decision path
	filter_scores(team0_output_fifo, team1_output_fifo, team2_output_fifo, team3_output_fifo, team4_output_fifo, output_fifo);
};
