/*
 * pattern.c
 *
 *  Created on: Oct 21, 2019
 *      Author: AKSHAY THITE
 */

#include "pattern.h"

void mem_status_write_pattern_array(uint32_t * loc, size_t length, uint8_t seed)
{
	uint32_t *temp1 =loc;
	gen_pattern(temp1,length,seed);

}


void gen_pattern(uint32_t * pattern, size_t length, int8_t seed)
{

	uint32_t lfsr = 0x1111ACE1;
	uint32_t bit;
	for (uint32_t i =0 ; i< length ; i++)
	{
		bit  = ((lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5) ) & 1;

		lfsr =  (lfsr >> 1) | (bit << 31);
		lfsr = (uint32_t)lfsr;
		*(pattern+i)= lfsr+ (uint32_t)(seed*i*1234);
		//return pattern;
	}
}
