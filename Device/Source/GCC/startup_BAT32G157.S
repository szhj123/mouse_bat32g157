/**************************************************************************//**
 * @file     startup_BAT32G157.S
 * @brief    CMSIS Cortex-M0+ Core Device Startup File for
 *           Device BAT32G157
 * @version  1.0.0
 * @date     2020/10/24-laidi-20220118
 ******************************************************************************/
/*
 * Copyright (c) 2009-2016 ARM Limited. All rights reserved.
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


 .syntax unified
  .cpu cortex-m0plus
  .fpu softvfp
  .thumb

.global  g_pfnVectors
.global  Default_Handler

/* start address for the initialization values of the .data section.
defined in linker script */
.word  _sidata
/* start address for the .data section. defined in linker script */
.word  _sdata
/* end address for the .data section. defined in linker script */
.word  _edata
/* start address for the .bss section. defined in linker script */
.word  _sbss
/* end address for the .bss section. defined in linker script */
.word  _ebss

    .section  .text.Reset_Handler
  .weak  Reset_Handler
  .type  Reset_Handler, %function
Reset_Handler:  
   ldr   r0, =_estack
   mov   sp, r0          /* set stack pointer */

/* Copy the data segment initializers from flash to SRAM */
  movs  r1, #0
  b  LoopCopyDataInit

CopyDataInit:
  ldr  r3, =_sidata
  ldr  r3, [r3, r1]
  str  r3, [r0, r1]
  adds  r1, r1, #4

LoopCopyDataInit:
  ldr  r0, =_sdata
  ldr  r3, =_edata
  adds  r2, r0, r1
  cmp  r2, r3
  bcc  CopyDataInit
  ldr  r2, =_sbss
  b  LoopFillZerobss
/* Zero fill the bss segment. */
FillZerobss:
  movs  r3, #0
  str  r3, [r2]
  adds r2, r2, #4


LoopFillZerobss:
  ldr  r3, = _ebss
  cmp  r2, r3
  bcc  FillZerobss

/* Call the clock system intitialization function.*/
  bl  SystemInit
/* Call static constructors */
    bl __libc_init_array
/* Call the application's entry point.*/
  bl  main

LoopForever:
    b LoopForever


.size  Reset_Handler, .-Reset_Handler

/**
 * @brief  This is the code that gets called when the processor receives an
 *         unexpected interrupt.  This simply enters an infinite loop, preserving
 *         the system state for examination by a debugger.
 *
 * @param  None
 * @retval : None
*/
    .section  .text.Default_Handler,"ax",%progbits
Default_Handler:
Infinite_Loop:
  b  Infinite_Loop
  .size  Default_Handler, .-Default_Handler
/******************************************************************************
*
* The minimal vector table for a Cortex M0.  Note that the proper constructs
* must be placed on this to ensure that it ends up at physical address
* 0x0000.0000.
*
******************************************************************************/
   .section  .isr_vector,"a",%progbits
  .type  g_pfnVectors, %object
  .size  g_pfnVectors, .-g_pfnVectors
  
  
g_pfnVectors:
	.word  _estack
	.word	Reset_Handler         /* Reset Handler */
	.word	NMI_Handler           /* NMI Handler */
	.word	HardFault_Handler     /* Hard Fault Handler */
	.word	0                     /* Reserved */
	.word	0                     /* Reserved */
	.word	0                     /* Reserved */
	.word	0                     /* Reserved */
	.word	0                     /* Reserved */
	.word	0                     /* Reserved */
	.word	0                     /* Reserved */
	.word	SVC_Handler           /* SVCall Handler */
	.word	0                     /* Reserved */
	.word	0                     /* Reserved */
	.word	PendSV_Handler        /* PendSV Handler */
	.word	SysTick_Handler       /* SysTick Handler */

	/* External interrupts */
/* ToDo:  Add here the vectors for the device specific external interrupts handler */
	.word	IRQ00_Handler              		/*  IRQ00: Handler         */
	.word	IRQ01_Handler              		/*  IRQ01: Handler         */
	.word	IRQ02_Handler              		/*  IRQ02: Handler         */
	.word	IRQ03_Handler              		/*  IRQ03: Handler         */
	.word	IRQ04_Handler              		/*  IRQ04: Handler         */
	.word	IRQ05_Handler              		/*  IRQ05: Handler         */
	.word	IRQ06_Handler              		/*  IRQ06: Handler         */
	.word	IRQ07_Handler              		/*  IRQ07: Handler         */
	.word	IRQ08_Handler              		/*  IRQ08: Handler         */
	.word	IRQ09_Handler              		/*  IRQ09: Handler         */
	.word	IRQ10_Handler              		/*  IRQ10: Handler         */
	.word	IRQ11_Handler              		/*  IRQ11: Handler         */
	.word	IRQ12_Handler              		/*  IRQ12: Handler         */
	.word	IRQ13_Handler              		/*  IRQ13: Handler         */
	.word	IRQ14_Handler              		/*  IRQ14: Handler         */
	.word	IRQ15_Handler              		/*  IRQ15: Handler         */
	.word	IRQ16_Handler              		/*  IRQ16: Handler         */
	.word	IRQ17_Handler              		/*  IRQ17: Handler         */
	.word	IRQ18_Handler              		/*  IRQ18: Handler         */
	.word	IRQ19_Handler              		/*  IRQ19: Handler         */
	.word	IRQ20_Handler              		/*  IRQ20: Handler         */
	.word	IRQ21_Handler              		/*  IRQ21: Handler         */
	.word	IRQ22_Handler              		/*  IRQ22: Handler         */
	.word	IRQ23_Handler              		/*  IRQ23: Handler         */
	.word	IRQ24_Handler              		/*  IRQ24: Handler         */
	.word	IRQ25_Handler              		/*  IRQ25: Handler         */
	.word	IRQ26_Handler              		/*  IRQ26: Handler         */
	.word	IRQ27_Handler              		/*  IRQ27: Handler         */
	.word	IRQ28_Handler              		/*  IRQ28: Handler         */
	.word	IRQ29_Handler              		/*  IRQ29: Handler         */
	.word	IRQ30_Handler              		/*  IRQ30: Handler         */
	.word	IRQ31_Handler              		/*  IRQ31: Handler         */

/*******************************************************************************
*
* Provide weak aliases for each Exception handler to the Default_Handler.
* As they are weak aliases, any function with the same name will override
* this definition.
*
*******************************************************************************/

   .weak      NMI_Handler
   .thumb_set NMI_Handler,Default_Handler

   .weak      HardFault_Handler
   .thumb_set HardFault_Handler,Default_Handler

   .weak      SVC_Handler
   .thumb_set SVC_Handler,Default_Handler

   .weak      PendSV_Handler
   .thumb_set PendSV_Handler,Default_Handler

   .weak      SysTick_Handler
   .thumb_set SysTick_Handler,Default_Handler

   .weak      IRQ00_Handler
   .thumb_set IRQ00_Handler,Default_Handler

   .weak      IRQ01_Handler
   .thumb_set IRQ01_Handler,Default_Handler

		.weak      IRQ02_Handler
   .thumb_set IRQ02_Handler,Default_Handler

   .weak      IRQ03_Handler
   .thumb_set IRQ03_Handler,Default_Handler

		.weak      IRQ04_Handler
   .thumb_set IRQ04_Handler,Default_Handler

   .weak      IRQ05_Handler
   .thumb_set IRQ05_Handler,Default_Handler

		.weak      IRQ06_Handler
   .thumb_set IRQ06_Handler,Default_Handler

   .weak      IRQ07_Handler
   .thumb_set IRQ07_Handler,Default_Handler

	.weak      IRQ08_Handler
   .thumb_set IRQ08_Handler,Default_Handler

   .weak      IRQ09_Handler
   .thumb_set IRQ09_Handler,Default_Handler

		.weak      IRQ10_Handler
   .thumb_set IRQ10_Handler,Default_Handler

   .weak      IRQ11_Handler
   .thumb_set IRQ11_Handler,Default_Handler

		.weak      IRQ12_Handler
   .thumb_set IRQ12_Handler,Default_Handler

   .weak      IRQ13_Handler
   .thumb_set IRQ13_Handler,Default_Handler

		.weak      IRQ14_Handler
   .thumb_set IRQ14_Handler,Default_Handler

   .weak      IRQ15_Handler
   .thumb_set IRQ15_Handler,Default_Handler

		.weak      IRQ16_Handler
   .thumb_set IRQ16_Handler,Default_Handler

   .weak      IRQ17_Handler
   .thumb_set IRQ17_Handler,Default_Handler

	.weak      IRQ18_Handler
   .thumb_set IRQ18_Handler,Default_Handler

   .weak      IRQ19_Handler
   .thumb_set IRQ19_Handler,Default_Handler

		.weak      IRQ20_Handler
   .thumb_set IRQ20_Handler,Default_Handler

   .weak      IRQ21_Handler
   .thumb_set IRQ21_Handler,Default_Handler

		.weak      IRQ22_Handler
   .thumb_set IRQ22_Handler,Default_Handler

   .weak      IRQ23_Handler
   .thumb_set IRQ23_Handler,Default_Handler

		.weak      IRQ24_Handler
   .thumb_set IRQ24_Handler,Default_Handler

   .weak      IRQ25_Handler
   .thumb_set IRQ25_Handler,Default_Handler

		.weak      IRQ26_Handler
   .thumb_set IRQ26_Handler,Default_Handler

   .weak      IRQ27_Handler
   .thumb_set IRQ27_Handler,Default_Handler

	.weak      IRQ28_Handler
   .thumb_set IRQ28_Handler,Default_Handler

   .weak      IRQ29_Handler
   .thumb_set IRQ29_Handler,Default_Handler
		
		.weak      IRQ30_Handler
   .thumb_set IRQ30_Handler,Default_Handler

   .weak      IRQ31_Handler
   .thumb_set IRQ31_Handler,Default_Handler
