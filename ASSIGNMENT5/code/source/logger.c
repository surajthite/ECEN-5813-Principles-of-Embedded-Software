#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "logger.h"
#include "main.h"
#include "uart_interrrupt.h"
#include "circularbuff.h"
#include "time_stamp.h"

modes a = Test;   // setting mode

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
	time_stamp_print();
	if (current_mode ==0)
	{
	    char *str ="\n \r -->Test Mode: \t";
	    UART0_print_string(str);
	}
	 if (current_mode ==1)
	{
		char *str ="\n \r -->Debug Mode: \t";
		UART0_print_string(str);
	}
	 if (current_mode ==2)
	{
		    char *str ="\n \r -->Normal Mode: \t";
		    UART0_print_string(str);
	}
	if (mycurrent_function==cbuffinit)
	{
		UART0_print_string(" -->Function name: cbuffinit \n");
	}
	else if (mycurrent_function==cbuffcheck_full)
	{
		UART0_print_string(" -->Function name: cbuffcheck_full \n");
	}
	else if (mycurrent_function==cbuffisempty)
	{
		UART0_print_string("-->Function name: cbuffisempty \n");
	}
	else if (mycurrent_function==cbuffadd)
	{
		UART0_print_string("Function name: cbuffadd \n");
	}
	else if (mycurrent_function==cbuffdelete)
	{
		UART0_print_string("Function name: cbuffdelete \n");
	}
	else if (mycurrent_function==verifyinit)
	{
		UART0_print_string("Function name: verifyinit \n");
	}
	else if (mycurrent_function==verifyptr)
	{
		UART0_print_string("Function name: verifyptr \n");
	}
	else if (mycurrent_function==cbuffresize)
	{
		UART0_print_string("Function name: cbuffresize \n");
	}
	else if (mycurrent_function==cbuffprint)
	{
		UART0_print_string("Function name: cbuffprint \n");
	}
	else if (mycurrent_function==InitUART0)
	{
		UART0_print_string("Function name: InitUART0 \n");
	}
	else if (mycurrent_function==Uartrx)
	{
		UART0_print_string("Function name: Uartrx \n");
	}
	else if (mycurrent_function==Uarttx)
	{
		UART0_print_string("Function name: 	Uarttx \n");
	}
	else if (mycurrent_function==Transmitwait)
	{
		UART0_print_string("Function name: 	Transmitwait \n");
	}
	else if (mycurrent_function==Recievewait)
	{
		UART0_print_string("Function name: Recievewait \n");
	}
	else if (mycurrent_function==UART0printstring)
	{
		UART0_print_string("Function name: UART0printstring \n");
	}
	else if (mycurrent_function==UART0print_int)
	{
		UART0_print_string("Function name: UART0print_int \n");
	}
	else if (mycurrent_function==putchcbuff)
	{
		UART0_print_string("Function name: putchcbuff \n");
	}
	else if (mycurrent_function==UART0IRQHandler)
	{
		UART0_print_string("Function name: UART0IRQHandler \n");
	}
	else if (mycurrent_function==cbuffstring)
	{
		UART0_print_string("Function name: cbuffstring \n");
	}
	else if (mycurrent_function==Getinfo)
	{
		UART0_print_string("Function name: Getinfo \n");
	}
	else
	{
		UART0_print_string("Function name: 	charactercount \n");
	}

	   printf("\n \r %s ",str);

}

///////////////Log level///////////////////////////
uint8_t Log_level()
{

	return a;
}



