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


void App_Rgb_Init(void );

#endif 

