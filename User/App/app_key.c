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
    .delayCnt = 0
};

key_mouse_ctrl_block_t keyMouseRight = 
{
    .port = PORTD,
    .pin  = PIN15,
    .name = KEY_MOUSE_RIGHT,
    .state = KEY_MOUSE_INIT,
    .delayCnt = 0
};

key_mouse_ctrl_block_t keyMouseMiddle = 
{
    .port = PORTD,
    .pin  = PIN2,
    .name = KEY_MOUSE_MIDDLE,
    .state = KEY_MOUSE_INIT,
    .delayCnt = 0
};


void App_Key_Init(void )
{
    Drv_Key_Init();

    Drv_Timer_Regist_Period(0, 1, App_Key_Handler, NULL);
	
}

static void App_Key_Handler(void *arg )
{
    uint16_t keyVal = KEY_NULL;
    
    App_Key_Mouse_Detect();

    keyVal = Drv_Key_Queue_Get();

    switch(keyVal)
    {
        case KEY_MOUSE_LEFT | KEY_DOWN:
        {
            break;
        }
        case KEY_MOUSE_RIGHT | KEY_DOWN:
        {
            break;
        }
        case KEY_MOUSE_MIDDLE | KEY_DOWN:
        {
            break;   
        }
    }
}

void App_Key_Mouse_Detect(void )
{
    Drv_Key_Mouse_Detect(&keyMouseLeft);

    Drv_Key_Mouse_Detect(&keyMouseRight);
    
    Drv_Key_Mouse_Detect(&keyMouseMiddle);
}


