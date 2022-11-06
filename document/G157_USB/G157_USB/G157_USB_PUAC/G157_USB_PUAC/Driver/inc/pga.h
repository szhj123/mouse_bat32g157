/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    pga.h
* @brief   This file implements device driver for PGA module.
* @version 1.0.0
* @date    2020/10/24
***********************************************************************************************************************/
#ifndef PGA_H
#define PGA_H

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/
/*
    PGA control register (PGACTL) 
*/
/* PGA operation selection (PGAEN) */
#define _00_PGA_OPERATION_STOP                        (0x00U) /* PGA operation stopped */
#define _80_PGA_OPERATION_ENABLE                      (0x80U) /* PGA operation enabled */
/* GND selection of feedback resistance of the programmable gain amplifier (PVRVS) */
#define _00_PGA_VSS_SELECTED                          (0x00U) /* selects VSS */
#define _08_PGA_PGAGND_SELECTED                       (0x08U) /* selects PGAGND */
/* Selected PGA amplification (PGAVG1,PGAVG0) */
#define _00_PGA_AMPLIFICATION_X1                      (0x00U) /* *1 is selected as the gain */
#define _01_PGA_AMPLIFICATION_X2                      (0x01U) /* *2 is selected as the gain */
#define _02_PGA_AMPLIFICATION_X4                      (0x02U) /* *4 is selected as the gain */
#define _03_PGA_AMPLIFICATION_X8                      (0x03U) /* *8 is selected as the gain */
#define _04_PGA_AMPLIFICATION_X16                     (0x04U) /* *16 is selected as the gain */
#define _05_PGA_AMPLIFICATION_X32                     (0x05U) /* *32 is selected as the gain */
#define _06_PGA_AMPLIFICATION_X64                     (0x06U) /* *64 is selected as the gain */
#define _07_PGA_AMPLIFICATION_X128                    (0x07U) /* *128 is selected as the gain */

#define PGAEN                                         (0x80U) /* PGA operation enabled */
#define C0MON                                         (1<<3U) /* CMP0 monitor flag */
#define C1MON                                         (1<<7U) /* CMP1 monitor flag */

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef enum 
{
    PGA_CHANNEL_0 = 1U,  // PGA0
    PGA_CHANNEL_1 = 2U,  // PGA1
    PGA_CHANNEL_A = 3U   // PGA0 & PGA1
} pga_channel_t;

typedef enum 
{
    PGA_VSS_REFERENCE_VOLTAGE    = 0U,  // Select VSS as GROUND of feedback resistance string 
    PGA_PGAGND_REFERENCE_VOLTAGE = 1U,  // Select PGAIN as PGA0+  , Select PGAGND as PGA0-   
    PGA_PGAGND_PGAIN_VOLTAGE     = 3U   // Select PGAGND as PGA0+ , Select PGAIN as PGA0-
} pga_vref_t;

typedef enum 
{
    PGA_GAIN_X1   = 0U,  // X1
    PGA_GAIN_X2   = 1U,  // X2
    PGA_GAIN_X4   = 2U,  // X4
    PGA_GAIN_X8   = 3U,  // X8
    PGA_GAIN_X16  = 4U,  // X16
    PGA_GAIN_X32  = 5U,  // X32
    PGA_GAIN_X64  = 6U,  // X64
    PGA_GAIN_X128 = 7U   // X128	
} pga_gain_t;

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
void PGA_Init(pga_channel_t ch, pga_vref_t vref, pga_gain_t gain, uint8_t pgaoen);
void PGA_Start(pga_channel_t ch);
void PGA_Stop(pga_channel_t ch);
/* Start user code for function. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#endif

