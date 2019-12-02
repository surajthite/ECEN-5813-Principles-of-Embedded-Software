/*
 * dma.c
 *
 *  Created on: Dec 1, 2019
 *      Author: SURAJ THITE
 */

#include "dma.h"

extern cbuff *dsp;
extern cbuff *adc;

dma_transfer_config_t transferConfig;

#define BUFF_LENGTH 4
#define DMA_CHANNEL 0
#define DMA_SOURCE 63

volatile bool g_Transfer_Done = false;

dma_handle_t g_DMA_Handle;

void dma_init()
{
	//Configure MUX for DMA
	DMAMUX_Init(DMAMUX0);
	DMAMUX_SetSource(DMAMUX0, DMA_CHANNEL, DMA_SOURCE);
	DMAMUX_EnableChannel(DMAMUX0, DMA_CHANNEL);

	//COnfigure DMA for Shot transfer
	DMA_Init(DMA0);

	PRINTF("\n \r ************DMA Initialized********** \n \r");

}


/* User callback function for DMA transfer. */
void DMA_Callback(dma_handle_t *handle, void *param)
{
	g_Transfer_Done = true;
}

void dma_transfer(uint32_t *srcAddr,uint32_t *destAddr , uint8_t no_of_words)
{
	DMA_CreateHandle(&g_DMA_Handle, DMA0, DMA_CHANNEL);
	DMA_SetCallback(&g_DMA_Handle, DMA_Callback, NULL);
	DMA_PrepareTransfer(&transferConfig, srcAddr, sizeof(srcAddr[0]), destAddr, sizeof(destAddr[0]), sizeof(srcAddr)*no_of_words, kDMA_MemoryToMemory);
	DMA_SubmitTransfer(&g_DMA_Handle, &transferConfig, kDMA_EnableInterrupt);
	DMA_StartTransfer(&g_DMA_Handle);
	while (g_Transfer_Done != true)
	{

	}
	PRINTF("\n \r ************DMA TRANSFER SUCCESSFUL**************");
}

