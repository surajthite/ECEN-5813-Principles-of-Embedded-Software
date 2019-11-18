
#include "circularbuff.h"
#include "fsl_debug_console.h"

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
		return null_ptr;
    }
	else
    {
		if((ptr->cbuffptr)==NULL)
		{
			ptr->head=NULL;
			ptr->tail=NULL;
			ptr->count=0;
			ptr->size=0;
			return cbuff_init_fail;
		}
		else
		{
			ptr->cbuffptr= (uint8_t*)malloc(sizeof(uint8_t)*length);
			ptr->size= length;
			ptr->count=0;
			ptr->head=ptr->cbuffptr;
			ptr->tail=ptr->cbuffptr;
			return  cbuff_init_success;
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
		return null_ptr;
    }
	else if ((ptr->cbuffptr)==NULL)
    {
		return buffer_NA;
    }
	else if ((ptr->count)==(ptr->size))
    {
		return cbuff_full;
    }
	else
    {
		return cbuff_not_full;
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
		return null_ptr;
    }
	else if ((ptr->cbuffptr)==NULL)
    {
		return buffer_NA;
    }
	else if ((ptr->count)==0)
    {
		return cbuff_empty;
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
		return null_ptr;
    }
	else if ((ptr->cbuffptr)==NULL)
    {
		return buffer_NA;
    }
	else if (cbuff_check_full(ptr)==cbuff_full)
    {
		return cbuff_full;
    }
	else if(ptr->head==((ptr->cbuffptr)+((ptr->size)-1)))
    {
		*(ptr->head)= val;
		PRINTF(" \r \n WRAP ADD ::New Item Inserted at position %d location :: %d ",ptr->head,*ptr->head);
		ptr->head=ptr->cbuffptr;
		//ptr->head++;
		ptr->count++;
		//ptr->count =0;
		return wrap_add;
    }
	else
    {
		*(ptr->head)=val;
		PRINTF(" \r \n New Item Inserted at position %d location :: %d ",ptr->head,*ptr->head);
		ptr->head++;
		ptr->count++;
		return cbuff_success;
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
		return null_ptr;
    }
	else if ((ptr->cbuffptr)==NULL)
    {
		return buffer_NA;
    }
	else if (cbuff_isempty(ptr)==cbuff_empty)
    {
		return cbuff_empty;
    }
	else if(ptr->tail==((ptr->cbuffptr)+((ptr->size)-1)))
    {
		*(val)=*(ptr->tail);
		ptr->tail=ptr->cbuffptr;
		ptr->count--;
		return wrap_remove;
    }
	else
    {
		*(val)=*(ptr->tail);
		ptr->tail++;
		ptr->count--;
		return cbuff_success;
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
			return buffer_init_failed;
		}
		else
		{
			return buffer_init_success;
		}
}

/*******************************************************************************************************
 * Function Name:cbuff_status verify_ptr(cbuff *ptr)
 * Description :This Function verifies whether a pointer is within the range of circular buffer
 * @input: pointer to circular buffer.
 * @Return : error status messages
 *******************************************************************************************************/

cbuff_status verify_ptr(cbuff *ptr)
{
	if(ptr >= ptr->cbuffptr && ptr <= ptr->head )
	{
		return ptr_valid;
	}
	else
	{
		return ptr_invalid;
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
		return null_ptr;
    }
	else if ((ptr->cbuffptr)==NULL)
    {
		return buffer_NA;
    }
	else
    {
		PRINTF(" \r \n Buffer Size Reallocated");
		ptr->newcbuffptr=(uint8_t *)realloc(ptr->cbuffptr,sizeof(uint8_t)*length);
		ptr->cbuffptr=ptr->newcbuffptr;
		ptr->size=length;
		return cbuff_success;
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
	uint8_t *temp = ptr->tail;
	for (int i=0;i<ptr->count;i++)
	{
		PRINTF(" \r \n value at position %x location :: %d ",temp,*temp);
		temp++;
	}
}



