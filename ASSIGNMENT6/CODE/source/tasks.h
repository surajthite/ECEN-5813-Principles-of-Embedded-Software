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

#define CBUFF_LEN 64

void dac_task(TimerHandle_t xTimer);
void adc_task(TimerHandle_t xTimer);

#endif /* TASKS_H_ */
