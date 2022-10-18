#ifndef _HAL_KEY_H
#define _HAL_KEY_H

#include "hal_bat32g157.h"

void Hal_Key_Init(void );
uint8_t Hal_Key_Get_Value(PORT_TypeDef port, PIN_TypeDef pin );

#endif 

