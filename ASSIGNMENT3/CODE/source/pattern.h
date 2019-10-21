/*
 * pattern.h
 *
 *  Created on: Oct 21, 2019
 *      Author: AKSHAY THITE
 */

#ifndef PATTERN_H_
#define PATTERN_H_


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void mem_status_write_pattern_array(uint32_t * loc, size_t length, uint8_t seed);
void gen_pattern(uint32_t * pattern, size_t length, int8_t seed);



#endif /* PATTERN_H_ */
