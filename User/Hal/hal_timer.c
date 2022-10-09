/********************************************************
* @file       hal_timer.c
* @author     szhj13
* @version    V1.0
* @date       2022-05-18
* @brief      the start address of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "hal_timer.h"
/* Private typedef --------------------------------------*/
/* Private define ---------------------------------------*/
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
void IRQ18_Handler(void) __attribute__((alias("tm40_channel0_interrupt")));

/* Private variables ------------------------------------*/
hal_isr_callback_t hal_timer_isr_callback = NULL;

void Hal_Timer_Init(void )
{
    CGC->PER0 |= CGC_PER0_TM40EN_Msk;  

    TM40->TPS0 &= ~TM40_TPS0_PRS00_Msk;

    TM40->TMR00 &= ~TM40_TMR00_CKS_Msk;
    
    TM40->TMR00 &= ~TM40_TMR00_STS_Msk;

    TM40->TMR00 &= ~TM40_TMR00_MD_Msk;

    TM40->TDR00 = (SystemCoreClock/1000 - 1);
    
    TM40->TOE0 &= ~_0001_TM4_CH0_OUTPUT_ENABLE;

    INTC_ClearPendingIRQ(TM00_IRQn);

    NVIC_ClearPendingIRQ(TM00_IRQn);

    INTC_EnableIRQ(TM00_IRQn);
    
    TM40->TS0 |= TM40_TS0_TS00_Msk;
}

void Hal_Timer_Regist_Isr_Callback(hal_isr_callback_t callback )
{
    hal_timer_isr_callback = callback;       
}

void tm40_channel0_interrupt(void )
{
    INTC_ClearPendingIRQ(TM00_IRQn);    

    if(hal_timer_isr_callback != NULL)
    {
        hal_timer_isr_callback();
    }
}

