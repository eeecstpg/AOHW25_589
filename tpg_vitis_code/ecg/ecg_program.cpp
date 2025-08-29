/**
 * File generated with GEGELATI v1.2.0
 * On the 2024-09-11 15:04:12
 * With the CodeGen::ProgramVitisGenerationEngine
 * Executable TPG to be used with AMD Vitis Platform.
 */

#include "ecg_program.h"
#include <iostream>
#include <cstdint>

#include "ap_int.h"

data_t add(data_t op0, data_t op1)
{
#pragma HLS INLINE
	return op0 + op1;
}

data_t subtract(data_t op0, data_t op1)
{
#pragma HLS INLINE
	return op0 - op1;
}

data_t multiply(data_t op0, data_t op1)
{
#pragma HLS INLINE
	data_t result;

#pragma HLS BIND_OP variable=result op=mul impl=FABRIC
	result = op0 * op1;
	return result;
}

data_t min(data_t op0, data_t op1)
{
#pragma HLS INLINE
	return (op0 < op1) ? op0 : op1;;
}

data_t max(data_t op0, data_t op1)
{
#pragma HLS INLINE
	return (op0 > op1) ? op0 : op1;
}

data_t rshift_one(data_t op0)
{
#pragma HLS INLINE
	return op0 >> 1;
}

data_t rshift_two(data_t op0)
{
#pragma HLS INLINE
	return op0 >> 2;
}

data_t P0(data_t input_value28, data_t input_value16)
{
#pragma HLS INLINE off
	// variables for storing intermediary results
	data_t reg0 = 0, reg1 = 0, reg2 = 0, reg3 = 0, reg4 = 0, reg5 = 0, reg6 = 0, reg7 = 0;

	// programs
	reg4 = 	rshift_one(input_value28); 
	reg6 = 	rshift_two(input_value16); 
	reg7 = 	subtract(reg6, reg4); 
	data_t reg0_0 = 	add(reg7, reg0); 

	return reg0_0;
}

data_t P1(data_t input_value7, data_t input_value40, data_t input_value15, data_t input_value24, data_t input_value5, data_t input_value46, data_t input_value4, data_t input_value31, data_t input_value48, data_t input_value37, data_t input_value30, data_t input_value35)
{
#pragma HLS INLINE off
	// variables for storing intermediary results
	data_t reg0 = 0, reg1 = 0, reg2 = 0, reg3 = 0, reg4 = 0, reg5 = 0, reg6 = 0, reg7 = 0;

	// programs
	reg4 = 	max(input_value7, input_value40); 
	reg0 = 	add(input_value15, input_value24); 
	reg1 = 	multiply(reg0, input_value5); 
	reg5 = 	multiply(reg1, input_value46); 
	reg7 = 	rshift_two(input_value4); 
	data_t reg7_0 = 	rshift_one(reg7); 
	reg0 = 	subtract(reg7_0, input_value31); 
	reg1 = 	rshift_one(reg4); 
	reg3 = 	max(reg0, reg5); 
	reg2 = 	max(reg1, reg3); 
	reg0 = 	min(reg2, input_value48); 
	reg4 = 	rshift_two(input_value37); 
	reg5 = 	rshift_two(input_value30); 
	reg6 = 	add(input_value35, reg5); 
	reg2 = 	add(reg6, reg0); 
	reg3 = 	add(reg0, reg2); 
	reg0 = 	subtract(reg4, reg3); 

	return reg0;
}

data_t P2(data_t input_value22, data_t input_value36)
{
#pragma HLS INLINE off
	// variables for storing intermediary results
	data_t reg0 = 0, reg1 = 0, reg2 = 0, reg3 = 0, reg4 = 0, reg5 = 0, reg6 = 0, reg7 = 0;

	// programs
	reg0 = 	add(input_value22, input_value36); 

	return reg0;
}

data_t P3(data_t input_value14, data_t input_value16, data_t input_value7, data_t input_value17, data_t input_value30)
{
#pragma HLS INLINE off
	// variables for storing intermediary results
	data_t reg0 = 0, reg1 = 0, reg2 = 0, reg3 = 0, reg4 = 0, reg5 = 0, reg6 = 0, reg7 = 0;

	// programs
	reg0 = 	subtract(input_value14, input_value16); 
	reg4 = 	min(reg0, input_value7); 
	reg7 = 	rshift_two(reg4); 
	reg2 = 	max(reg7, reg0); 
	reg5 = 	add(input_value17, reg2); 
	reg0 = 	max(input_value30, reg5); 

	return reg0;
}

data_t P4(data_t input_value43, data_t input_value36, data_t input_value38, data_t input_value37)
{
#pragma HLS INLINE off
	// variables for storing intermediary results
	data_t reg0 = 0, reg1 = 0, reg2 = 0, reg3 = 0, reg4 = 0, reg5 = 0, reg6 = 0, reg7 = 0;

	// programs
	reg3 = 	min(input_value43, input_value36); 
	data_t reg3_0 = 	multiply(reg3, input_value38); 
	reg4 = 	rshift_two(input_value37); 
	reg0 = 	subtract(reg4, reg3_0); 

	return reg0;
}

data_t P5(data_t input_value45, data_t input_value41, data_t input_value46, data_t input_value17, data_t input_value30)
{
#pragma HLS INLINE off
	// variables for storing intermediary results
	data_t reg0 = 0, reg1 = 0, reg2 = 0, reg3 = 0, reg4 = 0, reg5 = 0, reg6 = 0, reg7 = 0;

	// programs
	reg0 = 	add(input_value45, input_value41); 
	reg2 = 	max(input_value46, reg0); 
	reg5 = 	add(input_value17, reg2); 
	reg0 = 	max(input_value30, reg5); 

	return reg0;
}

data_t P6(data_t input_value43, data_t input_value36, data_t input_value38, data_t input_value37)
{
#pragma HLS INLINE off
	// variables for storing intermediary results
	data_t reg0 = 0, reg1 = 0, reg2 = 0, reg3 = 0, reg4 = 0, reg5 = 0, reg6 = 0, reg7 = 0;

	// programs
	reg3 = 	min(input_value43, input_value36); 
	data_t reg3_0 = 	add(reg3, input_value38); 
	reg4 = 	rshift_two(input_value37); 
	reg0 = 	subtract(reg4, reg3_0); 

	return reg0;
}

data_t P7(data_t input_value11, data_t input_value19, data_t input_value6, data_t input_value49, data_t input_value16, data_t input_value20, data_t input_value13)
{
#pragma HLS INLINE off
	// variables for storing intermediary results
	data_t reg0 = 0, reg1 = 0, reg2 = 0, reg3 = 0, reg4 = 0, reg5 = 0, reg6 = 0, reg7 = 0;

	// programs
	reg4 = 	min(input_value11, input_value19); 
	reg6 = 	rshift_two(input_value6); 
	reg1 = 	subtract(input_value49, reg4); 
	reg5 = 	subtract(input_value16, reg6); 
	reg7 = 	rshift_one(reg1); 
	reg3 = 	subtract(reg7, reg1); 
	reg0 = 	rshift_two(reg3); 
	reg4 = 	multiply(reg5, reg0); 
	reg6 = 	max(input_value20, reg4); 
	reg0 = 	max(input_value13, reg6); 

	return reg0;
}

data_t P8(data_t input_value22, data_t input_value0)
{
#pragma HLS INLINE off
	// variables for storing intermediary results
	data_t reg0 = 0, reg1 = 0, reg2 = 0, reg3 = 0, reg4 = 0, reg5 = 0, reg6 = 0, reg7 = 0;

	// programs
	reg0 = 	add(input_value22, input_value0); 

	return reg0;
}

data_t P9(data_t input_value17, data_t input_value44, data_t input_value5, data_t input_value0, data_t input_value31, data_t input_value21, data_t input_value41, data_t input_value7, data_t input_value22, data_t input_value4, data_t input_value43, data_t input_value37, data_t input_value38)
{
#pragma HLS INLINE off
	// variables for storing intermediary results
	data_t reg0 = 0, reg1 = 0, reg2 = 0, reg3 = 0, reg4 = 0, reg5 = 0, reg6 = 0, reg7 = 0;

	// programs
	reg4 = 	rshift_two(input_value17); 
	reg7 = 	add(input_value44, input_value5); 
	reg0 = 	add(reg4, input_value0); 
	reg1 = 	add(reg7, input_value31); 
	reg7 = 	multiply(reg0, reg1); 
	reg5 = 	subtract(reg7, input_value21); 
	reg3 = 	add(input_value41, input_value7); 
	data_t reg5_0 = 	min(input_value22, reg5); 
	reg7 = 	rshift_two(input_value4); 
	data_t reg5_1 = 	max(reg5_0, reg0); 
	data_t reg3_0 = 	max(reg5_1, reg3); 
	reg2 = 	max(reg7, reg3_0); 
	reg4 = 	subtract(reg2, input_value17); 
	reg6 = 	min(input_value43, reg4); 
	reg4 = 	rshift_two(input_value37); 
	data_t reg3_1 = 	multiply(reg3_0, input_value38); 
	data_t reg4_0 = 	max(reg4, reg6); 
	reg0 = 	subtract(reg4_0, reg3_1); 

	return reg0;
}

data_t P10(data_t input_value0, data_t input_value21, data_t input_value43, data_t input_value22, data_t input_value42, data_t input_value3, data_t input_value8, data_t input_value33, data_t input_value29)
{
#pragma HLS INLINE off
	// variables for storing intermediary results
	data_t reg0 = 0, reg1 = 0, reg2 = 0, reg3 = 0, reg4 = 0, reg5 = 0, reg6 = 0, reg7 = 0;

	// programs
	reg5 = 	multiply(input_value0, input_value21); 
	data_t reg5_0 = 	min(input_value43, reg5); 
	reg1 = 	max(input_value22, input_value42); 
	reg2 = 	add(reg5_0, input_value3); 
	reg5_0 = 	add(reg1, reg2); 
	reg1 = 	subtract(reg0, reg5_0); 
	reg6 = 	max(input_value8, reg3); 
	data_t reg6_0 = 	subtract(reg1, reg6); 
	reg5_0 = 	subtract(reg6_0, input_value33); 
	reg0 = 	subtract(reg5_0, input_value29); 
	data_t reg1_0 = 	multiply(reg1, reg0); 
	reg0 = 	multiply(reg1_0, reg1_0); 
	data_t reg0_0 = 	rshift_two(reg0); 

	return reg0_0;
}

data_t P11(data_t input_value23, data_t input_value29, data_t input_value33)
{
#pragma HLS INLINE off
	// variables for storing intermediary results
	data_t reg0 = 0, reg1 = 0, reg2 = 0, reg3 = 0, reg4 = 0, reg5 = 0, reg6 = 0, reg7 = 0;

	// programs
	reg0 = 	rshift_two(input_value23); 
	reg1 = 	subtract(reg0, input_value29); 
	reg0 = 	multiply(input_value33, reg1); 

	return reg0;
}

data_t P12(data_t input_value16, data_t input_value11, data_t input_value19, data_t input_value49, data_t input_value46, data_t input_value47, data_t input_value42, data_t input_value44, data_t input_value24, data_t input_value40, data_t input_value20, data_t input_value13)
{
#pragma HLS INLINE off
	// variables for storing intermediary results
	data_t reg0 = 0, reg1 = 0, reg2 = 0, reg3 = 0, reg4 = 0, reg5 = 0, reg6 = 0, reg7 = 0;

	// programs
	reg0 = 	rshift_two(input_value16); 
	reg4 = 	min(input_value11, input_value19); 
	reg1 = 	subtract(input_value49, reg4); 
	reg2 = 	max(input_value46, reg0); 
	reg0 = 	min(input_value47, reg2); 
	reg6 = 	rshift_two(input_value42); 
	reg3 = 	min(input_value44, reg1); 
	reg7 = 	multiply(input_value11, input_value24); 
	data_t reg6_0 = 	min(reg6, reg7); 
	data_t reg6_1 = 	max(reg6_0, reg3); 
	reg5 = 	add(input_value40, reg6_1); 
	reg4 = 	multiply(reg5, reg0); 
	reg6_1 = 	max(input_value20, reg4); 
	reg0 = 	max(input_value13, reg6_1); 

	return reg0;
}

data_t P13(data_t input_value25)
{
#pragma HLS INLINE off
	// variables for storing intermediary results
	data_t reg0 = 0, reg1 = 0, reg2 = 0, reg3 = 0, reg4 = 0, reg5 = 0, reg6 = 0, reg7 = 0;

	// programs
	reg0 = 	rshift_one(input_value25); 

	return reg0;
}

