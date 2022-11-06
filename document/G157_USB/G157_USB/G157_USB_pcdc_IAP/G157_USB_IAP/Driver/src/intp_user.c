/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    intp_user.c
* @brief   This file implements device driver for INTP module.
* @version 1.0.0
* @date    2020/10/24
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "userdefine.h"
#include "BAT32G157.h"
#include "intp.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
void IRQ01_Handler(void) __attribute__((alias("intp_0_4_interrupt")));
void IRQ02_Handler(void) __attribute__((alias("intp_1_5_interrupt")));
void IRQ03_Handler(void) __attribute__((alias("intp_2_6_interrupt")));
void IRQ04_Handler(void) __attribute__((alias("intp_3_7_interrupt")));

/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
volatile uint32_t g_intp0Taken;  	/* INTP0 taken */
volatile uint32_t g_intp1Taken;  	/* INTP1 taken */
volatile uint32_t g_intp2Taken;  	/* INTP2 taken */
volatile uint32_t g_intp3Taken;  	/* INTP3 taken */
volatile uint32_t g_intp4Taken;  	/* INTP4 taken */
volatile uint32_t g_intp5Taken;  	/* INTP5 taken */
volatile uint32_t g_intp6Taken;  	/* INTP6 taken */
volatile uint32_t g_intp7Taken;  	/* INTP7 taken */

/***********************************************************************************************************************
* Function Name: intp_0_4_interrupt
* @brief  INTP0 interrupt service routine
* @param  None
* @return None
***********************************************************************************************************************/
void intp_0_4_interrupt(void)
{

    volatile uint8_t ifl, ifh;

    ifl = INTC_GetPendingIRQ(INTP0_IRQn);
    ifh = INTC_GetPendingIRQ(INTP4_IRQn);

    if(ifl)
    {
        INTC_ClearPendingIRQ(INTP0_IRQn);
        intp0_callback();   
    }

    if(ifh)
    {
        INTC_ClearPendingIRQ(INTP4_IRQn);
        intp4_callback();   
    }

    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: intp0_callback
* @brief  This function is a callback function when INTP0 interrupt occurs.
* @param  None
* @return None
***********************************************************************************************************************/
static void intp0_callback(void)
{
    /* Start user code. Do not edit comment generated here */
    g_intp0Taken++;
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: intp4_callback
* @brief  This function is a callback function when INTP4 interrupt occurs.
* @param  None
* @return None
***********************************************************************************************************************/
static void intp4_callback(void)
{
    /* Start user code. Do not edit comment generated here */
    g_intp4Taken++;
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: intp_1_5_interrupt
* @brief  INTP1 interrupt service routine
* @param  None
* @return None
***********************************************************************************************************************/
void intp_1_5_interrupt(void)
{
    volatile uint8_t ifl, ifh;

    ifl = INTC_GetPendingIRQ(INTP1_IRQn);
    ifh = INTC_GetPendingIRQ(INTP5_IRQn);

    if(ifl)
    {
        INTC_ClearPendingIRQ(INTP1_IRQn);
        intp1_callback();   
    }

    if(ifh)
    {
        INTC_ClearPendingIRQ(INTP5_IRQn);
        intp5_callback();   
    }

    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: intp1_callback
* @brief  This function is a callback function when INTP1 interrupt occurs.
* @param  None
* @return None
***********************************************************************************************************************/
static void intp1_callback(void)
{
    /* Start user code. Do not edit comment generated here */
    g_intp1Taken++;
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: intp5_callback
* @brief  This function is a callback function when INTP5 interrupt occurs.
* @param  None
* @return None
***********************************************************************************************************************/
static void intp5_callback(void)
{
    /* Start user code. Do not edit comment generated here */
    g_intp5Taken++;
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: intp_2_6_interrupt
* @brief  INTP2 interrupt service routine
* @param  None
* @return None
***********************************************************************************************************************/
void intp_2_6_interrupt(void)
{
    volatile uint8_t ifl, ifh;

    ifl = INTC_GetPendingIRQ(INTP2_IRQn);
    ifh = INTC_GetPendingIRQ(INTP6_IRQn);

    if(ifl)
    {
        INTC_ClearPendingIRQ(INTP2_IRQn);
        intp2_callback();   
    }

    if(ifh)
    {
        INTC_ClearPendingIRQ(INTP6_IRQn);
        intp6_callback();   
    }

    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: intp2_callback
* @brief  This function is a callback function when INTP2 interrupt occurs.
* @param  None
* @return None
***********************************************************************************************************************/
static void intp2_callback(void)
{
    /* Start user code. Do not edit comment generated here */
    g_intp2Taken++;
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: intp6_callback
* @brief  This function is a callback function when INTP6 interrupt occurs.
* @param  None
* @return None
***********************************************************************************************************************/
static void intp6_callback(void)
{
    /* Start user code. Do not edit comment generated here */
    g_intp6Taken++;
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: intp_3_7_interrupt
* @brief  INTP3 interrupt service routine
* @param  None
* @return None
***********************************************************************************************************************/
void intp_3_7_interrupt(void)
{
    volatile uint8_t ifl, ifh;

    ifl = INTC_GetPendingIRQ(INTP3_IRQn);
    ifh = INTC_GetPendingIRQ(INTP7_IRQn);

    if(ifl)
    {
        INTC_ClearPendingIRQ(INTP3_IRQn);
        intp3_callback();   
    }

    if(ifh)
    {
        INTC_ClearPendingIRQ(INTP7_IRQn);
        intp7_callback();   
    }

    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: intp3_callback
* @brief  This function is a callback function when INTP3 interrupt occurs.
* @param  None
* @return None
***********************************************************************************************************************/
static void intp3_callback(void)
{
    /* Start user code. Do not edit comment generated here */
    g_intp3Taken++;
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: intp7_callback
* @brief  This function is a callback function when INTP7 interrupt occurs.
* @param  None
* @return None
***********************************************************************************************************************/
static void intp7_callback(void)
{
    /* Start user code. Do not edit comment generated here */
    g_intp7Taken++;
    /* End user code. Do not edit comment generated here */
}
/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

