/****************************************************************************
 *   $Id:: gpio.c 6874 2011-03-22 01:58:31Z usb00423                        $
 *   Project: NXP LPC11xx GPIO example
 *
 *   Description:
 *     This file contains GPIO code example which include GPIO
 *     initialization, GPIO interrupt handler, and related APIs for
 *     GPIO access.
 *
 ****************************************************************************
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * products. This software is supplied "AS IS" without any warranties.
 * NXP Semiconductors assumes no responsibility or liability for the
 * use of the software, conveys no license or title under any patent,
 * copyright, or mask work right to the product. NXP Semiconductors
 * reserves the right to make changes in the software without
 * notification. NXP Semiconductors also make no representation or
 * warranty that such application will be suitable for the specified
 * use without further testing or modification.
****************************************************************************/
#define __GPIO_C__

#include "Pixart_Sensor.h"

/*****************************************************************************
** Function name:		FLEX_INT0_IRQHandler
**
** Descriptions:		Use one GPIO pin as interrupt source
**
** parameters:			None
**
** Returned value:		None
**
*****************************************************************************/
void FLEX_INT0_IRQHandler(void)
{
	while(1){}
}

/*****************************************************************************
** Function name:		FLEX_INT1_IRQHandler
**
** Descriptions:		Use one GPIO pin as interrupt source
**
** parameters:			None
**
** Returned value:		None
**
*****************************************************************************/
void FLEX_INT1_IRQHandler(void)
{
	while(1){}
}

/*****************************************************************************
** Function name:		FLEX_INT2_IRQHandler
**
** Descriptions:		Use one GPIO pin as interrupt source
**
** parameters:			None
**
** Returned value:		None
**
*****************************************************************************/
void FLEX_INT2_IRQHandler(void)
{
	while(1){}
}

/*****************************************************************************
** Function name:		FLEX_INT3_IRQHandler
**
** Descriptions:		Use one GPIO pin as interrupt source
**
** parameters:			None
**
** Returned value:		None
**
*****************************************************************************/
void FLEX_INT3_IRQHandler(void)
{
	while(1){}
}

/*****************************************************************************
** Function name:		FLEX_INT4_IRQHandler
**
** Descriptions:		Use one GPIO pin as interrupt source
**
** parameters:			None
**
** Returned value:		None
**
*****************************************************************************/
void FLEX_INT4_IRQHandler(void)
{
	while(1){}
}

/*****************************************************************************
** Function name:		FLEX_INT5_IRQHandler
**
** Descriptions:		Use one GPIO pin as interrupt source
**
** parameters:			None
**
** Returned value:		None
**
*****************************************************************************/
void FLEX_INT5_IRQHandler(void)
{
	while(1){}
}

/*****************************************************************************
** Function name:		FLEX_INT6_IRQHandler
**
** Descriptions:		Use one GPIO pin as interrupt source
**
** parameters:			None
**
** Returned value:		None
**
*****************************************************************************/
void FLEX_INT6_IRQHandler(void)
{
	while(1){}
}

/*****************************************************************************
** Function name:		FLEX_INT7_IRQHandler
**
** Descriptions:		Use one GPIO pin as interrupt source
**
** parameters:			None
**
** Returned value:		None
**
*****************************************************************************/
void FLEX_INT7_IRQHandler(void)
{
	while(1){}
}

/*****************************************************************************
** Function name:		GINT0_IRQHandler
**
** Descriptions:		Use one GPIO pin as interrupt source
**
** parameters:			None
**
** Returned value:		None
**
*****************************************************************************/
void GINT0_IRQHandler(void)
{

/*
    // Falling edge detected
    if (LPC_GPIO_PIN_INT->FALL & (1 << 0))
    {
        // Clear interrupt
        LPC_GPIO_PIN_INT->FALL = (1 << 0);
    }

    // Rising edge detected
    if (LPC_GPIO_PIN_INT->RISE & (1 << 0))
    {
        // Clear interrupt
        LPC_GPIO_PIN_INT->RISE = (1 << 0);

    }
	*/
}

/*****************************************************************************
** Function name:		GINT1_IRQHandler
**
** Descriptions:		Use one GPIO pin as interrupt source
**
** parameters:			None
**
** Returned value:		None
**
*****************************************************************************/
void GINT1_IRQHandler(void)
{
	//while(1){}
}

/*****************************************************************************
** Function name:		nsAPI_GPIO_Init
**
** Descriptions:		Initialize GPIO, install the
**						GPIO interrupt handler
**
** parameters:			None
**
** Returned value:		true or false, return false if the VIC table
**						is full and GPIO interrupt handler can be
**						installed.
**
*****************************************************************************/
void nsAPI_GPIO_Init( void )
{
    g_GpioButtonEvent.ButtonEvent = 0;
    g_GpioButtonEvent.ButtonEventCount = 0;
    g_GpioButtonEvent.PreButtonEvent = 0;
    g_GpioButtonEvent.ButtonStatus = GPIO_SCANKEY_NULL;
    g_GpioButtonEvent.KeycodeTblIdx = 0;
    g_GpioButtonEvent.PreQIEStatus = QIE_STOP;

    // Enable AHB clock to the GPIO domain.
    LPC_SYSCON->SYSAHBCLKCTRL |= BIT6;

    // Enable AHB clock to the FlexInt, GroupedInt domain.
    LPC_SYSCON->SYSAHBCLKCTRL |= (BIT19| BIT23| BIT24);

	//Dennis: defining the SWD
	LPC_IOCON->SWDIO_PIO0_15 = 0x00000090;
	LPC_IOCON->SWCLK_PIO0_10 = 0x00000090;

 // UGS2 real hardware
//**************************************
// Project UGS 2
// USED GPIO
// UGS 2
// DLED 1  PORT 0 _20
// DLED 2  Port 1 _26
// DLED 3  Port 1 _27
// ZB Port 0 _7
// ZA Port 1 _28
// MOTION Port 1_31
// SN_RESET Pin Port 1_21
// SW3 Port 0 _11
// SW2 Port 0 _12
// SW1 Port 0 _13
// N_OE1 Port 1 _14
// DIR1 Port 0 _23
// BUTTON_RIGHT PIO1_15
// BUTTON_MID PIO0_17
// BUTTON_LEFT PIO0_18
// BUTTON_CPI_P PIO0_19
// BUTTON_CPI_M PIO1_16
//**************************************

//  EXT_CLK  PORT 0 _14
//	LPC_IOCON->PIO0_14 &= ~0x07;
//  LPC_IOCON->PIO0_14 |= BIT4;
//  NDrv_GPIO_SetDir(PORT0,14,GPIOIN);

	// ZB Port 0 _7
	LPC_IOCON->PIO0_7 &= ~0x07;
    LPC_IOCON->PIO0_7 |= BIT4;
    NDrv_GPIO_SetDir(PORT0,7,GPIOIN);

	// ZA Port 1 _28
	LPC_IOCON->PIO1_28 &= ~0x07;
    LPC_IOCON->PIO1_28 |= BIT4;
    NDrv_GPIO_SetDir(PORT1,28,GPIOIN);

	// MISO  PORT 0 _8
	LPC_IOCON->PIO0_8 &= ~0x07;
   // LPC_IOCON->PIO0_8 |= BIT4;
    NDrv_GPIO_SetDir(PORT0,8,GPIOIN);

	// DLED 1  PORT 0 _20
	LPC_IOCON->PIO0_20 &= ~0x07;
    LPC_IOCON->PIO0_20 |= BIT4;
    NDrv_GPIO_SetDir(PORT0,20,GPIOOUT);

	// DLED 2  Port 1 _26
	LPC_IOCON->PIO1_26 &= ~0x07;
    LPC_IOCON->PIO1_26 |= BIT4;
    NDrv_GPIO_SetDir(PORT1,26,GPIOOUT);

	// DLED 3  Port 1 _27
	LPC_IOCON->PIO1_27 &= ~0x07;
    LPC_IOCON->PIO1_27 |= BIT4;
    NDrv_GPIO_SetDir(PORT1,27,GPIOOUT);

	// MOTION Port 1_31 
	LPC_IOCON->PIO1_31 &= ~0x07;
    LPC_IOCON->PIO1_31 |= BIT4;
    NDrv_GPIO_SetDir(PORT1,31,GPIOIN);

	// SN_RESET Pin Port 1_21 
	LPC_IOCON->PIO1_21 &= ~0x07;
    LPC_IOCON->PIO1_21 |= BIT4;
    NDrv_GPIO_SetDir(PORT1,21,GPIOOUT);

	// SW3 Port 0 _11
	LPC_IOCON->TDI_PIO0_11 &= ~0x07;
    LPC_IOCON->TDI_PIO0_11 |= BIT4;
    NDrv_GPIO_SetDir(PORT0,11,GPIOOUT);
					
	// SW2 Port 0 _14
	LPC_IOCON->TRST_PIO0_14 &= ~0x07;
    LPC_IOCON->TRST_PIO0_14 |= BIT4;
    NDrv_GPIO_SetDir(PORT0,14,GPIOOUT);

	// SW1 Port 0 _13
	LPC_IOCON->TDO_PIO0_13 &= ~0x07;
    LPC_IOCON->TDO_PIO0_13 |= BIT4;
    NDrv_GPIO_SetDir(PORT0,13,GPIOOUT);

    LPC_IOCON->TDI_PIO0_11 = 0x00000091;     // binary: 00000000_00000000_00000000_10010001 
    LPC_IOCON->TMS_PIO0_12 = 0x00000091;     // binary: 00000000_00000000_00000000_10010001 
    LPC_IOCON->TDO_PIO0_13 = 0x00000091;     // binary: 00000000_00000000_00000000_10010001 
	LPC_IOCON->TRST_PIO0_14 = 0x00000091;
	
	// N_OE1 Port 1 _14
	LPC_IOCON->PIO1_14 &= ~0x07;
    LPC_IOCON->PIO1_14 |= BIT4;
    NDrv_GPIO_SetDir(PORT1,14,GPIOOUT);

	// DIR1 Port 0 _23
//	LPC_IOCON->PIO0_23 &= ~0x07;
//  LPC_IOCON->PIO0_23 |= BIT4;
//  NDrv_GPIO_SetDir(PORT0,23,GPIOOUT);

	// BUTTON_RIGHT PIO1_15
	LPC_IOCON->PIO1_15 &= ~0x07;
    LPC_IOCON->PIO1_15 |= BIT4;
    NDrv_GPIO_SetDir(PORT1,15,GPIOIN);

	// BUTTON_MID PIO0_17
	LPC_IOCON->PIO0_17 &= ~0x07;
    LPC_IOCON->PIO0_17 |= BIT4;
    NDrv_GPIO_SetDir(PORT0,17,GPIOIN);

	// BUTTON_LEFT PIO0_18
	LPC_IOCON->PIO0_18 &= ~0x07;
    LPC_IOCON->PIO0_18 |= BIT4;
    NDrv_GPIO_SetDir(PORT0,18,GPIOIN);

	// BUTTON_CPI_P PIO0_19
	LPC_IOCON->PIO0_19 &= ~0x07;
    LPC_IOCON->PIO0_19 |= BIT4;
    NDrv_GPIO_SetDir(PORT0,19,GPIOIN);

	// BUTTON_CPI_M PIO1_16
	LPC_IOCON->PIO1_16 &= ~0x07;
    LPC_IOCON->PIO1_16 |= BIT4;
    NDrv_GPIO_SetDir(PORT1,16,GPIOIN);

	// NCS SPI PIO0_2
	LPC_IOCON->PIO0_2 &= ~0x07;
	LPC_IOCON->PIO0_2 |= BIT4;
	NDrv_GPIO_SetDir(PORT0,2,GPIOOUT);
}

/*****************************************************************************
** Function name:		NDrv_GPIO_SetBitValue
**
** Descriptions:		Set/clear a bit in a specific position
**
** parameters:			port num, bit position, bit value
**
** Returned value:		None
**
*****************************************************************************/
void NDrv_GPIO_SetBitValue( U32 portNum, U32 bitPosi, U32 bitVal )
{
	if(bitVal)
	LPC_GPIO->SET[portNum] = 1 << bitPosi;
	else
	LPC_GPIO->CLR[portNum] = 1 << bitPosi;
}

/*****************************************************************************
** Function name:		GPIOGetPinValue
**
** Descriptions:		Read Current state of port pin, PIN register value
**
** parameters:			port num, bit position
** Returned value:		None
**
*****************************************************************************/
RetU32 nsAPI_GPIO_GetPinValue( U8 portNum, U32 bitPosi )
{
	U32 regVal = 0;
	
	if(bitPosi == 0xFF)
	{
		regVal = LPC_GPIO->PIN[portNum];
	}
	else
	{
		if(LPC_GPIO->PIN[portNum] &  bitPosi)
			regVal = 1;
	}

	return (regVal);
}

/*****************************************************************************
** Function name:		NDrv_GPIO_SetDir
**
** Descriptions:		Set the direction in GPIO port
**
** parameters:			portNum, bit position, direction (1 out, 0 input)
**
** Returned value:		None
**
*****************************************************************************/
void NDrv_GPIO_SetDir(U32 portNum, U32 bitPosi, U32 dir )
{
	if(dir)
	LPC_GPIO->DIR[portNum] |= (1 << bitPosi);
	else
	LPC_GPIO->DIR[portNum] &= ~(1 << bitPosi);
}

void nsAPI_GPIO_LEDSetting(U8 uPort, U32 uPosition, U8 uValue)
{
	NDrv_GPIO_SetBitValue(uPort,uPosition,uValue);
}

RetU8 nsAPI_GPIO_ScanButton(void)
{
	U8 Ret				= FALSE;
	U32 u32ButtonGPIO1	= 0;
	u32ButtonGPIO1  	= nsAPI_GPIO_GetPinValue(PORT1,0xFF);
	u32ButtonGPIO1		&= GPIO1_PR;

	if( (u32ButtonGPIO1 != GPIO1_PR))
	{ 	
		if( g_GpioButtonEvent.ButtonStatus != GPIO_SCANKEY_PR )
		{
			if(!(u32ButtonGPIO1 & BIT13))
				g_GpioButtonEvent.ButtonEvent = BIT0;
			else if(!(u32ButtonGPIO1 & BIT14))
				g_GpioButtonEvent.ButtonEvent = BIT1;
			else if(!(u32ButtonGPIO1 & BIT15))
				g_GpioButtonEvent.ButtonEvent = BIT2;
			else if(!(u32ButtonGPIO1 & BIT19))
				g_GpioButtonEvent.ButtonEvent = BIT3;
			else if(!(u32ButtonGPIO1 & BIT20))
				g_GpioButtonEvent.ButtonEvent = BIT4;
			else
			{
				g_GpioButtonEvent.ButtonEvent = 0;
				g_Main_Setting.MouseEvent &= ~MAIN_FLAG_MOUSE_BUTTON_EVENT;
			}

			if( g_GpioButtonEvent.ButtonEvent > 0 )
				Ret = TRUE;
		}
	}
	else
	{
		if( g_GpioButtonEvent.ButtonStatus == GPIO_SCANKEY_PR )
		{			
			g_GpioButtonEvent.ButtonEvent = 0;
		}
	}
	return Ret;
}

void nsAPI_GPIO_MouseButtonMonitor(void)
{
	static U16 temp_prev = 0;
	static U8 same_event_counter = 0;
	
	if(nsAPI_MouseScanButton())	 
	{
		
		if( g_GpioButtonEvent.PreButtonEvent != g_GpioButtonEvent.ButtonEvent )
		{
			if(temp_prev != g_GpioButtonEvent.ButtonEvent)
				same_event_counter = 0;
			else 
				same_event_counter++;

			temp_prev = g_GpioButtonEvent.ButtonEvent;

			if(same_event_counter>2)
			{
				g_GpioButtonEvent.PreButtonEvent	= g_GpioButtonEvent.ButtonEvent;
				g_GpioButtonEvent.ButtonStatus		= GPIO_SCANKEY_PR;
				g_Main_Setting.MouseEvent		   |= MAIN_FLAG_MOUSE_BUTTON_EVENT;
				same_event_counter = 0;

				switch( g_GpioButtonEvent.PreButtonEvent )
				{
					case BIT0:
					case BIT1: 
					case BIT2:
					case BIT3:
					case BIT4:
					g_GpioButtonEvent.KeycodeTblIdx = nsAPI_GPIO_ChangingIndex(g_GpioButtonEvent.PreButtonEvent);
					nsAPI_Main_GetInMouseButtonReport(	&g_GpioButtonEvent.PreButtonEvent,
														&g_GpioButtonEvent.ButtonStatus,
														&g_GpioButtonEvent.KeycodeTblIdx);
					break;
	
					default:
					break;
				}
			}
		}
		else
			same_event_counter = 0;
	}
	else
	{
		if(g_GpioButtonEvent.PreButtonEvent != g_GpioButtonEvent.ButtonEvent)
		{
			g_GpioButtonEvent.ButtonStatus 		= GPIO_SCANKEY_RELEASE;
			g_Main_Setting.MouseEvent		   &= ~MAIN_FLAG_MOUSE_BUTTON_EVENT;
			g_GpioButtonEvent.PreButtonEvent 	= g_GpioButtonEvent.ButtonEvent;
			g_GpioButtonEvent.ButtonEventCount	= 0;
			g_GpioButtonEvent.KeycodeTblIdx     = g_GpioButtonEvent.PreButtonEvent;
			nsAPI_Main_GetInMouseButtonReport(	 &g_GpioButtonEvent.PreButtonEvent,
												 &g_GpioButtonEvent.ButtonStatus,
												 &g_GpioButtonEvent.KeycodeTblIdx);
		}
	}
}


RetU16 nsAPI_GPIO_ChangingIndex(U16 u16Index)
{
    U16 u16Ret;

	switch(u16Index)
	{
		case BIT0: u16Ret = 0x01;break; //LEFT BUTTON
		case BIT1: u16Ret = 0x02;break;	//RIGHT BUTTON
		case BIT2: u16Ret = 0x04;break; //MIDDLE BUTTON
		case BIT3: u16Ret = 0x08;break; //LEFT BUTTON
		case BIT4: u16Ret = 0x10;break; //RIGHT BUTTON
		default:
		u16Ret = 0x00;					//No Press;
		break;
	}
	return u16Ret;
}

U8 nsAPI_GPIO_Get_QIE(void)
{
	U8 u8Ret = QIE_SAME;
	U32 u32Temp;

	u32Temp = nsAPI_GPIO_GetPinValue(PORT1,0xFF);
	u32Temp = ((u32Temp & (BIT22|BIT21)) >> 21) & 0x03;

	if(g_GpioButtonEvent.PreQIEStatus != u32Temp)
	{
		switch(g_GpioButtonEvent.PreQIEStatus)
		{
			case 0x00:
			switch(u32Temp)
			{
				case 0x00: u8Ret = QIE_STOP;
				g_GpioButtonEvent.PreQIEStatus = u32Temp;
				break;

				case 0x01: u8Ret = QIE_FORWARD;
				g_GpioButtonEvent.PreQIEStatus = u32Temp;
				break;
				case 0x02: u8Ret = QIE_BACKWARD;
				g_GpioButtonEvent.PreQIEStatus = u32Temp;
				break;
			}
			break;

			case 0x01:
			switch(u32Temp)
			{
				case 0x00: u8Ret = QIE_BACKWARD;
				g_GpioButtonEvent.PreQIEStatus = u32Temp;
				break;

				case 0x01: u8Ret = QIE_STOP;
				g_GpioButtonEvent.PreQIEStatus = u32Temp;
				break;

				case 0x03: u8Ret = QIE_FORWARD;
				g_GpioButtonEvent.PreQIEStatus = u32Temp;
				break;
			}
			break;

			case 0x02:
			switch(u32Temp)
			{
				case 0x00: u8Ret = QIE_FORWARD;
				g_GpioButtonEvent.PreQIEStatus = u32Temp;
				break;

				case 0x02: u8Ret = QIE_STOP;
				g_GpioButtonEvent.PreQIEStatus = u32Temp;
				break;

				case 0x03: u8Ret = QIE_BACKWARD;
				g_GpioButtonEvent.PreQIEStatus = u32Temp;
				break;
			}
			break;

			case 0x03:
			switch(u32Temp)
			{
				case 0x01: u8Ret = QIE_BACKWARD;
				g_GpioButtonEvent.PreQIEStatus = u32Temp;
				break;

				case 0x02: u8Ret = QIE_FORWARD;
				g_GpioButtonEvent.PreQIEStatus = u32Temp;
				break;

				case 0x03: u8Ret = QIE_STOP;
				g_GpioButtonEvent.PreQIEStatus = u32Temp;
				break;
			}
			break;
		}
	}

	return u8Ret;
}

void nsAPI_GPIO_QIE_Monitor(void)
{
	U8 u8Temp;

	u8Temp = nsAPI_GPIO_Get_QIE();

	if(u8Temp != QIE_SAME)
	nsAPI_Main_GetInMouseQIEReport(u8Temp);

}

void nsAPI_GPIO_MacroKey_Monitor(void)
{



}
