/****************************************************************************
 *   $Id:: timer32.c 6951 2011-03-23 22:11:07Z usb00423                     $
 *   Project: NXP LPC11xx 32-bit timer example
 *
 *   Description:
 *     This file contains 32-bit timer code example which include timer 
 *     initialization, timer interrupt handler, and related APIs for 
 *     timer setup.
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
#define __TIMER32_C__

#include "LPC11Uxx.h"
#include "timer32.h"
#include "uart.h"
#include "Pixart_Sensor.h"

/******************************************************************************
** Function name:		TIMER32_0_IRQHandler
**
** Descriptions:		Timer/CounterX and captureX interrupt handler
**
** parameters:			None
** Returned value:		None
** 
******************************************************************************/
void TIMER32_0_IRQHandler(void)
{
  if ( LPC_CT32B0->IR & (0x01<<0) )
  { 
	LPC_CT32B0->IR |= (0x01<<0);

  }
  if ( LPC_CT32B0->IR & (0x01<<1) )
  {  
	LPC_CT32B0->IR = 0x1<<1;			/* clear interrupt flag */
  }
  if ( LPC_CT32B0->IR & (0x01<<2) )
  {  
	LPC_CT32B0->IR = 0x1<<2;			/* clear interrupt flag */
  }
  if ( LPC_CT32B0->IR & (0x01<<3) )
  {  
	LPC_CT32B0->IR = 0x1<<3;			/* clear interrupt flag */
  }
  if ( LPC_CT32B0->IR & (0x1<<4) )
  {  
	LPC_CT32B0->IR = 0x1<<4;			/* clear interrupt flag */	
  }
  if ( LPC_CT32B0->IR & (0x1<<5) )
  {  
	LPC_CT32B0->IR = 0x1<<5;			/* clear interrupt flag */
  }
  if ( LPC_CT32B0->IR & (0x1<<6) )
  {  
	LPC_CT32B0->IR = 0x1<<6;			/* clear interrupt flag */
  }
  if ( LPC_CT32B0->IR & (0x1<<7) )
  {  
	LPC_CT32B0->IR = 0x1<<7;			/* clear interrupt flag */
  }
 
}

/******************************************************************************
** Function name:		TIMER32_1_IRQHandler
**
** Descriptions:		Timer/CounterX and captureX interrupt handler
**
** parameters:			None
** Returned value:		None
** 
******************************************************************************/
void TIMER32_1_IRQHandler(void)
{
  if ( LPC_CT32B1->IR & (0x01<<0) )
  {  
	LPC_CT32B1->IR = 0x1<<0;			/* clear interrupt flag */
  }
  if ( LPC_CT32B1->IR & (0x01<<1) )
  {  
	LPC_CT32B1->IR = 0x1<<1;			/* clear interrupt flag */
  }
  if ( LPC_CT32B1->IR & (0x01<<2) )
  {  
	LPC_CT32B1->IR = 0x1<<2;			/* clear interrupt flag */
  }
  if ( LPC_CT32B1->IR & (0x01<<3) )
  {  
	LPC_CT32B1->IR = 0x1<<3;			/* clear interrupt flag */
  }
  if ( LPC_CT32B1->IR & (0x1<<4) )
  {  
	LPC_CT32B1->IR = 0x1<<4;			/* clear interrupt flag */
  }
  if ( LPC_CT32B1->IR & (0x1<<5) )
  {  
	LPC_CT32B1->IR = 0x1<<5;			/* clear interrupt flag */
	
  }
  if ( LPC_CT32B1->IR & (0x1<<6) )
  {  
	LPC_CT32B1->IR = 0x1<<6;			/* clear interrupt flag */
  }
  if ( LPC_CT32B1->IR & (0x1<<7) )
  {  
	LPC_CT32B1->IR = 0x1<<7;			/* clear interrupt flag */
  }
 
}

/******************************************************************************
** Function name:		enable_timer
**
** Descriptions:		Enable timer
**
** parameters:			timer number: 0 or 1
** Returned value:		None
** 
******************************************************************************/
void NDrv_Timer32_Enable(U8 timer_num)
{
	if(timer_num == 0)  
	LPC_CT32B0->TCR = 1;  
	else  
	LPC_CT32B1->TCR = 1; 
}

/******************************************************************************
** Function name:		disable_timer
**
** Descriptions:		Disable timer
**
** parameters:			timer number: 0 or 1
** Returned value:		None
** 
******************************************************************************/
void NDrv_Timer32_Disable(U8 timer_num)
{
	if(timer_num == 0)  
	LPC_CT32B0->TCR = 0;  
	else  
	LPC_CT32B1->TCR = 0;  
}

/******************************************************************************
** Function name:		reset_timer
**
** Descriptions:		Reset timer
**
** parameters:			timer number: 0 or 1
** Returned value:		None
** 
******************************************************************************/
void NDrv_Timer32_Reset(U8 timer_num)
{
	U32 regVal;

	if(timer_num == 0)
	{
		regVal = LPC_CT32B0->TCR;
		regVal |= BIT1;
		LPC_CT32B0->TCR = regVal;
	}
	else
	{
		regVal = LPC_CT32B1->TCR;
		regVal |= BIT1;
		LPC_CT32B1->TCR = regVal;
	}  
}

/******************************************************************************
** Function name:		set_timer_match
**
** Descriptions:		Set timer match based on location
**
** parameters:			timer number: 0~1, location 0~2
** Returned value:		None
** 
******************************************************************************/
void nsAPI_Timer32_Setting_MatchFunction(U8 timer_num, U8 match_enable, U8 location)
{
	if(timer_num == 0)
	{
		if(match_enable & BIT0)
		{
			if(location == 0)
			{
				LPC_IOCON->PIO0_18 &= ~(BIT2|BIT1|BIT0);	
				LPC_IOCON->PIO0_18 |= BIT1;/* Timer0_32 MAT0 */
			}
			else if(location == 1)
			{
				LPC_IOCON->PIO1_24 &= ~(BIT2|BIT1|BIT0);
				LPC_IOCON->PIO1_24 |= BIT0;/* Timer0_32 MAT0 */
			}
		}
		
		if(match_enable & BIT1)
		{
			if ( location == 0 )
			{
				//LPC_IOCON->PIO0_19 &= ~(BIT2|BIT1|BIT0);
				//LPC_IOCON->PIO0_19 |= BIT1;/* Timer0_32 MAT1 */
			}
			else if ( location == 1 )
			{
				//LPC_IOCON->PIO1_25 &= ~(BIT2|BIT1|BIT0);
				//LPC_IOCON->PIO1_25 |= BIT0;/* Timer0_32 MAT1 */
			}
		}
		
		if(match_enable & BIT2)
		{
			if ( location == 0 )
			{
				LPC_IOCON->PIO0_1 &= ~(BIT2|BIT1|BIT0);
				LPC_IOCON->PIO0_1 |= BIT1;/* Timer0_32 MAT2 */
			}
			else if ( location == 1 )
			{
			//	LPC_IOCON->PIO1_26 &= ~(BIT2|BIT1|BIT0);
			//	LPC_IOCON->PIO1_26 |= BIT0;/* Timer0_32 MAT2 */
			}
		}
	
		if(match_enable & BIT3)
		{
			if ( location == 0 )
			{
				LPC_IOCON->TDI_PIO0_11 &= ~(BIT2|BIT1|BIT0);
				LPC_IOCON->TDI_PIO0_11 |= (BIT1|BIT0);/* Timer0_32 MAT3 */
			}
			else if ( location == 1 )
			{
				LPC_IOCON->PIO1_27 &= ~(BIT2|BIT1|BIT0);
				LPC_IOCON->PIO1_27 |= BIT0;/* Timer0_32 MAT3 */
			}
		}
	}
	else if(timer_num == 1)
	{
		if(match_enable & BIT0)
		{
			if(location == 0)
			{
				//LPC_IOCON->PIO1_0 &= ~0x07;
				//LPC_IOCON->PIO1_0 |= 0x01;/* Timer1_32 MAT0 */
			}
			else if(location == 1)
			{
				LPC_IOCON->TDO_PIO0_13 &= ~(BIT2|BIT1|BIT0);
				LPC_IOCON->TDO_PIO0_13 |= (BIT1|BIT0);/* Timer1_32 MAT0 */
			}
		}
 
		if(match_enable & BIT1)
		{
			if(location == 0)
			{
				//LPC_IOCON->PIO1_1 &= ~0x07;
				//LPC_IOCON->PIO1_1 |= 0x01;/* Timer1_32 MAT1 */
			}
			else if(location == 1)
			{
				//LPC_IOCON->TRST_PIO0_14 &= ~(BIT2|BIT1|BIT0);
				//LPC_IOCON->TRST_PIO0_14 |= (BIT1|BIT0);/* Timer1_32 MAT1 */
			}
		}
	
		if(match_enable & BIT2)
		{
			if(location == 0)
			{
				//LPC_IOCON->PIO1_2 &= ~0x07;
				//LPC_IOCON->PIO1_2 |= 0x01;/* Timer1_32 MAT2 */
			}
			else if ( location == 1 )
			{
#if __SWD_DISABLED
				LPC_IOCON->SWDIO_PIO0_15 &= ~(BIT2|BIT1|BIT0);
				LPC_IOCON->SWDIO_PIO0_15 |= (BIT1|BIT0);/* Timer1_32 MAT2 */
#endif
			}
		}
	
		if(match_enable & BIT3)
		{
			if(location == 0)
			{
				//LPC_IOCON->PIO1_3 &= ~0x07;
				//LPC_IOCON->PIO1_3 |= 0x01;/* Timer1_32 MAT3 */
			}
			else if(location == 1)
			{
				LPC_IOCON->PIO0_16 &= ~(BIT2|BIT1|BIT0);
				LPC_IOCON->PIO0_16 |= BIT1;/* Timer1_32 MAT3 */
			}
		}
	}	
}

void nsAPI_Timer32PWM_Breathing_ReSetting(U8 u8Breathing)
{
	g_Timer32_LED_Setting.LEDStatusType = LED_BREATHING;
	g_Timer32_LED_Setting.BreathingStatusType = 0;
	g_Timer32_LED_Setting.BreathingDelayCount = 0;
	g_Timer32_LED_Setting.BreathingStepStatus &= ~BREATHING_STEP_RESETTING;
	g_Timer32_LED_Setting.BreathingStep = BREATHING_STEP*u8Breathing;
}

/******************************************************************************
** Function name:		init_timer32PWM
**
** Descriptions:		Initialize timer as PWM
**
** parameters:			timer number, period and match enable:
**						match_enable[0] = PWM for MAT0 
**						match_enable[1] = PWM for MAT1
**						match_enable[2] = PWM for MAT2
** Returned value:		None
** 
******************************************************************************/
void nsAPI_Timer32PWM_Init(U8 timer_num, U32 period, U8 match_enable)
{
	NDrv_Timer32_Disable(timer_num);
	
	nsAPI_Timer32PWM_Breathing_ReSetting(1);

	if(timer_num == 1)
	{
		U32 u32Timer32_1_period; 

		LPC_SYSCON->SYSAHBCLKCTRL |= BIT10;

		/* Setup the external match register */
		LPC_CT32B1->EMR = (1 << EMC2)|(2 << EMC1)|(1 << EMC0);

		/* Setup the outputs */
		/* If match0 is enabled, set the output, use location 0 for test. */
		nsAPI_Timer32_Setting_MatchFunction(timer_num,match_enable,1);
		
		LPC_CT32B1->PWMC |= match_enable;
		/* Setup the match registers */
		/* set the period value to a global variable */
		u32Timer32_1_period = period*Timer32_IntervalmS;		
		
		LPC_CT32B1->MR0 = u32Timer32_1_period / 2;
		LPC_CT32B1->MR1 = u32Timer32_1_period / 2;
		LPC_CT32B1->MR2 = u32Timer32_1_period / 2;
		LPC_CT32B1->MR3 = u32Timer32_1_period;		
		LPC_CT32B1->MCR = BIT10;/* Reset on MR3 */
	}
	else
	{
		U32 u32Timer32_0_period;
		/* Some of the I/O pins need to be clearfully planned if
		you use below module because JTAG and TIMER CAP/MAT pins are muxed. */
		LPC_SYSCON->SYSAHBCLKCTRL |= BIT9;

		LPC_CT32B0->PR = Timer32_MHz_Prescale;
		
		/* Setup the external match register */
		LPC_CT32B0->EMR = (3 << EMC2)|(3 << EMC1)|(3 << EMC0);

		/* Setup the outputs */
		/* If match0 is enabled, set the output, use location 0 for test. */
		nsAPI_Timer32_Setting_MatchFunction(timer_num, match_enable,1);

		/* Enable the selected PWMs and enable Match3 */
		LPC_CT32B0->PWMC = match_enable;

		/* Setup the match registers */
		/* set the period value to a global variable */
		u32Timer32_0_period = period*Timer32_IntervalmS;	

		if(u32Timer32_0_period < BREATHING_FREQ_GAP)
		u32Timer32_0_period = BREATHING_FREQ_GAP;	
		
		LPC_CT32B0->MR0 = u32Timer32_0_period -BREATHING_FREQ_GAP;
		LPC_CT32B0->MR1 = u32Timer32_0_period -BREATHING_FREQ_GAP;
		LPC_CT32B0->MR2 = u32Timer32_0_period -BREATHING_FREQ_GAP;
		LPC_CT32B0->MR3 = u32Timer32_0_period;		
		LPC_CT32B0->MCR = BIT10;	/* Reset on MR3 */	
		
		g_Timer32_LED_Setting.CurBreathingFreq = u32Timer32_0_period -BREATHING_FREQ_GAP;
		g_Timer32_LED_Setting.PreBreathingFreq = u32Timer32_0_period;		
	}
	
	NDrv_Timer32_Reset(timer_num);
	NDrv_Timer32_Enable(timer_num);
}

/******************************************************************************
** Function name:		pwm32_setMatch
**
** Descriptions:		Set the pwm32 match values
**
** parameters:			timer number, match numner and the value
**
** Returned value:		None
** 
******************************************************************************/
void NDrv_Timer32PWM_ReSettingMatch(U8 timer_num, U32 period)
{
	U32 u32Timer32_period;

	u32Timer32_period = period*Timer32_IntervalmS;	

	if(u32Timer32_period == 0)
	u32Timer32_period = 10;	  

	if(timer_num)
	{    
		LPC_CT32B1->MR0 = u32Timer32_period / 2;    
		LPC_CT32B1->MR1 = u32Timer32_period / 2;     
		LPC_CT32B1->MR2 = u32Timer32_period / 2;     
		LPC_CT32B1->MR3 = u32Timer32_period;    
	}
	else 
	{   
		LPC_CT32B0->MR0 = u32Timer32_period / 2;     
		LPC_CT32B0->MR1 = u32Timer32_period / 2;   
		LPC_CT32B0->MR2 = u32Timer32_period / 2;   
		LPC_CT32B0->MR3 = u32Timer32_period;    
	}
	
	LPC_CT32B0->MCR = BIT10;	/* Reset on MR3 */
}

void NDrv_Timer32PWM_Breathing(void)
{
	U32 u32Timer32_period = g_Timer32_LED_Setting.CurBreathingFreq;
	
       if(g_Timer32_LED_Setting.BreathingStatusType)
       {        		
	   
		if(u32Timer32_period <  (g_Timer32_LED_Setting.PreBreathingFreq -BREATHING_FREQ_GAP*2))
		{
			u32Timer32_period += (g_Timer32_LED_Setting.BreathingStep*BREATHING_STEP);			
                   
			LPC_CT32B0->MR0 = u32Timer32_period;	 
			LPC_CT32B0->MR1 = u32Timer32_period;   
			LPC_CT32B0->MR2 = u32Timer32_period;   

			g_Timer32_LED_Setting.CurBreathingFreq = u32Timer32_period; 	
			g_Timer32_LED_Setting.BreathingDelayCount = BREATHING_DELAY_TIMER / 2;
		}
		else
		{       
			if(g_Timer32_LED_Setting.BreathingDelayCount > 0)
			g_Timer32_LED_Setting.BreathingDelayCount --;
			else  
			g_Timer32_LED_Setting.BreathingStatusType = 0;						
		}	
       }
       else
       { 	 
        
             if((u32Timer32_period - (g_Timer32_LED_Setting.BreathingStep*BREATHING_STEP)) > BREATHING_FREQ_GAP /4)	        
		{
			u32Timer32_period -= (g_Timer32_LED_Setting.BreathingStep*BREATHING_STEP);					
                       
			LPC_CT32B0->MR0 = u32Timer32_period;	 
			LPC_CT32B0->MR1 = u32Timer32_period;   
			LPC_CT32B0->MR2 = u32Timer32_period;

			g_Timer32_LED_Setting.CurBreathingFreq = u32Timer32_period; 	
			g_Timer32_LED_Setting.BreathingDelayCount = BREATHING_DELAY_TIMER;
		}
		else
		{          
			if(g_Timer32_LED_Setting.BreathingDelayCount > 0)
			g_Timer32_LED_Setting.BreathingDelayCount --;
			else  
			g_Timer32_LED_Setting.BreathingStatusType = 1;	
		}	
       }	
}

void init_timer32( U32 timer )
{
//
// 48000UL = 1ms
// 4800UL  = 100us
// 480UL   = 10uS
// Notes: <Frequency modulation>: We are using 480UL as default to measure 1000Hz
//         for 2ms rising edge to rising edge, readback is 203 => 203 x 10uS = 2.03ms

		NVIC_DisableIRQ(TIMER_32_0_IRQn);
		NDrv_Timer32_Reset(Timer32_0);

	    LPC_SYSCON->SYSAHBCLKCTRL |= BIT9;
		LPC_CT32B0->PR = timer;
		
		LPC_IOCON->PIO0_17 = (1<<1)|(2<<3);//CT32B0_CAP0;
		LPC_CT32B0->CTCR |= 0;//CAP0|CAP_MODE_BOTH_EDGE;	// Timer mode 
		LPC_CT32B0->CCR |= 5;//CAP0FE|CAP0RE;				// Capture 0 on rising edge, interrupt enable.
		//LPC_CT32B0->MCR |= MR0I;						// Interrupt on MR0
		LPC_CT32B0->TCR |= 1;//CEN;							// Start counting
		
		NVIC_EnableIRQ(TIMER_32_0_IRQn); // Enable the TIMER0 Interrupt

//	NDrv_Timer32_Enable(timer_num);
}

