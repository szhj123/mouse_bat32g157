/****************************************************************************
 *   $Id:: gpio.h 6172 2011-01-13 18:22:51Z usb00423                        $
 *   Project: NXP LPC11xx software example
 *
 *   Description:
 *     This file contains definition and prototype for GPIO.
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
#ifndef __GPIO_H__ 
#define __GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "Type.h"

#ifdef  __GPIO_C__
#define INTERFACE
#else
#define INTERFACE extern
#endif

#define PORT0 0
#define PORT1 1

#define GROUP0 0
#define GROUP1 1

#define GPIOIN 0
#define GPIOOUT 1

#define GPIO_SCANKEY_NULL 0
#define GPIO_SCANKEY_PR BIT0
#define GPIO_SCANKEY_PH BIT1
#define GPIO_SCANKEY_RELEASE BIT2

#define GPIO0_PR (0xFFFFFFFF)
//#define GPIO1_PR (BIT20|BIT19|BIT15|BIT14|BIT13) //ori
#define GPIO1_PR (BIT31|BIT28|BIT27|BIT26|BIT25)

typedef enum _QIEStatusIndex_
{   
    QIE_STOP = 0x00,
    QIE_FORWARD = 0x01,
    QIE_BACKWARD = 0xFF,    
    QIE_SAME = 0xAA  
}QIEStatusIndex;


typedef struct _LPC11Uxx_Gpio_Setting_
{
	U16 ButtonStatus; 
	U16 ButtonEvent;	
	U16 ButtonEventCount;	
	U16 PreButtonEvent;	
	U16 KeycodeTblIdx; 
	U8  PreQIEStatus;
}LPC11Uxx_Gpio_Setting;


INTERFACE LPC11Uxx_Gpio_Setting g_GpioButtonEvent;



INTERFACE void FLEX_INT0_IRQHandler(void);
INTERFACE void FLEX_INT1_IRQHandler(void);
INTERFACE void FLEX_INT2_IRQHandler(void);
INTERFACE void FLEX_INT3_IRQHandler(void);
INTERFACE void FLEX_INT4_IRQHandler(void);
INTERFACE void FLEX_INT5_IRQHandler(void);
INTERFACE void FLEX_INT6_IRQHandler(void);
INTERFACE void FLEX_INT7_IRQHandler(void);
INTERFACE void GINT0_IRQHandler(void);
INTERFACE void GINT1_IRQHandler(void);
INTERFACE void nsAPI_GPIO_Init( void );
INTERFACE void NDrv_GPIO_SetBitValue(U32 portNum, U32 bitPosi, U32 bitVal );
INTERFACE RetU32 nsAPI_GPIO_GetPinValue( U8 portNum, U32 bitPosi);
INTERFACE void NDrv_GPIO_SetDir( U32 portNum, U32 bitPosi, U32 dir );
INTERFACE void nsAPI_GPIO_LEDSetting(U8 uPort, U32 uPosition, U8 uValue);
INTERFACE RetU8 nsAPI_GPIO_ScanButton(void);
INTERFACE void nsAPI_GPIO_MouseButtonMonitor(void);
INTERFACE RetU16 nsAPI_GPIO_ChangingIndex(U16 u16Index);
INTERFACE U8 nsAPI_GPIO_Get_QIE(void);
INTERFACE void nsAPI_GPIO_QIE_Monitor(void);
INTERFACE void nsAPI_GPIO_Macrokey_Monitor(void);

#undef INTERFACE
#ifdef __cplusplus
}
#endif
#endif /* end __GPIO_H */

