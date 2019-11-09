/*
 * uart.c
 *
 *  Created on: Nov 9, 2019
 *      Author: SURAJ THITE
 */


/*******************************************************************************************************
 * Function Name: Log_integer(uint32_t intval)
 * Description : This function prints the integer value to the serial terminal
 * @input: integer to be printed
 * @Return : void
 *******************************************************************************************************/
void UART_configure(void)
{
	uint8_t i;
	i = CB_init(&buffer,size);
	buffer.head = buffer.buffptr;
	buffer.tail = buffer.buffptr;
	buffer.count = 0;
	buffer.length = size;
	buffer.count = 0;
	if(i==Success)
	return;
}
