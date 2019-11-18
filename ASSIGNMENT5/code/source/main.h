/*
 * main.h
 *
 *  Created on: Nov 9, 2019
 *      Author: AKSHAY THITE
 */

#ifndef MAIN_H_
#define MAIN_H_

#include "circularbuff.h"
#include "char_count_update.h"
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "circularbuff.h"
#include "uart_interrrupt.h"
#include "time_stamp.h"
#include "logger.h"

void echo_function_interrupt();
void echo_function_poll(char a);
void application_poll(uint8_t *ch);
void application_int();

#endif /* MAIN_H_ */
