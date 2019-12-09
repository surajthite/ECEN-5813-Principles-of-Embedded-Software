/*
 * wave.c
 *
 *  Created on: Dec 1, 2019
 *      Author: SURAJ THITE
 */

#include "wave.h"
#include "fsl_debug_console.h"
#include "logger.h"
extern modes a;
// from  dac_adc example
const static float digital_conversion_factor = 1/(3.30/4096.0);	//Digital conversion faction Reference : DAC_ADC SDK Example

uint32_t count = 0;

static uint16_t sine[NUM_OF_SAMPLES] = {0};	//Look up table to store sine values


/*******************************************************************************************************
 * Function Name:void sine_lookup_generate()
 * Description :This function generates sine values and stores them in the lookup table for DMA transfer.
 * @input:  pointer to uint8_t
 * @Return : pointer
 * Reference: ADC_DAC SDK Example
 *******************************************************************************************************/

void sine_lookup_generate()
{
	uint64_t c = 2;	//Shift in Y axis so that maximum and minimum values are 3 and 1 volts resp.
	for(int x =0; x < NUM_OF_SAMPLES; x++)
	{
		sine[x] = (sin((2.0 * PI * (x/(float)(NUM_OF_SAMPLES)))) + c) * digital_conversion_factor;	//Generate sine values
		PRINTF(" \n \r Value written into lookup table sine[x] : %d",sine[x]);
	}
}

/*******************************************************************************************************
 * Function Name:uint16_t get_next_val()
 * Description :This function Returns the next  look up sine value to the called function
 * @input:  void
 * @Return : uint16_t
 *******************************************************************************************************/
uint16_t get_next_val()
{

	return sine[count++ % NUM_OF_SAMPLES];	//Returns the sine value from the lookup table in closed end fashion.
}
