/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    ssie_user.c
* @brief   This file implements device driver for SSIE module.
* @version 1.0.0
* @date    2019/12/24
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "userdefine.h"
#include "BAT32G157.h"
#include "ssie.h"
#include "dma.h"

#include "spi_flash.h"
#include "usbd_audio.h"

/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
extern uint8_t iistxbuff[2][512],iisrxbuff[512];

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
void IRQ18_Handler(void) __attribute__((alias("SSIDMART_interrupt")));
void IRQ19_Handler(void) __attribute__((alias("SSIDMARX_interrupt")));
void IRQ20_Handler(void) __attribute__((alias("SSIDMATX_interrupt")));
void IRQ21_Handler(void) __attribute__((alias("SSIINTREQ_interrupt")));

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
volatile uint32_t iisdmacount;

/***********************************************************************************************************************
* Function Name: SSIINTREQ_interrupt
* @brief  SSIE REQ interrupt service routine
* @param  None
* @return None
***********************************************************************************************************************/
void SSIINTREQ_interrupt(void)
{
    INTC_ClearPendingIRQ(SSIINTREQ_IRQn);	/* Clear SSIE REQ interrupt pending flag */
    
}
/***********************************************************************************************************************
* Function Name: SSIDMART_interrupt
* @brief  SSIE DMA RT interrupt service routine
* @param  None
* @return None
***********************************************************************************************************************/
void SSIDMART_interrupt(void)
{
    INTC_ClearPendingIRQ(SSIDMART_IRQn);	/* Clear SSIE DMA RT interrupt pending flag */
    
}
/***********************************************************************************************************************
* Function Name: SSIDMARX_interrupt
* @brief  SSIE DMA RX interrupt service routine
* @param  None
* @return None
***********************************************************************************************************************/
void SSIDMARX_interrupt(void)
{
    INTC_ClearPendingIRQ(SSIDMARX_IRQn);	/* Clear SSIE DMA RX interrupt pending flag */
    
}
/***********************************************************************************************************************
* Function Name: SSIDMATX_interrupt
* @brief  SSIE DMA TX interrupt service routine
* @param  None
* @return None
***********************************************************************************************************************/
void SSIDMATX_interrupt(void)
{
	uint16_t ssi_dummy;
	
  INTC_ClearPendingIRQ(SSIDMATX_IRQn);	/* Clear SSIE DMA TX interrupt pending flag */
	
	iisdmacount++;
//	if(++iisdmacount>=15*1024)
//	{
//		iisdmacount = 0;
//		SPI_CS_HIGH();
//		INTC_DisableIRQ(SSIDMATX_IRQn);
//	}
//	else
//	{
		if(iisdmacount&0x01)
		{
			DMAVEC->CTRL[IISTX_DMA_CHANNEL].DMSAR = (uint32_t)((uint16_t*)&iistxbuff[1][0]);
//			DMAVEC->CTRL[SPI_DMA_CHANNEL].DMDAR = (uint32_t)((uint16_t*)&iistxbuff[0][0]);
		
		}
		else
		{
			DMAVEC->CTRL[IISTX_DMA_CHANNEL].DMSAR = (uint32_t)((uint16_t*)&iistxbuff[0][0]);
//			DMAVEC->CTRL[SPI_DMA_CHANNEL].DMDAR = (uint32_t)((uint16_t*)&iistxbuff[1][0]);
		
		}
		DMAVEC->CTRL[IISTX_DMA_CHANNEL].DMACT = EP3_MAX_PKT_SIZE/(8*2);//sizeof(iistxbuff)/(8*2*2);
		
		DMA_Enable(DMA_VECTOR_SSI_TX);
		
//		DMAVEC->CTRL[SPI_DMA_CHANNEL].DMACT = sizeof(iistxbuff)/(2*2);
		
//		DMA_Enable(DMA_VECTOR_SPIHS1);
//		ssi_dummy = SPIHS1->SDRI1;
//	}
	
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
