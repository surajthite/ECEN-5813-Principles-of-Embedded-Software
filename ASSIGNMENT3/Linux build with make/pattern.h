/*
 * pattern.h
 *
 *  Created on: Oct 21, 2019
 *      Author: SURAJ THITE
 */

#ifndef PATTERN_H_
#define PATTERN_H_


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//Function to generate pattern for storing and verification purpose.
void mem_status_write_pattern_array(uint32_t * loc, uint32_t length, uint8_t seed);
void gen_pattern(uint32_t * pattern, uint32_t length, int8_t seed);



#endif /* PATTERN_H_ */
