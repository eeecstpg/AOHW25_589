/**
 * File generated with GEGELATI v1.2.0
 * On the 2025-08-07 16:43:36
 * With the CodeGen::DataflowFPGAGenerationEngine
 * Definitions for TPG.
*/

#ifndef C_TPG_DEFINITIONS_H
#define C_TPG_DEFINITIONS_H

#include <stdint.h>
#include <climits>
#include <hls_stream.h>
#include <hls_math.h>
#include <ap_fixed.h>
#include "ap_int.h"

#define DATA_SIZE 9
#define NUM_TEAMS 10

typedef ap_fixed<32,16> data_t;
typedef int int_t;

#define FIFO_DEPTH 1

struct team0_actor_data
{
	data_t value2;
	data_t value5;
};

struct team1_actor_data
{
	data_t value5;
	data_t value8;
	data_t value4;
	data_t value7;
};

struct team2_actor_data
{
	data_t value5;
	data_t value8;
	data_t value4;
	data_t value7;
};

struct team3_actor_data
{
	data_t value5;
	data_t value8;
	data_t value4;
	data_t value3;
	data_t value7;
	data_t value2;
};

struct team4_actor_data
{
	data_t value0;
	data_t value7;
	data_t value4;
	data_t value3;
	data_t value5;
	data_t value2;
};

struct team5_actor_data
{
	data_t value4;
	data_t value2;
	data_t value0;
	data_t value7;
	data_t value8;
	data_t value3;
	data_t value5;
	data_t value1;
};

struct team6_actor_data
{
	data_t value0;
	data_t value1;
	data_t value7;
	data_t value3;
	data_t value4;
	data_t value5;
	data_t value2;
	data_t value6;
	data_t value8;
};

struct team7_actor_data
{
	data_t value1;
	data_t value0;
	data_t value7;
	data_t value6;
	data_t value5;
	data_t value8;
	data_t value3;
	data_t value4;
};

struct input_data_struct
{
	data_t value0;
	data_t value1;
	data_t value2;
	data_t value3;
	data_t value4;
	data_t value5;
	data_t value6;
	data_t value7;
	data_t value8;
};

#endif
