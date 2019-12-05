/*
 * wave.h
 *
 *  Created on: Dec 1, 2019
 *      Author: SURAJ THITE
 */

#ifndef WAVE_H_
#define WAVE_H_

#include <math.h>
#include <stdint.h>

#define NUM_OF_SAMPLES 50
#define INV_3_FACTORIAL (1/6)
#define INV_5_FACTORIAL (1/120)
#define INV_7_FACTORIAL (1/5040)
#define PI 3.14159265358979323846


void sine_lookup_generate();

uint16_t get_next_val();


#endif /* WAVE_H_ */
