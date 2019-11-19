/*
 * RGBled.c
 *
 *  Created on: Sep 28, 2019
 *      Author:SURAJ THITE , ATHARV DESAI
 */



#include "board.h"
#include "fsl_debug_console.h"
#include "fsl_gpio.h"

#include "clock_config.h"
#include "pin_mux.h"

/*******************************************************************************/
/* Function name:RGB_init
 * Parameters: void
 * Return : void
 * Description: Function to initialize the GPIO RGB Led Pins . */
/*******************************************************************************/
void RGB_init()
{
		gpio_pin_config_t led_blue_config = {
	        kGPIO_DigitalOutput, 1,
	    };	//Config the pin  for BLUE LED to Digital Output
		GPIO_PinInit(BOARD_LED_BLUE_GPIO,BOARD_LED_BLUE_GPIO_PIN, &led_blue_config);
	    gpio_pin_config_t led_red_config = {
	        kGPIO_DigitalOutput, 1,
	    };	//Config the pin  for RED LED to Digital Output
	    GPIO_PinInit(BOARD_LED_RED_GPIO,BOARD_LED_RED_GPIO_PIN, &led_red_config);
	    gpio_pin_config_t led_green_config = {
	        kGPIO_DigitalOutput, 1,
	    };	//Config the pin  for GREEN LED to Digital Output
	    GPIO_PinInit(BOARD_LED_GREEN_GPIO,BOARD_LED_GREEN_GPIO_PIN, &led_green_config);	//Initialize the GPIO Pins
}


/*******************************************************************************/
/* Function name:led_switch(int n )
 * Parameters: current state n
 * Return : void
 * Description: Function to initialize the GPIO RGB Led Pins . */
/*******************************************************************************/
void led_switch(int n)
 {
	GPIO_SetPinsOutput(BOARD_LED_GREEN_GPIO, 1u << BOARD_LED_GREEN_GPIO_PIN);	//Clear the Pins
	GPIO_SetPinsOutput(BOARD_LED_RED_GPIO, 1u << BOARD_LED_RED_GPIO_PIN);
	GPIO_SetPinsOutput(BOARD_LED_BLUE_GPIO, 1u << BOARD_LED_BLUE_GPIO_PIN);

	switch (n)
	{
	// Switch LED BLUE ON and TURN OTHER LEDs OFF
	case 0:
		{
		GPIO_ClearPinsOutput(BOARD_LED_BLUE_GPIO, 1u << BOARD_LED_BLUE_GPIO_PIN);
		GPIO_SetPinsOutput(BOARD_LED_RED_GPIO, 1u << BOARD_LED_RED_GPIO_PIN);
		GPIO_SetPinsOutput(BOARD_LED_GREEN_GPIO, 1u << BOARD_LED_GREEN_GPIO_PIN);
		delay(100);
		}
		break;
		// Switch LED RED ON and TURN OTHER LEDs OFF
	case 1:
	{

			GPIO_ClearPinsOutput(BOARD_LED_RED_GPIO, 1u << BOARD_LED_RED_GPIO_PIN);
			GPIO_SetPinsOutput(BOARD_LED_BLUE_GPIO, 1u << BOARD_LED_BLUE_GPIO_PIN);
			GPIO_SetPinsOutput(BOARD_LED_GREEN_GPIO, 1u << BOARD_LED_GREEN_GPIO_PIN);
			delay(100);
	}
			break;
			// Switch LED GREEN ON and TURN OTHER LEDs OFF
	case 2:
	{
			GPIO_ClearPinsOutput(BOARD_LED_GREEN_GPIO, 1u << BOARD_LED_GREEN_GPIO_PIN);
			GPIO_SetPinsOutput(BOARD_LED_RED_GPIO, 1u << BOARD_LED_RED_GPIO_PIN);
			GPIO_SetPinsOutput(BOARD_LED_BLUE_GPIO, 1u << BOARD_LED_BLUE_GPIO_PIN);
			//delay(1000);
	}
			break;
	case 3:
		{
			// Switch LED BLUE ON and TURN OTHER LEDs OFF
		GPIO_ClearPinsOutput(BOARD_LED_BLUE_GPIO, 1u << BOARD_LED_BLUE_GPIO_PIN);
		GPIO_SetPinsOutput(BOARD_LED_RED_GPIO, 1u << BOARD_LED_RED_GPIO_PIN);
		GPIO_SetPinsOutput(BOARD_LED_GREEN_GPIO, 1u << BOARD_LED_GREEN_GPIO_PIN);
		}
		break;
	}
 }


/*******************************************************************************************************
 * Function Name:int delay(int time_ms)
 * Description : this function provides delay in milliseconds according to input parameters
 * @input:time in milliseconds
 * @Return : NULL
 *******************************************************************************************************/

void delay(int time_ms)
{
	volatile uint32_t i = 0;
	for (i = 0; i < 2400*time_ms; ++i)
	{
		__asm("NOP"); /* No operation */
	}
}

/*******************************************************************************/
/* Function name:RGB_off
 * Parameters: void
 * Return : void
 * Description: Function to turn off the RGB Led Pins . */
/*******************************************************************************/

void RGB_OFF()
{	// Clear all the  LEDs.
	GPIO_SetPinsOutput(BOARD_LED_BLUE_GPIO, 1u << BOARD_LED_BLUE_GPIO_PIN);
	GPIO_SetPinsOutput(BOARD_LED_GREEN_GPIO, 1u << BOARD_LED_GREEN_GPIO_PIN);
	GPIO_SetPinsOutput(BOARD_LED_RED_GPIO, 1u << BOARD_LED_RED_GPIO_PIN);
}
