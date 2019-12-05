/*
 * tasks.h
 *
 *  Created on: Dec 1, 2019
 *      Author: SURAJ THITE
 */

#ifndef TASKS_H_
#define TASKS_H_

#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "fsl_dma.h"
#include "fsl_dmamux.h"
#define CBUFF_LEN 64

void dac_task(void *x);
void adc_task(void *p);
void start_dsp(void *p);
void updateTime(void *p);
void DMA_Callback(dma_handle_t *handle, void *param);
#endif /* TASKS_H_ */
