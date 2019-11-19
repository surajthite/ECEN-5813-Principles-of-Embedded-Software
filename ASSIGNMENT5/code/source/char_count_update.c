/*
 * char_count_update.c
 *
 *  Created on: Nov 17, 2019
 *      Author: SURAJ THITE & Atharv Desai
 */

#include "char_count_update.h"

uint8_t char_count[256];

/*******************************************************************************************************
 * Function Name:uint8_t* character_count(uint8_t *char_val)
 * Description :This function receives the character and updates its count in the char_count array
 * @input:  pointer to uint8_t
 * @Return : pointer
 *******************************************************************************************************/

uint8_t* character_count(uint8_t *char_val)
{
	char_count[*char_val] ++;	//Increment character value in the char_count global variable
	return char_count;	//Return pointer to array
}

/*******************************************************************************************************
 * Function Name: void generate_report()
 * Description : This function generates report to be printed on detection of '.' character
 * @input:  void
 * @Return : void
 *******************************************************************************************************/
void generate_report()
{
	printf("\n \r");
	for (int i=65;i<=90;i++)	//Check for A-Z and a-z ascii characters only
	{
		if(char_count[i]!=0)	//If count is not zero , print the value
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
