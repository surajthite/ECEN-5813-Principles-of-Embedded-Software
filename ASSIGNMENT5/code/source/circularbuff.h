/*
 * circularbuff.h
 *
 *  Created on: Nov 9, 2019
 *      Author: SURAJ THITE
 */

#ifndef CIRCULARBUFF_H_
#define CIRCULARBUFF_H_
#include "stdint.h"
#include "stdio.h"

typedef struct
{
int8_t* cbuffptr; // base of the circular buffer
int8_t* head;	//head of the circular buffer
int8_t* tail;	//tail of the circular buffer
int8_t  size;	// maximum size of the circular buffer
//int8_t length;	//Length of the circular buffer
int8_t count;	//no of elements used in the circular buffer
}cbuff;


typedef enum
{
	SUCCESS,
	FAIL,
	allocated_free,
	pointer_invalid,
	buffer_not_initialized,
	added,
	removed,
	buffer_full,
	buffer_not_full,
	buffer_empty,
	buffer_not_empty,
	wrap_Add,
	wrap_Remove,
	over_fill,
	over_empty,
}cbuff_status;

int8_t cbuff_init(cbuff* ptr,int8_t length);
uint8_t cbuff_add(cbuff* ptr,uint8_t data);
uint8_t cbuff_remove(cbuff* ptr,uint8_t store);
uint8_t cbuff_is_full(cbuff* ptr);
uint8_t cbuff_is_empty(cbuff* ptr);
uint8_t cbuff_destroy(cbuff* ptr);

void cbuff_print(cbuff* ptr);

#endif /* CIRCULARBUFF_H_ */
