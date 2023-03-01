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
    uint8_t regVal;
    
    Drv_Mouse_Sensor_Init();

    Drv_Timer_Regist_Period(500, 1, App_Mouse_Sensor_Monitor, NULL);

    regVal = App_Mouse_Get_Dpi_RegVal(App_Mouse_Get_Dpi_Index());

    App_Mouse_Sensor_Set_Cpi_Value(App_Mouse_Sensor_Get_Cpi_Value(regVal));
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
        if(Usb_Get_Suspend_Flag())
        {
            Usb_Wakeup();
        }
        
        App_Key_Mouse_Motion(mouseSensorCtrl.deltaX, mouseSensorCtrl.deltaY);
    }
}

uint32_t App_Mouse_Sensor_Get_Cpi_Value(uint8_t regVal )
{
    switch(regVal )
    {
        case 0x04: return 200;
	    case 0x06: return 300;
	    case 0x08: return 400;
     	case 0x0b: return 500;
     	case 0x0d: return 600;
     	case 0x0f: return 700;
     	case 0x12: return 800;
     	case 0x14: return 900;
     	case 0x16: return 1000;
     	case 0x19: return 1100;
     	case 0x1b: return 1200;
     	case 0x1d: return 1300;
     	case 0x20: return 1400;
     	case 0x22: return 1500;
     	case 0x24: return 1600;
     	case 0x27: return 1700;
     	case 0x29: return 1800;
     	case 0x2b: return 1900;
     	case 0x2e: return 2000;
     	case 0x30: return 2100;
     	case 0x32: return 2200;
     	case 0x34: return 2300;
     	case 0x37: return 2400;
     	case 0x39: return 2500;
     	case 0x3b: return 2600;
     	case 0x3e: return 2700;
     	case 0x40: return 2800;
     	case 0x42: return 2900;
     	case 0x45: return 3000;
     	case 0x47: return 3100;
     	case 0x49: return 3200;
     	case 0x4c: return 3300;
     	case 0x4e: return 3400;
     	case 0x50: return 3500;
     	case 0x53: return 3600;
     	case 0x55: return 3700;
     	case 0x57: return 3800;
     	case 0x5a: return 3900;
     	case 0x5c: return 4000;
     	case 0x5e: return 4100;
     	case 0x61: return 4200;
     	case 0x63: return 4300;
     	case 0x65: return 4400;
     	case 0x68: return 4500;
     	case 0x6a: return 4600;
    	case 0x6c: return 4700;
    	case 0x6f: return 4800;
    	case 0x71: return 4900;
    	case 0x73: return 5000;
    	case 0x45 | 0x80: return 6000;
    	case 0x50 | 0x80: return 7000;
    	case 0x5c | 0x80: return 8000;
    	case 0x68 | 0x80: return 9000;
    	case 0x73 | 0x80: return 10000;
        default: break;
    }
		
		return 3000;
}

void App_Mouse_Sensor_Set_Cpi_Value(uint32_t cpiVal )
{    
    if(cpiVal < 50)
        return ;
    
    if(cpiVal < 5000)
    {
        Drv_Mouse_Sensor_Write(0x5A,0x10);
    }
    else
    {
        Drv_Mouse_Sensor_Write(0x5A,0x90);
    }

    if(cpiVal <= 10000)
    {
        
        Drv_Mouse_Sensor_Write(0x4D,0x50);

        
        Drv_Mouse_Sensor_Write(0x4E,(cpiVal / 50) - 1);
    }
    else
    {
        Drv_Mouse_Sensor_Write(0x4D,0xD0);
        
        Drv_Mouse_Sensor_Write(0x4E,(cpiVal / 100) - 1);
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

