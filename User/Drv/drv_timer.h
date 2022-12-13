#ifndef _DRV_TIMER_H
#define _DRV_TIMER_H

#include "hal_timer.h"

#define TIMER_MAX_NUM                   16
#define TIMER_NULL                      (TIMER_MAX_NUM)

typedef void (*timer_callback_t)(void *);

typedef struct _timer_ctrl_block_t
{
    timer_callback_t callback;
    void *arg;
    uint16_t ticks;
    uint16_t period;
    uint8_t  isRegist;
}timer_ctrl_block_t;



void Drv_Timer_Init(void );
uint8_t Drv_Timer_Regist_Oneshot(uint16_t ticks, timer_callback_t callback, void *arg );
uint8_t Drv_Timer_Regist_Period(uint16_t ticks, uint16_t period, timer_callback_t callback, void *arg );
void Drv_Timer_Delete(uint8_t timerId );

#endif 

