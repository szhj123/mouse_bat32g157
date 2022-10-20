/****************************************************************************
 *   $Id:: timer32.h 6956 2011-03-23 23:03:25Z usb00423                     $
 *   Project: NXP LPC11xx software example
 *
 *   Description:
 *     This file contains definition and prototype for 32-bit timer 
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
#ifndef __TIMER32_H__ 
#define __TIMER32_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "Type.h"

#ifdef  __TIMER32_C__
#define INTERFACE
#else
#define INTERFACE extern
#endif

#define EMC0	4
#define EMC1	6
#define EMC2	8
#define EMC3	10

#define MATCH0 BIT0
#define MATCH1 BIT1
#define MATCH2 BIT2
#define MATCH3 BIT3

#define Timer32_0 0
#define Timer32_1 1



#define BREATHING_FREQ_GAP 100
#define BREATHING_DELAY_TIMER 40
#define BREATHING_STEP 2

#define PWM_MATCH_ENABLE (MATCH2|MATCH1|MATCH0)
#define Timer32_IntervalmS 1000UL 
#define Timer32_MHz_Prescale (SystemCoreClock/1000000UL)

typedef enum _Timer32_LED_Type_
{
	LED_NORMAL = 0,
	LED_BREATHING   
}Timer32_LED_Type;


#define BREATHING_STEP_RESETTING BIT0

typedef struct _LPC11Uxx_TIMER32_LED_SETTING_
{
	Timer32_LED_Type LEDStatusType;/* 0 -> Normal : 1 -> Breathing */	
	U8 BreathingStatusType;/*1 -> Inc : 0 -> Dec*/
	U8 BreathingStep; 
	U8 BreathingStepStatus; 
	U32 BreathingDelayCount;
	U32 CurBreathingFreq;
	U32 PreBreathingFreq;	
}LPC11Uxx_TIMER32_LED_SETTING;

INTERFACE LPC11Uxx_TIMER32_LED_SETTING g_Timer32_LED_Setting; 

INTERFACE void TIMER32_0_IRQHandler(void);
INTERFACE void TIMER32_1_IRQHandler(void);
INTERFACE void NDrv_Timer32_Enable(U8 timer_num);
INTERFACE void NDrv_Timer32_Disable(U8 timer_num);
INTERFACE void NDrv_Timer32_Reset(U8 timer_num);
INTERFACE void nsAPI_Timer32_Setting_MatchFunction(uint8_t timer_num, uint8_t match_enable, uint8_t location);
INTERFACE void nsAPI_Timer32PWM_Init(U8 timer_num, U32 period, U8 match_enable);
INTERFACE void NDrv_Timer32PWM_ReSettingMatch(U8 timer_num, U32 period);
INTERFACE void NDrv_Timer32PWM_Breathing(void);
INTERFACE RetU32 nsAPI_Timer32PWM_GetCurBreathingFreqValue(void);
INTERFACE void nsAPI_Timer32PWM_Breathing_ReSetting(U8 u8Breathing);
extern void init_timer32(U32 timer );

#undef INTERFACE
#ifdef __cplusplus
}
#endif
#endif /* end __TIMER32_H */

