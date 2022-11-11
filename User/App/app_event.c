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
#include "usb_phid_apl.h"
#include "app_event.h"
#include "app_mouse_protocol.h"
#include "app_key.h"
#include "app_light.h"
/* Private typedef --------------------------------------*/
/* Private define ---------------------------------------*/
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
static void Drv_Event_Handler(void *arg );
static void App_Event_Key_Handler(key_event_t keyEvent );
static void App_Event_Usb_Set_Report(uint8_t *buf, uint8_t length );
static void App_Event_Usb_Get_Report(uint8_t *buf, uint8_t length );
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
        switch((app_event_t )msg.msgType)
        {
            case APP_EVENT_KEY:
            {
                App_Event_Key_Handler((key_event_t )msg.buf[0]);
                
                break;
            }            
            case APP_EVENT_USB_SET_REPORT:
            {
                App_Event_Usb_Set_Report(msg.buf, msg.length);
                
                break;
            }
            case APP_EVENT_USB_GET_REPORT:
            {
                App_Event_Usb_Get_Report(msg.buf, msg.length);
                break;
            }
            default: break;
        }
    }
}

static void App_Event_Key_Handler(key_event_t keyEvent )
{
    switch(keyEvent)
    {
        case KEY_EVENT_MOUSE_LEFT_DOWN:
        {
            key_val_t key1;

            App_Mouse_Get_Key_1(&key1);
            
            App_Key_Function(key1);
            
            break;
        }
        case KEY_EVENT_MOUSE_RIGHT_DOWN:
        {
            break;
        }
        case KEY_EVENT_MOUSE_MIDDLE_DOWN:
        {
            break;
        }
        default: break;
    }
}

static void App_Event_Usb_Set_Report(uint8_t *buf, uint8_t length )
{
    switch(buf[0])
    {
        case REPORT_ID_KEY_VALUE:
        {
            App_Mouse_Set_Key_Value(buf, length);
            
            break;
        }
        case REPORT_ID_LIGHT_DPI_RATE:
        {
            light_dpi_rate_t lightDpiRate = *(light_dpi_rate_t *)buf;
            
            App_Mouse_Set_Light_Dpi_Rate(buf, length);

            App_Light_Switch(lightDpiRate.lightMode);;
            
            break;
        }
        case REPORT_ID_KEY_MODE:
        {
            App_Mouse_Set_Key_Mode(buf, length);
            break;
        }
        case REPORT_ID_LIGHT_EFFECT:
        {
            App_Mouse_Set_Light_Effect(buf, length);
            break;
        }
        default: break;
    }
}

static void App_Event_Usb_Get_Report(uint8_t *buf, uint8_t length )
{
    switch(buf[2])
    {
        case REPORT_ID_LIGHT_DPI_RATE:
        {
            App_Mouse_Get_Light_Dpi_Rate(buf, length);
            break;
        }
        case REPORT_ID_KEY_MODE:
        {
            App_Mouse_Get_Key_Mode(buf, length);
            break;
        }
        default: break;
    }
}


