/******************************************************************************
 * File Name    : usb_phid_descriptor.c
 * Description  : USB HID application code
 ******************************************************************************/

/******************************************************************************
 Includes   <System Includes> , "Project Includes"
 ******************************************************************************/
#include "usb_basic_mini_if.h"
#include "usb_phid_apl.h"
#include "usb_phid_apl_config.h"

/******************************************************************************
 Macro definitions
 ******************************************************************************/
#define USB_BCDNUM          (0x0200u)           /* bcdUSB */
#define USB_RELEASE         (0x0200u)           /* Release Number */
#define USB_CONFIGNUM       (1u)                /* Configuration number */
#define USB_DCPMAXP         (8u)               /* DCP max packet size */

/* [Vendor ID & Product ID setting] */
#define USB_VENDORID        (0xFF01)
#define USB_PRODUCTID       (0x0001)


#define USB_IFPROTOCOL      (USB_IFPRO_NONE)
#define ITEM_LEN            (27)
#define MXPS                (8)
#define NUM_EP              (2)


/************************************************************
 *  Device Descriptor                                       *
 ************************************************************/
__align(4) const uint8_t g_apl_device[] =
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
 *  Configuration Descriptor                                *
 ************************************************************/

#define     CD_LEN      (18+9+7+7)    /* Configuration Descriptor Length */

__align(4) const uint8_t g_apl_configuration[CD_LEN + (CD_LEN % 2)] =
{
    USB_CD_BLENGTH,                                             /*  0:bLength */
    USB_DT_CONFIGURATION,                                       /*  1:bDescriptorType */
    (uint8_t) (CD_LEN % 256),                                   /*  2:wTotalLength(L) */
    (uint8_t) (CD_LEN / 256),                                   /*  3:wTotalLength(H) */
    1,                                                          /*  4:bNumInterfaces */
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
    NUM_EP,                                                     /*  4:bNumEndpoints */
    USB_IFCLS_HID,                                              /*  5:bInterfaceClass(HID) */
    USB_IFSUB_NOBOOT,                                           /*  6:bInterfaceSubClass(NonBOOT) */
    USB_IFPROTOCOL,                                             /*  7:bInterfaceProtocol */
    0,                                                          /*  8:iInterface */

    /* HID Descriptor */
    9,                                                          /*  0:bLength */
    USB_DT_TYPE_HIDDESCRIPTOR,                                  /*  1:bDescriptor */
    0x10,                                                       /*  2:HID Ver */
    0x01,                                                       /*  3:HID Ver */
    0x00,                                                       /*  4:bCountryCode */
    0x01,                                                       /*  5:bNumDescriptors */
    0x22,                                                       /*  6:bDescriptorType */
    ITEM_LEN,                                                   /*  7:wItemLength(L) */
    0x00,                                                       /*  8:wItemLength(H) */

    /* Endpoint Descriptor 0 */
    USB_ED_BLENGTH,                                             /*  0:bLength */
    USB_DT_ENDPOINT,                                            /*  1:bDescriptorType */
    (uint8_t) (USB_EP_IN | HID_IN_EP),                            /*  2:bEndpointAddress */
    USB_EP_INT,                                                 /*  3:bmAttribute */
    IN_EP_MAX_PKT_SIZE,                                         /*  4:wMaxPacketSize_lo */
    0,                                                          /*  5:wMaxPacketSize_hi */
    0x01,                                                       /*  6:bInterval */

		/* Endpoint Descriptor 1 */
    USB_ED_BLENGTH,                                             /*  0:bLength */
    USB_DT_ENDPOINT,                                            /*  1:bDescriptorType */
    (uint8_t) (USB_EP_OUT | HID_OUT_EP),                            /*  2:bEndpointAddress */
    USB_EP_INT,                                                 /*  3:bmAttribute */
    OUT_EP_MAX_PKT_SIZE,                                         /*  4:wMaxPacketSize_lo */
    0,                                                          /*  5:wMaxPacketSize_hi */
    0x01,                                                       /*  6:bInterval */
};

/************************************************************
 *  String Descriptor 0                                     *
 ************************************************************/
/* UNICODE 0x0409 English (United States) */
__align(4) const static uint8_t gs_apl_string0[] =
{
    4,                                              /*  0:bLength */
    USB_DT_STRING,                                  /*  1:bDescriptorType */
    0x09, 0x04                                      /*  2:wLANGID[0] */
};

/************************************************************
 *  String Descriptor 1                                     *
 ************************************************************/
/* 14:iManufacturer */
__align(4) const uint8_t gs_apl_string1[] =
{
    20,                         /*  0:bLength */
    USB_DT_STRING,              /*  1:bDescriptorType */
    'C', 0x00,                  /*  2:wLANGID[0] */
    'M', 0x00,
    'S', 0x00,
    'e', 0x00,
    'm', 0x00,
    'i', 0x00,
    'c', 0x00,
    'o', 0x00,
    'n', 0x00,
};

/************************************************************
 *  String Descriptor 2                                     *
 ************************************************************/
/* 15:iProduct */
__align(4) const static uint8_t gs_apl_string2[] =
{
	  26,                 /*  0:bLength */
    USB_DT_STRING,      /*  1:bDescriptorType */
    'U', 0x00,
    'S', 0x00,
    'B', 0x00,
    ' ', 0x00,
    'H', 0x00,
    'I', 0x00,
    'D', 0x00,
    ' ', 0x00,
	  'I', 0x00,
    'S', 0x00,
    'P', 0x00,
};

/************************************************************
 *  String Descriptor 3                                     *
 ************************************************************/
/* 16:iSerialNumber */
__align(4) const static uint8_t gs_apl_string3[] =
{
    10,                 /*  0:bLength */
    USB_DT_STRING,      /*  1:bDescriptorType */
    'P', 0x00,
    '0', 0x00,
    '0', 0x00,
    '1', 0x00,
};


/************************************************************
 *  String Descriptor Table address                         *
 ************************************************************/
__align(4) const uint8_t * gp_apl_string_table[] =
{
    gs_apl_string0,                             /* UNICODE 0x0409 English (United States) */
    gs_apl_string1,                             /* iManufacturer */
    gs_apl_string2,                             /* iProduct */
    gs_apl_string3,                             /* iSerialNumber */
};

/************************************************************
 *  HID Report Discriptor for Keyboard                      *
 ************************************************************/
__align(4) const uint8_t g_apl_report[] =
{
    0x05, 0x01,                                     /* Usage Page (Generic Desktop) */
    0x09, 0x00,                                     /* Usage (0) */
    0xA1, 0x01,                                     /* Collection (Application) */
    0x19, 0x00,                                     /* Usage Minimum (0) */
    0x29, 0xFF,                                     /* Usage Maximum (255) */
    0x15, 0x00,                                     /* Logical Minimum (0) */
    0x25, 0xFF,                                     /* Logical Maximum (255) */
    0x75, 0x08,                                     /* Report Size (8) */
    0x95, 0x40,                                     /* Report Count (8) */
    0x81, 0x02,                                     /* Input (Data , Variable , Absolute)  ;Modifier byte */
    0x19, 0x00,                                     /* Usage Minimum (0) */
    0x29, 0xFF,                                     /* Usage Maximum (255) */
    0x91, 0x02,                                     /* Output (Data , Variable , Absolute)  ;LED report */
    0xC0,                                           /* End Collection */
};

/******************************************************************************
 End  Of File
 ******************************************************************************/
