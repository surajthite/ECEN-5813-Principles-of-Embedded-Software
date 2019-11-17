/*
 * uart.c
 *
 *  Created on: Nov 9, 2019
 *  Author: SURAJ THITE
 *  Reference for Initializing Logger : https://github.com/alexander-g-dean/ESF/blob/master/Code/Chapter_8/Serial-Demo/inc/UART.h
 */

#include "MKL25Z4.h"
#include "circularbuff.h"
#include "main.h"
#include "fsl_debug_console.h"

char ch1;
uint8_t deleted_element;
extern cbuff *rx;
extern uint8_t *element_deleted;
extern uint8_t info[256];
extern int tx_flag;
int wait_flag;
int8_t rx_data;

#define USE_UART_INTERRUPTS 	(1) // 0 for polled UART communications, 1 for interrupt-driven
#define UART_OVERSAMPLE_RATE 	(16)
#define BUS_CLOCK 				(24e6)
#define SYS_CLOCK				(48e6)

void Init_UART0(uint32_t baud_rate)
{
	uint16_t sbr;
	uint8_t temp;

	// Enable clock gating for UART0 and Port A
	SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;

	// Make sure transmitter and receiver are disabled before init
	UART0->C2 &= ~UART0_C2_TE_MASK & ~UART0_C2_RE_MASK;

	// Set UART clock to 48 MHz clock
	SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1);
	SIM->SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK;

	// Set pins to UART0 Rx and Tx
	PORTA->PCR[1] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(2); // Rx
	PORTA->PCR[2] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(2); // Tx

	// Set baud rate and oversampling ratio
	sbr = (uint16_t)((SYS_CLOCK)/(baud_rate * UART_OVERSAMPLE_RATE));
	UART0->BDH &= ~UART0_BDH_SBR_MASK;
	UART0->BDH |= UART0_BDH_SBR(sbr>>8);
	UART0->BDL = UART0_BDL_SBR(sbr);
	UART0->C4 |= UART0_C4_OSR(UART_OVERSAMPLE_RATE-1);

	// Disable interrupts for RX active edge and LIN break detect, select one stop bit
	UART0->BDH |= UART0_BDH_RXEDGIE(0) | UART0_BDH_SBNS(0) | UART0_BDH_LBKDIE(0);

	// Don't enable loopback mode, use 8 data bit mode, don't use parity
	UART0->C1 = UART0_C1_LOOPS(0) | UART0_C1_M(0) | UART0_C1_PE(0);
	// Don't invert transmit data, don't enable interrupts for errors
	UART0->C3 = UART0_C3_TXINV(0) | UART0_C3_ORIE(0)| UART0_C3_NEIE(0)
			| UART0_C3_FEIE(0) | UART0_C3_PEIE(0);

	// Clear error flags
	UART0->S1 = UART0_S1_OR(1) | UART0_S1_NF(1) | UART0_S1_FE(1) | UART0_S1_PF(1);

	// Try it a different way
	UART0->S1 |= UART0_S1_OR_MASK | UART0_S1_NF_MASK |
									UART0_S1_FE_MASK | UART0_S1_PF_MASK;

	// Send LSB first, do not invert received data
	UART0->S2 = UART0_S2_MSBF(0) | UART0_S2_RXINV(0);

#if USE_UART_INTERRUPTS
	// Enable interrupts. Listing 8.11 on p. 234
	//	Q_Init(&TxQ);
	//	Q_Init(&RxQ);

	NVIC_SetPriority(UART0_IRQn, 2); // 0, 1, 2, or 3
	NVIC_ClearPendingIRQ(UART0_IRQn);
	NVIC_EnableIRQ(UART0_IRQn);

	// Enable receive interrupts but not transmit interrupts yet
	UART0->C2 |= UART_C2_RIE(1);
#endif

	// Enable UART receiver and transmitter
	UART0->C2 |= UART0_C2_RE(1) | UART0_C2_TE(1);

	// Clear the UART RDRF flag
	temp = UART0->D;
	UART0->S1 &= ~UART0_S1_RDRF_MASK;

}
#if USE_UART_INTERRUPTS
/* Non-Blocking function to receive the character over the UART0*/
char uart_rx(void)
{
	return UART0->D;
}

/* Non-Blocking function to send the character over the UART0*/
void uart_tx(char ch)
{
	UART0->D = ch;
}
#else
/* Blocking function to receive the character over the UART0*/
char uart_rx(void)
{
	recieve_wait();
	putch_cbuff(UART0->D);
	return UART0->D;
}

/* Blocking function to send the character over the UART0*/
void uart_tx(char ch)
{
  transmit_wait();
  UART0->D = ch;
}
#endif



void transmit_wait()
{
	while (!(UART0->S1 & UART_S1_TDRE_MASK));
}
void recieve_wait()
{
	while (!(UART0->S1 &  UART_S1_RDRF_MASK));
}


void UART0_print_string(char *str)
{
	while(*str != '\0')
	{
		transmit_wait();
		uart_tx(*str);
		str++;
	}
}


void UART0_print_int(uint16_t count)
{
	char str[10];
	sprintf(str,"%d",count);
	UART0_print_string(str);
}


void putch_cbuff(char ch)
{
	cbuff_add(rx,ch);
}

void UART0_IRQHandler()
{
	__disable_irq();

	//Interrupt Handler for  transmit interrupt
	if(UART0->S1 & UART0_S1_TDRE_MASK)
	{
//		wait_flag = 1;
//		tx_flag = 1;
		UART0->C2 &= ~(UART0_C2_TIE_MASK);

	}
	//Interrupt Handler for  Rx interrupt
	if(UART0->S1 & UART0_S1_RDRF_MASK)
	{
		ch1=UART0->D;
		printf(" \n \r Rx Interrupt Handler");
		putch_cbuff(ch1);
	}
	__enable_irq();
}

void cbuff_string(char *str)
{
	while(*str != '\0')
	{
		putch_cbuff(*str);
		str++;
	}
}

void getinfo(uint8_t *element_deleted)
{
	info[*(element_deleted)]++;
}
