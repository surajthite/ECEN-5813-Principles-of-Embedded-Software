/*
 * memory.c
 *
 *  Created on: Oct 20, 2019
 *      Author: SURAJ THITE
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "memory.h"
#include "RGBled.h"
#include "pattern.h"
uint32_t  *ptr;
uint32_t *last_ptr;
int i;

uint32_t * allocate_words(size_t length)
{

	i=4*length;

	ptr= malloc(i);

	last_ptr=ptr + length;


	/*check the pointer to see whether the memory block can be allocated or not*/
	if (ptr==NULL)
	{
		printf("\n \r Can't allocate memory\n");
		led_switch(1);
		exit(0);
	}

	printf("\n \r Memory Allocated and starting memory is %p\n", ptr);
	printf("\n \r Memory Allocated and ending memory is %p\n", last_ptr);
	led_switch(2);
	return ptr;
}

void free_mem(uint32_t *ptr1)
{
	if(ptr1 != NULL)
	{
		free(ptr1);
		printf("\n \r Memory block cleared for the pointer");
		led_switch(2);
	}
	else
	{
		printf("\n \r Warning: trying to clear free memory");
		led_switch(1);

	}
}
///////////////// To display a Memory block //////////////
uint32_t* display_mem(uint32_t * loc, size_t length)
{
	int j=0;
	printf(" \n \r Data at address %p of ptr \n",loc);
	for (j=0;j<length;j++)
	{
		printf("%X  ",*loc);
		loc++;
	}
	return loc;
}

///////////////// To write to a memory block //////////////
mem_status write_memory(uint32_t * loc, uint16_t value)
{
	mem_status a;
	if (loc <= last_ptr && loc >= ptr)
	{
		a=SUCCESS;
		*loc = value;
		printf("\n \r You wrote Data:%d at Memory Location:%p",value,loc);
		led_switch(2);
		return a;

	}
	else
	{
		a=FAILED;
		led_switch(1);
		return a;

	}
}

///////////////// Using XOR to invert a block /////////////
mem_status invert_block(uint32_t * loc, size_t length)
{
	mem_status a;
	if (loc <= last_ptr && loc >= ptr)
	{
		a=SUCCESS;
		int i=0;
		for(i=0;i<length; i++)
		{
			*(loc +i) ^= 0xFFFFFFFF;
		}
		led_switch(2);
		return a;
	}
	else
	{
		a=FAILED;
		led_switch(1);
		return a;
	}
}


///////////////// To pass the data to Pattern Generator //////////
mem_status write_pattern(uint32_t * loc, size_t length, uint8_t seed)
{
	mem_status a;
	if (loc <= last_ptr && loc >= ptr)
	{
		a=SUCCESS;
		uint32_t *temp1 =loc;
		//	int temp =0;
		//	while (temp < length)
		//	{
		gen_pattern(temp1,length,seed);
		//		temp ++;
		//		temp1++;
		//	}
		led_switch(2);
		return a;
	}
	else
	{
		a=FAILED;
		led_switch(1);
		return a;
	}
}

/////////////////Pattern Generator ///////////////////////////
//void gen_pattern(uint32_t * pattern, size_t length, int8_t seed)
//{
//
//	uint32_t lfsr = 0x1111ACE1;
//	uint32_t bit;
//	for (uint32_t i =0 ; i< length ; i++)
//	{
//		bit  = ((lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5) ) & 1;
//
//		lfsr =  (lfsr >> 1) | (bit << 31);
//		lfsr = (uint32_t)lfsr;
//		*(pattern+i)= lfsr+ (uint32_t)(seed*i*1234);
//		//return pattern;
//	}
//}

uint32_t * verify_pattern(uint32_t * loc, size_t length, int8_t seed)
{
	uint32_t  *temp1 = NULL;
	uint32_t ptr2[length];
	uint32_t *p = loc;
	mem_status_write_pattern_array (ptr2,length,5);
	int i =0;
	int flag1=0;
	//temp2 = ptr2;
	while (i<length)
	{
		if(*loc == *(ptr2+i))
		{
			printf(" \n \r Same");
			//flag1 =0;
		}
		else
		{
			flag1 = 1;
			printf("\n \r Different value");
			//return ptr2;
			temp1 = loc;
			p=loc;

		}
		loc ++;
		//		p++ ;
		i++;
	}

	if ( flag1 ==1 ) return p;
	if ( flag1 ==0) return NULL;
	//	printf("\n \r Memory Freed which was used for verification");
}

//void mem_status_write_pattern_array(uint32_t * loc, size_t length, uint8_t seed)
//{
//	uint32_t *temp1 =loc;
//	gen_pattern(temp1,length,seed);
//
//}

uint32_t * get_address(uint32_t  offset)
{
	uint32_t *temp;
	temp = ptr + offset;
	return (temp);
}
