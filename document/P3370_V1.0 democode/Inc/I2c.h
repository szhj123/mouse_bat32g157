/*****************************************************************************
 *   i2c.h:  Header file for NXP LPC11xx Family Microprocessors
 *
 *   Copyright(C) 2006, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2006.07.19  ver 1.00    Preliminary version, first Release
 *
******************************************************************************/
#ifndef __I2C_H__ 
#define __I2C_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "Type.h"

#ifdef  __I2C_C__
#define INTERFACE
#else
#define INTERFACE extern
#endif

#if 0
#define _DEBUG_I2C_(x) x
#else
#define _DEBUG_I2C_(x) 
#endif

#define I2CBUFSIZE 4
#define MAX_TIMEOUT 0x00FFFFFF

#define AT24C512_ADDR 0xA0
#define READ_STATUS 0x01

#define I2C_BUS_IDLE 0
#define I2C_BUS_WRITE 1
#define I2C_BUS_READ 2

#define I2C_IDLE 0
#define I2C_DEVICEARD 1
#define I2C_FWORDARD 2
#define I2C_SWORDARD 3
#define I2C_RESTARTED 4
#define I2C_REPEATED_START 5
#define DATA_ACK 6
#define DATA_NACK 7

#define I2CONSET_I2EN BIT6/* I2C Control Set Register */
#define I2CONSET_AA BIT2
#define I2CONSET_SI BIT3
#define I2CONSET_STO BIT4
#define I2CONSET_STA BIT5

#define I2CONCLR_AAC BIT2/* I2C Control clear Register */
#define I2CONCLR_SIC BIT3
#define I2CONCLR_STAC BIT5
#define I2CONCLR_I2ENC BIT6

#define I2C_SPEED 400000UL//400K
#define I2SCLH_SCLH (SystemCoreClock / I2C_SPEED) / 2/* I2C SCL Duty Cycle High Reg */
#define I2SCLL_SCLL I2SCLH_SCLH/* I2C SCL Duty Cycle Low Reg */

typedef struct _LPC11Uxx_I2C_Setting_
{	
	U8 I2CMasterState;
	U8 I2CDeviceAdr;
	U8 I2CBusState;		
	U8 I2CMasterBuffer[I2CBUFSIZE];
	U8 I2CSlaveBuffer[I2CBUFSIZE];
	U8 I2CReadLength;
	U8 I2CWriteLength;	
	U8 RdIndex;
	U8 WrIndex;	
	U16 I2CWordAdr;
} LPC11Uxx_I2C_Setting;

INTERFACE LPC11Uxx_I2C_Setting g_I2C_Setting;

INTERFACE void I2C_IRQHandler(void);
INTERFACE void nsAPI_I2C_Init(void);
INTERFACE void NDrv_API_I2C_Stop(void);
INTERFACE void nsAPI_I2C_Write(void);
INTERFACE void nsAPI_I2C_Read(void);
INTERFACE void nsAPI_I2C_Write_Database(U16 u16Adr,U8 *pBuf);
INTERFACE RetU8 nsAPI_I2C_Read_Database(U16 u16Adr);

#undef INTERFACE
#ifdef __cplusplus
}
#endif
#endif /* end __I2C_H */

