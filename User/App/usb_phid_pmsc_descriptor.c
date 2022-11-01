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
/* bcdUSB */
#define USB_BCDNUM                      (0x0200U)
/* Release Number */
#define USB_RELEASE                     (0x0200U)
/* DCP max packet size */
#define USB_DCPMAXP                     (64U)
/* Configuration number */
#define USB_CONFIGNUM                   (1U)
/* Vendor ID */
#define USB_VENDORID                    (0x464DU)
/* Product ID */
#define USB_PRODUCTID                   (0x0402U)

/* Miscellaneous Device Class */
#define USB_MISC_CLASS                  (0xEF)
/* Common Class */
#define USB_COMMON_CLASS                (0x02)
/* Interface Association Descriptor */
#define USB_IAD_DESC                    (0x01)
/* Interface Association Descriptor Type */
#define USB_IAD_TYPE                    (0x0B)

/* Class-Specific Configuration Descriptors */
#define     USB_PCDC_CS_INTERFACE                               (0x24U)

/* bDescriptor SubType in Communications Class Functional Descriptors */
/* Header Functional Descriptor */
#define     USB_PCDC_DT_SUBTYPE_HEADER_FUNC                     (0x00U)
/* Call Management Functional Descriptor. */
#define     USB_PCDC_DT_SUBTYPE_CALL_MANAGE_FUNC                (0x01U)
/* Abstract Control Management Functional Descriptor. */
#define     USB_PCDC_DT_SUBTYPE_ABSTRACT_CTR_MANAGE_FUNC        (0x02U)
/* Union Functional Descriptor */
#define     USB_PCDC_DT_SUBTYPE_UNION_FUNC                      (0x06U)

/* Communications Class Subclass Codes */
#define     USB_PCDC_CLASS_SUBCLASS_CODE_ABS_CTR_MDL            (0x02U)

/* USB Class Definitions for Communications Devices Specification
 release number in binary-coded decimal. */
#define     USB_PCDC_BCD_CDC          (0x0110U)

/* Descriptor length */
#define USB_DQD_LEN                   (10U)
//#define USB_DD_BLENGTH                (18U)
#define STRING_DESCRIPTOR0_LEN        (4U)
#define STRING_DESCRIPTOR1_LEN        (20U)
#define STRING_DESCRIPTOR2_LEN        (36U)
#define STRING_DESCRIPTOR3_LEN        (36U)
#define STRING_DESCRIPTOR4_LEN        (22U)
#define STRING_DESCRIPTOR5_LEN        (18U)
#define STRING_DESCRIPTOR6_LEN        (28U)

/* Descriptor data Mask */
#define USB_UCHAR_MAX                 (0xffU)
#define USB_W_TOTAL_LENGTH_MASK       (256U)
#define USB_W_MAX_PACKET_SIZE_MASK    (64U)
#define USB_PCDC_BCD_CDC_MASK         (256U)

/* Sub_class code */
#define USB_ATAPI                 ((uint8_t) 0x05U)
#define USB_SCSI                  ((uint8_t) 0x06U)

/* ----- Subclass Codes ----- */
#define USB_IFSUB_NOBOOT                ((uint8_t)0x00)   /* No Subclass */
#define USB_IFSUB_BOOT                  ((uint8_t)0x01)   /* Boot Interface Subclass */

/* Protocol code */
#define USB_BOTP                  ((uint8_t) 0x50U)
#define USB_TOTALEP               ((uint8_t) 0x02U)

/* Select SubClass */

//#define USB_INTERFACE_SUBCLASS  (USB_SCSI)
#define USB_INTERFACE_SUBCLASS    (USB_ATAPI)

#define USB_VALUE_64              (64)

#if OPERATION_MODE == USB_ECHO
    #define USB_IFPROTOCOL      (USB_IFPRO_NONE)
    #define ITEM_LEN            (34)	//client 21
    #define MXPS                (64)
    #define NUM_EP              (2)
#else   /* OPERATION_MODE == USB_ECHO */
    #define USB_IFPROTOCOL      (USB_IFPRO_KBD)
    #define ITEM_LEN            (76)
    #define MXPS                (8)
    #define NUM_EP              (1)
#endif

#define HID_KEYBOARD            (0x01)
#define HID_MOUSE               (0x02)

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
	0x85, RID_MOUSE,    // Report ID

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
    0x85,RID_KEYBOARD,  /* REPORT ID 0x02 */
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
    0x85,RID_CONSUMER,  /* REPORT ID 0x03 */
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
	0x85, RID_KEY_REUSE,// REPORT_ID (0x60)
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
	0x85, RID_LDR,      // REPORT_ID (0x61)
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
	0x85, RID_KEY_MODE, // REPORT_ID (0x62)
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
	0x85, RID_LGT_EFECT, // REPORT_ID (0x63)
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
    0x85,RID_MACRO,     // REPORT_ID (5)
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
    0x85,RPT_PIC,/* REPORT ID 0x08 */
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
	0x85, RID_DPI,		// REPORT_ID (6)
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
    (USB_BCDNUM & (uint8_t) USB_UCHAR_MAX),                     /*  2:bcdUSB_lo */
    ((uint8_t) (USB_BCDNUM >> 8) & (uint8_t) USB_UCHAR_MAX),    /*  3:bcdUSB_hi */
    0x00,                                     /*  4:bDeviceClass */	//USB_MISC_CLASS
    0x00,                                   /*  5:bDeviceSubClass */	//USB_COMMON_CLASS
    0x00,                                       /*  6:bDeviceProtocol */	//USB_IAD_DESC
    (uint8_t) USB_DCPMAXP,                              /*  7:bMAXPacketSize(for DCP) */
    (USB_VENDORID & (uint8_t) USB_UCHAR_MAX),                   /*  8:idVendor_lo */
    ((uint8_t) (USB_VENDORID >> 8) & (uint8_t) USB_UCHAR_MAX),  /*  9:idVendor_hi */
    ((uint16_t) USB_PRODUCTID & (uint8_t) USB_UCHAR_MAX),       /* 10:idProduct_lo */
    ((uint8_t) (USB_PRODUCTID >> 8) & (uint8_t) USB_UCHAR_MAX), /* 11:idProduct_hi */
    (USB_RELEASE & (uint8_t) USB_UCHAR_MAX),                    /* 12:bcdDevice_lo */
    ((uint8_t) (USB_RELEASE >> 8) & (uint8_t) USB_UCHAR_MAX),   /* 13:bcdDevice_hi */
    1,                                                  /* 14:iManufacturer */
    3,                                                  /* 15:iProduct */
    6,                                                  /* 16:iSerialNumber */
    USB_CONFIGNUM /* 17:bNumConfigurations */
};

/************************************************************
 *  Configuration Or Other_Speed_Configuration Descriptor   *
 ************************************************************/
/* For Full-Speed */
#define USB_PCDC_PMSC_CD_LEN                (USB_CD_BLENGTH + USB_ID_BLENGTH*4 + USB_ED_BLENGTH*3)

const uint8_t g_apl_configuration[USB_PCDC_PMSC_CD_LEN + (USB_PCDC_PMSC_CD_LEN % 2)] =
{
    USB_CD_BLENGTH,     /* bLength */
    USB_DT_CONFIGURATION,    /* bDescriptorType */
    /* wTotalLength */
    USB_PCDC_PMSC_CD_LEN & 0x00FF,
    (USB_PCDC_PMSC_CD_LEN & 0xFF00) >> 8,
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
const uint8_t g_apl_string_descriptor0[STRING_DESCRIPTOR0_LEN + ( STRING_DESCRIPTOR0_LEN % 2)] =
{
    STRING_DESCRIPTOR0_LEN,     /*  0:bLength */
    USB_DT_STRING,              /*  1:bDescriptorType */
    0x09, 0x04                  /*  2:wLANGID[0] */
};

/* iManufacturer */
const uint8_t g_apl_string_descriptor1[STRING_DESCRIPTOR1_LEN + ( STRING_DESCRIPTOR1_LEN % 2)] =
{
    STRING_DESCRIPTOR1_LEN,     /*  0:bLength */
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
const uint8_t g_apl_string_descriptor2[STRING_DESCRIPTOR2_LEN + ( STRING_DESCRIPTOR2_LEN % 2)] =
{
    STRING_DESCRIPTOR2_LEN, /*  0:bLength */
    USB_DT_STRING,          /*  1:bDescriptorType */
    'U', 0x00,
    'S', 0x00,
    'B', 0x00,
    ' ', 0x00,
    'D', 0x00,
    'e', 0x00,
    'm', 0x00,
    'o', 0x00,
    'n', 0x00,
    's', 0x00,
    't', 0x00,
    'r', 0x00,
    'a', 0x00,
    't', 0x00,
    'i', 0x00,
    'o', 0x00,
    'n', 0x00,
};

/* iInterface */
const uint8_t g_apl_string_descriptor3[STRING_DESCRIPTOR3_LEN + ( STRING_DESCRIPTOR3_LEN % 2)] =
{
    STRING_DESCRIPTOR3_LEN, /*  0:bLength */
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

/* iConfiguration */
const uint8_t g_apl_string_descriptor4[STRING_DESCRIPTOR4_LEN + ( STRING_DESCRIPTOR4_LEN % 2)] =
{
    STRING_DESCRIPTOR4_LEN, /*  0:bLength */
    USB_DT_STRING,          /*  1:bDescriptorType */
    'F', 0x00,              /*  2:wLANGID[0] */
    'u', 0x00,
    'l', 0x00,
    'l', 0x00,
    '-', 0x00,
    'S', 0x00,
    'p', 0x00,
    'e', 0x00,
    'e', 0x00,
    'd', 0x00
};

/* iConfiguration */
const uint8_t g_apl_string_descriptor5[STRING_DESCRIPTOR5_LEN + ( STRING_DESCRIPTOR5_LEN % 2)] =
{
    STRING_DESCRIPTOR5_LEN, /*  0:bLength */
    USB_DT_STRING,          /*  1:bDescriptorType */
    'H', 0x00,              /*  2:wLANGID[0] */
    'i', 0x00,
    '-', 0x00,
    'S', 0x00,
    'p', 0x00,
    'e', 0x00,
    'e', 0x00,
    'd', 0x00
};

/* iSerialNumber */
const uint8_t g_apl_string_descriptor6[STRING_DESCRIPTOR6_LEN + ( STRING_DESCRIPTOR6_LEN % 2)] =
{
    STRING_DESCRIPTOR6_LEN, /*  0:bLength */
    USB_DT_STRING,          /*  1:bDescriptorType */
    '0', 0x00,              /*  2:wLANGID[0] */
    '0', 0x00,
    '0', 0x00,
    '0', 0x00,
    '0', 0x00,
    '0', 0x00,
    '0', 0x00,
    '0', 0x00,
    '0', 0x00,
    '0', 0x00,
    '0', 0x00,
    '0', 0x00,
    '1', 0x00,
};

const uint8_t *gp_apl_string_table[] =
{
    g_apl_string_descriptor0,
    g_apl_string_descriptor1,
    g_apl_string_descriptor2,
    g_apl_string_descriptor3,
    g_apl_string_descriptor4,
    g_apl_string_descriptor5,
    g_apl_string_descriptor6
};

