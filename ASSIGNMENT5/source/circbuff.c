#include "circbuff.h"
#include "main.h"

/******************Function init_buffer*************************/
errorcheck init_buffer(circbuffstruct * ptr, uint8_t buffersize)

{
	if(ptr->buffer == NULL || buffersize < 0)
		{
			return buffer_init_fail;
		}
		else
		{
			ptr->buffer =(uint8_t *)malloc(sizeof(uint8_t)*buffersize);
			ptr->head = ptr->buffer;
			ptr->tail = ptr->buffer;
			ptr->maxlength = buffersize;
			ptr->countofdata = 0;
			return buffer_init_pass;
		}
	}

/********************************* Function to add data to buffer***********************************/

errorcheck add_to_buffer(circbuffstruct* ptr,uint8_t newelement)
{
	if(ptr ==NULL)
		return buffer_init_fail;
	else if(ptr->countofdata ==ptr->maxlength)
	{
		/* Call realloc Function*******************/
		ptr->head = ptr->buffer;
		*ptr->head =newelement;  //data overwriting starts#########
		ptr->countofadds++;
		ptr->countofdata++;
		return bufferfull_pass;
	}
	else if(ptr->head == ptr->buffer + ptr->maxlength -1)   // ptr-> count == ptr-> maxlength -1
	{
		*ptr->head =newelement;            // using head to write the data
		ptr->head = ptr->buffer;   // to bring head back to starting position
		ptr->countofadds++;
		ptr->countofdata++;
		return wrap_flag_add;      // Data written on wrap around flag
	}
	else
	{
		*ptr ->head =newelement;
		ptr->head++;
		ptr->countofdata++;
		ptr->countofadds++;
		return addtobuffer_pass;
	}
}


/*********************************Remove data from buffer*****************************************/

errorcheck rem_data_from_buffer(circbuffstruct* ptr,uint8_t remelement)
{
	if(ptr==NULL)
		return buffer_init_fail;                             // to check if buffer isnt initialized
	else if (ptr->countofremoves <= ptr->countofadds)
	{
		if (ptr->tail == ptr->buffer + ptr->maxlength -1)   // wrap around byte removal condition
		{
		remelement = *ptr->tail;
		ptr->tail = ptr->buffer;
		ptr->countofdata--;
		ptr->countofremoves++;
		return wrap_flag_remove;
		}
		else                                               // general condition for remove element
		{
		remelement = *ptr->tail;
	    ptr->tail++;
		ptr->countofdata--;
		ptr->countofremoves++;
		return remfrombuffer_pass;
		}
	}
	else
	{
		printf(" Error: Trying to read more data than written in buffer");
		return remfrombuffer_fail;
	}
}


/*********************************Check if buffer full********************************************/

errorcheck is_buffer_full(circbuffstruct* ptr)
{
	if(ptr==NULL)
		return buffer_init_fail;
	else if (ptr->countofdata == ptr->maxlength)
		return bufferfull_pass;
	/************Call realloc function**************/
	else
		return bufferfull_fail;
}

/*********************************Check if buffer empty**************************************************************/

errorcheck is_buffer_empty(circbuffstruct* ptr)
{
	if(ptr==NULL)
		return buffer_init_fail;
	else if (ptr->head == ptr->buffer)    //ptr->count == 0
		return buffer_empty_pass;
	else
		return buffer_empty_fail;

}

/*********************************Destroy a buffer**********************************************************************/
errorcheck buffer_destroy(circbuffstruct* ptr)
{
	if(ptr==NULL)
	{
		return buffer_delete_fail;
	}
	else
	{
		free(ptr->buffer);
		return buffer_delete_pass;
	}
}

/**************************************Buffer initialize verify***********************************************************/
errorcheck verify_buffer_init(circbuffstruct * ptr, uint8_t buffersize)

{
	if(ptr->buffer == NULL || buffersize < 0)
		{
			return buffer_init_fail;
		}
		else
		{
			return buffer_init_pass;
		}
}

/**************************************Reallocate a circular buffer on overflow*******************************************/
errorcheck realloc_buffer(circbuffstruct * ptr)

{
	    ptr->buffer = realloc(ptr->buffer,ptr->maxlength*2);
	    ptr->maxlength = (ptr->maxlength)*2;
	    if (ptr->buffer == NULL)
	    	return buffer_realloc_fail;
	    else
	    	return buffer_realloc_pass;
}
