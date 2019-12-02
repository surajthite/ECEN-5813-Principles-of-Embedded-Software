/*
 * adc_dac.c
 *
 *  Created on: Dec 1, 2019
 *      Author: SURAJ THITE
 */

#include "adc_dac.h"

static adc16_config_t adc_config_struct;
static adc16_channel_config_t adc_channel_config_struct;

static dac_config_t dac_config;


//Reference from SDK example to initialize the DAX
void initialize_dac()
{
	DAC_GetDefaultConfig(&dac_config);

	DAC_Init(DAC0, &dac_config);

	DAC_Enable(DAC0,1);

	DAC_SetBufferReadPointer(DAC0, 0U);
}


void initialize_adc()
{
	ADC16_GetDefaultConfig(&adc_config_struct);

	ADC16_Init(ADC0, &adc_config_struct);

	ADC16_EnableHardwareTrigger(ADC0, false);

	adc_channel_config_struct.channelNumber = 0;

	adc_channel_config_struct.enableInterruptOnConversionCompleted = false;
}



void dac_write(uint32_t val)
{
	DAC_SetBufferValue(DAC0,0,val);
}


uint32_t adc_read()
{
	ADC16_SetChannelConfig(ADC0, 0, &adc_channel_config_struct);
	while ((ADC16_GetChannelStatusFlags(ADC0,0) & kADC16_ChannelConversionDoneFlag)==0)
	{


	}
	return ADC16_GetChannelConversionValue(ADC0,0);

}
