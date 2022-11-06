/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    ssie.c
* @brief   This file implements device driver for SSIE module.
* @version 1.0.0  
* @date    2020/10/16
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "userdefine.h"
#include "BAT32G157.h"
#include "ssie.h"

/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/

/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: SSIE_Init
* @brief  This function initializes the SSIE module.
* @param  None
* @return None
***********************************************************************************************************************/
void SSIE_Init(SSIE_Typedef* pSsie)
{
	
    CGC->PER2 |= CGC_PER2_SSIEN_Msk;              /* enables input clock supply */
    
	SSI->SSICR &= ~SSI_SSICR_CKDV_Msk; /* clock divider */
	SSI->SSICR |= (pSsie->iise_clock_divider)<<SSI_SSICR_CKDV_Pos;
	
	SSI->SSICR &= ~SSI_SSICR_SWL_Msk; /* system width */
	SSI->SSICR |= (pSsie->iise_systemwidth)<<SSI_SSICR_SWL_Pos;
	
	SSI->SSICR &= ~SSI_SSICR_DWL_Msk; /* data width */
	SSI->SSICR |= (pSsie->iise_datawidth)<<SSI_SSICR_DWL_Pos;
	
	SSI->SSICR &= ~SSI_SSICR_LRCKP_Msk; /* LRCKP */
	SSI->SSICR &= ~SSI_SSICR_BCKP_Msk; /* BCKP */
	
	SSI->SSICR &= ~SSI_SSICR_PDTA_Msk; /* left align */
	
	if(pSsie->iise_alignmentformat == SSIE_LEFT_ALIGN)
	{
		
		SSI->SSICR &= ~SSI_SSICR_SDTA_Msk;/* Data->Full bit */
	}
	else
	{
		
		SSI->SSICR |= SSI_SSICR_SDTA_Msk;/* Full bit->Data */
	}
	
	if(pSsie->iise_dataformat == SSIE_FORMAT_I2S)
	{
		SSI->SSICR &= ~SSI_SSICR_DEL_Msk;/* iis format */
	}
	else
	{
		SSI->SSICR |= SSI_SSICR_DEL_Msk;	
	}
	
	SSI->SSITDMR &= ~SSI_SSITDMR_OMOD_Msk;
	if(pSsie->iise_channel == SSIE_MONO)/* mono channel */
	{
		SSI->SSITDMR |= 2<<SSI_SSITDMR_OMOD_Pos;
	}
	
	SSI->SSICR &= ~SSI_SSICR_CKS_Msk; /* Select audio clock input */
	
	if(pSsie->iise_mode == SSIE_MODE_MASTER)/* iis mode */
	{
//		SSI->SSICR |= SSI_SSICR_CKS_Msk; /* Select GTIOC1A input */
		SSI->SSICR |= SSI_SSICR_MST_Msk; /* Master mode */
		SSI->SSIFCR |= SSI_SSIFCR_AUCKE_Msk;/* Enable audio clock output */
	}
	else
	{
//		SSI->SSICR &= ~SSI_SSICR_CKS_Msk; /* Select audio clock input */
		SSI->SSICR &= ~SSI_SSICR_MST_Msk; /* Slaver mode */
		SSI->SSIFCR &= ~SSI_SSIFCR_AUCKE_Msk;/* Disable audio clock output */
	}
	
	SSI->SSISCR &= ~SSI_SSISCR_TDES_Msk; 	
	SSI->SSISCR |= (pSsie->iise_tx_fifo_size-1)<<SSI_SSISCR_TDES_Pos; 	/* set TX FIFO */
	SSI->SSISCR &= ~SSI_SSISCR_RDFS_Msk; 	
	SSI->SSISCR |= (pSsie->iise_rx_fifo_size-1)<<SSI_SSISCR_RDFS_Pos; 	/* set RX FIFO */
	
	SSI->SSIFCR |= SSI_SSIFCR_TFRST_Msk; /* Reset TX FIFO */
	SSI->SSIFCR |= SSI_SSIFCR_RFRST_Msk; /* Reset RX FIFO */
	SSI->SSIFCR &= ~SSI_SSIFCR_TFRST_Msk; /* Clear Reset TX FIFO */
	SSI->SSIFCR &= ~SSI_SSIFCR_RFRST_Msk; /* Clear Reset RX FIFO */
	
	while(SSI->SSIFCR & SSI_SSIFCR_TFRST_Msk);
	while(SSI->SSIFCR & SSI_SSIFCR_RFRST_Msk);

	SSI->SSICR |= SSI_SSICR_REN_Msk|SSI_SSICR_TEN_Msk; /* enable TX & RX */
	
    /* Set SSIE pin */
	PORT->PMCD &= ~0xF004;/* PD15 PD14 PD13 PD12 PD2 SSI*/
	PORT->PMD &= ~0xE000;/* PD15 PD14 PD13 SSI*/
	PORT->PMD |= 0x1004;/* PD12 PD2 SSI*/
	PORT->PD &= ~0xF004;/* PD15 PD14 PD13 PD12 PD2 SSI*/
	
}

/***********************************************************************************************************************
* Function Name: SSIE_Start
* @brief  This function stops SSIE module operation.
* @param  None
* @return None
***********************************************************************************************************************/
void SSIE_Start(void)
{
	INTC_ClearPendingIRQ(SSIINTREQ_IRQn);	/* Clear SSIE interrupt pending flag */
    INTC_EnableIRQ(SSIINTREQ_IRQn);         /* Enable SSIE interrupt flag */     
	
}
/***********************************************************************************************************************
* Function Name: SSIE_Stop
* @brief  This function sets SSIE stop condition flag.
* @param  None
* @return None
***********************************************************************************************************************/
void SSIE_Stop(void)
{
    INTC_ClearPendingIRQ(SSIINTREQ_IRQn);	/* Clear SSIE interrupt pending flag */
    INTC_DisableIRQ(SSIINTREQ_IRQn);         /* Disable SSIE interrupt flag */     
	
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
