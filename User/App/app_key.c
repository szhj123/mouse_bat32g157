/********************************************************
* @file       app_key.c
* @author     szhj13
* @version    V1.0
* @date       2022-05-18
* @brief      the start address of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "app_key.h"
#include "app_event.h"
/* Private typedef --------------------------------------*/
/* Private define ---------------------------------------*/
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
static void App_Key_Handler(void *arg );
/* Private variables ------------------------------------*/
key_mouse_ctrl_block_t keyMouseLeft = 
{
    .port = PORTC,//PORTD,
    .pin  = PIN6,//PIN14,
    .name = KEY_MOUSE_LEFT,
    .state = KEY_MOUSE_INIT,
    .shortPressTime = KEY_SHORT_PRESS_TIME,
    .delayCnt = 0
};

key_mouse_ctrl_block_t keyMouseRight = 
{
    .port = PORTD,
    .pin  = PIN15,
    .name = KEY_MOUSE_RIGHT,
    .state = KEY_MOUSE_INIT,
    .shortPressTime = KEY_SHORT_PRESS_TIME,
    .delayCnt = 0
};

key_mouse_ctrl_block_t keyMouseMiddle = 
{
    .port = PORTD,
    .pin  = PIN2,
    .name = KEY_MOUSE_MIDDLE,
    .state = KEY_MOUSE_INIT,
    .shortPressTime = KEY_SHORT_PRESS_TIME,
    .delayCnt = 0
};

key_media_ctrl_block_t keyMediaForward = 
{
    .port1 = PORTD,
    .pin1 = PIN3,
    .port2 = (PORT_TypeDef )((uint8_t )PORTH +1),
    .pin2 = (PIN_TypeDef )((uint8_t )PIN15 + 1),
    .name = KEY_MEDIA_FORWARD,
    .state = KEY_MEDIA_INIT,
    .isDoubleKey = 0,
    .isCompositeKey = 0,
    .delayCnt = 0,
    .shortPressTime = KEY_SHORT_PRESS_TIME,
};

key_media_ctrl_block_t keyMediaBackward = 
{
    .port1 = PORTD,
    .pin1 = PIN4,
    .port2 = (PORT_TypeDef )((uint8_t )PORTH +1),
    .pin2 = (PIN_TypeDef )((uint8_t )PIN15 + 1),
    .name = KEY_MEDIA_BACKWARD,
    .state = KEY_MEDIA_INIT,
    .isDoubleKey = 0,
    .isCompositeKey = 0,
    .delayCnt = 0,
    .shortPressTime = KEY_SHORT_PRESS_TIME,
};

key_media_ctrl_block_t keyMediaDpiInc = 
{
    .port1 = PORTD,
    .pin1 = PIN5,
    .port2 = (PORT_TypeDef )((uint8_t )PORTH +1),
    .pin2 = (PIN_TypeDef )((uint8_t )PIN15 + 1),
    .name = KEY_MEDIA_DPI_INC,
    .state = KEY_MEDIA_INIT,
    .isDoubleKey = 0,
    .isCompositeKey = 0,
    .delayCnt = 0,
    .shortPressTime = KEY_SHORT_PRESS_TIME,
};

key_media_ctrl_block_t keyMediaDpiDec = 
{
    .port1 = PORTD,
    .pin1 = PIN6,
    .port2 = (PORT_TypeDef )((uint8_t )PORTH +1),
    .pin2 = (PIN_TypeDef )((uint8_t )PIN15 + 1),
    .name = KEY_MEDIA_DPI_DEC,
    .state = KEY_MEDIA_INIT,
    .isDoubleKey = 0,
    .isCompositeKey = 0,
    .delayCnt = 0,
    .shortPressTime = KEY_SHORT_PRESS_TIME,
};

key_media_ctrl_block_t keyMediaFire = 
{
    .port1 = PORTD,
    .pin1 = PIN7,
    .port2 = (PORT_TypeDef )((uint8_t )PORTH +1),
    .pin2 = (PIN_TypeDef )((uint8_t )PIN15 + 1),
    .name = KEY_MEDIA_FIRE,
    .state = KEY_MEDIA_INIT,
    .isDoubleKey = 0,
    .isCompositeKey = 0,
    .delayCnt = 0,
    .shortPressTime = KEY_SHORT_PRESS_TIME,
};

key_media_ctrl_block_t keyMediaReportRate = 
{
    .port1 = PORTD,
    .pin1 = PIN8,
    .port2 = (PORT_TypeDef )((uint8_t )PORTH +1),
    .pin2 = (PIN_TypeDef )((uint8_t )PIN15 + 1),
    .name = KEY_MEDIA_REPORT_RATE,
    .state = KEY_MEDIA_INIT,
    .isDoubleKey = 0,
    .isCompositeKey = 0,
    .delayCnt = 0,
    .shortPressTime = KEY_SHORT_PRESS_TIME,
};


void App_Key_Init(void )
{
    Drv_Key_Init();

    Drv_Timer_Regist_Period(0, 1, App_Key_Handler, NULL);
}

static void App_Key_Handler(void *arg )
{
    uint16_t keyVal = KEY_NULL;
    key_event_t keyEvent = KEY_EVENT_NULL;
    
    App_Key_Mouse_Detect();

    App_Key_Media_Detect();

    keyVal = Drv_Key_Queue_Get();

    switch(keyVal)
    {
        case KEY_MOUSE_LEFT | KEY_DOWN:
        {
            keyEvent = KEY_EVENT_MOUSE_LEFT_DOWN;
            break;
        }
        case KEY_MOUSE_LEFT | KEY_UP:
        {
            keyEvent = KEY_EVENT_MOUSE_LEFT_UP;
            break;
        }
        case KEY_MOUSE_RIGHT | KEY_DOWN:
        {
            keyEvent = KEY_EVENT_MOUSE_RIGHT_DOWN;
            break;
        }
        case KEY_MOUSE_RIGHT | KEY_UP:
        {
            keyEvent = KEY_EVENT_MOUSE_RIGHT_UP;
            break;
        }
        case KEY_MOUSE_MIDDLE | KEY_DOWN:
        {
            keyEvent = KEY_EVENT_MOUSE_MIDDLE_DOWN;
            break;   
        }
        case KEY_MOUSE_MIDDLE | KEY_UP:
        {
            keyEvent = KEY_EVENT_MOUSE_MIDDLW_UP;
            break;
        }
        case KEY_MEDIA_FORWARD | KEY_DOWN | KEY_UP:
        {
            keyEvent = KEY_EVENT_MEDIA_FORWARD_DOWN;
            break;
        }
        case KEY_MEDIA_BACKWARD | KEY_DOWN | KEY_UP:
        {
            keyEvent = KEY_EVENT_MEDIA_BACKWARD_DOWN;
            break;
        }
        case KEY_MEDIA_DPI_INC | KEY_DOWN | KEY_UP:
        {
            keyEvent = KEY_EVENT_MEDIA_DPI_INC_DOWN;
            break;
        }
        case KEY_MEDIA_DPI_DEC | KEY_DOWN | KEY_UP:
        {
            keyEvent = KEY_EVENT_MEDIA_DPI_DEC_DOWN;
            break;
        }
        case KEY_MEDIA_FIRE | KEY_DOWN | KEY_UP:
        {
            keyEvent = KEY_EVENT_MEDIA_FIRE_DWON;
            break;
        }
        case KEY_MEDIA_REPORT_RATE | KEY_DOWN | KEY_UP:
        {
            keyEvent = KEY_EVENT_MEDIA_REPORT_RATE_DOWN;
            break;
        }
        default: break;
    }

    if(keyVal != KEY_NULL)
    {
        Drv_Event_Put((uint8_t )APP_EVENT_KEY, (uint8_t *)&keyEvent, 1);
    }
}

void App_Key_Mouse_Detect(void )
{
    Drv_Key_Mouse_Detect(&keyMouseLeft);

    Drv_Key_Mouse_Detect(&keyMouseRight);
    
    Drv_Key_Mouse_Detect(&keyMouseMiddle);
}

void App_Key_Media_Detect(void )
{
    Drv_Key_Media_Detect(&keyMediaForward);
    
    Drv_Key_Media_Detect(&keyMediaBackward);

    Drv_Key_Media_Detect(&keyMediaDpiInc);
    
    Drv_Key_Media_Detect(&keyMediaDpiDec);
    
    Drv_Key_Media_Detect(&keyMediaFire);
    
    Drv_Key_Media_Detect(&keyMediaReportRate);
}


