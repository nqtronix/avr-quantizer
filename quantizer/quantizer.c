/*
 * quantizer.c
 *
 * Created: 31.12.2020 12:45:55
 *  Author: Dennis (nqtronix@protonmail.com)
 */ 

#include "quantizer.h"


//////////////////////////////////////////////////////////////////////////
// Structs & Typedef
//////////////////////////////////////////////////////////////////////////

typedef union
{
	uint16_t u16;
	uint8_t u8[2];
} uint16_u;


//////////////////////////////////////////////////////////////////////////
// Functions
//////////////////////////////////////////////////////////////////////////

uint8_t quantizer_1d2(const __flash uint8_t* lut, uint16_t value)
{
	// convert data type, this allows efficient acces of the high and low byte
	uint16_u data	= (uint16_u)value;
	
	// find row = count leading zeros
	uint8_t row = lut[0]-1;		// preload with max row value; a decrementing loop is faster
	while (row != 0)
	{
		// high byte == 0? => data is 255 or lower; correct row found
		if (data.u8[1]==0)
			break;
			
		// go to next row
		data.u16 >>= 1;
		row--;
	}
	// correct row value, idx of header element
	row = lut[0]-row-1;
	
	
	// find column = linear search on row elements
	uint8_t idx = lut[row];		// preload with start index of row
	while (idx < lut[row+1])
	{
		if (data.u8[0] <= lut[idx])
			break;
		
		 idx++;
	}
	// remove header part to turn index into id
	idx = idx-lut[0];
	
	return idx;
}