#ifndef _APP_EVENT_H
#define _APP_EVENT_H

#include "drv_task.h"
#include "drv_event.h"

typedef enum _app_event_t
{
    APP_EVENT_NULL = 0,
    APP_EVENT_KEY
}app_event_t;


void App_Event_Init(void );


#endif 

