/*
 * main implementation: use this 'C' sample to create your own application
 *
 */



#include "derivative.h" /* include peripheral declarations */
#include "typedef.h"
#include "I2C_master.h"




u8 byte_counter = 0;
u8 rx_buffer[BUFFER_SIZE];


int main(void)
{
	I2C_Master_Init();	// Initialize I2C module in master mode
	
	I2C_Master_Transmit();	// Start transmission
	
	for(;;){}
	
	return 0;
}
