/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    clk.h
* @brief   This file implements device driver for clock generate module.
* @version 1.0.0 
* @date    2020/10/24
***********************************************************************************************************************/
#ifndef CLK_H
#define CLK_H

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/
/*
    Clock operation mode control register (CMC) 
*/
/* Control of X1 clock oscillation frequency (AMPH) */
#define _00_CGC_SYSOSC_UNDER10M                    (0x00U) /* 1MHz <= fX <= 10MHz */
#define _01_CGC_SYSOSC_OVER10M                     (0x01U) /* 10MHz < fX <= 20MHz */
/* XT1 oscillator oscillation mode selection (AMPHS1,AMPHS0) */
#define _00_CGC_LOW_OSCILLATION                    (0x00U) /* low power consumption oscillation */
#define _02_CGC_NORMAL_OSCILLATION                 (0x02U) /* normal oscillation */
#define _04_CGC_ULTRA_LOW_OSCILLATION              (0x04U) /* ultra-low power consumption oscillation */
/* Subsystem clock pin operation mode (EXCLKS,OSCSELS) */
#define _00_CGC_SUB_PORT                           (0x00U) /* XT1, XT2 as I/O port */
#define _10_CGC_SUB_OSC                            (0x10U) /* XT1, XT2 as crystal connection */
#define _20_CGC_SUB_PORT1                          (0x20U) /* XT1, XT2 as I/O port */
#define _30_CGC_SUB_EXT                            (0x30U) /* XT1 as I/O port, XT2 as external clock input */
#define _30_CGC_SUB_PIN                            (0x30U) /* XT1, XT2 pin setting */
/* High-speed system clock pin operation mode (EXCLK,OSCSEL) */
#define _00_CGC_HISYS_PORT                         (0x00U) /* X1, X2 as I/O port */
#define _40_CGC_HISYS_OSC                          (0x40U) /* X1, X2 as crystal/ceramic resonator connection */
#define _80_CGC_HISYS_PORT1                        (0x80U) /* X1, X2 as I/O port */
#define _C0_CGC_HISYS_EXT                          (0xC0U) /* X1 as I/O port, X2 as external clock input */
#define _C0_CGC_HISYS_PIN                          (0xC0U) /* X1, X2 pin setting */

/*
    System clock control register (CKC) 
*/
/* Main system clock (fMAIN) operation control (MCM0) */
#define _00_CGC_MAINCLK_SELFOCO                    (0x00U) /* selects the high-speed on-chip oscillator clock (fIH) as the main system clock (fMAIN) */
#define _10_CGC_MAINCLK_SELHISYS                   (0x10U) /* selects the high-speed system clock (fMX) as the main system clock (fMAIN) */
/* Status of Main system clock (fMAIN) (MCS) */
#define _00_CGC_MAINCLK_FOCO                       (0x00U) /* high-speed on-chip oscillator clock (fIH) */
#define _20_CGC_MAINCLK_HISYS                      (0x20U) /* high-speed system clock (fMX) */
/* Selection of CPU/peripheral hardware clock (fCLK) (CSS) */
#define _00_CGC_MAINCLK_SELECTED                   (0x00U) /* main system clock (fMAIN) */
#define _40_CGC_MAINCLK_FSUB                       (0x40U) /* subsystem clock (fSUB) */
/* Status of CPU/peripheral hardware clock (fCLK) (CLS) */
#define _00_CGC_MAINCLK_STATUS                     (0x00U) /* main system clock (fMAIN) */
#define _80_CGC_MAINCLK_STATUS                     (0x80U) /* subsystem clock (fSUB) */

/*
    Clock operation status control register (CSC) 
*/
/* High-speed on-chip oscillator clock operation control (HIOSTOP) */
#define _00_CGC_HIO_OPER                           (0x00U) /* high-speed on-chip oscillator operating */
#define _01_CGC_HIO_STOP                           (0x01U) /* high-speed on-chip oscillator stopped */
/* Subsystem clock operation control (XTSTOP) */
#define _00_CGC_FSUB_OPER                          (0x00U) /* XT1 oscillator/external clock operating */
#define _40_CGC_FSUB_STOP                          (0x40U) /* XT1 oscillator/external clock stopped */
/* High-speed system clock operation control (MSTOP) */
#define _00_CGC_HISYS_OPER                         (0x00U) /* X1 oscillator/external clock operating */
#define _80_CGC_HISYS_STOP                         (0x80U) /* X1 oscillator/external clock stopped */

/*
    Oscillation stabilization time counter status register (OSTC) 
*/
/* oscillation stabilization time status (MOST8,MOST9,MOST10,MOST11,MOST13,MOST15,MOST17,MOST18) */
#define _00_CGC_OSCSTAB_STA0                       (0x00U) /* 2^8/fX max. */
#define _80_CGC_OSCSTAB_STA8                       (0x80U) /* 2^8/fX */
#define _C0_CGC_OSCSTAB_STA9                       (0xC0U) /* 2^9/fX */
#define _E0_CGC_OSCSTAB_STA10                      (0xE0U) /* 2^10/fX */
#define _F0_CGC_OSCSTAB_STA11                      (0xF0U) /* 2^11/fX */
#define _F8_CGC_OSCSTAB_STA13                      (0xF8U) /* 2^13/fX */
#define _FC_CGC_OSCSTAB_STA15                      (0xFCU) /* 2^15/fX */
#define _FE_CGC_OSCSTAB_STA17                      (0xFEU) /* 2^17/fX */
#define _FF_CGC_OSCSTAB_STA18                      (0xFFU) /* 2^18/fX */

/*
    Oscillation stabilization time select register (OSTS) 
*/
/* oscillation stabilization time selection (OSTS2,OSTS1,OSTS0) */
#define _00_CGC_OSCSTAB_SEL8                       (0x00U) /* 2^8/fX */
#define _01_CGC_OSCSTAB_SEL9                       (0x01U) /* 2^9/fX */
#define _02_CGC_OSCSTAB_SEL10                      (0x02U) /* 2^10/fX */
#define _03_CGC_OSCSTAB_SEL11                      (0x03U) /* 2^11/fX */
#define _04_CGC_OSCSTAB_SEL13                      (0x04U) /* 2^13/fX */
#define _05_CGC_OSCSTAB_SEL15                      (0x05U) /* 2^15/fX */
#define _06_CGC_OSCSTAB_SEL17                      (0x06U) /* 2^17/fX */
#define _07_CGC_OSCSTAB_SEL18                      (0x07U) /* 2^18/fX */

/*
    Subsystem clock supply mode control register (OSMC) 
*/
/* Setting in STOP mode or HALT mode while subsystem clock is selected as CPU clock (RTCLPC) */
#define _00_CGC_CLK_ENABLE                         (0x00U) /* enables supply of subsystem clock to peripheral functions */
#define _80_CGC_CLK_STOP                           (0x80U) /* stops supply of subsystem clock to peripheral functions  */
/* Selection of operation clock for real-time clock, 12-bit interval timer, and timer RJ (WUTMMCK0) */
#define _00_CGC_TMRJ_IT_CLK_SUBSYSTEM_CLK          (0x00U) /* subsystem clock */
#define _10_CGC_TMRJ_IT_CLK_FIL                    (0x10U) /* low-speed on-chip oscillator clock  */

/*
    PLL Control Register (PLLCR)
*/
/* PLL Operation Control (PLLON[0:0]) */
#define _00_CGC_PLL_OPER            (0x00U) /* PLL operation */
#define _01_CGC_PLL_STOP            (0x01U) /* PLL Stop */
/* Frequency Multiplication Factor Select (PLLMUL[1:1]) */
#define _00_CGC_PLL_MUL_12_0        (0x00U) /* x12 */
#define _02_CGC_PLL_MUL_16_0        (0x02U) /* x16 */
/* PLL Input Frequency Division Ratio Select (PLIDIV[3:2]) */
#define _00_CGC_PLL_DIV_1           (0x00U) /* x1 */
#define _04_CGC_PLL_DIV_2           (0x04U) /* x1/2 */
#define _08_CGC_PLL_DIV_4           (0x08U) /* x1/4 */
/* PLL Source Select (PLLSRSEL) */
#define _00_CGC_PLLSR_fIH           (0x00U) /* fIH is selected for PLL source */
#define _80_CGC_PLLSR_fMX           (0x80U) /* fMX is selected for PLL source */
/*
    USB-dedicated PLL Control Register (UPLLCR)
*/
/* USB-dedicated PLL Operation Control (UPLLON[0:0]) */
#define _00_CGC_UPLL_OPER            (0x00U) /* UPLL operation */
#define _01_CGC_UPLL_STOP            (0x01U) /* UPLL Stop */
/* Frequency Multiplication Factor Select (UPLLMUL[1:1]) */
#define _00_CGC_UPLL_MUL_12_0        (0x00U) /* x12 */
#define _02_CGC_UPLL_MUL_16_0        (0x02U) /* x16 */
/* PLL Input Frequency Division Ratio Select (UPLIDIV[3:2]) */
#define _00_CGC_UPLL_DIV_1           (0x00U) /* x1 */
#define _04_CGC_UPLL_DIV_2           (0x04U) /* x1/2 */
#define _08_CGC_UPLL_DIV_4           (0x08U) /* x1/4 */
/* USB-Dedicated PLL Source Select (UPLLSRSEL) */
#define _00_CGC_UPLLSR_fIH           (0x00U) /* fIH is selected for UCLK PLL source */
#define _80_CGC_UPLLSR_fMX           (0x80U) /* fMX is selected for UCLK PLL source */


/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define CGC_SUBWAITTIME               (360U)   /* change the waiting time according to the system */

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef enum
{
    OSC_PORT,
    OSC_OSCILLATOR,
    OSC_EXCLK 
} osc_pin_mode_t;

typedef enum
{
    MAINCLK_FIH,
    MAINCLK_FMX,
    MAINCLK_FSUB, 
    MAINCLK_FIL,
    MAINCLK_FPLL    
} clock_select_t;

typedef enum
{
    OSC_LOW_POWER,
    OSC_NORMAL_POWER,
    OSC_ULTRA_LOW_POWER 
} osc_power_mode_t;

typedef enum
{
    OSC_UNDER_10M,
    OSC_OVER_10M,
} osc_speed_mode_t;

typedef enum
{
    PLL_DIV_1,
    PLL_DIV_2,
    PLL_DIV_4
} pll_div_t;

typedef enum
{
    PLL_MUL_12,
    PLL_MUL_16,
} pll_mul_t;

typedef enum
{
    PLL_SR_fIH,
    PLL_SR_fMX,
} pll_src_t;


/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
void CLK_Osc_Setting(osc_pin_mode_t main, osc_pin_mode_t sub);
void CLK_MainOsc_Setting(osc_pin_mode_t main, osc_speed_mode_t amph);
void CLK_SubOsc_Setting(osc_pin_mode_t sub, osc_power_mode_t amphs);
void CLK_PLL_Setting(pll_src_t src, pll_div_t div, pll_mul_t mul);
void CLK_UPLL_Setting(pll_src_t src, pll_div_t div, pll_mul_t mul);
uint8_t CLK_Fclk_Select(clock_select_t cks);
void CLK_MainOsc_Stop(void);
void CLK_MainOsc_Start(void);
void CLK_SubOsc_Stop(void);
void CLK_SubOsc_Start(void);
void CLK_Hoco_Stop(void);
void CLK_Hoco_Start(void);
void CLK_PLL_Stop(void);
void CLK_PLL_Start(void);
void CLK_UPLL_Stop(void);
void CLK_UPLL_Start(void);

#endif
