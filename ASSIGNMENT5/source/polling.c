#include "polling.h""
#include "main.h"
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
/***Reference-http://cache.freescale.com/files/32bit/doc/quick_ref_guide/KLQRUG.pdf**/


void UART_config()
{

/*********SIM Module Configuration*****************/
SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1);                      //MCGFLLCLK is used as a source clock for UART0
SIM->SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK;

SIM->SCGC4 = SIM_SCGC4_UART0_MASK;                        //enable clocks for PORTA and UART0
SIM->SCGC5 = SIM_SCGC5_PORTA_MASK;

UART0->C2 &= ~ (UART0_C2_TE_MASK| UART0_C2_RE_MASK);      // UART module TX RX disabled before changing the settings.


PORTA->PCR[2] = PORT_PCR_ISF_MASK|PORT_PCR_MUX(0x2);      // Setting pin  in UART0 TX Configuration
PORTA->PCR[1] = PORT_PCR_ISF_MASK|PORT_PCR_MUX(0x2);      // Setting pin  in UART0 RX Configuration

/*********UART Baud Rate configuration*********************/
/*  • Oversampling ratio 16
    • 115200 kbit/s baud rate

 */
UART0->BDH = 0x00;
UART0->BDL = 0x1A;        // PRESCALAR VALUE = 26
UART0->C4 = 0x0F;

UART0->C1 = 0x00;
UART0->C3 = 0x00;
UART0->MA1 = 0x00;
UART0->MA1 = 0x00;
UART0->S1 |= 0x1F;
UART0->S2 |= 0xC0;


/* Interrupt mode operation is being used,so receiver interrupt enabled.This interrupt is associated with UARTx_S1[RDRF].*/

UART0->C2 |= UART0_C2_TE_MASK| UART0_C2_RE_MASK;   // the receiver and transmitter can be enabled

#if UART_MODE == INTERRUPT_MODE
UART0->C2 = UART0_C2_RIE_MASK;  //Enable receiver transmitter interrupt
__enable_irq();   // please verify once if location correct
NVIC_SetPriority(UART0_IRQn, 2); // priority level 2 selected in 0, 1, 2, or 3
NVIC_ClearPendingIRQ(UART0_IRQn);
NVIC_EnableIRQ(UART0_IRQn);
#endif
///////////////////////////////////////////////////////////////////

//UART0->C2 |= UART0_C2_TE_MASK| UART0_C2_RE_MASK;   // should be put before or after RIE???+

}


uint8_t c;
uint8_t retdata;
uint8_t txdata;

/****************************************Polling *********************************************/



/******************************UART Receiver Functions*************************************/
uint8_t check_rx_ready()
{

	if (!(UART0->S1 & UART_S1_RDRF_MASK))    // Check if Rx data register full flag is set
		return 1;
	else
		return 0;
}


uint8_t rx_datarx()
{
	  c =UART0->D ;  //Data read from UART Data Register
	  return c;

}


uint8_t check_and_receive()
{
	//#if UART_MODE == POLLING_MODE
	//uint8_t check;
	while (1)
	{
		if (check_rx_ready()){
			retdata =rx_datarx();
			// If receive buffer ready, call other function to receive the data
		return retdata;              // we are returning the data to function where it was called
	}
	//#endif
}
}
/////////////////////////////////////////////////////////////////////////////////////////////////


/******************************UART Transmitter Functions*************************************/
uint8_t check_trans_ready()
{

	if (!(UART0->S1 & UART0_S1_TDRE_MASK) && !(UART0->S1 & UART0_S1_TC_MASK))    // UARTx_S1[TDRE] and UARTx_S1[TC] are set then ideal for transmission
		return 1;
	else
		return 0;
}

uint8_t trans_datatx()
{
	 UART0->D = c;  //UARTx_D is loaded with received character
	 return c;

}

uint8_t check_and_transmit()
{
	//#if UART_MODE == POLLING_MODE
	//uint8_t check;
	while (1)
	{
		if (check_trans_ready())
			txdata= trans_datatx();// If tansmit buffer ready, call other function to transmit the data
		    printf("%d",txdata);
		return txdata;
	}
//#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* while (1)
 {
#if UART_MODE == POLLING_MODE
 while(!(UART0->S1 & UART_S1_RDRF_MASK));   // Check if Rx data register full flag is set
 c = UART0->D;       // Data read from UART Data Register
 while(!(UART0->S1 & UART0_S1_TDRE_MASK) && !(UART0->S1 & UART0_S1_TC_MASK));
 UART0->D = c;      // UARTx_S1[TDRE] and UARTx_S1[TC] are set then UARTx_D is loaded with received character
#endif
 }

*/


/////////////////////////////////////////////////////INTERRUPT MODE/////////////////////////////////////////////////////////////



#if UART_MODE == INTERRUPT_MODE
void uart_irqhandler(void)
{
	__disable_irq();
	uint8_t intr_rx_data= intr_check_and_receive();
	printf("my data %d", intr_rx_data);
	uint8_t intr_tx_data= intr_check_and_transmit();
	printf("my data %d", intr_tx_data);



	__enable_irq();







// if (UART0->S1 & UART_S1_RDRF_MASK)
// {
// c = UART0->D;
// if (!(UART0->S1 & UART_S1_TDRE_MASK) && !(UART0->S1 & UART_S1_TC_MASK))
// {
// UART0->D = c;
// }
// }
}
#endif


uint8_t intr_check_and_transmit()
{
		if (check_trans_ready())
			txdata= trans_datatx();    // If tansmit buffer ready, call other function to transmit the data
		return txdata;
	}

////// Uart not printing so trying stdout and stdin/////////////////////
FILE __stdout;  //Use with printf
FILE __stdin;		//use with fget/sscanf, or scanf
uint8_t intr_check_and_receive()
{
		if (check_receive_ready())
			txdata= trans_datatx();    // If tansmit buffer ready, call other function to transmit the data
		return retdata;
	}


int fputc(int ch, FILE *f){
	while(!(UART0->S1 & UART_S1_TDRE_MASK) && !(UART0->S1 & UART_S1_TC_MASK));
	UART0->D = ch;
	return ch;
}


int fgetc(FILE *f){
	while(!(UART0->S1 & UART_S1_RDRF_MASK));
	return UART0->D;
}



