/*
 * circularbuff.h
 *
 *  Created on: Nov 9, 2019
 *      Author: SURAJ THITE
 */

#ifndef CIRCULARBUFF_H_
#define CIRCULARBUFF_H_

typedef struct
{
uint8_t* cbuffptr; // base of the circular buffer
uint8_t* head;	//head of the circular buffer
uint8_t* tail;	//tail of the circular buffer
uint8_t* size;	// maximum size of the circular buffer
uint8_t length;	//Length of the circular buffer
uint8_t count;	//no of elements used in the circular buffer
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



#endif /* CIRCULARBUFF_H_ */
