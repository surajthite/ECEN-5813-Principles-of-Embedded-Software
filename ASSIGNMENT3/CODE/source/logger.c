#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "memory.h"
#include "RGBled.h"

uint8_t flag;
////// Logger for integer ///////////

/*******************************************************************************************************
 * Function Name: Log_integer(uint32_t intval)
 * Description : This function prints the integer value to the serial terminal
 * @input: integer to be printed
 * @Return : void
 *******************************************************************************************************/
void Log_integer(uint32_t intval)
{
	if(flag==1)	//if logging enabled
		printf("%d \n",intval); // Print the  data
}


/*******************************************************************************************************
 * Function Name: Log_string(char* str)
 * Description : This function prints the string pointed by the input argument
 * @input:  pointer from which string  to be printed
 * @Return : void
 *******************************************************************************************************/
////// Logger for string ///////////
void Log_string(char* str)
{
	if(flag==1)			//Check
		printf("\n \r%s",str);	//Print the string to the terminal

}


/*******************************************************************************************************
 * Function Name: Log_data(uint32_t * loc,uint32_t length)
 * Description : This function  is used to log the address and variable value stored at it.
 * @input:  pointer to the memory location and the length
 * @Return : void
 *******************************************************************************************************/
////// Logger for data ///////////
void Log_data(uint32_t * loc,uint32_t length)
{
	if(flag==1) {
		int i=0;
		printf("\n\rThe Address is %p  ",loc);   //Print the address of the memory block pointed by the pointer
		if (length !=0)
		{
			printf(" and data is");
		}
		for(i=0;i<length;i++)
		{
			printf(" %x",*(loc+i));	//Print the data stored at the memory location
		}

	}
}
////// Logger status, enable and Disable ///////////

/*******************************************************************************************************
 * Function Name:void Log_enable()
 * Description : This function .enables the logging for the system
 * @input:  void
 * @Return : void
 *******************************************************************************************************/
////// Logger for data ///////////
void Log_enable()
{
	flag =1;
}

/*******************************************************************************************************
 * Function Name: Log_disable()
 * Description : This function .disables the logging for the system
 * @input:  void
 * @Return : void
 *******************************************************************************************************/
////// Logger for data ///////////
void Log_disable()
{
	flag =0;
}

/*******************************************************************************************************
 * Function Name:uint8_t Log_status()
 * Description : This function  enables whether log is enabled or disabled for the system
 * @input:  void
 * @Return : flag of uint8_t
 *******************************************************************************************************/
////// Logger for data ///////////
uint8_t Log_status()
{
	return flag;
}






