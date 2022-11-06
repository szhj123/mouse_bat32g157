/******************************************************************************
 Includes   <System Includes> , "Project Includes"
 ******************************************************************************/
//#include "r_usb_basic.h"
//#include "r_usb_basic_api.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "usb_phid_pmsc_apl.h"

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
#define USB_PCDC_PMSC_CD_LEN          (80U)
#define STRING_DESCRIPTOR0_LEN        (4U)
#define STRING_DESCRIPTOR1_LEN        (20U)
#define STRING_DESCRIPTOR2_LEN        (36U)
#define STRING_DESCRIPTOR3_LEN        (36U)
#define STRING_DESCRIPTOR4_LEN        (22U)
#define STRING_DESCRIPTOR5_LEN        (18U)
#define STRING_DESCRIPTOR6_LEN        (28U)
#define NUM_STRING_DESCRIPTOR         (7U)

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

/******************************************************************************
 Private global variables and functions
 ******************************************************************************/

/******************************************************************************
 Exported global variables
 ******************************************************************************/

/******************************************************************************
 Exported global functions (to be accessed by other files)
 ******************************************************************************/

/* Standard Device Descriptor */
uint8_t g_apl_device[USB_DD_BLENGTH + ( USB_DD_BLENGTH % 2)] =
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
uint8_t g_apl_configuration[USB_PCDC_PMSC_CD_LEN + (USB_PCDC_PMSC_CD_LEN % 2)] =
{
    USB_CD_BLENGTH,                 /*  0:bLength */
    USB_DT_CONFIGURATION,                /*  1:bDescriptorType */
    USB_PCDC_PMSC_CD_LEN % USB_W_TOTAL_LENGTH_MASK, /*  2:wTotalLength(L) */
    USB_PCDC_PMSC_CD_LEN / USB_W_TOTAL_LENGTH_MASK, /*  3:wTotalLength(H) */
    2,                              /*  4:bNumInterfaces */
    1,                              /*  5:bConfigurationValue */
    0,                              /*  6:iConfiguration */
    USB_CF_RESERVED | USB_CF_SELFP, /*  7:bmAttributes */
    0x32,                       /*  8:MAXPower (100mA unit) */
	
/* Mass Storage Class */

    /* Interface Association Descriptor (IAD) */
    0x08,                           /*  0:bLength */
    USB_IAD_TYPE,                  /*  1:bDescriptorType */
    0x00,                           /*  2:bFirstInterface */
    0x01,                           /*  3:bInterfaceCount */
    USB_IFCLS_MAS,                  /*  4:bFunctionClass  */
    USB_INTERFACE_SUBCLASS, 							/* 5:bFunctionSubClass */
    USB_BOTP,                           /*  6:bFunctionProtocol */
    0x00,                           /*  7:iFunction */

    /* Interface Descriptor */
    USB_ID_BLENGTH,                       /*  0:bLength */
    USB_DT_INTERFACE,                     /*  1:bDescriptor */
    0,                                    /*  2:bInterfaceNumber */
    0,                                    /*  3:bAlternateSetting */
    2,                                    /*  4:bNumEndpoints */
    USB_IFCLS_MAS,                        /*  5:bInterfaceClass */
    USB_INTERFACE_SUBCLASS,               /*  6:bInterfaceSubClass */
    USB_BOTP,                             /*  7:bInterfaceProtocol */
    4,                                    /*  8:iInterface */

    /* Endpoint Descriptor 0 */
    USB_ED_BLENGTH,                       /*  0:bLength */
    USB_DT_ENDPOINT,                      /*  1:bDescriptorType */
    USB_EP_IN | USB_EP4,                  /*  2:bEndpointAddress */
    USB_EP_BULK,                          /*  3:bmAttribute */
    USB_VALUE_64,                         /*  4:wMAXPacketSize_lo */
    0,                                    /*  5:wMAXPacketSize_hi */
    0,                                    /*  6:bInterval */

    /* Endpoint Descriptor 1 */
    USB_ED_BLENGTH,                       /*  0:bLength */
    USB_DT_ENDPOINT,                      /*  1:bDescriptorType */
    USB_EP_OUT | USB_EP5,                 /*  2:bEndpointAddress */
    USB_EP_BULK,                          /*  3:bmAttribute */
    USB_VALUE_64,                         /*  4:wMAXPacketSize_lo */
    0,                                    /*  5:wMAXPacketSize_hi */
    1,                                    /*  6:bInterval */

/* Communication Device Class */

    /* Interface Association Descriptor (IAD) */
    0x08,                           /*  0:bLength */
    USB_IAD_TYPE,                  /*  1:bDescriptorType */	
    0x01,                           /*  2:bFirstInterface */
    0x01,                           /*  3:bInterfaceCount */
    USB_IFCLS_HID,                  /*  4:bFunctionClass  */
    USB_IFSUB_NOBOOT, 							/* 5:bFunctionSubClass */
    0x00,                           /*  6:bFunctionProtocol */
    0x00,                           /*  7:iFunction */

    /* Interface Descriptor */
    USB_ID_BLENGTH,                 /*  0:bLength */
    USB_DT_INTERFACE,               /*  1:bDescriptor */
    1,                              /*  2:bInterfaceNumber */
    0,                              /*  3:bAlternateSetting */
    2,                              /*  4:bNumEndpoints */
    USB_IFCLS_HID,                  /*  5:bInterfaceClass */
    USB_IFSUB_NOBOOT,  						  /*  6:bInterfaceSubClass */
    0,                              /*  7:bInterfaceProtocol */
    0,                              /*  8:iInterface */

			/* HID Descriptor */
			9,                                                          /*  0:bLength */
			USB_DT_TYPE_HIDDESCRIPTOR,                                  /*  1:bDescriptor */
			0x00,                                                       /*  2:HID Ver */	//11
			0x01,                                                       /*  3:HID Ver */
			0x00,                                                       /*  4:bCountryCode */
			0x01,                                                       /*  5:bNumDescriptors */
			0x22,                                                       /*  6:bDescriptorType */
			ITEM_LEN,                                                   /*  7:wItemLength(L) */
			0x00,                                                       /*  8:wItemLength(H) */

				/* Endpoint Descriptor 0 */
				USB_ED_BLENGTH,                                             /*  0:bLength */
				USB_DT_ENDPOINT,                                            /*  1:bDescriptorType */
				(uint8_t) (USB_EP_IN | USB_EP1),                            /*  2:bEndpointAddress */
				USB_EP_INT,                                                 /*  3:bmAttribute */
				MXPS,                                                       /*  4:wMaxPacketSize_lo */
				0,                                                          /*  5:wMaxPacketSize_hi */
				0x0A,                                                       /*  6:bInterval */
				#if OPERATION_MODE == USB_ECHO
				/* Endpoint Descriptor 1 */
				USB_ED_BLENGTH,                                             /*  0:bLength */
				USB_DT_ENDPOINT,                                            /*  1:bDescriptorType */
				(uint8_t) (USB_EP_OUT | USB_EP2),                           /*  2:bEndpointAddress */
				USB_EP_INT,                                                 /*  3:bmAttribute */
				MXPS,                                                       /*  4:wMaxPacketSize_lo */
				0,                                                          /*  5:wMaxPacketSize_hi */
				0x0A,                                                       /*  6:bInterval */
				#endif  /* OPERATION_MODE == USB_ECHO */
};


/*************************************
 *    String Descriptor              *
 *************************************/
/* UNICODE 0x0409 English (United States) */
uint8_t g_apl_string_descriptor0[STRING_DESCRIPTOR0_LEN + ( STRING_DESCRIPTOR0_LEN % 2)] =
{
    STRING_DESCRIPTOR0_LEN,     /*  0:bLength */
    USB_DT_STRING,              /*  1:bDescriptorType */
    0x09, 0x04                  /*  2:wLANGID[0] */
};

/* iManufacturer */
uint8_t g_apl_string_descriptor1[STRING_DESCRIPTOR1_LEN + ( STRING_DESCRIPTOR1_LEN % 2)] =
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
uint8_t g_apl_string_descriptor2[STRING_DESCRIPTOR2_LEN + ( STRING_DESCRIPTOR2_LEN % 2)] =
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
uint8_t g_apl_string_descriptor3[STRING_DESCRIPTOR3_LEN + ( STRING_DESCRIPTOR3_LEN % 2)] =
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
uint8_t g_apl_string_descriptor4[STRING_DESCRIPTOR4_LEN + ( STRING_DESCRIPTOR4_LEN % 2)] =
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
uint8_t g_apl_string_descriptor5[STRING_DESCRIPTOR5_LEN + ( STRING_DESCRIPTOR5_LEN % 2)] =
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
uint8_t g_apl_string_descriptor6[STRING_DESCRIPTOR6_LEN + ( STRING_DESCRIPTOR6_LEN % 2)] =
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

uint8_t *gp_apl_string_table[] =
{
    g_apl_string_descriptor0,
    g_apl_string_descriptor1,
    g_apl_string_descriptor2,
    g_apl_string_descriptor3,
    g_apl_string_descriptor4,
    g_apl_string_descriptor5,
    g_apl_string_descriptor6
};

const usb_descriptor_t g_usb_descriptor =
{
    g_apl_device,                   /* Pointer to the device descriptor */
    g_apl_configuration,            /* Pointer to the configuration descriptor for Full-speed */
    gp_apl_string_table,             /* Pointer to the string descriptor table */
    NUM_STRING_DESCRIPTOR
};

#if OPERATION_MODE == USB_ECHO
/************************************************************
 *  HID Report Discriptor for Echo mode                     *
 ************************************************************/
const uint8_t g_apl_report[] =
{
    0x06, 0xA0, 0xFF,                               /* Usage Page - Vendor defined*/
    0x09, 0x00,                                     /* Usage ID within this page (Vendor defined)*/
    0xA1, 0x01,                                     /* Collection App (Windows requires an Application Collection) */

    /* *** The INPUT REPORT *** */
    0x09, 0x00,                                     /* Usage ID within this page*/
    0x15, 0x00,                                     /* Logical Min 0 */
    0x26, 0xFF, 0x00,                               /* Logical Max 255 */
    0x75, 0x08,                                     /* Size 8 Bits (Each Field will be 8bits) */
    0x95, 0x40,                                     /* Count(Number of fields(bytes) in INPUT report) */
    0x81, 0x02,                                     /* Input Report - type variable data */

    /* *** The OUTPUR REPORT *** */
    0x09, 0x00,                                     /* Usage ID within this page (Vendor defined)*/
    0x15, 0x00,                                     /* Logical Min 0 */
    0x26, 0xFF, 0x00,                               /* Logical Max 255 */
    0x75, 0x08,                                     /* Size 8 Bits (Each Field will be 8bits) */
    0x95, 0x40,                                     /* Count(Number of fields(bytes) in OUTPUT report)*/
    0x91, 0x02,                                     /* Output Report - type variable data */
    0xC0,                                           /* End collection */
};

#else /* OPERATION_MODE == USB_ECHO */
/************************************************************
 *  HID Report Discriptor for Keyboard                      *
 ************************************************************/
const uint8_t g_apl_report[] =
{
    0x05, 0x01,                                     /* Usage Page (Generic Desktop) */
    0x09, 0x06,                                     /* Usage (Keyboard) */
    0xA1, 0x01,                                     /* Collection (Application) */
    0x05, 0x07,                                     /* Usage Page (Key Codes); */
    0x19, 0xE0,                                     /* Usage Minimum (224) */
    0x29, 0xE7,                                     /* Usage Maximum (231) */
    0x15, 0x00,                                     /* Logical Minimum (0) */
    0x25, 0x01,                                     /* Logical Maximum (1) */
    0x75, 0x01,                                     /* Report Size (1) */
    0x95, 0x08,                                     /* Report Count (8) */
    0x81, 0x02,                                     /* Input (Data , Variable , Absolute)  ;Modifier byte */
    0x95, 0x01,                                     /* Report Count (1) */
    0x75, 0x08,                                     /* Report Size (8) */
    0x81, 0x01,                                     /* Input (Constant) ;Reserved byte */
    0x95, 0x05,                                     /* Report Count (5) */
    0x75, 0x01,                                     /* Report Size (1) */
    0x05, 0x08,                                     /* Usage Page (Page# for LEDs) */
    0x19, 0x01,                                     /* Usage Minimum (1) */
    0x29, 0x05,                                     /* Usage Maximum (5) */
    0x91, 0x02,                                     /* Output (Data , Variable , Absolute)  ;LED report */
    0x95, 0x01,                                     /* Report Count (1) */
    0x75, 0x03,                                     /* Report Size (3) */
    0x91, 0x01,                                     /* Output (Constant) ;LED report padding */
    0x95, 0x06,                                     /* Report Count (6) */
    0x75, 0x08,                                     /* Report Size (8) */
    0x15, 0x00,                                     /* Logical Minimum (0) */
    0x25, 0x65,                                     /* Logical Maximum(101) */
    0x05, 0x07,                                     /* Usage Page (Key Codes) */
    0x19, 0x00,                                     /* Usage Minimum (0) */
    0x29, 0x65,                                     /* Usage Maximum (101) */
    0x81, 0x00,                                     /* Input (Data , Array)  ;Key arrays (6 bytes) */

    /* *** The OUTPUR REPORT *** */
    0x09, 0x00,                                     /* Usage ID within this page (Vendor defined)*/
    0x15, 0x00,                                     /* Logical Min 0 */
    0x26, 0xFF, 0x00,                               /* Logical Max 255 */
    0x75, 0x08,                                     /* Size 8 Bits (Each Field will be 8bits) */
    0x95, 0x01,                                     /* Count (Number of fields(bytes) in OUTPUT report) */
    0x91, 0x02,                                     /* Output Report - type variable data */
    0xC0,                                           /* End Collection */
};
#endif  /* OPERATION_MODE == USB_ECHO */

/******************************************************************************
 End  Of File
 ******************************************************************************/