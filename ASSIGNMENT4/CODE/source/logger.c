#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "logger.h"
#include "main.h"

modes a = Test;

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
	printf("%d ",intval); // Print the  data
}


/*******************************************************************************************************
 * Function Name: Log_string(char* str)
 * Description : This function prints the string pointed by the input argument
 * @input:  pointer from which string  to be printed
 * @Return : void
 *******************************************************************************************************/
////// Logger for string ///////////
void Log_String(uint8_t current_mode,fnnames mycurrent_function, char* str)
{
	if (current_mode ==0)
	{
	    printf("\n \r -->Test Mode: \t");
	    //call Unittest();
	}
	 if (current_mode ==1)
	{
		printf("\n \r -->Debug Mode: \t");
		/*if(mycurrent_state1==0)
		{
			printf("POST_STATES: \t Running Power on Startup test \n");
		}
		if(mycurrent_state1==1)
	    {
			printf("I2C_READ_TEMPERATURE:\t ENTERED <STATE I2C_READ_TEMPERATURE> \n CURRENT TEMP VALUE :");
		}
		if(mycurrent_state1==2)
		{
			printf("AVERAGE_WAIT:\t ENTERED <AVERAGE WAIT> \n \r AVERAGE TEMPERATURE VALUE FOR ITERATION: ");
		}
		if(mycurrent_state1==3)
		{
			printf("TEMP_ALERT:\t Led set to red \n ************ALERT : TEMPERTURE BELOW 0 DEGREE C ************** ");
		}*/

	}
	 if (current_mode ==2)
	{
	    printf("\n \r -->Normal Mode: \t");
	    /*if(mycurrent_state1==3)
	    {
	    	printf("TEMP_ALERT:\t Led set to red \n ************ALERT : TEMPERTURE BELOW 0 DEGREE C ************** ");
	    }*/
	}
	if (mycurrent_function==state_machine1)
	{
		printf(" -->Function name: state_machine_1 \n");
	}
	else if (mycurrent_function==i2cwrite)
	{
		printf(" -->Function name: i2c_write \n");
	}
	else if (mycurrent_function==i2creadtemperature)
	{
	    printf("-->Function name: i2c_read_temperature \n");
	}
	else if (mycurrent_function==POST_TESTread_bytes)
	{
		printf("Function name: POST_TEST_read_bytes \n");
	}
	else if (mycurrent_function==checkconnection)
	{
		printf("Function name: check connection \n");
	}
	else if (mycurrent_function==SysTickHandler)
	{
		printf("Function name: SysTick_Handler \n");
	}
	else if (mycurrent_function==InitSystick)
	{
		printf("Function name: InitSystick \n");
	}
	else if (mycurrent_function==state_machine2)
	{
		printf("Function name: state_machine2 \n");
	}
	else if (mycurrent_function==state_transition__intable)
	{
		printf("Function name: state_transition__intable \n");
	}
	else if (mycurrent_function==POSTSTATE)
	{
		printf("Function name: POSTSTATE \n");
	}
	else if (mycurrent_function==I2C_READ_TEMPERATURESTATE)
	{
		printf("Function name: I2C_READ_TEMPERATURESTATE \n");
	}
	else if (mycurrent_function==	AVERAGE_WAITSTATE)
	{
		printf("Function name: 	AVERAGE_WAITSTATE \n");
	}
	else if (mycurrent_function==	TMEP_ALERTSTATE)
	{
		printf("Function name: 	TMEP_ALERTSTATE \n");
	}
	else if (mycurrent_function==	DISCONNECTEDSTATE)
	{
		printf("Function name: 	DISCONNECTEDSTATE \n");
	}
	else
	{
		printf("Function name: 	ENDSTATE \n");
	}

	   printf("\n \r %s ",str);

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


////// Logger test, debug and normal ///////////

/*******************************************************************************************************
 * Function Name:void Log_test()
 * Description : This function .enables the logging for the system
 * @input:  void
 * @Return : void
 *******************************************************************************************************/
/*
////// Logger set flag for test mode  ///////////
void Log_test()
{
	flag =0;
}

******************************************************************************************************
 * Function Name: Log_debug()
 * Description : This function .disables the logging for the system
 * @input:  void
 * @Return : void
 ******************************************************************************************************
////// Logger set flag for debug mode ///////////
void Log_debug()
{
	flag =1;
}

////// Logger set flag for normal mode ///////////
void Log_normal()
{
	flag =2;
}
*/

/*******************************************************************************************************
 * Function Name:uint8_t Log_status()
 * Description : This function  enables whether log is enabled or disabled for the system
 * @input:  void
 * @Return : flag of uint8_t
 *******************************************************************************************************/
/*////// Logger for data ///////////
uint8_t Log_status()
{
	return flag;
}*/

///////////////Log level///////////////////////////
uint8_t Log_level()
{

	return a;
}



