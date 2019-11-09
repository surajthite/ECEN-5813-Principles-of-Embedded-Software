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
Buffer_Full,
Buffer_Empty,
Success,
Null_Error,
}cbuff_status;



#endif /* CIRCULARBUFF_H_ */
