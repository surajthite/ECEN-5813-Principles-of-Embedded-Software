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
// from  dac adc example
const static float digital_conversion_factor = 1/(3.30/4096.0);

uint32_t count = 0;

static uint32_t sine[NUM_OF_SAMPLES] = {0};

//float sine_function(float x)
//{
//	float x2 = x*x;
//	return x*(1 - x2 * (INV_3_FACTORIAL + x2 * (INV_5_FACTORIAL - INV_7_FACTORIAL * x2)));
//}


void sine_lookup_generate()
{
	uint64_t c = 2;
	for(int x =0; x < NUM_OF_SAMPLES; x++)
	{
		sine[x] = (sin((2.0 * PI * (x/(float)(NUM_OF_SAMPLES)))) + c) * digital_conversion_factor;
		PRINTF(" \n \r Value written into lookup table sine[x] : %d",sine[x]);
	}
}

uint32_t get_next_val()
{

	return sine[count++ % NUM_OF_SAMPLES];
}
