#ifndef _HAL_MOUSE_SENSOR_H
#define _HAL_MOUSE_SENSOR_H

#include "hal_bat32g157.h"

void Hal_Mouse_Sensor_Spi_Init(void );
void Hal_Mouse_Sensor_Spi_Start(void );
void Hal_Mouse_Sensor_Spi_Stop(void );
void Hal_Mouse_Sensor_Spi_Write_One_Data(uint8_t dat );
uint8_t Hal_Mouse_Sensor_Spi_Read_One_Data(void );

#endif 

