/*
 * time_stamp.h
 *
 *  Created on: Nov 17, 2019
 *      Author: SURAJ THITE
 */

#ifndef TIME_STAMP_H_
#define TIME_STAMP_H_

#include "circularbuff.h"

void Init_SysTick(void);
void SysTick_Handler();
uint64_t get_current_time();
uint64_t time_passed(uint64_t since);
void time_stamp_print();

#endif /* TIME_STAMP_H_ */
