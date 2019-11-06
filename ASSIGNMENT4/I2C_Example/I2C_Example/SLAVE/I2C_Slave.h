/*
 * I2C_Master.h
 *
 *  Created on: Jan 29, 2014
 *      Author: B47334
 */

#ifndef I2C_MASTER_H_
#define I2C_MASTER_H_

#include "derivative.h"
#include "typedef.h"


#define SLAVE_ADDRESS 0x75

#define BUFFER_SIZE	10

#define WRITE	0x00
#define	READ	0x01


extern u8 byte_counter;
extern u8 tx_buffer[];


void I2C_Slave_Init(void);


#endif /* I2C_MASTER_H_ */
