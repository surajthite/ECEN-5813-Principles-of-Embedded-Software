/*
 * dma.c
 *
 *  Created on: Dec 1, 2019
 *      Author: SURAJ THITE
 */

#include "dma.h"


dma_transfer_config_t transferConfig;	//Structure to store the DMA configuration


//bool g_Transfer_Done = false;

dma_handle_t g_DMA_Handle;	//Handle for DMA transfer

/*******************************************************************************************************
 * Function Name:void dma_init()
 * Description :This function initializes the DMA on Zero Channel and DMAMUX0 for shot transfer mode
 * @input:  pointer to uint8_t
 * @Return : pointer
 * Reference: DMA Transfer example from SDK
 *******************************************************************************************************/
void dma_init()
{
	//Configure MUX for DMA
	DMAMUX_Init(DMAMUX0);	//Initialize the DMA Multiplexer
	DMAMUX_SetSource(DMAMUX0, DMA_CHANNEL, DMA_SOURCE);	//Set source for and channel for DMA transfer
	DMAMUX_EnableChannel(DMAMUX0, DMA_CHANNEL); //Enable DMA

	//COnfigure DMA for Shot transfer
	DMA_Init(DMA0);	//Initialize the DMA peripheral

	PRINTF("\n \r ************DMA Initialized********** \n \r");

}


/* User callback function for DMA transfer. */
//void DMA_Callback(dma_handle_t *handle, void *param)
//{
//	g_Transfer_Done = true;
//}
/*******************************************************************************************************
 * Function Name:void dma_transfer(uint8_t srcAddr,uint32_t *destAddr , uint8_t no_of_words)
 * Description :This function transfers the data from source to destination passed as arguments.
 * @input:  source address,destination address ,words to transfer.
 * @Return : pointer
 *******************************************************************************************************/
void dma_transfer(uint8_t srcAddr,uint32_t *destAddr , uint8_t no_of_words)
{
	DMA_CreateHandle(&g_DMA_Handle, DMA0, DMA_CHANNEL);	//Create the DMA handle associated with DMA0 and DMA_channel
	DMA_SetCallback(&g_DMA_Handle, DMA_Callback, NULL);	//Set callback function for DMA complete.
	DMA_PrepareTransfer(&transferConfig, srcAddr, 2 , destAddr, 2 , 2*no_of_words, kDMA_MemoryToMemory);	//Prepare transfer
	DMA_SubmitTransfer(&g_DMA_Handle, &transferConfig, kDMA_EnableInterrupt);	//Submit transfer configuration to the DMA handle
	DMA_StartTransfer(&g_DMA_Handle);	//Start DMA Transfer
//	while (g_Transfer_Done != true)
//	{
//
//	}
	PRINTF("\n \r ************DMA TRANSFER SUCCESSFUL**************");
}

