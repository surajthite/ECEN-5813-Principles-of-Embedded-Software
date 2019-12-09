/*
 * logger.c
 *
 *  Created on: Nov 17, 2019
 *      Author: SURAJ THITE & Atharv Desai
 */
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
	PRINTF("%d",intval);
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


	if (mycurrent_function==dactask)
	{
		PRINTF("\t Function: DACtask \n");
	}
	else if (mycurrent_function==adctask)
	{
		PRINTF("\t Function: ADCtask \n");
	}
	else if (mycurrent_function==startdsp)
	{
		PRINTF("\t Function: Start Dsp \n");
	}
	else if (mycurrent_function==dmacallback)
	{
		PRINTF("\t Function: DMA Callback \n");
	}
	else if (mycurrent_function==Main)
	{
		PRINTF("\t Function: Main \n");
	}


}

///////////////Log level///////////////////////////
uint8_t Log_level()
{

	return a;
}



