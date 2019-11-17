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
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "circularbuff.h"
#include "uart_interrrupt.h"

uint8_t no_of_blocks=0;
cbuff *rx;
uint8_t *element_deleted;
uint8_t* info;
int tx_flag=1;
int count=0;
int fibo_flag;
char recv;

/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */

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
	//PRINTF("Hello");
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
	rx= malloc(sizeof(cbuff));
	rx->cbuffptr = malloc(sizeof(int8_t) * 10);
	cbuff_init(rx,10);
	//UART_configure();
	Init_UART0(BAUDRATE*2);
	UART0_print_string("\n \r Suraj");
	//char c;
	while (1)
	{
		//c= uart_rx();
		//printf("%c",c);
	}
	return 0 ;
}
