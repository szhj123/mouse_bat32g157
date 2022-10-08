/**************************************************************************//**
 * @file     system_BAT32G157.h
 * @brief    CMSIS Cortex-M0+ Device Peripheral Access Layer Header File for
 *           Device BAT32G157
 * @version  V1.00
 * @date     2020/9/15
 ******************************************************************************/
/*
 * Copyright (c) 2009-2018 Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef SYSTEM_BAT32G157_H
#define SYSTEM_BAT32G157_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

extern uint32_t SystemCoreClock;     /*!< System Clock Frequency (Core Clock)  */


/**
  \brief Setup the microcontroller system.

   Initialize the System and update the SystemCoreClock variable.
 */
extern void SystemInit (void);


/**
  \brief  Update SystemCoreClock variable.

   Updates the SystemCoreClock with current core Clock retrieved from cpu registers.
 */
extern void SystemCoreClockUpdate (void);


/* =========================================================================================================================== */
/* ================                               INTC Function ProtoTypes                          	      ================ */
/* =========================================================================================================================== */

/** @addtogroup INTC_Function_ProtoTypes
  * @{
  */

typedef struct {
   __IO uint8_t  	IFL;
   __IO uint8_t  	IFH;
   __IO uint16_t  	RESERVED;
}  R_INT_IF_Type;

typedef struct {
   __IO uint8_t  	MKL;
   __IO uint8_t  	MKH;
   __IO uint16_t  	RESERVED;
}  R_INT_MK_Type;

typedef struct {
   R_INT_IF_Type     	IF[32];
   uint32_t   		RESERVED[32];
   R_INT_MK_Type     	MK[32];
}  R_INT_Type;

#define R_INT_BASE	(0x40006000UL)           /*!< (INTC     ) Base Address */
#define R_INT		((R_INT_Type            *) R_INT_BASE)
	
__STATIC_INLINE void INTC_EnableIRQ(IRQn_Type IRQn)
{
  if (IRQn < 32)// 0~31
    R_INT->MK[IRQn % 32].MKL = 0;
  else if (IRQn < 64)  	// 32~64
    R_INT->MK[IRQn % 32].MKH = 0;
  else
  ;//  MSG(("IRQ number %d exceeds the legal value!\n", IRQn)); 
}

__STATIC_INLINE void INTC_DisableIRQ(IRQn_Type IRQn)
{
  if (IRQn < 32)// 0~31
    R_INT->MK[IRQn % 32].MKL = 1;
  else if (IRQn < 64)  	// 32~64
    R_INT->MK[IRQn % 32].MKH = 1;
  else
  ;//  MSG(("IRQ number %d exceeds the legal value!\n", IRQn)); 
}

__STATIC_INLINE void INTC_ClearPendingIRQ(IRQn_Type IRQn)
{
  if (IRQn < 32)// 0~31
    R_INT->IF[IRQn % 32].IFL = 0;
  else if (IRQn < 64)  	// 32~64
    R_INT->IF[IRQn % 32].IFH = 0;
  else
  ;//  MSG(("IRQ number %d exceeds the legal value!\n", IRQn)); 
}

__STATIC_INLINE void INTC_SetPendingIRQ(IRQn_Type IRQn)
{
  if (IRQn < 32)// 0~31
    R_INT->IF[IRQn % 32].IFL = 1;
  else if (IRQn < 64)  	// 32~64
    R_INT->IF[IRQn % 32].IFH = 1;
  else
  ;//  MSG(("IRQ number %d exceeds the legal value!\n", IRQn)); 
}

__STATIC_INLINE uint8_t INTC_GetPendingIRQ(IRQn_Type IRQn)
{
  if (IRQn < 32)// 0~31
    return (R_INT->IF[IRQn % 32].IFL);
  else if (IRQn < 64)  	// 32~64
    return (R_INT->IF[IRQn % 32].IFH);
  else
    return 0;//  MSG(("IRQ number %d exceeds the legal value!\n", IRQn)); 
}

/* Enable Interrupt */
#define __EI  	__set_PRIMASK(0)
/* Disable Interrupt */
#define __DI  	__set_PRIMASK(1)

/* Enter sleep mode */
#define __HALT() 	do { \
						SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;\
						__WFI();\
					} while (0U)

#define __SLEEP    __HALT

/* Enter deep sleep mode */
#define __STOP() 	do { \
						SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;\
						__WFI();\
					} while (0U)

/** @} */ /* End of group INTC_Function_ProtoTypes */

#ifdef __cplusplus
}
#endif

#endif /* SYSTEM_BAT32G157_H */
