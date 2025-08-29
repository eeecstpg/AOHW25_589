/**
 * File generated with GEGELATI v1.2.0
 * On the 2025-08-07 16:43:36
 * With the CodeGen::TPGVitisGenerationEngine
 * Executable TPG to be used with AMD Vitis Platform.
 */
#include "dvs.h"
#include "dvs_program.h"
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
	data_t program_scores[2];
	program_scores[0] = P0(actor_data.value2, actor_data.value5);
	program_scores[1] = P1();

	// determine best programs
	int_t best_program_id = 0;
	data_t best_program_score = program_scores[0];
	data_t program_score;
	for (int i = 1; i < 2; i++)
	{
#pragma HLS UNROLL factor=1
		program_score = program_scores[i];
		if (program_score >= best_program_score)
		{
			best_program_id = i;
			best_program_score = program_score;
		}
	}

	// populate team output FIFO
	const enum vertices next[2] = {A8, A9, };
	int_t best_program = next[best_program_id];
	successor_actor_output.write(best_program);
}

void team1(hls::stream<team1_actor_data, FIFO_DEPTH> &input_fifo, hls::stream<int_t, FIFO_DEPTH> &successor_actor_output)
{
#pragma HLS INLINE off
#pragma HLS PIPELINE II=1
	team1_actor_data actor_data = input_fifo.read();

	// execute programs
	data_t program_scores[2];
	program_scores[0] = P2(actor_data.value5, actor_data.value8);
	program_scores[1] = P3(actor_data.value5, actor_data.value4, actor_data.value7);

	// determine best programs
	int_t best_program_id = 0;
	data_t best_program_score = program_scores[0];
	data_t program_score;
	for (int i = 1; i < 2; i++)
	{
#pragma HLS UNROLL factor=1
		program_score = program_scores[i];
		if (program_score >= best_program_score)
		{
			best_program_id = i;
			best_program_score = program_score;
		}
	}

	// populate team output FIFO
	const enum vertices next[2] = {A9, A8, };
	int_t best_program = next[best_program_id];
	successor_actor_output.write(best_program);
}

void team2(hls::stream<team2_actor_data, FIFO_DEPTH> &input_fifo, hls::stream<int_t, FIFO_DEPTH> &successor_actor_output)
{
#pragma HLS INLINE off
#pragma HLS PIPELINE II=1
	team2_actor_data actor_data = input_fifo.read();

	// execute programs
	data_t program_scores[3];
	program_scores[0] = P2(actor_data.value5, actor_data.value8);
	program_scores[1] = P4(actor_data.value5, actor_data.value4, actor_data.value7);
	program_scores[2] = P5(actor_data.value4, actor_data.value5);

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
	const enum vertices next[3] = {A9, A8, A9, };
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
	program_scores[0] = P2(actor_data.value5, actor_data.value8);
	program_scores[1] = P6(actor_data.value4, actor_data.value3, actor_data.value7);
	program_scores[2] = P2(actor_data.value5, actor_data.value8);
	program_scores[3] = P0(actor_data.value2, actor_data.value5);
	program_scores[4] = P3(actor_data.value5, actor_data.value4, actor_data.value7);

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
	const enum vertices next[5] = {A9, T0, A9, A8, A8, };
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
	program_scores[0] = P7(actor_data.value0, actor_data.value7, actor_data.value4, actor_data.value3, actor_data.value5);
	program_scores[1] = P1();
	program_scores[2] = P8(actor_data.value2, actor_data.value5);
	program_scores[3] = P9(actor_data.value7, actor_data.value4);
	program_scores[4] = P10(actor_data.value4);

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
	const enum vertices next[5] = {T0, A9, T3, T0, A9, };
	int_t best_program = next[best_program_id];
	successor_actor_output.write(best_program);
}

void team5(hls::stream<team5_actor_data, FIFO_DEPTH> &input_fifo, hls::stream<int_t, FIFO_DEPTH> &successor_actor_output)
{
#pragma HLS INLINE off
#pragma HLS PIPELINE II=1
	team5_actor_data actor_data = input_fifo.read();

	// execute programs
	data_t program_scores[4];
	program_scores[0] = P11(actor_data.value4, actor_data.value2, actor_data.value0, actor_data.value7, actor_data.value8);
	program_scores[1] = P12(actor_data.value8, actor_data.value0);
	program_scores[2] = P13(actor_data.value7, actor_data.value3, actor_data.value5, actor_data.value2, actor_data.value4);
	program_scores[3] = P14(actor_data.value3, actor_data.value1, actor_data.value8, actor_data.value2, actor_data.value5, actor_data.value0, actor_data.value4);

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
	const enum vertices next[4] = {A9, A9, A9, T2, };
	int_t best_program = next[best_program_id];
	successor_actor_output.write(best_program);
}

void team6(hls::stream<team6_actor_data, FIFO_DEPTH> &input_fifo, hls::stream<int_t, FIFO_DEPTH> &successor_actor_output)
{
#pragma HLS INLINE off
#pragma HLS PIPELINE II=1
	team6_actor_data actor_data = input_fifo.read();

	// execute programs
	data_t program_scores[5];
	program_scores[0] = P15(actor_data.value0, actor_data.value1, actor_data.value7);
	program_scores[1] = P16(actor_data.value3, actor_data.value1);
	program_scores[2] = P17(actor_data.value0);
	program_scores[3] = P18(actor_data.value4, actor_data.value5, actor_data.value3);
	program_scores[4] = P19(actor_data.value4, actor_data.value2, actor_data.value0, actor_data.value7, actor_data.value6, actor_data.value8, actor_data.value1, actor_data.value3);

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
	const enum vertices next[5] = {T1, A9, A9, T4, T5, };
	int_t best_program = next[best_program_id];
	successor_actor_output.write(best_program);
}

void team7(hls::stream<team7_actor_data, FIFO_DEPTH> &input_fifo, hls::stream<int_t, FIFO_DEPTH> &successor_actor_output)
{
#pragma HLS INLINE off
#pragma HLS PIPELINE II=1
	team7_actor_data actor_data = input_fifo.read();

	// execute programs
	data_t program_scores[4];
	program_scores[0] = P20(actor_data.value1, actor_data.value0, actor_data.value7);
	program_scores[1] = P21(actor_data.value0, actor_data.value1, actor_data.value6, actor_data.value5, actor_data.value8, actor_data.value7, actor_data.value3, actor_data.value4);
	program_scores[2] = P17(actor_data.value0);
	program_scores[3] = P22(actor_data.value4, actor_data.value6, actor_data.value8, actor_data.value7, actor_data.value0);

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
	const enum vertices next[4] = {A8, A9, A9, T6, };
	int_t best_program = next[best_program_id];
	successor_actor_output.write(best_program);
}

void distribute_data(hls::stream<input_data_struct, FIFO_DEPTH> &input_fifo, hls::stream<team0_actor_data, FIFO_DEPTH> &team0_input_fifo, hls::stream<team1_actor_data, FIFO_DEPTH> &team1_input_fifo, hls::stream<team2_actor_data, FIFO_DEPTH> &team2_input_fifo, hls::stream<team3_actor_data, FIFO_DEPTH> &team3_input_fifo, hls::stream<team4_actor_data, FIFO_DEPTH> &team4_input_fifo, hls::stream<team5_actor_data, FIFO_DEPTH> &team5_input_fifo, hls::stream<team6_actor_data, FIFO_DEPTH> &team6_input_fifo, hls::stream<team7_actor_data, FIFO_DEPTH> &team7_input_fifo)
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
	team5_actor_data team5_actor;
	team6_actor_data team6_actor;
	team7_actor_data team7_actor;

	// input data for actor team0
	team0_actor.value2 = actor_data_token.value2;
	team0_actor.value5 = actor_data_token.value5;

	// input data for actor team1
	team1_actor.value5 = actor_data_token.value5;
	team1_actor.value8 = actor_data_token.value8;
	team1_actor.value4 = actor_data_token.value4;
	team1_actor.value7 = actor_data_token.value7;

	// input data for actor team2
	team2_actor.value5 = actor_data_token.value5;
	team2_actor.value8 = actor_data_token.value8;
	team2_actor.value4 = actor_data_token.value4;
	team2_actor.value7 = actor_data_token.value7;

	// input data for actor team3
	team3_actor.value5 = actor_data_token.value5;
	team3_actor.value8 = actor_data_token.value8;
	team3_actor.value4 = actor_data_token.value4;
	team3_actor.value3 = actor_data_token.value3;
	team3_actor.value7 = actor_data_token.value7;
	team3_actor.value2 = actor_data_token.value2;

	// input data for actor team4
	team4_actor.value0 = actor_data_token.value0;
	team4_actor.value7 = actor_data_token.value7;
	team4_actor.value4 = actor_data_token.value4;
	team4_actor.value3 = actor_data_token.value3;
	team4_actor.value5 = actor_data_token.value5;
	team4_actor.value2 = actor_data_token.value2;

	// input data for actor team5
	team5_actor.value4 = actor_data_token.value4;
	team5_actor.value2 = actor_data_token.value2;
	team5_actor.value0 = actor_data_token.value0;
	team5_actor.value7 = actor_data_token.value7;
	team5_actor.value8 = actor_data_token.value8;
	team5_actor.value3 = actor_data_token.value3;
	team5_actor.value5 = actor_data_token.value5;
	team5_actor.value1 = actor_data_token.value1;

	// input data for actor team6
	team6_actor.value0 = actor_data_token.value0;
	team6_actor.value1 = actor_data_token.value1;
	team6_actor.value7 = actor_data_token.value7;
	team6_actor.value3 = actor_data_token.value3;
	team6_actor.value4 = actor_data_token.value4;
	team6_actor.value5 = actor_data_token.value5;
	team6_actor.value2 = actor_data_token.value2;
	team6_actor.value6 = actor_data_token.value6;
	team6_actor.value8 = actor_data_token.value8;

	// input data for actor team7
	team7_actor.value1 = actor_data_token.value1;
	team7_actor.value0 = actor_data_token.value0;
	team7_actor.value7 = actor_data_token.value7;
	team7_actor.value6 = actor_data_token.value6;
	team7_actor.value5 = actor_data_token.value5;
	team7_actor.value8 = actor_data_token.value8;
	team7_actor.value3 = actor_data_token.value3;
	team7_actor.value4 = actor_data_token.value4;


	// write actor FIFOs to relevant streams
	team0_input_fifo.write(team0_actor);
	team1_input_fifo.write(team1_actor);
	team2_input_fifo.write(team2_actor);
	team3_input_fifo.write(team3_actor);
	team4_input_fifo.write(team4_actor);
	team5_input_fifo.write(team5_actor);
	team6_input_fifo.write(team6_actor);
	team7_input_fifo.write(team7_actor);
}

void reconstruct_output(hls::stream<int_t, FIFO_DEPTH> &team0_output_fifo, hls::stream<int_t, FIFO_DEPTH> &team1_output_fifo, hls::stream<int_t, FIFO_DEPTH> &team2_output_fifo, hls::stream<int_t, FIFO_DEPTH> &team3_output_fifo, hls::stream<int_t, FIFO_DEPTH> &team4_output_fifo, hls::stream<int_t, FIFO_DEPTH> &team5_output_fifo, hls::stream<int_t, FIFO_DEPTH> &team6_output_fifo, hls::stream<int_t, FIFO_DEPTH> &team7_output_fifo, hls::stream<int_t, FIFO_DEPTH> &tpg_output)
{
#pragma HLS INLINE off
#pragma HLS PIPELINE II=1
	// get the output of each team
	int_t team0_output = team0_output_fifo.read();
	int_t team1_output = team1_output_fifo.read();
	int_t team2_output = team2_output_fifo.read();
	int_t team3_output = team3_output_fifo.read();
	int_t team4_output = team4_output_fifo.read();
	int_t team5_output = team5_output_fifo.read();
	int_t team6_output = team6_output_fifo.read();
	int_t team7_output = team7_output_fifo.read();

	int_t root_decision = team7_output;

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
			case T3:
				next_decision_step = team3_output;
				break;
			case T4:
				next_decision_step = team4_output;
				break;
			case T5:
				next_decision_step = team5_output;
				break;
			case T6:
				next_decision_step = team6_output;
				break;
			default:
				break;
		}
	}

	// produce token for final score based on decision path
	tpg_output.write((next_decision_step == A8) ? 0 : 1);
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
	hls::stream<team5_actor_data, FIFO_DEPTH> team5_input_fifo;
	hls::stream<team6_actor_data, FIFO_DEPTH> team6_input_fifo;
	hls::stream<team7_actor_data, FIFO_DEPTH> team7_input_fifo;
	distribute_data(input_fifo, team0_input_fifo, team1_input_fifo, team2_input_fifo, team3_input_fifo, team4_input_fifo, team5_input_fifo, team6_input_fifo, team7_input_fifo);

	// create FIFOs for each dataflow actor output
	hls::stream<int_t, FIFO_DEPTH> team0_output_fifo;
	hls::stream<int_t, FIFO_DEPTH> team1_output_fifo;
	hls::stream<int_t, FIFO_DEPTH> team2_output_fifo;
	hls::stream<int_t, FIFO_DEPTH> team3_output_fifo;
	hls::stream<int_t, FIFO_DEPTH> team4_output_fifo;
	hls::stream<int_t, FIFO_DEPTH> team5_output_fifo;
	hls::stream<int_t, FIFO_DEPTH> team6_output_fifo;
	hls::stream<int_t, FIFO_DEPTH> team7_output_fifo;

	// execute dataflow actors
	team0(team0_input_fifo, team0_output_fifo);
	team1(team1_input_fifo, team1_output_fifo);
	team2(team2_input_fifo, team2_output_fifo);
	team3(team3_input_fifo, team3_output_fifo);
	team4(team4_input_fifo, team4_output_fifo);
	team5(team5_input_fifo, team5_output_fifo);
	team6(team6_input_fifo, team6_output_fifo);
	team7(team7_input_fifo, team7_output_fifo);

	// construct TPG decision path
	reconstruct_output(team0_output_fifo, team1_output_fifo, team2_output_fifo, team3_output_fifo, team4_output_fifo, team5_output_fifo, team6_output_fifo, team7_output_fifo, output_fifo);
};
