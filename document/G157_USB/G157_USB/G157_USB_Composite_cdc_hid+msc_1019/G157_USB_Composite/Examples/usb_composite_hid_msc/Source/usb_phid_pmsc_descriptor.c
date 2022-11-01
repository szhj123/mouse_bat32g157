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
 const uint8_t g_apl_mouse_report[] =
{
    0x05, 0x01,         /* Usage Page(Generic Desktop Controls) */
    0x09, 0x02,         /* Usage(Mouse) */
    0xA1, 0x01,         /* Collection(Application) */
    0x09, 0x01,         /* Usage(Pointer) */
    0xA1, 0x00,         /* Collection(Physical) */
    0x05, 0x09,         /* Usage Page(Button) */
    0x19, 0x01,         /* Usage Minimum(0x1) */
    0x29, 0x03,         /* Usage Maximum(0x3) */
    0x15, 0x00,         /* Logical Minimum(0x0) */
    0x25, 0x01,         /* Logical Maximum(0x1) */
    0x75, 0x01,         /* Report Size(0x1) */
    0x95, 0x03,         /* Report Count(0x3) */
    0x81, 0x02,         /* Input(3 button bit) */
    0x75, 0x05,         /* Report Size(0x5) */
    0x95, 0x01,         /* Report Count(0x1) */
    0x81, 0x01,         /* Input(5 bit padding) */
    0x05, 0x01,         /* Usage Page(Generic Desktop Controls) */
    0x09, 0x30,         /* Usage(X) */
    0x09, 0x31,         /* Usage(Y) */
    0x09, 0x38,         /* Usage(Wheel) */
    0x15, 0x81,         /* Logical Minimum(0x81)(-127) */
    0x25, 0x7F,         /* Logical Maximum(0x7F)(127) */
    0x75, 0x08,         /* Report Size(0x8) */
    0x95, 0x03,         /* Report Count(0x3) */
    0x81, 0x06,         /* Input(1 byte wheel) */
    0xC0,               /* End Collection */
    0xC0                /* End Collection */
};

const uint8_t g_apl_keyboard_report[] =
{
    0x05, 0x01,         /* Usage Page(Generic Desktop Controls) */
    0x09, 0x06,         /* Usage(Keyboard) */
    0xA1, 0x01,         /* Collection(Application) */
    0x05, 0x07,         /* Usage Page(Keyboard/Keypad) */
    0x19, 0xE0,         /* Usage Minimum(0xE0) */
    0x29, 0xE7,         /* Usage Maximum(0xE7) */
    0x15, 0x00,         /* Logical Minimum(0x0) */
    0x25, 0x01,         /* Logical Maximum(0x1) */
    0x75, 0x01,         /* Report Size(0x1) */
    0x95, 0x08,         /* Report Count(0x8) */
    0x81, 0x02,         /* Input (Data) => Modifier byte */
    0x95, 0x01,         /* Report Count(0x1) */
    0x75, 0x08,         /* Report Size(0x8) */
    0x81, 0x01,         /* Input (Constant) => Reserved byte */
    0x95, 0x05,         /* Report Count(0x5) */
    0x75, 0x01,         /* Report Size(0x1) */
    0x05, 0x08,         /* Usage Page(LEDs) */
    0x19, 0x01,         /* Usage Minimum(0x1) */
    0x29, 0x05,         /* Usage Maximum(0x5) */
    0x91, 0x02,         /* Output (Data) => LED report */
    0x95, 0x01,         /* Report Count(0x1) */
    0x75, 0x03,         /* Report Size(0x3) */
    0x91, 0x01,         /* Output (Constant) => LED report padding */
    0x95, 0x06,         /* Report Count(0x6) */
    0x75, 0x08,         /* Report Size(0x8) */
    0x15, 0x00,         /* Logical Minimum(0x0) */
    0x26, 0x65, 0x00,         /* Logical Maximum(0x65) */
    0x05, 0x07,         /* Usage Page(Keyboard/Keypad) */
    0x19, 0x00,         /* Usage Minimum(0x0) */
    0x29, 0x65,         /* Usage Maximum(0x65) */
    0x81, 0x00,         /* Input (Data) */
    0xC0,                /* End Collection */
};

uint32_t REPORT_MOUSE_SIZE = sizeof(g_apl_mouse_report);
uint32_t REPORT_KEYBOARD_SIZE = sizeof(g_apl_keyboard_report);

/* Standard Device Descriptor */
uint8_t g_apl_device[USB_DD_BLENGTH + ( USB_DD_BLENGTH % 2)] =
{
     USB_DD_BLENGTH,                                             /*  0:bLength */
    USB_DT_DEVICE,                                              /*  1:bDescriptorType */
    (uint8_t) ( USB_BCDNUM & (uint8_t) 0xff),                   /*  2:bcdUSB_lo */
    (uint8_t) ((uint8_t) (USB_BCDNUM >> 8) & (uint8_t) 0xff),   /*  3:bcdUSB_hi */
    0x00,                                                       /*  4:bDeviceClass */
    0x00,                                                       /*  5:bDeviceSubClass */
    0x00,                                                       /*  6:bDeviceProtocol */
    (uint8_t) USB_DCPMAXP,                                      /*  7:bMAXPacketSize(for DCP) */
    (uint8_t) (USB_VENDORID & (uint8_t) 0xff),                  /*  8:idVendor_lo */
    (uint8_t) ((uint8_t) (USB_VENDORID >> 8) & (uint8_t) 0xff), /*  9:idVendor_hi */
    (uint8_t) (USB_PRODUCTID & (uint8_t) 0xff),                 /* 10:idProduct_lo */
    (uint8_t) ((uint8_t) (USB_PRODUCTID >> 8) & (uint8_t) 0xff),/* 11:idProduct_hi */
    (uint8_t) (USB_RELEASE & (uint8_t) 0xff),                   /* 12:bcdDevice_lo */
    (uint8_t) ((uint8_t) (USB_RELEASE >> 8) & (uint8_t) 0xff),  /* 13:bcdDevice_hi */
    1,                                                          /* 14:iManufacturer */
    2,                                                          /* 15:iProduct */
    3,                                                          /* 16:iSerialNumber */
    USB_CONFIGNUM,                                              /* 17:bNumConfigurations */
};

/************************************************************
 *  Configuration Or Other_Speed_Configuration Descriptor   *
 ************************************************************/
/* For Full-Speed */
#define     CD_LEN      (USB_CD_BLENGTH + USB_ID_BLENGTH*4 + USB_ED_BLENGTH*2) 

const uint8_t g_apl_configuration[CD_LEN + (CD_LEN % 2)] =
{
    USB_CD_BLENGTH,                                             /*  0:bLength */
    USB_DT_CONFIGURATION,                                       /*  1:bDescriptorType */
    (uint8_t) (CD_LEN % 256),                                   /*  2:wTotalLength(L) */
    (uint8_t) (CD_LEN / 256),                                   /*  3:wTotalLength(H) */
    2,                                                          /*  4:bNumInterfaces */
    1,                                                          /*  5:bConfigurationValue */
    0,                                                          /*  6:iConfiguration */
    /* Support RemoteWakeUp */
    (uint8_t) (USB_CF_RESERVED | USB_CF_SELFP | USB_CF_RWUPON), /*  7:bmAttributes */
    (uint8_t) (100 / 2),                                        /*  8:bMaxPower (2mA unit) */

    /* Interface Descriptor */
    USB_ID_BLENGTH,                                             /*  0:bLength */
    USB_DT_INTERFACE,                                           /*  1:bDescriptor */
    0,                                                          /*  2:bInterfaceNumber */
    0,                                                          /*  3:bAlternateSetting */
    1,                                                          /*  4:bNumEndpoints */
    USB_IFCLS_HID,                                              /*  5:bInterfaceClass(HID) */
    USB_IFSUB_NOBOOT,                                           /*  6:bInterfaceSubClass(NonBOOT) */
    0x02,                                                       /*  7:bInterfaceProtocol */
    0,                                                          /*  8:iInterface */

    /* HID Descriptor */
    9,                                                          /*  0:bLength */
    USB_DT_TYPE_HIDDESCRIPTOR,                                  /*  1:bDescriptor */
    0x10,                                                       /*  2:HID Ver */
    0x01,                                                       /*  3:HID Ver */
    0x00,                                                       /*  4:bCountryCode */
    0x01,                                                       /*  5:bNumDescriptors */
    0x22,                                                       /*  6:bDescriptorType */
    sizeof(g_apl_mouse_report) & 0x00FF,                                                         /*  7:wItemLength(L) */
    (sizeof(g_apl_mouse_report) & 0xFF00) >> 8,                                                       /*  8:wItemLength(H) */

    /* Endpoint Descriptor 0 */
    USB_ED_BLENGTH,                                             /*  0:bLength */
    USB_DT_ENDPOINT,                                            /*  1:bDescriptorType */
    (uint8_t) (USB_EP_IN | USB_EP1),                            /*  2:bEndpointAddress */
    USB_EP_INT,                                                 /*  3:bmAttribute */
    8,                                                       /*  4:wMaxPacketSize_lo */
    0,                                                          /*  5:wMaxPacketSize_hi */
    0x01,                                                       /*  6:bInterval */

    /* Interface Descriptor */
    USB_ID_BLENGTH,                                             /*  0:bLength */
    USB_DT_INTERFACE,                                           /*  1:bDescriptor */
    1,                                                          /*  2:bInterfaceNumber */
    0,                                                          /*  3:bAlternateSetting */
    1,                                                          /*  4:bNumEndpoints */
    USB_IFCLS_HID,                                              /*  5:bInterfaceClass(HID) */
    USB_IFSUB_NOBOOT,                                           /*  6:bInterfaceSubClass(NonBOOT) */
    0x01,                                                       /*  7:bInterfaceProtocol */
    0,                                                          /*  8:iInterface */

    /* HID Descriptor */
    9,                                                          /*  0:bLength */
    USB_DT_TYPE_HIDDESCRIPTOR,                                  /*  1:bDescriptor */
    0x10,                                                       /*  2:HID Ver */
    0x01,                                                       /*  3:HID Ver */
    0x00,                                                       /*  4:bCountryCode */
    0x01,                                                       /*  5:bNumDescriptors */
    0x22,                                                       /*  6:bDescriptorType */
    sizeof(g_apl_keyboard_report) & 0x00FF,                                                         /*  7:wItemLength(L) */
    (sizeof(g_apl_keyboard_report) & 0xFF00) >> 8,                                                       /*  8:wItemLength(H) */

    /* Endpoint Descriptor 0 */
    USB_ED_BLENGTH,                                             /*  0:bLength */
    USB_DT_ENDPOINT,                                            /*  1:bDescriptorType */
    (uint8_t) (USB_EP_IN | USB_EP2),                            /*  2:bEndpointAddress */
    USB_EP_INT,                                                 /*  3:bmAttribute */
    8,                                                       /*  4:wMaxPacketSize_lo */
    0,                                                          /*  5:wMaxPacketSize_hi */
    0x01,                                                       /*  6:bInterval */
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