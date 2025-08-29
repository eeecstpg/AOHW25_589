/**
 * File generated with GEGELATI v1.2.0
 * On the 2024-09-10 21:31:40
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

#define DATA_SIZE 78
#define NUM_TEAMS 7
#define FIFO_DEPTH 1

//typedef ap_fixed<33, 33> data_t;
typedef ap_int<33> data_t;
typedef int int_t;

struct team0_actor_data
{
	data_t value13;
	data_t value23;
	data_t value47;
	data_t value42;
	data_t value57;
	data_t value8;
	data_t value49;
	data_t value51;
	data_t value56;
	data_t value3;
};

struct team1_actor_data
{
	data_t value47;
	data_t value57;
	data_t value24;
	data_t value73;
	data_t value42;
	data_t value21;
	data_t value8;
};

struct team2_actor_data
{
	data_t value51;
	data_t value56;
	data_t value3;
	data_t value5;
	data_t value47;
	data_t value27;
	data_t value41;
	data_t value71;
	data_t value36;
	data_t value73;
	data_t value13;
	data_t value62;
};

struct team3_actor_data
{
	data_t value34;
	data_t value1;
	data_t value51;
	data_t value36;
	data_t value73;
	data_t value32;
	data_t value20;
	data_t value72;
	data_t value49;
	data_t value77;
	data_t value17;
	data_t value62;
	data_t value42;
	data_t value68;
};

struct team4_actor_data
{
	data_t value38;
	data_t value53;
	data_t value35;
	data_t value29;
	data_t value26;
	data_t value69;
	data_t value77;
	data_t value20;
	data_t value34;
	data_t value11;
	data_t value75;
	data_t value37;
	data_t value3;
	data_t value1;
	data_t value42;
	data_t value49;
	data_t value52;
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
	data_t value9;
	data_t value10;
	data_t value11;
	data_t value12;
	data_t value13;
	data_t value14;
	data_t value15;
	data_t value16;
	data_t value17;
	data_t value18;
	data_t value19;
	data_t value20;
	data_t value21;
	data_t value22;
	data_t value23;
	data_t value24;
	data_t value25;
	data_t value26;
	data_t value27;
	data_t value28;
	data_t value29;
	data_t value30;
	data_t value31;
	data_t value32;
	data_t value33;
	data_t value34;
	data_t value35;
	data_t value36;
	data_t value37;
	data_t value38;
	data_t value39;
	data_t value40;
	data_t value41;
	data_t value42;
	data_t value43;
	data_t value44;
	data_t value45;
	data_t value46;
	data_t value47;
	data_t value48;
	data_t value49;
	data_t value50;
	data_t value51;
	data_t value52;
	data_t value53;
	data_t value54;
	data_t value55;
	data_t value56;
	data_t value57;
	data_t value58;
	data_t value59;
	data_t value60;
	data_t value61;
	data_t value62;
	data_t value63;
	data_t value64;
	data_t value65;
	data_t value66;
	data_t value67;
	data_t value68;
	data_t value69;
	data_t value70;
	data_t value71;
	data_t value72;
	data_t value73;
	data_t value74;
	data_t value75;
	data_t value76;
	data_t value77;
};

#endif
