#ifndef _APP_LIGHT_H
#define _APP_LIGHT_H

#include "app_mouse_protocol.h"
#include "drv_light.h"
#include "drv_task.h"

typedef enum _light_mode_t
{
    LIGHT_OFF = 0,
    LIGHT_COLOR_STREAM,
    LIGHT_SOLID_ON,
    LIGHT_BREATH,
    LIGHT_NEON,
    LIGHT_FLASH,
    LIGHT_MONOCHROMATIC_DRAG,
    LIGHT_REACTION,
    LIGHT_CHROMATIC_DRAG
}light_mode_t;

typedef enum 
{
    BRIGHTNESS_25 = 1, 
    BRIGHTNESS_50,
    BRIGHTNESS_75,
    BRIGHTNESS_100
}brightness_t;

typedef struct _solid_on_para_t
{
    brightness_t brightness;
    light_color_t lightColor;
}solid_on_para_t;

void App_Light_Init(void );
void App_Light_Switch(uint8_t lightMode );

void App_Light_Solid_On_Para_Init(void );
void App_Light_Solid_On_Show(void );

#endif 

