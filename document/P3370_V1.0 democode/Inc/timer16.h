/****************************************************************************
 *   $Id:: timer16.h 6956 2011-03-23 23:03:25Z usb00423                     $
 *   Project: NXP LPC11xx software example
 *
 *   Description:
 *     This file contains definition and prototype for 16-bit timer 
 *     configuration.
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
#ifndef __TIMER16_H__ 
#define __TIMER16_H__

#ifdef __cplusplus
extern "C" {
#endif 

#include "type.h"
	
#ifdef __TIMER16_C__
#define INTERFACE
#else
#define INTERFACE extern
#endif


#define Timer16_0 0
#define Timer16_1 1
///* For 16-bit timer, make sure that TIME_INTERVAL should be no
//greater than 0xFFFF. */
#define Timer16_IntervalmS 1000UL 
#define Timer16_MHz_Prescale (SystemCoreClock/1000000UL)

typedef struct _LPC11Uxx_Timer16_Setting_
{
	U32 Timer16_0_Counter[2];
	U32 Timer16_1_Counter[2];
	
} LPC11Uxx_Timer16_Setting;

INTERFACE LPC11Uxx_Timer16_Setting g_Timer16_Setting;

INTERFACE void TIMER16_0_IRQHandler(void);
INTERFACE void TIMER16_1_IRQHandler(void);
INTERFACE void NDrv_Timer16_Enable(U8 timer_num);
INTERFACE void NDrv_Timer16_Disable(U8 timer_num);
INTERFACE void NDrv_Timer16_Reset(U8 timer_num);
INTERFACE void nsAPI_Timer16_Init(U8 timer_num, U32 timer);

#undef INTERFACE
#ifdef __cplusplus
}
#endif 
#endif /* end __TIMER16_H */

