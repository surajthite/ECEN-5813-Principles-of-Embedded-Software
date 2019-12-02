/*
 * logger.c
 *
 *  Created on: Nov 17, 2019
 *      Author: SURAJ THITE & Atharv Desai
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "logger.h"

#include "circularbuff.h"
#include "time_stamp.h"
#include "fsl_debug_console.h"
modes a = Debug;   // setting mode

fnnames fn_name;

////////TABLE for modes and current states////////////////////////////////

uint8_t flag;
////// Logger for integer ///////////

/*******************************************************************************************************
 * Function Name: Log_integer(uint32_t intval)
 * Description : This function prints the integer value to the serial terminal
 * @input: integer to be printed
 * @Return : void
 *******************************************************************************************************/
void Log_integer(modes current_mode,int16_t intval)
{
	if(current_mode != 1)      // since no integers to print in normal status mode
	//printf("%d ",intval); // Print the  data
	PRINTF(intval);
}


/*******************************************************************************************************
 * Function Name: Log_string(char* str)
 * Description : This function prints the string pointed by the input argument
 * @input:  pointer from which string  to be printed
 * @Return : void
 *******************************************************************************************************/
////// Logger for string ///////////
void Log_String(uint8_t current_mode,fnnames mycurrent_function, char *str)
{
	time_stamp_print();		//Print time stamp
	if (current_mode ==0)
	{
	   PRINTF("\t Test Mode: ");
	}
	 if (current_mode ==1)
	{
		 PRINTF("\t Debug Mode: ");
	}
	 if (current_mode ==2)
	{
		 PRINTF("\t Normal Mode: ");
	}


	 PRINTF(" %s ",str);


	if (mycurrent_function==cbuffinit)
	{
		PRINTF("\t Function: cbuffinit \n");
	}
	else if (mycurrent_function==cbuffcheck_full)
	{
		PRINTF("\t Function: cbuffcheck_full \n");
	}
	else if (mycurrent_function==cbuffisempty)
	{
		PRINTF("\t Function: cbuffisempty \n");
	}
	else if (mycurrent_function==cbuffadd)
	{
		PRINTF("\t Function: cbuffadd \n");
	}
	else if (mycurrent_function==cbuffdelete)
	{
		PRINTF("\t Function: cbuffdelete \n");
	}
	else if (mycurrent_function==verifyinit)
	{
		PRINTF("\t Function: verifyinit \n");
	}
	else if (mycurrent_function==verifyptr)
	{
		PRINTF("\t Function: verifyptr \n");
	}
	else if (mycurrent_function==cbuffresize)
	{
		PRINTF("\t Function: cbuffresize \n");
	}
	else if (mycurrent_function==cbuffprint)
	{
		PRINTF("\t Function: cbuffprint \n");
	}
	else if (mycurrent_function==InitUART0)
	{
		PRINTF("\t Function: InitUART0 \n");
	}
	else if (mycurrent_function==Uartrx)
	{
		PRINTF("\t Function: Uartrx \n");
	}
	else if (mycurrent_function==Uarttx)
	{
		PRINTF("\t Function: 	Uarttx \n");
	}
	else if (mycurrent_function==Transmitwait)
	{
		PRINTF("\t Function:	Transmitwait \n");
	}
	else if (mycurrent_function==Recievewait)
	{
		PRINTF("\t Function:Recievewait \n");
	}
	else if (mycurrent_function==UART0printstring)
	{
		PRINTF("\t Function: UART0printstring \n");
	}
	else if (mycurrent_function==UART0print_int)
	{
		PRINTF("\t Function: UART0print_int \n");
	}
	else if (mycurrent_function==putchcbuff)
	{
		PRINTF("\t Function: putchcbuff \n");
	}
	else if (mycurrent_function==UART0IRQHandler)
	{
		PRINTF("\t Function: UART0IRQHandler \n");
	}
	else if (mycurrent_function==cbuffstring)
	{
		PRINTF("\t Function: cbuffstring \n");
	}
	else if (mycurrent_function==Getinfo)
	{
		PRINTF("\t Function: Getinfo \n");
	}
	else if(mycurrent_function==charactercount)
	{
		PRINTF("\t Function: charactercount \n");
	}
	else if(mycurrent_function==Application_poll)
		{
		PRINTF("\t Function: Application_poll \n");
		}
	else if(mycurrent_function==Application_int)
		{
		PRINTF("\t Function: Application_int \n");
		}
	else if(mycurrent_function==Echo_function_poll)
			{
		PRINTF("\t Function: echo_function_poll \n");
			}
	else if(mycurrent_function==Echo_function_interrupt)
			{
		PRINTF("\t Function: echo_function_interrupt \n");
			}
	else if(mycurrent_function==Generate_report)
			{
		PRINTF("\t Function: generate_report \n");
			}
	else if(mycurrent_function==Main)
			{
		PRINTF("\t Function: Main \n");
			}

}

///////////////Log level///////////////////////////
uint8_t Log_level()
{

	return a;
}



