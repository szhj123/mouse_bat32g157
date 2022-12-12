#ifndef _APP_LIGHT_H
#define _APP_LIGHT_H

#include "app_mouse_protocol.h"
#include "drv_light.h"
#include "drv_task.h"
#include "drv_timer.h"

typedef enum _light_mode_t
{
    LIGHT_OFF = 0,
    LIGHT_RAINBOW,
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

typedef struct _rainbow_para_t
{
    uint8_t speed;
    uint8_t direction;
    uint8_t  lightIndex;
    uint16_t delayTime;
}rainbow_para_t;

typedef struct _solid_on_para_t
{
    brightness_t brightness;
    light_color_t lightColor;
}solid_on_para_t;

typedef struct _breath_para_t
{
    uint8_t speed;
    uint8_t lightColorIndex;    
    uint8_t breathDirecton;
    uint8_t brightnessStep; 
    uint16_t delayTime;
    light_color_t lightColor;
    light_color_t lightColorBuf[7];
}breath_para_t;

typedef struct _neon_para_t
{
    uint8_t speed;
    uint16_t delayTime;
    light_t light;
}neon_para_t;

typedef struct _flash_para_t
{
    uint8_t  lightColorFlag;
    uint8_t  lightIndex;
    uint16_t delayTime;
    light_color_t lightColorBuf[2];
}flash_para_t;

typedef struct _monochroma_para_t
{
    uint8_t speed;
    uint8_t direction;
    uint8_t lightIndex;
    uint8_t lightFlag;
    uint16_t delayTime;
    light_color_t lightColor;
}monochroma_para_t;

void App_Light_Init(void );
void App_Ligth_Delay_Count(void );
void App_Light_Clr_Delay_Count(void );
uint16_t App_Light_Get_Delay_Count(void );

void App_Light_Switch(void *arg );
void App_Light_Off(void );
void App_Light_Rainbow(void );
void App_Light_Solid_On(void );
void App_Light_Breath(void );
void App_Light_Neon(void );
void App_Light_Flash(void );
void App_Light_Monochroma_Drag(void );

void App_Light_Dpi(light_color_t dpiColor );

#endif 

