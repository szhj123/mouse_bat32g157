/******************************************************************************
 Includes   <System Includes> , "Project Includes"
 ******************************************************************************/
//#include "r_usb_basic.h"
//#include "r_usb_basic_api.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "usb_phid_pmsc_apl.h"
#include "usb_phid_apl.h"
/******************************************************************************
 Macro definitions
 ******************************************************************************/
#define USBD_VID                        0x0416
#define USBD_PID                        0x5020

#define USB_CONFIG_DESCRIPTOR_LEN       (USB_CD_BLENGTH + USB_ID_BLENGTH*4 + USB_ED_BLENGTH*3)

#define HID_KEYBOARD                    0x01
#define HID_MOUSE                       0x02

/******************************************************************************
 Private global variables and functions
 ******************************************************************************/

/******************************************************************************
 Exported global variables
 ******************************************************************************/

/******************************************************************************
 Exported global functions (to be accessed by other files)
 ******************************************************************************/

const uint8_t g_apl_mouse_report[] =
{
    0x05, 0x01,			// Usage Page (Generic Desktop Control)
	0x09, 0x02,			// Usage (Mouse)
	0xA1, 0x01,			// Collection (Application)
	0x85, REPORT_ID_MOUSE,    // Report ID

    0x09, 0x01,			// Usage (Pointer)
	0xA1, 0x00,			// Collection (Physical)
	0x05, 0x09,			// Usage Page (Button)
	0x19, 0x01,			// Usage Minimum (1)
	0x29, 0x05,			// Usage Maximum (5)
	0x15, 0x00,			// Logical Minimum (0)
	0x25, 0x01,			// Logical Maximum (1)

	0x75, 0x01,			// Report Size (1)
	0x95, 0x05,			// Report Count (5)
	0x81, 0x02,			// Input (Data, Variable, Absolute)

    0x75, 0x03,         /* Report Size(0x3) */
    0x95, 0x01,         /* Report Count(0x1) */
    0x81, 0x01,         /* Input(5 bit padding) */

	0x05, 0x01,			// Usage Page (Generic Desktop Control)
	0x09, 0x30,			// Usage (X)
	0x09, 0x31,			// Usage (Y)
	0x16, 0x00, 0x80,	// Logical Minimum (-32768) LSB first
	0x26, 0xff, 0x7f,	// Logical Maximum (32767)
	0x75, 0x10,			// Report Size (16)	//4BYTE
	0x95, 0x02,			// Report Count (2)
	0x81, 0x06,			// Input (Data, Variable, Relative)
	0x05, 0x01,			// Usage Page (Generic Desktop Control)
	0x09, 0x38,			// Usage (Wheel)
	0x15, 0x80,			// Logical Minimum (-128)
	0x25, 0x7F,			// Logical Maximum (127)
	0x75, 0x08,			// Report Size (8)
	0x95, 0x01,			// Report Count (1)
	0x81, 0x06,			// Input (Data, Variable, Relative)
	0xC0,				// End Collection
	0xC0				// End Collection
};

const uint8_t g_apl_keyboard_report[] =
{
    0x05,0x01,          /* Usage Page(Generic Desktop Controls) */
    0x09,0x06,          /* Usage(Keyboard) */
    0xa1,0x01,          /* Collection(Application) */
    0x85,REPORT_ID_KEYBOARD,  /* REPORT ID 0x02 */
    0x05,0x07,          /* Usage Page(Keyboard/Keypad) */
    0x19,0xe0,          /* Usage Minimum(0xE0) */
    0x29,0xe7,          /* Usage Maximum(0xE7) */
    0x15,0x00,          /* Logical Minimum(0x0) */
    0x25,0x01,          /* Logical Maximum(0x1) */
    0x95,0x08,          /* Report Count(0x8) */
    0x75,0x01,          /* Report Size(0x1) */
    0x81,0x02,          /* Input (Data) => Modifier byte */

    0x95,0x06,          /* Report Count(0x6) */
    0x75,0x08,          /* Report Size(0x8) */
    0x15,0x00,          /* Logical Minimum(0x0) */
    0x25,0xff,          /* Logical Maximum(0xff) */
    0x05,0x07,          /* Usage Page(Keyboard/Keypad) */
    0x19,0x00,          /* Usage Minimum(0x0) */
    0x29,0xff,          /* Usage Maximum(0xff) */
    0x81,0x00,          /* Input (Data) */
    0xc0,               /* End Collection */

    0x05,0x0c,          /* Usage page (Consumer) */
    0x09,0x01,          /* Consumer Control */
    0xa1,0x01,          /* Collection(Application) */
    0x85,REPORT_ID_CONSUMER,  /* REPORT ID 0x03 */
    0x0A,0x21,0x02,     // USAGE WWW SEARCH
    0x0A,0x23,0x02,     // USAGE WWW HOME
    0x0A,0x24,0x02,     // USAGE WWW BACKWARD
    0x0A,0x25,0x02,     // USAGE WWW FORWARD
    0x0A,0x26,0x02,     // USAGE WWW STOP
    0x0A,0x27,0x02,     // USAGE WWW REFRESH
    0x0A,0x2A,0x02,     // USAGE MY FAVORITE
    0x0A,0xB1,0x02,     // TURBO
    0x15, 0x00,         // Logical Minimum (0)
    0x25, 0x01,         // Logical Maximum (1)
    0x95,0x08,          /* Report Count(0x8) */
    0x75,0x01,          /* Report Size(0x1) */
    0x81,0x03,          /* Input (Data) */

    0x0A,0xB5,0x00,		// USAGE NEXT_TRACK
	0x0A,0xB6,0x00,		// USAGE PRE_TRACK
	0x0A,0xB7,0x00,		// USAGE STOP
	0x0A,0xCD,0x00,		// USAGE PLAY/PAUSE
	0x0A,0xE2,0x00,		// USAGE MUTE
	0x0A,0xA2,0x00,		// USAGE FLIP 3D
	0x0A,0xE9,0x00,		// USAGE VOL_INC
	0x0A,0xEA,0x00,		// USAGE VOL_DEC
	0x15,0x00,			// Logical Minimum (0)
	0x25,0x01,			// Logical Maximum (1)
    0x95,0x08,          // Report Count(0x8)
    0x75,0x01,          // Report Size(0x1)
	0x81,0x03,			// INPUT()

    0x0A,0x83,0x01,		// USAGE MEDIA SELECT
	0x0A,0x94,0x01,		// USAGE My Computer
	0x0A,0x86,0x01,		// USAGE EXCEL
	0x0A,0x88,0x01,		// USAGE POWER POINT
	0x0A,0x8A,0x01,		// USAGE EMAIL
	0x0A,0x92,0x01,		// USAGE CALCULATOR
	0x0A,0xA8,0x02,		// USAGE PHOTO GALLERY
	0x0A,0x84,0x01,		// USAGE Word
	0x15,0x00,			// Logical Minimum (0)
	0x25,0x01,			// Logical Maximum (1)
    0x95,0x08,          // Report Count(0x8)
    0x75,0x01,          // Report Size(0x1)
	0x81,0x03,			// INPUT()
    0xc0,               /* End Collection */

    0x06, 0x02, 0xFF, 	// usage page(�Զ���)
	0x09, 0x01,			// usage(1)
	0xA1, 0x01,			// Collection(Application)
	0x85, REPORT_ID_KEY_VALUE,// REPORT_ID (0x60)
	0x15, 0x00,			// Logical Minimum (0)
	0x26, 0xFF, 0x00,	// Logical Maximum (255)
	0x09, 0x00,
	0x75, 0x08,			// REPORT SIZE (8)
	0x95, 0x3f,			// REPORT COUNT(63)
	0xB1, 0x02,			// FEATURE(DATA,VARIABLE,ABSOLUTE)
	0xC0,

    0x06, 0x03, 0xFF, 	// usage page(�Զ���)
	0x09, 0x01,			// usage(1)
	0xA1, 0x01,			// Collection(Application)
	0x85, REPORT_ID_LIGHT_DPI_RATE,      // REPORT_ID (0x61)
	0x15, 0x00,			// Logical Minimum (0)
	0x26, 0xFF, 0x00,	// Logical Maximum (255)
	0x09, 0x00,
	0x75, 0x08,			// REPORT SIZE (8)
	0x95, 0x3f,			// REPORT COUNT(63)
	0xB1, 0x02,			// FEATURE(DATA,VARIABLE,ABSOLUTE)
	0xC0,

    0x06, 0x04, 0xFF, 	// usage page(�Զ���)
	0x09, 0x01,			// usage(1)
	0xA1, 0x01,			// Collection(Application)
	0x85, REPORT_ID_KEY_MODE, // REPORT_ID (0x62)
	0x15, 0x00,			// Logical Minimum (0)
	0x26, 0xFF, 0x00,	// Logical Maximum (255)
	0x09, 0x00,
	0x75, 0x08,			// REPORT SIZE (8)
	0x95, 0x3f,			// REPORT COUNT(63)
	0xB1, 0x02,			// FEATURE(DATA,VARIABLE,ABSOLUTE)
	0xC0,

    0x06, 0x05, 0xFF, 	// usage page(�Զ���)
	0x09, 0x01,			// usage(1)
	0xA1, 0x01,			// Collection(Application)
	0x85, REPORT_ID_LIGHT_EFFECT, // REPORT_ID (0x63)
	0x15, 0x00,			// Logical Minimum (0)
	0x26, 0xFF, 0x00,	// Logical Maximum (255)
	0x09, 0x00,
	0x75, 0x08,			// REPORT SIZE (8)
	0x95, 0x3f,			// REPORT COUNT(63)
	0xB1, 0x02,			// FEATURE(DATA,VARIABLE,ABSOLUTE)
	0xC0,

    0x06,0x06,0xff,     // usage page(�Զ���)
    0x09,0x01,          // usage(1)
    0xa1,0x01,          // Collection(Application)
    0x85,REPORT_ID_MACRO,     // REPORT_ID (5)
    0x15,0x00,          // Logical Minimum (0)
    0x26,0xff,0x00,     // Logical Maximum (255)
    0x09,0x00,
    0x75,0x08,          // REPORT SIZE (8)
    0x95,0x3f,          // REPORT COUNT(63)
    0xb1,0x02,          // FEATURE(DATA,VARIABLE,ABSOLUTE)
    0xc0,

    0x06,0x01,0xff,     /* Usage page(vendor custom define) */
    0x09,0x01,          /* Consumer Control */
    0xa1,0x01,          /* Collection(Application) */
    0x85,REPORT_ID_PIC,/* REPORT ID 0x08 */
    0x15,0x00,          /* Logical Minimum(0x0) */
    0x26,0xff,0x00,     /* Logical Maximum(0xff) */
    0x09,0x20,
    0x95,0x3f,          /* Report Count(63) */
    0x75,0x08,          /* Report Size(0x08) */
    0x91,0x02,          /* Feature (Data) */
    0xc0,

    0x06, 0x07, 0xFF, 	// usage page(�Զ���)
	0x09, 0x01,			// usage(1)
	0xA1, 0x01,			// Collection(Application)
	0x85, REPORT_ID_DPI,		// REPORT_ID (6)
	0x15, 0x00,			// Logical Minimum (0)
	0x26, 0xFF, 0x00,	// Logical Maximum (255)
	0x09, 0x00,
	0x75, 0x08,			// REPORT SIZE (8)
	0x95, 0x02,			// REPORT COUNT(2)
	0x81, 0x02,			// Input (Data) => Modifier byte
	0xC0,               /* End Collection */
};

const uint32_t REPORT_MOUSE_SIZE = sizeof(g_apl_mouse_report)/sizeof(uint8_t ) ;
const uint32_t REPORT_KEYBOARD_SIZE = sizeof(g_apl_keyboard_report)/sizeof(uint8_t ) ;

/* Standard Device Descriptor */
const uint8_t g_apl_device[USB_DD_BLENGTH + ( USB_DD_BLENGTH % 2)] =
{
    USB_DD_BLENGTH,                                     /*  0:bLength */
    USB_DT_DEVICE,                                      /*  1:bDescriptorType */
    0x10,                                               /*  2:bcdUSB_lo */
    0x01,                                               /*  3:bcdUSB_hi */
    0x00,                                               /*  4:bDeviceClass */	
    0x00,                                               /*  5:bDeviceSubClass */	
    0x00,                                               /*  6:bDeviceProtocol */	
    0x40,                                               /*  7:bMAXPacketSize(for DCP) */
    USBD_VID & 0x00FF,                                  /*  8:idVendor_lo */
    (USBD_VID & 0xFF00) >> 8,                           /*  9:idVendor_hi */
    USBD_PID & 0x00FF,                                  /* 10:idProduct_lo */
    (USBD_PID & 0xFF00) >> 8,                           /* 11:idProduct_hi */
    0x00,                                               /* 12:bcdDevice_lo */
    0x00,                                               /* 13:bcdDevice_hi */
    1,                                                  /* 14:iManufacturer */
    2,                                                  /* 15:iProduct */
    3,                                                  /* 16:iSerialNumber */
    0x01                                                /* 17:bNumConfigurations */
};

/************************************************************
 *  Configuration Or Other_Speed_Configuration Descriptor   *
 ************************************************************/
/* For Full-Speed */
const uint8_t g_apl_configuration[USB_CONFIG_DESCRIPTOR_LEN + (USB_CONFIG_DESCRIPTOR_LEN % 2)] =
{
    USB_CD_BLENGTH,     /* bLength */
    USB_DT_CONFIGURATION,    /* bDescriptorType */
    /* wTotalLength */
    USB_CONFIG_DESCRIPTOR_LEN & 0x00FF,
    (USB_CONFIG_DESCRIPTOR_LEN & 0xFF00) >> 8,
    0x02,           /* bNumInterfaces */
    0x01,           /* bConfigurationValue */
    0x00,           /* iConfiguration */
    USB_CF_RESERVED | USB_CF_RWUPON,/* bmAttributes */
    0x32,         /* MaxPower */

    /* I/F descr: HID - Mouse */
    USB_ID_BLENGTH,   /* bLength */
    USB_DT_INTERFACE, /* bDescriptorType */
    0x00,           /* bInterfaceNumber */
    0x00,           /* bAlternateSetting */
    0x01,           /* bNumEndpoints */
    0x03,           /* bInterfaceClass */
    0x00,           /* bInterfaceSubClass */
    HID_MOUSE,      /* bInterfaceProtocol */
    0x00,           /* iInterface */

    /* HID Descriptor */
    0x09,        /* Size of this descriptor in UINT8s. */
    0x21,       /* HID descriptor type. */
    0x10, 0x01,     /* HID Class Spec. release number. */
    0x00,           /* H/W target country. */
    0x01,           /* Number of HID class descriptors to follow. */
    0x22,   /* Descriptor type. */
    /* Total length of report descriptor. */
    sizeof(g_apl_mouse_report) & 0x00FF,
    (sizeof(g_apl_mouse_report) & 0xFF00) >> 8,

    /* EP Descriptor: interrupt in. */
    USB_ED_BLENGTH,   /* bLength */
    USB_DT_ENDPOINT,  /* bDescriptorType */
    (uint8_t) (USB_EP_IN | USB_EP1), /* bEndpointAddress */
    USB_EP_INT,         /* bmAttributes */
    /* wMaxPacketSize */
    0x08,
    0x00,
    0x01,     /* bInterval */
    
	/* I/F descr: HID - keyboard */
    USB_ID_BLENGTH,   /* bLength */
    USB_DT_INTERFACE, /* bDescriptorType */
    0x01,           /* bInterfaceNumber */
    0x00,           /* bAlternateSetting */
    0x02,           /* bNumEndpoints */
    0x03,           /* bInterfaceClass */
    0x00,           /* bInterfaceSubClass */
    HID_KEYBOARD,      /* bInterfaceProtocol */
    0x00,           /* iInterface */

    /* HID Descriptor */
    0x09,        /* Size of this descriptor in UINT8s. */
    0x21,       /* HID descriptor type. */
    0x10, 0x01,     /* HID Class Spec. release number. */
    0x00,           /* H/W target country. */
    0x01,           /* Number of HID class descriptors to follow. */
    0x22,   /* Descriptor type. */
    /* Total length of report descriptor. */
    sizeof(g_apl_keyboard_report) & 0x00FF,
    (sizeof(g_apl_keyboard_report) & 0xFF00) >> 8,

    /* EP Descriptor: interrupt in. */
    USB_ED_BLENGTH,   /* bLength */
    USB_DT_ENDPOINT,  /* bDescriptorType */
    (uint8_t) (USB_EP_IN | USB_EP2), /* bEndpointAddress */
    USB_EP_INT,         /* bmAttributes */
    /* wMaxPacketSize */
    0x08,
    0x00,
    0x01,     /* bInterval */

    /* EP Descriptor: interrupt out. */
    USB_ED_BLENGTH,   /* bLength */
    USB_DT_ENDPOINT,  /* bDescriptorType */
    (uint8_t) (USB_EP_OUT | USB_EP3), /* bEndpointAddress */
    USB_EP_INT,         /* bmAttributes */
    /* wMaxPacketSize */
    0x40,
    0x00,
    0x01,     /* bInterval */
};


/*************************************
 *    String Descriptor              *
 *************************************/
/* UNICODE 0x0409 English (United States) */
const uint8_t g_apl_string_descriptor0[] =
{
    4,                          /*  0:bLength */
    USB_DT_STRING,              /*  1:bDescriptorType */
    0x09, 0x04                  /*  2:wLANGID[0] */
};

/* iManufacturer */
const uint8_t g_apl_string_descriptor1[] =
{
    20,                         /*  0:bLength */
    USB_DT_STRING,              /*  1:bDescriptorType */
    'C', 0x00,                  /*  2:wLANGID[0] */
    'M', 0x00,
    's', 0x00,
    'e', 0x00,
    'm', 0x00,
    'i', 0x00,
    'c', 0x00,
    'o', 0x00,
	'n', 0x00,
};

/* iProduct */
const uint8_t g_apl_string_descriptor2[] =
{
    24,                     /*  0:bLength */
    USB_DT_STRING,          /*  1:bDescriptorType */
    'U', 0x00,
    'S', 0x00,
    'B', 0x00,
    ' ', 0x00,
    'T', 0x00,
    'i', 0x00,
    'f', 0x00,
    'f', 0x00,
    'a', 0x00,
    'n', 0x00,
    'y', 0x00,
};

/* iInterface */
const uint8_t g_apl_string_descriptor3[] =
{
    36,                     /*  0:bLength */
    USB_DT_STRING,          /*  1:bDescriptorType */
    'C', 0x00,
    'o', 0x00,
    'm', 0x00,
    'p', 0x00,
    'o', 0x00,
    's', 0x00,
    'i', 0x00,
    't', 0x00,
    'e', 0x00,
    ' ', 0x00,
    'D', 0x00,
    'e', 0x00,
    'v', 0x00,
    'i', 0x00,
    'c', 0x00,
    'e', 0x00,
    's', 0x00
};

const uint8_t *gp_apl_string_table[] =
{
    g_apl_string_descriptor0,
    g_apl_string_descriptor1,
    g_apl_string_descriptor2,
    g_apl_string_descriptor3
};

