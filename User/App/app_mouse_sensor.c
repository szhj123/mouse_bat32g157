/********************************************************
* @file       app_mouse_sensor.c
* @author     szhj13
* @version    V1.0
* @date       2022-05-18
* @brief      the start address of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "app_mouse_sensor.h"
#include "app_mouse_protocol.h"
#include "app_key.h"
/* Private typedef --------------------------------------*/
/* Private define ---------------------------------------*/
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
/* Private variables ------------------------------------*/
mouse_sensor_ctrl_block_t mouseSensorCtrl;

void App_Mouse_Sensor_Init(void )
{
    Drv_Mouse_Sensor_Init();

    Drv_Timer_Regist_Period(0, 1, App_Mouse_Sensor_Monitor, NULL);
}

void App_Mouse_Sensor_Monitor(void *arg )
{
    uint8_t motion;
    
    Drv_Mouse_Sensor_Get_Motion(mouseSensorCtrl.burstMotionData, sizeof(mouseSensorCtrl.burstMotionData));

    motion = mouseSensorCtrl.burstMotionData[0];

    if(motion & 0x80)
    {
        mouseSensorCtrl.deltaX = (uint16_t )mouseSensorCtrl.burstMotionData[3] << 8 | mouseSensorCtrl.burstMotionData[2];
        mouseSensorCtrl.deltaY = (uint16_t )mouseSensorCtrl.burstMotionData[5] << 8 | mouseSensorCtrl.burstMotionData[4];
    }
    else
    {
        mouseSensorCtrl.deltaX = 0;

        mouseSensorCtrl.deltaY = 0;
    }

    if(mouseSensorCtrl.deltaX != 0 || mouseSensorCtrl.deltaY != 0)
    {
        App_Key_Mouse_Motion(mouseSensorCtrl.deltaX, mouseSensorCtrl.deltaY);
    }
}

void App_Mouse_Sensor_Set_Report_Interval_Time(void )
{
    uint16_t mReportRate = App_Mouse_Get_Report_Rate();

    mouseSensorCtrl.delayTime = 1000 / mReportRate;
}

uint16_t App_Mouse_Sensor_Get_Report_Interva_Time(void )
{
    return mouseSensorCtrl.delayTime;
}

