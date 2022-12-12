#ifndef _APP_EVENT_H
#define _APP_EVENT_H

#include "drv_task.h"
#include "drv_event.h"

typedef enum _app_event_t
{
    APP_EVENT_NULL = 0,
    APP_EVENT_KEY,
    App_EVENT_LIGHT,
    APP_EVENT_USB_SET_REPORT,
    APP_EVENT_USB_GET_REPORT,
    APP_EVENT_USB_INTERUPT_OUT,
    APP_EVENT_USB_SUSPEND,
    APP_EVENT_USB_WAKEUP
}app_event_t;


void App_Event_Init(void );


#endif 

