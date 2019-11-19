/*
 * circularbuff.c
 *
 *  Created on: Nov 17, 2019
 *      Author: SURAJ THITE & Atharv Desai
 */
#include "circularbuff.h"
#include "fsl_debug_console.h"
#include "RGBled.h"
extern modes a;
/*******************************************************************************************************
 * Function Name:cbuff_status cbuff_init(cbuff *ptr, uint16_t length)
 * Description :This Function Initializes the circular buffer
 * @input: pointer to circular buffer and length of the circular buffer
 * @Return : error status messages
 *******************************************************************************************************/

cbuff_status cbuff_init(cbuff *ptr, uint16_t length)
{

	if(ptr==NULL || length <=0)
	{
		led_switch(1);	//Change LED to red upon error
		return null_ptr;
	}
	else
	{
		if((ptr->cbuffptr)==NULL)
		{
			led_switch(1);	//Change LED to red upon error
			ptr->head=NULL;	//Initialize  head pointer to NULL
			ptr->tail=NULL;	//Initialize tail pointer to NULL
			ptr->count=0;	//Initialize count to zero
			ptr->size=0;	//Initialize size to zero
			return cbuff_init_fail;	//Return Fail status message
		}
		else
		{
			ptr->cbuffptr= (uint8_t*)malloc(sizeof(uint8_t)*length);	//Allocate memory for the circular buffer
			ptr->size= length;	//Set size of the buffer
			ptr->count=0;	//Initialize count to zero
			ptr->head=ptr->cbuffptr;	//Set head to base address
			ptr->tail=ptr->cbuffptr;	//Set tail to base address
			return  cbuff_init_success;	//Return status
		}
	}
}

/*******************************************************************************************************
 * Function Name:cbuff_status cbuff_check_full(cbuff *ptr)
 * Description :This Function checks whether circular buffer is full or not
 * @input: pointer to circular buffer
 * @Return : error status messages
 *******************************************************************************************************/

cbuff_status cbuff_check_full(cbuff *ptr)
{
	if(ptr==NULL)
	{
		led_switch(1);		//Change LED to red upon error
		return null_ptr;	//Return Status
	}
	else if ((ptr->cbuffptr)==NULL)
	{
		return buffer_NA;	//Return Status
	}
	else if ((ptr->count)==(ptr->size))
	{
		led_switch(1);		//Change LED to red upon error
		return cbuff_full;	//Return Status
	}
	else
	{
		return cbuff_not_full; //Return Status
	}
}

/*******************************************************************************************************
 * Function Name:cbuff_status cbuff_isempty(cbuff *ptr)
 * Description :This Function checks whether circular buffer is empty or not
 * @input: pointer to circular buffer
 * @Return : error status messages
 *******************************************************************************************************/
cbuff_status cbuff_isempty(cbuff *ptr)
{
	if(ptr==NULL)
	{
		led_switch(1);			//Change LED to red upon error
		return null_ptr;		//Return Status
	}
	else if ((ptr->cbuffptr)==NULL)
	{
		return buffer_NA;	//Return Status
	}
	else if ((ptr->count)==0)
	{
		led_switch(1);			//Change LED to red upon error
		return cbuff_empty;		//Return Status
	}
}

/*******************************************************************************************************
 * Function Name:cbuff_status cbuff_add(cbuff *ptr, uint8_t val)
 * Description :This Function adds the value to the address pointed by the head of the circular buffer
 * @input: pointer to circular buffer and value to be added
 * @Return : error status messages
 *******************************************************************************************************/

cbuff_status cbuff_add(cbuff *ptr, uint8_t val)
{
	if(ptr==NULL)
	{
		led_switch(1);		//Change LED to red upon error
		return null_ptr;	//Return Status
	}
	else if ((ptr->cbuffptr)==NULL)
	{
		return buffer_NA;	//Return Status
	}
	else if (cbuff_check_full(ptr)==cbuff_full)
	{
		led_switch(1);			//Change LED to red upon error
		return cbuff_full;		//Return Status
	}
	else if(ptr->head==((ptr->cbuffptr)+((ptr->size)-1)))	//handle Wrap add Condition
	{
		*(ptr->head)= val;	//Store the value at the address pointed by the head

		printf("WRAP ADD ::New Item Inserted at position %d location :: %d \r \n",ptr->head,*ptr->head);
		ptr->head=ptr->cbuffptr;	//Initialize the head to base address of the cbuff pointer
		ptr->count++;	//Increment count
		return wrap_add;	//Return Status
	}
	else
	{
		*(ptr->head)=val;//Store the value at the address pointed by the head
		printf("New Item Inserted at position %d location :: %d  \r \n",ptr->head,*ptr->head);
		ptr->head++;	//Increment the head pointer
		ptr->count++;	//Increment the count
		return cbuff_success;	//Return Status
	}
}

/*******************************************************************************************************
 * Function Name:cbuff_status cbuff_delete(cbuff *ptr, uint8_t *val)
 * Description :This Function deletes  the value to the address pointed by the tail of the circular buffer
 * @input: pointer to circular buffer and pointer to a location where the removed value to be stored
 * @Return : error status messages
 *******************************************************************************************************/
cbuff_status cbuff_delete(cbuff *ptr, uint8_t *val)
{
	if(ptr==NULL)
	{
		led_switch(1);		//Change LED to red upon error
		return null_ptr;	//Return Status
	}
	else if ((ptr->cbuffptr)==NULL)
	{
		led_switch(1);		//Change LED to red upon error
		return buffer_NA;	//Return Status
	}
	else if (cbuff_isempty(ptr)==cbuff_empty)
	{
		led_switch(1);		//Change LED to red upon error
		return cbuff_empty;	//Return Status
	}
	else if(ptr->tail==((ptr->cbuffptr)+((ptr->size)-1)))	//Handle Wrap remove condition
	{
		*(val)=*(ptr->tail);	//Store the value pointed by the tail to a memory address
		ptr->tail=ptr->cbuffptr;	//point tail to the base address of the circular buffer
		ptr->count--;	//Decrement count
		if(a==0 || a==1)
			Log_String(a,cbuffdelete,"Wrap- Deleted");	//T

		return wrap_remove;	//Return Status
	}
	else
	{
		*(val)=*(ptr->tail);	//Store the value pointed by the tail to a memory address
		ptr->tail++;	//Increment the tail address
		ptr->count--;	//Decrement count
		if(a==0 || a==1)
			Log_String(a,cbuffdelete,"Deleted");	//T

		return cbuff_success;	//Return status
	}

}
/*******************************************************************************************************
 * Function Name:cbuff_status verify_init(cbuff* ptr)
 * Description :This Function verifies whether a circular buffer is initialized or not by checking the pointer
 * @input: pointer to circular buffer.
 * @Return : error status messages
 *******************************************************************************************************/
cbuff_status verify_init(cbuff* ptr)
{
	if(ptr->cbuffptr==NULL)
	{
		led_switch(1);		//Change LED to red upon error
		return buffer_init_failed;	//Return status
	}
	else
	{
		return buffer_init_success;	//Return Status
	}
}

/*******************************************************************************************************
 * Function Name:cbuff_status verify_ptr(cbuff *ptr)
 * Description :This Function verifies whether a pointer is within the range of circular buffer
 * @input: pointer to circular buffer.
 * @Return : error status messages
 *******************************************************************************************************/

cbuff_status verify_ptr(uint8_t *ptr1,cbuff *ptr)
{
	if(ptr1 >= ptr->cbuffptr && ptr1 <= ptr->head )	//Check whether passed pointer is in the range of circular buffer
	{

		return ptr_valid;	//return status
	}
	else
	{
		led_switch(1);			//Change LED to red upon error
		return ptr_invalid;		//Return Status
	}

}

/*******************************************************************************************************
 * Function Name:cbuff_status cbuff_resize(cbuff *ptr,uint8_t length)
 * Description :This Function resizes the circular buffer to the size of length passed as parameter implementing realloc function
 * @input: pointer to circular buffer and new length.
 * @Return : error status messages
 *******************************************************************************************************/

cbuff_status cbuff_resize(cbuff *ptr,uint8_t length)
{
	if(ptr==NULL)
	{
		led_switch(1);	//Change LED to red upon error
		return null_ptr;	//Return Status
	}
	else if ((ptr->cbuffptr)==NULL)
	{
		return buffer_NA;	//Return Status
	}
	else
	{
		if(a==0 || a==1)
			Log_String(a,cbuffresize,"*** EXTRA CREDIT: BUFFER RESIZED***");	//T
		ptr->newcbuffptr=(uint8_t *)realloc(ptr->cbuffptr,sizeof(uint8_t)*length);	//Reallocate the memory
		ptr->cbuffptr=ptr->newcbuffptr;	//Set pointer value to new memory location pointed by newcbuff pointer
		//ptr->head =ptr->newcbuffptr;
		ptr->size=length;	//Set size to length passed
		ptr->count =0;		//Rest count to zero
		return cbuff_success;	//Return Status
	}
}

/*******************************************************************************************************
 * Function Name:cbuff_status cbuff_resize(cbuff *ptr,uint8_t length)
 * Description :This Function prints the elements in the circular buffer along with its location
 * @input: pointer to circular buffer.
 * @Return : void
 *******************************************************************************************************/

void cbuff_print(cbuff* ptr)
{
	uint8_t *temp = ptr->tail;	//Temporary pointer to store address of Out location(Tail) of the circular buffer
	for (int i=0;i<ptr->count;i++)
	{
		printf(" \r \n value at position %x location :: %d ",temp,*temp);	//Print the elements of circular buffer
		temp++;	//Increment pointer
	}
}
/*******************************************************************************************************
 * Function Name:cbuff_status cbuff_destroy(cbuff* ptr)
 * Description :This Function destroys the memory allocated for circular buffer
 * @input: pointer to circular buffer and new length.
 * @Return : error status messages
 *******************************************************************************************************/


cbuff_status cbuff_destroy(cbuff* ptr)
{
	if(ptr->cbuffptr==NULL)
	{
		led_switch(1);		//Change LED to red upon error
		return destroy_failed;	//Return Status
	}
	else
	{
		free(ptr->cbuffptr);	//Free memory allocated to cbuff pointer

		return destroy_pass;	//Return Status
	}
}
