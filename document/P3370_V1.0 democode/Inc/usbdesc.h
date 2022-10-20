/*----------------------------------------------------------------------------
 *      U S B  -  K e r n e l
 *----------------------------------------------------------------------------
 * Name:    usbdesc.h
 * Purpose: USB Descriptors Definitions
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

#ifndef __USBDESC_H__
#define __USBDESC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "Type.h"

#ifdef  __UART_C__
#define INTERFACE
#else
#define INTERFACE extern
#endif

#define WBVAL(x) ((x) & 0xFF),(((x) >> 8) & 0xFF)

#define USB_DEVICE_DESC_SIZE (sizeof(USB_DEVICE_DESCRIPTOR))
#define USB_CONFIGUARTION_DESC_SIZE (sizeof(USB_CONFIGURATION_DESCRIPTOR))
#define USB_INTERFACE_DESC_SIZE (sizeof(USB_INTERFACE_DESCRIPTOR))
#define USB_ENDPOINT_DESC_SIZE (sizeof(USB_ENDPOINT_DESCRIPTOR))
#define USB_BOS_DESC_SIZE (sizeof(USB_BOS_DESCRIPTOR))
#define USB_SS_DEVICE_CAPABILITY_SIZE (sizeof(USB_SS_DEVICE_CAPABILITY_DESCRIPTOR))
#define USB_DEVICE_CAPABILITY_SIZE (sizeof(USB_DEVICE_CAPABILITY_DESCRIPTOR))

#define HID_DESC_OFFSET 0x0012
#define HID_DESC_SIZE (sizeof(HID_DESCRIPTOR))
#define HID_REPORT_DESC_MOUSE_SIZE (sizeof(HID_ReportDescriptorMouse))


INTERFACE const U8 USB_DeviceDescriptor[];
INTERFACE const U8 USB_ConfigDescriptor[];
INTERFACE const U8 USB_StringDescriptor[];
INTERFACE const U8 USB_BOSDescriptor[];

INTERFACE const U8 HID_ReportDescriptorMouse[];
INTERFACE const U16 HID_ReportDescMouseSize;


#undef INTERFACE
#ifdef __cplusplus
}
#endif
#endif  /* __USBDESC_H__ */
