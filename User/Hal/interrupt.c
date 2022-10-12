/********************************************************
* @file       interrupt.c
* @author     szhj13
* @version    V1.0
* @date       2022-05-18
* @brief      the start address of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "hal_task.h"
#include "hal_timer.h"
#include "hal_spi_flash.h"
/* Private typedef --------------------------------------*/
/* Private define ---------------------------------------*/
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
void IRQ12_Handler(void) __attribute__((alias("spi1_interrupt")));
void IRQ18_Handler(void) __attribute__((alias("tm40_channel0_interrupt")));
void IRQ15_Handler(void) __attribute__((alias("lcdb_interrupt")));
/* Private variables ------------------------------------*/


void SysTick_Handler(void )
{
    Hal_Task_Isr_Handler();
}

void tm40_channel0_interrupt(void )
{
    INTC_ClearPendingIRQ(TM00_IRQn);    

    Hal_Timer_Isr_Handler();
}

void spi1_interrupt(void )
{
    Hal_Spi_Flash_Tx_Isr_Handler();

    Hal_Spi_Flash_Rx_Isr_Handler();
    
    INTC_ClearPendingIRQ(SPI1_IRQn);
}

void lcdb_interrupt(void )
{
    INTC_ClearPendingIRQ(LCDB_IRQn);     /* clear LCDB interrupt flag */

    Hal_Lcd_Clr_Isr_Handler();
}


