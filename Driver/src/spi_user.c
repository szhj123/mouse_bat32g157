/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    spi_user.c
* @brief   This file implements device driver for SPI module.
* @version 1.0.0
* @date    2020/10/24
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "BAT32G157.h"
#include "spi.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
void IRQ09_Handler(void) __attribute__((alias("spi0_interrupt")));
void IRQ12_Handler(void) __attribute__((alias("spi1_interrupt")));
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: spi0_interrupt
* @brief  SPI0 interrupt service routine
* @param  None
* @return None
***********************************************************************************************************************/
void spi0_interrupt(void)
{
    volatile uint8_t sio_dummy;

    if (g_spi0_tx_count > 0U || g_spi0_rx_count > 1U)
    {
        /* reveive data */
        if (0U != gp_spi0_rx_address)
        {
            *gp_spi0_rx_address = SPIHS0->SDRI0;
            gp_spi0_rx_address++;
            g_spi0_rx_count--;
        }
        else
        {
            sio_dummy = SPIHS0->SDRI0;
        }

        /* send data */
        if (0U != gp_spi0_tx_address)
        {
            SPIHS0->SDRO0 = *gp_spi0_tx_address;
            gp_spi0_tx_address++;
            g_spi0_tx_count--;
        }
        else
        {
            SPIHS0->SDRO0 = 0xFFU;
        }

    }
    else 
    {
        /* CPU receive the last data */
        if (1U == g_spi0_rx_count)
        {
            SPIHS0->SPIM0 &= ~_0080_SPI_START_TRG_ON;
            if (0U != gp_spi0_rx_address)
            {
                *gp_spi0_rx_address = SPIHS0->SDRI0;
                 g_spi0_rx_count--;
            }
            else
            {
                sio_dummy = SPIHS0->SDRI0;
            }
        }
        if (0U != gp_spi0_rx_address)
        {
            spi0_callback_receiveend();    /* complete receive */
        }
        /* wait the last data sent for DMA transfer */
        if (0U != gp_spi0_tx_address)
        {
            while(SPIHS0->SPIS0 & _0001_SPI_UNDER_EXECUTE) 
            {
                ;
            }
            spi0_callback_sendend();    /* complete send */
        }
    }
    INTC_ClearPendingIRQ(SPI0_IRQn);
}
/***********************************************************************************************************************
* Function Name: spi0_callback_receiveend
* @brief  This function is a callback function when spi finishes reception.
* @param  None
* @return None
***********************************************************************************************************************/
static void spi0_callback_receiveend(void)
{
    /* Start user code. Do not edit comment generated here */
    SPI0_Stop();
    gp_spi0_rx_address = 0;    /* reinitialize global variable */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: spi0_callback_sendend
* @brief  This function is a callback function when spi finishes transmission.
* @param  None
* @return None
***********************************************************************************************************************/
static void spi0_callback_sendend(void)
{
    /* Start user code. Do not edit comment generated here */
    SPI0_Stop();
    gp_spi0_tx_address = 0;    /* reinitialize global variable */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: spi1_interrupt
* @brief  SPI1 interrupt service routine
* @param  None
* @return None
***********************************************************************************************************************/
void spi1_interrupt(void)
{
    volatile uint8_t sio_dummy;

    if (g_spi1_tx_count > 0U || g_spi1_rx_count > 1U)
    {
        /* reveive data */
        if (0U != gp_spi1_rx_address)
        {
            *gp_spi1_rx_address = SPIHS1->SDRI1;
            gp_spi1_rx_address++;
            g_spi1_rx_count--;
        }
        else
        {
            sio_dummy = SPIHS0->SDRI0;
        }

        /* send data */
        if (0U != gp_spi1_tx_address)
        {
            SPIHS1->SDRO1 = *gp_spi1_tx_address;
            gp_spi1_tx_address++;
            g_spi1_tx_count--;
        }
        else
        {
            SPIHS1->SDRO1 = 0xFFU;
        }

    }
    else 
    {
        /* CPU receive the last data */
        if (1U == g_spi1_rx_count)
        {
            SPIHS1->SPIM1 &= ~_0080_SPI_START_TRG_ON;
            if (0U != gp_spi1_rx_address)
            {
                *gp_spi1_rx_address = SPIHS1->SDRI1;
                 g_spi1_rx_count--;
            }
            else
            {
                sio_dummy = SPIHS1->SDRI1;
            }
        }
        if (0U != gp_spi1_rx_address)
        {
            spi1_callback_receiveend();    /* complete receive */
        }
        /* wait the last data sent for DMA transfer */
        if (0U != gp_spi1_tx_address)
        {
            while(SPIHS1->SPIS1 & _0001_SPI_UNDER_EXECUTE) 
            {
                ;
            }
            spi1_callback_sendend();    /* complete send */
        }
    }
    INTC_ClearPendingIRQ(SPI1_IRQn);
}
/***********************************************************************************************************************
* Function Name: spi1_callback_receiveend
* @brief  This function is a callback function when spi finishes reception.
* @param  None
* @return None
***********************************************************************************************************************/
static void spi1_callback_receiveend(void)
{
    /* Start user code. Do not edit comment generated here */
    SPI1_Stop();
    gp_spi1_rx_address = 0;    /* reinitialize global variable */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: spi1_callback_sendend
* @brief  This function is a callback function when spi finishes transmission.
* @param  None
* @return None
***********************************************************************************************************************/
static void spi1_callback_sendend(void)
{
    /* Start user code. Do not edit comment generated here */
    SPI1_Stop();
    gp_spi1_tx_address = 0;    /* reinitialize global variable */
    /* End user code. Do not edit comment generated here */
}
/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
