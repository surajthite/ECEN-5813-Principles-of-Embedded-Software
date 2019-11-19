/*
 * uart.h
 *
 *  Created on: Nov 9, 2019
 *      Author: SURAJ THITE
 */

#ifndef UART_INTERRRUPT_H_
#define UART_INTERRRUPT_H_

#include "main.h"
#include "MKL25Z4.h"
#include "circularbuff.h"
#include "fsl_debug_console.h"
//void UART_configure(void);


#define USE_UART_INTERRUPTS 	(1) // 0 for polled UART communications, 1 for interrupt-driven
#define UART_OVERSAMPLE_RATE 	(16)
#define BUS_CLOCK 				(24e6)
#define SYS_CLOCK				(48e6)
#define  START_CRITICAL()  __disable_irq()
#define  END_CRITICAL()   __enable_irq()
void tx_poll();
void custom_printf(char *);
void Init_UART0(uint32_t baud_rate);
void transmit_wait();
void recieve_wait();
void UART0_print_string(char *str);
char uart_rx(void);
void uart_tx(char ch);
void UART0_print_int(uint16_t count);
#endif /* UART_INTERRRUPT_H_ */
