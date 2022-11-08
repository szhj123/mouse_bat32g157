/********************************************************
* @file       app_light.c
* @author     szhj13
* @version    V1.0
* @date       2022-05-18
* @brief      the start address of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "app_light.h"
/* Private typedef --------------------------------------*/
typedef void (*light_show_callback_t)(void );
/* Private define ---------------------------------------*/
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
static void App_Light_Handler(void *arg );
/* Private variables ------------------------------------*/
static light_show_callback_t light_show_callback = NULL;

static solid_on_para_t solidOnPara;


void App_Light_Init(void )
{
    Drv_Light_Init();

    Drv_Task_Regist_Period(0, 1, App_Light_Handler, NULL);
}

static void App_Light_Handler(void *arg )
{
    if(light_show_callback != NULL)
    {
        light_show_callback();
    }
}

void App_Light_Solid_On_Para_Init(void )
{
    solidOnPara.brightness = (brightness_t)App_Mouse_Get_Solid_On_Brightness();
    solidOnPara.lightColor = App_Mouse_Get_Solid_On_Color();    
}

void App_Light_Solid_On_Show(void )
{
    switch(solidOnPara.brightness)
    {
        case BRIGHTNESS_25:
        {
            solidOnPara.lightColor.rVal = solidOnPara.lightColor.rVal / 4;
            solidOnPara.lightColor.gVal = solidOnPara.lightColor.gVal / 4;
            solidOnPara.lightColor.bVal = solidOnPara.lightColor.bVal / 4;
            break;
        }
        case BRIGHTNESS_50:
        {
            solidOnPara.lightColor.rVal = solidOnPara.lightColor.rVal / 2;
            solidOnPara.lightColor.gVal = solidOnPara.lightColor.gVal / 2;
            solidOnPara.lightColor.bVal = solidOnPara.lightColor.bVal / 2;
            break;
        }
        case BRIGHTNESS_75:
        {
            solidOnPara.lightColor.rVal = solidOnPara.lightColor.rVal * 3 / 4;
            solidOnPara.lightColor.gVal = solidOnPara.lightColor.gVal * 3 / 4;
            solidOnPara.lightColor.bVal = solidOnPara.lightColor.bVal * 3 / 4;
            break;
        }
        case BRIGHTNESS_100:
        default: break;
    }

    Drv_Light_Set_All_On(solidOnPara.lightColor.rVal, solidOnPara.lightColor.gVal, solidOnPara.lightColor.bVal);
}

void App_Light_Switch(uint8_t lightMode )
{
    switch((light_mode_t )lightMode)
    {
        case LIGHT_OFF:
        {
            break;
        }
        case LIGHT_COLOR_STREAM:
        {
            break;
        }
        case LIGHT_SOLID_ON:
        {
            App_Light_Solid_On_Para_Init();

            App_Light_Solid_On_Show();

            light_show_callback = NULL;
            break;
        }
        case LIGHT_BREATH:
        {
            break;
        }
        case LIGHT_NEON:
        {
            break;
        }
        case LIGHT_FLASH:
        {
            break;
        }
        case LIGHT_MONOCHROMATIC_DRAG:
        {
            break;
        }
        case LIGHT_REACTION:
        {
            break;
        }
        case LIGHT_CHROMATIC_DRAG:
        {
            break;
        }
        default: break;
    }
}

