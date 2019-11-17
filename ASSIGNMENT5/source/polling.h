#ifndef POLLING_H_
#define POLLING_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "main.h"
#include "circbuff.h"



#define POLLING_MODE 1
#define INTERRUPT_MODE 2

#define UART_MODE 1    // to select among two modes


uint8_t rx_datarx();
uint8_t check_rx_ready();
uint8_t check_and_transmit();
uint8_t trans_datatx();
uint8_t check_trans_ready();
void uart_irqhandler(void);
uint8_t intr_check_and_transmit();
uint8_t intr_check_and_receive();


#endif
