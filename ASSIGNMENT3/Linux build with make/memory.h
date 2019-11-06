/*
 * memory.h
 *
 *  Created on: Oct 20, 2019
 *      Author: SURAJ THITE
 */

#ifndef MEMORY_H_
#define MEMORY_H_
#include <stdint.h>
typedef enum mem_status
{
SUCCESS = 0, // no error
FAILED // failure case
} mem_status;


// Functions for memory tests //

mem_status write_pattern(uint32_t * loc, uint32_t length, uint8_t seed);
mem_status invert_block(uint32_t * loc, uint32_t length);
mem_status write_memory(uint32_t * loc, uint16_t value);
uint32_t* display_mem(uint32_t * loc, uint32_t length);
void free_mem(uint32_t *ptr1);
uint32_t * allocate_words(uint32_t length);
uint32_t * verify_pattern(uint32_t * loc, uint32_t length, int8_t seed);
uint32_t * get_address(uint32_t  offset);


#endif /* MEMORY_H_ */
