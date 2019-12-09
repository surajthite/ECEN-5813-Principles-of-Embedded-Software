/*
 * adc_dac.c
 *
 *  Created on: Dec 1, 2019
 *      Author: SURAJ THITE
 */

#include "adc_dac.h"

#include "fsl_debug_console.h"

static adc16_config_t adc_config_struct;	//Structure to store the ADC configuration

static adc16_channel_config_t adc_channel_config_struct;	//Structure to store channel configuration of the ADC

static dac_config_t dac_config;		//Structure to store the DAC configuration of the DAC

/*******************************************************************************************************
 * Function Name:void initialize_dac()
 * Description :This function Initializes and enables the DAC on default configuration.
 * @input:  pointer to uint8_t
 * @Return : pointer
 *******************************************************************************************************/
//Reference from SDK example to initialize the DAC
void initialize_dac()
{
	DAC_GetDefaultConfig(&dac_config);	//Get Default configuration of DAC

	DAC_Init(DAC0, &dac_config);	//INitialize the DAC with default configuration

	DAC_Enable(DAC0,1);	//ENable the DAC peripheral

	DAC_SetBufferReadPointer(DAC0, 0U);	//Set buffer read pointer to starting location

	PRINTF("*********DAC INITIALIZED**********");
}

/*******************************************************************************************************
 * Function Name:void initialize_adc()
 * Description :This function Initializes the ADC to default configuration. The AutoCalibration Feature is
 * set on while interrupts is disabled upon conversion of the ADC value. Channel no 0 is selected for input.
 * @input:  pointer to uint8_t
 * @Return : pointer
 *******************************************************************************************************/
void initialize_adc()
{
	ADC16_GetDefaultConfig(&adc_config_struct);	//Get default configuration of the ADC

	ADC16_Init(ADC0, &adc_config_struct);	//Initialize the ADC with Default configuration

	ADC16_EnableHardwareTrigger(ADC0, false);	//Enable hardware trigger for ADC

	 ADC16_DoAutoCalibration(ADC0); 	//Enable Auto Calibration for the ADC0

	adc_channel_config_struct.channelNumber = 0;	//Select channel number for ADC


	adc_channel_config_struct.enableInterruptOnConversionCompleted = false;	//Disable ADC interrupts
	PRINTF("\n \r *********ADC INITIALIZED**********");
}


/*******************************************************************************************************
 * Function Name:void dac_write(uint16_t val)
 * Description :This function Writes the values to the DAC buffer
 * @input:  uint16_t value to be written
 * @Return : void
 *******************************************************************************************************/
void dac_write(uint16_t val)
{
	DAC_SetBufferValue(DAC0,0,val);	//Set the DAC buffer value to the input value recieved
//	PRINTF("\n \r*********VALUE WRITTEN TO DAC**********");
}

/*******************************************************************************************************
 * Function Name:uint32_t adc_read()
 * Description :This function Reads the ADC value from the buffer and returns the value to the calling function
 * @input:  void
 * @Return :uint32_t value from ADC
 *******************************************************************************************************/
uint32_t adc_read()
{
	ADC16_SetChannelConfig(ADC0, 0, &adc_channel_config_struct);	//Set channel to 0 and initialize with channel struct config
	while ((ADC16_GetChannelStatusFlags(ADC0,0) & kADC16_ChannelConversionDoneFlag)==0)	//Wait for channel convertion flag to set
	{


	}
	return ADC16_GetChannelConversionValue(ADC0,0);	//Return the ADC value to the called function

}
