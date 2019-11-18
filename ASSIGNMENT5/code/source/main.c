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



//Program Execution Control Variables
#define ECHO 0
#define APPLICATION 1

// Program Definations

#define buff_length (10)
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
	//	cbuff* a ;
	//	a= malloc(sizeof(cbuff));
	//	a->cbuffptr = malloc(sizeof(int8_t) * 10);
	//	cbuff_init(a,10);
	//
	//	for (int i=0;i<8;i++)
	//	{
	//		cbuff_add(a,i);
	//	}
	//	printf("\n \r \n \n\n");
	//	cbuff_print(a);
	//	printf("\n \r \n \n\n");
	//	uint8_t sar =0;
	//	cbuff_delete(a,&sar);
	//	cbuff_print(a);
	//	printf("\n \r \n \n\n");
	//	cbuff_add(a,5);
	//	cbuff_print(a);
	//	printf("\n \r \n \n\n");
	//	cbuff_delete(a,&sar);
	//	cbuff_print(a);
	//	printf("\n \r \n \n\n");
	//	cbuff_resize(a,20);
	//	printf("\n \r \n \n\n");
	//	for (int i=0;i<8;i++)
	//		{
	//			cbuff_add(a,i);
	//		}
	//	cbuff_print(a);
	//cbuff* a ;

	Init_SysTick();		//Initialize the Systick Timer

	rx= malloc(sizeof(cbuff));	//Initialize the Rx circular buffer with size of structure

	rx->cbuffptr = malloc(sizeof(int8_t) * buff_length);	//store the starting address of the Length in the base pointer of the structure

	cbuff_init(rx,buff_length);

	Init_UART0(BAUDRATE*2);

#if ECHO
#if USE_UART_INTERRUPTS
	Log_String(2,Main,"**** ECHO USING INTERRUPTS****");
	while (1)
	{
		echo_function_interrupt();
	}

#else
	Log_String(2,Main,"**** ECHO USING POLLING****");
	while (1)
	{
		char a = uart_rx();
		echo_function_poll(a);
	}

#endif
#endif

#if APPLICATION
#if USE_UART_INTERRUPTS
	Log_String(2,Main,"**** APPLICATION USING INTERRUPTS****");
		while (int_exit ==0)
		{
			application_int();
		}

#else
		Log_String(2,Main,"**** APPLICATION USING POLLING****");
		while(1)
		{
			char a = uart_rx();
			if(a == '.')
			{
				break;
			}
			application_poll(&a);
		}

#endif
#endif

	generate_report();
	return 0 ;

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
		uint8_t *current = rx->head;
		current --;
		char time_buf[2048] = {0};
		sprintf(time_buf, " \n %c", *current);
		UART0_print_string(time_buf);
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
		rx_flag_1=0;
		uart_tx(a);
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
		Log_String(1,Application_poll,"Character Received");
		rx_flag_1=0;
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
		uint8_t *current = rx->head;
		current --;
		if(*current == '.')
		{
			int_exit =1;
		}
		character_count(current);
		//UART0_print_string(time_buf);
		rx_flag=0;
	}
}
