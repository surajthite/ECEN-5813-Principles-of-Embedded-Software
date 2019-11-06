/*
 * pattern.c
 *
 *  Created on: Oct 21, 2019
 *      Author: AKSHAY THITE
 */

#include "pattern.h"

/*******************************************************************************************************
 * Function Name:void mem_status_write_pattern_array(uint32_t * loc, size_t length, uint8_t seed)
 * Description : this function writes the generated pattern for verification purposes.
 * @input: pointer to location , Length , Seed value
 * @Return : Void
 *******************************************************************************************************/
void mem_status_write_pattern_array(uint32_t * loc, size_t length, uint8_t seed)
{
	uint32_t *temp1 =loc;
	gen_pattern(temp1,length,seed); // Generate pattern at different location for verification purposes

}

/*******************************************************************************************************
 * Function Name:void gen_pattern(uint32_t * pattern, size_t length, int8_t seed)
 * Description : this function generates a pattern w.r.t. seed value and specified length
 * @input:Location where the address to be stored , Length and Seed value
 * @Return : void
 *******************************************************************************************************/
void gen_pattern(uint32_t * pattern, size_t length, int8_t seed)
{

	uint32_t lfsr = 0x1111ACE1; //Create a constant value
	uint32_t bit;
	for (uint32_t i =0 ; i< length ; i++)
	{
		bit  = ((lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5) ) & 1; // Shift the buts by 0 ,2, 3,5 to the right and xor the result and and the overall value with one
		lfsr =  (lfsr >> 1) | (bit << 31); //Shit the lsfr by one bit to the right and shift the above calculated value by 31 bits to left and or the result.
		lfsr = (uint32_t)lfsr;
		*(pattern+i)= lfsr+ (uint32_t)(seed*i*1234);	//Calculate the stored value of the pattern in the memory location
	}
}
