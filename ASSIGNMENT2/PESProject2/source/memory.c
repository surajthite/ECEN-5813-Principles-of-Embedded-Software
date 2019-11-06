/*
 * memory.c
 *
 *  Created on: Oct 20, 2019
 *      Author: SURAJ THITE
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint32_t  *ptr;
uint32_t *last_ptr;
int max_word,i;

void main ()
{
	uint32_t  *ptr1;
	size_t length =2;
	ptr1 =  allocate_words(length);
}

uint32_t * allocate_words(size_t length)
{
	printf("Enter number of 32 bit words\n");
	scanf ("%d", &max_word);
	i=4*max_word;
	ptr= malloc(i);

	last_ptr=ptr + max_word;

	/*check the pointer to see whether the memory block can be allocated or not*/
	if (ptr==NULL)
	{
	printf("\nCan't allocate memory\n");
	exit(0);
	}
	printf("\n Memory Allocated and starting memory is %p\n", ptr);
	return ptr;
}
