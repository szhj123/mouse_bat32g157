//------------------------------Software IIC Interface-----------------------------------------
#include <stdio.h>
#include "BAT32G157.h"
#include "sw_iic.h"


#define BIT_WIDTH 10//12*1
//#define SLAVER_ADDRESS 0xA0//0xA8

//set PC05 sda
#define SDA_DIR_OUTPUT() PORT->PMC &= ~(1<<5);\
						 PORT->PMCC &= ~(1<<5);
#define SDA_DIR_INPUT() PORT->PMC |= (1<<5);
#define SDA_HIGH() PORT->PSETC = (1<<5);
#define SDA_LOW() PORT->PCLRC = (1<<5);
#define SDA_PIN() (PORT->PREADC & (1<<5))
#define SDA_PULLUP() PORT->PUC |= (1<<5);
//set PC03 scl
#define SCL_DIR_OUTPUT() PORT->PMC &= ~(1<<3);\
						 PORT->PMCC &= ~(1<<3);
#define SCL_HIGH() PORT->PSETC = (1<<3);
#define SCL_LOW() PORT->PCLRC = (1<<3);

void DelayUs(uint32_t us)
{
	while(--us);
}

void IIC_Start(void)
{
	SDA_PULLUP()
	SCL_DIR_OUTPUT()
	SDA_DIR_OUTPUT()

	SDA_HIGH()
	SCL_HIGH()
	DelayUs(BIT_WIDTH);
	
	SDA_LOW()
	DelayUs(BIT_WIDTH);
	SCL_LOW()
}


void IIC_Stop(void)
{
	SDA_DIR_OUTPUT()

	SDA_LOW()
	SCL_LOW()
	
	DelayUs(BIT_WIDTH);
	
	SCL_HIGH()
	DelayUs(BIT_WIDTH);
	SDA_HIGH()
	
	
}

uint8_t IIC_WriteByte(uint8_t dat)
{
	uint8_t i;
	uint8_t ack = 0;
	
	for(i=0;i<8;i++)
	{
		SCL_LOW()
		if(dat & 0x80)
		{
			SDA_HIGH()
		}
		else
		{
			SDA_LOW()
		}
		DelayUs(BIT_WIDTH);
		
		SCL_HIGH()
		dat <<= 1;
		DelayUs(BIT_WIDTH+3);
	}
	
	//SDA_LOW()
	SCL_LOW()
	SDA_HIGH()
	DelayUs(BIT_WIDTH+3);
	//SDA_HIGH()
	SCL_HIGH()
	SDA_DIR_INPUT()
	DelayUs(BIT_WIDTH+3);
	//read ACK
	if(!SDA_PIN())
	{
		ack = 1;
	}
	SCL_LOW()
	SDA_DIR_OUTPUT()
	return ack;

}

uint8_t IIC_ReadByte(void)
{
	uint8_t i,dat;
	SDA_DIR_INPUT()
	SDA_HIGH()

	for(i=0;i<8;i++)
	{
		SCL_LOW()
                DelayUs(BIT_WIDTH);
                SCL_HIGH()
                dat <<= 1;
		if(SDA_PIN())
		{
                  dat++;
		}
		
		DelayUs(BIT_WIDTH+3);
	}
	
	//SDA_LOW()
	SCL_LOW()
	SDA_DIR_OUTPUT()

	SDA_LOW()//write ACK
	DelayUs(BIT_WIDTH+3);
	//SDA_HIGH()
	SCL_HIGH()
	DelayUs(BIT_WIDTH+3);
	
	SCL_LOW()
	
	return dat;

	
}

uint8_t IIC_ReadByte_Noack(void)
{
	uint8_t i,dat;
	SDA_DIR_INPUT()

	SDA_HIGH()

	for(i=0;i<8;i++)
	{
		SCL_LOW()
                DelayUs(BIT_WIDTH);
                SCL_HIGH()
                dat <<= 1;
		if(SDA_PIN())
		{
                  dat++;
		}
		
		DelayUs(BIT_WIDTH+3);
	}
	
	//SDA_LOW()
	SCL_LOW()
	SDA_DIR_OUTPUT()

	SDA_HIGH()//write ACK
	DelayUs(BIT_WIDTH+3);
	//SDA_HIGH()
	SCL_HIGH()
	DelayUs(BIT_WIDTH+3);
	
	SCL_LOW()
	
	return dat;
	
}

void IIC_Write_NByte(uint8_t devaddr,uint8_t* buf,uint8_t len)
{
	uint8_t i;
	
	IIC_Start();
	
	IIC_WriteByte(devaddr);
	  
	for(i=0;i<len;i++)
	{
		IIC_WriteByte(buf[i]);
	}
	
	IIC_Stop();
	
}

void IIC_Write(uint8_t devaddr,uint8_t regaddr,uint8_t* buf,uint8_t len)
{
	uint8_t i;
	
	IIC_Start();
	
	IIC_WriteByte(devaddr);
	IIC_WriteByte(regaddr);
        
	for(i=0;i<len;i++)
	{
		IIC_WriteByte(buf[i]);
	}
	
	IIC_Stop();
	
}

void IIC_Read(uint8_t devaddr,uint8_t regaddr,uint8_t* buf,uint8_t len)
{
	uint8_t i;
	
	IIC_Start();
	
	IIC_WriteByte(devaddr);
	IIC_WriteByte(regaddr);
        
    IIC_Start();
    IIC_WriteByte(devaddr|0x01);

	for(i=0;i<len-1;i++)
	{
		buf[i] = IIC_ReadByte();
	}
	buf[i] = IIC_ReadByte_Noack();
        
	IIC_Stop();
	
}
