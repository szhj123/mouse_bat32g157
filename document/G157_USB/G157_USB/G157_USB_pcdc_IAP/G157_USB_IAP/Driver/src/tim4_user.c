/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    tim4_user.c
* @brief   This file implements device driver for Timer 4 module.
* @version 1.0.0
* @date    2020/10/24
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "BAT32G157.h"
#include "tim4.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
void IRQ18_Handler(void) __attribute__((alias("tm40_channel0_interrupt")));
void IRQ19_Handler(void) __attribute__((alias("tm40_channel1_interrupt")));
void IRQ20_Handler(void) __attribute__((alias("tm40_channel2_interrupt")));
void IRQ21_Handler(void) __attribute__((alias("tm40_channel3_interrupt")));
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* For TM40 pulse measurement */
volatile uint32_t g_tm40_ch0_width = 0UL;
volatile uint32_t g_tm40_ch1_width = 0UL;
volatile uint32_t g_tm40_ch2_width = 0UL;
volatile uint32_t g_tm40_ch3_width = 0UL;
volatile uint32_t g_inttm00Taken = 0UL;
volatile uint32_t g_inttm01Taken = 0UL;
volatile uint32_t g_inttm02Taken = 0UL;
volatile uint32_t g_inttm03Taken = 0UL;
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: tm40_channel0_interrupt
* @brief  This function INTTM00 interrupt service routine.
* @param  None
* @return None
***********************************************************************************************************************/
static void tm40_channel0_interrupt(void)
{
    INTC_ClearPendingIRQ(TM00_IRQn);    /* clear INTTM00 interrupt flag */
    g_inttm00Taken++;
    if (1U == (TM40->TSR00 & _0001_TM4_OVERFLOW_OCCURS))    /* overflow occurs */
    {
        g_tm40_ch0_width = (uint32_t)(TM40->TDR00 + 1UL) + 0x10000UL;
    }
    else
    {
        g_tm40_ch0_width = (uint32_t)(TM40->TDR00 + 1UL);
    }
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: tm40_channel1_interrupt
* @brief  This function INTTM01 interrupt service routine.
* @param  None
* @return None
***********************************************************************************************************************/
static void tm40_channel1_interrupt(void)
{
    INTC_ClearPendingIRQ(TM01_IRQn);    /* clear INTTM01 interrupt flag */
    g_inttm01Taken++;
    if (1U == (TM40->TSR01 & _0001_TM4_OVERFLOW_OCCURS))    /* overflow occurs */
    {
        g_tm40_ch1_width = (uint32_t)(TM40->TDR01 + 1UL) + 0x10000UL;
    }
    else
    {
        g_tm40_ch1_width = (uint32_t)(TM40->TDR01 + 1UL);
    }
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: tm40_channel2_interrupt
* @brief  This function INTTM02 interrupt service routine.
* @param  None
* @return None
***********************************************************************************************************************/
static void tm40_channel2_interrupt(void)
{
    INTC_ClearPendingIRQ(TM02_IRQn);    /* clear INTTM02 interrupt flag */
    g_inttm02Taken++;
    if (1U == (TM40->TSR02 & _0001_TM4_OVERFLOW_OCCURS))    /* overflow occurs */
    {
        g_tm40_ch2_width = (uint32_t)(TM40->TDR02 + 1UL) + 0x10000UL;
    }
    else
    {
        g_tm40_ch2_width = (uint32_t)(TM40->TDR02 + 1UL);
    }
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: tm40_channel3_interrupt
* @brief  This function INTTM03 interrupt service routine.
* @param  None
* @return None
***********************************************************************************************************************/
static void tm40_channel3_interrupt(void)
{
    INTC_ClearPendingIRQ(TM03_IRQn);    /* clear INTTM03 interrupt flag */
    g_inttm03Taken++;
    if (1U == (TM40->TSR03 & _0001_TM4_OVERFLOW_OCCURS))    /* overflow occurs */
    {
        g_tm40_ch3_width = (uint32_t)(TM40->TDR03 + 1UL) + 0x10000UL;
    }
    else
    {
        g_tm40_ch3_width = (uint32_t)(TM40->TDR03 + 1UL);
    }
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}