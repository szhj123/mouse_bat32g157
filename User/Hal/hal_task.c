/********************************************************
* @file       hal_task.c
* @author     szhj13
* @version    V1.0
* @date       2022-05-18
* @brief      the start address of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "hal_task.h"
/* Private typedef --------------------------------------*/
/* Private define ---------------------------------------*/
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
/* Private variables ------------------------------------*/
hal_isr_callback_t hal_systick_isr_callback = NULL;

void Hal_Task_Init(void )
{
    SysTick_Config(SystemCoreClock/1000);
}

void Hal_Task_Regist_Isr_Callback(hal_isr_callback_t callback )
{
    hal_systick_isr_callback = callback;
}

void SysTick_Handler(void )
{
    if(hal_systick_isr_callback != NULL)
    {
        hal_systick_isr_callback();
    }
}



