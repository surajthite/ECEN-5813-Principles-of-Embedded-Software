/*
 * main.h
 *
 *  Created on: Nov 2, 2019
 *      Author: SURAJ THITE
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "logger.h"
#include "i2c.h"
#include "state_machine.h"


///////////////ENUM for test, debug and status///////////////////
typedef enum
{
	Test,
	Debug,
	Status
}modes ;
/////////////////////////////////////////////////////////////

typedef enum
{
	state_machine1,
	i2cwrite,
	i2creadtemperature,
	POST_TESTread_bytes,
	checkconnection,
	SysTickHandler,
	InitSystick,
	state_machine2,
	state_transition__intable,
	POSTSTATE,
	I2C_READ_TEMPERATURESTATE,
	AVERAGE_WAITSTATE,
	TMEP_ALERTSTATE,
	DISCONNECTEDSTATE,
	ENDSTATE

}fnnames;

////////////////////////////////////////////////////////////////

#endif /* MAIN_H_ */
