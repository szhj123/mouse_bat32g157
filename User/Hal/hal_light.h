#ifndef _HAL_LIGHT_H
#define _HAL_LIGHT_H

#include "hal_bat32g157.h"

void Hal_Light_Gpio_Init(void );
void Hal_Light_Pwm_Init(void );
void Hal_Light_Pwm_Start(void );
void Hal_Light_Pwm_Stop(void );

void Hal_Light_Pwm_Set_Duty(uint8_t rDuty, uint8_t gDuty, uint8_t bDuty );
void Hal_Light_Gpio_Set(PORT_TypeDef port, PIN_TypeDef pin );
void Hal_Light_Gpio_Clr(PORT_TypeDef port, PIN_TypeDef pin );

#endif 

