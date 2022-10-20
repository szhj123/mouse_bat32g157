#define __SYSTICK_C__

#include "LPC11Uxx.h"
#include "core_cm0.h"
#include "Gpio.h"
#include "Uart.h"
#include "Systick.h"
#include "Timer32.h"


void SysTick_Handler(void)
{   

//	if(g_Timer32_LED_Setting.LEDStatusType == LED_BREATHING)
//	{	
//		if((g_Timer32_LED_Setting.BreathingStepStatus & BREATHING_STEP_RESETTING) == BREATHING_STEP_RESETTING)  
//		nsAPI_Timer32PWM_Breathing_ReSetting(15);

//		NDrv_Timer32PWM_Breathing();	
//	}
}


void nsAPI_SysTick_Init(void)
{
	NVIC_DisableIRQ(SysTick_IRQn);

	if(SysTick_Config(SYSTICK_TIMER*10/*ms*/))/* Setup SysTick Timer for 10 msec interrupts  */
	//if(SysTick_Config(SYSTICK_TIMER))//*10/*ms*/))/* Setup SysTick Timer for 10 msec interrupts  */		
	{
		while(1){}/*Systick Error*/
	}
	
	NVIC_EnableIRQ(SysTick_IRQn);	
}

