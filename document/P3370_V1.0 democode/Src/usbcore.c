//----------------------------------------------------------------------------
//      U S B  -  K e r n e l
//----------------------------------------------------------------------------
// Name:    usbcore.c
// Purpose: USB Core Module
// Version: V1.20
//----------------------------------------------------------------------------
//      This software is supplied "AS IS" without any warranties, express,
//      implied or statutory, including but not limited to the implied
//      warranties of fitness for purpose, satisfactory quality and
//      noninfringement. Keil extends you a royalty-free right to reproduce
//      and distribute executable files created using this software for use
//      on NXP Semiconductors LPC family microcontroller devices only. Nothing
//      else gives you the right to use this software.
//
// Copyright (c) 2009 Keil - An ARM Company. All rights reserved.
//----------------------------------------------------------------------------
// History:
//          V1.20 Added vendor specific requests
//                Changed string descriptor handling
//                Reworked Endpoint0
//          V1.00 Initial Version
//----------------------------------------------------------------------------
#define  __USBCORE_C__

//----------------------------------------------------------------------------
// Include
//----------------------------------------------------------------------------

#if (USB_CLASS)
#if (USB_HID)
#include "hid.h"
#include "hiduser.h"
#endif
#endif
#if (USB_VENDOR)
#include "vendor.h"
#endif

#include "Pixart_Sensor.h"
#pragma diag_suppress 111,177,1441 

//------------------------------------------------------------------------------------
// Variable
//------------------------------------------------------------------------------------
U8 usb_reg_addr;
U8 usb_reg_data;
U8 usbSROM[SROM_BUFFER_SIZE] __attribute__((aligned(4)));

//----------------------------------------------------------------------------
//  Reset USB Core
//----------------------------------------------------------------------------
void nsAPI_USB_ResetCore (void)
{
	usb_reg_addr = 0;
	usb_reg_data = 0;
	
	g_USBCore_Setting.USB_DeviceStatus = USB_POWER;
	g_USBCore_Setting.USB_DeviceAddress = 0;
	g_USBCore_Setting.USB_Configuration = 0;
	g_USBCore_Setting.USB_EndPointMask = 0x00010001;
	g_USBCore_Setting.USB_EndPointHalt = 0x00000000;
	g_USBCore_Setting.USB_EndPointStall = 0x00000000;
}


//----------------------------------------------------------------------------
//  USB Request - Setup Stage
//----------------------------------------------------------------------------
void nsAPI_USB_SetupStage(void)
{
	nsAPI_USB_ReadSetupEP(0x00, (U8 *)&g_USBCore_Setting.SetupPacket);
}


//----------------------------------------------------------------------------
//  USB Request - Data In Stage
//----------------------------------------------------------------------------
void nsAPI_USB_DataInStage(void)
{
	U32 cnt;

	if(g_USBCore_Setting.EP0Data.Count > USB_MAX_PACKET0)
		cnt = USB_MAX_PACKET0;
	else
		cnt = g_USBCore_Setting.EP0Data.Count;

	cnt = nsAPI_USB_WriteEP(0x80, g_USBCore_Setting.EP0Data.pData, cnt);
	g_USBCore_Setting.EP0Data.pData += cnt;
	g_USBCore_Setting.EP0Data.Count -= cnt;
}


//----------------------------------------------------------------------------
//  USB Request - Data Out Stage
//----------------------------------------------------------------------------
void nsAPI_USB_DataOutStage(void)
{
	U32 cnt;

	cnt = nsAPI_USB_ReadEP(0x00, g_USBCore_Setting.EP0Data.pData);
	g_USBCore_Setting.EP0Data.Count -= cnt;
}


//----------------------------------------------------------------------------
//  USB Request - Status In Stage
//----------------------------------------------------------------------------
void nsAPI_USB_StatusInStage(void)
{
	nsAPI_USB_WriteEP(0x80, NULL, 0);
}


//----------------------------------------------------------------------------
//  USB Request - Status Out Stage
//----------------------------------------------------------------------------
void nsAPI_USB_StatusOutStage(void)
{
	nsAPI_USB_ReadEP(0x00, g_USBCore_Setting.EP0Buf);
}


//----------------------------------------------------------------------------
//  Get Status USB Request
//----------------------------------------------------------------------------
__inline Boolean nsAPI_USB_ReqGetStatus(void)
{
	U32 n, m;

	switch(g_USBCore_Setting.SetupPacket.bmRequestType.BM.Recipient)
	{
		case REQUEST_TO_DEVICE:
			g_USBCore_Setting.EP0Data.pData = (U8 *)&g_USBCore_Setting.USB_DeviceStatus;
			break;

		case REQUEST_TO_INTERFACE:
			if((g_USBCore_Setting.USB_Configuration != 0) && (g_USBCore_Setting.SetupPacket.wIndex.WB.L < g_USBCore_Setting.USB_NumInterfaces))
			{
				*((__packed U16 *)g_USBCore_Setting.EP0Buf) = 0;
				g_USBCore_Setting.EP0Data.pData = g_USBCore_Setting.EP0Buf;
			}
			else
				return (FALSE);
			break;

		case REQUEST_TO_ENDPOINT:
			n = g_USBCore_Setting.SetupPacket.wIndex.WB.L & 0x8F;
			m = (n & 0x80) ? ((1 << 16) << (n & 0x0F)) : (1 << n);
	
			if(((g_USBCore_Setting.USB_Configuration != 0) || ((n & 0x0F) == 0)) && (g_USBCore_Setting.USB_EndPointMask & m))
			{
				*((__packed U16 *)g_USBCore_Setting.EP0Buf) = (g_USBCore_Setting.USB_EndPointHalt & m) ? 1 : 0;
				g_USBCore_Setting.EP0Data.pData = g_USBCore_Setting.EP0Buf;
			}
			else
			{
				return (FALSE);
			}
			break;

		default:
			return (FALSE);
	}

	return (TRUE);
}


//----------------------------------------------------------------------------
//  Set/Clear Feature USB Request
//----------------------------------------------------------------------------
__inline Boolean nsAPI_USB_ReqSetClrFeature(U32 sc)
{
	U32 n, m;

	switch(g_USBCore_Setting.SetupPacket.bmRequestType.BM.Recipient)
	{
		case REQUEST_TO_DEVICE:
			if(g_USBCore_Setting.SetupPacket.wValue.W == USB_FEATURE_REMOTE_WAKEUP)
			{
				if(sc)
				{
					NDrv_USB_WakeUpCfg(TRUE);
					g_USBCore_Setting.USB_DeviceStatus |=  USB_GETSTATUS_REMOTE_WAKEUP;
				}
				else
				{
					NDrv_USB_WakeUpCfg(FALSE);
					g_USBCore_Setting.USB_DeviceStatus &= ~USB_GETSTATUS_REMOTE_WAKEUP;
				}
			}
			else
			{
				return (FALSE);
			}
			break;

		case REQUEST_TO_INTERFACE:
			return (FALSE);

		case REQUEST_TO_ENDPOINT:
			n = g_USBCore_Setting.SetupPacket.wIndex.WB.L & 0x8F;
			m = (n & 0x80) ? ((1 << 16) << (n & 0x0F)) : (1 << n);
	
			if((g_USBCore_Setting.USB_Configuration != 0) && ((n & 0x0F) != 0) && (g_USBCore_Setting.USB_EndPointMask & m))
			{
				if(g_USBCore_Setting.SetupPacket.wValue.W == USB_FEATURE_ENDPOINT_STALL)
				{
					if(sc)
					{
						nsAPI_USB_SetStallEP(n);
						g_USBCore_Setting.USB_EndPointHalt |=  m;
					}
					else
					{
						if((g_USBCore_Setting.USB_EndPointStall & m) != 0)
							return (TRUE);
						
						nsAPI_USB_ClrStallEP(n);
						g_USBCore_Setting.USB_EndPointHalt &= ~m;
					}
				}
				else
				{
					return (FALSE);
				}
			}
			else
		  	{
				return (FALSE);
			}
			break;

		default:
			return (FALSE);
	}

	return (TRUE);
}


//----------------------------------------------------------------------------
//  Set Address USB Request
//----------------------------------------------------------------------------
__inline Boolean nsAPI_USB_ReqSetAddress(void)
{
	switch(g_USBCore_Setting.SetupPacket.bmRequestType.BM.Recipient)
	{
		case REQUEST_TO_DEVICE:
			g_USBCore_Setting.USB_DeviceAddress = (0x80 | g_USBCore_Setting.SetupPacket.wValue.WB.L);
			break;
		
		default:
			return (FALSE);
	}

	return (TRUE);
}


//----------------------------------------------------------------------------
//  Get Descriptor USB Request
//----------------------------------------------------------------------------
__inline Boolean nsAPI_USB_ReqGetDescriptor(void)
{
	U8 *pD;
	U32 len, n;

	switch(g_USBCore_Setting.SetupPacket.bmRequestType.BM.Recipient)
	{
		case REQUEST_TO_DEVICE:
			switch(g_USBCore_Setting.SetupPacket.wValue.WB.H)
			{
				case USB_DEVICE_DESCRIPTOR_TYPE:
					g_USBCore_Setting.EP0Data.pData = (U8 *)USB_DeviceDescriptor;
					len = USB_DEVICE_DESC_SIZE;
					break;

				case USB_CONFIGURATION_DESCRIPTOR_TYPE:
					pD = (U8 *)USB_ConfigDescriptor;
					for(n = 0; n != g_USBCore_Setting.SetupPacket.wValue.WB.L; n++)
						if(((USB_CONFIGURATION_DESCRIPTOR *)pD)->bLength != 0)
							pD += ((USB_CONFIGURATION_DESCRIPTOR *)pD)->wTotalLength;

					if(((USB_CONFIGURATION_DESCRIPTOR *)pD)->bLength == 0)
						return (FALSE);

					g_USBCore_Setting.EP0Data.pData = pD;
					len = ((USB_CONFIGURATION_DESCRIPTOR *)pD)->wTotalLength;
					break;

#if LPM_SUPPORT
				case USB_BOS_TYPE:
					pD = (uint8_t *)USB_BOSDescriptor;
					for(n = 0; n != g_USBCore_Setting.SetupPacket.wValue.WB.L; n++)
						if(((USB_BOS_DESCRIPTOR *)pD)->bLength != 0)
							pD += ((USB_BOS_DESCRIPTOR *)pD)->wTotalLength;

					if(((USB_BOS_DESCRIPTOR *)pD)->bLength == 0)
						return (FALSE);

					g_USBCore_Setting.EP0Data.pData = pD;
					len = ((USB_BOS_DESCRIPTOR *)pD)->wTotalLength;
					break;
#endif

				case USB_STRING_DESCRIPTOR_TYPE:
					pD = (uint8_t *)USB_StringDescriptor;
					for(n = 0; n != g_USBCore_Setting.SetupPacket.wValue.WB.L; n++)
						if(((USB_STRING_DESCRIPTOR *)pD)->bLength != 0)
							pD += ((USB_STRING_DESCRIPTOR *)pD)->bLength;

					if(((USB_STRING_DESCRIPTOR *)pD)->bLength == 0)
						return (FALSE);

					g_USBCore_Setting.EP0Data.pData = pD;
					len = ((USB_STRING_DESCRIPTOR *)g_USBCore_Setting.EP0Data.pData)->bLength;
					break;
			
				default:
					return (FALSE);
			}
			break;

		case REQUEST_TO_INTERFACE:
			switch(g_USBCore_Setting.SetupPacket.wValue.WB.H)
			{
#if USB_HID
				case HID_HID_DESCRIPTOR_TYPE:
					g_USBCore_Setting.EP0Data.pData = ((U8 *)USB_ConfigDescriptor + HID_DESC_OFFSET+(g_USBCore_Setting.SetupPacket.wIndex.WB.L * 25));
					len = HID_DESC_SIZE;
					break;

				case HID_REPORT_DESCRIPTOR_TYPE:
					switch(g_USBCore_Setting.SetupPacket.wIndex.WB.L)
					{
						case 0:
							len = HID_ReportDescMouseSize;
							g_USBCore_Setting.EP0Data.pData = (U8 *)HID_ReportDescriptorMouse;
							break;
						
						default:
							return (FALSE);
					}
					break;
	
				case HID_PHYSICAL_DESCRIPTOR_TYPE:
					return (FALSE);		// HID Physical Descriptor is not supported
#endif
				default:
					return (FALSE);
			}
			break;
		
			default:
				return (FALSE);
	}

	if(g_USBCore_Setting.EP0Data.Count > len)
		g_USBCore_Setting.EP0Data.Count = len;

	return (TRUE);
}


//----------------------------------------------------------------------------
//  Get Configuration USB Request
//----------------------------------------------------------------------------
__inline Boolean nsAPI_USB_ReqGetConfiguration(void)
{
	switch(g_USBCore_Setting.SetupPacket.bmRequestType.BM.Recipient)
	{
		case REQUEST_TO_DEVICE:
			g_USBCore_Setting.EP0Data.pData = &g_USBCore_Setting.USB_Configuration;
			break;
		
		default:
			return (FALSE);
	}

	return (TRUE);
}


//----------------------------------------------------------------------------
//  Set Configuration USB Request
//----------------------------------------------------------------------------
__inline Boolean nsAPI_USB_ReqSetConfiguration(void)
{
	USB_COMMON_DESCRIPTOR *pD;
	U32 alt = 0, n, m;

	switch(g_USBCore_Setting.SetupPacket.bmRequestType.BM.Recipient)
	{
		case REQUEST_TO_DEVICE:
			if(g_USBCore_Setting.SetupPacket.wValue.WB.L)
			{
				pD = (USB_COMMON_DESCRIPTOR *)USB_ConfigDescriptor;
				while(pD->bLength)
				{
					switch (pD->bDescriptorType)
					{
						case USB_CONFIGURATION_DESCRIPTOR_TYPE:
							if(((USB_CONFIGURATION_DESCRIPTOR *)pD)->bConfigurationValue == g_USBCore_Setting.SetupPacket.wValue.WB.L)
							{
								g_USBCore_Setting.USB_Configuration = g_USBCore_Setting.SetupPacket.wValue.WB.L;
								g_USBCore_Setting.USB_NumInterfaces = ((USB_CONFIGURATION_DESCRIPTOR *)pD)->bNumInterfaces;
		
								for(n = 0; n < USB_IF_NUM; n++)
									g_USBCore_Setting.USB_AltSetting[n] = 0;
		
								for(n = 1; n < USB_LOGIC_EP_NUM; n++)
								{
									if(g_USBCore_Setting.USB_EndPointMask & (1 << n))
										nsAPI_USB_DisableEP(n);
		
									if(g_USBCore_Setting.USB_EndPointMask & ((1 << 16) << n))
										nsAPI_USB_DisableEP(n | 0x80);
								}
		
								g_USBCore_Setting.USB_EndPointMask = 0x00010001;
								g_USBCore_Setting.USB_EndPointHalt = 0x00000000;
								g_USBCore_Setting.USB_EndPointStall = 0x00000000;
								NDrv_USB_Configure(TRUE);
		
								if(((USB_CONFIGURATION_DESCRIPTOR *)pD)->bmAttributes & USB_CONFIG_POWERED_MASK)
									g_USBCore_Setting.USB_DeviceStatus |=  USB_GETSTATUS_SELF_POWERED;
								else
									g_USBCore_Setting.USB_DeviceStatus &= ~USB_GETSTATUS_SELF_POWERED;
							}
							else
							{
								(U8 *)pD += ((USB_CONFIGURATION_DESCRIPTOR *)pD)->wTotalLength;
								continue;
							}
							break;
	
						case USB_INTERFACE_DESCRIPTOR_TYPE:
							alt = ((USB_INTERFACE_DESCRIPTOR *)pD)->bAlternateSetting;
							break;
	
						case USB_ENDPOINT_DESCRIPTOR_TYPE:
							if(alt == 0)
							{
								n = ((USB_ENDPOINT_DESCRIPTOR *)pD)->bEndpointAddress & 0x8F;
								m = (n & 0x80) ? ((1 << 16) << (n & 0x0F)) : (1 << n);
								g_USBCore_Setting.USB_EndPointMask |= m;
								nsAPI_USB_EnableEP(n);
								nsAPI_USB_ResetEP(n);
							}
							break;
					}
	
					(U8 *)pD += pD->bLength;
				}
			}
			else
			{
				g_USBCore_Setting.USB_Configuration = 0;
	
				for(n = 1; n < USB_LOGIC_EP_NUM; n++)
				{
					if(g_USBCore_Setting.USB_EndPointMask & (1 << n))
						nsAPI_USB_DisableEP(n);
	
					if(g_USBCore_Setting.USB_EndPointMask & ((1 << 16) << n))
						nsAPI_USB_DisableEP(n | 0x80);
				}
	
				g_USBCore_Setting.USB_EndPointMask = 0x00010001;
				g_USBCore_Setting.USB_EndPointHalt = 0x00000000;
				g_USBCore_Setting.USB_EndPointStall = 0x00000000;
				NDrv_USB_Configure(FALSE);
			}
	
			if(g_USBCore_Setting.USB_Configuration != g_USBCore_Setting.SetupPacket.wValue.WB.L)
				return (FALSE);
			break;
					
		default:
			return (FALSE);
	}

	return (TRUE);
}


//----------------------------------------------------------------------------
//  Get Interface USB Request
//----------------------------------------------------------------------------
__inline Boolean nsAPI_USB_ReqGetInterface(void)
{
	switch(g_USBCore_Setting.SetupPacket.bmRequestType.BM.Recipient)
	{
		case REQUEST_TO_INTERFACE:
			if((g_USBCore_Setting.USB_Configuration != 0) && (g_USBCore_Setting.SetupPacket.wIndex.WB.L < g_USBCore_Setting.USB_NumInterfaces))
				g_USBCore_Setting.EP0Data.pData = g_USBCore_Setting.USB_AltSetting + g_USBCore_Setting.SetupPacket.wIndex.WB.L;
			else
				return (FALSE);	
			break;
		
		default:
			return (FALSE);
	}

	return (TRUE);
}


//----------------------------------------------------------------------------
//  Set Interface USB Request
//----------------------------------------------------------------------------
__inline Boolean nsAPI_USB_ReqSetInterface(void)
{
	USB_COMMON_DESCRIPTOR *pD;
	U32 ifn = 0, alt = 0, old = 0, msk = 0, n, m, set;

	switch(g_USBCore_Setting.SetupPacket.bmRequestType.BM.Recipient)
	{
		case REQUEST_TO_INTERFACE:
			if(g_USBCore_Setting.USB_Configuration == 0)
				return (FALSE);

			set = FALSE;
			pD = (USB_COMMON_DESCRIPTOR *)USB_ConfigDescriptor;

			while(pD->bLength)
			{
				switch(pD->bDescriptorType)
				{
					case USB_CONFIGURATION_DESCRIPTOR_TYPE:
						if(((USB_CONFIGURATION_DESCRIPTOR *)pD)->bConfigurationValue != g_USBCore_Setting.USB_Configuration)
						{
							(uint8_t *)pD += ((USB_CONFIGURATION_DESCRIPTOR *)pD)->wTotalLength;
							continue;
						}
						break;

					case USB_INTERFACE_DESCRIPTOR_TYPE:
						ifn = ((USB_INTERFACE_DESCRIPTOR *)pD)->bInterfaceNumber;
						alt = ((USB_INTERFACE_DESCRIPTOR *)pD)->bAlternateSetting;
						msk = 0;
						
						if((ifn == g_USBCore_Setting.SetupPacket.wIndex.WB.L) && (alt == g_USBCore_Setting.SetupPacket.wValue.WB.L))
						{
							set = TRUE;
							old = g_USBCore_Setting.USB_AltSetting[ifn];
							g_USBCore_Setting.USB_AltSetting[ifn] = (U8)alt;
						}
						break;

					case USB_ENDPOINT_DESCRIPTOR_TYPE:
						if(ifn == g_USBCore_Setting.SetupPacket.wIndex.WB.L)
						{
							n = ((USB_ENDPOINT_DESCRIPTOR *)pD)->bEndpointAddress & 0x8F;
							m = (n & 0x80) ? ((1 << 16) << (n & 0x0F)) : (1 << n);
		
							if(alt == g_USBCore_Setting.SetupPacket.wValue.WB.L)
							{
								g_USBCore_Setting.USB_EndPointMask |=  m;
								g_USBCore_Setting.USB_EndPointHalt &= ~m;
								nsAPI_USB_EnableEP(n);
								nsAPI_USB_ResetEP(n);
								msk |= m;
							}
							else if((alt == old) && ((msk & m) == 0))
							{
								g_USBCore_Setting.USB_EndPointMask &= ~m;
								g_USBCore_Setting.USB_EndPointHalt &= ~m;
								nsAPI_USB_DisableEP(n);
							}
						}
						break;
				}

				(U8 *)pD += pD->bLength;
			}
			break;
		
		default:
			return (FALSE);
	}

	return (set);
}


//----------------------------------------------------------------------------
//  USB Endpoint 0 Event Callback
//----------------------------------------------------------------------------
void nsAPI_USB_EndPoint0(U32 event)
{
	Boolean bSetupClassOk = FALSE, bOutClassOk = FALSE;

	//----------------------------------------------------------
	// USB Params for tickle read write capabilities
	//----------------------------------------------------------
	
	static U8 ready_flash_flag = 0;
	static U16 sromCntr = 0;
	static U32 flash_sector_address = 0;
	static U32 flash_address_offset = 0;
/*
	static U8 frameCntr = 0;
	static U8 tempframe[FRAME_CAPTURE_SIZE] = {0}; //frame capture
	*/
	//-----------------------------------------------------------

	switch(event)
	{
		case USB_EVT_SETUP:
			nsAPI_USB_SetupStage();
			g_USBCore_Setting.EP0Data.Count = g_USBCore_Setting.SetupPacket.wLength;	// number of bytes to transfer

			switch(g_USBCore_Setting.SetupPacket.bmRequestType.BM.Type)
			{		
				case REQUEST_STANDARD:
					switch(g_USBCore_Setting.SetupPacket.bRequest)
					{
						case USB_REQUEST_GET_STATUS:
#if 0
							if(!nsAPI_USB_ReqGetStatus())
								goto stall_i;
							
							nsAPI_USB_DataInStage();
#else
							if(nsAPI_USB_ReqGetStatus())
								nsAPI_USB_DataInStage();
							else
								nsAPI_USBCore_Stall_i();
#endif
							break;

						case USB_REQUEST_CLEAR_FEATURE:
#if 0
							if(!nsAPI_USB_ReqSetClrFeature(0))
								goto stall_i;

							nsAPI_USB_StatusInStage();
#if USB_FEATURE_EVENT
							USB_Feature_Event();
#endif
#else
							if(nsAPI_USB_ReqSetClrFeature(0))
							{
								nsAPI_USB_StatusInStage();
#if USB_FEATURE_EVENT
								USB_Feature_Event();
#endif
							}
							else
							{
								nsAPI_USBCore_Stall_i();
							}
#endif
							break;

						case USB_REQUEST_SET_FEATURE:
#if 0
							if(!nsAPI_USB_ReqSetClrFeature(1))
								goto stall_i;
							
							nsAPI_USB_StatusInStage();
#if USB_FEATURE_EVENT
							USB_Feature_Event();
#endif
#else
							if(nsAPI_USB_ReqSetClrFeature(1))
							{
								nsAPI_USB_StatusInStage();
#if USB_FEATURE_EVENT
								USB_Feature_Event();
#endif
							}
							else
							{
								nsAPI_USBCore_Stall_i();
							}
#endif
							break;

						case USB_REQUEST_SET_ADDRESS:
#if 0
							if(!nsAPI_USB_ReqSetAddress())
								goto stall_i;
							
							nsAPI_USB_StatusInStage();
#else
							if(nsAPI_USB_ReqSetAddress())
								nsAPI_USB_StatusInStage();
							else
								nsAPI_USBCore_Stall_i();
#endif
							break;

						case USB_REQUEST_GET_DESCRIPTOR:
#if 0
							if(!nsAPI_USB_ReqGetDescriptor())
								goto stall_i;
				
							nsAPI_USB_DataInStage();
#else
							if(nsAPI_USB_ReqGetDescriptor())
								nsAPI_USB_DataInStage();
							else
								nsAPI_USBCore_Stall_i();
#endif
							break;

						case USB_REQUEST_SET_DESCRIPTOR:
							nsAPI_USB_SetStallEP(0x00);
							g_USBCore_Setting.EP0Data.Count = 0;
							break;

						case USB_REQUEST_GET_CONFIGURATION:
#if 0
							if(!nsAPI_USB_ReqGetConfiguration())
								goto stall_i;
							
							nsAPI_USB_DataInStage();
#else
							if(nsAPI_USB_ReqGetConfiguration())
								nsAPI_USB_DataInStage();
							else
								nsAPI_USBCore_Stall_i();
#endif
							break;

						case USB_REQUEST_SET_CONFIGURATION:
#if 0
							if(!nsAPI_USB_ReqSetConfiguration())
								goto stall_i;
							
							nsAPI_USB_StatusInStage();
#if USB_CONFIGURE_EVENT
							nsAPI_USB_Configure_Event();
#endif
#else
							if(nsAPI_USB_ReqSetConfiguration())
							{
								nsAPI_USB_StatusInStage();
#if USB_CONFIGURE_EVENT
								nsAPI_USB_Configure_Event();
#endif
							}
							else
							{
								nsAPI_USBCore_Stall_i();
							}
#endif
							break;

						case USB_REQUEST_GET_INTERFACE:
#if 0
							if(!nsAPI_USB_ReqGetInterface())
								goto stall_i;
							
							nsAPI_USB_DataInStage();
#else
							if(nsAPI_USB_ReqGetInterface())
								nsAPI_USB_DataInStage();
							else
								nsAPI_USBCore_Stall_i();
#endif
							break;

						case USB_REQUEST_SET_INTERFACE:
#if 0
							if(!nsAPI_USB_ReqSetInterface())
								goto stall_i;

							nsAPI_USB_StatusInStage();
#if USB_INTERFACE_EVENT
							USB_Interface_Event();
#endif
#else
							if(nsAPI_USB_ReqSetInterface())
							{
								nsAPI_USB_StatusInStage();
#if USB_INTERFACE_EVENT
								USB_Interface_Event();
#endif
							}
							else
							{
								nsAPI_USBCore_Stall_i();
							}
#endif
							break;

						default:
#if 0
							goto stall_i;
#else
							nsAPI_USBCore_Stall_i();
#endif
					}
					break;

#if USB_CLASS
				case REQUEST_CLASS:
					switch(g_USBCore_Setting.SetupPacket.bmRequestType.BM.Recipient)
					{
						case REQUEST_TO_DEVICE:
							goto stall_i;
							break;
		
						case REQUEST_TO_INTERFACE:
#if USB_HID
							switch(g_USBCore_Setting.SetupPacket.bRequest)
							{
								case HID_REQUEST_GET_REPORT:
								{
									g_USBCore_Setting.EP0Data.pData = g_USBCore_Setting.EP0Buf;
									nsAPI_USB_DataInStage();
									bSetupClassOk = TRUE;
								}

								wnDrv_Usb_ClrGetReqStatus(0x80); 
								break;

								case HID_REQUEST_SET_REPORT:
									nsAPI_USB_SetupStage();
									nsAPI_USB_StatusInStage();
									g_USBCore_Setting.EP0Data.pData = g_USBCore_Setting.EP0Buf;                             
									bSetupClassOk = TRUE;
									break;
		
								case HID_REQUEST_GET_IDLE:
									if(HID_GetIdle())
									{
										g_USBCore_Setting.EP0Data.pData = g_USBCore_Setting.EP0Buf;	// point to data to be sent
										nsAPI_USB_DataInStage();									// send requested data
										bSetupClassOk = TRUE;
									}
									break;
		
								case HID_REQUEST_SET_IDLE:
									if(HID_SetIdle())
									{
										nsAPI_USB_StatusInStage();									// send Acknowledge
										bSetupClassOk = TRUE;
									}
									break;
		
								case HID_REQUEST_GET_PROTOCOL:
									if(HID_GetProtocol())
									{
										g_USBCore_Setting.EP0Data.pData = g_USBCore_Setting.EP0Buf;	// point to data to be sent
										nsAPI_USB_DataInStage();									// send requested data
										bSetupClassOk = TRUE;
									}
									break;
		
								case HID_REQUEST_SET_PROTOCOL:
									if(HID_SetProtocol())
									{
										nsAPI_USB_StatusInStage();									// send Acknowledge
										bSetupClassOk = TRUE;
									}
									break;
							}
#endif
						case REQUEST_TO_ENDPOINT:
						default:
#if 0
							goto stall_i;
#else
							if(!bSetupClassOk)
								nsAPI_USBCore_Stall_i();
#endif
					}
setup_class_ok: // request finished successfully
					break;
#endif

				case REQUEST_VENDOR:						 	
					switch(g_USBCore_Setting.SetupPacket.bmRequestType.BM.Recipient)
					{
						case REQUEST_TO_DEVICE:
							if(g_USBCore_Setting.SetupPacket.bmRequestType.B == TCL_CONTROL_0_READ)		// read
							{
								usb_reg_addr = g_USBCore_Setting.SetupPacket.wIndex.WB.L;	// get the register address
								
								if(g_USBCore_Setting.SetupPacket.bRequest == 0x04)			// mcu register
								{  
									
									switch(usb_reg_addr)
									{
										case REF_MOUSE_INFO_ADDR:
											usb_reg_data = MOUSE_INFO;					// get infomation for mouse
											break;
		      
										case REF_MOUSE_EVENT_CTRL_ADDR:
											usb_reg_data = mouse_event_ctrl;			// get event control settings for mouse
											break;

										case REF_MOUSE_FIRMWARE_MAJOR_ADDR:
											usb_reg_data = MOUSE_FIRMWARE_major;		// get major firmware revision for mouse
											break;
										
										case REF_MOUSE_FIRMWARE_MINOR_ADDR:
											usb_reg_data = MOUSE_FIRMWARE_minor;		// get minor firmware revision for mouse
											break;

										case REF_MOUSE_RECOGNITION_ADDR:
											usb_reg_data = REFERENCE_MOUSE;					// get minor firmware revision for mouse
											break;
										
										case REF_MOUSE_SROM_WRITE_ADDR:
											usb_reg_data = ready_flash_flag;
											break;
										/*
										case REF_MOUSE_SPI_BURST_FRAME_CAPTURE:

											for(frameCntr = 0; frameCntr < FRAME_CAPTURE_SIZE; frameCntr++)
												tempframe[frameCntr] = 0;

											nsAPI_SSP_Sensor_Write(0x10, 0x00);
											nsAPI_SSP_Sensor_Write(0x12, 0x83);
											nsAPI_SSP_Sensor_Write(0x12, 0xC5);

											NCS_LOW();
											
											for(frameCntr = 0; frameCntr < FRAME_CAPTURE_SIZE; frameCntr++)
												nsAPI_SSP_Receive( &tempframe[frameCntr],1);

											NCS_HIGH();
											frameCntr = 0;

											usb_reg_data = 1;

											break;
										case REF_MOUSE_SPI_BURST_FRAME_CAPTURE_READ:
											usb_reg_data =	tempframe[frameCntr];
											frameCntr++;
											break;
										*/
																					
										default:
											usb_reg_data = 0;
											break;
									
									} 
								}
								else if(g_USBCore_Setting.SetupPacket.bRequest == 0x01)		// sensor register
								{	
									usb_reg_data = nsAPI_SSP_Sensor_Read(usb_reg_addr);
									nsAPI_SSP_Sensor_Write(0x50, 0x01); 					// UGS 2 only needed
								}							
								g_USBCore_Setting.EP0Data.pData = &usb_reg_data;
							    g_USBCore_Setting.EP0Data.Count = sizeof(usb_reg_data);
							}
							else if(g_USBCore_Setting.SetupPacket.bmRequestType.B == TCL_CONTROL_0_WRITE)	// write
							{
								usb_reg_addr = g_USBCore_Setting.SetupPacket.wIndex.WB.L;	// get the register address
								usb_reg_data = g_USBCore_Setting.SetupPacket.wIndex.WB.H;	// get the register data

								if(g_USBCore_Setting.SetupPacket.bRequest == 0x04)			// mcu register
								{  
									switch(usb_reg_addr)
									{
											
										case REF_MOUSE_EVENT_CTRL_ADDR:
											mouse_event_ctrl = usb_reg_data;      // set event control settings for mouse
											break;
								  					    
										case REF_MOUSE_SROM_LOAD_CTRL_ADDR:
											__disable_irq(); 											

											if((usb_reg_data & BIT2) == REBOOT) // reboot										
											{	
												nsAPI_SSP_Sensor_Init();
											}

											if( (usb_reg_data & BIT0) == INIT_TCL_FLASH)		// start flash initialization
											{
												sromCntr = 0;
												ready_flash_flag = FREE;
												flash_address_offset = 0;
												flash_sector_address = START_OF_FLASH_SECTOR;
		
												memset(usbSROM, 0, SROM_BUFFER_SIZE);
												
												if(msAPI_Flash_PrepareSec(Sector_6, Sector_7) == IAP_STA_CMD_SUCCESS)	// erase flash sector for incoming data
													msAPI_Flash_EraseSec(Sector_6, Sector_7);
											}
											else if( (usb_reg_data & BIT1) == TCL_END_FLASH)	// stop flash (by fill last sector)
											{																	
												if(sromCntr)									// sending leftover data inside RAM to FLASH
												{
													ready_flash_flag = READY_TO_FLASH;
													sromCntr =0;
												}														
											}
											
											__enable_irq();
											break;

										case REF_MOUSE_SROM_WRITE_ADDR:
											__disable_irq();

											if( sromCntr < SROM_BUFFER_SIZE )		// check if buffer is full
												usbSROM[sromCntr++] = usb_reg_data;	// if not continue loading the buffers
											
											if(sromCntr >= SROM_BUFFER_SIZE)		// if RAM buffer is full then proceed to ready the flashing
											{										
												sromCntr =0;						
												ready_flash_flag = READY_TO_FLASH;
											}
											__enable_irq();
											break;

										case REF_MOUSE_LED_SW_ADDR:
											if(usb_reg_data == 0x03) 
											{
												TURN_ON_20R_SW1_LED(LOW);	// Both CLOSED. the highest light
												TURN_ON_39R_SW2_LED(LOW);	
											} 
											else if (usb_reg_data == 0x02)
											{
												TURN_ON_20R_SW1_LED(LOW);	// 2nd highest light
												TURN_ON_39R_SW2_LED(HIGH);
											}
											else if (usb_reg_data == 0x01)
											{
												TURN_ON_20R_SW1_LED(HIGH);	// 3rd highest light
												TURN_ON_39R_SW2_LED(LOW);
											}
											else if (usb_reg_data == 0x00)
											{
												TURN_ON_20R_SW1_LED(HIGH);	// Turn off LED
												TURN_ON_39R_SW2_LED(HIGH);
											}
										break;
											
										default:
											break;
									}

									if(ready_flash_flag == READY_TO_FLASH)
									{
										__disable_irq();
									
										if(msAPI_Flash_PrepareSec(Sector_6, Sector_7) == IAP_STA_CMD_SUCCESS)
											msAPI_Flash_CopyRAM2Flash((U32)(START_OF_FLASH_SECTOR + flash_address_offset),	// target start of flash
																	  (U32)usbSROM,			// source 
																	  SROM_BUFFER_SIZE);	// package size
									
										if((flash_sector_address + flash_address_offset) < END_OF_FLASH_SECTOR)
											flash_address_offset = flash_address_offset + SROM_BUFFER_SIZE;
									
										memset(usbSROM, 0, SROM_BUFFER_SIZE);
	
										__enable_irq();

										ready_flash_flag = FREE;
									}
								}
								else if(g_USBCore_Setting.SetupPacket.bRequest == 0x01)		// sensor register
								{
									ready_flash_flag = BUSY_RW;		
									nsAPI_SSP_Sensor_Write(usb_reg_addr, usb_reg_data);
									ready_flash_flag = FREE;
								}	 
							}
							break;
		
						case REQUEST_TO_INTERFACE:
							break;
		
						case REQUEST_TO_ENDPOINT:
							break;

						default:
							goto stall_i;
					}
	
	
					if(g_USBCore_Setting.SetupPacket.wLength)
					{
						if(g_USBCore_Setting.SetupPacket.bmRequestType.BM.Dir == REQUEST_DEVICE_TO_HOST)
							nsAPI_USB_DataInStage();  // read only
					}
					else
					{
						nsAPI_USB_StatusInStage();
					}
					break;


#if USB_VENDOR
				case REQUEST_VENDOR:
					switch(g_USBCore_Setting.SetupPacket.bmRequestType.BM.Recipient)
					{
						case REQUEST_TO_DEVICE:
							if(!USB_ReqVendorDev(TRUE))
								goto stall_i;
							break;
		
						case REQUEST_TO_INTERFACE:
							if(!USB_ReqVendorIF(TRUE))
								goto stall_i;
							break;
		
						case REQUEST_TO_ENDPOINT:
							if(!USB_ReqVendorEP(TRUE))
								goto stall_i;
							break;
		
						default:
							goto stall_i;
					}

					if(g_USBCore_Setting.SetupPacket.wLength)
					{
						if(g_USBCore_Setting.SetupPacket.bmRequestType.BM.Dir == REQUEST_DEVICE_TO_HOST)
							nsAPI_USB_DataInStage();
					}
					else
					{
						nsAPI_USB_StatusInStage();
					}
					break;
#endif

				default:
stall_i:
					nsAPI_USBCore_Stall_i();
					break;
			}
			break;

		case USB_EVT_OUT:
			if(g_USBCore_Setting.SetupPacket.bmRequestType.BM.Dir == REQUEST_HOST_TO_DEVICE)
			{
				if(g_USBCore_Setting.EP0Data.Count)				// still data to receive ?
				{
					nsAPI_USB_DataOutStage();					// receive data

					if(g_USBCore_Setting.EP0Data.Count == 0)	// data complete ?
					{
						switch(g_USBCore_Setting.SetupPacket.bmRequestType.BM.Type)
						{
							case REQUEST_STANDARD:
#if 0
								goto stall_i;
#else
								nsAPI_USBCore_Stall_i();
								break;
#endif
#if (USB_CLASS)
							case REQUEST_CLASS:
								switch(g_USBCore_Setting.SetupPacket.bmRequestType.BM.Recipient)
								{
									case REQUEST_TO_DEVICE:
#if 0
										goto stall_i;
#else
										nsAPI_USBCore_Stall_i();
										break;
#endif
									case REQUEST_TO_INTERFACE:
#if USB_HID
										if(g_USBCore_Setting.SetupPacket.wIndex.WB.L == USB_HID_IF_NUM)	// if number correct?
										{
											switch(g_USBCore_Setting.SetupPacket.bRequest)
											{
												case HID_REQUEST_SET_REPORT:
													if(HID_SetReport())
													{
														nsAPI_USB_StatusInStage();	// send Acknowledge
														bOutClassOk = TRUE;
													}
													break;
											}
										}
#endif

									case REQUEST_TO_ENDPOINT:
									default:
										if(!bOutClassOk)
											nsAPI_USBCore_Stall_i();
								}
out_class_ok:
								break;
#endif
#if USB_VENDOR
							case REQUEST_VENDOR:
								switch(g_USBCore_Setting.SetupPacket.bmRequestType.BM.Recipient)
								{
									case REQUEST_TO_DEVICE:
										if(!USB_ReqVendorDev(FALSE))
											goto stall_i;
										break;
		
									case REQUEST_TO_INTERFACE:
										if(!USB_ReqVendorIF(FALSE))
											goto stall_i;
										break;
		
									case REQUEST_TO_ENDPOINT:
										if(!USB_ReqVendorEP(FALSE))
											goto stall_i;
										break;
									
									default:
										goto stall_i;
								}

								nsAPI_USB_StatusInStage();
								break;
#endif
							default:
#if 0
								goto stall_i;
#else
								nsAPI_USBCore_Stall_i();
								break;
#endif
						}
					}
				}
			}
			else
			{
				nsAPI_USB_StatusOutStage();	// receive Acknowledge
			}
			break;

		case USB_EVT_IN:
			if(g_USBCore_Setting.SetupPacket.bmRequestType.BM.Dir == REQUEST_DEVICE_TO_HOST)
			{
				nsAPI_USB_DataInStage();	// send data
			}
			else
			{
				if(g_USBCore_Setting.USB_DeviceAddress & 0x80)
				{
					g_USBCore_Setting.USB_DeviceAddress &= 0x7F;
					nsAPI_USB_SetAddress(g_USBCore_Setting.USB_DeviceAddress);
				}
			}
			break;

		case USB_EVT_OUT_STALL:
			nsAPI_USB_ClrStallEP(0x00);
			break;

		case USB_EVT_IN_STALL:
			nsAPI_USB_ClrStallEP(0x80);
			break;
	}
}


//----------------------------------------------------------------------------
//  
//----------------------------------------------------------------------------
void nsAPI_USBCore_Stall_i(void)
{
	nsAPI_USB_SetStallEP(0x80);
	g_USBCore_Setting.EP0Data.Count = 0;
}
