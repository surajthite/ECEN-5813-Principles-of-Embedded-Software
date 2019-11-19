/*
 * Copyright 2016-2019 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file    PES_ASSIGNMENT5.c
 * @brief   Application entry point.
 */
/* TODO: insert other include files here. */
#include "main.h"
#include "unitTest.h"
#include "RGBled.h"


//Program Execution Control Variables
#define ECHO 0
#define APPLICATION 1
#define TESTMODE 0

// Program Definitions

#define buff_length (15)
#define BAUDRATE (9600)

/* TODO: insert other Global declarations here. */

uint8_t no_of_blocks=0;
cbuff *rx;
uint8_t *element_deleted;
uint8_t* info;
int tx_flag=1;
int count=0;
char recv;
bool rx_flag;
bool rx_flag_1;
extern uint8_t char_count[256];
bool int_exit;
extern modes a;

/*
 * @brief   Application entry point.
 */
int main(void) {

	/* Init board hardware. */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();
	/* Init FSL debug console. */
	BOARD_InitDebugConsole();

	Init_SysTick();		//Initialize the Systick Timer

	RGB_init();	//Initialize the LEDs

	led_switch(0);	//Initialize the LED to Blue

	rx= malloc(sizeof(cbuff));	//Initialize the Rx circular buffer with size of structure

	rx->cbuffptr = malloc(sizeof(int8_t) * buff_length);	//store the starting address of the Length in the base pointer of the structure

	cbuff_status s = cbuff_init(rx,buff_length);

	Init_UART0(BAUDRATE*2);

#if TESTMODE
	UCUNIT_Init();
	UCUNIT_WriteString("\n**************************************");
	UCUNIT_WriteString("\nuCUnit demo application");
	UCUNIT_WriteString("\nDate:     ");
	UCUNIT_WriteString(__DATE__);
	UCUNIT_WriteString("\nTime:     ");
	UCUNIT_WriteString(__TIME__);

	UCUNIT_WriteString("\n**************************************");
	Testsuite_RunTests();
	UCUNIT_Shutdown();

#else

#if ECHO
#if USE_UART_INTERRUPTS
	if(a==1 || a==2)
		Log_String(a,Main,"**** ECHO USING INTERRUPTS****");
	while (1)
	{
		echo_function_interrupt();
	}

#else
	if(a==1 || a==2)
		Log_String(a,Main,"**** ECHO USING POLLING****");
	while (1)
	{
		char a = uart_rx();
		echo_function_poll(a);
	}

#endif
#endif

#if APPLICATION
#if USE_UART_INTERRUPTS
	if(a==1 || a==2)
		Log_String(a,Main,"**** APPLICATION USING INTERRUPTS****");	//1
	while (1)
	{
		application_int();
	}

#else
	if(a==1 || a==2)
		Log_String(a,Main,"**** APPLICATION USING POLLING****"); //1
	while(1)
	{
		char a = uart_rx();
		if(a == '.')
		{
			if(a==1 || a==2)
				Log_String(a,Main,"****Generating Report*****");	//1
			generate_report();

			//Clear the array where previous values were stored
			for (int i=65;i<=90;i++)
			{
				char_count[i] =0;
			}
			for (int i=97;i<=122;i++)
			{
				char_count[i] =0;
			}
			//	break;
		}
		application_poll(&a);
	}

#endif
#endif

	//	if(a==1 || a==2)
	//		Log_String(a,Main,"****Generating Report*****");	//1
	//	generate_report();
	return 0 ;
#endif
}

/*******************************************************************************************************
 * Function Name:void echo_function_interrupt()
 * Description :This function echoes the characters recieved from the sender via non-blocking mode of operation
 * @input: char
 * @Return : void
 *******************************************************************************************************/
void echo_function_interrupt()
{
	if(rx_flag ==1)
	{
		if(a==1 || a==2)
			Log_String(a,Echo_function_interrupt,"Character Received");	//1
		uint8_t *current = rx->head;
		current --;
		char time_buf[2048] = {0};
		sprintf(time_buf, " \n %c \n", *current);
		UART0_print_string(time_buf);
		if(a==1 || a==2)
			Log_String(a,Echo_function_interrupt,"Character Transmitted");//1
		rx_flag=0;
	}
}

/*******************************************************************************************************
 * Function Name:void echo_function_poll(char a)
 * Description :This function echoes the characters recieved from the sender via blocking mode of operation
 * @input: char
 * @Return : void
 *******************************************************************************************************/
void echo_function_poll(char a)
{
	if(rx_flag_1==1)
	{
		if(a==1 || a==2)
			Log_String(a,Echo_function_poll,"Character Received");//1
		rx_flag_1=0;
		uart_tx(a);
		if(a==1 || a==2)
			Log_String(2,Echo_function_poll,"Character Transmitted");//1
	}
}
/*******************************************************************************************************
 * Function Name:void application_poll(uint8_t *ch)
 * Description :This function runs the application mode of operation in polling mode
 * @input: pointer to a char value.
 * @Return : void
 *******************************************************************************************************/
void application_poll(uint8_t *ch)
{
	if(rx_flag_1==1)
	{
		if(a==1 || a==2)
			Log_String(a,Application_poll,"Character Received"); //1
		rx_flag_1=0;
		if(a==1 || a==2)
			Log_String(a,charactercount,"Character Count Incremented");	//1
		character_count(ch);
		//printf("%d",char_count[51]);
	}
}

/*******************************************************************************************************
 * Function Name:void application_int()
 * Description :This function runs the application mode of operation in interrupt mode
 * @input: void
 * @Return : void
 *******************************************************************************************************/
void application_int()
{
	if(rx_flag ==1)
	{
		if(a==1 || a==2)
			Log_String(a,Application_int,"Character Received");//1
		uint8_t *current = rx->head;
		current --;
		if(*current == '.')
		{

			if(a==1 || a==2)
				Log_String(a,Main,"****Generating Report*****");	//1
			generate_report();

			//Clear the values where all previous values were stored
			for (int i=65;i<=90;i++)
			{
				char_count[i] =0;
			}
			for (int i=97;i<=122;i++)
			{
				char_count[i] =0;
			}

		}
		if(a==1 || a==2)
			Log_String(a,charactercount,"Character Count Incremented"); //1
		character_count(current);
		rx_flag=0;
	}
}
