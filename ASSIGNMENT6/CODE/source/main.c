/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "dma.h"
#include "circularbuff.h"

/* Freescale includes. */

#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "board.h"

#include "pin_mux.h"
#include "wave.h"

#include "adc_dac.h"

#include "tasks.h"
//cbuff *adc_buffer;

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define APPLICATION 1
/* Task priorities. */
//#define hello_task_PRIORITY (configMAX_PRIORITIES - 1)

TimerHandle_t DACTimerHandle = NULL;
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
QueueHandle_t ADC_BUFF;

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Application entry point.
 */
int main(void)
{
	/* Init board hardware. */
	BOARD_InitPins();
	BOARD_BootClockRUN();
	BOARD_InitDebugConsole();

//	adc_buffer= malloc(sizeof(cbuff));
//	adc_buffer->cbuffptr = malloc(sizeof(uint32_t) * 64);
//	cbuff_init(adc_buffer,64);
//	PRINTF("\n \r ADC buffer  Initialized");


	//
	//    dma_init();
	//
	//    for (int i=20;i<30;i++)
	//    {
	//    	cbuff_add(x,i);
	//    }
	//
	//    cbuff_print(x);
	//
	//    dma_transfer(x->cbuffptr, y->cbuffptr,10);
	//
	//    y->count = 10;
	//
	//    cbuff_print(y);

	initialize_dac();

	initialize_adc();

	dma_init();

	sine_lookup_generate();
	ADC_BUFF = xQueueCreate(64,sizeof(uint16_t));
	PRINTF("\n \r xQueue Create Initialized Initialized");
	xTaskCreate(updateTime,( portCHAR *)"upadte_time", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
	xTaskCreate(dac_task,( portCHAR *)"dactask", configMINIMAL_STACK_SIZE, NULL, 3, NULL);

#if APPLICATION

	xTaskCreate(adc_task,( portCHAR *)"readadc", configMINIMAL_STACK_SIZE, NULL, 4, NULL);

#endif

	vTaskStartScheduler();


	while (1)
	{

	}
}


