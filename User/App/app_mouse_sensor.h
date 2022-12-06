#ifndef _APP_MOUSE_SENSOR_H
#define _APP_MOUSE_SENSOR_H

#include "drv_mouse_sensor.h"
#include "drv_timer.h"

typedef struct _mouse_sensor_ctrl_block_t
{
    uint8_t burstMotionData[6];
    int16_t deltaX;
    int16_t deltaY;

    uint16_t delayCnt;
    uint16_t delayTime;
}mouse_sensor_ctrl_block_t;

void App_Mouse_Sensor_Init(void );
void App_Mouse_Sensor_Set_Report_Interval_Time(void );
uint16_t App_Mouse_Sensor_Get_Report_Interva_Time(void );
void App_Mouse_Sensor_Monitor(void *arg );

uint32_t App_Mouse_Sensor_Get_Cpi_Value(uint8_t regVal );
void App_Mouse_Sensor_Set_Cpi_Value(uint32_t cpiVal );

#endif 

