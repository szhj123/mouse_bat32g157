/********************************************************
* @file       drv_timer.c
* @author     szhj13
* @version    V1.0
* @date       2022-05-18
* @brief      the start address of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "drv_timer.h"
/* Private typedef --------------------------------------*/
/* Private define ---------------------------------------*/
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
static void Drv_Timer_Isr_Handler(void );
/* Private variables ------------------------------------*/
timer_ctrl_block_t timerBuf[TIMER_MAX_NUM];

void Drv_Timer_Init(void )
{
    uint8_t i;
    
    Hal_Timer_Init();

    Hal_Timer_Regist_Isr_Callback(Drv_Timer_Isr_Handler);

    for(i=0;i<TIMER_MAX_NUM;i++)
    {
        timerBuf[i].callback = NULL;
        timerBuf[i].arg = NULL;
        timerBuf[i].ticks = 0;
        timerBuf[i].period = 0;
        timerBuf[i].isRegist = 0;
    }
}

static uint8_t Drv_Timer_Reigst(uint16_t ticks, uint16_t period, timer_callback_t callback, void *arg )
{
    uint8_t timerId;

    for(timerId=0;timerId<TIMER_MAX_NUM;timerId++)
    {
        if(timerBuf[timerId].isRegist == 0)
        {
            timerBuf[timerId].callback = callback;
            timerBuf[timerId].arg = arg;
            timerBuf[timerId].ticks = ticks;
            timerBuf[timerId].period = period;

            timerBuf[timerId].isRegist = 1;

            return timerId;
        }
    }

    return TIMER_NULL;
}

uint8_t Drv_Timer_Regist_Oneshot(uint16_t ticks, timer_callback_t callback, void *arg )
{
    return Drv_Timer_Reigst(ticks, 0, callback, arg);
}

uint8_t Drv_Timer_Regist_Period(uint16_t ticks, uint16_t period, timer_callback_t callback, void *arg )
{
    return Drv_Timer_Reigst(ticks, period, callback, arg);
}

void Drv_Timer_Delete(uint8_t timerId )
{
    if(timerId >= TIMER_MAX_NUM)
    {
        return ;
    }
    
    timerBuf[timerId].isRegist = 0;
    timerBuf[timerId].callback = NULL;
    timerBuf[timerId].arg = NULL;
    timerBuf[timerId].ticks = 0;
    timerBuf[timerId].period = 0;
}

static void Drv_Timer_Isr_Handler(void )
{
    uint8_t timerId;

    for(timerId=0;timerId<TIMER_MAX_NUM;timerId++)
    {
        if(timerBuf[timerId].isRegist)
        {
            if(timerBuf[timerId].ticks)
            {
                timerBuf[timerId].ticks--;
            }

            if(timerBuf[timerId].ticks == 0)
            {
                if(timerBuf[timerId].callback != NULL)
                {
                    timerBuf[timerId].callback(timerBuf[timerId].arg);
                }

                if(timerBuf[timerId].period)
                {
                    timerBuf[timerId].ticks = timerBuf[timerId].period;
                }
                else
                {
                    Drv_Timer_Delete(timerId);
                }
            }
        }
    }
}

