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
	wrap_flag_remove,
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
	buffer_realloc_pass,
	buffer_realloc_fail
}errorcheck;

typedef struct {                 //create structure for circular buffer
    uint8_t *buffer;             // pointer to a buffer
    uint8_t *head;               // buffer head used for write
    uint8_t *tail; 				 // buffer tail used for read
    uint8_t maxlength;           // Maximum length of buffer
    uint8_t countofdata;               // Count of data occupied by buffer
    uint8_t countofadds;         // count of no. of times data added
    uint8_t countofremoves;      // count of no. of times data removed
} circbuffstruct;


// Function declaration
errorcheck init_buffer(circbuffstruct *ptr, uint8_t buffersize);
errorcheck add_to_buffer(circbuffstruct *ptr, uint8_t newelement);
errorcheck is_buffer_full(circbuffstruct* ptr);
errorcheck is_buffer_empty(circbuffstruct* ptr);
errorcheck rem_data_from_buffer(circbuffstruct* ptr,uint8_t remelement);
errorcheck buffer_destroy(circbuffstruct* ptr);
errorcheck verify_buffer_init(circbuffstruct * ptr, uint8_t buffersize);
errorcheck realloc_buffer(circbuffstruct * ptr);




#endif
