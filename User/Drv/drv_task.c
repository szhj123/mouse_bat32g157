/********************************************************
* @file       drv_task.c
* @author     szhj13
* @version    V1.0
* @date       2022-05-18
* @brief      the start address of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "drv_task.h"
/* Private typedef --------------------------------------*/
/* Private define ---------------------------------------*/
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
static void Drv_Task_Isr_Handler(void );
/* Private variables ------------------------------------*/
task_ctrl_block_t *taskHead = NULL;

void Drv_Task_Init(void )
{
    Hal_Task_Init();

    Hal_Task_Regist_Isr_Callback(Drv_Task_Isr_Handler);
}

static task_ctrl_block_t * Drv_Task_Regist(uint16_t ticks, uint16_t period, task_callback_t callback ,void *arg )
{
    task_ctrl_block_t *task = (task_ctrl_block_t *)malloc(sizeof(task_ctrl_block_t));

    if(task == NULL)
    {
        return NULL;
    }

    task->callback = callback;
    task->arg = arg;
    task->ticks = ticks;
    task->period = period;
    if(ticks)
    {
        task->state = TASK_SUSPEND;
    }
    else
    {
        task->state = TASK_READY;
    }

    task->prev = NULL;
    task->next = NULL;

    if(taskHead == NULL)
    {
        taskHead = task;
    }
    else
    {
        task_ctrl_block_t *pTask = taskHead;

        while(pTask->next != NULL)
        {
            pTask = pTask->next;
        }

        pTask->next = task;
        task->prev = pTask;
    }

    return task;
}

task_ctrl_block_t * Drv_Task_Regist_Oneshot(uint16_t ticks, task_callback_t callback, void *arg )
{
    return Drv_Task_Regist(ticks, 0, callback, arg);
}

task_ctrl_block_t * Drv_Task_Regist_Period(uint16_t ticks, uint16_t period, task_callback_t callback, void *arg )
{
    return Drv_Task_Regist(ticks, period, callback, arg);
}

uint8_t Drv_Task_Delay(task_ctrl_block_t *task, uint16_t ticks )
{
    if(task == NULL || task->state == TASK_IDLE)
    {
        return TASK_ERR;
    }

    task->ticks = ticks;

    task->state = TASK_SUSPEND;

    return TASK_OK;
}

uint8_t Drv_Task_Sleep(task_ctrl_block_t *task )
{
    if(task == NULL || task->state == TASK_SLEEP || task->state == TASK_IDLE)
    {
        return TASK_ERR;
    }

    task->ticks = 0;
    task->state = TASK_SLEEP;

    return TASK_OK;
}

uint8_t Drv_Task_Wakeup(task_ctrl_block_t *task )
{
    if(task == NULL || task->state != TASK_SLEEP)
    {
        return TASK_ERR;
    }

    task->ticks = 0;
    task->state = TASK_READY;

    return TASK_OK;
}

uint8_t Drv_Task_Delete(task_ctrl_block_t *task )
{
    if(task == NULL || task->state == TASK_IDLE)
    {
        return TASK_ERR;
    }
    
    if(task->prev == NULL)
    {
        if(task->next == NULL)
        {
            taskHead = NULL;
            taskHead->next = NULL;
            taskHead->prev = NULL;
        }
        else
        {
            taskHead = task->next;
            taskHead->prev = NULL;
        }
    }
    else if(task->next == NULL)
    {
        task->prev->next = NULL;
    }
    else
    {
        task->prev->next = task->next;
        task->next->prev = task->prev;
    }

    free(task);

    task = NULL;

    return TASK_OK;
}

void Drv_Task_Schedule(void )
{
    task_ctrl_block_t *pTask = taskHead;

    while(pTask != NULL)
    {
        if(pTask->state == TASK_READY)
        {
            if(pTask->callback != NULL)
            {
                pTask->callback(pTask->arg);

                if(pTask->period)
                {
                    if(pTask->ticks == 0)
                    {
                        pTask->ticks = pTask->period;
                    }

                    pTask->state = TASK_SUSPEND;
                }
                else
                {
                    if(pTask->next == NULL)
                    {
                       Drv_Task_Delete(pTask);
                       
                       pTask = NULL;

                       break;
                    }
                    else
                    {
                        pTask = pTask->next;

                        Drv_Task_Delete(pTask->prev);

                        continue;
                    }                    
                }
            }
        }

        pTask = pTask->next;
    }
}

static void Drv_Task_Isr_Handler(void )
{
    task_ctrl_block_t *pTask = taskHead;

    while(pTask != NULL)
    {
        if(pTask->state == TASK_SUSPEND)
        {
            if(pTask->ticks > 0)
            {
                pTask->ticks--;
            }

            if(pTask->ticks == 0)
            {
                pTask->state = TASK_READY;
            }
        }

        pTask = pTask->next;
    }
}

