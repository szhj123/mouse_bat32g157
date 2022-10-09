#ifndef _HAL_TIMER_H
#define _HAL_TIMER_H

#include "hal_bat32g157.h"

void Hal_Timer_Init(void );

void Hal_Timer_Regist_Isr_Callback(hal_isr_callback_t callback );

#endif 

