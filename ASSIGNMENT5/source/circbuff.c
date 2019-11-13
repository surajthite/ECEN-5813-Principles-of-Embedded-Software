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
			ptr->count = 0;
			return buffer_init_pass;
		}
	}

/******************** Function to add data to buffer***********************/

errorcheck add_to_buffer(circbuffstruct* ptr,uint8_t data)
{
	if(ptr ==NULL)
		return buffer_init_fail;
	else if(ptr->count ==ptr->maxlength)
		return addtobuffer_fail;
	else if(ptr->head == ptr->buffer + ptr->maxlength -1)   // ptr-> count == ptr-> maxlength -1
	{
		*ptr->head =data;            // using head to write the data
		ptr->head = ptr->buffer;   // to bring head back to starting position
		ptr->count++;
		return wrap_flag_add;
	}
	else
	{
		*ptr ->head =data;
		ptr->head++;
		ptr->count++;
		return addtobuffer_pass;
	}
}


/***********************Remove data from buffer****************************/
