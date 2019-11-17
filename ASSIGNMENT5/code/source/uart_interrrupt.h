/*
 * uart.h
 *
 *  Created on: Nov 9, 2019
 *      Author: SURAJ THITE
 */

#ifndef UART_INTERRRUPT_H_
#define UART_INTERRRUPT_H_


//void UART_configure(void);
void tx_poll();
void custom_printf(char *);
void Init_UART0(uint32_t baud_rate);
void transmit_wait();
void recieve_wait();

#endif /* UART_INTERRRUPT_H_ */
