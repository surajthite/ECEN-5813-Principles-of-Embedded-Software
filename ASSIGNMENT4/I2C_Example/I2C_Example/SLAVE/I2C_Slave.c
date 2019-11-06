/*
 * I2C_Slave.c
 *
 *  Created on: Jan 29, 2014
 *      Author: B47334
 */

#include "I2C_Slave.h"



void Enable_irq (int irq)
{   
    /* Make sure that the IRQ is an allowable number. Up to 32 is 
     * used.
     *
     * NOTE: If you are using the interrupt definitions from the header
     * file, you MUST SUBTRACT 16!!!
     */

      /* Set the ICPR and ISER registers accordingly */
      NVIC_ICPR |= 1 << (irq%32);
      NVIC_ISER |= 1 << (irq%32);
}



void I2C_Slave_Init(void)
{
	/* Enable clock for I2C0 module */
	SIM_SCGC4 |= SIM_SCGC4_I2C0_MASK;
	
	/* Enable clock for Port C */
	SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
	
	
	/* Port C MUX configuration */
	PORTC_PCR8 |=  PORT_PCR_MUX(2);
	PORTC_PCR9 |=  PORT_PCR_MUX(2);
	
	
	/* Set Slave Address */
	I2C0_A1 |= (SLAVE_ADDRESS << 1);
	
	/* Enable I2C module and interrupt */
	I2C0_C1 |= (I2C_C1_IICEN_MASK | I2C_C1_IICIE_MASK);
	
	/* Enable I2C0 NVIC interrupt */
	Enable_irq(INT_I2C0 - 16);
}




void I2C0_IRQHandler(void)
{
	u8 status = 0x00;
	u8 dummy_var;
	
	status = I2C0_S;	// Read status
	
	I2C0_S |= I2C_S_IICIF_MASK;	// Clear interrupt flag
	
	if(status & I2C_S_IAAS_MASK)	// Addressed as slave?
	{
		if(status & I2C_S_SRW_MASK)	// Read?
		{
			I2C0_C1 |= I2C_C1_TX_MASK;	// Change to transmitter mode
			I2C0_D = tx_buffer[byte_counter++];	// Write first byte to data register
		}
	}
	else
	{
		if((status & I2C_S_RXAK_MASK) == 0x00)	// ACK received?
		{
			I2C0_D = tx_buffer[byte_counter++];	// Write next byte
		}
		else
		{
			I2C0_C1 &= ~I2C_C1_TX_MASK;	// Switch to RX mode
		 	dummy_var = I2C0_D;	// Dummy read
		 	byte_counter = 0;	// Initialize counter
		}
	}
}
