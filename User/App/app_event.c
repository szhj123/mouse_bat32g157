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
static void App_Event_Usb_Interrupt_Out(uint8_t *buf, uint8_t length );
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
                if(Usb_Get_Suspend_Flag())
                {
                    Usb_Wakeup();
                }
                
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
            case APP_EVENT_USB_INTERUPT_OUT:
            {
                App_Event_Usb_Interrupt_Out(msg.buf, msg.length);
                break;
            }
            case APP_EVENT_USB_SUSPEND:
            {
                App_Light_Off();
                break;
            }
            case APP_EVENT_USB_WAKEUP:
            {
                App_Light_Switch(NULL);
                break;
            }
            default: break;
        }
    }
}

static void App_Event_Key_Handler(key_event_t keyEvent )
{
    key_val_t keyVal;
    
    switch(keyEvent)
    {
        case KEY_EVENT_MOUSE_LEFT_DOWN:
        {
            App_Mouse_Get_Key_1(&keyVal);
            App_Key_Down_Handler(keyVal);
            break;
        }
        case KEY_EVENT_MOUSE_LEFT_UP:
        {
            App_Mouse_Get_Key_1(&keyVal);
            App_Key_Up_Handler(keyVal);
            break;
        }
        case KEY_EVENT_MOUSE_RIGHT_DOWN:
        {
            App_Mouse_Get_Key_2(&keyVal);
            App_Key_Down_Handler(keyVal);
            break;
        }
        case KEY_EVENT_MOUSE_RIGHT_UP:
        {
            App_Mouse_Get_Key_2(&keyVal);
            App_Key_Up_Handler(keyVal);
            break;
        }
        case KEY_EVENT_MOUSE_MIDDLE_DOWN:
        {
            App_Mouse_Get_Key_3(&keyVal);
            App_Key_Down_Handler(keyVal);
            break;
        }
        case KEY_EVENT_MOUSE_MIDDLW_UP:
        {
            App_Mouse_Get_Key_3(&keyVal);
            App_Key_Up_Handler(keyVal);
            break;
        }
        case KEY_EVENT_MEDIA_FORWARD_DOWN:
        {
            App_Mouse_Get_Key_4(&keyVal);
            App_Key_Down_Handler(keyVal);
            break;
        }
        case KEY_EVENT_MEDIA_FORWARD_UP:
        {
            App_Mouse_Get_Key_4(&keyVal);
            App_Key_Up_Handler(keyVal);
            break;
        }
        case KEY_EVENT_MEDIA_BACKWARD_DOWN:
        {
            App_Mouse_Get_Key_5(&keyVal);
            App_Key_Down_Handler(keyVal);
            break;
        }
        case KEY_EVENT_MEDIA_BACKWARD_UP:
        {
            App_Mouse_Get_Key_5(&keyVal);
            App_Key_Up_Handler(keyVal);
            break;
        }
        case KEY_EVENT_MEDIA_DPI_INC_DOWN:
        {
            App_Mouse_Get_Key_6(&keyVal);
            App_Key_Down_Handler(keyVal);
            break;
        }
        case KEY_EVENT_MEDIA_DPI_INC_UP:
        {
            App_Mouse_Get_Key_6(&keyVal);
            App_Key_Up_Handler(keyVal);
            break;
        }
        case KEY_EVENT_KNOB_ROTATE:
        {
            App_Key_Knob_Handle();
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
            App_Mouse_Set_Light_Dpi_Rate(buf, length);
            
            break;
        }
        case REPORT_ID_KEY_MODE:
        {
            App_Mouse_Set_Key_Mode(buf, length);
            break;
        }
        case REPORT_ID_LIGHT_EFFECT:
        {
            static uint8_t timerLightSwitchId = TIMER_NULL;
            
            App_Mouse_Set_Light_Effect(buf, length);

            Drv_Timer_Delete(timerLightSwitchId);

            timerLightSwitchId = Drv_Timer_Regist_Oneshot(250, App_Light_Switch, NULL);

            break;
        }
        case REPORT_ID_MACRO:
        {
            App_Mouse_Set_Macro(buf, length );
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

static void App_Event_Usb_Interrupt_Out(uint8_t *buf, uint8_t length )
{    
    if(buf[0] == REPORT_ID_PIC)
    {
        App_Mouse_Set_Pic(buf, length );        
    }
}


