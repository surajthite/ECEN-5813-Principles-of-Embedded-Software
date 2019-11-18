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

void generate_report()
{
	for (int i=65;i<=90;i++)
	{
		if(char_count[i]!=0)
		{
			printf("%c-%d,",i,char_count[i]);
		}
	}

	for (int i=97;i<=122;i++)
		{
			if(char_count[i]!=0)
			{
				printf("%c-%d,",i,char_count[i]);
			}
		}
}
