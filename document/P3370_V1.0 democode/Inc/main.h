/*----------------------------------------------------------------------------
 *      Name:    MAIN.H
 *      Purpose: USB HID Demo Definitions
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
#ifndef __MAIN_H__
#define __MAIN_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "Type.h"
#include "usbcfg.h"
//#include "Pixart_Sensor.h"

#ifdef _MAIN_C_
#define INTERFACE
#else
#define INTERFACE extern
#endif

#define _DEMO_ONLY_ 0

#define EP1_IN BIT0
#define EP1_OUT BIT1
#define EP2_IN BIT2
#define EP2_OUT BIT3
#define EP3_IN BIT4
#define EP3_OUT BIT5
#define EP4_IN BIT6
#define EP4_OUT BIT7

#define MISC_EVENT (BIT3|BIT2)


typedef enum _GIndex_
{
    GIdx0 = 0,
    GIdx1,
    GIdx2,
    GIdx3,
    GIdx4,
    GIdx5,
    GIdx6,
    GIdx7,
    GIdx8,
    GIdxLen =  GIdx8,
}GIndex;

#define MAIN_FLAG_MOUSE_REPORT_READY	BIT0	
#define MAIN_FLAG_MOUSE_BUTTON_EVENT	BIT1	
#define MAIN_FLAG_MOUSE_QIE_EVENT		BIT2
//#define MAIN_FLAG_MOUSE_EVENT	BIT3
#define MAIN_FLAG_MOUSE_EVENT			BIT3
//#define MAIN_FLAG_MOUSE_FRAME_CAPTURE_EVENT BIT4

/* HID Demo Variables */
typedef struct _LPC11Uxx_MAIN_SETTING_
{
	U8 InReport[USB_PACKET_SIZE];
	U8 OutReport[USB_PACKET_SIZE];
	U8 EPInOutReq;
	U8 InReportSize;
	U16 MouseEvent;
}LPC11Uxx_MAIN_SETTING;

INTERFACE LPC11Uxx_MAIN_SETTING g_Main_Setting;


/* HID Demo Functions */
INTERFACE void nsAPI_Main_GetInReport(void);
INTERFACE void SetOutReport(void);
INTERFACE void nsAPI_Main_MouseEventHandle(void);
INTERFACE void nsAPI_Main_GetInMouseButtonReport(U16 *PreButtonEvent,U16 *u16ButtonStatus,U16 *KeycodeTblIdx);
INTERFACE void nsAPI_Main_GetInMouseQIEReport(S8 s8Temp);
INTERFACE void nsAPI_Main_Clr_MouseEvent(void);
INTERFACE void Mapp_Main_Init(void);

#undef INTERFACE
#ifdef __cplusplus
}
#endif
#endif //__MAIN_H__
