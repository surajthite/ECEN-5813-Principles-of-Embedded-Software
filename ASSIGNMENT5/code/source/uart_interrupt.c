/*
 * uart.c
 *
 *  Created on: Nov 9, 2019
 *      Author: SURAJ THITE
 */

#include "MKL25Z4.h"
#include "circularbuff.h"

cbuff *ptr;
int flag;
int c[256];
int8_t rx_data;

#define CLK_EN_UART0					0x400u			//Enable clock for UART0
#define BDH_VALUE						0x00			//Baud rate value higher bits
#define BDL_VALUE						0x18			//Baud rate value lower bits
#define OSR_VALUE						0x0F			//Over sampling ratio/rate(OSR) value
#define ENABLE_CLOCK_PORTA				0x0200			//Enable clock for PORTA
#define CLOCK_SELECT					0x04000000		//Use FFL output for UART Baud rate generator
#define TIE_FLAG						0x80u			//Enable Transmit Interrupt
#define RIE_FLAG						0x20u			//Enable Receive Interrupt
#define PIN_MUX_CTRL					0x0200			//Select Alternative 2
#define TE_FLAG							0x08			//Enable Transmitter
#define RE_FLAG							0x04			//Enable Receiver
/*******************************************************************************************************
 * Function Name: Log_integer(uint32_t intval)
 * Description : This function prints the integer value to the serial terminal
 * @input: integer to be printed
 * @Return : void
 *******************************************************************************************************/
void UART_configure(void)
{

}
