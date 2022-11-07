#ifndef _APP_RGB_H
#define _APP_RGB_H

#include "drv_rgb.h"

typedef struct _rgb_ctrl_block_t
{
    PORT_TypeDef port;
    PIN_TypeDef  pin;

    uint8_t      rVal;
    uint8_t      gVal;
    uint8_t      bVal;
    
}rgb_ctrl_block_t;

typedef enum _rgb_mode_t
{
    RGB_OFF = 0,
    RGB_COLOR_STREAM,
    RGB_SOLID_ON,
    RGB_BREATH,
    RGB_NEON,
    RGB_FLASH,
    RGB_MONOCHROMATIC_DRAG,
    RGB_REACTION,
    RGB_CHROMATIC_DRAG
}rgb_mode_t;

void App_Rgb_Init(void );

#endif 

