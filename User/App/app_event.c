/********************************************************
* @file       app_event.c
* @author     szhj13
* @version    V1.0
* @date       2022-05-18
* @brief      the start address of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "app_event.h"

/* Private typedef --------------------------------------*/
/* Private define ---------------------------------------*/
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
static void Drv_Event_Handler(void *arg );
/* Private variables ------------------------------------*/

void App_Event_Init(void )
{
    Drv_Event_Init();

    Drv_Task_Regist_Period(0, 1, Drv_Event_Handler, NULL);
}

static void Drv_Event_Handler(void *arg )
{
    static msg_t msg;

    if(Drv_Event_Get(&msg) == MSG_OK)
    {
        switch(msg.msgType)
        {
            default: break;
        }
    }
}

