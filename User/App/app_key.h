#ifndef _APP_KEY_H
#define _APP_KEY_H

#include "drv_timer.h"
#include "drv_key.h"

typedef enum _key_event_t
{
    KEY_EVENT_NULL= 0,
    KEY_EVENT_MOUSE_LEFT_DOWN,
    KEY_EVENT_MOUSE_LEFT_UP,
    KEY_EVENT_MOUSE_RIGHT_DOWN,
    KEY_EVENT_MOUSE_RIGHT_UP,
    KEY_EVENT_MOUSE_MIDDLE_DOWN,
    KEY_EVENT_MOUSE_MIDDLW_UP
}key_event_t;

void App_Key_Init(void );
void App_Key_Mouse_Detect(void );
void App_Key_Media_Detect(void );

#endif 

