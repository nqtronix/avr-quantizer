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
const __flash uint8_t lut16_E12_1K1M[49] =
{
	// header
	10, 22, 25, 29, 33, 36, 40, 44, 47, 48,

	// data
	27, 33, 41, 51, 62, 76, 93, 112, 133, 160, 193, 233,
	141, 171, 210,
	128, 155, 190, 233,
	140, 167, 200, 241,
	145, 177, 214,
	131, 160, 194, 238,
	145, 175, 209, 250,
	150, 182, 221,
	133,
	255
};

const __flash uint8_t lut32_E12_10R10M[93] =
{
	// header
	18, 36, 39, 43, 47, 50, 54, 57, 61, 65, 68, 72, 76, 79, 83, 86, 90, 92,

	// data
	8, 10, 13, 16, 19, 24, 29, 35, 42, 51, 61, 74, 90, 109, 134, 164, 199, 244,
	149, 179, 214,
	128, 154, 187, 227,
	137, 168, 205, 249,
	152, 187, 224,
	133, 160, 193, 233,
	141, 171, 210,
	128, 155, 190, 233,
	140, 167, 200, 241,
	145, 177, 214,
	131, 160, 194, 238,
	145, 175, 209, 250,
	150, 182, 221,
	133, 164, 200, 243,
	149, 182, 219,
	130, 156, 188, 228,
	138, 167,
	255
};

const __flash uint8_t lut16_E12_1K47K[28] =
{
	// header
	5, 17, 20, 24, 27,

	// data
	27, 33, 41, 51, 62, 76, 93, 112, 133, 160, 193, 233,
	141, 171, 210,
	128, 155, 190, 233,
	140, 167, 200,
	255
};


//////////////////////////////////////////////////////////////////////////
// Functions
//////////////////////////////////////////////////////////////////////////

int main(void)
{
    // test the upper and lower limit of each bin at start, middle and end of the LUT table 
 	volatile uint8_t id0L = quantizer_uint16(lut16_E12_1K1M, 0);
	volatile uint8_t id0H = quantizer_uint16(lut16_E12_1K1M, 27);
	volatile uint8_t id1L = quantizer_uint16(lut16_E12_1K1M, 28);
	volatile uint8_t id1H = quantizer_uint16(lut16_E12_1K1M, 33);
	volatile uint8_t id2L = quantizer_uint16(lut16_E12_1K1M, 34);
	
	volatile uint8_t id14H = quantizer_uint16(lut16_E12_1K1M, 210<<1);
	volatile uint8_t id15L = quantizer_uint16(lut16_E12_1K1M, 211<<1);
	volatile uint8_t id15H = quantizer_uint16(lut16_E12_1K1M, 128<<2);
	volatile uint8_t id16L = quantizer_uint16(lut16_E12_1K1M, 129<<2);
	
	volatile uint8_t id36H = quantizer_uint16(lut16_E12_1K1M, 221<<7);
	volatile uint8_t id37L = quantizer_uint16(lut16_E12_1K1M, 222<<7);
	volatile uint8_t id37H = quantizer_uint16(lut16_E12_1K1M, 133<<8);
	volatile uint8_t id38L = quantizer_uint16(lut16_E12_1K1M, 134<<8);
	volatile uint8_t id38H = quantizer_uint16(lut16_E12_1K1M, UINT16_MAX);
	
	// test behavior id max input value is <32k => row count <9
	// to be valid, this test requires a lut where: lut[lut[0]] < lut[lut[0]+1]
	// output range is limited to the amount of elements, where ID23 is the max value
// 	volatile uint8_t id0L = quantizer_uint16(lut16_E12_1K47K, 0);
// 	volatile uint8_t id0H = quantizer_uint16(lut16_E12_1K47K, 27);
// 	volatile uint8_t id1L = quantizer_uint16(lut16_E12_1K47K, 28);
// 	volatile uint8_t id1H = quantizer_uint16(lut16_E12_1K47K, 33);
// 	volatile uint8_t id2L = quantizer_uint16(lut16_E12_1K47K, 34);
// 	
// 	volatile uint8_t id14H = quantizer_uint16(lut16_E12_1K47K, 210<<1);
// 	volatile uint8_t id15L = quantizer_uint16(lut16_E12_1K47K, 211<<1);
// 	volatile uint8_t id15H = quantizer_uint16(lut16_E12_1K47K, 128<<2);
// 	volatile uint8_t id16L = quantizer_uint16(lut16_E12_1K47K, 129<<2);
// 	
// 	volatile uint8_t id21H = quantizer_uint16(lut16_E12_1K47K, 200<<3);
// 	volatile uint8_t id22L = quantizer_uint16(lut16_E12_1K47K, 201<<3);
// 	volatile uint8_t id22H = quantizer_uint16(lut16_E12_1K47K, 254<<4);
// 	volatile uint8_t id23L = quantizer_uint16(lut16_E12_1K47K, 255<<4);
// 	volatile uint8_t id23H = quantizer_uint16(lut16_E12_1K47K, UINT16_MAX);
	
	// test uint8 variant
// 	volatile uint8_t id0L = quantizer_uint8(lut16_E12_1K47K, 0);
// 	volatile uint8_t id0H = quantizer_uint8(lut16_E12_1K47K, 27);
// 	volatile uint8_t id1L = quantizer_uint8(lut16_E12_1K47K, 28);
// 	volatile uint8_t id1H = quantizer_uint8(lut16_E12_1K47K, 33);
// 	volatile uint8_t id2L = quantizer_uint8(lut16_E12_1K47K, 34);
// 
// 	volatile uint8_t id11H = quantizer_uint8(lut16_E12_1K47K, 233);
// 	volatile uint8_t id12L = quantizer_uint8(lut16_E12_1K47K, 234);
// 	volatile uint8_t id12H = quantizer_uint8(lut16_E12_1K47K, 255);

	// test uint32 variant
//	volatile uint8_t id0L = quantizer_uint32(lut32_E12_10R10M, 0);
// 	volatile uint8_t id0H = quantizer_uint32(lut32_E12_10R10M, 8);
// 	volatile uint8_t id1L = quantizer_uint32(lut32_E12_10R10M, 9);
// 	volatile uint8_t id1H = quantizer_uint32(lut32_E12_10R10M, 10);
// 	volatile uint8_t id2L = quantizer_uint32(lut32_E12_10R10M, 11);
// 
// 	volatile uint8_t id20H = quantizer_uint32(lut32_E12_10R10M, ((uint32_t)214)<<1);
// 	volatile uint8_t id21L = quantizer_uint32(lut32_E12_10R10M, ((uint32_t)215)<<1);
// 	volatile uint8_t id21H = quantizer_uint32(lut32_E12_10R10M, ((uint32_t)128)<<2);
// 	volatile uint8_t id22L = quantizer_uint32(lut32_E12_10R10M, ((uint32_t)129)<<2);
// 
// 	volatile uint8_t id72H = quantizer_uint32(lut32_E12_10R10M, ((uint32_t)128)<<16);
// 	volatile uint8_t id73L = quantizer_uint32(lut32_E12_10R10M, ((uint32_t)139)<<16);
// 	volatile uint8_t id73H = quantizer_uint32(lut32_E12_10R10M, ((uint32_t)167)<<16);
// 	volatile uint8_t id74L = quantizer_uint32(lut32_E12_10R10M, ((uint32_t)168)<<16);
// 	volatile uint8_t id74H = quantizer_uint32(lut32_E12_10R10M, UINT32_MAX);
	
	// test average execution time 
// 	for (uint16_t i=0; i < UINT16_MAX; i++)
// 	{
// 		volatile uint8_t dummy = quantizer_uint16(lut16_E12_1K1M, i);
// 	}
// 	volatile uint8_t dummy = quantizer_uint16(lut16_E12_1K1M, 0);
	
    while (1);
}

