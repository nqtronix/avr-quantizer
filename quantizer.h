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

// const __flash uint8_t lut16_E12_1K1M[49] =
// {
// 	// header
// 	10, 22, 25, 29, 33, 36, 40, 44, 47, 48,
// 
// 	// data
// 	27, 33, 41, 51, 62, 76, 93, 112, 133, 160, 193, 233,
// 	141, 171, 210,
// 	128, 155, 190, 233,
// 	140, 167, 200, 241,
// 	145, 177, 214,
// 	131, 160, 194, 238,
// 	145, 175, 209, 250,
// 	150, 182, 221,
// 	133,
// 	255
// };// Explanation:// The first bytes are the header. It contains indices to the data section, each element in the// header corresponds to a row. The algorithm shifts the eg. 2 byte input data until the resulting// value is 255 or less so that it can be compared to the values in the LUT. For each shift, the// row counter is advanced by one.//// The comparison values are rounded down upper limits and which can result in unexpected borders
// between the bins. Let's take an example and assume a 8.8 fix point formating as an input value
// which shall be mapped to 8, 10 or 12. You may choose the values in between (9, 11, 13) as borders
// and get the following mapping;
//	9:	0..9	-> 8
//	11:	9..11	-> 10
//	13:	11..13	-> 12
// Assume now that you enter the binary equivalent to 11.5. According to the table above you'd assume
// to get "2" as a result, matching the entry "12"; but it'll actually be "1". The reason is that
// the shifting included in the algorithm inherently rounds down the input data (to 11 in this case)
// and that passes the comparison "data <= 11 (lut entry)".
// Changing the code will result in a less efficient implementation, so it is suggested to change
// the LUT instead. The included excel files compensate for this already.


//////////////////////////////////////////////////////////////////////////
// Function Declarations
//////////////////////////////////////////////////////////////////////////

// quantities an input value based on the provided look-up table
// Multiple variants are provided depending on size of input value. LUTs are downward compatible,
// ie. a lut16 may be used for the *_uint8 variant. Using a smaller variant can increase performance.
// param:
//	lut:	look-up table
//	value:	the input value to be quantized
uint8_t quantizer_uint8(const __flash uint8_t* lut8, uint8_t value);
uint8_t quantizer_uint16(const __flash uint8_t* lut16, uint16_t value);
uint8_t quantizer_uint32(const __flash uint8_t* lut32, uint32_t value);


#endif /* QUANTIZER_H_ */