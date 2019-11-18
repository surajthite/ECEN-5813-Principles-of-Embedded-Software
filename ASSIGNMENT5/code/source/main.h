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
void echo_function_interrupt();
void echo_function_poll(char a);
void application_poll(uint8_t *ch);
#define BAUDRATE 9600
#endif /* MAIN_H_ */
