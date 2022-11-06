/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    lcdb_user.c
* @brief   This file implements device driver for LCD module.
* @version 1.0.0
* @date    2020/10/12
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "BAT32G157.h"
#include "dma.h"
#include "lcdb.h"
#include "lcd.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
void IRQ15_Handler(void) __attribute__((alias("lcdb_interrupt")));

/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
//volatile uint32_t int_lcdb_flag;
volatile uint32_t lcdbint_cnt;

/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: lcdb_interrupt
* @brief  LCDB interrupt service routine
* @param  None
* @return None
***********************************************************************************************************************/
void lcdb_interrupt(void)
{
    INTC_ClearPendingIRQ(LCDB_IRQn);     /* clear LCDB interrupt flag */
    /* Start user code. Do not edit comment generated here */
//	int_lcdb_flag = 1;
	if(++lcdbint_cnt==1)
	{
		DMAVEC->CTRL[DMA_CTRL_DATA_LCDB].DMACT = (LCD_W*LCD_H)/2-1;
		DMA_Enable(DMA_VECTOR_LCDB);
		LCDB->LBDATA = 0xffff;
	}
	else
	{
		LCD_CS_HIGH();
		
		LCDB_Stop();
	}
	
    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
