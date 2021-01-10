/*
 * quantizer.h
 *
 * Created: 31.12.2020 12:46:02
 *  Author: Dennis (nqtronix@protonmail.com)
 */ 


#ifndef QUANTIZER_H_
#define QUANTIZER_H_

#include <avr/io.h>


//////////////////////////////////////////////////////////////////////////
// Example LUT
//////////////////////////////////////////////////////////////////////////

// This table was generated with the included excel files
// Generate custom LUTs as needed for your application and copy the LUT into your code. You do not
// need to modify quantizer.h/.c

// const __flash uint8_t lut1d2_E12_1K1M[48] =
// {
// 	// header
// 	10, 22, 25, 29, 33, 36, 40, 44, 47, 48,
// 
// 	// data
// 	28, 34, 42, 52, 63, 77, 94, 113, 134, 161, 194, 234,
// 	142, 172, 211,
// 	129, 156, 191, 234,
// 	141, 168, 201, 242,
// 	146, 178, 215,
// 	132, 161, 195, 239,
// 	146, 176, 210, 251,
// 	151, 183, 222,
// 	134,
// };

//////////////////////////////////////////////////////////////////////////
// Function Declarations
//////////////////////////////////////////////////////////////////////////

// quantities an input value based on the provided look-up table
// Multiple variants are provided, eg. 1d2 takes a 1*n byte LUT and a 2 byte data input. 
// param:
//	lut:	look-up table
//	value:	the input value to be quantized
uint8_t quantizer_1d1(const __flash uint8_t* lut, uint8_t value);
uint8_t quantizer_1d2(const __flash uint8_t* lut, uint16_t value);
uint8_t quantizer_1d4(const __flash uint8_t* lut, uint32_t value);



#endif /* QUANTIZER_H_ */