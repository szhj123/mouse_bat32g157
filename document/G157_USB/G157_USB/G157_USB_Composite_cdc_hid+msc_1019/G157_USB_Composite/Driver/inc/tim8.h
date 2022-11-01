/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    tim8.h
* @brief   This file implements device driver for TM4 module.
* @version 1.0.0
* @date    2020/10/24
***********************************************************************************************************************/
#ifndef TM8_H
#define TM8_H

#include <stdio.h>

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/
/*
    Timer Clock Select Register m (TPSm) 
*/
/* Operating mode and clear mode selection (PRSm03,PRSm02,PRSm01,PRSm00) */
#define _0000_TM8_CKM0_fCLK_0                   (0x0000U) /* ckm0 - fCLK */
#define _0001_TM8_CKM0_fCLK_1                   (0x0001U) /* ckm0 - fCLK/2^1 */
#define _0002_TM8_CKM0_fCLK_2                   (0x0002U) /* ckm0 - fCLK/2^2 */
#define _0003_TM8_CKM0_fCLK_3                   (0x0003U) /* ckm0 - fCLK/2^3 */
#define _0004_TM8_CKM0_fCLK_4                   (0x0004U) /* ckm0 - fCLK/2^4 */
#define _0005_TM8_CKM0_fCLK_5                   (0x0005U) /* ckm0 - fCLK/2^5 */
#define _0006_TM8_CKM0_fCLK_6                   (0x0006U) /* ckm0 - fCLK/2^6 */
#define _0007_TM8_CKM0_fCLK_7                   (0x0007U) /* ckm0 - fCLK/2^7 */
#define _0008_TM8_CKM0_fCLK_8                   (0x0008U) /* ckm0 - fCLK/2^8 */
#define _0009_TM8_CKM0_fCLK_9                   (0x0009U) /* ckm0 - fCLK/2^9 */
#define _000A_TM8_CKM0_fCLK_10                  (0x000AU) /* ckm0 - fCLK/2^10 */
#define _000B_TM8_CKM0_fCLK_11                  (0x000BU) /* ckm0 - fCLK/2^11 */
#define _000C_TM8_CKM0_fCLK_12                  (0x000CU) /* ckm0 - fCLK/2^12 */
#define _000D_TM8_CKM0_fCLK_13                  (0x000DU) /* ckm0 - fCLK/2^13 */
#define _000E_TM8_CKM0_fCLK_14                  (0x000EU) /* ckm0 - fCLK/2^14 */
#define _000F_TM8_CKM0_fCLK_15                  (0x000FU) /* ckm0 - fCLK/2^15 */
/* Operating mode and clear mode selection (PRSm13,PRSm12,PRSm11,PRSm10) */
#define _0000_TM8_CKM1_fCLK_0                   (0x0000U) /* ckm1 - fCLK */
#define _0010_TM8_CKM1_fCLK_1                   (0x0010U) /* ckm1 - fCLK/2^1 */
#define _0020_TM8_CKM1_fCLK_2                   (0x0020U) /* ckm1 - fCLK/2^2 */
#define _0030_TM8_CKM1_fCLK_3                   (0x0030U) /* ckm1 - fCLK/2^3 */
#define _0040_TM8_CKM1_fCLK_4                   (0x0040U) /* ckm1 - fCLK/2^4 */
#define _0050_TM8_CKM1_fCLK_5                   (0x0050U) /* ckm1 - fCLK/2^5 */
#define _0060_TM8_CKM1_fCLK_6                   (0x0060U) /* ckm1 - fCLK/2^6 */
#define _0070_TM8_CKM1_fCLK_7                   (0x0070U) /* ckm1 - fCLK/2^7 */
#define _0080_TM8_CKM1_fCLK_8                   (0x0080U) /* ckm1 - fCLK/2^8 */
#define _0090_TM8_CKM1_fCLK_9                   (0x0090U) /* ckm1 - fCLK/2^9 */
#define _00A0_TM8_CKM1_fCLK_10                  (0x00A0U) /* ckm1 - fCLK/2^10 */
#define _00B0_TM8_CKM1_fCLK_11                  (0x00B0U) /* ckm1 - fCLK/2^11 */
#define _00C0_TM8_CKM1_fCLK_12                  (0x00C0U) /* ckm1 - fCLK/2^12 */
#define _00D0_TM8_CKM1_fCLK_13                  (0x00D0U) /* ckm1 - fCLK/2^13 */
#define _00E0_TM8_CKM1_fCLK_14                  (0x00E0U) /* ckm1 - fCLK/2^14 */
#define _00F0_TM8_CKM1_fCLK_15                  (0x00F0U) /* ckm1 - fCLK/2^15 */
/* Operating mode and clear mode selection (PRSm21,PRSm20) */
#define _0000_TM8_CKM2_fCLK_1                   (0x0000U) /* ckm2 - fCLK/2^1 */
#define _0100_TM8_CKM2_fCLK_2                   (0x0100U) /* ckm2 - fCLK/2^2 */
#define _0200_TM8_CKM2_fCLK_4                   (0x0200U) /* ckm2 - fCLK/2^4 */
#define _0300_TM8_CKM2_fCLK_6                   (0x0300U) /* ckm2 - fCLK/2^6 */
/* Operating mode and clear mode selection (30PRSm31,PRSm30) */
#define _0000_TM8_CKM3_fCLK_8                   (0x0000U) /* ckm3 - fCLK/2^8 */
#define _1000_TM8_CKM3_fCLK_10                  (0x1000U) /* ckm3 - fCLK/2^10 */
#define _2000_TM8_CKM3_fCLK_12                  (0x2000U) /* ckm3 - fCLK/2^12 */
#define _3000_TM8_CKM3_fCLK_14                  (0x3000U) /* ckm3 - fCLK/2^14 */

/*
    Timer Channel Start Register m (TSm) 
*/
/* Operation enable (start) trigger of channel 7 (TSm7) */
#define _0000_TM8_CH7_START_TRG_OFF             (0x0000U) /* no trigger operation */
#define _0080_TM8_CH7_START_TRG_ON              (0x0080U) /* operation is enabled (start trigger is generated) */
/* Operation enable (start) trigger of channel 6 (TSm6) */
#define _0000_TM8_CH6_START_TRG_OFF             (0x0000U) /* no trigger operation */
#define _0040_TM8_CH6_START_TRG_ON              (0x0040U) /* operation is enabled (start trigger is generated) */
/* Operation enable (start) trigger of channel 5 (TSm5) */
#define _0000_TM8_CH5_START_TRG_OFF             (0x0000U) /* no trigger operation */
#define _0020_TM8_CH5_START_TRG_ON              (0x0020U) /* operation is enabled (start trigger is generated) */
/* Operation enable (start) trigger of channel 4 (TSm4) */
#define _0000_TM8_CH4_START_TRG_OFF             (0x0000U) /* no trigger operation */
#define _0010_TM8_CH4_START_TRG_ON              (0x0010U) /* operation is enabled (start trigger is generated) */
/* Operation enable (start) trigger of channel 3 (TSm3) */
#define _0000_TM8_CH3_START_TRG_OFF             (0x0000U) /* no trigger operation */
#define _0008_TM8_CH3_START_TRG_ON              (0x0008U) /* operation is enabled (start trigger is generated) */
/* Operation enable (start) trigger of channel 2 (TSm2) */
#define _0000_TM8_CH2_START_TRG_OFF             (0x0000U) /* no trigger operation */
#define _0004_TM8_CH2_START_TRG_ON              (0x0004U) /* operation is enabled (start trigger is generated) */
/* Operation enable (start) trigger of channel 1 (TSm1) */
#define _0000_TM8_CH1_START_TRG_OFF             (0x0000U) /* no trigger operation */
#define _0002_TM8_CH1_START_TRG_ON              (0x0002U) /* operation is enabled (start trigger is generated) */
/* Operation enable (start) trigger of channel 0 (TSm0) */
#define _0000_TM8_CH0_START_TRG_OFF             (0x0000U) /* no trigger operation */
#define _0001_TM8_CH0_START_TRG_ON              (0x0001U) /* operation is enabled (start trigger is generated) */

/*
    Timer Channel Stop Register m (TTm) 
*/

/* Operation stop trigger of channel 7 (TTm7) */
#define _0000_TM8_CH7_STOP_TRG_OFF              (0x0000U) /* no trigger operation */
#define _0080_TM8_CH7_STOP_TRG_ON               (0x0080U) /* operation is stopped (stop trigger is generated) */
/* Operation stop trigger of channel 6 (TTm6) */
#define _0000_TM8_CH6_STOP_TRG_OFF              (0x0000U) /* no trigger operation */
#define _0040_TM8_CH6_STOP_TRG_ON               (0x0040U) /* operation is stopped (stop trigger is generated) */
/* Operation stop trigger of channel 5 (TTm5) */
#define _0000_TM8_CH5_STOP_TRG_OFF              (0x0000U) /* no trigger operation */
#define _0020_TM8_CH5_STOP_TRG_ON               (0x0020U) /* operation is stopped (stop trigger is generated) */
/* Operation stop trigger of channel 4 (TTm4) */
#define _0000_TM8_CH4_STOP_TRG_OFF              (0x0000U) /* no trigger operation */
#define _0010_TM8_CH4_STOP_TRG_ON               (0x0010U) /* operation is stopped (stop trigger is generated) */
/* Operation stop trigger of channel 3 (TTm3) */
#define _0000_TM8_CH3_STOP_TRG_OFF              (0x0000U) /* no trigger operation */
#define _0008_TM8_CH3_STOP_TRG_ON               (0x0008U) /* operation is stopped (stop trigger is generated) */
/* Operation stop trigger of channel 2 (TTm2) */
#define _0000_TM8_CH2_STOP_TRG_OFF              (0x0000U) /* no trigger operation */
#define _0004_TM8_CH2_STOP_TRG_ON               (0x0004U) /* operation is stopped (stop trigger is generated) */
/* Operation stop trigger of channel 1 (TTm1) */
#define _0000_TM8_CH1_STOP_TRG_OFF              (0x0000U) /* no trigger operation */
#define _0002_TM8_CH1_STOP_TRG_ON               (0x0002U) /* operation is stopped (stop trigger is generated) */
/* Operation stop trigger of channel 0 (TTm0) */
#define _0000_TM8_CH0_STOP_TRG_OFF              (0x0000U) /* no trigger operation */
#define _0001_TM8_CH0_STOP_TRG_ON               (0x0001U) /* operation is stopped (stop trigger is generated) */
/*
    Timer Mode Register mn (TMRmn) 
*/
/* Selection of macro clock (MCK) of channel n (CKSmn1,CKSmn0) */
#define _0000_TM8_CLOCK_SELECT_CKM0             (0x0000U) /* operation clock CK0 set by PRS register */
#define _8000_TM8_CLOCK_SELECT_CKM1             (0x8000U) /* operation clock CK1 set by PRS register */
#define _4000_TM8_CLOCK_SELECT_CKM2             (0x4000U) /* operation clock CK2 set by PRS register */
#define _C000_TM8_CLOCK_SELECT_CKM3             (0xC000U) /* operation clock CK3 set by PRS register */
/* Selection of count clock (CCK) of channel n (CCSmn) */
#define _0000_TM8_CLOCK_MODE_CKS                (0x0000U) /* macro clock MCK specified by CKSmn bit */
#define _1000_TM8_CLOCK_MODE_TIMN               (0x1000U) /* valid edge of input signal input from TImn pin */
/* Operation explanation of channel 1 or 3 (SPLITmn) */
#define _0000_TM8_16BITS_MODE                   (0x0000U) /* operates as 16 bits timer */
#define _0800_TM8_8BITS_MODE                    (0x0800U) /* operates as 8 bits timer */
/* Selection of slave/master of channel n (MASTERmn) */
#define _0000_TM8_COMBINATION_SLAVE             (0x0000U) /* operates as slave channel */
#define _0800_TM8_COMBINATION_MASTER            (0x0800U) /* operates as master channel */
/* Setting of start trigger or capture trigger of channel n (STSmn2,STSmn1,STSmn0) */
#define _0000_TM8_TRIGGER_SOFTWARE              (0x0000U) /* only software trigger start is valid */
#define _0100_TM8_TRIGGER_TIMN_VALID            (0x0100U) /* TImn input edge is used as a start/capture trigger */
#define _0200_TM8_TRIGGER_TIMN_BOTH             (0x0200U) /* TImn input edges are used as a start/capture trigger */
#define _0400_TM8_TRIGGER_MASTER_INT            (0x0400U) /* interrupt signal of the master channel is used */
/* Selection of TImn pin input valid edge (CISmn1,CISmn0) */
#define _0000_TM8_TIMN_EDGE_FALLING             (0x0000U) /* falling edge */
#define _0040_TM8_TIMN_EDGE_RISING              (0x0040U) /* rising edge */
#define _0080_TM8_TIMN_EDGE_BOTH_LOW            (0x0080U) /* both edges (when low-level width is measured) */
#define _00C0_TM8_TIMN_EDGE_BOTH_HIGH           (0x00C0U) /* both edges (when high-level width is measured) */
/* Operation mode of channel n (MDmn3,MDmn2,MDmn1) */
#define _0000_TM8_MODE_INTERVAL_TIMER           (0x0000U) /* interval timer mode */
#define _0004_TM8_MODE_CAPTURE                  (0x0004U) /* capture mode */
#define _0006_TM8_MODE_EVENT_COUNT              (0x0006U) /* event counter mode */
#define _0008_TM8_MODE_ONE_COUNT                (0x0008U) /* one count mode */
#define _000C_TM8_MODE_HIGHLOW_MEASURE          (0x000CU) /* high-/low-level width measurement mode */
/* Setting of starting counting and interrupt (MDmn0) */
#define _0000_TM8_START_INT_UNUSED              (0x0000U) /* interrupt is not generated when counting is started */
#define _0001_TM8_START_INT_USED                (0x0001U) /* interrupt is generated when counting is started */
/* Operation mode of channel n (MDmn3,MDmn2,MDmn1,MDmn0) */
#define _0001_TM8_MODE_PWM_MASTER               (0x0001U) /* PWM function (master channel) mode */
#define _0009_TM8_MODE_PWM_SLAVE                (0x0009U) /* PWM function (slave channel) mode */
#define _0008_TM8_MODE_ONESHOT                  (0x0008U) /* one-shot pulse output mode */

/*
    Timer Output Mode Register m (TOMm) 
*/
/* Control of timer output mode of channel 7 (TOMm7) */
#define _0000_TM8_CH7_MASTER_OUTPUT             (0x0000U) /* master channel output mode */
#define _0080_TM8_CH7_SLAVE_OUTPUT              (0x0080U) /* slave channel output mode */
/* Control of timer output mode of channel 6 (TOMm6) */
#define _0000_TM8_CH6_MASTER_OUTPUT             (0x0000U) /* master channel output mode */
#define _0040_TM8_CH6_SLAVE_OUTPUT              (0x0040U) /* slave channel output mode */
/* Control of timer output mode of channel 5 (TOMm5) */
#define _0000_TM8_CH5_MASTER_OUTPUT             (0x0000U) /* master channel output mode */
#define _0020_TM8_CH5_SLAVE_OUTPUT              (0x0020U) /* slave channel output mode */
/* Control of timer output mode of channel 4 (TOMm4) */
#define _0000_TM8_CH4_MASTER_OUTPUT             (0x0000U) /* master channel output mode */
#define _0010_TM8_CH4_SLAVE_OUTPUT              (0x0010U) /* slave channel output mode */
/* Control of timer output mode of channel 3 (TOMm3) */
#define _0000_TM8_CH3_MASTER_OUTPUT             (0x0000U) /* master channel output mode */
#define _0008_TM8_CH3_SLAVE_OUTPUT              (0x0008U) /* slave channel output mode */
/* Control of timer output mode of channel 2 (TOMm2) */
#define _0000_TM8_CH2_MASTER_OUTPUT             (0x0000U) /* master channel output mode */
#define _0004_TM8_CH2_SLAVE_OUTPUT              (0x0004U) /* slave channel output mode */
/* Control of timer output mode of channel 1 (TOMm1) */
#define _0000_TM8_CH1_MASTER_OUTPUT             (0x0000U) /* master channel output mode */
#define _0002_TM8_CH1_SLAVE_OUTPUT              (0x0002U) /* slave channel output mode */
/*
    Timer Output Level Register 0 (TOLm) 
*/
/* Control of timer output level of channel 7 (TOLm7) */
#define _0000_TM8_CH7_OUTPUT_LEVEL_H            (0x0000U) /* positive logic output (active-high) */
#define _0080_TM8_CH7_OUTPUT_LEVEL_L            (0x0080U) /* inverted output (active-low) */
/* Control of timer output level of channel 6 (TOLm6) */
#define _0000_TM8_CH6_OUTPUT_LEVEL_H            (0x0000U) /* positive logic output (active-high) */
#define _0040_TM8_CH6_OUTPUT_LEVEL_L            (0x0040U) /* inverted output (active-low) */
/* Control of timer output level of channel 5 (TOLm5) */
#define _0000_TM8_CH5_OUTPUT_LEVEL_H            (0x0000U) /* positive logic output (active-high) */
#define _0020_TM8_CH5_OUTPUT_LEVEL_L            (0x0020U) /* inverted output (active-low) */
/* Control of timer output level of channel 4 (TOLm4) */
#define _0000_TM8_CH4_OUTPUT_LEVEL_H            (0x0000U) /* positive logic output (active-high) */
#define _0010_TM8_CH4_OUTPUT_LEVEL_L            (0x0010U) /* inverted output (active-low) */
/* Control of timer output level of channel 3 (TOLm3) */
#define _0000_TM8_CH3_OUTPUT_LEVEL_H            (0x0000U) /* positive logic output (active-high) */
#define _0008_TM8_CH3_OUTPUT_LEVEL_L            (0x0008U) /* inverted output (active-low) */
/* Control of timer output level of channel 2 (TOLm2) */
#define _0000_TM8_CH2_OUTPUT_LEVEL_H            (0x0000U) /* positive logic output (active-high) */
#define _0004_TM8_CH2_OUTPUT_LEVEL_L            (0x0004U) /* inverted output (active-low) */
/* Control of timer output level of channel 1 (TOLm1) */
#define _0000_TM8_CH1_OUTPUT_LEVEL_H            (0x0000U) /* positive logic output (active-high) */
#define _0002_TM8_CH1_OUTPUT_LEVEL_L            (0x0002U) /* inverted output (active-low) */

/*
    Timer Output Register m (TOm) 
*/
/* Timer output of channel 7 (TOm7) */
#define _0000_TM8_CH7_OUTPUT_VALUE_0            (0x0000U) /* timer output value is "0" */
#define _0080_TM8_CH7_OUTPUT_VALUE_1            (0x0080U) /* timer output value is "1" */
/* Timer output of channel 6 (TOm6) */
#define _0000_TM8_CH6_OUTPUT_VALUE_0            (0x0000U) /* timer output value is "0" */
#define _0040_TM8_CH6_OUTPUT_VALUE_1            (0x0040U) /* timer output value is "1" */
/* Timer output of channel 5 (TOm5) */
#define _0000_TM8_CH5_OUTPUT_VALUE_0            (0x0000U) /* timer output value is "0" */
#define _0020_TM8_CH5_OUTPUT_VALUE_1            (0x0020U) /* timer output value is "1" */
/* Timer output of channel 4 (TOm4) */
#define _0000_TM8_CH4_OUTPUT_VALUE_0            (0x0000U) /* timer output value is "0" */
#define _0010_TM8_CH4_OUTPUT_VALUE_1            (0x0010U) /* timer output value is "1" */
/* Timer output of channel 3 (TOm3) */
#define _0000_TM8_CH3_OUTPUT_VALUE_0            (0x0000U) /* timer output value is "0" */
#define _0008_TM8_CH3_OUTPUT_VALUE_1            (0x0008U) /* timer output value is "1" */
/* Timer output of channel 2 (TOm2) */
#define _0000_TM8_CH2_OUTPUT_VALUE_0            (0x0000U) /* timer output value is "0" */
#define _0004_TM8_CH2_OUTPUT_VALUE_1            (0x0004U) /* timer output value is "1" */
/* Timer output of channel 1 (TOm1) */
#define _0000_TM8_CH1_OUTPUT_VALUE_0            (0x0000U) /* timer output value is "0" */
#define _0002_TM8_CH1_OUTPUT_VALUE_1            (0x0002U) /* timer output value is "1" */
/* Timer output of channel 0 (TOm0) */
#define _0000_TM8_CH0_OUTPUT_VALUE_0            (0x0000U) /* timer output value is "0" */
#define _0001_TM8_CH0_OUTPUT_VALUE_1            (0x0001U) /* timer output value is "1" */

/*
    Timer Output Enable Register m (TOEm) 
*/
/* Timer output enable/disable of channel 7 (TOEm7) */
#define _0000_TM8_CH7_OUTPUT_DISABLE            (0x0000U) /* timer output is disabled */
#define _0080_TM8_CH7_OUTPUT_ENABLE             (0x0080U) /* timer output is enabled */
/* Timer output enable/disable of channel 6 (TOEm6) */
#define _0000_TM8_CH6_OUTPUT_DISABLE            (0x0000U) /* timer output is disabled */
#define _0040_TM8_CH6_OUTPUT_ENABLE             (0x0040U) /* timer output is enabled */
/* Timer output enable/disable of channel 5 (TOEm5) */
#define _0000_TM8_CH5_OUTPUT_DISABLE            (0x0000U) /* timer output is disabled */
#define _0020_TM8_CH5_OUTPUT_ENABLE             (0x0020U) /* timer output is enabled */
/* Timer output enable/disable of channel 4 (TOEm4) */
#define _0000_TM8_CH4_OUTPUT_DISABLE            (0x0000U) /* timer output is disabled */
#define _0010_TM8_CH4_OUTPUT_ENABLE             (0x0010U) /* timer output is enabled */
/* Timer output enable/disable of channel 3 (TOEm3) */
#define _0000_TM8_CH3_OUTPUT_DISABLE            (0x0000U) /* timer output is disabled */
#define _0008_TM8_CH3_OUTPUT_ENABLE             (0x0008U) /* timer output is enabled */
/* Timer output enable/disable of channel 2 (TOEm2) */
#define _0000_TM8_CH2_OUTPUT_DISABLE            (0x0000U) /* timer output is disabled */
#define _0004_TM8_CH2_OUTPUT_ENABLE             (0x0004U) /* timer output is enabled */
/* Timer output enable/disable of channel 1 (TOEm1) */
#define _0000_TM8_CH1_OUTPUT_DISABLE            (0x0000U) /* timer output is disabled */
#define _0002_TM8_CH1_OUTPUT_ENABLE             (0x0002U) /* timer output is enabled */
/* Timer output enable/disable of channel 0 (TOEm0) */
#define _0000_TM8_CH0_OUTPUT_DISABLE            (0x0000U) /* timer output is disabled */
#define _0001_TM8_CH0_OUTPUT_ENABLE             (0x0001U) /* timer output is enabled */

/*
    Noise Filter Enable Register 1  (NFEN1) 
*/
/* Enable/disable using noise filter of TI17 pin input signal (TNFEN17) */
#define _00_TM8_CH7_NOISE_OFF                   (0x00U) /* noise filter OFF */
#define _80_TM8_CH7_NOISE_ON                    (0x80U) /* noise filter ON */
/* Enable/disable using noise filter of TI16 pin input signal (TNFEN16) */
#define _00_TM8_CH6_NOISE_OFF                   (0x00U) /* noise filter OFF */
#define _40_TM8_CH6_NOISE_ON                    (0x40U) /* noise filter ON */
/* Enable/disable using noise filter of TI15 pin input signal (TNFEN15) */
#define _00_TM8_CH5_NOISE_OFF                   (0x00U) /* noise filter OFF */
#define _20_TM8_CH5_NOISE_ON                    (0x20U) /* noise filter ON */
/* Enable/disable using noise filter of TI14 pin input signal (TNFEN14) */
#define _00_TM8_CH4_NOISE_OFF                   (0x00U) /* noise filter OFF */
#define _10_TM8_CH4_NOISE_ON                    (0x10U) /* noise filter ON */
/* Enable/disable using noise filter of TI13 pin input signal (TNFEN13) */
#define _00_TM8_CH3_NOISE_OFF                   (0x00U) /* noise filter OFF */
#define _08_TM8_CH3_NOISE_ON                    (0x08U) /* noise filter ON */
/* Enable/disable using noise filter of TI12 pin input signal (TNFEN12) */
#define _00_TM8_CH2_NOISE_OFF                   (0x00U) /* noise filter OFF */
#define _04_TM8_CH2_NOISE_ON                    (0x04U) /* noise filter ON */
/* Enable/disable using noise filter of TI11 pin input signal (TNFEN11) */
#define _00_TM8_CH1_NOISE_OFF                   (0x00U) /* noise filter OFF */
#define _02_TM8_CH1_NOISE_ON                    (0x02U) /* noise filter ON */
/* Enable/disable using noise filter of TI10 pin input signal (TNFEN10) */
#define _00_TM8_CH0_NOISE_OFF                   (0x00U) /* noise filter OFF */
#define _01_TM8_CH0_NOISE_ON                    (0x01U) /* noise filter ON */

/*
    Timer Status Register mn (TSRmn)
*/
/* Counter overflow status of channel n (OVF) */
#define _0000_TM8_OVERFLOW_NOT_OCCURS     (0x0000U) /* overflow does not occur */
#define _0001_TM8_OVERFLOW_OCCURS         (0x0001U) /* overflow occurs */

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
/* Clock divisor for TM81 channel 1 */
#define TM81_CHANNEL1_DIVISOR             (1U)      /* fCLK */

/***********************************************************************************************************************
Register bit definitions
***********************************************************************************************************************/
#define TMRMN_CIS_Pos   6

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef enum 
{
	TM8_CHANNEL_0 = 0x01U,
	TM8_CHANNEL_1 = 0x02U,
	TM8_CHANNEL_2 = 0x04U,
	TM8_CHANNEL_3 = 0x08U,
	TM8_CHANNEL_4 = 0x10U,
	TM8_CHANNEL_5 = 0x20U,
	TM8_CHANNEL_6 = 0x40U,
	TM8_CHANNEL_7 = 0x80U
} tm8_channel_t;

typedef enum 
{
	TM8_TI_NEGEDGE 	 		= (0x00U), /* falling edge of TI */
	TM8_TI_POSEDGE 	 		= (0x01U), /* rising edge of TI */
	TM8_TI_BOTHEDGE 	 	= (0x02U), /* both edge of TI */
} tm8_edge_t;

typedef enum 
{
	TM8_PULSE_PERIOD_FALLING 	= (0x00U), /* measure falling edge interval of TI */
	TM8_PULSE_PERIOD_RISING 	= (0x01U), /* measure rising edge interval of TI */
	TM8_PULSE_PERIOD_BOTH 	 	= (0x02U), /* measure both edge interval of TI */
	TM8_PULSE_WIDTH_LOW 	    = (0x02U), /* measure low level width of TI */
	TM8_PULSE_WIDTH_HIGH 	    = (0x03U)  /* measure high level width of TI */
} tm8_pulse_t;

/***********************************************************************************************************************
Global variables
***********************************************************************************************************************/
/* For TM81 pulse measurement */
extern volatile uint32_t g_tm81_ch0_width;
extern volatile uint32_t g_tm81_ch1_width;
extern volatile uint32_t g_tm81_ch2_width;
extern volatile uint32_t g_tm81_ch3_width;
extern volatile uint32_t g_tm81_ch4_width;
extern volatile uint32_t g_tm81_ch5_width;
extern volatile uint32_t g_tm81_ch6_width;
extern volatile uint32_t g_tm81_ch7_width;
extern volatile uint32_t g_inttm10Taken;
extern volatile uint32_t g_inttm11Taken;
extern volatile uint32_t g_inttm12Taken;
extern volatile uint32_t g_inttm13Taken;
extern volatile uint32_t g_inttm14Taken;
extern volatile uint32_t g_inttm15Taken;
extern volatile uint32_t g_inttm16Taken;
extern volatile uint32_t g_inttm17Taken;


/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
void TM81_IntervalTimer(tm8_channel_t ch, uint16_t num);
void TM81_SquareOutput(tm8_channel_t ch, uint16_t num);
void TM81_FreqDivider(tm8_channel_t ch, tm8_edge_t edge, uint16_t num);
void TM81_EventCount(tm8_channel_t ch, tm8_edge_t edge, uint16_t num);
uint32_t TM81_Get_PulsePeriod(tm8_channel_t ch, tm8_pulse_t edge);
uint32_t TM81_Get_PulseWidth(tm8_channel_t ch, tm8_pulse_t level);
void TM81_DelayCounter(tm8_channel_t ch, tm8_edge_t edge, uint16_t delay);
void TM81_One_Shot_Pulse_Output(tm8_edge_t edge, uint16_t delay, uint16_t width);
void TM81_PWM_1Period_1Duty(uint16_t period, uint16_t duty);
void TM81_PWM_1Period_2Duty(uint16_t period, uint16_t duty1, uint16_t duty2);
void TM81_PWM_1Period_3Duty(uint16_t period, uint16_t duty1, uint16_t duty2, uint16_t duty3);
void TM81_PWM_2Period_2Duty(uint16_t period1, uint16_t duty1, uint16_t period2, uint16_t duty2);
void TM81_Channel_Start(tm8_channel_t ch);
void TM81_Channel_Stop(tm8_channel_t ch);

#endif
