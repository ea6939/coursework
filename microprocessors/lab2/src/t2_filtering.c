#include <stm32f4xx.h>
#include "t2_filtering.h"

/*!
@file t2_filtering.c
@author Loren Lugosch 260404057
@author Radhika Chandra 260427945
@brief Library for filtering methods.
*/

/*!
@brief Shift values into buffer
@param new_value the latest sample
@param buffer an array of samples
@param avg pointer to the average value
@param size size of array
@return converted data
@pre there must be a buffer uint16_t array of length size
@post array will contain the new value, lose the oldest value; average will change

*/
void shift_in_value(uint16_t new_value, uint16_t * buffer, uint16_t * avg, int size)
{
	// Adds a new sample to the buffer and recalculates average.
	
	// remember the least recent sample
	uint16_t shifted_out = buffer[size-1];
	
	// shift old samples over by 1
	int i;
	for (i = size; i > 0; i--){
		buffer[i] = buffer[i-1];
	}
	
	// add new sample
	buffer[0] = new_value;
	
	// recalculate average
	(*avg) = (*avg) - (shifted_out/size) + (new_value/size);
}


/*!
@brief Shift values into buffer
@param buffer an array of samples
@param size size of array
@pre there must be a buffer uint16_t array of length size
@post array will contain zeroes

*/
void zero_initialize(uint16_t * buffer, int size)
{
  int i;
  for (i = 0; i < size ; i++) { buffer[i] = 0; } // zero-initialize buffer
}
