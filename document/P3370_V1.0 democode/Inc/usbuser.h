/*----------------------------------------------------------------------------
 *      U S B  -  K e r n e l
 *----------------------------------------------------------------------------
 * Name:    usbuser.h
 * Purpose: USB Custom User Definitions
 * Version: V1.20
 *----------------------------------------------------------------------------
 *      This software is supplied "AS IS" without any warranties, express,
 *      implied or statutory, including but not limited to the implied
 *      warranties of fitness for purpose, satisfactory quality and
 *      noninfringement. Keil extends you a royalty-free right to reproduce
 *      and distribute executable files created using this software for use
 *      on NXP Semiconductors LPC family microcontroller devices only. Nothing 
 *      else gives you the right to use this software.
 *
 * Copyright (c) 2009 Keil - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#ifndef __USBUSER_H__
#define __USBUSER_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "Type.h"

#ifdef  _USBUSER_C_
#define INTERFACE
#else
#define INTERFACE extern
#endif

/* USB Device Events Callback Functions */
INTERFACE void USB_Power_Event(U32 power);
INTERFACE void USB_Reset_Event(void);
INTERFACE void USB_Suspend_Event(void);
INTERFACE void USB_Resume_Event(void);
INTERFACE void USB_WakeUp_Event(void);
INTERFACE void USB_SOF_Event(void);
INTERFACE void USB_Error_Event(U32 error);

/* USB Endpoint Callback Events */
#define USB_EVT_SETUP 1/* Setup Packet */
#define USB_EVT_OUT 2/* OUT Packet */
#define USB_EVT_IN 3/* IN Packet */
#define USB_EVT_OUT_NAK 4   /* OUT Packet - Not Acknowledged */
#define USB_EVT_IN_NAK 5   /* IN Packet - Not Acknowledged */
#define USB_EVT_OUT_STALL 6/* OUT Packet - Stalled */
#define USB_EVT_IN_STALL 7/*  IN Packet - Stalled */

/* USB Endpoint Events Callback Pointers */
INTERFACE void (* const USB_P_EP[USB_LOGIC_EP_NUM])(U32 event);

/* USB Endpoint Events Callback Functions */
INTERFACE void nsAPI_USB_EndPoint0(U32 event);
INTERFACE void nsAPI_USB_EndPoint1(U32 event);
INTERFACE void nsAPI_USB_EndPoint2(U32 event);
INTERFACE void nsAPI_USB_EndPoint3(U32 event);
INTERFACE void nsAPI_USB_EndPoint4(U32 event);
INTERFACE void nsAPI_USB_EndPointClr(void);
/* USB Core Events Callback Functions */
INTERFACE void nsAPI_USB_Configure_Event(void);
INTERFACE void USB_Interface_Event(void);
INTERFACE void USB_Feature_Event(void);

#undef INTERFACE
#ifdef __cplusplus
}
#endif
#endif  /* __USBUSER_H__ */
