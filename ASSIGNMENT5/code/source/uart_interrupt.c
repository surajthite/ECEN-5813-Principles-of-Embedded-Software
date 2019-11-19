/*
 * uart.c
 *
 *  Created on: Nov 9, 2019
 *  Author: SURAJ THITE ,Atharv Desai
 *  Reference for Initializing Logger : https://github.com/alexander-g-dean/ESF/blob/master/Code/Chapter_8/Serial-Demo/inc/UART.h
 */

#include "uart_interrrupt.h"
#include "logger.h"
#include "RGBled.h"

//Global Variables Access//
char ch1;
uint8_t deleted_element;
extern cbuff *rx;
extern uint8_t *element_deleted;
extern uint8_t info[256];
extern int tx_flag;
extern bool rx_flag;
extern bool rx_flag_1;
extern modes a;
int wait_flag;
int8_t rx_data;




/*******************************************************************************************************
 * Function Name:Init_UART0(uint32_t baud_rate)
 * Description :This function initializes the UART0 with selected baud rate as input
 * @input: BAUD
 * @Return : void
 * Reference :https://github.com/alexander-g-dean/ESF/blob/master/Code/Chapter_8/Serial-Demo/inc/UART.h
 *******************************************************************************************************/
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

/*******************************************************************************************************
 * Function Name:char uart_rx(void)
 * Description :This Non-Blocking function to receive the character over the UART0 and return
 * @input: void
 * @Return : char
 *******************************************************************************************************/
char uart_rx(void)
{
	return UART0->D;	//Return value recieved at the recieve buffer
}

/*******************************************************************************************************
 * Function Name:void uart_tx(char ch)
 * Description :Non-Blocking function to send the character over the UART0
 * @input: char
 * @Return : void
 *******************************************************************************************************/
void uart_tx(char ch)
{
	UART0->D = ch;	//Store the character value in the transmit buffer
}
#else
/*******************************************************************************************************
 * Function Name:char uart_rx(void)
 * Description :Blocking function to receive the character over the UART0
 * @input: void
 * @Return : char
 *******************************************************************************************************/
char uart_rx(void)
{
	recieve_wait();	//Wait for character to recieve
	rx_flag_1 =1;	//Set the Flag
	return UART0->D;	//Return the received data
}

/*******************************************************************************************************
 * Function Name:char uart_rx(void)
 * Description :Blocking function to send the character over the UART0
 * @input: char
 * @Return : void
 *******************************************************************************************************/
void uart_tx(char ch)
{
	transmit_wait();	//Wait for Tx interrupt
	UART0->D = ch;		//Store the character value in transmit buffer
}
#endif

/*******************************************************************************************************
 * Function Name:void transmit_wait()
 * Description :This function waits for Tx flag
 * @input: void
 * @Return : void
 *******************************************************************************************************/


void transmit_wait()
{
	led_switch(2);	//Set LED to green
	while (!(UART0->S1 & UART_S1_TDRE_MASK));	//Wait for Tx
}

/*******************************************************************************************************
 * Function Name:char uart_rx(void)
 * Description :This function waits for Tx flag
 * @input: void
 * @Return : void
 *******************************************************************************************************/

void recieve_wait()
{
	led_switch(0);	//Switch led to Blue
	if (a==1)
		Log_String(a,Recievewait,"Waiting for Character to receive");
	while(!(UART0->S1 & UART_S1_RDRF_MASK));	//Wait for Rx
}

/*******************************************************************************************************
 * Function Name:void UART0_print_string(char *str)
 * Description :This function Prints the string on by transmitting it through the UART terminal
 * @input: string
 * @Return : void
 *******************************************************************************************************/

void UART0_print_string(char *str)
{
	while(*str != '\0')
	{
		transmit_wait();	//Wait for Tx
		uart_tx(*str);	//Transmit character of the string
		str++;	//Increment the pointer
	}
}

/*******************************************************************************************************
 * Function Name:void UART0_print_int(uint16_t count)
 * Description :This function prints the integer to the uart terminal
 * @input: integer value to be transmitted
 * @Return : void
 *******************************************************************************************************/


void UART0_print_int(uint16_t count)
{
	char str[10];	//Temporary array
	sprintf(str,"%d",count);	//Convert integer value to char
	UART0_print_string(str);	//Transmit the string via UART
}

/*******************************************************************************************************
 * Function Name:void putch_cbuff(char ch)
 * Description :This function adds the value received to the UART terminal
 * @input: char
 * @Return : void
 *******************************************************************************************************/


void putch_cbuff(char ch)
{
	cbuff_status overflow = cbuff_add(rx,ch);	//Check whether circular buffer is overflowed
	if (overflow == cbuff_full)
	{
		if(a==1 || a==0)
		{
			Log_String(a,putchcbuff,"Buffer_Full"); //T
			Log_String(a,putchcbuff,"Resizing the buffer");
			cbuff_resize(rx,20); //Resize the buffer if overflow status recieved  = cbuff_full

		}
	}
}

/*******************************************************************************************************
 * Function Name:void UART0_IRQHandler()
 * Description :This is the interrupt handler for UART0
 * @input: void
 * @Return : void
 *******************************************************************************************************/


void UART0_IRQHandler()
{
	START_CRITICAL();			//START OF CRITICAL REGION
	//Handling of Errors
	if (UART0->S1 & (UART_S1_OR_MASK |UART_S1_NF_MASK | UART_S1_FE_MASK | UART_S1_PF_MASK))
	{
		//Change LED to RED
		led_switch(1);
		UART0->S1 |= UART0_S1_OR_MASK | UART0_S1_NF_MASK | UART0_S1_FE_MASK | UART0_S1_PF_MASK;
		ch1 = UART0->D;
	}

	//Interrupt Handler for  transmit interrupt
	if(UART0->S1 & UART0_S1_TDRE_MASK)
	{
		UART0->C2 &= ~(UART0_C2_TIE_MASK);

	}
	//Interrupt Handler for  Rx interrupt
	if(UART0->S1 & UART0_S1_RDRF_MASK)
	{
		led_switch(0);	//Change LED to blue
		ch1=UART0->D;	//store received character into variable
		if(a==1)
			Log_String(a,UART0IRQHandler,"RX Interrupt Detected");
		putch_cbuff(ch1); //Store recieved character into circular buffer
		rx_flag = 1; //Set flag to 1
	}
	END_CRITICAL();	//END OF CRITICAL REGION
}

/*******************************************************************************************************
 * Function Name:void cbuff_string(char *str)
 * Description :This function adds the string to the circular buffer
 * @input: char
 * @Return : void
 *******************************************************************************************************/

void cbuff_string(char *str)
{

	while(*str != '\0')
	{
		if (a==1)
			Log_String(a,cbuffstring,"Adding String to Circular Buffer");
		putch_cbuff(*str);	//Print character pointed by str
		str++;	//Increment the pointer
	}
}
/*******************************************************************************************************
 * Function Name:void getinfo(uint8_t *element_deleted)
 * Description :This function updates the count of elements that have been deleted
 * @input: pointer to the deleted element
 * @Return : void
 *******************************************************************************************************/

void getinfo(uint8_t *element_deleted)
{
	info[*(element_deleted)]++;
}
