#ifndef _DRV_TASK_H
#define _DRV_TASK_H

#include "hal_task.h"

typedef void (*task_callback_t)(void * );

#define TASK_OK                 0
#define TASK_ERR                (!TASK_OK)

typedef enum _task_state_t
{
    TASK_READY = 0,
    TASK_SUSPEND,
    TASK_SLEEP,
    TASK_IDLE
}task_state_t;

typedef struct _task_ctrl_block_t
{
    task_callback_t callback;
    void            *arg;

    task_state_t    state;
    uint16_t        period;
    uint16_t        ticks;

    struct _task_ctrl_block_t *prev;
    struct _task_ctrl_block_t *next;
}task_ctrl_block_t;

void Drv_Task_Init(void );
task_ctrl_block_t * Drv_Task_Regist_Oneshot(uint16_t ticks, task_callback_t callback, void *arg );
task_ctrl_block_t * Drv_Task_Regist_Period(uint16_t ticks, uint16_t period, task_callback_t callback, void *arg );
uint8_t Drv_Task_Delay(task_ctrl_block_t *task, uint16_t ticks );
uint8_t Drv_Task_Sleep(task_ctrl_block_t *task );
uint8_t Drv_Task_Wakeup(task_ctrl_block_t *task );
uint8_t Drv_Task_Delete(task_ctrl_block_t *task );
void Drv_Task_Schedule(void );


#endif 

