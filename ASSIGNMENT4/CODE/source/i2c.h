/*
 * i2c.h
 *
 *  Created on: Nov 2, 2019
 *      Author: SURAJ THITE
 */

#ifndef I2C_H_
#define I2C_H_

#include "state_machine.h"
#include "main.h"


extern int16_t temp_val;



void i2c_init(void);
void i2c_write(uint8_t addr, uint8_t reg,uint8_t data);
int16_t i2c_read_temperature(uint8_t dev, uint8_t reg);
void POST_TEST_read_bytes(uint8_t dev, uint8_t reg);
void Init_SysTick(void);
uint8_t check_connection(uint8_t dev, uint8_t reg);
uint16_t CONFIG_REGISTER_VALUE();
uint8_t i2c_dealy1();



#endif /* I2C_H_ */
