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
	Allocate_Free,
	Invalid_Pointer,
	Non_Initialized_Buffer,
	Added,
	Removed,
	Buffer_Full,
	Buffer_Not_Full,
	Buffer_Empty,
	Buffer_Not_Empty,
	Wrap_Add,
	Wrap_Remove,
	Over_Fill,
	Over_Empty,
}cbuff_status;



#endif /* CIRCULARBUFF_H_ */
