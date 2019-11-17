
#include "circularbuff.h"
#include "fsl_debug_console.h"

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
		PRINTF(" \r \n New Item Inserted at position %d location :: %d ",ptr->head,*ptr->head);
		ptr->head=ptr->cbuffptr;
		ptr->head++;
		ptr->count++;
		return cbuff_success;
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
		return cbuff_success;
    }
	else
    {
		*(val)=*(ptr->tail);
		ptr->tail++;
		ptr->count--;
		return cbuff_success;
    }

}


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

void cbuff_print(cbuff* ptr)
{
	uint8_t *temp = ptr->tail;
	for (int i=0;i<ptr->count;i++)
	{
		PRINTF(" \r \n value at position %x location :: %d ",temp,*temp);
		temp++;
	}
}
