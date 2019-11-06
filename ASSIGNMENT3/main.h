/*
 * main.h
 *
 *  Created on: Oct 20, 2019
 *      Author: SURAJ THITE , Atharv Desai
 */

#ifndef MAIN_H_
#define MAIN_H_

//Include Files
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "memory.h"
#include "pattern.h"


//Function to create the delay for LEDS to observe the State
void delay(int time_ms);

# define SEED 5
# define length 4

#endif /* MAIN_H_ */
