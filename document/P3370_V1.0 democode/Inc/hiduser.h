/*----------------------------------------------------------------------------
 *      U S B  -  K e r n e l
 *----------------------------------------------------------------------------
 *      Name:    HIDUSER.H
 *      Purpose: HID Custom User Definitions
 *      Version: V1.20
 *----------------------------------------------------------------------------
 *      This software is supplied "AS IS" without any warranties, express,
 *      implied or statutory, including but not limited to the implied
 *      warranties of fitness for purpose, satisfactory quality and
 *      noninfringement. Keil extends you a royalty-free right to reproduce
 *      and distribute executable files created using this software for use
 *      on NXP Semiconductors LPC microcontroller devices only. Nothing else 
 *      gives you the right to use this software.
 *
 * Copyright (c) 2009 Keil - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#ifndef __HIDUSER_H__
#define __HIDUSER_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "Type.h"

#ifdef  __HIDUSER_C__
#define INTERFACE
#else
#define INTERFACE extern
#endif


/* HID Number of Reports */
#define HID_REPORT_NUM 1

/* HID In/Out Endpoint Address */
#define HID_EP1_IN 0x81
#define HID_EP1_OUT 0x01
#define HID_EP2_IN 0x82
#define HID_EP2_OUT 0x02
#define HID_EP3_IN 0x83
#define HID_EP3_OUT 0x03
#define HID_EP4_IN 0x84
#define HID_EP4_OUT 0x04


/* HID Global Variables */
extern uint8_t HID_Protocol;
extern uint8_t HID_IdleTime[HID_REPORT_NUM];

/* HID Requests Callback Functions */
INTERFACE uint32_t HID_GetReport   (void);
INTERFACE uint32_t HID_SetReport   (void);
INTERFACE uint32_t HID_GetIdle     (void);
INTERFACE uint32_t HID_SetIdle     (void);
INTERFACE uint32_t HID_GetProtocol (void);
INTERFACE uint32_t HID_SetProtocol (void);

#undef INTERFACE
#ifdef __cplusplus
}
#endif
#endif  /* __HIDUSER_H__ */
