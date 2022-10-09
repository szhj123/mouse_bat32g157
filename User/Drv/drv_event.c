/********************************************************
* @file       drv_event.c
* @author     szhj13
* @version    V1.0
* @date       2022-05-18
* @brief      the start address of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "drv_event.h"
/* Private typedef --------------------------------------*/
/* Private define ---------------------------------------*/
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
/* Private variables ------------------------------------*/
msg_queue_t msgQueue;

void Drv_Event_Init(void )
{
    msgQueue.head = msgQueue.rear = 0;
}

void Drv_Event_Put(uint8_t msgType, uint8_t *buf, uint8_t length )
{
    uint8_t i;

    if(length > MSG_MAX_LENGTH)
    {
        length = MSG_MAX_LENGTH;
    }
    
    msgQueue.buf[msgQueue.rear].msgType = msgType;

    for(i=0;i<length;i++)
    {
        msgQueue.buf[msgQueue.rear].msgBuf[i] = buf[i];
    }

    msgQueue.buf[msgQueue.rear].msgLength = length;

    msgQueue.rear = (msgQueue.rear + 1) % MSG_QUEUE_MAX_LENGTH;
}

uint8_t Drv_Event_Get(msg_t *msg )
{
    if(msgQueue.head != msgQueue.rear)
    {
        *msg = msgQueue.buf[msgQueue.head];

        msgQueue.head = (msgQueue.head + 1) % MSG_QUEUE_MAX_LENGTH;

        return MSG_OK;
    }
    else
    {
        return MSG_ERR;
    }
}

