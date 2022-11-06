/******************************************************************************
 * File Name    : usb_pmsc_descriptor.c
 * Description  : USB Host and Peripheral Interrupt code
 ******************************************************************************/

/******************************************************************************
 Includes   <System Includes> , "Project Includes"
 ******************************************************************************/
#include <stdlib.h>
#include <stdio.h>

#include "usb_pmsc_apl.h"

/******************************************************************************
 Macro definitions
 ******************************************************************************/
/* bcdUSB */
#define USB_BCDNUM              (0x0200u)

/* Release Number */
#define USB_RELEASE             (0x0200u)

/* DCP max packet size */
#define USB_DCPMAXP             (0x40u)

/* Configuration number */
#define USB_CONFIGNUM           (0x01u)

/* Vendor ID */
#define USB_VENDORID            (0x0000u)

/* Product ID */
#define USB_PRODUCTID           (0x0008u)

#define USB_PMSC_QD_BLENGTH     (0x0au)
#define USB_PMSC_CD1_BLENGTH    (0x20u)
#define USB_PMSC_SD0_BLENGTH    (0x04u)
#define USB_PMSC_SD1_BLENGTH    (0x14u)
#define USB_PMSC_SD2_BLENGTH    (0x22u)
#define USB_PMSC_SD3_BLENGTH    (0x20u)
#define USB_PMSC_SD4_BLENGTH    (0x16u)
#define USB_PMSC_SD5_BLENGTH    (0x12u)
#define USB_PMSC_SD6_BLENGTH    (0x1cu)

/* Sub_class code */
#define USB_ATAPI               (0x05u)
#define USB_SCSI                (0x06u)

/* Protocol code */
#define USB_BOTP                (0x50u)
#define USB_TOTALEP             (0x02u)

/* Select SubClass */
/* #define USB_INTERFACE_SUBCLASS  (USB_SCSI) */
#define USB_INTERFACE_SUBCLASS  (USB_ATAPI)

/*******************************************************************************
 Typedef definitions
 ******************************************************************************/

/*******************************************************************************
 Exported global variables (to be accessed by other files)
 ******************************************************************************/

/* Standard Device Descriptor */
uint8_t g_apl_device[USB_DD_BLENGTH + ( USB_DD_BLENGTH % 2)] =
{
    USB_DD_BLENGTH,                                         /*  0:bLength */
    USB_DT_DEVICE,                                          /*  1:bDescriptorType */
    (USB_BCDNUM & (uint8_t) 0xffu),                         /*  2:bcdUSB_lo */
    ((uint8_t) (USB_BCDNUM >> 8) & (uint8_t) 0xffu),        /*  3:bcdUSB_hi */
    0,                                                      /*  4:bDeviceClass */
    0,                                                      /*  5:bDeviceSubClass */
    0,                                                      /*  6:bDeviceProtocol */
    (uint8_t) USB_DCPMAXP,                                  /*  7:bMAXPacketSize(for DCP) */
    (USB_VENDORID & (uint8_t) 0xffu),                       /*  8:idVendor_lo */
    ((uint8_t) (USB_VENDORID >> 8) & (uint8_t) 0xffu),      /*  9:idVendor_hi */
    ((uint16_t) USB_PRODUCTID & (uint8_t) 0xffu),           /* 10:idProduct_lo */
    ((uint8_t) (USB_PRODUCTID >> 8) & (uint8_t) 0xffu),     /* 11:idProduct_hi */
    (USB_RELEASE & (uint8_t) 0xffu),                        /* 12:bcdDevice_lo */
    ((uint8_t) (USB_RELEASE >> 8) & (uint8_t) 0xffu),       /* 13:bcdDevice_hi */
    1,                                                      /* 14:iManufacturer */
    2,                                                      /* 15:iProduct */
    6,                                                      /* 16:iSerialNumber */
    USB_CONFIGNUM                                           /* 17:bNumConfigurations */
};

/* Configuration Descriptor */
uint8_t g_apl_configuration[USB_PMSC_CD1_BLENGTH + ( USB_PMSC_CD1_BLENGTH % 2)] =
{
    USB_CD_BLENGTH,                     /*  0:bLength */
    USB_DT_CONFIGURATION,               /*  1:bDescriptorType */
    USB_PMSC_CD1_BLENGTH % 256,         /*  2:wTotalLength(L) */
    USB_PMSC_CD1_BLENGTH / 256,         /*  3:wTotalLength(H) */
    1,                                  /*  4:bNumInterfaces */
    1,                                  /*  5:bConfigurationValue */
    4,                                  /*  6:iConfiguration */
    USB_CF_RESERVED | USB_CF_SELFP,     /*  7:bmAttributes */
    (10 / 2),                           /*  8:MAXPower (2mA unit) */

    /* Interface Descriptor */
    USB_ID_BLENGTH,                     /*  0:bLength */
    USB_DT_INTERFACE,                   /*  1:bDescriptor */
    0,                                  /*  2:bInterfaceNumber */
    0,                                  /*  3:bAlternateSetting */
    2,                                  /*  4:bNumEndpoints */
    USB_IFCLS_MAS,                      /*  5:bInterfaceClass */
    USB_INTERFACE_SUBCLASS,             /*  6:bInterfaceSubClass */
    USB_BOTP,                           /*  7:bInterfaceProtocol */
    3,                                  /*  8:iInterface */

    /* Endpoint Descriptor 0 */
    USB_ED_BLENGTH,                 /*  0:bLength */
    USB_DT_ENDPOINT,                /*  1:bDescriptorType */
    USB_EP_IN | USB_EP1,            /*  2:bEndpointAddress */
    USB_EP_BULK,                    /*  3:bmAttribute */
    64,                             /*  4:wMAXPacketSize_lo */
    0,                              /*  5:wMAXPacketSize_hi */
    0,                              /*  6:bInterval */

    /* Endpoint Descriptor 1 */
    USB_ED_BLENGTH,                 /*  0:bLength */
    USB_DT_ENDPOINT,                /*  1:bDescriptorType */
    USB_EP_OUT | USB_EP2,           /*  2:bEndpointAddress */
    USB_EP_BULK,                    /*  3:bmAttribute */
    64,                             /*  4:wMAXPacketSize_lo */
    0,                              /*  5:wMAXPacketSize_hi */
    1,                              /*  6:bInterval */
};

/* String Descriptor */
static uint8_t gs_usb_pmsc_str_descriptor0[USB_PMSC_SD0_BLENGTH + ( USB_PMSC_SD0_BLENGTH % 2)] =
{
    /* UNICODE 0x0409 English (United States) */
    USB_PMSC_SD0_BLENGTH,   /*  0:bLength */
    USB_DT_STRING,          /*  1:bDescriptorType */
    0x09, 0x04              /*  2:wLANGID[0] */
};

static uint8_t gs_usb_pmsc_str_descriptor1[USB_PMSC_SD1_BLENGTH + ( USB_PMSC_SD1_BLENGTH % 2)] =
{
    /* iManufacturer */
    USB_PMSC_SD1_BLENGTH,   /*  0:bLength */
    USB_DT_STRING,          /*  1:bDescriptorType */
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

static uint8_t gs_usb_pmsc_str_descriptor2[USB_PMSC_SD2_BLENGTH + ( USB_PMSC_SD2_BLENGTH % 2)] =
{
    /* iProduct */
    USB_PMSC_SD2_BLENGTH,   /*  0:bLength */
    USB_DT_STRING,          /*  1:bDescriptorType */
    'U', 0x00,
    'S', 0x00,
    'B', 0x00,
    ' ', 0x00,
    'M', 0x00,
    'a', 0x00,
    's', 0x00,
    's', 0x00,
    ' ', 0x00,
    'S', 0x00,
    't', 0x00,
    'o', 0x00,
    'r', 0x00,
    'a', 0x00,
    'g', 0x00,
    'e', 0x00
};

static uint8_t gs_usb_pmsc_str_descriptor3[USB_PMSC_SD3_BLENGTH + ( USB_PMSC_SD3_BLENGTH % 2)] =
{
    /* iInterface */
    USB_PMSC_SD3_BLENGTH,   /*  0:bLength */
    USB_DT_STRING,          /*  1:bDescriptorType */
    'R', 0x00,
    'e', 0x00,
    'm', 0x00,
    'o', 0x00,
    'v', 0x00,
    'a', 0x00,
    'b', 0x00,
    'l', 0x00,
    'e', 0x00,
    ' ', 0x00,
    'D', 0x00,
    'r', 0x00,
    'i', 0x00,
    'v', 0x00,
    'e', 0x00
};

static uint8_t gs_usb_pmsc_str_descriptor4[USB_PMSC_SD4_BLENGTH + ( USB_PMSC_SD4_BLENGTH % 2)] =
{
    /* iConfiguration */
    USB_PMSC_SD4_BLENGTH,   /*  0:bLength */
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

static uint8_t gs_usb_pmsc_str_descriptor5[USB_PMSC_SD5_BLENGTH + ( USB_PMSC_SD5_BLENGTH % 2)] =
{
    /* iConfiguration */
    USB_PMSC_SD5_BLENGTH,   /*  0:bLength */
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

static uint8_t gs_usb_pmsc_str_descriptor6[USB_PMSC_SD6_BLENGTH + ( USB_PMSC_SD6_BLENGTH % 2)] =
{
    /* iSerialNumber */
    USB_PMSC_SD6_BLENGTH,   /*  0:bLength */
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
    gs_usb_pmsc_str_descriptor0,
    gs_usb_pmsc_str_descriptor1,
    gs_usb_pmsc_str_descriptor2,
    gs_usb_pmsc_str_descriptor3,
    gs_usb_pmsc_str_descriptor4,
    gs_usb_pmsc_str_descriptor5,
    gs_usb_pmsc_str_descriptor6
};

/*******************************************************************************
 Private global variables and functions
 ******************************************************************************/

/******************************************************************************
 End  Of File
 ******************************************************************************/
