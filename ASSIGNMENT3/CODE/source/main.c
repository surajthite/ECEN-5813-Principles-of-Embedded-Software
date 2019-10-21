
#include "main.h"
#include "memory.h"
#include "RGBled.h"

int main(void) {

	/* Init board hardware. */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();
	/* Init FSL debug console. */
	BOARD_InitDebugConsole();
	//Code Start
	uint32_t  *ptr1;
	uint32_t  *ptr2 ;
	size_t length = 4;

	RGB_init();
	RGB_OFF();






	led_switch(0);
	ptr1 =  allocate_words(length);


	led_switch(0);
	mem_status r1;
	r1 = write_pattern(ptr1,4,5);
	if (r1==SUCCESS)  printf(" \n \r RESPONSE : SUCCESS");
	else printf("\n \r RESPONSE : FAILED");



	display_mem(ptr1,length);


	led_switch(0);
	ptr2=NULL;
	ptr2 = verify_pattern(ptr1,4,5);
	if(ptr2 != NULL)
	{
		printf("\n \r Different value found at location %p",ptr2);
		led_switch(1);
	}
	else
		{
		printf("\n \r Passed!");
		led_switch(2);
		}


	led_switch(0);
	mem_status res1;
	res1 = write_memory(ptr1+1, 0xFFEE);
	if (res1==SUCCESS)  printf(" \n \r RESPONSE : SUCCESS");
	else printf("\n \r RESPONSE : FAILED");



	display_mem(ptr1,length);


	//	ptr2 =  allocate_words(length);
	//	mem_status_write_pattern(ptr2,length,5);
	led_switch(0);
	ptr2=NULL;
	ptr2 = verify_pattern(ptr1,4,5);
	if(ptr2 != NULL)
	{
		printf("\n \r Different value found at location %p",ptr2);
		led_switch(1);
	}
	else
	{
		printf("\n \r Passed!");
		led_switch(2);
	}

	display_mem(ptr1,length);

	led_switch(0);
	mem_status r2;
	r2=write_pattern(ptr1,length,5);
	if (r2==SUCCESS)  printf(" \n \r RESPONSE : SUCCESS");
	else printf("\n \r RESPONSE : FAILED");


	display_mem(ptr1,length);


	led_switch(0);
	ptr2=NULL;
	ptr2 = verify_pattern(ptr1,4,5);
	if(ptr2 != NULL)
	{
		printf("\n \r Different value found at location %p",ptr2);
		led_switch(1);
	}
	else
	{
		printf("\n \r Passed!");
		led_switch(2);
	}

	led_switch(0);
	mem_status res2;
	res2 = invert_block(ptr1+0,1);
	if (res2==SUCCESS)  printf(" \n \r RESPONSE : SUCCESS");
	else printf("\n \r RESPONSE : FAILED");


	display_mem(ptr1,length);

	led_switch(0);
	ptr2=NULL;
	ptr2 = verify_pattern(ptr1,4,5);
	if(ptr2 != NULL)
	{
		printf("\n \r Different value found at location %p",ptr2);
		led_switch(1);
	}
	else
	{
	printf("\n \r Passed!");
	led_switch(2);

	}


	led_switch(0);
	mem_status res3;
	res3 = invert_block(ptr1+0,1);
	if (res3==SUCCESS)  printf(" \n \r RESPONSE : SUCCESS");
	else printf("\n \r RESPONSE : FAILED");


	display_mem(ptr1,length);


	led_switch(0);
	ptr2=NULL;
	ptr2 = verify_pattern(ptr1,4,5);
	if(ptr2 != NULL)
	{
		printf("\n \r Different value found at location %p",ptr2);
		led_switch(1);
	}
	else
	{
		printf("\n \r Passed!");
		led_switch(2);

	}




	free_mem(ptr1);

	display_mem(ptr1,length);

	return 0;
}


int delay(int time_ms)
{
	volatile uint32_t i = 0;
	for (i = 0; i < 2400*time_ms; ++i)
	{
		__asm("NOP"); /* No operation */
	}
	return i;
}
