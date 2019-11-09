/*
 * circularbuff.c
 *
 *  Created on: Nov 9, 2019
 *      Author: SURAJ THITE
 */

#include "circularbuff.h"
/*******************************************************************************************************
 * Function Name: cbuff_init(cbuff* ptr,uint16_t length)
 * Description : This function initializes the circular buffer
 * @input: pointer to a structure , length of circular buffer to be initialized
 * @Return : status codes
 *******************************************************************************************************/

int8_t cbuff_init(cbuff* ptr,uint16_t length)
{
	(ptr -> cbuffptr) = malloc(length);
	ptr = malloc(sizeof(cbuff));
	if(ptr->cbuffptr == NULL)
		{return Null_Error;}
	else
		{return Success;}
}



/*******************************************************************************************************
 * Function Name:cbuff_is_full(cbuff* ptr)
 * Description : This function checks whether the circular buffer is full or not.
 * @input: pointer to a structure
 * @Return :status codes
 *******************************************************************************************************/

uint8_t cbuff_add(cbuff* ptr,uint8_t data)
{
	uint8_t i = cbuff_is_full(ptr);
	if(i == Buffer_Full)
		{return Buffer_Full;}
	else
	{
		if (((ptr->head)+1)==(ptr->cbuffptr+ptr->length))
			{ptr->head = ptr->cbuffptr;}
		else
			{
			ptr->head++;
			(ptr->count++);
			}
		*(ptr->head) = data;
		return Success;
	}
}


/*******************************************************************************************************
 * Function Name:cbuff_remove(cbuff* ptr,uint8_t* store)
 * Description : This function removes an element from the circular buffer and stores it in the pointer store passed as argument
 * @input: pointer to a structure , pointer to a location where data is to be stored.
 * @Return :status codes
 *******************************************************************************************************/

uint8_t cbuff_remove(cbuff* ptr,uint8_t* store)
{
	uint8_t i = cbuff_is_empty(ptr);
	if(i == Buffer_Empty)
		{return Buffer_Empty;}
	else
	{
		if (((ptr->tail)+1)==(ptr->cbuffptr)+(ptr->length))
			{ptr->tail = ptr->cbuffptr;}
		else
			{
			ptr->tail++;
			(ptr->count--);
			}
		*store=*(ptr->tail);
		return Success;
	}
}


/*******************************************************************************************************
 * Function Name:cbuff_is_full(cbuff* ptr)
 * Description : This function checks whether the circular buffer is full or not.
 * @input: pointer to a structure
 * @Return :status codes
 *******************************************************************************************************/
uint8_t cbuff_is_full(cbuff* ptr)
	{
	if((ptr->tail)==(ptr->head)+1)
		return Buffer_Full;
	else
		return Success;
	}

/*******************************************************************************************************
 * Function Name: cbuff_is_empty(cbuff* ptr)
 * Description : This function checks whether the buffer is empty or not
 * @input: pointer to a structure
 * @Return :status codes
 *******************************************************************************************************/

uint8_t cbuff_is_empty(cbuff* ptr)
{
	if((ptr->tail)==(ptr->head))
		return Buffer_Empty;
	else
		return Success;
}

/*******************************************************************************************************
 * Function Name: cbuff_destroy(cbuff* ptr)
 * Description : This function frees the memory allocated for circular buffer
 * @input: pointer to a structure
 * @Return : status codes
 *******************************************************************************************************/

uint8_t cbuff_destroy(cbuff* ptr)
{
	{
	free(ptr->cbuffptr);
	free(ptr->head);
	free(ptr->tail);
	free(ptr->size);
	free(ptr);
	return Success;
	}
}






