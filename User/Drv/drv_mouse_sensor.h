#ifndef _DRV_MOUSE_SENSOR_H
#define _DRV_MOUSE_SENSOR_H

#include "hal_mouse_sensor.h"

void Drv_Mouse_Sensor_Init(void );
void Drv_Mouse_Sensor_3370_Init(void );
void Drv_Mouse_Sensor_Get_Motion(uint8_t *buf, uint8_t length );
void Drv_Mouse_Sensor_Write(uint8_t addr, uint8_t regVal );
uint8_t Drv_Mouse_Sensor_Read(uint8_t addr );


void Drv_Mouse_Sensor_Delay_Ms(uint32_t ms );
void Drv_Mouse_Sensor_Delay_Us(uint32_t us );

#endif 

