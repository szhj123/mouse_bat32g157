#ifndef __USB_DEF_H
#define __USB_DEF_H

#include "..\include\stdtype.h"

/******************************************************************************************
steup define
******************************************************************************************/
//steup order bmRequestType																				
#define	HOST_TO_DEVICE			 			0x00
#define	DEVICE_TO_HOST			 			0x80
#define	STANDARD						 			0x00
#define	CLASS											0x20
#define	VENDOR							 			0x40
#define	DEVICE							 			0x00
#define	INTERFACE						 			0x01
#define	ENDPOINT						 			0x02
#define	OTHER											0x03

//usb steup order wValue
#define USB_GET_STATUS						0x00
#define USB_CLEAR_FEATURE					0x01
#define USB_SET_FEATURE						0x03
#define USB_SET_ADDRESS						0x05
#define USB_GET_DESCRIPTOR				0x06
#define USB_SET_DESCRIPTOR				0x07
#define	USB_GET_CONFIGURATION			0x08
#define	USB_SET_CONFIGURATION			0x09
#define	USB_GET_INTERFACE					0x0A
#define	USB_SET_INTERFACE					0x0B
#define USB_SYNCH_FRAME						0x0C

//hid steup order wValue
#define HID_GET_REPORT						0x01
#define HID_GET_IDLE							0x02
#define HID_GET_PROTOCOL					0x03
#define HID_SET_REPORT						0x09
#define HID_SET_IDLE							0x0A
#define HID_SET_PROTOCOL					0x0B


#define BULK_CLASS1_PROTOCOL			0xFE	
#define BULK_CLASS2_PROTOCOL			0xFF	

/******************************************************************************************
usb emu data define
******************************************************************************************/

//usb configration type id
#define	USB_DEVICE								0x01
#define	USB_CONFIGURATION					0x02
#define	USB_STRING								0x03
#define	USB_INTERFACE							0x04
#define	USB_ENDPOINT							0x05
	
//string type id	
#define STRING_LANGUAGE_ID				0x00
#define STRING_MANUFACTURER				0x01
#define STRING_PRODUCT						0x02
#define STRING_SERIAL_NUMBER			0x03
#define STRING_SINO								0xFF
	
//descriptor type
#define	USB_HID										0x21
#define	USB_REPORT								0x22



/* hid mode */
#define REPORT_TYPE_INPUT   				1	
#define REPORT_TYPE_OUTPUT  				2
#define REPORT_TYPE_FEATURE 				3

	
#define DEVICE_REMOTE_WAKEUP				1
#define BOOT_PROTOCOL								0
#define REPORT_PROTOCOL							1


/* 数据类型状态 */
#define DEVICE_TYPE									0
#define INTERFACE_TYPE							1
#define ENDPOINT_TYPE								2

/* EP0 */
#define NEW_SETUP_PHASE						0x00
#define IN0_DATA_PHASE						0x01
#define OUT0_STATUS_PHASE					0x02
#define IN0_STATUS_PHASE					0x03
#define OUT0_LED_PHASE						0x04
#define OUT0_Rev_PHASE						0x06

#define OUT0_TYPE_Config_PHASE			0x05
#define OUT0_TYPE_KEY_PHASE					0x08

#define OUT0_ISP_PHASE						0X05//0x09
/* interface */
#define interface0_PHASE					0x00
#define interface1_PHASE					0x01

/* USB buffer address */
#define OUT0_BUFFER_ADDRESS	  				0x1100
#define IN0_BUFFER_ADDRESS	  				0x1108
#define IN1_BUFFER_ADDRESS	  				0x1120
#define IN2_BUFFER_ADDRESS	  				0x1180
#define OUT2_BUFFER_ADDRESS	  				0x11c0
#define OUT1_BUFFER_ADDRESS	  				0x1110

/* ENDPOINT0 */
#define EP0_MAX_SIZE						8


#define GET_DEVICE_DESCRIPTOR				1
#define GET_CONFIG_DESCRIPTOR				2
#define GET_STRING_DESCRIPTOR				3

#define IN0_SET_READY			{EP0CON |= BIT2;}			
#define IN0_SET_STALL			{EP0CON |= BIT3;}
#define IN0_CANCEL_STALL	{ EP0CON &= ~BIT3;  }

#define OUT0_SET_READY		{USBIF1 &= ~(BIT6); EP0CON |= BIT0; }
#define OUT0_SET_STALL		{EP0CON |= BIT1;}
#define OUT0_CANCEL_STALL	{EP0CON &= ~BIT1;}

#define IN1_SET_READY			{EP1CON |= BIT2;}
#define IN1_SET_STALL			{EP1CON |= BIT3;}
#define IN1_CANCEL_STALL	{EP1CON &= ~BIT3;}

#define OUT1_SET_READY		{EP1CON |= BIT0;}
#define OUT1_SET_STALL		{EP1CON |= BIT1;}
#define OUT1_CANCEL_STALL	{EP1CON &= ~BIT1;}

#define OUT2_SET_READY		{EP2CON |= BIT0;}
#define OUT2_SET_STALL		{EP2CON |= BIT1;}
#define OUT2_CANCEL_STALL	{EP2CON &= ~BIT1;}

#define IN2_SET_READY			{EP2CON |= BIT2;}
#define IN2_SET_STALL			{EP2CON |= BIT3;}
#define IN2_CANCEL_STALL	{EP2CON &= ~BIT3;}


/******************************************************************************************
usb reg	tyd
******************************************************************************************/


typedef struct 
{
	U8	bmRequestType;		// BIT7 - DATA TRANSFER DIRECTION
												//	0 = HOST-TO-DEVICE
												//	1 = DEVICE-TO-HOST
												// BIT6:5 - TYPE
												//	0 = STANDARD
												//	1 = CLASS
												//	2 = VENDOR
												//	3 = RESERVED
												// BIT4:0 - RECIPIENT
												//	0 = DEVICE
												//	1 = INTERFACE
												//	2 = ENDPOINT
												//	3 = OTHER
												//	4..31 = RESERVED
	U8	bRequest;
	U16	wValue;						// Notice this Length
	U16	wIndex;
	U16	wLength;
}usb_device_req;

typedef union 
{
	U8		Bdata[8];
	usb_device_req	u;
}rx0_buffer_union;

///////////////////////////////////////

/******************************************************************************************
HID report Information2
******************************************************************************************/
#define EP2_ACPI_ENABLE					1
#if(EP2_ACPI_ENABLE)		  	
	#define ACPI_RID							0x01
	#define ACPI_SIZE							1
#endif

#define EP2_CONSUMER_ENABLE			1
#if(EP2_CONSUMER_ENABLE)
	#define CONSUMER_RID					0x02
	#define CONSUMER_SIZE					2
#endif

#define EP2_VENDOR_ENABLE				0		// No being used
#if(EP2_VENDOR_ENABLE)
	#define VENDOR_RID						0x03
	#define VENDOR_SIZE						2
#endif

#define EP2_ISP_ENABLE					1	// ISP function enable
#if(EP2_ISP_ENABLE)
	#define ISP_CTRL_RID					0x05	// Must be 0x05, Because PC soft Lock!!!
	#define ISP_RID								0x05
#endif


#if(EP2_ISP_ENABLE || EP2_ACPI_ENABLE || EP2_CONSUMER_ENABLE)
	#define EP2_KEY_ENABLE				1
	#define EP2_ENABLE						1

	#define INTERFACE1_ENABLE			1
	#define INTERFACE_NO					2
#else
	#define EP2_KEY_ENABLE				0
	#define EP2_ENABLE						0

	#define INTERFACE1_ENABLE			0
	#define INTERFACE_NO					1
#endif


/******************************************************************************************

						procedure  declare

******************************************************************************************/

///////////////////////////computer hid data ////////////////////////
void usb_init(void);
void get_out_usb_buffer(void);
void IN0_SetReady(void);
void fill_in0_buf(U8 code *ctr, U8 len);
static void prep_ep0_in_dat(void);
void SETUP_IRQ_Prog(void);
void SUSPEND_IRQ_Prog(void);
void OUT0_IRQ_Prog(void);
void IN0_IRQ_Prog(void);

void USB_QueryINT_Prog(void);

static void stall_ep0(void);
static void clear_remote_wakeup(void);
static void clear_endpoint_halt(void);
static void set_remote_wakeup(void);
static void set_endpoint_halt(void);
static void set_address(void);
static void set_configuration(void);
static void set_interface(void);
static void set_descriptor(void);
static void get_device_status(void);
static void get_interface_status(void);
static void get_endpoint_status(void);
static void get_descriptor();
static void get_configuration(void);
static void get_interface(void);
static void get_report(void);
static void set_report(void);
static void USB_HID_SETIDLE(void);
static void USB_HID_GET_IDLE(void);
static void USB_HID_SETPROTOCOL(void);
static void USB_HID_GETPROTOCOL(void);

void IN2_IRQ_Prog(U8 *ctr, U8 len);
//void OUT2_IRQ_Prog(void);
void IN1_IRQ_Prog(U8 *ctr, U8 len);
//void OUT1_IRQ_Prog(void);


#endif
