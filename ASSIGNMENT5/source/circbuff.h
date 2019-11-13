#ifndef CIRCBUFF_H_
#define CIRCBUFF_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "main.h"
 // pass and fail cases for functions to return errors
typedef enum errorcheck
{
	addtobuffer_pass=0,
	addtobuffer_fail,
	wrap_flag_add,
	remfrombuffer_pass,
	remfrombuffer_fail,
	bufferfull_pass,
	bufferfull_fail,
	buffer_empty_pass,
	buffer_empty_fail,
	buffer_ptr_valid,
	buffer_ptr_invalid,
	buffer_init_pass,
	buffer_init_fail,
	buffer_delete_pass,
	buffer_delete_fail,
}errorcheck;

typedef struct {                 //create structure for circular buffer
    uint8_t *buffer;      // pointer to a buffer
    uint8_t *head;               // buffer head used for write
    uint8_t *tail; 				// buffer tail used for read
    uint8_t maxlength;        // Maximum length of buffer
    uint8_t count;              // Count of data occupied by buffer
} circbuffstruct;


// Function declaration
errorcheck init_buffer(circbuffstruct *ptr, uint8_t buffersize);
errorcheck add_to_buffer(circbuffstruct *ptr, uint8_t newelement);





#endif
