/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    intp.h
* @brief   This file implements device driver for INTP module.
* @version 1.0.0
* @date    2020/10/24
***********************************************************************************************************************/
#ifndef INTP_H
#define INTP_H

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define INTP_WAITTIME                    (1U)   /* change the waiting time according to the system */ 

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef enum
{
	INTP_NONE,
	INTP_FALLING,
	INTP_RISING,
	INTP_BOTH
} intp_edge_t;

/***********************************************************************************************************************
Global variables
***********************************************************************************************************************/
extern volatile uint32_t g_intp0Taken;  	/* INTP0 taken */
extern volatile uint32_t g_intp1Taken;  	/* INTP1 taken */
extern volatile uint32_t g_intp2Taken;  	/* INTP2 taken */
extern volatile uint32_t g_intp3Taken;  	/* INTP3 taken */
extern volatile uint32_t g_intp4Taken;  	/* INTP4 taken */
extern volatile uint32_t g_intp5Taken;  	/* INTP5 taken */
extern volatile uint32_t g_intp6Taken;  	/* INTP6 taken */
extern volatile uint32_t g_intp7Taken;  	/* INTP7 taken */

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
void INTP_Init(uint16_t pinMsk, intp_edge_t edge);
void INTP_Start(uint16_t pinMsk);
void INTP_Stop(uint16_t pinMsk);
static void intp0_callback(void);
static void intp1_callback(void);
static void intp2_callback(void);
static void intp3_callback(void);
static void intp4_callback(void);
static void intp5_callback(void);
static void intp6_callback(void);
static void intp7_callback(void);
/* Start user code for function. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#endif
