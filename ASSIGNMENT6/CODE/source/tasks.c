/*
 * tasks.c
 *
 *  Created on: Dec 1, 2019
 *      Author: SURAJ THITE
 */

#include "tasks.h"

#include "circularbuff.h"
#include "logger.h"
#include "wave.h"
#include "adc_dac.h"
#include "fsl_debug_console.h"

cbuff *dsp;
cbuff *adc;

void tasks_init()
{
	TimerHandle_t adc_timer_handle = NULL;
	TimerHandle_t dac_timer_handle = NULL;
	dac_timer_handle = xTimerCreate("DAC Timer", pdMS_TO_TICKS(100), pdTRUE, 0, dac_task);
	adc_timer_handle = xTimerCreate("ADC Timer", pdMS_TO_TICKS(100), pdTRUE, 0, adc_task);

	xTimerStart(dac_timer_handle, 0);

	xTimerStart(adc_timer_handle, 0);

	dsp= malloc(sizeof(cbuff));
	dsp->cbuffptr = malloc(sizeof(int8_t) * CBUFF_LEN);
	cbuff_init(dsp,CBUFF_LEN);

	adc= malloc(sizeof(cbuff));
	adc->cbuffptr = malloc(sizeof(int8_t) * CBUFF_LEN);
	cbuff_init(adc,CBUFF_LEN);

	vTaskStartScheduler();
}



void dac_task(TimerHandle_t xTimer)
{
	uint32_t val = get_next_val();
	PRINTF(" \n \r Writing %d to the DAC.", val);
	dac_write(val);
}


void adc_task(TimerHandle_t xTimer)
{
	uint32_t val = adc_read();
	PRINTF(" \n \r Reading %d to the ADC.", val);
	cbuff_add(adc,val);
	if(adc->count==CBUFF_LEN)
	{
		PRINTF(" \n \r Buffer Full!! Reinitializing Buffer");
		cbuff_reset(adc);
	}
}


