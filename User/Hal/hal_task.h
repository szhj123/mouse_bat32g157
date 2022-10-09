#ifndef _HAL_TASK_H
#define _HAL_TASK_H

#include "hal_bat32g157.h"

void Hal_Task_Init(void );
void Hal_Task_Regist_Isr_Callback(hal_isr_callback_t callback );


#endif 
