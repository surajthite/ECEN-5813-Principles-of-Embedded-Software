
#ifndef MAIN_H_
#define MAIN_H_

#include <polling.h>
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "circbuff.h"
#include "polling.h"


/* interrupt vertor redefined in isr.h to point to the appropriate interrupt service routine. */
extern void uart_irqhandler(void);
#undef VECTOR_028
#define VECTOR_028 uart0_isr



#endif
