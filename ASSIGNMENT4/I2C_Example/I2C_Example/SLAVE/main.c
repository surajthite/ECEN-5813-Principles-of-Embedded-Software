/*
 * main implementation: use this 'C' sample to create your own application
 *
 */


#include "derivative.h" /* include peripheral declarations */
#include "typedef.h"
#include "I2C_Slave.h"


u8 byte_counter = 0;
u8 tx_buffer[BUFFER_SIZE] = {1,2,3,4,5,6,7,8,9,10};


int main(void)
{
	I2C_Slave_Init();	// Initialize I2C module in slave mode
	
	for(;;){}
	
	return 0;
}
