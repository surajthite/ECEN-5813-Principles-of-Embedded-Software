/*
 * adc_dac.h
 *
 *  Created on: Dec 1, 2019
 *      Author: SURAJ THITE
 */

#ifndef ADC_DAC_H_
#define ADC_DAC_H_

#include "board.h"
#include "fsl_dac.h"
#include "fsl_adc16.h"

#include "pin_mux.h"
#include "clock_config.h"

void initialize_dac();

void initialize_adc();

void dac_write(uint16_t val);

uint32_t adc_read();
#endif /* ADC_DAC_H_ */
