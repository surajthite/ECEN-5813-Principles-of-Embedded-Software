/*
 * main.c
 *
 *  Created on: Sep 28, 2019
 *      Author:SURAJ THITE , ATHARV DESAI
 */
/*******************************************************************************
 * Include Files
 ******************************************************************************/


#include "fsl_rtc.h"
#include "board.h"
#include "fsl_debug_console.h"
#include "fsl_gpio.h"

#include "clock_config.h"
#include "pin_mux.h"
#include "RGBled.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
//#define BOARD_LED_BLUE_GPIO BLUE_LED_PORT
//#define BOARD_LED_BLUE_GPIO_PIN BLUE_LED_PIN

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief delay a while.
 */
int delay(int x);
void RTC_get();
void RTC_init();




/*******************************************************************************
 * Variables
 ******************************************************************************/
unsigned int time[]= {3000,1000,2000,600,1000,400,1000,200,500,100,500,100,500,100,1000,200,1000,400,2000,600};

rtc_datetime_t date;
rtc_config_t rtcConfig;

/*******************************************************************************
 * Code
 ******************************************************************************/

/*******************************************************************************/
/* Function name: delay
 * Parameters: time in mili seconds
 * Return : return the no of counts for the delay generated.
 * Description: Function to create delays.
 * no of cycles required for for loop = 1/(24Mhz)*10 = 2400 cycles.
/*******************************************************************************/
int delay(int time_ms)
{
	volatile uint32_t i = 0;
	for (i = 0; i < 2400*time_ms; ++i)
	{
		__asm("NOP"); /* No operation */
	}
	return i;
}


/*!
 * @brief Main function
 */

/*******************************************************************************/
/* Function name: main
 * Parameters: void
 * Return : return
 * Description: Main loop . */
/*******************************************************************************/
int main(void)
{
	/* Board pin, clock, debug console init */
	BOARD_InitPins();
	BOARD_BootClockRUN();
	BOARD_InitDebugConsole();
	RTC_init();
	RGB_init();
	int time_last_event;
	/* Init output LED GPIO. */
	// GPIO_PinInit(BOARD_LED_BLUE_GPIO,BOARD_LED_BLUE_GPIO_PIN, &led_blue_config);

	unsigned int i = 0;
#ifdef fb_run			//TO be executed for RUN = fb_run flag set.
	for ( i=0;i<20;i++)
	{
		if ((i)%2==0)	//Check status for ON condition
		{
			led_switch(i/6);	//Switch to led state according to the data array
			delay(time[i]);		//Delay according to the current lookup table.
		}
		else
		{
			RGB_OFF();	//Switch LED off
			delay(time[i]);	//Delay according to the current lookup table.
		}

	}
#endif

#ifdef fb_debug		//TO be executed for RUN = fb_debug flag set.
	for ( i=0;i<20;i++)
	{
		if ((i)%2==0)	//Check status for ON condition
		{
			led_switch(i/6);
			status_print_on(i/6);	//Switch to led state according to the data array
			time_last_event=delay(time[i]);	//Return value for no of loops executed for previous delay
			PRINTF("%d  ",time_last_event);	//Print no of cycles executed for previous state.
			RTC_get();	//Print RTC values on the Terminal for the real time date and time from the RTC.

		}
		else
		{
			status_print_0ff();//Switch to led state according to the data array
			time_last_event= delay(time[i]);//Return value for no of loops executed for previous delay
			PRINTF("%d  ",time_last_event);	//Print no of cycles executed for previous state.
			RTC_get();	//Print RTC values on the Terminal for the real time date and time from the RTC.

		}

	}
#endif

#ifdef pc_run	//TO be executed for RUN = fb_debug flag set.
	int main (void)
	{
	    int i=0;

	for ( i=0;i<20;i++)
	    {
	    	if ((i)%2==0)	//Check for ON condition
	    	{

	    		status_print_on(i/6);	// Print the on status for the current state

	    		delay(time[i]*1000);	//Delay according to the current state.
	    	}
	    	else
	    	{

	    		status_print_0ff();	//OFF State

	    		delay(time[i]*1000);	//Delay according to the current state
	    	}

	    }

	return 0;
	}
#endif

#ifdef pc_debug
	int main (void)
	{
	    int i=0;
	    int time_last_event;
	for ( i=0;i<20;i++)
	    {
	    	if ((i)%2==0)
	    	{

	    		status_print_on(i/6);
	    		time_last_event=delay(time[i]*1000);
	    		printf("%d",time_last_event);
	    	}
	    	else
	    	{

	    		status_print_0ff();
	    		time_last_event= delay(time[i]*1000);
	    		printf("%d",time_last_event);
	    	}

	    }

	return 0;
	}
#endif
}

/*******************************************************************************/
/* Function name: RTC_init
 * Parameters: void
 * Return : void
 * Description: Function to initialize the RTC  and set current date/time. */
/*******************************************************************************/
void RTC_init()
{
	RTC_GetDefaultConfig(&rtcConfig);	//Default config for RTC
	RTC_Init(RTC, &rtcConfig);	//Initialize the RTC

	CLOCK_EnableClock(kCLOCK_Rtc0);	//Enable CLock
	CLOCK_SetRtcClkOutClock(kCLOCK_Rtc0);	//Set Clock
	date.year = 2019U;
	date.month = 10U;	//Initialize
	date.day = 30U;
	date.hour = 14U;
	date.minute = 0;
	date.second = 0;
	RTC_SetDatetime(RTC, &date);
	RTC_StartTimer(RTC);


}
/*******************************************************************************/
/* Function name: RTC_get
 * Parameters: void
 * Return : void
 * Description: This function prints the current date and time from RTC. */
/*******************************************************************************/

void RTC_get()
{
	RTC_GetDatetime(RTC, &date);
	PRINTF("Current datetime: %d-%d-%d %d:%d:%d\r\n", date.year, date.month, date.day, date.hour,date.minute, date.second);

}

