/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    key.c
* @brief   This file implements device driver for KEY module.
* @version 1.0.0
* @date    2020/10/24
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "userdefine.h"
#include "BAT32G157.h"
#include "key.h"
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
* Function Name: KEY_Init
* @brief  This function initializes the key return module.
* @param  pinMsk - select the active key input pins
* @return None
* @pin    PC06/KR0,PC07/KR1,PC12/KR2,PC13/KR3,PC14/KR4,PC15/KR5,PC08/KR6,PC09/KR7
***********************************************************************************************************************/
void KEY_Init(uint8_t pinMsk)
{
    volatile uint8_t w_count;
    /* Set KRn pin */
	  
	  if(pinMsk<=1)
		{
			PORT->PMCC &= ~(pinMsk<<6);
      PORT->PUC |= (pinMsk<<6);
      PORT->PMC |= (pinMsk<<6);
		}else if((pinMsk>1)&&(pinMsk<=5))
		{
			PORT->PMCC &= ~(pinMsk<<10);
      PORT->PUC |= (pinMsk<<10);
      PORT->PMC |= (pinMsk<<10);
    }else if((pinMsk>5)&&(pinMsk<=7))
		{
			PORT->PMCC &= ~(pinMsk<<2);
      PORT->PUC |= (pinMsk<<2);
      PORT->PMC |= (pinMsk<<2);
    }		
    INTC_DisableIRQ(KEY_IRQn);      /* disable INTKR interrupt */
    INTC_ClearPendingIRQ(KEY_IRQn); /* clear INTKR interrupt flag */
	
    KEY->KRM |= pinMsk;
	
    /* Change the waiting time according to the system  */
    for (w_count = 0U; w_count <= KEY_WAITTIME; w_count++)
    {   
        __NOP();
    }
}
/***********************************************************************************************************************
* Function Name: KEY_Start
* @brief  This function clears INTKR interrupt flag and enables interrupt.
* @param  None
* @return None
***********************************************************************************************************************/
void KEY_Start(void)
{
    INTC_ClearPendingIRQ(KEY_IRQn); /* clear INTKR interrupt flag */
    INTC_EnableIRQ(KEY_IRQn);/* enable INTKR interrupt */
}
/***********************************************************************************************************************
* Function Name: KEY_Stop
* @brief  This function disables INTKR interrupt and clears interrupt flag.
* @param  None
* @return None
***********************************************************************************************************************/
void KEY_Stop(void)
{
    INTC_DisableIRQ(KEY_IRQn);      /* disable INTKR interrupt */
    INTC_ClearPendingIRQ(KEY_IRQn); /* clear INTKR interrupt flag */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
