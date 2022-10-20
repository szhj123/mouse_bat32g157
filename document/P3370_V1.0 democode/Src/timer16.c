/****************************************************************************
 *   $Id:: timer16.c 6950 2011-03-23 22:09:44Z usb00423                     $
 *   Project: NXP LPC11xx 16-bit timer example
 *
 *   Description:
 *     This file contains 16-bit timer code example which include timer 
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
#define __TIMER16_C__

#include "Pixart_Sensor.h"


U16 poll_tick_btn, poll_usb, poll_id, poll_z_wheel,glitch_prevention, cpi_clicked_flag, poll_motion, poll_counter;
/******************************************************************************
** Function name:		TIMER_0_IRQHandler
**
** Descriptions:		Timer/CounterX and CaptureX interrupt handler
**
** parameters:			None
** Returned value:		None
** 
******************************************************************************/
void TIMER16_0_IRQHandler(void)
{
	if(LPC_CT16B0->IR & BIT0)
	{
		LPC_CT16B0->IR = BIT0;/*Clear interrupt flag */
		g_Timer16_Setting.Timer16_0_Counter[0]++;	// Dennis: what is this for?
		poll_tick_btn++;
		poll_usb++;
		poll_id++;
		poll_z_wheel++;
		poll_motion++;
		poll_counter++;

		if (glitch_prevention>0)
		glitch_prevention--;

		if (cpi_clicked_flag) {
			if( g_GpioButtonEvent.ButtonEvent == CPI_P_CLICKED) 
			{
				cpi_p_Cntr++;		
			}
			if ( g_GpioButtonEvent.ButtonEvent == CPI_M_CLICKED)
			{
				cpi_m_Cntr++;
			}
		}

	}

	if(LPC_CT16B0->IR & BIT1)
	{
		LPC_CT16B0->IR = BIT1;/*Clear interrupt flag */
		g_Timer16_Setting.Timer16_0_Counter[1]++;	// Dennis: what is this for?	
	}
}

/******************************************************************************
** Function name:		TIMER_1_IRQHandler
**
** Descriptions:		Timer/CounterX and CaptureX interrupt handler
**
** parameters:			None
** Returned value:		None
** 
******************************************************************************/
void TIMER16_1_IRQHandler(void)
{
	if(LPC_CT16B1->IR & BIT0)
	{  
		LPC_CT16B1->IR = BIT0;/* clear interrupt flag */
		//g_Timer16_Setting.Timer16_1_Counter[0]++;				
	}

	if(LPC_CT16B1->IR & BIT1)
	{  
		LPC_CT16B1->IR = BIT1;/* clear interrupt flag */
		//g_Timer16_Setting.Timer16_1_Counter[1]++;		
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
void NDrv_Timer16_Enable(U8 timer_num)
{
	if(timer_num == 0) 
	LPC_CT16B0->TCR = 1; 
	else 
	LPC_CT16B1->TCR = 1;  
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
void NDrv_Timer16_Reset(uint8_t timer_num)
{
	uint32_t regVal;

	if(timer_num == 0)
	{
		regVal = LPC_CT16B0->TCR;
		regVal |= 0x02;
		LPC_CT16B0->TCR = regVal;
	}
	else
	{
		regVal = LPC_CT16B1->TCR;
		regVal |= 0x02;
		LPC_CT16B1->TCR = regVal;
	}
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
void NDrv_Timer16_Disable(U8 timer_num)
{
	if(timer_num == 0) 
	LPC_CT16B0->TCR = 0; 
	else 
	LPC_CT16B1->TCR = 0; 
}
/******************************************************************************
** Function name:		init_timer
**
** Descriptions:		Initialize timer, set timer interval, reset timer,
**						install timer interrupt handler
**
** parameters:			timer number and timer interval
** Returned value:		None
** 
******************************************************************************/
void nsAPI_Timer16_Init(U8 timer_num, U32 timer) 
{
	if(timer_num == Timer16_0)
	{
		NVIC_DisableIRQ(TIMER_16_0_IRQn);						// disable 16bit timer_0 interrupt
		NDrv_Timer16_Reset(Timer16_0);							// reset 16bit timer_0 interrupt
		LPC_SYSCON->SYSAHBCLKCTRL |= BIT7;					// enable clock for 16bit timer_0		
		LPC_CT16B0->PR = Timer16_MHz_Prescale;			// set prescale value
		LPC_CT16B0->MR0 = timer*Timer16_IntervalmS;	// set Timer Counter Match value

		/* Capture 0 and 1 on rising edge, interrupt enable. */
		LPC_CT16B0->CCR = (BIT0|BIT2);
		LPC_CT16B0->MCR = (BIT0|BIT1);/*Interrupt and Reset on MR0 and MR1*/		

		/* Enable the TIMER0 Interrupt */
		NVIC_EnableIRQ(TIMER_16_0_IRQn);

		NDrv_Timer16_Enable(Timer16_0); 			
	}
	else if(timer_num ==  Timer16_1)
	{
		NVIC_DisableIRQ(TIMER_16_1_IRQn);
		NDrv_Timer16_Reset(Timer16_1);
		/* Some of the I/O pins need to be clearfully planned if
		you use below module because JTAG and TIMER CAP/MAT pins are muxed. */
		LPC_SYSCON->SYSAHBCLKCTRL |= BIT8;
		LPC_CT16B1->PR = Timer16_MHz_Prescale;	  

		LPC_CT16B1->MR0 = timer*Timer16_IntervalmS;
		//LPC_CT16B1->MR1 = timer*Timer16_IntervalmS;	

		/* Capture 0 and 1 on rising edge, interrupt enable. */
		LPC_CT16B1->CCR = (BIT0|BIT2);
		LPC_CT16B1->MCR = (BIT0|BIT2);/* Interrupt and Reset on MR0 and MR1 */

		/* Enable the TIMER1 Interrupt */
		NVIC_EnableIRQ(TIMER_16_1_IRQn);

		NDrv_Timer16_Enable(Timer16_1);    
	}
}


