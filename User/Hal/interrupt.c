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
#include "hal_lcd.h"
/* Private typedef --------------------------------------*/
/* Private define ---------------------------------------*/
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
void IRQ12_Handler(void) __attribute__((alias("spi1_interrupt")));
void IRQ27_Handler(void) __attribute__((alias("tm81_channel10_14_interrupt")));
void IRQ15_Handler(void) __attribute__((alias("lcdb_interrupt")));
/* Private variables ------------------------------------*/


void SysTick_Handler(void )
{
    Hal_Task_Isr_Handler();
}

void tm81_channel10_14_interrupt(void )
{
    volatile uint8_t ifl, ifh;
    
    ifl = INTC_GetPendingIRQ(TM10_IRQn);
    
    ifh = INTC_GetPendingIRQ(TM14_IRQn);
		
    if(ifl)
	{
        INTC_ClearPendingIRQ(TM10_IRQn);    /* clear INTTM10 interrupt flag */
    
        Hal_Timer_Isr_Handler();
	}

    if(ifh)
	{
        INTC_ClearPendingIRQ(TM14_IRQn);    /* clear INTTM14 interrupt flag */

	}
}

void spi1_interrupt(void )
{
    INTC_ClearPendingIRQ(SPI1_IRQn);

    Hal_Spi_Tx_Isr_Handler();

    Hal_Spi_Rx_Isr_Handler();
}

void lcdb_interrupt(void )
{
    INTC_ClearPendingIRQ(LCDB_IRQn);     /* clear LCDB interrupt flag */

    Hal_Lcd_Clr_Isr_Handler();
}


