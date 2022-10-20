/**************************************************************************//**
 * @file     system_LPC11Uxx.h
 * @brief    CMSIS Cortex-M0 Device Peripheral Access Layer Header File
 *           for the NXP LPC11Uxx Device Series
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


#ifndef __SYSTEM_LPC11Uxx_H__
#define __SYSTEM_LPC11Uxx_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "Type.h"

#ifdef  __SYSTEM_LPC11Uxx_C__
#define INTERFACE
#else
#define INTERFACE extern
#endif

#define SYSOSCCTRL_Val 0x00000000/* Reset: 0x000*/
#define WDTOSCCTRL_Val 0x00000000/*Reset: 0x000*/
#define SYSPLLCTRL_Val 0x00000023/*eset: 0x000*/
#define SYSPLLCLKSEL_Val 0x00000001/*Reset: 0x000*/
#define MAINCLKSEL_Val 0x00000003/*Reset: 0x000*/
#define SYSAHBCLKDIV_Val 0x00000001/*Reset: 0x001*/
#define USBPLLCTRL_Val 0x00000023/*Reset: 0x000*/
#define USBPLLCLKSEL_Val 0x00000001/*Reset: 0x000*/
#define USBCLKSEL_Val 0x00000000/*Reset: 0x000*/
#define USBCLKDIV_Val 0x00000001/*Reset: 0x001*/
/*----------------------------------------------------------------------------
  Define clocks
 *----------------------------------------------------------------------------*/
#define __XTAL (12000000UL)/* Oscillator frequency*/
#define __SYS_OSC_CLK (__XTAL)/* Main oscillator frequency*/
/*----------------------------------------------------------------------------
  Check the register settings
 *----------------------------------------------------------------------------*/

INTERFACE U32 SystemCoreClock;/*!< System Clock Frequency (Core Clock)*/
/**
 * Initialize the system
 *
 * @param  none
 * @return none
 *
 * @brief  Setup the microcontroller system.
 *         Initialize the System and update the SystemCoreClock variable.
 */
INTERFACE void nsAPI_System_Init(void);

#undef INTERFACE
#ifdef __cplusplus
}
#endif
#endif /* __SYSTEM_LPC11Uxx_H */
