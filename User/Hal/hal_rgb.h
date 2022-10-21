#ifndef _HAL_RGB_H
#define _HAL_RGB_H

#include "hal_bat32g157.h"

void Hal_Rgb_Gpio_Init(void );
void Hal_Rgb_Pwm_Init(void );
void Hal_Rgb_Pwm_Start(void );
void Hal_Rgb_Pwm_Stop(void );

void Hal_Rgb_Pwm_Set_Duty(uint8_t rDuty, uint8_t gDuty, uint8_t bDuty );
void Hal_Rgb_Gpio_Set(PORT_TypeDef port, PIN_TypeDef pin );
void Hal_Rgb_Gpio_Clr(PORT_TypeDef port, PIN_TypeDef pin );

#endif 

