#ifndef _DRV_EVENT_H
#define _DRV_EVENT_H

#include "hal_bat32g157.h"

#define MSG_MAX_LENGTH                   64 
#define MSG_QUEUE_MAX_LENGTH             8

#define MSG_OK                           0
#define MSG_ERR                          (!MSG_OK)

typedef struct _msg_t
{
    uint8_t msgType;
    uint8_t msgBuf[MSG_MAX_LENGTH];
    uint8_t msgLength;
}msg_t;

typedef struct _msg_queue_t
{
    msg_t buf[MSG_QUEUE_MAX_LENGTH];
    uint8_t head;
    uint8_t rear;
}msg_queue_t;

void Drv_Event_Init(void );
void Drv_Event_Put(uint8_t msgType, uint8_t *buf, uint8_t length );
uint8_t Drv_Event_Get(msg_t *msg );


#endif 

