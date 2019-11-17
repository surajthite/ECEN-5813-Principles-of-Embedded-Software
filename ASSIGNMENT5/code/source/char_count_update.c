/*
 * char_count_update.c
 *
 *  Created on: Nov 17, 2019
 *      Author: SURAJ THITE & Atharv Desai
 */

#include "char_count_update.h"

uint8_t char_count[256];

//This function receives the character and updates its count in the char_count array
uint8_t* character_count(uint8_t *char_val)
{
	char_count[*char_val] ++;
	return char_count;
}
