/*
 * main.c
 *
 *  Created on: Oct 20, 2019
 *      Author: SURAJ THITE ,Atharv Desai
 */


#include "main.h"
#include "RGBled.h"
#include "unitTest.h"


/*******************************************************************************************************
 * Function Name:main (void)
 * Description : this is the main function
 * @input:void
 * @Return : 0
 *******************************************************************************************************/
int main(void)
{
	Log_enable(); // Enable Logging
	/* Init board hardware. */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();
	/* Init FSL debug console. */
	BOARD_InitDebugConsole();
	//Code Start

	// Initialize the pointers, length and seed value
	uint32_t  *ptr1;
	uint32_t  *ptr2 ;


	//Initialize the LED and Set them to off state
	RGB_init();
	RGB_OFF();

	//Turn the Blue LED on
	led_switch(0);

	//Allocate the 16 bytes of memory and take store the returning pointer of the starting memory location
	ptr1 =  allocate_words(length);


	//Turn the Blue LED on
	led_switch(0);

	//Initialize the enum to store the response

	//Display the log status

	uint8_t a = Log_status();
	printf(" \n \r Log Status Value");
	printf("\n \r %d",a);


	mem_status r1;

	//Write pattern with length 4 and seed value 5. Response is stored in enum declared.
	r1 = write_pattern(ptr1,length,SEED);

	//Check for response
	if (r1==SUCCESS)  Log_string(" \n \r RESPONSE : SUCCESS");
	else Log_string("\n \r RESPONSE : FAILED");


	//Display the contents of memory location pointed by ptr1.
	display_mem(ptr1,length);

	//Turn the Blue LED on
	led_switch(0);
	//Initialize the pointer to store the result of verify pattern
	ptr2=NULL;
	// Verify the pattern with pattern generated at ptr1 location
	ptr2 = verify_pattern(ptr1,length,SEED);

	//Print the status
	if(ptr2 != NULL)
	{
		Log_string("\n \r Different value found at location ");
		Log_data(ptr2,0);
		//Change the LED color to RED
		led_switch(1);
	}
	else
		{
		Log_string("\n \r Passed!");

		//Change the LED Color to Green
		led_switch(2);
		}

	//Turn the Blue LED on
	led_switch(0);


	//Initialize the enum to store the response
	mem_status res1;


	//Write to memory address with OFFSET 1 with value FFEE and store its response in res1
	res1 = write_memory(get_address(1), 0xFFEE);

	//Check for the response
	if (res1==SUCCESS)  Log_string(" \n \r RESPONSE : SUCCESS");
	else Log_string("\n \r RESPONSE : FAILED");


	//Display the contents of the memory location
	display_mem(ptr1,length);


	//Turn the Blue LED on
	led_switch(0);

	//Initialize the pointer to store the result of verify pattern
	ptr2=NULL;

	// Verify the pattern with pattern generated at ptr1 location
	ptr2 = verify_pattern(ptr1,length,SEED);

	//Print the status
	if(ptr2 != NULL)
	{
		Log_string("\n \r Different value found at location ");
		Log_data(ptr2,0);
	  //Change the LED color to RED
		led_switch(1);
	}
	else
	{
		Log_string("\n \r Passed!");
		//Change the LED Color to Green
		led_switch(2);
	}


	//Display the COntents of Memory Location
	display_mem(ptr1,length);


	//Turn the Blue LED on
	led_switch(0);

	//Initialize the enum to store the response
	mem_status r2;
	//Write the pattern to the location pointed by ptr1 with SEED Value 5
	r2=write_pattern(ptr1,length,SEED);

	//Print the response
	if (r2==SUCCESS)  Log_string(" \n \r RESPONSE : SUCCESS");
	else Log_string("\n \r RESPONSE : FAILED");



	//Display the contents of memory location pointed by ptr1
	display_mem(ptr1,length);


	//Turn the Blue LED on
	led_switch(0);

	//Initialize the pointer to store the result of verify pattern
	ptr2=NULL;

	// Verify the pattern with pattern generated at ptr1 location
	ptr2 = verify_pattern(get_address(0),length,SEED);

	//Print the response
	if(ptr2 != NULL)
	{
		Log_string("\n \r Different value found at location ");
		Log_data(ptr2,0);

		//Change the LED color to RED
		led_switch(1);
	}
	else
	{
		Log_string("\n \r Passed!");
		//Change the LED color to GREEN
		led_switch(2);
	}

	//Turn the Blue LED on
	led_switch(0);

	//INvert the contents of the zero location with respect to first memory of the block
	mem_status res2;
	res2 = invert_block(get_address(0),1);

	//Print the response
	if (res2==SUCCESS)  Log_string(" \n \r RESPONSE : SUCCESS");
	else Log_string("\n \r RESPONSE : FAILED");


	//Display the contents of the memory location
	display_mem(ptr1,length);


	//Turn the Blue LED on
	led_switch(0);

	//Initialize the pointer
	ptr2=NULL;

	//Verify the pattern
	ptr2 = verify_pattern(ptr1,length,SEED);

	//Print the response
	if(ptr2 != NULL)
	{
		Log_string("\n \r Different value found at location ");
		Log_data(ptr2,0);
		//Change the LED color to RED
		led_switch(1);
	}
	else
	{
	Log_string("\n \r Passed!");
	//Change the LED Color to Green
	led_switch(2);

	}


	//Turn the Blue LED on
	led_switch(0);

	//Invert the same location which was inverted before and log its response
	mem_status res3;
	res3 = invert_block(get_address(0),1);

	//Check for return data
	if (res3==SUCCESS)  Log_string(" \n \r RESPONSE : SUCCESS");
	else Log_string("\n \r RESPONSE : FAILED");


	//Display the contents of the memory location pointed by ptr1
	display_mem(ptr1,length);



	//Turn the Blue LED on
	led_switch(0);

	//Initialize the pointer to null and check for return type for the address of mismatching locaiton
	ptr2=NULL;

	//Verify the Pattern
	ptr2 = verify_pattern(ptr1,length,SEED);
	if(ptr2 != NULL)
	{
		Log_string("\n \r Different value found at location ");
		Log_data(ptr2,0);
		//Change the Color of the LED to red
		led_switch(1);
	}
	else
	{
		Log_string("\n \r Passed!");
		//Change the color of the LED to green
		led_switch(2);

	}

	//Free the memory pointed by ptr1
	free_mem(ptr1);

	//Display the COntents of the memory location
	display_mem(ptr1,length);


	//retun 0 to the funcion calling main
	RGB_OFF();
	printf("\n \r Running Test Cases");
	Testsuite_RunTests();
	return 0;
}


/*******************************************************************************************************
 * Function Name:int delay(int time_ms)
 * Description : this function provides delay in milliseconds according to input parameters
 * @input:time in milliseconds
 * @Return : NULL
 *******************************************************************************************************/

void delay(int time_ms)
{
	volatile uint32_t i = 0;
	for (i = 0; i < 2400*time_ms; ++i)
	{
		__asm("NOP"); /* No operation */
	}
}
