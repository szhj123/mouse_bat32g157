#ifndef _DRV_LIGHT_H
#define _DRV_LIGHT_H

#include "hal_light.h"

typedef enum _light_state_t
{
    LIGHT_STATE_RED = 0,
    LIGHT_STATE_BLUE,
    LIGHT_STATE_GREEN
}light_state_t;

typedef struct _light_t
{
    PORT_TypeDef  port;
    PIN_TypeDef   pin;

    light_state_t lightState;

    uint8_t       rVal;
    uint8_t       gVal;
    uint8_t       bVal;
}light_t;

void Drv_Light_Init(void );
void Drv_Light_Set_On(light_t light );
void Drv_Light_Set_Off(light_t light );
void Drv_Light_Set_All_Off(void );
void Drv_Light_Set_All_On(uint8_t rVal, uint8_t gVal, uint8_t bVal );

#endif 

