/********************************************************
* @file       drv_mouse_sensor.c
* @author     szhj13
* @version    V1.0
* @date       2022-05-18
* @brief      the start address of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "drv_mouse_sensor.h"
/* Private typedef --------------------------------------*/
/* Private define ---------------------------------------*/
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
/* Private variables ------------------------------------*/

void Drv_Mouse_Sensor_Init(void )
{
    static uint8_t mSensorId = 0;
    
    Hal_Mouse_Sensor_Spi_Init();

    Drv_Mouse_Sensor_Write(0x3A,0x5A);  

    Drv_Mouse_Sensor_Delay_Ms(5);

    //Drv_Mouse_Sensor_Write(0x7F,0x12);  
	//Drv_Mouse_Sensor_Write(0x47,0x00);
	//Drv_Mouse_Sensor_Write(0x7F,0x00);
	//Drv_Mouse_Sensor_Write(0x18,0x00);
	//Drv_Mouse_Sensor_Write(0x40,0x80);
	//Drv_Mouse_Sensor_Write(0x55,0x01);

    Drv_Mouse_Sensor_Delay_Ms(1);
    while(1)
    {
    mSensorId = Drv_Mouse_Sensor_Read(0x00);
    }
}

void Drv_Mouse_Sensor_Write(uint8_t addr, uint8_t regVal )
{
    Hal_Mouse_Sensor_Spi_Start();

    Hal_Mouse_Sensor_Spi_Write_One_Data(addr | 0x80);

    Drv_Mouse_Sensor_Delay_Us(1);
    
    Hal_Mouse_Sensor_Spi_Write_One_Data(regVal);

    Drv_Mouse_Sensor_Delay_Us(1);

    Hal_Mouse_Sensor_Spi_Stop();
    
    Drv_Mouse_Sensor_Delay_Us(5);
}

uint8_t Drv_Mouse_Sensor_Read(uint8_t addr )
{
    uint8_t regVal = 0x00;
    
    Hal_Mouse_Sensor_Spi_Start();

    Drv_Mouse_Sensor_Delay_Us(1);

    Hal_Mouse_Sensor_Spi_Write_One_Data(addr & 0x7f);

    Drv_Mouse_Sensor_Delay_Us(2);

    regVal = Hal_Mouse_Sensor_Spi_Read_One_Data();
    
    Drv_Mouse_Sensor_Delay_Us(1);
    
    Hal_Mouse_Sensor_Spi_Stop();
    
    Drv_Mouse_Sensor_Delay_Us(10);

    return regVal;
}

void Drv_Mouse_Sensor_Delay_Ms(uint32_t ms )
{    
    if(ms <= 0)
    {
        return ;
    }

    while(ms--)
    {
        Drv_Mouse_Sensor_Delay_Us(1000);
    }
}

void Drv_Mouse_Sensor_Delay_Us(uint32_t us )
{    
    uint8_t delayCnt = 30;

    if(us <= 0)
    {
        return ;
    }

    while(us--)
    {
        while(delayCnt--);
    }
}

