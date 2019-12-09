/*
 * tasks.c
 *
 *  Created on: Dec 1, 2019
 *      Author: SURAJ THITE
 */

#include "main.h"
#include "RGBled.h"

#include "tasks.h"
#include "logger.h"
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
#include "logger.h"
#include "time_stamp.h"
extern uint64_t current_time;
extern modes a;
uint8_t adc_read_count;	//Global variable to store the no of iterations for the  ADC

TaskHandle_t DSP_Handle;	//DSP Task Handle

SemaphoreHandle_t led_mutex;	//Semaphore to control the LED

//extern cbuff *adc_buffer;

extern QueueHandle_t ADC_BUFF;	//Queue handle to store the Recieved ADC values in the Queues

QueueHandle_t DSP_BUFF;

uint16_t buffer[64];	//BUffer to store the DSP values for DSP processing


float min;	//variable to store minimum values
float max;	//variable to store maximum values
float avg;	//variable to store average value
uint16_t minInt;	//Variable to store minimum values
uint16_t maxInt;	//Variable to store the maximum integer value
uint32_t sum;	//Variable to store the sum
float values[64];	//Temporary buffer
float standard_dev;	//Variable to store standard deviation
float std_deviation_sum;	//Variable to accumulate standard deviation sum
//uint16_t current;
uint8_t iterations = 0;	//Variable to store no of iterations



extern dma_handle_t g_DMA_Handle;	//DMA handle
extern dma_transfer_config_t transferConfig;	//DMA config
volatile bool g_Transfer_Done;
#define RES (3.3/4096)	//Reference from SDK Example ADC_DAC

/*******************************************************************************************************
 * Function Name:void dac_task(void *x)
 * Description :This is a DAC write task which writes the values generated from lookup table to the DAC
 * @input:  void pointer
 * @Return : void pointer
 *******************************************************************************************************/

void dac_task(void *x)
{

	while(1)
	{
#if APPLICATION
		if(led_mutex != NULL)	//If mutex is not equal to null then take the semaphore and release the mutex
		{
			if(xSemaphoreTake(led_mutex,(TickType_t) 100) == pdTRUE)
			{
				//SET RGB LED
				xSemaphoreGive( led_mutex );
				uint16_t val = get_next_val();	//Get new value to from the lookup table
				if (a == Debug)
					PRINTF(" \n \r Writing %d to the DAC.", val);
				led_switch(2);	//Switch LED
				dac_write(val);	//Write value from lookup table to DAC
				RGB_OFF();	//Turn off the RGB led
			}
		}
#endif

	if (a == Debug)

	{	PRINTF("\n \r ********** Writing to  DAC***********");
		PRINTF("\n \r ********** Waiting for Next Task***********");
	}

	vTaskDelay(100);	//GIve a delay for 100 milliseconds and start rescheduling algorithm
	current_time++;
	if (a == Debug)
		PRINTF("\n \r ********** Writing Next Value to DAC***********");
	}
}

/*******************************************************************************************************
 * Function Name:void adc_task(void *p)
 * Description :This function reads the values from the ADC and stores it in a queue.The values are
 * transferred to the DSP buffer using DMA transfer.
 * @input:  void pointer
 * @Return : void
 *******************************************************************************************************/
void adc_task(void *p)
{
	while (1)
	{
		adc_read_count++;	//Increment the adc Count
		if(adc_read_count > 4)	//If count is greater than 4, give semaphore signal
		{
			xSemaphoreGive(led_mutex);
		}

		uint16_t val = adc_read();	//Get value to be read from ADC periopheral
		if (a == Debug)
			PRINTF(" \n \r Reading %d from  the ADC.", val);

		if((xQueueSend(ADC_BUFF,(void *)&val,0) != 1))	//If Queue is full the initiazte the DMA transfer

		{

			//PRINTF("\n \r ************DMA TRANSFER STARTED**************");
			adc_read_count = 0;

			xSemaphoreTake(led_mutex,(TickType_t) 100);	//Take Mutex
			//RGBLED_set(led, false, false,true);
			//Initiate the DMA transfer
			DMA_CreateHandle(&g_DMA_Handle, DMA0, DMA_CHANNEL);
			DMA_SetCallback(&g_DMA_Handle, DMA_Callback, NULL);
			DMA_PrepareTransfer(&transferConfig,ADC_BUFF->pcHead,2,buffer,2,64*2,kDMA_MemoryToMemory);
			DMA_SubmitTransfer(&g_DMA_Handle, &transferConfig, kDMA_EnableInterrupt);
			DMA_StartTransfer(&g_DMA_Handle);
			if (a == Debug)
				PRINTF("\n \r ************DMA TRANSFER STARTED**************");
			//Wait for DMA transfer to complete
			while (g_Transfer_Done != true)
				{

				}
				PRINTF("\n \r ************DMA TRANSFER SUCCESSFUL**************");
				led_switch(0);
				RGB_OFF();
			if (a == Debug)
			PRINTF("\n \r ************Queue Reset**************");
			//Reset the Queue to store next values
			xQueueReset(ADC_BUFF);
			//initiate the DSP task
			xTaskCreate(start_dsp,( portCHAR *)"DSP started", configMINIMAL_STACK_SIZE, NULL, 1, &DSP_Handle);
		}
		if (a == Debug)
			PRINTF("\n \r ********** Waiting for Next Task***********");

		//Give a delay of 0.1 seconds and reschedule the tasks
		vTaskDelay(100);
		current_time++;
		if (a == Debug)
		PRINTF("\n \r ********** Reading Next Value to ADC***********");
	}
}
/*******************************************************************************************************
 * Function Name:void start_dsp(void *p)
 * Description :This function starts the DSP processing upon the values recieved in the DSP buffer.
 * @input:  void pointer
 * @Return : void
 *******************************************************************************************************/
void start_dsp(void *p)
{
Log_String(a,2,"Started with DSP");
//PRINTF("\n\r ***********Started With  DSP***********");
	while(1)
		{
			minInt = 65535;
			maxInt = 0;
			sum = 0;
			std_deviation_sum = 0;
			for(int i = 0; i < 64; i++)
			{
		    	if(buffer[i] > maxInt)		//Store the maximum value
		    	{
		    		maxInt = buffer[i] ;
		    	}
		    	if(buffer[i]  < minInt)	//Store the minimum value
		    	{
		    		minInt = buffer[i] ;
		    	}
		    	values[i] = buffer[i] *RES;	//Store the resolution values in an temporary array
		    	sum+=buffer[i];	//Increment the sum
			}
			//Update  average , maximum , minimum values with the resultion
			avg = sum*RES/64.0;
		    min = minInt*RES;
		    max = maxInt*RES;

		    float std_deviation_sum = 0.0f;
		    for(int j = 0; j < 64; j++)
		    {
		    	std_deviation_sum += powf((values[j] - avg), 2); //Calculate the sum for standard deviation
		    }
		    standard_dev = sqrtf(std_deviation_sum/64.0);	//Calculate standard deviation
		  //  if (a == Debug)
		    PRINTF("\n \r --------- Generating Report----------");
		  //  if (a == Debug)
		    PRINTF("\n \rIterations: %d \n \r",iterations);

		    PRINTF("Min: %f\n\rMaximum Value : %f\n\rAvgerage Value: %f\n\rStandard Deviation: %f\n\r",min,max,avg,standard_dev);	//Print Minimum value ,Maximum value and Standard Deviation

		    iterations++;	//increment the iterations count

		    if(iterations > 4)
		    {
		    	vTaskEndScheduler();	//If 4 iterations are done then , End the task scheduler
		    }
		    vTaskSuspend( NULL );	//Suspend task and service next task in the Queue
		}

}

/*******************************************************************************************************
 * Function Name:void DMA_Callback(dma_handle_t *handle, void *param)
 * Description :This is a callback function to indicate the successful transfer and set the flag respectively.
 * @input:  dma handle pointer , void pointer
 * @Return : void
 *******************************************************************************************************/
void DMA_Callback(dma_handle_t *handle, void *param)
{
	g_Transfer_Done = true;	//Set a flag to indicate thw DMA transfer is complete.
}

