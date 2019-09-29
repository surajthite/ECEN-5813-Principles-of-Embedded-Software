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
void delay(int x);

/*******************************************************************************
 * Variables
 ******************************************************************************/
//unsigned int time[]= {3000,1000,2000,600,1000,400,1000,200,500,100,500,100,500,100,1000,200,1000,400,2000,600};

unsigned int time[]= {3000};

/*******************************************************************************
 * Code
 ******************************************************************************/
void delay(int x)
{
    volatile uint32_t i = 0;
    for (i = 0; i < 8000000*x; ++i)
    {
        __asm("NOP"); /* delay */
    }
}


/*!
 * @brief Main function
 */
int main(void)
{
    /* Define the init structure for the output LED pin*/
//    gpio_pin_config_t led_blue_config = {
//        kGPIO_DigitalOutput, 0,
//    };
//    gpio_pin_config_t led_red_config = {
//        kGPIO_DigitalOutput, 0,
//    };
//    gpio_pin_config_t led_green_config = {
//        kGPIO_DigitalOutput, 0,
//    };
	RGB_init();

    /* Board pin, clock, debug console init */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    /* Init output LED GPIO. */
   // GPIO_PinInit(BOARD_LED_BLUE_GPIO,BOARD_LED_BLUE_GPIO_PIN, &led_blue_config);

    //unsigned int i = 0;
//    for ( i=0;i<20;i++)
//    {
//    	if ((i)%2==0)
//    	{
//    		GPIO_SetPinsOutput(BOARD_LED_GPIO, 1u << BOARD_LED_GPIO_PIN);
//    		delay(i);
//    	}
//    	else
//    	{
//    		GPIO_ClearPinsOutput(BOARD_LED_GPIO, 1u << BOARD_LED_GPIO_PIN);
//    		delay(i);
//    	}
    int i=1;
    while (1)
    {
        delay(1);
        led_switch(i);
        i=i+1;
       if(i==4)
       {
    	   i=1;
       }

    }
}
