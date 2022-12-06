#ifndef _APP_KEY_H
#define _APP_KEY_H

#include "drv_timer.h"
#include "drv_key.h"
#include "drv_spi_flash.h"

#include "app_mouse_protocol.h"
#include "usb_phid_apl.h"


typedef enum _key_event_t
{
    KEY_EVENT_NULL= 0,
    KEY_EVENT_MOUSE_LEFT_DOWN,
    KEY_EVENT_MOUSE_LEFT_UP,
    KEY_EVENT_MOUSE_RIGHT_DOWN,
    KEY_EVENT_MOUSE_RIGHT_UP,
    KEY_EVENT_MOUSE_MIDDLE_DOWN,
    KEY_EVENT_MOUSE_MIDDLW_UP,
    KEY_EVENT_MEDIA_FORWARD_DOWN,
    KEY_EVENT_MEDIA_FORWARD_UP,
    KEY_EVENT_MEDIA_BACKWARD_DOWN,
    KEY_EVENT_MEDIA_BACKWARD_UP,
    KEY_EVENT_MEDIA_DPI_INC_DOWN,
    KEY_EVENT_MEDIA_DPI_INC_UP,
    KEY_EVENT_MEDIA_DPI_DEC_DOWN,
    KEY_EVENT_MEDIA_FIRE_DWON,
    KEY_EVENT_MEDIA_REPORT_RATE_DOWN
}key_event_t;

void App_Key_Init(void );
void App_Key_Mouse_Detect(void );
void App_Key_Media_Detect(void );
void App_Key_Down_Handler(key_val_t keyVal );
void App_Key_Up_Handler(key_val_t keyVal );
void App_Key_Mouse_Down(key_val_t keyVal );
void App_Key_Mouse_Up(key_val_t keyVal );
void App_Key_Mouse_Motion(int16_t deltaX, int16_t deltaY );
void App_Key_Board_Down(key_val_t keyVal );
void App_Key_Dpi_Down(void );
void App_Key_Macro_Down(key_val_t keyVal );
void App_Key_Macro_Up(void );
void App_Key_Set_Press_State(void );
void App_Key_Clr_Press_State(void );

#endif 

