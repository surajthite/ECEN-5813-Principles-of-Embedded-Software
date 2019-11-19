/*
 * timer_stamp.c
 *
 *  Created on: Nov 17, 2019
 *      Author: SURAJ THITE ,Atrharv Desai
 */

#include "time_stamp.h"
#include "main.h"
#include "MKL25Z4.h"
static uint64_t current_time = 0;
static const uint64_t time_max = ~0;
/*******************************************************************************************************
 * Function Name:Init_SysTick(void)
 * Description :This function Initializes the SysTick Timer for 0.1 second interrupt.
 * @input: void
 * @Return : Void
 *******************************************************************************************************/
void Init_SysTick(void)
{
	SysTick->LOAD = (48000000L/100);	//Initialize Load value
	NVIC_SetPriority(SysTick_IRQn,3);		//Enable NVIC Interrupt with priority 3
	NVIC_EnableIRQ(SysTick_IRQn);	//Enable NVIC IRQ
	SysTick->VAL=0;	//Set VAL =0
	SysTick->CTRL = SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;	//Enable interrupt
}

/*******************************************************************************************************
 * Function Name:void SysTick_Handler()
 * Description :This function is the IRQ Handler which increments global varibale value for current time in tenths of seconds
 * @input: void
 * @Return : void
 *******************************************************************************************************/
//Event handler for SystickTimer for 15 seconds delay
void SysTick_Handler()
{
	current_time++;	//Increment the gloabl variable
}

/*******************************************************************************************************
 * Function Name:uint64_t get_current_time()
 * Description :This function returns current Systick Counter ValueE
 * @input: void
 * @Return : void
 *******************************************************************************************************/

uint64_t get_current_time()
{
	return current_time;	//Return current time
}

/*******************************************************************************************************
 * Function Name:uint64_t time_passed(uint64_t since)
 * Description :This function returns time elapsed since the bootup
 * Reference from "Making Embedded Systems: Design Patterns for Great Software ;Elecia White Book"
 * @input: void
 * @Return : void
 *******************************************************************************************************/

uint64_t time_passed(uint64_t since)
{
	uint64_t now = current_time;

	if(now >= since)
	{
		return now - since;
	}

	return (now + (time_max-since));
}

/*******************************************************************************************************
 * Function Name:void time_stamp_print()
 * Description :This function prints the time stamp on host connected to the UART0 terminal
 * @input: void
 * @Return : void
 *******************************************************************************************************/

void time_stamp_print()
{
	static char time_buf[2048] = {0};
	for(int i = 0; i < 2048; i++) time_buf[i] = '\0';	//Initialize array with nullCharacters

	uint64_t tenths_count = get_current_time();	//Get current time

	float current = tenths_count / 10;

	//Calculations for conversion to Hours , mins , seconds
	uint64_t sec = (uint64_t)(current)%60;
	uint64_t min = (uint64_t)(current/60)%60;
	uint64_t hrs = (uint64_t)(current/3600)%60;


	sprintf(time_buf, "\n%02d:",  hrs);	//Convert hrs to string
	UART0_print_string(time_buf);	//Send value over UART
	sprintf(time_buf, "%02d:",  min);//Convert min to string
	UART0_print_string(time_buf);//Send value over UART
	sprintf(time_buf, "%02d:",  sec);//Convert sec to string
	UART0_print_string(time_buf);//Send value over UART
	sprintf(time_buf, ".%1d",  tenths_count%10);//Convert tenths_count to string
	UART0_print_string(time_buf);//Send value over UART
}
