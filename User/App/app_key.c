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
#include "app_light.h"
#include "app_mouse_sensor.h"
#include "usb_phid_apl.h"
/* Private typedef --------------------------------------*/
typedef enum _macro_key_state_t
{
    MACRO_KEY_STATE_GET = 0,
    MACRO_KEY_STATE_SEND,
    MACRO_KEY_STATE_EXIT
}macro_key_state_t;
    
typedef struct _macro_key_ctrl_block_t
{
    macro_key_state_t state;
    loop_type_t loopType;
    uint8_t  loopCount;
    uint16_t delayTime;
    uint16_t delayCnt;
    uint8_t  index;
    uint8_t  macroDataIsPress;
    uint8_t  macroKeyIsPress;
    uint8_t  otherKeyIsPress;
    uint8_t  keyVal;
    uint8_t  timerId;
}macro_key_ctrl_block_t;
/* Private define ---------------------------------------*/
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
static void App_Key_Handler(void *arg );
/* Private variables ------------------------------------*/
key_mouse_ctrl_block_t keyMouseLeft = 
{
    .port = PORTD,
    .pin  = PIN14,
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

key_knob_ctrl_block_t keyKnob = 
{
    .port1 = PORTD,
    .pin1  = PIN12,
    .port2 = PORTD,
    .pin2  = PIN13,
};


val_t mouseReportBuf[8] = {0};
val_t keyBoardReportBuf[8] = {0};

macro_key_ctrl_block_t macroKeyCtrl = 
{
    .timerId = TIMER_NULL,
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

    App_Key_Knob_Detect();

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
        case KEY_MEDIA_FORWARD | KEY_DOWN:
        {
            keyEvent = KEY_EVENT_MEDIA_FORWARD_DOWN;
            break;
        }
        case KEY_MEDIA_FORWARD | KEY_DOWN | KEY_UP:
        {
            keyEvent = KEY_EVENT_MEDIA_FORWARD_UP;
            break;
        }
        case KEY_MEDIA_BACKWARD | KEY_DOWN:
        {
            keyEvent = KEY_EVENT_MEDIA_BACKWARD_DOWN;
            break;
        }
        case KEY_MEDIA_BACKWARD | KEY_DOWN | KEY_UP:
        {
            keyEvent = KEY_EVENT_MEDIA_BACKWARD_UP;
            break;
        }
        case KEY_MEDIA_DPI_INC | KEY_DOWN:
        {
            keyEvent = KEY_EVENT_MEDIA_DPI_INC_DOWN;
            break;
        }
        case KEY_MEDIA_DPI_INC | KEY_DOWN | KEY_UP:
        case KEY_MEDIA_DPI_INC | KEY_LONG | KEY_UP:
        case KEY_MEDIA_DPI_INC | KEY_CONT | KEY_UP:
        {
            keyEvent = KEY_EVENT_MEDIA_DPI_INC_UP;
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
        case KEY_MOUSE_KNOB | KEY_ROTATE:
        {
            keyEvent = KEY_EVENT_KNOB_ROTATE;
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

void App_Key_Knob_Detect(void )
{
    Drv_Key_Knob_Detect(&keyKnob);
}

void App_Key_Down_Handler(key_val_t keyVal )
{
    switch((key_type_t )keyVal.keyType)
    {
        case KEY_TYPE_MOUSE:
        {
            App_Key_Mouse_Down(keyVal);
            
            App_Key_Set_Press_State();

            break;
        }
        case KEY_TYPE_DPI:
        {
            App_Key_Dpi_Down();
            
            App_Key_Set_Press_State();
            break;
        }
        case KEY_TYPE_MACRO:
        {
            App_Key_Macro_Down(keyVal);
            break;
        }
        default: break;
    }
}

void App_Key_Up_Handler(key_val_t keyVal )
{
    switch((key_type_t )keyVal.keyType)
    {
        case KEY_TYPE_MOUSE:
        {
            App_Key_Mouse_Up(keyVal);
            
            App_Key_Clr_Press_State();
            
            break;
        }
        case KEY_TYPE_DPI:
        {
            App_Key_Clr_Press_State();
            
            break;
        }
        case KEY_TYPE_MACRO:
        {
            App_Key_Macro_Up();
            
            break;
        }
        default: break;
    }
}

void App_Key_Mouse_Down(key_val_t keyVal )
{
    mouseReportBuf[0].val = REPORT_ID_MOUSE;
    
    switch((key_mouse_func_t )keyVal.keyFunc)
    {
        case KEY_MOUSE_FUNC_LEFT: mouseReportBuf[1].val_b.val_0 = 1; break;
        case KEY_MOUSE_FUNC_RIGHT: mouseReportBuf[1].val_b.val_1 = 1; break;
        case KEY_MOUSE_FUNC_MIDDLE: mouseReportBuf[1].val_b.val_2 = 1; break;
        case KEY_MOUSE_FUNC_FRONT: mouseReportBuf[1].val_b.val_3 = 1; break;
        case KEY_MOUSE_FUNC_BACK: mouseReportBuf[1].val_b.val_4 = 1; break;
        default :break;
    }

    mouseReportBuf[2].val = 0;
    mouseReportBuf[3].val = 0;
    mouseReportBuf[4].val = 0;
    mouseReportBuf[5].val = 0;
    mouseReportBuf[6].val = keyKnob.count;

    Usb_Ep1_In((uint8_t *)mouseReportBuf, 7);
}

void App_Key_Mouse_Up(key_val_t keyVal )
{
    mouseReportBuf[0].val = REPORT_ID_MOUSE;
    
    switch((key_mouse_func_t )keyVal.keyFunc)
    {
        case KEY_MOUSE_FUNC_LEFT: mouseReportBuf[1].val_b.val_0 = 0; break;
        case KEY_MOUSE_FUNC_RIGHT: mouseReportBuf[1].val_b.val_1 = 0; break;
        case KEY_MOUSE_FUNC_MIDDLE: mouseReportBuf[1].val_b.val_2 = 0; break;
        case KEY_MOUSE_FUNC_FRONT: mouseReportBuf[1].val_b.val_3 = 0; break;
        case KEY_MOUSE_FUNC_BACK: mouseReportBuf[1].val_b.val_4 = 0; break;
        default :break;
    }
    
    mouseReportBuf[2].val = 0;
    mouseReportBuf[3].val = 0;
    mouseReportBuf[4].val = 0;
    mouseReportBuf[5].val = 0;
    mouseReportBuf[6].val = 0;

    Usb_Ep1_In((uint8_t *)mouseReportBuf, 7);
}


void App_Key_Knob_Handle(void )
{
    mouseReportBuf[0].val = REPORT_ID_MOUSE;

    mouseReportBuf[2].val = 0;
    mouseReportBuf[3].val = 0;
    mouseReportBuf[4].val = 0;
    mouseReportBuf[5].val = 0;
    mouseReportBuf[6].val = keyKnob.count;
    
    Usb_Ep1_In((uint8_t *)mouseReportBuf, 7);

    keyKnob.count = 0;
}

void App_Key_Mouse_Motion(int16_t deltaX, int16_t deltaY )
{
    mouseReportBuf[0].val = REPORT_ID_MOUSE;

    mouseReportBuf[2].val = (uint8_t )deltaX;
    mouseReportBuf[3].val = (uint8_t )(deltaX >> 8);
    mouseReportBuf[4].val = (uint8_t )deltaY;
    mouseReportBuf[5].val = (uint8_t )(deltaY >> 8);
    mouseReportBuf[6].val = keyKnob.count;

    Usb_Ep1_In((uint8_t *)mouseReportBuf, 7);
}

void App_Key_Board_Down(key_val_t keyVal )
{
    uint8_t i;
    
    keyBoardReportBuf[0].val = REPORT_ID_KEYBOARD;

    keyBoardReportBuf[1].val = 0;

    for(i=0;i<8;i++)
    {
        if(keyVal.keyFunc & (1 << i))
            keyBoardReportBuf[1].val |= (1 << i);
    }

    keyBoardReportBuf[2].val = keyVal.keyVal_l;
    keyBoardReportBuf[3].val = keyVal.keyVal_h;

    Usb_Ep2_In((uint8_t *)keyBoardReportBuf, 8);
}



void App_Key_Dpi_Down(void )
{
    light_color_t dpiColor;
    uint32_t cpiVal;
    uint8_t dpiRegVal;
    uint8_t dpiIndex = App_Mouse_Get_Dpi_Index();

    dpiIndex++;

    if(dpiIndex >= App_Mouse_Get_Dpi_Num())
    {
        dpiIndex = 0;
    }

    dpiRegVal = App_Mouse_Get_Dpi_RegVal(dpiIndex);

    cpiVal = App_Mouse_Sensor_Get_Cpi_Value(dpiRegVal);

    App_Mouse_Sensor_Set_Cpi_Value(cpiVal);

    App_Mouse_Get_Dpi_Color(dpiIndex, &dpiColor);

    App_Light_Dpi(dpiColor);

    keyBoardReportBuf[0].val = REPORT_ID_DPI;
    keyBoardReportBuf[1].val = 1;
    keyBoardReportBuf[2].val = dpiIndex+1;
    
    Usb_Ep2_In((uint8_t *)keyBoardReportBuf, 3);

    App_Mouse_Set_Dpi_Index(dpiIndex);
}

static void App_Key_Macro_Down_Callback(void *arg )
{
    static macro_key_val_t macroKeyVal;
    static key_val_t keyVal;
    
    if(macroKeyCtrl.delayCnt < 0xffff)
    {
        macroKeyCtrl.delayCnt++;
    }

    switch(macroKeyCtrl.state)
    {
        case MACRO_KEY_STATE_GET:
        {
            App_Mouse_Get_Macro_Key_Val(macroKeyCtrl.index, &macroKeyVal);

            macroKeyCtrl.macroDataIsPress = (macroKeyVal.delayTime_h & 0x80) ? 1 : 0;

            macroKeyCtrl.delayTime = (uint16_t )(macroKeyVal.delayTime_h & 0x7f) << 8 | macroKeyVal.delayTime_l;

            macroKeyCtrl.keyVal = macroKeyVal.keyVal;
            
            macroKeyCtrl.delayCnt = 0;

            macroKeyCtrl.state = MACRO_KEY_STATE_SEND;
            
            break;
        }
        case MACRO_KEY_STATE_SEND:
        {
            if(macroKeyCtrl.macroDataIsPress)
            {
                switch(macroKeyCtrl.keyVal)
                {
                    case 0xf0: case 0xf1: case 0xf2: case 0xf3: case 0xf4: 
                    {
                        keyVal.keyType = (uint8_t )KEY_TYPE_MOUSE;
                        keyVal.keyFunc = macroKeyCtrl.keyVal;
                           
                        App_Key_Mouse_Down(keyVal);
                        
                        break;
                    }
                    case 0xe0: case 0xe1: case 0xe2: case 0xe3: case 0xe4: case 0xe5: case 0xe6: case 0xe7:
                    {
                        keyVal.keyType = (uint8_t )KEY_TYPE_KEYBOARD;
                        keyVal.keyFunc = 1 << (macroKeyCtrl.keyVal & 0x07);
    
                        App_Key_Board_Down(keyVal);
                        
                        break;
                    }
                    default: 
                    {
                        keyVal.keyType = (uint8_t )KEY_TYPE_KEYBOARD;
                        keyVal.keyVal_l = macroKeyCtrl.keyVal;
                        
                        App_Key_Board_Down(keyVal);
                        break;
                    }
                }
            }
            else
            {
                switch(macroKeyCtrl.keyVal)
                {
                    case 0xf0: case 0xf1: case 0xf2: case 0xf3: case 0xf4:
                    {
                        keyVal.keyType = (uint8_t )KEY_TYPE_MOUSE;
                        keyVal.keyFunc = 0x00;
                        keyVal.keyVal_h = 0x00;
                        keyVal.keyVal_l = 0x00;
                        App_Key_Mouse_Down(keyVal);
                        break;
                    }
                    default:
                    {
                        keyVal.keyType = (uint8_t )KEY_TYPE_KEYBOARD;
                        keyVal.keyFunc = 0x00;
                        keyVal.keyVal_h = 0x00;
                        keyVal.keyVal_l = 0x00;
                        App_Key_Board_Down(keyVal);
                        break;
                    }
                }
            }

            macroKeyCtrl.delayCnt = 0;

            macroKeyCtrl.state = MACRO_KEY_STATE_EXIT;
                
            break;
        }
        case MACRO_KEY_STATE_EXIT:
        {
            if(macroKeyCtrl.delayCnt >= macroKeyCtrl.delayTime)
            {
                macroKeyCtrl.delayCnt = 0;
                
                macroKeyCtrl.index++;

                if(macroKeyCtrl.index >= App_Mouse_Get_Macro_Key_Num())
                {
                    macroKeyCtrl.index = 0;

                    if(macroKeyCtrl.loopType == LOOP_FIX_COUNT)
                    {
                        if(macroKeyCtrl.loopCount > 0)
                        {
                            macroKeyCtrl.loopCount--;
                        }
                    }
                    else
                    {
                        macroKeyCtrl.loopCount = 0;
                    }
                }

                macroKeyCtrl.state = MACRO_KEY_STATE_GET;
            }
            break;
        }
        default: break;
    }
    
    switch(macroKeyCtrl.loopType)
    {
        case LOOP_FIX_COUNT:
        {
            if(macroKeyCtrl.loopCount == 0)
            {
                App_Key_Macro_Up();
                
                Drv_Timer_Delete(macroKeyCtrl.timerId);
            }
            break;
        }
        case LOOP_KEY_UP_TERMINATION:
        {
            if(macroKeyCtrl.macroKeyIsPress == 0)
            {
                App_Key_Macro_Up();
                
                Drv_Timer_Delete(macroKeyCtrl.timerId);
            }
            break;
        }
        case LOOP_ANY_KEY_PRESS_TERMINATION:
        {
            if(macroKeyCtrl.otherKeyIsPress)
            {
                App_Key_Macro_Up();
                
                Drv_Timer_Delete(macroKeyCtrl.timerId);

                macroKeyCtrl.otherKeyIsPress = 0;

                macroKeyCtrl.timerId = TIMER_NULL;

            }
            
            break;
        }
        default: break;
    }
}

void App_Key_Macro_Down(key_val_t keyVal )
{
    App_Mouse_Get_Macro_Key(keyVal.keyFunc);

    macroKeyCtrl.loopType = (loop_type_t )keyVal.keyVal_l;
    macroKeyCtrl.loopCount = keyVal.keyVal_h;   
    macroKeyCtrl.delayCnt = 0;
    macroKeyCtrl.index = 0;
    macroKeyCtrl.state = MACRO_KEY_STATE_GET;
    macroKeyCtrl.macroKeyIsPress = 1;

    Drv_Timer_Delete(macroKeyCtrl.timerId);

    if(macroKeyCtrl.loopType == LOOP_ANY_KEY_PRESS_TERMINATION)
    {        
        if(macroKeyCtrl.timerId == TIMER_NULL)
        {
            macroKeyCtrl.timerId = Drv_Timer_Regist_Period(0, 1, App_Key_Macro_Down_Callback, NULL);
        }
        else
        {
            App_Key_Macro_Up();
                
            macroKeyCtrl.timerId = TIMER_NULL;
        }
    }
    else
    {
        macroKeyCtrl.timerId = Drv_Timer_Regist_Period(0, 1, App_Key_Macro_Down_Callback, NULL);
    }
}

void App_Key_Macro_Up(void )
{
    key_val_t keyVal;
    
    keyVal.keyType = (uint8_t )KEY_TYPE_KEYBOARD;
    keyVal.keyFunc = 0x00;
    keyVal.keyVal_h = 0x00;
    keyVal.keyVal_l = 0x00;
    
    App_Key_Board_Down(keyVal);

    macroKeyCtrl.macroKeyIsPress = 0;
}

void App_Key_Set_Press_State(void )
{
    macroKeyCtrl.otherKeyIsPress = 1;
}

void App_Key_Clr_Press_State(void )
{
    macroKeyCtrl.otherKeyIsPress = 0;

    if(macroKeyCtrl.timerId != TIMER_NULL)
    {
        Drv_Timer_Delete(macroKeyCtrl.timerId);

        macroKeyCtrl.timerId = TIMER_NULL;
    }
}

