/******************************************************************************
 * @file     system_LPC11Uxx.c
 * @purpose  CMSIS Cortex-M3 Device Peripheral Access Layer Source File
 *           for the NXP LPC13xx Device Series
 * @version  V1.10
 * @date     24. November 2010
 *
 * @note
 * Copyright (C) 2009-2010 ARM Limited. All rights reserved.
 *
 * @par
 * ARM Limited (ARM) is supplying this software for use with Cortex-M
 * processor based microcontrollers.  This file can be freely distributed
 * within development tools that are supporting such ARM based processors.
 *
 * @par
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 ******************************************************************************/
#define __SYSTEM_LPC11Uxx_C__

#include "system_LPC11Uxx.h"
#include "LPC11Uxx.h"
#include "Timer16.h"
#include "timer32.h"
#include "Uart.h"
#include "Gpio.h"
#include "Usbhw.h"
#include "Systick.h"
#include "Ssp.h"
#include "I2c.h"

/*----------------------------------------------------------------------------
  Clock functions
 *----------------------------------------------------------------------------*/
/**
 * Initialize the system
 *
 * @param  none
 * @return none
 *
 * @brief  Setup the microcontroller system.
 *         Initialize the System.
 */
void nsAPI_System_Init(void)
{
	U8 i;

	LPC_SYSCON->PDRUNCFG &= ~BIT5;				//Power-up System Osc
	LPC_SYSCON->SYSOSCCTRL = SYSOSCCTRL_Val;
	for (i = 0; i < 200; i++) __NOP();

	LPC_SYSCON->SYSPLLCLKSEL = SYSPLLCLKSEL_Val;//Select PLL Input
	LPC_SYSCON->SYSPLLCLKUEN = 0x01;			//Update Clock Source
	LPC_SYSCON->SYSPLLCLKUEN = 0x00;			//Toggle Update Register
	LPC_SYSCON->SYSPLLCLKUEN = 0x01;
	while(!(LPC_SYSCON->SYSPLLCLKUEN & BIT0)){}	//Wait Until Updated

	LPC_SYSCON->SYSPLLCTRL = SYSPLLCTRL_Val;	//Main Clock is PLL Out
	LPC_SYSCON->PDRUNCFG &= ~BIT7;				//Power-up SYSPLL
	while(!(LPC_SYSCON->SYSPLLSTAT & BIT0)){}	//Wait Until PLL Locked

	LPC_SYSCON->MAINCLKSEL = MAINCLKSEL_Val;	//Select PLL Clock Output
	LPC_SYSCON->MAINCLKUEN = 0x01;				//Update MCLK Clock Source
	LPC_SYSCON->MAINCLKUEN = 0x00;				//Toggle Update Register
	LPC_SYSCON->MAINCLKUEN = 0x01;
	while (!(LPC_SYSCON->MAINCLKUEN & BIT0)){}	//Wait Until Updated

	LPC_SYSCON->SYSAHBCLKDIV  = SYSAHBCLKDIV_Val;
	LPC_SYSCON->PDRUNCFG &= ~BIT10;				//Power-up USB PHY
	LPC_SYSCON->PDRUNCFG &= ~BIT8;				//Power-up USB PLL
	LPC_SYSCON->USBPLLCLKSEL = USBPLLCLKSEL_Val;//Select PLL Input
	LPC_SYSCON->USBPLLCLKUEN = 0x01;			//Update Clock Source
	LPC_SYSCON->USBPLLCLKUEN = 0x00;			//Toggle Update Register
	LPC_SYSCON->USBPLLCLKUEN = 0x01;

	while (!(LPC_SYSCON->USBPLLCLKUEN & BIT0)){}//Wait Until Updated
	LPC_SYSCON->USBPLLCTRL = USBPLLCTRL_Val;

	while (!(LPC_SYSCON->USBPLLSTAT & BIT0)){}	//Wait Until PLL Locked
	LPC_SYSCON->USBCLKSEL = 0x00;				//Select USB PLL
	LPC_SYSCON->USBCLKSEL = USBCLKSEL_Val;		//Select USB Clock
	LPC_SYSCON->USBCLKDIV = USBCLKDIV_Val;		//Set USB clock divider

	//System clock to the IOCON needs to be enabled or
	//most of the I/O related peripherals won't work.
	LPC_SYSCON->SYSAHBCLKCTRL |= BIT16;

	SystemCoreClock = (__SYS_OSC_CLK * ((LPC_SYSCON->SYSPLLCTRL & 0x01F) + 1));
	SystemCoreClock /= LPC_SYSCON->SYSAHBCLKDIV;

	nsAPI_UART_Init(BR);
	nsAPI_I2C_Init();
	nsAPI_GPIO_Init();
	nsAPI_USB_Init();							// USB Initialization
	nsAPI_Timer16_Init(Timer16_0,1); 			// ms resolution setup
	nsAPI_SysTick_Init();
	nsAPI_SSP_Init(); //SPI init
	//xprintf("\r\n SystemCoreClock = %d MHz", SystemCoreClock / 1000000UL);
}
