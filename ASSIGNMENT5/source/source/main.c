
 
/**
 * @file    pespro5_1.1.c
 * @brief   Application entry point.
 */

#include "main.h"
/*
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
*/

int main(void) {

  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
  	/* Init FSL debug console. */
    BOARD_InitDebugConsole();

    uint8_t myrxdata;
    uint8_t mytxdata;
    while(1) {

   // myrxdata= check_and_receive();   //here error coming please check
   // mytxdata= check_and_transmit();
        __asm volatile ("nop");
    }
    return 0 ;
}
