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


uint32_t  *ptr; // GLobal Pointer to store the starting address of the memory block
uint32_t *last_ptr;  // GLobal Pointer to store the ending address of the memory block
int i;

/*******************************************************************************************************
 * Function Name:uint32_t * allocate_words(size_t length)
 * Description : this function allocates memory of type uint32_t of specified length(nos).
 * @input:Length
 * @Return : pointer to first location of the memory block
 *******************************************************************************************************/

uint32_t * allocate_words(size_t length)
{

	i=4*length;

	ptr= malloc(i);		//Allocate memory

	last_ptr=ptr + length;	//Store the address of the last memory block


	/*check the pointer to see whether the memory block can be allocated or not*/
	if (ptr==NULL)
	{
		printf("\n \r Can't allocate memory\n");
		led_switch(1);
		exit(0);
	}

	printf("\n \r Memory Allocated and starting memory is %p\n", ptr); //Print the starting address of the memory block
	printf("\n \r Memory Allocated and ending memory is %p\n", last_ptr); // Print the ending address of the memory block
	led_switch(2);
	return ptr;
}

/*******************************************************************************************************
 * Function Name:void free_mem(uint32_t *ptr1)
 * Description : this function frees  memory  block pointed by ptr1.
 * @input:pointer to memory block *ptr1
 * @Return :void
 *******************************************************************************************************/
void free_mem(uint32_t *ptr1)
{
	if(ptr1 != NULL)	// Check if null pointer is passed
	{
		free(ptr1);
		printf("\n \r Memory block cleared for the pointer");	// Memory block cleared
		led_switch(2);	//Change the LED color to Green
	}
	else
	{
		printf("\n \r Warning: trying to clear free memory");	// Handle error
		led_switch(1);	//Change the LED color to RED

	}
}

/*******************************************************************************************************
 * Function Name:uint32_t* display_mem(uint32_t * loc, size_t length)
 * Description : This function displays the contents of memory location pointed by loc of specified length
 * @input:pointer to memory block *ptr1 and length
 * @Return :uint32_t type of pointer
 *******************************************************************************************************/
///////////////// To display a Memory block //////////////
uint32_t* display_mem(uint32_t * loc, size_t length)
{
	int j=0;
	printf(" \n \r Data at address %p of ptr \n",loc);
	for (j=0;j<length;j++)
	{
		printf("%X  ",*loc);	//Print he data at the memory location
		loc++;	//Increment the pointer
	}
	return loc;
}
/*******************************************************************************************************
 * Function Name:mem_status write_memory(uint32_t * loc, uint16_t value)
 * Description : This function writes the value to the memory pointed by the passed pointer.
 * @input:pointer to memory block *ptr1 and vlaue to be stored
 * @Return :enum of type mem_status
 *******************************************************************************************************/
///////////////// To write to a memory block //////////////
mem_status write_memory(uint32_t * loc, uint16_t value)
{
	mem_status a;	// Create enum to return
	if (loc <= last_ptr && loc >= ptr)	//Memory bound checking
	{
		a=SUCCESS;
		*loc = value;	//Write data to address pointed by loc
		printf("\n \r You wrote Data:%d at Memory Location:%p",value,loc); // Print the value and address of the location
		led_switch(2);	//Change the LED color to Green
		return a;	//Return Success

	}
	else
	{
		a=FAILED;
		led_switch(1);	//Change the LED color to Red
		return a;	//Return Failed

	}
}


/*******************************************************************************************************
 * Function Name:mem_status invert_block(uint32_t * loc, size_t length)
 * Description : This function inverts the vlaue stored the memory block at location pointed by loc pointer
 * @input:pointer to the memory location and length
 * @Return :enum of type mem_status
 *******************************************************************************************************/
///////////////// Using XOR to invert a block /////////////

mem_status invert_block(uint32_t * loc, size_t length)
{
	mem_status a;
	if (loc <= last_ptr && loc >= ptr)	//memory bound checking
	{
		a=SUCCESS;
		int i=0;
		for(i=0;i<length; i++)
		{
			*(loc +i) ^= 0xFFFFFFFF;	//Invert the contents pointed by location pointer by implementing xor logic
		}
		led_switch(2);	//Switch LED color to Green
		return a;	//Return SUCCESS
	}
	else
	{
		a=FAILED;
		led_switch(1);	//Switch LED color to RED
		return a;	//Return Failure
	}
}


/*******************************************************************************************************
 * Function Name:mem_status write_pattern(uint32_t * loc, size_t length, uint8_t seed)
 * Description : This function writes the generated pattern at location pointed by the pointer
 * @input:pointer to the memory location and length and seed value
 * @Return :enum of type mem_status
 *******************************************************************************************************/

///////////////// To pass the data to Pattern Generator //////////
mem_status write_pattern(uint32_t * loc, size_t length, uint8_t seed)
{
	mem_status a;
	if (loc <= last_ptr && loc >= ptr)	//Memory Bound Checking
	{
		a=SUCCESS;
		uint32_t *temp1 =loc;
		gen_pattern(temp1,length,seed); //Call the pattern generator function
		led_switch(2); //Change the Led to Green
		return a;	//Return Success
	}
	else
	{
		a=FAILED;
		led_switch(1);	//Change the LED color to RED
		return a;	//Return Failed
	}
}

/*******************************************************************************************************
 * Function Name:uint32_t * verify_pattern(uint32_t * loc, size_t length, int8_t seed)
 * Description : This function verifies the generated pattern at location pointed by the pointer
 * @input:pointer to the memory location and length and seed value
 * @Return :pointer of uint32_t type which returns the address of different value
 *******************************************************************************************************/
uint32_t * verify_pattern(uint32_t * loc, size_t length, int8_t seed)
{
	uint32_t  *temp1 = NULL;
	uint32_t ptr2[length];	//Define array to store the pattern
	uint32_t *p = loc;	//store location address to temp pointer
	mem_status_write_pattern_array (ptr2,length,5);	//Write pattern at different location
	int i =0;
	int flag1=0;	//Set Flag to 0
	//temp2 = ptr2;
	while (i<length)
	{
		if(*loc == *(ptr2+i))		//Check if both the values ate equal
		{
			printf(" \n \r Same");
			//flag1 =0;
		}
		else
		{
			flag1 = 1;
			printf("\n \r Different value");	//Check if both the value different
			//return ptr2;
			temp1 = loc;	//Store the location into temporary pointer
			p=loc;

		}
		loc ++;
		//		p++ ;
		i++;
	}

	if ( flag1 ==1 ) return p;	//Return address if different values found
	if ( flag1 ==0) return NULL;	//Return NULL if all values are same.
	//	printf("\n \r Memory Freed which was used for verification");
}

/*******************************************************************************************************
 * Function Name:uint32_t * get_address(uint32_t  offset)
 * Description : This function returns the absolute address wrt input offset.
 * @input:pointer to the memory location.
 * @Return :pointer of uint32_t type which returns the absolute  address of the memory location
 *******************************************************************************************************/

uint32_t * get_address(uint32_t  offset)
{
	uint32_t *temp;
	temp = ptr + offset;	//Calculate the offset address
	return (temp);	//return the absolute address
}
