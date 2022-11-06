/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    lcdb.c
* @brief   This file implements device driver for LCD module.
* @version 1.0.0
* @date    2020/10/12
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "userdefine.h"
#include "BAT32G157.h"
#include "lcdb.h"
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
* Function Name: LCDB_Init
* @brief  This function initializes the LCDB module.
* @param  pinMsk - 
* @return None
***********************************************************************************************************************/
void LCDB_Init(LCDB_Typedef* pLcdb)
{
    CGC->PER1 |= CGC_PER1_LCDBEN_Msk;	/*enable lcdb clock*/
	
	if(LCDB_MODE_TYPE_8080 == pLcdb->mode)
	{
		LCDB->LBCTL &= ~LCDB_LBCTL_IMD_Msk;
	}
	else
	{
		LCDB->LBCTL |= LCDB_LBCTL_IMD_Msk;
		if(LCDB_MODE_6800_CNTL_ENABLE_HIGH == pLcdb->mode_6800_E_level)
		{
			LCDB->LBCTL &= ~LCDB_LBCTL_EL_Msk;
		}
		else
		{
			LCDB->LBCTL |= LCDB_LBCTL_EL_Msk;
		}
	}
	
	LCDB->LBCTL &= ~LCDB_LBCTL_LBC_Msk;//lcdb clock divider
	LCDB->LBCTL |= (pLcdb->clock_div)<<LCDB_LBCTL_LBC_Pos;
	
	LCDB->LBCYC = pLcdb->cycle;
	
	LCDB->LBWST = pLcdb->wait_cycle;
	
    /* Set LCDB pin */
	PORT->PC &= ~0xF3C0;//PC6-9 PC12-15
	PORT->PC |= 0x0C00;//PC10-11
	
    PORT->PMCC &= ~(0x3FF<<6);//PC6-15 digital function
    PORT->PMC &= ~0x0C00;//PC10-11 output mode
	PORT->PMC |= 0xF3C0;//PC6-9 PC12-15 input mode
	
    INTC_DisableIRQ(LCDB_IRQn);      /* disable LCDB interrupt */
    INTC_ClearPendingIRQ(LCDB_IRQn); /* clear LCDB interrupt flag */
	
}

/***********************************************************************************************************************
* Function Name: LCDB_Start
* @brief  This function clears LCDB interrupt flag and enables interrupt.
* @param  None
* @return None
***********************************************************************************************************************/
void LCDB_Start(void)
{
    INTC_ClearPendingIRQ(LCDB_IRQn); /* clear LCDB interrupt flag */
    INTC_EnableIRQ(LCDB_IRQn);/* enable LCDB interrupt */
}
/***********************************************************************************************************************
* Function Name: LCDB_Stop
* @brief  This function disables LCDB interrupt and clears interrupt flag.
* @param  None
* @return None
***********************************************************************************************************************/
void LCDB_Stop(void)
{
    INTC_DisableIRQ(LCDB_IRQn);      /* disable LCDB interrupt */
    INTC_ClearPendingIRQ(LCDB_IRQn); /* clear LCDB interrupt flag */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
