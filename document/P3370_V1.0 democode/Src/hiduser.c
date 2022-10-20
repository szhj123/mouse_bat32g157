/*----------------------------------------------------------------------------
 *      U S B  -  K e r n e l
 *----------------------------------------------------------------------------
 *      Name:    HIDUSER.C
 *      Purpose: HID Custom User Module
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
#define __HIDUSER_C__
 
#include "type.h"

#include "usb.h"
#include "hid.h"
#include "usbcfg.h"
#include "usbcore.h"
#include "hiduser.h"
#include "main.h"


uint8_t HID_Protocol;
uint8_t HID_IdleTime[HID_REPORT_NUM];


/*
 *  HID Get Report Request Callback
 *   Called automatically on HID Get Report Request
 *    Parameters:      None (global SetupPacket and EP0Buf)
 *    Return Value:    TRUE - Success, FALSE - Error
 */

uint32_t HID_GetReport(void)
{
	/* ReportID = SetupPacket.wValue.WB.L; */
	switch(g_USBCore_Setting.SetupPacket.wValue.WB.H)
	{
		case HID_REPORT_INPUT:
		nsAPI_Main_GetInReport();
		g_USBCore_Setting.EP0Buf[0] = g_Main_Setting.InReport[0];
		break;

		case HID_REPORT_OUTPUT:/* Not Supported */           
		case HID_REPORT_FEATURE:/* Not Supported */
		/* g_USBCore_Setting.EP0Buf[] = ...; */
		/* break; */
		return (FALSE);          
	}
	return (TRUE);
}


/*
 *  HID Set Report Request Callback
 *   Called automatically on HID Set Report Request
 *    Parameters:      None (global SetupPacket and EP0Buf)
 *    Return Value:    TRUE - Success, FALSE - Error
 */

uint32_t HID_SetReport (void)
{
	/* ReportID = SetupPacket.wValue.WB.L; */
	switch(g_USBCore_Setting.SetupPacket.wValue.WB.H) 
	{		
		case HID_REPORT_OUTPUT:
		g_Main_Setting.OutReport[0] = g_USBCore_Setting.EP0Buf[0];
		SetOutReport();
		break;

		case HID_REPORT_INPUT:/* Not Supported */
		case HID_REPORT_FEATURE:/* Not Supported */
		return (FALSE);
	}
	return (TRUE);
}


/*
 *  HID Get Idle Request Callback
 *   Called automatically on HID Get Idle Request
 *    Parameters:      None (global SetupPacket and EP0Buf)
 *    Return Value:    TRUE - Success, FALSE - Error
 */

uint32_t HID_GetIdle (void) {

  g_USBCore_Setting.EP0Buf[0] = HID_IdleTime[g_USBCore_Setting.SetupPacket.wValue.WB.L];
  return (TRUE);
}


/*
 *  HID Set Idle Request Callback
 *   Called automatically on HID Set Idle Request
 *    Parameters:      None (global SetupPacket)
 *    Return Value:    TRUE - Success, FALSE - Error
 */

uint32_t HID_SetIdle (void) {

  HID_IdleTime[g_USBCore_Setting.SetupPacket.wValue.WB.L] = g_USBCore_Setting.SetupPacket.wValue.WB.H;

  /* Idle Handling if needed */
  /* ... */

  return (TRUE);
}


/*
 *  HID Get Protocol Request Callback
 *   Called automatically on HID Get Protocol Request
 *    Parameters:      None (global SetupPacket)
 *    Return Value:    TRUE - Success, FALSE - Error
 */

uint32_t HID_GetProtocol (void) {

  g_USBCore_Setting.EP0Buf[0] = HID_Protocol;
  return (TRUE);
}


/*
 *  HID Set Protocol Request Callback
 *   Called automatically on HID Set Protocol Request
 *    Parameters:      None (global SetupPacket)
 *    Return Value:    TRUE - Success, FALSE - Error
 */

uint32_t HID_SetProtocol (void) {

  HID_Protocol = g_USBCore_Setting.SetupPacket.wValue.WB.L;

  /* Protocol Handling if needed */
  /* ... */

  return (TRUE);
}
