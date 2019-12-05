/*
 * tasks.c
 *
 *  Created on: Dec 1, 2019
 *      Author: SURAJ THITE
 */

#include "main.h"


#include "tasks.h"

#include "circularbuff.h"
#include "logger.h"
#include "wave.h"
#include "adc_dac.h"
#include "fsl_debug_console.h"
#include "semphr.h"
#include "math.h"
#include "queue.h"
#include "FreeRTOS.h"
#include "dma.h"
uint8_t adc_read_count;
TaskHandle_t DSP_Handle;
SemaphoreHandle_t led_mutex;

//extern cbuff *adc_buffer;
extern QueueHandle_t ADC_BUFF;
QueueHandle_t DSP_BUFF;
uint16_t buffer[64];

uint16_t minInt;
uint16_t maxInt;
uint32_t sum;
uint32_t stdDevSum;
float values[64];
float min;
float max;
float average;
float std_dev;
uint16_t current;
uint8_t cycle = 0;



extern dma_handle_t g_DMA_Handle;
extern dma_transfer_config_t transferConfig;
volatile bool g_Transfer_Done;
#define RES (3.3/4096)


void dac_task(void *x)
{

	while(1)
	{
#if APPLICATION
		if(led_mutex != NULL)
		{
			if(xSemaphoreTake(led_mutex,(TickType_t) 100) == pdTRUE)
			{
				//SET RGB LED
				xSemaphoreGive( led_mutex );
			}
		}
#else
		//Set RGB led
#endif

	//	PRINTF("\n \r ********** Writing to  DAC***********");

		uint16_t val = get_next_val();

		PRINTF(" \n \r Writing %d to the DAC.", val);

		dac_write(val);


	//	PRINTF("\n \r ********** Waiting for Next Task***********");

		vTaskDelay(100);

	//	PRINTF("\n \r ********** Writing Next Value to DAC***********");
	}
}


void adc_task(void *p)
{
	while (1)
	{
		adc_read_count++;
		if(adc_read_count > 4)
		{
			xSemaphoreGive(led_mutex);
		}

		uint16_t val = adc_read();

		PRINTF(" \n \r Reading %d from  the ADC.", val);

//		cbuff_add(adc_buffer,val);
//		 cbuff_print(adc_buffer);
	//	PRINTF("\n \r Writing value to the Queue");
		if((xQueueSend(ADC_BUFF,(void *)&val,0) != 1))

		{

			//PRINTF("\n \r ************DMA TRANSFER STARTED**************");
			adc_read_count = 0;

			xSemaphoreTake(led_mutex,(TickType_t) 100);
			//RGBLED_set(led, false, false,true);

			DMA_CreateHandle(&g_DMA_Handle, DMA0, DMA_CHANNEL);
			DMA_SetCallback(&g_DMA_Handle, DMA_Callback, NULL);
			DMA_PrepareTransfer(&transferConfig,ADC_BUFF->pcHead,2,buffer,2,64*2,kDMA_MemoryToMemory);
			DMA_SubmitTransfer(&g_DMA_Handle, &transferConfig, kDMA_EnableInterrupt);
			DMA_StartTransfer(&g_DMA_Handle);
			PRINTF("\n \r ************DMA TRANSFER STARTED**************");
			while (g_Transfer_Done != true)
				{

				}
				PRINTF("\n \r ************DMA TRANSFER SUCCESSFUL**************");

			PRINTF("\n \r ************Queue Reset**************");

			xQueueReset(ADC_BUFF);

			xTaskCreate(start_dsp,( portCHAR *)"DSP started", configMINIMAL_STACK_SIZE, NULL, 1, &DSP_Handle);
		}
		PRINTF("\n \r ********** Waiting for Next Task***********");
		vTaskDelay(100);
		PRINTF("\n \r ********** Reading Next Value to ADC***********");
	}
}

void start_dsp(void *p)
{
	while(1)
		{
			minInt = 65535;
			maxInt = 0;
			sum = 0;
			stdDevSum = 0;
			for(int i = 0; i < 64; i++)
			{
		    	if(buffer[i] > maxInt)
		    	{
		    		maxInt = buffer[i] ;
		    	}
		    	if(buffer[i]  < minInt)
		    	{
		    		minInt = buffer[i] ;
		    	}
		    	values[i] = buffer[i] *RES;
		    	sum+=buffer[i];
			}

		    min = minInt*RES;
		    max = maxInt*RES;
		    average = sum*RES/64.0;
		    float stdDevSum = 0.0f;
		    for(int j = 0; j < 64; j++)
		    {
		    	stdDevSum += powf((values[j] - average), 2);
		    }
		    std_dev = sqrtf(stdDevSum/64.0);
		  //  Logger_logString(logger, "DSP REPORT", "doDSP", STATUS_LEVEL);
		    PRINTF("\n \r Generating Report");
		    PRINTF("\n \rIteration: %d \n \r",cycle);
		    PRINTF("Min: %f\n\rMax: %f\n\rAvg: %f\n\rStandard Dev: %f\n\r",min,max,average,std_dev);
		    cycle++;
		    if(cycle > 4)
		    {
		    	vTaskEndScheduler();
		    }
		    vTaskSuspend( NULL );
		}

}


void DMA_Callback(dma_handle_t *handle, void *param)
{
	g_Transfer_Done = true;
}

