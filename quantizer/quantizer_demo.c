/*
 * quantizer.c
 *
 * Created: 31.12.2020 11:41:53
 *  Author: Dennis (nqtronix@protonmail.com)
 */ 

#include <avr/io.h>
#include "quantizer.h"


//////////////////////////////////////////////////////////////////////////
// Example LUTs
//////////////////////////////////////////////////////////////////////////

// These tables were generated with the included excel files
const __flash uint8_t lut1d2_E12_1K1M[48] =
{
	// header
	10, 22, 25, 29, 33, 36, 40, 44, 47, 48, 

	// data
	28, 34, 42, 52, 63, 77, 94, 113, 134, 161, 194, 234, 
	142, 172, 211, 
	129, 156, 191, 234, 
	141, 168, 201, 242, 
	146, 178, 215, 
	132, 161, 195, 239, 
	146, 176, 210, 251, 
	151, 183, 222, 
	134, 
	255
};

const __flash uint8_t lut1d4_E12_10R10M[92] =
{
	// header
	18, 36, 39, 43, 47, 50, 54, 57, 61, 65, 68, 72, 76, 79, 83, 86, 90, 92, 

	// data
	9, 11, 14, 17, 20, 25, 30, 36, 43, 52, 62, 75, 91, 110, 135, 165, 200, 245, 
	150, 180, 215, 
	129, 155, 188, 228, 
	138, 169, 206, 250, 
	153, 188, 225, 
	134, 161, 194, 234, 
	142, 172, 211, 
	129, 156, 191, 234, 
	141, 168, 201, 242, 
	146, 178, 215, 
	132, 161, 195, 239, 
	146, 176, 210, 251, 
	151, 183, 222, 
	134, 165, 201, 244, 
	150, 183, 220, 
	131, 157, 189, 229, 
	139, 168, 
	255
};

const __flash uint8_t lut1d2_E12_1K47K[27] =
{
	// header
	5, 17, 20, 24, 27, 

	// data
	28, 34, 42, 52, 63, 77, 94, 113, 134, 161, 194, 234, 
	142, 172, 211, 
	129, 156, 191, 234, 
	141, 168, 201, 
	255
};


//////////////////////////////////////////////////////////////////////////
// Functions
//////////////////////////////////////////////////////////////////////////

int main(void)
{
    // test the upper and lower limit of each bin at start, middle and end of the LUT table 
// 	volatile uint8_t id0L = quantizer_1d2(lut1d2_E12_1K1M, 0);
// 	volatile uint8_t id0H = quantizer_1d2(lut1d2_E12_1K1M, 28);
// 	volatile uint8_t id1L = quantizer_1d2(lut1d2_E12_1K1M, 29);
// 	volatile uint8_t id1H = quantizer_1d2(lut1d2_E12_1K1M, 34);
// 	volatile uint8_t id2L = quantizer_1d2(lut1d2_E12_1K1M, 35);
// 	
// 	volatile uint8_t id14H = quantizer_1d2(lut1d2_E12_1K1M, 211<<1);
// 	volatile uint8_t id15L = quantizer_1d2(lut1d2_E12_1K1M, 212<<1);
// 	volatile uint8_t id15H = quantizer_1d2(lut1d2_E12_1K1M, 129<<2);
// 	volatile uint8_t id16L = quantizer_1d2(lut1d2_E12_1K1M, 130<<2);
// 	
// 	volatile uint8_t id36H = quantizer_1d2(lut1d2_E12_1K1M, 222<<7);
// 	volatile uint8_t id37L = quantizer_1d2(lut1d2_E12_1K1M, 223<<7);
// 	volatile uint8_t id37H = quantizer_1d2(lut1d2_E12_1K1M, 134<<8);
// 	volatile uint8_t id38L = quantizer_1d2(lut1d2_E12_1K1M, 135<<8);
// 	volatile uint8_t id38H = quantizer_1d2(lut1d2_E12_1K1M, UINT16_MAX);
	
	// test behavior id max input value is <32k => row count <9
	// to be valid, this test requires a lut where: lut[lut[0]] < lut[lut[0]+1]
	// output range is limited to the amount of elements, where ID23 is the max value
	volatile uint8_t id0L = quantizer_1d2(lut1d2_E12_1K47K, 0);
	volatile uint8_t id0H = quantizer_1d2(lut1d2_E12_1K47K, 28);
	volatile uint8_t id1L = quantizer_1d2(lut1d2_E12_1K47K, 29);
	volatile uint8_t id1H = quantizer_1d2(lut1d2_E12_1K47K, 34);
	volatile uint8_t id2L = quantizer_1d2(lut1d2_E12_1K47K, 35);
	
	volatile uint8_t id14H = quantizer_1d2(lut1d2_E12_1K47K, 211<<1);
	volatile uint8_t id15L = quantizer_1d2(lut1d2_E12_1K47K, 212<<1);
	volatile uint8_t id15H = quantizer_1d2(lut1d2_E12_1K47K, 129<<2);
	volatile uint8_t id16L = quantizer_1d2(lut1d2_E12_1K47K, 130<<2);
	
	volatile uint8_t id21H = quantizer_1d2(lut1d2_E12_1K47K, 201<<3);
	volatile uint8_t id22L = quantizer_1d2(lut1d2_E12_1K47K, 202<<3);
	volatile uint8_t id22H = quantizer_1d2(lut1d2_E12_1K47K, 254<<4);
	volatile uint8_t id23L = quantizer_1d2(lut1d2_E12_1K47K, 255<<4);
	volatile uint8_t id23H = quantizer_1d2(lut1d2_E12_1K47K, UINT16_MAX);
	
    while (1);
}

