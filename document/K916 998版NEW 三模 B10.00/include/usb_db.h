#ifndef __USB_DP_H
#define __USB_DP_H

#include "..\include\usb_def.h"
#include "..\include\stdtype.h"
#include "..\include\auser.h"
/******************************************************************************************
USB emu
******************************************************************************************/

/******************************************************************************************
string Information
******************************************************************************************/
#define IC_MANUFACTURER_STR	"B\0Y\0 \0T\0e\0c\0h\0"
//#define MANUFACTURER_DESC	"S\0I\0N\0O\0 \0W\0E\0A\0L\0T\0H\0"
#define PRODUCT_DESC		"\K\0e\0y\0b\0o\0a\0r\0d\0"
#define USB_STRING_LENGTH(length)	((length) * 2 + 2)

 
#define VID					0x258A//0x045e
#define PID					0x00A1//0x028e
#define DEV_RELEASE_NO		0x1000
#define BCDUSB				0x0110	  
const U8 code str_dp_product[] =
{
	USB_STRING_LENGTH(18),		//length
	0x03, 	// type
	//GAME MOUSE
	//'R', 0, 'K', 0, ' ', 0,
	'B', 0, 'l', 0, 'u', 0, 'e', 0, 't', 0,'o', 0,'o', 0,'t', 0,'h', 0,' ', 0,  
	'K', 0, 'e', 0, 'y', 0, 'b', 0, 'o', 0,'a', 0,'r', 0,'d', 0,
};

const U8 code str_dp_manufact[] =
{
	USB_STRING_LENGTH(11),		//length
	0x03, 	// type
	//GAME MOUSE
	'S', 0, 'I', 0, 'N', 0, 'O', 0, ' ', 0,
	'W', 0,'E', 0, 'A', 0, 'L', 0, 'T', 0,'H', 0	
	/*
	2 + sizeof(MANUFACTURER_DESC)-1,		//size of string + string type + unicode string
	USB_STRING,									        // type
	MANUFACTURER_DESC
	*/
};

const U8 code str_dp_sn[] =
{
	USB_STRING_LENGTH(4),								//length
	USB_STRING,									       // type
	'0', 0, '0', 0, '0', 0, '1', 0
};

const U8 code str_dp_sino[] =
{
	2 + sizeof(IC_MANUFACTURER_STR)-1,		//size of string + string type + unicode string
	USB_STRING, 													// type
	IC_MANUFACTURER_STR
};
const U8 code str_dp_langID[] =
{
	0x04,																//Length
	USB_STRING,													//String Type
	0x09,																//Language
	0x04		
};


/******************************************************************************************
 HID report Information1
******************************************************************************************/
//keyboard
const U8 code HID_report_desc1[] =
{
	//	KEYBORAD REPORT DESCRIPTOR
	 	0x05, 0x01, 		// USAGE_PAGE (Generic Desktop)
		 0x09, 0x06, 		// USAGE (Keyboard)
		 0xA1, 0x01, 		// COLLECTION (Application)
		 0x05, 0x07, 		//     USAGE_PAGE (Keyboard/Keypad)
		 0x19, 0xe0, 		//     USAGE_MINIMUM (L_Ctrl,L_Shift,L_Alt,L_Gui,R_Ctrl,R_Shift,R_Alt,R_Gui)
		 0x29, 0xe7, 		//     USAGE_MAXIMUM (Keyboard Right GUI)
		 0x15, 0x00, 		//     LOGICAL_MINIMUM (0)
		 0x25, 0x01, 		//     LOGICAL_MAXIMUM (1)
		 0x95, 0x08, 		//     REPORT_COUNT (8)
		 0x75, 0x01, 		//     REPORT_SIZE (1)
		 0x81, 0x02, 		//     INPUT (Data,Var,Abs)
		
		 0x95, 0x01, 		//     REPORT_COUNT (1)
		 0x75, 0x08, 		//     REPORT_SIZE (8)
		 0x81, 0x03, 		//     INPUT (Cnst,Var,Abs)
		 	 
		 0x95, 0x06, 		//   REPORT_COUNT (6)
		 0x75, 0x08, 		//   REPORT_SIZE (8)
		 0x15, 0x00, 		//   LOGICAL_MINIMUM (0)
		 0x26, 0xff, 0x00, 	//   LOGICAL_MAXIMUM (255)
		 0x05, 0x07, 		//   USAGE_PAGE (Keyboard/Keypad)
		 0x19, 0x00, 		//   USAGE_MINIMUM (Reserved (no event indicated))
		 0x2a, 0xff, 0x00, 	//   USAGE_MAXIMUM (Keyboard Application)
		 0x81, 0x00, 		//     INPUT (Data,Ary,Abs)
		 
		 0x25, 0x01, 		//   LOGICAL_MAXIMUM (1)
		 0x95, 0x05, 		//   REPORT_COUNT (5)
		 0x75, 0x01, 		//   REPORT_SIZE (1)
		 0x05, 0x08, 		//   USAGE_PAGE (LEDs)
		 0x19, 0x01,		//   USAGE_MINIMUM (Num Lock)
		 0x29, 0x05,		//   USAGE_MAXIMUM (Kana)
		 0x91, 0x02, 		//   OUTPUT (Data,Var,Abs)
		 0x95, 0x01, 		//   REPORT_COUNT (1)
		 0x75, 0x03, 		//   REPORT_SIZE (3)
		 0x91, 0x03, 		//   OUTPUT (Cnst,Var,Abs)
		         
		 0xc0        		//   END_COLLECTION
};
const U8 code HID_report_desc2[] =
{
//#if(EP2_ACPI_ENABLE)
// *****************************************************
// ACPI REPORT DESCRIPTOR, bit0/bit1/bit2 correspond KeyCode 0x81/0x82/0x83.
// *****************************************************
	0x05,0x01,		// USAGE PAGE(GENERIC DESKTOP)
	0x09,0x80,		// Usage (SYSTEM CONTROL)
	0xA1,0x01,		// Collection (Application)
	0x85,0x01,		//ACPI_RID,	// Report ID (ACPI)
	0x19,0x81,		// USAGE MINIMUM(0x81)
	0x29,0x83,		// USAGE MAXIMUM(0x83)
	0x15,0x00,		// LOGICAL MINIMUM(0)
	0x25,0x01,		// LOGICAL MINIMUM(1)
	0x75,0x01,		// Report Size(1)
	0x95,0x03,		// REPORT_COUNT(3)
	0x81,0x02,		// Input (Data, Variable, )
	0x95,0x05,		// Report Count(5)
	0x81,0x01,		// Input (CONSTANT)
	0xC0,			// END COLLECTION
//#endif

//#if(EP2_CONSUMER_ENABLE)
// *****************************************************
// CONSUMER REPORT DESCRIPTOR, Report original code.
// *****************************************************
	0x05,0x0C,				// Usage Page
	0x09,0x01,				// Usage
	0xA1,0x01,			// Collection
	0x85,0x02,				//	CONSUMER_RID,		// Report ID
	0x19,0x00,				// Usage Minimum
	0x2A,0x3C,0x02,		//0x80, 0x03, 		// Usage Maximum
	0x15,0x00,				// Logical Minimum
	0x26,0x3C,0x02,		//0x80, 0x03,		// Logical Maximum
	0x95,0x01,				// Report Count
	0x75,0x10,				// Report Size(16bit,2Bytes)
	0x81,0x00,				// Input
	0xC0,					// End Collection
	
//#if(EP2_ISP_ENABLE)
	0x06, 0x00, 0xFF,		// usage page(﹚竡)
	0x09, 0x01,				// usage(1)
	0xA1, 0x01,				// Collection(Application)
	0x85, 0x05,			//	ISP_CTRL_RID,		// REPORT_ID (5)
	0x15, 0x00,				// Logical Minimum (0)
	0x26, 0xFF, 0x00,		// Logical Maximum (255)
	0x19, 0x01,				// Usage Minimum(0x01)
	0x29, 0x02,				// Usage Maximum(0x05)
	0x75, 0x08,				// REPORT SIZE (8)
	0x95, 0x05,				// REPORT COUNT(5)
	0xB1, 0x02,				// FEATURE(DATA,VARIABLE,ABSOLUTE)
	0xC0,					// END COLLECTION
//#endif
	//全键无冲突键盘
	0x05, 0x01, 
	0x09, 0x06,  
	0xa1, 0x01, 
	0x85, 0x06,  	         
	0x05, 0x07, 
	0x19, 0x04,  
	0x29, 0x70, 
	0x15, 0x00,  
	0x25, 0x01, 
	0x75, 0x01,  
	0x95, 0x78, 
	0x81, 0x02,  
	0xc0, 		
	//*****************************
//#if(EP2_Unconflicted_ENABLE)
//	0x06, 0x00, 0xFF, 	// usage page(自定义)   
//	0x09, 0x01,			// usage(1)
//	0xA1, 0x01,			// Collection(Application)
//	0x85, General_RID,		// REPORT_ID (0x09)
//	0x15, 0x00,			// Logical Minimum (0)
//	0x26, 0xFF, 0x00,	// Logical Maximum (255)
//	0x09, 0x00,
//	0x75, 0x08,			// REPORT SIZE (8)
//	0x96, 0x00,0X04,			// REPORT COUNT(576)  
//	0xB1, 0x02,			// FEATURE(DATA,VARIABLE,ABSOLUTE)
//	0xC0,
	
	0x06, 0x00, 0xFF, 		// usage page(自定义)   
	0x09, 0x01,			// usage(1)
	0xA1, 0x01,			// Collection(Application)
	0x85, LedMode_RID,	// 0X0a
	0x15, 0x00,			// Logical Minimum (0)
	0x26, 0xFF, 0x00,		// Logical Maximum (255)
	0x09, 0x00,
	0x75, 0x08,			// REPORT SIZE (8)
	0x95, 64,				// REPORT COUNT(576)  
	0xB1, 0x02,			// FEATURE(DATA,VARIABLE,ABSOLUTE)
	0xC0,
//#endif
};
/******************************************************************************************
device information
******************************************************************************************/

const U8 code device_descriptor[] =
{
	0x12,										// device descriptor length
	USB_DEVICE,							// device descriptor type 0x01
	(BCDUSB & 0xff),				
	(BCDUSB >> 8),					// usb type: usb1.1
	0x00,										// bDevice class:normal 0
	0x00,										// bDevice sub class:normal 0  (0xff:﹚竡砞称)
	0x00,										// bDevice protocl:normal 0	(0xff:﹚竡砞称)
	0x08,										// end0 max data length:8bytes
	(VID & 0xFF),
	(VID >> 8),
	(PID & 0xFF),
	(PID >> 8),						//VID & PID
	(DEV_RELEASE_NO & 0xFF),	
	(DEV_RELEASE_NO >> 8),			// device release NO. 0x19
	0x01,										// imanufacturer index
	0x02,										// iproduct idex
	0x00,										// iserial Number index(0:no serial NO.)
	0x01										// number of configurations(1:one type conf.)
};
/******************************************************************************************
configration  Information (configaration/interface/hid/endpoint)
******************************************************************************************/
#define CONFIGURATION_SIZE 	    CONFIG_DESC_SIZE+(INTERFACE_SIZE+HID_SIZE+ENDPOINT_SIZE)*2
#define CONFIG_DESC_SIZE		9
#define INTERFACE_SIZE			9
#define HID_SIZE						9
#define ENDPOINT_SIZE				7
#define BCDHID							0x0111
static const U8 code config_descriptor[] =
{
/* configration descriptor */
	CONFIG_DESC_SIZE,									// configration descriptor length
	USB_CONFIGURATION,								// configration descriptor type 0x02
	(CONFIGURATION_SIZE & 0xff),	
	(CONFIGURATION_SIZE >> 8),				//wtotallength :total length of configration information 
	INTERFACE_NO,											// device interface NO.
	0x01,															// configration valueindex
	0x00,															// the confi string index (0:null)
	0xa0,															// 	bus supply power & support suspend
	0xfa,															// 	max current from bus(500mA)

/* interface descriptor/NO.0 */
	INTERFACE_SIZE,										// interface descriptor length
	USB_INTERFACE,										// interface descriptor type 0x04
	0x00,															// interface NO.(start 0)
	0x00,															// alternnate interface NO.
	0x01,															// this interface contian endpoint number
	0x03,															// 	interface type(HID)
	0x01,															// 	binterface sub class:0x00: No subclass/ 0x01:startsubclass/ 0x02~0xff:Reserved
	0x01,															//  binterface protocl:0x01: keyboard; 0x02: mouse 0x00:None 0x03~0xff:Reserved
	0x00,															// the interface string index (0:null)

/* HID class descriptor */
	HID_SIZE,													// HID class descriptor length
	USB_HID,													// HID class descriptor type 0x21
	(BCDHID & 0xff),									// 02H - BCDHID:HID CLASS SPECIFICATION RELEASE NUMBER IN BINARYCODED DECIMAL (FOR EXAMPLE, 2.10 IS 0X210).
	(BCDHID >> 8),
	0x00,															// 04H - BCOUNTRYCODE:HARDWARE TARGET COUNTRY.
	0x01,															// 05H - BNUMDESCRIPTORS:NUMBER OF HID CLASS DESCRIPTORS TO FOLLOW.
	0x22,															// 06H - BDESCRIPTORTYPE:REPORT DESCRIPTOR TYPE.
	(sizeof(HID_report_desc1)&0xff), (sizeof(HID_report_desc1)>>8), 	// 报表描述符总长度
	

/* endpoint descriptor */
	ENDPOINT_SIZE,										// endpoint descriptor length
	USB_ENDPOINT,											// endpoint descriptor type 0x05
	0x81,															// the endpoint address(D7=1:IND3~D0endpoint number)
	0x03,															// endpoint type0x03interrupt endpoint
	0x08, 														// endpoint data  length8bytes
	0x00,						
	0x01,															// host get message time1ms/t

/* interface descriptor/NO.1 */	

	INTERFACE_SIZE,										// interface descriptor length
	USB_INTERFACE,										// interface descriptor type 0x04
	0x01,															// interface NO.(start 0)
	0x00,															// alternnate interface NO.
	0x01,															// this interface contian endpoint number
	0x03,															// 	interface type(HID)
	0x00,															// 	binterface sub class:0x00: No subclass/ 0x01:startsubclass/ 0x02~0xff:Reserved
	0x00,															//  binterface protocl:0x01: keyboard; 0x02: mouse 0x00:None 0x03~0xff:Reserved
	0x00,															// the interface string index (0:null)

/* HID class descriptor */
	HID_SIZE,													// HID class descriptor length
	USB_HID,													// HID class descriptor type 0x21
	(BCDHID & 0xff),									// 02H - BCDHID:HID CLASS SPECIFICATION RELEASE NUMBER IN BINARYCODED DECIMAL (FOR EXAMPLE, 2.10 IS 0X210).
	(BCDHID >> 8),
	0x00,															// 04H - BCOUNTRYCODE:HARDWARE TARGET COUNTRY.
	0x01,															// 05H - BNUMDESCRIPTORS:NUMBER OF HID CLASS DESCRIPTORS TO FOLLOW.
	0x22,															// 06H - BDESCRIPTORTYPE:REPORT DESCRIPTOR TYPE.
	(sizeof(HID_report_desc2)&0xff), (sizeof(HID_report_desc2)>>8), 	// 报表描述符总长度
	

/* endpoint descriptor */
	ENDPOINT_SIZE,										// endpoint descriptor length
	USB_ENDPOINT,											// endpoint descriptor type 0x05
	0x82,															// the endpoint address(D7=1:IND3~D0endpoint number)
	0x03,															// endpoint type0x03interrupt endpoint
	0x10, 														// 
	0x00,						
	0x01,															// host get message time8ms/t
	
};

/******************************************************************************************
mouse hid  Information1 
******************************************************************************************/
const U8 code hid_descriptor1[] =	
{
	/* HID class descriptor */
	0x09,						
	USB_HID,			
	0x11, 0x01,		
	0x00,			
	0x01,			
	0x22,			
	(sizeof(HID_report_desc1)&0xff), (sizeof(HID_report_desc1)>>8), 	
};
/******************************************************************************************
mouse hid  Information2 
******************************************************************************************/
const U8 code hid_descriptor2[] =	
{
	/* HID class descriptor */
	0x09,			
	USB_HID,			
	0x11, 0x01,	
	0x00,			
	0x01,			
	0x22,			
	(sizeof(HID_report_desc2)&0xff), (sizeof(HID_report_desc2)>>8), 	
};


#endif

