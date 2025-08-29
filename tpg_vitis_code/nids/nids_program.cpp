/**
 * File generated with GEGELATI v1.2.0
 * On the 2024-09-10 21:31:40
 * With the CodeGen::ProgramVitisGenerationEngine
 * Executable TPG to be used with AMD Vitis Platform.
 */

#include "nids_program.h"
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
data_t nulltest(data_t op0)
{
#pragma HLS INLINE
	return (op0 == 0.0) ? 10.0 : 0.0;
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

data_t P0(data_t input_value13, data_t input_value23, data_t input_value47)
{
#pragma HLS INLINE off
	// variables for storing intermediary results
	data_t reg0 = 0, reg1 = 0, reg2 = 0, reg3 = 0, reg4 = 0, reg5 = 0, reg6 = 0, reg7 = 0;

	// programs
	reg7 = 	rshift_two(input_value13); 
	reg5 = 	nulltest(input_value23); 
	reg3 = 	add(reg5, reg7); 
	reg0 = 	multiply(input_value47, reg3); 

	return reg0;
}

data_t P1(data_t input_value42)
{
#pragma HLS INLINE off
	// variables for storing intermediary results
	data_t reg0 = 0, reg1 = 0, reg2 = 0, reg3 = 0, reg4 = 0, reg5 = 0, reg6 = 0, reg7 = 0;

	// programs
	reg1 = 	multiply(reg4, reg3); 
	reg0 = 	subtract(reg1, input_value42); 

	return reg0;
}

data_t P2(data_t input_value57, data_t input_value8)
{
#pragma HLS INLINE off
	// variables for storing intermediary results
	data_t reg0 = 0, reg1 = 0, reg2 = 0, reg3 = 0, reg4 = 0, reg5 = 0, reg6 = 0, reg7 = 0;

	// programs
	reg0 = 	add(input_value57, input_value8); 

	return reg0;
}

data_t P3(data_t input_value49, data_t input_value51, data_t input_value56, data_t input_value3, data_t input_value23, data_t input_value47)
{
#pragma HLS INLINE off
	// variables for storing intermediary results
	data_t reg0 = 0, reg1 = 0, reg2 = 0, reg3 = 0, reg4 = 0, reg5 = 0, reg6 = 0, reg7 = 0;

	// programs
	reg4 = 	rshift_two(input_value49); 
	data_t reg4_0 = 	rshift_two(reg4); 
	reg5 = 	rshift_two(input_value51); 
	data_t reg5_0 = 	nulltest(reg5); 
	reg3 = 	rshift_two(reg5_0); 
	reg6 = 	nulltest(reg4_0); 
	reg5_0 = 	multiply(input_value56, reg6); 
	reg2 = 	add(reg5_0, reg5_0); 
	data_t reg2_0 = 	subtract(reg2, input_value3); 
	reg4_0 = 	add(input_value51, reg3); 
	reg7 = 	rshift_two(reg2_0); 
	reg1 = 	rshift_two(reg4_0); 
	data_t reg7_0 = 	subtract(reg1, reg7); 
	reg5_0 = 	nulltest(input_value23); 
	reg3 = 	add(reg5_0, reg7_0); 
	reg0 = 	multiply(input_value47, reg3); 

	return reg0;
}

data_t P4(data_t input_value47)
{
#pragma HLS INLINE off
	// variables for storing intermediary results
	data_t reg0 = 0, reg1 = 0, reg2 = 0, reg3 = 0, reg4 = 0, reg5 = 0, reg6 = 0, reg7 = 0;

	// programs
	reg0 = 	nulltest(input_value47); 

	return reg0;
}

data_t P5(data_t input_value47)
{
#pragma HLS INLINE off
	// variables for storing intermediary results
	data_t reg0 = 0, reg1 = 0, reg2 = 0, reg3 = 0, reg4 = 0, reg5 = 0, reg6 = 0, reg7 = 0;

	// programs
	reg0 = 	nulltest(input_value47); 

	return reg0;
}

data_t P6(data_t input_value57, data_t input_value24)
{
#pragma HLS INLINE off
	// variables for storing intermediary results
	data_t reg0 = 0, reg1 = 0, reg2 = 0, reg3 = 0, reg4 = 0, reg5 = 0, reg6 = 0, reg7 = 0;

	// programs
	reg0 = 	add(input_value57, input_value24); 

	return reg0;
}

data_t P7(data_t input_value73)
{
#pragma HLS INLINE off
	// variables for storing intermediary results
	data_t reg0 = 0, reg1 = 0, reg2 = 0, reg3 = 0, reg4 = 0, reg5 = 0, reg6 = 0, reg7 = 0;

	// programs
	reg0 = 	add(input_value73, reg2); 

	return reg0;
}

data_t P8(data_t input_value42, data_t input_value21)
{
#pragma HLS INLINE off
	// variables for storing intermediary results
	data_t reg0 = 0, reg1 = 0, reg2 = 0, reg3 = 0, reg4 = 0, reg5 = 0, reg6 = 0, reg7 = 0;

	// programs
	reg0 = 	add(input_value42, input_value21); 

	return reg0;
}

data_t P9(data_t input_value51, data_t input_value56, data_t input_value3, data_t input_value5, data_t input_value47)
{
#pragma HLS INLINE off
	// variables for storing intermediary results
	data_t reg0 = 0, reg1 = 0, reg2 = 0, reg3 = 0, reg4 = 0, reg5 = 0, reg6 = 0, reg7 = 0;

	// programs
	data_t reg4_0 = 	rshift_two(reg4); 
	reg5 = 	rshift_two(input_value51); 
	data_t reg5_0 = 	nulltest(reg5); 
	reg3 = 	rshift_two(reg5_0); 
	reg6 = 	nulltest(reg4_0); 
	reg5_0 = 	multiply(input_value56, reg6); 
	reg2 = 	add(reg5_0, reg5_0); 
	data_t reg2_0 = 	subtract(reg2, input_value3); 
	reg4_0 = 	add(input_value51, reg3); 
	reg7 = 	rshift_two(reg2_0); 
	reg1 = 	rshift_two(reg4_0); 
	data_t reg7_0 = 	subtract(reg1, reg7); 
	reg5_0 = 	rshift_two(input_value5); 
	reg3 = 	add(reg5_0, reg7_0); 
	reg0 = 	multiply(input_value47, reg3); 

	return reg0;
}

data_t P10(data_t input_value27, data_t input_value41, data_t input_value71, data_t input_value51, data_t input_value36)
{
#pragma HLS INLINE off
	// variables for storing intermediary results
	data_t reg0 = 0, reg1 = 0, reg2 = 0, reg3 = 0, reg4 = 0, reg5 = 0, reg6 = 0, reg7 = 0;

	// programs
	reg1 = 	subtract(input_value27, input_value41); 
	reg4 = 	rshift_one(reg1); 
	reg5 = 	add(reg4, input_value71); 
	reg0 = 	rshift_one(reg5); 
	reg7 = 	add(input_value51, reg0); 
	reg0 = 	add(input_value36, reg7); 

	return reg0;
}

data_t P11(data_t input_value73)
{
#pragma HLS INLINE off
	// variables for storing intermediary results
	data_t reg0 = 0, reg1 = 0, reg2 = 0, reg3 = 0, reg4 = 0, reg5 = 0, reg6 = 0, reg7 = 0;

	// programs
	reg6 = 	rshift_one(input_value73); 
	reg0 = 	nulltest(reg6); 

	return reg0;
}

data_t P12(data_t input_value56, data_t input_value5, data_t input_value13, data_t input_value62, data_t input_value47)
{
#pragma HLS INLINE off
	// variables for storing intermediary results
	data_t reg0 = 0, reg1 = 0, reg2 = 0, reg3 = 0, reg4 = 0, reg5 = 0, reg6 = 0, reg7 = 0;

	// programs
	reg5 = 	nulltest(input_value56); 
	reg7 = 	nulltest(input_value5); 
	reg1 = 	add(reg5, input_value13); 
	reg2 = 	rshift_one(reg1); 
	reg6 = 	rshift_two(reg2); 
	reg3 = 	add(reg5, reg7); 
	reg1 = 	multiply(reg3, reg6); 
	reg2 = 	add(reg7, reg1); 
	reg4 = 	rshift_one(input_value62); 
	reg5 = 	subtract(reg1, reg4); 
	reg3 = 	rshift_one(reg2); 
	data_t reg5_0 = 	add(reg5, reg4); 
	data_t reg5_1 = 	nulltest(reg5_0); 
	reg1 = 	add(reg5_1, reg3); 
	reg0 = 	nulltest(input_value47); 
	reg4 = 	multiply(reg1, reg0); 
	reg0 = 	nulltest(reg4); 

	return reg0;
}

data_t P13(data_t input_value34, data_t input_value1, data_t input_value51, data_t input_value36)
{
#pragma HLS INLINE off
	// variables for storing intermediary results
	data_t reg0 = 0, reg1 = 0, reg2 = 0, reg3 = 0, reg4 = 0, reg5 = 0, reg6 = 0, reg7 = 0;

	// programs
	reg3 = 	add(input_value34, input_value1); 
	reg0 = 	add(input_value1, reg3); 
	reg7 = 	add(input_value51, reg0); 
	reg0 = 	add(input_value36, reg7); 

	return reg0;
}

data_t P14(data_t input_value32, data_t input_value20, data_t input_value72, data_t input_value49, data_t input_value77, data_t input_value17, data_t input_value62)
{
#pragma HLS INLINE off
	// variables for storing intermediary results
	data_t reg0 = 0, reg1 = 0, reg2 = 0, reg3 = 0, reg4 = 0, reg5 = 0, reg6 = 0, reg7 = 0;

	// programs
	reg6 = 	rshift_two(input_value32); 
	reg1 = 	rshift_two(reg6); 
	reg0 = 	nulltest(input_value20); 
	reg4 = 	add(input_value72, reg1); 
	reg5 = 	subtract(reg1, reg4); 
	reg3 = 	add(reg5, reg4); 
	reg2 = 	nulltest(input_value49); 
	reg6 = 	nulltest(input_value77); 
	data_t reg2_0 = 	add(reg2, reg6); 
	reg6 = 	add(reg0, reg2_0); 
	reg1 = 	subtract(reg3, reg6); 
	reg7 = 	subtract(input_value17, input_value62); 
	reg4 = 	add(reg1, input_value17); 
	reg5 = 	subtract(reg7, reg4); 
	reg0 = 	rshift_one(reg5); 

	return reg0;
}

data_t P15(data_t input_value68, data_t input_value1, data_t input_value51, data_t input_value36)
{
#pragma HLS INLINE off
	// variables for storing intermediary results
	data_t reg0 = 0, reg1 = 0, reg2 = 0, reg3 = 0, reg4 = 0, reg5 = 0, reg6 = 0, reg7 = 0;

	// programs
	reg3 = 	rshift_one(input_value68); 
	reg0 = 	add(input_value1, reg3); 
	reg7 = 	add(input_value51, reg0); 
	reg0 = 	add(input_value36, reg7); 

	return reg0;
}

data_t P16(data_t input_value38, data_t input_value53, data_t input_value35, data_t input_value29)
{
#pragma HLS INLINE off
	// variables for storing intermediary results
	data_t reg0 = 0, reg1 = 0, reg2 = 0, reg3 = 0, reg4 = 0, reg5 = 0, reg6 = 0, reg7 = 0;

	// programs
	reg5 = 	rshift_one(input_value38); 
	reg4 = 	add(input_value53, input_value35); 
	reg2 = 	rshift_one(reg5); 
	data_t reg4_0 = 	subtract(reg4, input_value29); 
	reg6 = 	nulltest(reg4_0); 
	reg4_0 = 	rshift_one(reg6); 
	reg0 = 	subtract(reg4_0, reg2); 

	return reg0;
}

data_t P17(data_t input_value26, data_t input_value69, data_t input_value77)
{
#pragma HLS INLINE off
	// variables for storing intermediary results
	data_t reg0 = 0, reg1 = 0, reg2 = 0, reg3 = 0, reg4 = 0, reg5 = 0, reg6 = 0, reg7 = 0;

	// programs
	reg2 = 	multiply(input_value26, input_value69); 
	reg0 = 	add(input_value77, reg2); 

	return reg0;
}

data_t P18(data_t input_value20, data_t input_value34, data_t input_value11, data_t input_value75, data_t input_value37, data_t input_value35, data_t input_value3, data_t input_value1)
{
#pragma HLS INLINE off
	// variables for storing intermediary results
	data_t reg0 = 0, reg1 = 0, reg2 = 0, reg3 = 0, reg4 = 0, reg5 = 0, reg6 = 0, reg7 = 0;

	// programs
	reg2 = 	rshift_one(reg7); 
	reg5 = 	rshift_two(input_value20); 
	data_t reg2_0 = 	add(reg2, reg5); 
	data_t reg2_1 = 	add(reg2_0, reg5); 
	reg6 = 	add(input_value34, input_value11); 
	data_t reg2_2 = 	add(reg2_1, reg6); 
	reg4 = 	multiply(input_value75, input_value37); 
	reg0 = 	subtract(reg4, reg2_2); 
	reg3 = 	subtract(input_value35, reg0); 
	reg5 = 	nulltest(reg3); 
	reg2_2 = 	subtract(reg5, input_value3); 
	reg0 = 	add(reg2_2, input_value1); 

	return reg0;
}

data_t P19(data_t input_value49, data_t input_value1, data_t input_value52)
{
#pragma HLS INLINE off
	// variables for storing intermediary results
	data_t reg0 = 0, reg1 = 0, reg2 = 0, reg3 = 0, reg4 = 0, reg5 = 0, reg6 = 0, reg7 = 0;

	// programs
	reg4 = 	rshift_two(input_value49); 
	reg3 = 	rshift_two(reg4); 
	reg0 = 	add(input_value1, reg3); 
	reg5 = 	multiply(input_value52, reg0); 
	reg0 = 	rshift_one(reg5); 

	return reg0;
}

