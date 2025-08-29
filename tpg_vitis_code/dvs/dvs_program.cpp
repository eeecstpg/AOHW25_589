/**
 * File generated with GEGELATI v1.2.0
 * On the 2025-08-07 16:43:36
 * With the CodeGen::ProgramVitisGenerationEngine
 * Executable TPG to be used with AMD Vitis Platform.
 */

#include "dvs_program.h"
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

data_t square(data_t op0)
{
#pragma HLS INLINE
	data_t result;

#pragma HLS BIND_OP variable=result op=mul impl=FABRIC
	result = op0 * op0;
	return result;
}

data_t average(data_t op0, data_t op1)
{
#pragma HLS INLINE
	data_t result;

#pragma HLS BIND_OP variable=result op=mul impl=FABRIC
	result = data_t(0.5) * (op0 + op1);
	return result;
}

data_t difference_abs(data_t op0, data_t op1)
{
#pragma HLS INLINE
	return (op0 > op1) ? op0 - op1 : op1 - op0;
}

data_t absolute(data_t op0)
{
#pragma HLS INLINE
	return (op0 < 0) ? data_t(-op0) : op0;
}

data_t is_equal(data_t op0, data_t op1)
{
#pragma HLS INLINE
	return (op0 == op1) ? data_t(1.0) : data_t(0.0);
}

data_t is_less(data_t op0, data_t op1)
{
#pragma HLS INLINE
	return (op0 < op1) ? data_t(1.0) : data_t(0.0);
}

data_t if_gt_else(data_t op0, data_t op1, data_t op2, data_t op3)
{
#pragma HLS INLINE
	return (op0 > op1) ? op2 : op3;
}

data_t threshold_zero(data_t op0, data_t op1)
{
#pragma HLS INLINE
	return (op0 > op1) ? op0 : data_t(0.0);
}

data_t clamp(data_t op0, data_t op1, data_t op2)
{
#pragma HLS INLINE
	data_t result;
	if (op0 < op1)
	    result = op1;
	else if (op0 > op2)
	    result = op2;
	else
	    result = op0;
	return result;
}

data_t P0(data_t input_value2, data_t input_value5)
{
#pragma HLS INLINE off
	// variables for storing intermediary results
	data_t reg0 = 0, reg1 = 0, reg2 = 0, reg3 = 0, reg4 = 0, reg5 = 0, reg6 = 0, reg7 = 0;


	// programs
	reg0 = 	is_less(input_value2, input_value5); 

	return reg0;
}

data_t P1()
{
#pragma HLS INLINE off
	// variables for storing intermediary results
	data_t reg0 = 0, reg1 = 0, reg2 = 0, reg3 = 0, reg4 = 0, reg5 = 0, reg6 = 0, reg7 = 0;


	// programs

	return reg0;
}

data_t P2(data_t input_value5, data_t input_value8)
{
#pragma HLS INLINE off
	// variables for storing intermediary results
	data_t reg0 = 0, reg1 = 0, reg2 = 0, reg3 = 0, reg4 = 0, reg5 = 0, reg6 = 0, reg7 = 0;


	// programs
	reg5 = 	average(input_value5, input_value5); 
	reg0 = 	min(reg5, input_value8); 

	return reg0;
}

data_t P3(data_t input_value5, data_t input_value4, data_t input_value7)
{
#pragma HLS INLINE off
	// variables for storing intermediary results
	data_t reg0 = 0, reg1 = 0, reg2 = 0, reg3 = 0, reg4 = 0, reg5 = 0, reg6 = 0, reg7 = 0;


	// programs
	reg3 = 	rshift_one(input_value5); 
	reg4 = 	subtract(input_value4, reg3); 
	reg5 = 	average(input_value7, input_value4); 
	reg1 = 	rshift_one(reg5); 
	reg0 = 	average(reg1, reg4); 

	return reg0;
}

data_t P4(data_t input_value5, data_t input_value4, data_t input_value7)
{
#pragma HLS INLINE off
	// variables for storing intermediary results
	data_t reg0 = 0, reg1 = 0, reg2 = 0, reg3 = 0, reg4 = 0, reg5 = 0, reg6 = 0, reg7 = 0;


	// programs
	reg3 = 	rshift_one(input_value5); 
	reg4 = 	subtract(input_value4, reg3); 
	reg5 = 	average(input_value7, input_value4); 
	reg1 = 	rshift_one(reg5); 
	reg0 = 	average(reg1, reg4); 

	return reg0;
}

data_t P5(data_t input_value4, data_t input_value5)
{
#pragma HLS INLINE off
	// variables for storing intermediary results
	data_t reg0 = 0, reg1 = 0, reg2 = 0, reg3 = 0, reg4 = 0, reg5 = 0, reg6 = 0, reg7 = 0;


	// programs
	reg0 = 	if_gt_else(reg1, reg7, input_value4, input_value5); 

	return reg0;
}

data_t P6(data_t input_value4, data_t input_value3, data_t input_value7)
{
#pragma HLS INLINE off
	// variables for storing intermediary results
	data_t reg0 = 0, reg1 = 0, reg2 = 0, reg3 = 0, reg4 = 0, reg5 = 0, reg6 = 0, reg7 = 0;


	// programs
	reg4 = 	subtract(input_value4, input_value3); 
	reg5 = 	average(input_value7, input_value4); 
	reg1 = 	rshift_one(reg5); 
	reg0 = 	average(reg1, reg4); 

	return reg0;
}

data_t P7(data_t input_value0, data_t input_value7, data_t input_value4, data_t input_value3, data_t input_value5)
{
#pragma HLS INLINE off
	// variables for storing intermediary results
	data_t reg0 = 0, reg1 = 0, reg2 = 0, reg3 = 0, reg4 = 0, reg5 = 0, reg6 = 0, reg7 = 0;


	// programs
	reg3 = 	subtract(input_value0, input_value7); 
	reg0 = 	subtract(reg6, reg3); 
	reg3 = 	min(reg0, input_value4); 
	reg0 = 	clamp(input_value3, reg6, reg3); 
	data_t reg0_0 = 	absolute(reg0); 
	reg6 = 	add(reg5, reg0_0); 
	reg3 = 	rshift_one(input_value5); 
	reg0_0 = 	multiply(reg6, reg3); 

	return reg0_0;
}

data_t P8(data_t input_value2, data_t input_value5)
{
#pragma HLS INLINE off
	// variables for storing intermediary results
	data_t reg0 = 0, reg1 = 0, reg2 = 0, reg3 = 0, reg4 = 0, reg5 = 0, reg6 = 0, reg7 = 0;


	// programs
	reg3 = 	is_less(reg5, reg5); 
	reg5 = 	rshift_two(input_value2); 
	data_t reg3_0 = 	clamp(input_value5, reg3, reg5); 
	reg0 = 	rshift_one(reg3_0); 

	return reg0;
}

data_t P9(data_t input_value7, data_t input_value4)
{
#pragma HLS INLINE off
	// variables for storing intermediary results
	data_t reg0 = 0, reg1 = 0, reg2 = 0, reg3 = 0, reg4 = 0, reg5 = 0, reg6 = 0, reg7 = 0;


	// programs
	reg4 = 	rshift_two(input_value7); 
	reg5 = 	average(input_value7, input_value4); 
	reg1 = 	rshift_one(reg5); 
	reg0 = 	average(reg1, reg4); 

	return reg0;
}

data_t P10(data_t input_value4)
{
#pragma HLS INLINE off
	// variables for storing intermediary results
	data_t reg0 = 0, reg1 = 0, reg2 = 0, reg3 = 0, reg4 = 0, reg5 = 0, reg6 = 0, reg7 = 0;


	// programs
	reg0 = 	rshift_one(input_value4); 

	return reg0;
}

data_t P11(data_t input_value4, data_t input_value2, data_t input_value0, data_t input_value7, data_t input_value8)
{
#pragma HLS INLINE off
	// variables for storing intermediary results
	data_t reg0 = 0, reg1 = 0, reg2 = 0, reg3 = 0, reg4 = 0, reg5 = 0, reg6 = 0, reg7 = 0;


	// programs
	reg6 = 	absolute(input_value4); 
	reg3 = 	clamp(input_value2, reg6, input_value0); 
	reg4 = 	is_equal(reg6, input_value7); 
	reg0 = 	add(reg3, reg4); 
	reg5 = 	absolute(reg0); 
	reg0 = 	min(reg5, input_value8); 

	return reg0;
}

data_t P12(data_t input_value8, data_t input_value0)
{
#pragma HLS INLINE off
	// variables for storing intermediary results
	data_t reg0 = 0, reg1 = 0, reg2 = 0, reg3 = 0, reg4 = 0, reg5 = 0, reg6 = 0, reg7 = 0;


	// programs
	reg0 = 	average(input_value8, input_value0); 
	data_t reg0_0 = 	rshift_two(reg0); 

	return reg0_0;
}

data_t P13(data_t input_value7, data_t input_value3, data_t input_value5, data_t input_value2, data_t input_value4)
{
#pragma HLS INLINE off
	// variables for storing intermediary results
	data_t reg0 = 0, reg1 = 0, reg2 = 0, reg3 = 0, reg4 = 0, reg5 = 0, reg6 = 0, reg7 = 0;


	// programs
	reg7 = 	is_less(input_value7, input_value3); 
	reg3 = 	rshift_one(input_value5); 
	reg6 = 	is_equal(reg7, input_value5); 
	reg0 = 	subtract(reg6, reg3); 
	reg1 = 	add(input_value2, reg0); 
	reg4 = 	subtract(input_value4, reg3); 
	reg0 = 	average(reg1, reg4); 

	return reg0;
}

data_t P14(data_t input_value3, data_t input_value1, data_t input_value8, data_t input_value2, data_t input_value5, data_t input_value0, data_t input_value4)
{
#pragma HLS INLINE off
	// variables for storing intermediary results
	data_t reg0 = 0, reg1 = 0, reg2 = 0, reg3 = 0, reg4 = 0, reg5 = 0, reg6 = 0, reg7 = 0;


	// programs
	reg0 = 	rshift_one(input_value3); 
	reg3 = 	threshold_zero(input_value1, reg0); 
	reg6 = 	if_gt_else(reg3, input_value8, reg1, input_value2); 
	reg3 = 	rshift_one(input_value5); 
	reg0 = 	multiply(reg6, reg3); 
	reg6 = 	clamp(input_value3, input_value2, input_value0); 
	reg4 = 	subtract(input_value4, input_value3); 
	reg5 = 	if_gt_else(reg6, input_value8, reg0, input_value3); 
	reg1 = 	rshift_one(reg5); 
	reg0 = 	average(reg1, reg4); 

	return reg0;
}

data_t P15(data_t input_value0, data_t input_value1, data_t input_value7)
{
#pragma HLS INLINE off
	// variables for storing intermediary results
	data_t reg0 = 0, reg1 = 0, reg2 = 0, reg3 = 0, reg4 = 0, reg5 = 0, reg6 = 0, reg7 = 0;


	// programs
	reg2 = 	add(input_value0, input_value1); 
	data_t reg0_0 = 	square(reg0); 
	data_t reg2_0 = 	average(reg0_0, reg2); 
	reg0_0 = 	subtract(reg2_0, input_value7); 

	return reg0_0;
}

data_t P16(data_t input_value3, data_t input_value1)
{
#pragma HLS INLINE off
	// variables for storing intermediary results
	data_t reg0 = 0, reg1 = 0, reg2 = 0, reg3 = 0, reg4 = 0, reg5 = 0, reg6 = 0, reg7 = 0;


	// programs
	reg5 = 	absolute(input_value3); 
	reg0 = 	min(input_value1, reg5); 

	return reg0;
}

data_t P17(data_t input_value0)
{
#pragma HLS INLINE off
	// variables for storing intermediary results
	data_t reg0 = 0, reg1 = 0, reg2 = 0, reg3 = 0, reg4 = 0, reg5 = 0, reg6 = 0, reg7 = 0;


	// programs
	reg0 = 	difference_abs(input_value0, reg6); 

	return reg0;
}

data_t P18(data_t input_value4, data_t input_value5, data_t input_value3)
{
#pragma HLS INLINE off
	// variables for storing intermediary results
	data_t reg0 = 0, reg1 = 0, reg2 = 0, reg3 = 0, reg4 = 0, reg5 = 0, reg6 = 0, reg7 = 0;


	// programs
	reg7 = 	rshift_two(reg5); 
	data_t reg7_0 = 	if_gt_else(reg7, input_value4, input_value5, input_value3); 
	data_t reg7_1 = 	min(input_value3, reg7_0); 
	reg0 = 	rshift_one(reg7_1); 
	data_t reg0_0 = 	square(reg0); 

	return reg0_0;
}

data_t P19(data_t input_value4, data_t input_value2, data_t input_value0, data_t input_value7, data_t input_value6, data_t input_value8, data_t input_value1, data_t input_value3)
{
#pragma HLS INLINE off
	// variables for storing intermediary results
	data_t reg0 = 0, reg1 = 0, reg2 = 0, reg3 = 0, reg4 = 0, reg5 = 0, reg6 = 0, reg7 = 0;


	// programs
	reg6 = 	absolute(input_value4); 
	reg3 = 	clamp(input_value2, reg6, input_value0); 
	reg4 = 	is_equal(reg6, input_value7); 
	reg0 = 	add(reg3, reg4); 
	reg2 = 	if_gt_else(input_value6, reg6, input_value8, reg4); 
	reg3 = 	difference_abs(reg2, reg0); 
	reg7 = 	average(input_value1, reg3); 
	reg4 = 	absolute(reg7); 
	reg6 = 	multiply(reg4, input_value8); 
	reg5 = 	multiply(input_value3, reg6); 
	reg0 = 	difference_abs(reg5, input_value1); 

	return reg0;
}

data_t P20(data_t input_value1, data_t input_value0, data_t input_value7)
{
#pragma HLS INLINE off
	// variables for storing intermediary results
	data_t reg0 = 0, reg1 = 0, reg2 = 0, reg3 = 0, reg4 = 0, reg5 = 0, reg6 = 0, reg7 = 0;


	// programs
	reg6 = 	multiply(input_value1, input_value0); 
	reg4 = 	rshift_two(input_value7); 
	reg5 = 	square(reg6); 
	reg1 = 	rshift_one(reg5); 
	reg0 = 	average(reg1, reg4); 

	return reg0;
}

data_t P21(data_t input_value0, data_t input_value1, data_t input_value6, data_t input_value5, data_t input_value8, data_t input_value7, data_t input_value3, data_t input_value4)
{
#pragma HLS INLINE off
	// variables for storing intermediary results
	data_t reg0 = 0, reg1 = 0, reg2 = 0, reg3 = 0, reg4 = 0, reg5 = 0, reg6 = 0, reg7 = 0;


	// programs
	data_t reg2_0 = 	max(reg2, input_value0); 
	reg1 = 	difference_abs(input_value1, input_value6); 
	reg0 = 	is_equal(reg1, input_value0); 
	reg7 = 	is_equal(reg2_0, reg3); 
	reg6 = 	max(input_value5, reg0); 
	reg4 = 	max(input_value5, input_value1); 
	reg2_0 = 	if_gt_else(input_value6, reg6, input_value8, reg4); 
	data_t reg6_0 = 	max(reg6, reg7); 
	reg1 = 	if_gt_else(input_value1, input_value6, input_value7, reg6_0); 
	reg5 = 	average(input_value5, input_value5); 
	reg0 = 	if_gt_else(input_value0, input_value7, reg3, reg1); 
	data_t reg0_0 = 	clamp(reg0, reg5, input_value7); 
	reg5 = 	clamp(reg2_0, input_value7, reg0_0); 
	reg0_0 = 	min(reg5, input_value3); 
	reg1 = 	is_less(reg0_0, input_value4); 
	reg6_0 = 	absolute(input_value4); 
	reg0_0 = 	multiply(input_value3, input_value0); 
	reg5 = 	average(reg1, reg0_0); 
	reg3 = 	difference_abs(reg6_0, reg0_0); 
	reg4 = 	multiply(reg5, input_value5); 
	data_t reg4_0 = 	add(input_value8, reg4); 
	reg0_0 = 	add(reg3, reg4_0); 

	return reg0_0;
}

data_t P22(data_t input_value4, data_t input_value6, data_t input_value8, data_t input_value7, data_t input_value0)
{
#pragma HLS INLINE off
	// variables for storing intermediary results
	data_t reg0 = 0, reg1 = 0, reg2 = 0, reg3 = 0, reg4 = 0, reg5 = 0, reg6 = 0, reg7 = 0;


	// programs
	reg6 = 	threshold_zero(input_value4, input_value4); 
	reg4 = 	absolute(reg6); 
	reg6 = 	absolute(input_value4); 
	reg2 = 	if_gt_else(input_value6, reg6, input_value8, reg4); 
	reg6 = 	square(reg2); 
	reg1 = 	subtract(input_value4, reg6); 
	data_t reg1_0 = 	average(reg1, input_value7); 
	reg0 = 	is_equal(reg1_0, input_value0); 
	data_t reg0_0 = 	max(input_value7, reg0); 

	return reg0_0;
}

