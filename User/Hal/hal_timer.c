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
/* Private variables ------------------------------------*/
hal_isr_callback_t hal_timer_isr_callback = NULL;

void Hal_Timer_Init(void )
{
    CGC->PER0 |= CGC_PER0_TM81EN_Msk;    /* enables input clock supply */
    TM81->TPS1 = _0000_TM8_CKM3_fCLK_8 | _0000_TM8_CKM2_fCLK_1 | _00F0_TM8_CKM1_fCLK_15 | _0000_TM8_CKM0_fCLK_0; 

    TM81->TT1 |= TM8_CHANNEL_0;
    
    INTC_ClearPendingIRQ(TM10_IRQn);
    NVIC_ClearPendingIRQ(TM10_IRQn);

    TM81->TMR10 = _0000_TM8_CLOCK_SELECT_CKM0 | _0000_TM8_CLOCK_MODE_CKS | _0000_TM8_TRIGGER_SOFTWARE |
                  _0000_TM8_MODE_INTERVAL_TIMER | _0000_TM8_START_INT_UNUSED;
    TM81->TDR10 = SystemCoreClock/1000 - 1;
    TM81->TOE1 &= ~_0001_TM8_CH0_OUTPUT_ENABLE;

    INTC_EnableIRQ(TM10_IRQn);

    TM81->TS1 |= TM8_CHANNEL_0;
}

void Hal_Timer_Regist_Isr_Callback(hal_isr_callback_t callback )
{
    hal_timer_isr_callback = callback;       
}

void Hal_Timer_Isr_Handler(void )
{
    if(hal_timer_isr_callback != NULL)
    {
        hal_timer_isr_callback();
    }
}


