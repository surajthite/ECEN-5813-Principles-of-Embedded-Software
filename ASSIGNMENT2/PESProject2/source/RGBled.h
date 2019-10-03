/*
 * RGBled.h
 *
 *  Created on: Sep 28, 2019
 *   Author:SURAJ THITE , ATHARV DESAI
 */

#ifndef RGBLED_H_
#define RGBLED_H_
void led_switch(int n);	//Function to switch the led_state
void RGB_init();	//Function to initialize the RGB Leds
void RGB_OFF();	//Function to turn off the RGB led off
void status_print_on();	//Function to Print the On status on the UART screen
void status_print_0ff();//Function to Print the Off status on the UART screen

#endif /* RGBLED_H_ */
