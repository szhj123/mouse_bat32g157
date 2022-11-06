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
#include "ssi_api_if.h"
#include <stdio.h>

/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

extern uint8_t iistxbuff[(BUFF_NUM +1) * SINGLE_BUFF_SIZE], iisrxbuff[256],i2semptybuff[EP3_MAX_PKT_SIZE];

extern uint8_t read_first_flag, play_flag;
extern uint32_t read_cnt, play_cnt;
extern uint32_t usb_read_pos, iis_send_pos, buff_size;

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
uint32_t cnt;
/***********************************************************************************************************************
* Function Name: SSIDMATX_interrupt
* @brief  SSIE DMA TX interrupt service routine
* @param  None
* @return None
***********************************************************************************************************************/
void SSIDMATX_interrupt(void)
{
//	volatile uint32_t i;
//	for(i = 0; i < 99; i++)
//	{
//		__NOP();
//	}
//	if(SSI_FLAG_SET == SSI_GetFlagTxUnderFlow(SSI_CH0))
//	{
//		SSI_ClearFlagTxUnderFlow(SSI_CH0);
//		printf("TX UF at: %d", cnt);
//	}
//	if(SSI_FLAG_SET == SSI_GetFlagTxOverFlow(SSI_CH0))
//	{
//		SSI_ClearFlagTxOverFlow(SSI_CH0);
//		printf("TX OF at: %d", cnt);
//	}
//	cnt++;
	
	DMAVEC->CTRL[IISTX_DMA_CHANNEL].DMSAR = (uint32_t)((uint16_t*)&iistxbuff[0]);
	DMAVEC->CTRL[IISTX_DMA_CHANNEL].DMACT = buff_size /(2*2);

//	SSI_Stop(SSI_CH0);
	DMA_Enable(DMA_VECTOR_SSI_TX);
//	SSI_Start(SSI_CH0);

	
/*	
	if(play_flag == 1)
	{
		play_cnt++;
		//if(play_cnt < read_cnt)
		{
			DMAVEC->CTRL[IISTX_DMA_CHANNEL].DMSAR = (uint32_t)((uint16_t*)&iistxbuff[play_cnt%BUFF_NUM][0]);
			
			DMAVEC->CTRL[IISTX_DMA_CHANNEL].DMACT =  SINGLE_BUFF_SIZE/(8*2); //sizeof(iistxbuff)/(8*2*2);
			DMA_Enable(DMA_VECTOR_SSI_TX);
		}
	}else
	{
		//laidi send empty data to I2S to avoid underflow
			DMAVEC->CTRL[IISTX_DMA_CHANNEL].DMSAR = (uint32_t)((uint16_t*)&i2semptybuff[0]);
			
			DMAVEC->CTRL[IISTX_DMA_CHANNEL].DMACT =  sizeof(i2semptybuff)/(8*2); 
			DMA_Enable(DMA_VECTOR_SSI_TX);
	}
	*/
	
	 INTC_ClearPendingIRQ(SSIDMATX_IRQn);	/* Clear SSIE DMA TX interrupt pending flag */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
