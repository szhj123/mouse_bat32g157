/*----------------------------------------------------------------------------
 *      Name:    MAIN.C
 *      Purpose: USB HID Main
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
#define  _MAIN_C_

#include "Pixart_Sensor.h"
			    
#if POWERDOWN_MODE_USB_WAKEUP
extern volatile uint32_t SuspendFlag;
extern volatile uint32_t timer16_0_counter;
extern volatile uint32_t USBWakeupInterruptFlag;
volatile uint32_t WakeupFlag = 0;
#endif
extern U8 stop_motion;


U8 mouse_event_ctrl;


/*
 *  Get HID Input Report -> InReport
 */
void nsAPI_Main_GetInReport(void)
{
  g_Main_Setting.InReport[0] = 0x00;

}

void nsAPI_Main_GetInMouseButtonReport(U16 *PreButtonEvent,U16 *u16ButtonStatus,U16 *KeycodeTblIdx)
{
	switch(*u16ButtonStatus)
	{
		case GPIO_SCANKEY_PR:
		g_Main_Setting.InReport[GIdx0] = u8MouseKeyTable[*KeycodeTblIdx];
		g_Main_Setting.MouseEvent|= MAIN_FLAG_MOUSE_REPORT_READY;
		break;

		case GPIO_SCANKEY_RELEASE:
		default:
		*KeycodeTblIdx = 0;
		g_Main_Setting.InReport[GIdx0] = u8MouseKeyTable[*KeycodeTblIdx];
		g_Main_Setting.MouseEvent |= MAIN_FLAG_MOUSE_REPORT_READY;
		break;
	}
}


void nsAPI_Main_GetInMouseQIEReport(S8 s8Temp)
{
	g_Main_Setting.InReport[GIdx5] = s8Temp;
	g_Main_Setting.MouseEvent |= (MAIN_FLAG_MOUSE_QIE_EVENT|MAIN_FLAG_MOUSE_REPORT_READY);
}


/*
 *  Set HID Output Report <- OutReport
 */
void SetOutReport (void)
{

}


/* Main Program */
void Mapp_Main_Init(void)
{
	g_Main_Setting.MouseEvent = 0;
	nsAPI_USB_EndPointClr();
}

int main (void)
{

	cpi_clicked_flag = 0; 
	cpi_p_Cntr = 0;		 
	cpi_m_Cntr = 0;		 

	// default configured as Burst motion read mode ENABLE_NON_BURST_MODE_BIT is to use normal motion register read
	mouse_event_ctrl = (ENABLE_MOTION_BIT|ENABLE_BUTTON_SCROLL_BIT );
	nsAPI_System_Init();
	nsAPI_SSP_Sensor_Init();
	Mapp_Main_Init();

    while(1)
    {
					
		if( IS_BIT_SET(mouse_event_ctrl,ENABLE_BUTTON_SCROLL_BIT) ) 
		{
			if(poll_tick_btn >= POLL_RATE_BTN)
			{
				poll_tick_btn = 0;
				nsAPI_GPIO_MouseButtonMonitor();
			}

			if(poll_z_wheel >= POLL_Z_WHEEL) 
			{
				poll_z_wheel = 0;
				Z_Wheel();
			}
		}	
		nsAPI_SSP_Sensor_Monitor();		
    }
}

/***************************************************************
	g_Main_Setting.InReport[0] =  button
	g_Main_Setting.InReport[1] =  x	L
	g_Main_Setting.InReport[2] =  x H
	g_Main_Setting.InReport[3] =  y L
	g_Main_Setting.InReport[4] =  y H
	g_Main_Setting.InReport[5] =  scroll	   
****************************************************************/
void nsAPI_Main_MouseEventHandle(void)
{
	__disable_irq();

//	if(	((g_Main_Setting.MouseEvent & MAIN_FLAG_MOUSE_REPORT_READY) == MAIN_FLAG_MOUSE_REPORT_READY) &&
//		((g_Main_Setting.EPInOutReq & EP1_IN) == EP1_IN))
	{								   
		g_Main_Setting.InReportSize 			= (U8)EP1_MAX_SIZE;
		g_Main_Setting.MouseEvent  	   		   &= ~MAIN_FLAG_MOUSE_REPORT_READY;
		g_Main_Setting.InReport[X_LOW]			= report1ms_data_x.b[0];
		g_Main_Setting.InReport[X_HIGH] 		= report1ms_data_x.b[1];
		g_Main_Setting.InReport[Y_LOW]			= report1ms_data_y.b[0];
		g_Main_Setting.InReport[Y_HIGH]			= report1ms_data_y.b[1];
		g_Main_Setting.InReport[WHEEL]			= count_z;
#ifdef	ENABLE_BURST_DAT_REPORT
		g_Main_Setting.InReport[MOTION]			= u8motion;
		g_Main_Setting.InReport[SQUAL]			= u8Squal;
		g_Main_Setting.InReport[PIXEL_SUM]		= u8PixelSum;
		g_Main_Setting.InReport[MAX_PIXEL]		= u16Pixel.b[1]; 
		g_Main_Setting.InReport[MIN_PIXEL]		= u16Pixel.b[0]; 
		g_Main_Setting.InReport[SHUTTER_UPPER]	= u16Shutter.b[1];
		g_Main_Setting.InReport[SHUTTER_LOWER]	= u16Shutter.b[0];
#endif
		nsAPI_USB_WriteEP(HID_EP1_IN,&g_Main_Setting.InReport[0],g_Main_Setting.InReportSize);
		nsAPI_Main_Clr_MouseEvent();

		count_z = 0;
		u8motion = 0;
		u8Squal = 0;
		u8PixelSum = 0;
		u16Pixel.w = 0;	
		u16Shutter.w = 0;
		g_Main_Setting.MouseEvent &= ~MAIN_FLAG_MOUSE_EVENT;
		g_Main_Setting.EPInOutReq &= ~EP1_IN;
	}
	__enable_irq();
}


void nsAPI_Main_Clr_MouseEvent(void)
{
	
	if((g_Main_Setting.MouseEvent & MAIN_FLAG_MOUSE_QIE_EVENT) == MAIN_FLAG_MOUSE_QIE_EVENT)
	{
		g_Main_Setting.MouseEvent &= ~MAIN_FLAG_MOUSE_QIE_EVENT;
	}

	if((g_Main_Setting.MouseEvent & MAIN_FLAG_MOUSE_EVENT) == MAIN_FLAG_MOUSE_EVENT)
	{
		g_Main_Setting.MouseEvent &= ~MAIN_FLAG_MOUSE_EVENT;
	}

	g_Main_Setting.InReport[X_LOW]			= 0; 
	g_Main_Setting.InReport[X_HIGH] 		= 0; 
	g_Main_Setting.InReport[Y_LOW]			= 0;
	g_Main_Setting.InReport[Y_HIGH]			= 0;
	g_Main_Setting.InReport[WHEEL]			= 0;
#ifdef	ENABLE_BURST_DAT_REPORT
	g_Main_Setting.InReport[MOTION]			= 0;
	g_Main_Setting.InReport[SQUAL]			= 0;
	g_Main_Setting.InReport[PIXEL_SUM]		= 0;
	g_Main_Setting.InReport[MAX_PIXEL]		= 0; 
	g_Main_Setting.InReport[MIN_PIXEL]		= 0; 
	g_Main_Setting.InReport[SHUTTER_UPPER]	= 0; 
	g_Main_Setting.InReport[SHUTTER_LOWER]	= 0;
#endif

}
