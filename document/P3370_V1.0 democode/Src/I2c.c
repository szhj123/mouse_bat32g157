/*****************************************************************************
 *   i2c.c:  I2C C file for NXP LPC11xx Family Microprocessors
 *
 *   Copyright(C) 2008, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2009.12.07  ver 1.00    Preliminary version, first Release
 *
*****************************************************************************/
#define __I2C_C__

#include "LPC11Uxx.h"
#include "I2c.h"
#include "Main.h"
#include "Uart.h"
#include "SSP.h"

/* 
From device to device, the I2C communication protocol may vary, 
in the example below, the protocol uses repeated start to read data from or 
write to the device:
For master read: the sequence is: STA,Addr(W),offset,RE-STA,Addr(r),data...STO 
for master write: the sequence is: STA,Addr(W),offset,RE-STA,Addr(w),data...STO
Thus, in state 8, the address is always WRITE. in state 10, the address could 
be READ or WRITE depending on the I2C command.
*/   

/*****************************************************************************
** Function name:		I2C_IRQHandler
**
** Descriptions:		I2C interrupt handler, deal with master mode only.
**
** parameters:			None
** Returned value:		None
** 
*****************************************************************************/
void I2C_IRQHandler(void) 
{
	U8 StatValue;

	/* this handler deals with master read and master write only */
	StatValue = LPC_I2C->STAT;
	_DEBUG_I2C_(xprintf("\r\n StatValue=%x",StatValue));

	switch(StatValue)
	{
		case 0x08:/* A Start condition is issued. */
		g_I2C_Setting.WrIndex = 0;
		LPC_I2C->DAT = g_I2C_Setting.I2CDeviceAdr;	
		LPC_I2C->CONCLR = I2CONCLR_STAC;		
		g_I2C_Setting.I2CMasterState = I2C_DEVICEARD;
		break;
	
		case 0x10:/* A repeated started is issued */
		g_I2C_Setting.RdIndex = 0;
		/* Send SLA with R bit set, */
		LPC_I2C->DAT = AT24C512_ADDR|READ_STATUS;
		LPC_I2C->CONCLR = I2CONCLR_STAC;
		g_I2C_Setting.I2CMasterState = I2C_RESTARTED;
		break;
	
		case 0x18:/* Regardless, it's a ACK */
		if(g_I2C_Setting.I2CMasterState == I2C_DEVICEARD)
		{
			g_I2C_Setting.I2CMasterState = I2C_FWORDARD;	
			LPC_I2C->DAT = (g_I2C_Setting.I2CWordAdr & 0xFF00) >> 8;					
		}	
		break; 

		case 0x28:/* Data byte has been transmitted, regardless ACK or NACK */		
		if(g_I2C_Setting.I2CMasterState == I2C_FWORDARD)
		{
			LPC_I2C->DAT = (g_I2C_Setting.I2CWordAdr & 0x00FF) >> 0;				
			g_I2C_Setting.I2CMasterState = I2C_SWORDARD; 			
			break;
		}
		
             if(g_I2C_Setting.I2CBusState == I2C_BUS_WRITE)
		{
			if(g_I2C_Setting.I2CMasterState == I2C_SWORDARD)
			{
				g_I2C_Setting.I2CMasterState = DATA_ACK; 			
				LPC_I2C->DAT = g_I2C_Setting.I2CMasterBuffer[g_I2C_Setting.WrIndex];
				g_I2C_Setting.WrIndex++;			
				break;
			}		
		}
		else
		{
			if(g_I2C_Setting.I2CBusState == I2C_BUS_READ)
			{
				LPC_I2C->CONSET = I2CONSET_STA;/* Set Repeated-start flag */
				g_I2C_Setting.I2CMasterState = I2C_REPEATED_START; 
				break;
			}
		}
			 
		case 0x30:
		if(g_I2C_Setting.WrIndex < g_I2C_Setting.I2CWriteLength)
		{   
			LPC_I2C->DAT = g_I2C_Setting.I2CMasterBuffer[g_I2C_Setting.WrIndex];/* this should be the last one */
			g_I2C_Setting.WrIndex++;
			g_I2C_Setting.I2CMasterState = DATA_ACK; 
		}
		else
		{
			if(g_I2C_Setting.I2CReadLength != 0)
			{
				LPC_I2C->CONSET = I2CONSET_STA;/* Set Repeated-start flag */
				g_I2C_Setting.I2CMasterState = I2C_REPEATED_START; 
			}
			else
			{
				g_I2C_Setting.I2CMasterState = DATA_NACK;
				LPC_I2C->CONSET = I2CONSET_STO;/* Set Stop flag */
			}
		}		
		break;
	
		case 0x40:/* Master Receive, SLA_R has been sent */
		if(g_I2C_Setting.I2CReadLength == 1)
		{
			/* Will go to State 0x58 */
			LPC_I2C->CONCLR = I2CONCLR_AAC;/* assert NACK after data is received */
		}
		else
		{
			/* Will go to State 0x50 */
			LPC_I2C->CONSET = I2CONSET_AA;/* assert ACK after data is received */
		}		
		break;
	
		case 0x50:/* Data byte has been received, regardless following ACK or NACK */
		g_I2C_Setting.I2CSlaveBuffer[g_I2C_Setting.RdIndex] = LPC_I2C->DAT;
		g_I2C_Setting.RdIndex++;
		
		if(g_I2C_Setting.RdIndex < g_I2C_Setting.I2CReadLength)
		{   
			g_I2C_Setting.I2CMasterState = DATA_ACK;
			LPC_I2C->CONSET = I2CONSET_AA;/* assert ACK after data is received */
		}
		else
		{
			g_I2C_Setting.I2CMasterState = DATA_NACK;
			LPC_I2C->CONCLR = I2CONCLR_AAC;/* assert NACK on last byte */
		}		
		break;
	
		case 0x58:
		g_I2C_Setting.I2CSlaveBuffer[g_I2C_Setting.RdIndex] = LPC_I2C->DAT;
		g_I2C_Setting.RdIndex++;
		g_I2C_Setting.I2CMasterState = DATA_NACK;
		LPC_I2C->CONSET = I2CONSET_STO;/* Set Stop flag */ 
		LPC_I2C->CONCLR = I2CONCLR_SIC;/* Clear SI flag */
		break;

		case 0x20:/* regardless, it's a NACK */
		case 0x48:		
		g_I2C_Setting.I2CMasterState = DATA_NACK;
		break;
	
		case 0x38:/* Arbitration lost, in this example, we don't
		deal with multiple master situation */
		default:		
		break;
	}

	LPC_I2C->CONCLR = I2CONCLR_SIC;	
}

/*****************************************************************************
** Function name:		I2CStart
**
** Descriptions:		Create I2C start condition, a timeout
**				value is set if the I2C never gets started,
**				and timed out. It's a fatal error. 
**
** parameters:			None
** Returned value:		true or false, return false if timed out
** 
*****************************************************************************/
Boolean NDrv_API_I2C_Start(void)
{
	U32 Timeout = 0;
	U8 retVal = FALSE;

	LPC_I2C->CONCLR = I2CONCLR_AAC | I2CONCLR_SIC | I2CONCLR_STAC | I2CONCLR_I2ENC;  
	/*--- Issue a start condition ---*/
	LPC_I2C->CONSET = I2CONSET_STA|I2CONSET_I2EN;/* Set Start flag */       
	/*--- Wait until START transmitted ---*/
	while(1)
	{
		if(g_I2C_Setting.I2CMasterState == I2C_DEVICEARD)
		{    
			retVal = TRUE;
			break;	
		}
		
		if(Timeout >= MAX_TIMEOUT )
		{
			retVal = FALSE;
			break;
		}
		Timeout++;
	}	
	return(retVal);
}

/*****************************************************************************
** Function name:		I2CStop
**
** Descriptions:		Set the I2C stop condition, if the routine
**				never exit, it's a fatal bus error.
**
** parameters:			None
** Returned value:		true or never return
** 
*****************************************************************************/
void NDrv_API_I2C_Stop(void)
{
	LPC_I2C->CONSET = I2CONSET_STO|I2CONSET_I2EN;/* Set Stop flag */ 
	LPC_I2C->CONCLR = I2CONCLR_SIC|I2CONCLR_STAC|I2CONCLR_AAC;/* Clear SI flag */ 

	/*--- Wait for STOP detected ---*/
	while( LPC_I2C->CONSET & I2CONSET_STO ){}  
}

/*****************************************************************************
** Function name:		I2CInit
**
** Descriptions:		Initialize I2C controller
**
** parameters:			I2c mode is either MASTER or SLAVE
** Returned value:		true or false, return false if the I2C
**				interrupt handler was not installed correctly
** 
*****************************************************************************/
void nsAPI_I2C_Init(void) 
{
	NVIC_DisableIRQ(I2C_IRQn);   

	g_I2C_Setting.I2CMasterState = I2C_IDLE;
	g_I2C_Setting.I2CBusState = I2C_BUS_IDLE;
	g_I2C_Setting.I2CReadLength = 0;
	g_I2C_Setting.I2CWriteLength = 0;
	g_I2C_Setting.RdIndex = 0;
	g_I2C_Setting.WrIndex = 0;
	
	/* It seems to be bit0 is for I2C, different from
	UM. To be retested along with SSP reset. SSP and I2C
	reset are overlapped, a known bug, for now, both SSP 
	and I2C use bit 0 for reset enable. Once the problem
	is fixed, change to "#if 1". */
#if 1
	LPC_SYSCON->PRESETCTRL |= BIT1;
#else
	LPC_SYSCON->PRESETCTRL |= BIT0;
#endif
	LPC_SYSCON->SYSAHBCLKCTRL |= BIT5;
	LPC_IOCON->PIO0_4 &= ~0x3F;/* I2C I/O config */
	LPC_IOCON->PIO0_4 |= BIT0;/*  I2C SCL */
	LPC_IOCON->PIO0_5 &= ~0x3F;	
	LPC_IOCON->PIO0_5 |= BIT0;/* I2C SDA */
	
	/*--- Clear flags ---*/
	LPC_I2C->CONCLR = I2CONCLR_AAC | I2CONCLR_SIC | I2CONCLR_STAC | I2CONCLR_I2ENC; 
	LPC_I2C->SCLL = I2SCLL_SCLL;
	LPC_I2C->SCLH = I2SCLH_SCLH;
	LPC_I2C->ADR0 = AT24C512_ADDR; 
	/* Enable the I2C Interrupt */
	NVIC_EnableIRQ(I2C_IRQn);
	
}


void nsAPI_I2C_Write(void)
{
      U8 u8Brk = 1; 
 
	g_I2C_Setting.I2CDeviceAdr = AT24C512_ADDR;     
	g_I2C_Setting.I2CMasterState = I2C_IDLE;		

	if(NDrv_API_I2C_Start() != TRUE)
	{	   
		NDrv_API_I2C_Stop();
		return;
	}

	while(u8Brk)
	{	 
		if(g_I2C_Setting.I2CMasterState == DATA_NACK)
		{	
			u8Brk = 0;
			NDrv_API_I2C_Stop();			
		}
	} 
}

void nsAPI_I2C_Read(void)
{
	g_I2C_Setting.I2CDeviceAdr = AT24C512_ADDR|READ_STATUS;  
	g_I2C_Setting.I2CMasterState = I2C_IDLE;	
	g_I2C_Setting.RdIndex = 0;		

	if(NDrv_API_I2C_Start() != TRUE)
	{	   
		NDrv_API_I2C_Stop();
		return;
	}

	while(1)
	{	 
		if(g_I2C_Setting.I2CMasterState == DATA_NACK)
		{		
			NDrv_API_I2C_Stop();
			break;
		}
	} 
}

void nsAPI_I2C_Write_Database(U16 u16Adr,U8 *pBuf)
{	
	g_I2C_Setting.I2CWordAdr = u16Adr;/*Word Address*/  
	g_I2C_Setting.I2CBusState = I2C_BUS_WRITE;
	g_I2C_Setting.I2CMasterBuffer[GIdx0] = *pBuf;/*Data*/ 

	g_I2C_Setting.I2CWriteLength = GIdx1;

	nsAPI_I2C_Write();
}

RetU8 nsAPI_I2C_Read_Database(U16 u16Adr)
{	
	g_I2C_Setting.I2CWordAdr = u16Adr;/*Word Address*/ 	
	g_I2C_Setting.I2CBusState = I2C_BUS_READ;		
	g_I2C_Setting.I2CWriteLength = GIdx0;

	nsAPI_I2C_Write();	
	//nsAPI_SSP_Delsy1us(1000);/*1ms*/	

	_DEBUG_I2C_(xprintf("\r\n buf=%x",g_I2C_Setting.I2CSlaveBuffer[0]));	

	return (g_I2C_Setting.I2CSlaveBuffer[0]);
}


