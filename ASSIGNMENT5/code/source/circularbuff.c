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

int8_t cbuff_init(cbuff* ptr,int8_t length)
{
	if(ptr->cbuffptr == NULL || length < 0)
	{
		return FAIL;
	}
	else
	{
		ptr->cbuffptr=(int8_t *)malloc(sizeof(int8_t)*length);
		ptr->head = ptr->cbuffptr;
		ptr->tail = ptr->cbuffptr;
		ptr->size = length;
		ptr->count = 0;
		return allocated_free;
	}
}



/*******************************************************************************************************
 * Function Name:cbuff_is_full(cbuff* ptr)
 * Description : This function checks whether the circular buffer is full or not.
 * @input: pointer to a structure
 * @Return :status codes
 *******************************************************************************************************/

uint8_t cbuff_add(cbuff* ptr,uint8_t data)
{
	if(ptr ==NULL)
		return FAIL;
	else if(ptr->count ==ptr->size)
		return over_fill;
	else if(ptr->head == ptr->cbuffptr + ptr->size - 1)
	{
		*ptr->head =data;
		ptr->head = ptr->cbuffptr;
		ptr->count++;
		return wrap_Add;
	}
	else
	{
		*ptr->head =data;
		(ptr->head)++;
		(ptr->count)++;
		return added;
	}
}


/*******************************************************************************************************
 * Function Name:cbuff_remove(cbuff* ptr,uint8_t* store)
 * Description : This function removes an element from the circular buffer and stores it in the pointer store passed as argument
 * @input: pointer to a structure , pointer to a location where data is to be stored.
 * @Return :status codes
 *******************************************************************************************************/

uint8_t cbuff_remove(cbuff* ptr,uint8_t store)
{
	if(ptr==NULL)
		return FAIL;
	else if(cbuff_is_empty(ptr)== buffer_empty)
	{
		return over_empty;
	}
	else if(ptr->tail ==ptr->cbuffptr + ptr->size -1)
	{
		store = *ptr->tail;
		ptr->tail = ptr->cbuffptr;
		(ptr->count)--;
		return wrap_Remove;
	}
	else
	{
		store = *ptr->tail;
		(ptr->tail)++;
		(ptr->count)--;
		return removed;
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
	if(ptr==NULL)
	{	return FAIL;	}
	else if (ptr->count == ptr->size)
	{	return buffer_full;	}
	else
	{	return buffer_not_full;	}
}

/*******************************************************************************************************
 * Function Name: cbuff_is_empty(cbuff* ptr)
 * Description : This function checks whether the buffer is empty or not
 * @input: pointer to a structure
 * @Return :status codes
 *******************************************************************************************************/

uint8_t cbuff_is_empty(cbuff* ptr)
{
	if(ptr==NULL)
		return FAIL;
	else if(ptr->count ==0)
	{
		return buffer_empty;
	}
	else
	{
		return buffer_not_empty;
	}
}

/*******************************************************************************************************
 * Function Name: cbuff_destroy(cbuff* ptr)
 * Description : This function frees the memory allocated for circular buffer
 * @input: pointer to a structure
 * @Return : status codes
 *******************************************************************************************************/

uint8_t cbuff_destroy(cbuff* ptr)
{
	if(ptr ==NULL)
	{
		return FAIL;
	}
	else
	{
		free(ptr->cbuffptr);
		return SUCCESS;
	}
}

/*******************************************************************************************************
 * Function Name: cbuff_print
 * Description : This function prints the elements of circular buffer
 * @input: pointer to a structure
 * @Return : status codes
 *******************************************************************************************************/
void cbuff_print(cbuff* ptr)
{
	int8_t *temp = ptr->tail;
	for (int i=0;i<ptr->count;i++)
	{
		printf("\n \r %d",*temp);
		temp++;
	}
}


