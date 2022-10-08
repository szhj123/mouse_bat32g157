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


#endif 

