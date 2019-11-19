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
#include "main.h"
#include "uart_interrrupt.h"
#include "circularbuff.h"
#include "time_stamp.h"

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
	UART0_print_int(intval);
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
	    char *s ="\t Test Mode: ";
	    UART0_print_string(s);
	}
	 if (current_mode ==1)
	{
		char *s =" \t Debug Mode: ";
		UART0_print_string(s);
	}
	 if (current_mode ==2)
	{
		    char *s ="\t Normal Mode: ";
		    UART0_print_string(s);
	}


	 UART0_print_string(str);


	if (mycurrent_function==cbuffinit)
	{
		UART0_print_string("\t Function: cbuffinit \n");
	}
	else if (mycurrent_function==cbuffcheck_full)
	{
		UART0_print_string("\t Function: cbuffcheck_full \n");
	}
	else if (mycurrent_function==cbuffisempty)
	{
		UART0_print_string("\t Function: cbuffisempty \n");
	}
	else if (mycurrent_function==cbuffadd)
	{
		UART0_print_string("\t Function: cbuffadd \n");
	}
	else if (mycurrent_function==cbuffdelete)
	{
		UART0_print_string("\t Function: cbuffdelete \n");
	}
	else if (mycurrent_function==verifyinit)
	{
		UART0_print_string("\t Function: verifyinit \n");
	}
	else if (mycurrent_function==verifyptr)
	{
		UART0_print_string("\t Function: verifyptr \n");
	}
	else if (mycurrent_function==cbuffresize)
	{
		UART0_print_string("\t Function: cbuffresize \n");
	}
	else if (mycurrent_function==cbuffprint)
	{
		UART0_print_string("\t Function: cbuffprint \n");
	}
	else if (mycurrent_function==InitUART0)
	{
		UART0_print_string("\t Function: InitUART0 \n");
	}
	else if (mycurrent_function==Uartrx)
	{
		UART0_print_string("\t Function: Uartrx \n");
	}
	else if (mycurrent_function==Uarttx)
	{
		UART0_print_string("\t Function: 	Uarttx \n");
	}
	else if (mycurrent_function==Transmitwait)
	{
		UART0_print_string("\t Function:	Transmitwait \n");
	}
	else if (mycurrent_function==Recievewait)
	{
		UART0_print_string("\t Function:Recievewait \n");
	}
	else if (mycurrent_function==UART0printstring)
	{
		UART0_print_string("\t Function: UART0printstring \n");
	}
	else if (mycurrent_function==UART0print_int)
	{
		UART0_print_string("\t Function: UART0print_int \n");
	}
	else if (mycurrent_function==putchcbuff)
	{
		UART0_print_string("\t Function: putchcbuff \n");
	}
	else if (mycurrent_function==UART0IRQHandler)
	{
		UART0_print_string("\t Function: UART0IRQHandler \n");
	}
	else if (mycurrent_function==cbuffstring)
	{
		UART0_print_string("\t Function: cbuffstring \n");
	}
	else if (mycurrent_function==Getinfo)
	{
		UART0_print_string("\t Function: Getinfo \n");
	}
	else if(mycurrent_function==charactercount)
	{
		UART0_print_string("\t Function: charactercount \n");
	}
	else if(mycurrent_function==Application_poll)
		{
			UART0_print_string("\t Function: Application_poll \n");
		}
	else if(mycurrent_function==Application_int)
		{
			UART0_print_string("\t Function: Application_int \n");
		}
	else if(mycurrent_function==Echo_function_poll)
			{
				UART0_print_string("\t Function: echo_function_poll \n");
			}
	else if(mycurrent_function==Echo_function_interrupt)
			{
				UART0_print_string("\t Function: echo_function_interrupt \n");
			}
	else if(mycurrent_function==Generate_report)
			{
				UART0_print_string("\t Function: generate_report \n");
			}
	else if(mycurrent_function==Main)
			{
				UART0_print_string("\t Function: Main \n");
			}

}

///////////////Log level///////////////////////////
uint8_t Log_level()
{

	return a;
}



