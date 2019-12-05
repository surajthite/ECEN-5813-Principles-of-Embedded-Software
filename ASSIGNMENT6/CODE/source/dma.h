/*
 * dma.h
 *
 *  Created on: Dec 1, 2019
 *      Author: SURAJ THITE
 */

#ifndef DMA_H_
#define DMA_H_

#include "fsl_dma.h"
#include "fsl_dmamux.h"
#include "tasks.h"
#include "circularbuff.h"
#include "fsl_debug_console.h"

//void dma_transfer(uint8_t *srcAddr,uint32_t *destAddr , uint8_t no_of_words);
void dma_transfer(uint8_t srcAddr,uint32_t *destAddr , uint8_t no_of_words);
//void DMA_Callback(dma_handle_t *handle, void *param);
void dma_init();

#define BUFF_LENGTH 4
#define DMA_CHANNEL 0
#define DMA_SOURCE 63

#endif /* DMA_H_ */
