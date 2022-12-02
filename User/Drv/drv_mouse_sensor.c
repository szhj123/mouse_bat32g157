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
    Hal_Mouse_Sensor_Spi_Init();

    Drv_Mouse_Sensor_3370_Init();
}

void Drv_Mouse_Sensor_3370_Init(void )
{
    uint8_t VarA = 0;
    uint8_t VarB = 0;
    
    Drv_Mouse_Sensor_Write(0x3A,0x5A);  

    Drv_Mouse_Sensor_Delay_Ms(5);
	
	// sensor initialization
	Drv_Mouse_Sensor_Write(0x7F,0x12);  
	Drv_Mouse_Sensor_Write(0x47,0x00);
	Drv_Mouse_Sensor_Write(0x7F,0x00);
	Drv_Mouse_Sensor_Write(0x18,0x00);
	Drv_Mouse_Sensor_Write(0x40,0x80);
	Drv_Mouse_Sensor_Write(0x55,0x01);
	Drv_Mouse_Sensor_Delay_Ms(1);						//wait for 1ms
	Drv_Mouse_Sensor_Write(0x7F,0x0E);
	Drv_Mouse_Sensor_Write(0x43,0x1D);
	VarA = (Drv_Mouse_Sensor_Read(0x46)); 
	Drv_Mouse_Sensor_Write(0x43,0x1E);
	VarB = (Drv_Mouse_Sensor_Read(0x46)); 

	Drv_Mouse_Sensor_Write(0x7F,0x14);
	Drv_Mouse_Sensor_Write(0x6A,VarA);
	Drv_Mouse_Sensor_Write(0x6C,VarB);	
	
	Drv_Mouse_Sensor_Write(0x7F,0x00);
	Drv_Mouse_Sensor_Write(0x55,0x00);
	Drv_Mouse_Sensor_Write(0x4D,0x50);
	Drv_Mouse_Sensor_Write(0x4E,0x3B);
	Drv_Mouse_Sensor_Write(0x4F,0x46);
	Drv_Mouse_Sensor_Write(0x54,0x34);
	Drv_Mouse_Sensor_Write(0x77,0x24);

	Drv_Mouse_Sensor_Write(0x7F,0x05);
	Drv_Mouse_Sensor_Write(0x44,0xA8);
	Drv_Mouse_Sensor_Write(0x46,0x15); 
	Drv_Mouse_Sensor_Write(0x4A,0x14);
	Drv_Mouse_Sensor_Write(0x51,0x10);
	Drv_Mouse_Sensor_Write(0x53,0x0C); 
	Drv_Mouse_Sensor_Write(0x55,0xC9); 
	Drv_Mouse_Sensor_Write(0x5B,0xEA); 
	Drv_Mouse_Sensor_Write(0x61,0x13);
	Drv_Mouse_Sensor_Write(0x62,0x0B); 
	Drv_Mouse_Sensor_Write(0x64,0x18); 
	Drv_Mouse_Sensor_Write(0x6D,0x86);
	Drv_Mouse_Sensor_Write(0x7D,0x85);
	Drv_Mouse_Sensor_Write(0x7E,0x03);

	Drv_Mouse_Sensor_Write(0x7F,0x06);
	Drv_Mouse_Sensor_Write(0x60,0xB0);
	Drv_Mouse_Sensor_Write(0x61,0x00);
	Drv_Mouse_Sensor_Write(0x6D,0x29);
	Drv_Mouse_Sensor_Write(0x6E,0x23);
	Drv_Mouse_Sensor_Write(0x7E,0x40);
	
	Drv_Mouse_Sensor_Write(0x7F,0x07);
	Drv_Mouse_Sensor_Write(0x42,0x15);
	
	Drv_Mouse_Sensor_Write(0x7F,0x08);
	Drv_Mouse_Sensor_Write(0x42,0x28);
	Drv_Mouse_Sensor_Write(0x43,0x32);
	
	Drv_Mouse_Sensor_Write(0x7F,0x09);
	Drv_Mouse_Sensor_Write(0x40,0x03);
	
	Drv_Mouse_Sensor_Write(0x7F,0x0A);
	Drv_Mouse_Sensor_Write(0x4A,0x28);
	Drv_Mouse_Sensor_Write(0x4C,0x28); 
	Drv_Mouse_Sensor_Write(0x49,0x00);
	Drv_Mouse_Sensor_Write(0x4F,0x02);

	Drv_Mouse_Sensor_Write(0x7F,0x0C);
	Drv_Mouse_Sensor_Write(0x40,0x90);
	Drv_Mouse_Sensor_Write(0x41,0x50);
	Drv_Mouse_Sensor_Write(0x42,0x0C);
	Drv_Mouse_Sensor_Write(0x43,0xA8);
	Drv_Mouse_Sensor_Write(0x44,0x47);
	Drv_Mouse_Sensor_Write(0x45,0x01);
	Drv_Mouse_Sensor_Write(0x4D,0x4F);
	Drv_Mouse_Sensor_Write(0x4E,0x1B);
	Drv_Mouse_Sensor_Write(0x54,0x00);
	Drv_Mouse_Sensor_Write(0x55,0x60);
	Drv_Mouse_Sensor_Write(0x56,0x60);
	Drv_Mouse_Sensor_Write(0x58,0x30);
	Drv_Mouse_Sensor_Write(0x59,0x63);

	Drv_Mouse_Sensor_Write(0x7F,0x0D);
	Drv_Mouse_Sensor_Write(0x4B,0x23);
	Drv_Mouse_Sensor_Write(0x4C,0x40);
	Drv_Mouse_Sensor_Write(0x4E,0x6B);
	Drv_Mouse_Sensor_Write(0x5E,0xC3);
	Drv_Mouse_Sensor_Write(0x4F,0x02);
	
	Drv_Mouse_Sensor_Write(0x7F,0x10);
	Drv_Mouse_Sensor_Write(0x45,0x1E);
	Drv_Mouse_Sensor_Write(0x46,0xF0);
	Drv_Mouse_Sensor_Write(0x48,0x0F);
	Drv_Mouse_Sensor_Write(0x49,0x88);
	Drv_Mouse_Sensor_Write(0x4C,0x15);
	Drv_Mouse_Sensor_Write(0x4F,0x00);
	Drv_Mouse_Sensor_Write(0x51,0x6F);
	Drv_Mouse_Sensor_Write(0x52,0x90);
	Drv_Mouse_Sensor_Write(0x54,0x64);
	Drv_Mouse_Sensor_Write(0x55,0xF0);
	Drv_Mouse_Sensor_Write(0x5C,0x40);
	Drv_Mouse_Sensor_Write(0x61,0xEE);
	Drv_Mouse_Sensor_Write(0x62,0xE5);
	
	Drv_Mouse_Sensor_Write(0x7F,0x14);
	Drv_Mouse_Sensor_Write(0x53,0x0C);
	Drv_Mouse_Sensor_Write(0x4A,0x67);
	Drv_Mouse_Sensor_Write(0x6D,0x20);
	Drv_Mouse_Sensor_Write(0x6E,0x00);
	Drv_Mouse_Sensor_Write(0x73,0x83);
	Drv_Mouse_Sensor_Write(0x74,0x00);
	Drv_Mouse_Sensor_Write(0x7A,0x16);
	Drv_Mouse_Sensor_Write(0x63,0x14);
	Drv_Mouse_Sensor_Write(0x62,0x14);

	Drv_Mouse_Sensor_Write(0x7F,0x00);
	Drv_Mouse_Sensor_Write(0x5B,0x40);
	Drv_Mouse_Sensor_Write(0x61,0xAD);
	Drv_Mouse_Sensor_Write(0x51,0xEA);
	Drv_Mouse_Sensor_Write(0x19,0x9F);
    
    Drv_Mouse_Sensor_Delay_Ms(10);

	Drv_Mouse_Sensor_Write(0x19,0x10);
	Drv_Mouse_Sensor_Write(0x61,0xD5);	
	Drv_Mouse_Sensor_Write(0x40,0x00);				
	Drv_Mouse_Sensor_Write(0x7F,0x00);
	Drv_Mouse_Sensor_Write(0x4D,0xD0);

    uint8_t u8InitTemp = 0;

	u8InitTemp = (Drv_Mouse_Sensor_Read(0x02));		
	u8InitTemp = (Drv_Mouse_Sensor_Read(0x03));
	u8InitTemp = (Drv_Mouse_Sensor_Read(0x04));
	u8InitTemp = (Drv_Mouse_Sensor_Read(0x05));
	u8InitTemp = (Drv_Mouse_Sensor_Read(0x06));
			
    Drv_Mouse_Sensor_Delay_Ms(10);	
}

void Drv_Mouse_Sensor_Write(uint8_t addr, uint8_t regVal )
{
    Hal_Mouse_Sensor_Spi_Start();
    
    Drv_Mouse_Sensor_Delay_Us(1);

    Hal_Mouse_Sensor_Spi_Write_One_Data(addr | 0x80);

    Hal_Mouse_Sensor_Spi_Write_One_Data(regVal);

    Drv_Mouse_Sensor_Delay_Us(1);

    Hal_Mouse_Sensor_Spi_Stop();
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
    
    return regVal;
}

void Drv_Mouse_Sensor_Get_Motion(uint8_t *buf, uint8_t length )
{
    uint8_t i;
    uint8_t regVal = 0x00;
    
    Hal_Mouse_Sensor_Spi_Start();
    
    Drv_Mouse_Sensor_Delay_Us(1);

    Hal_Mouse_Sensor_Spi_Write_One_Data(0x16);

    Drv_Mouse_Sensor_Delay_Us(2);

    for(i=0;i<length;i++)
    {
        buf[i] = Hal_Mouse_Sensor_Spi_Read_One_Data();
    }

    Drv_Mouse_Sensor_Delay_Us(1);

    Hal_Mouse_Sensor_Spi_Stop();
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

