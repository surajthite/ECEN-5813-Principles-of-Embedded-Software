/*
 * Copyright 2016-2019 NXP
 * All rights reserved.
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
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
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

/**
 * @file    PES-PROJECT4.c
 * @brief   Application entry point.
 */


/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */

/*
 * @brief   Application entry point.
 */


#include "main.h"
#include "RGBled.h"
#include "unitTest.h"
#include "uCUnit-v1.0.h"

#define MODE (0)

//MODE 0 FOR STATE MACHINE AND MODE 1 FOR TEST CASES


int16_t temp_val; //GLobal Variable to Store current temperature value
int32_t average_temp;//Global variable to store average temperature value
uint32_t total_count; //Global variable to store total no of iterations
states current_state1; //Global variable to store current state
events event1 = INIT;//Global variable to store current event in the state machine
modes select;
bool disconnected; //Check on disconnected state
uint8_t conn_check;//Check on connection check
uint8_t terminate_flag;

int main(void) {

	/* Init board hardware. */

	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();
	/* Init FSL debug console. */
	BOARD_InitDebugConsole();
	RGB_init(); //Initialize the RGB LEDs
	RGB_OFF();	//TURN Them off for now
	i2c_init(); //Initialize the i2c
	Init_SysTick(); //Initialize the Systick timer for 15 seconds delay

#if MODE == 0
	while(terminate_flag==0)
	{
		state_machine_1();// start state machine
	}
#else
	{
		UCUNIT_Init();
		UCUNIT_WriteString("\n**************************************");
		UCUNIT_WriteString("uCUnit demo application");
		UCUNIT_WriteString(__DATE__);
		UCUNIT_WriteString("\nTime:     ");
		UCUNIT_WriteString(__TIME__);
		printf("\n \r Running Test Cases");
		Testsuite_RunTests();
	}
#endif

	printf("\n \r **************PROGRAM TERMINATED*******************");

	return 0 ;
}

