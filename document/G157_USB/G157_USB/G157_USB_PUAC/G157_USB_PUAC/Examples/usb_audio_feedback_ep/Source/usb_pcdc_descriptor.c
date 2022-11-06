/*******************************************************************************
 * File Name    : usb_pcdc_descriptor.c
 * Description  : USB PCDC Descriptor data.
 *******************************************************************************/

/******************************************************************************
 Includes   <System Includes> , "Project Includes"
 ******************************************************************************/

#include "usb_basic_mini_if.h"
#include "usb_pcdc_apl_config.h"

/******************************************************************************
 Macro definitions
 ******************************************************************************/

/* bcdUSB */
#define USB_BCDNUM                      (0x0200u)
/* Release Number */
#define USB_RELEASE                     (0x0200u)
/* DCP max packet size */
#define USB_DCPMAXP                     (64u)
/* Configuration number */
#define USB_CONFIGNUM                   (1u)
/* Vendor ID */
//#define USB_VENDORID                    (0xFA7Bu)
#define USB_VENDORID                    (0x0000u)
/* Product ID */
//#define USB_PRODUCTID                   (0x0024u)
#define USB_PRODUCTID                   (0x0002u)

/* Class-Specific Configuration Descriptors */
#define     USB_PCDC_CS_INTERFACE                               (0x24u)

/* bDescriptor SubType in Communications Class Functional Descriptors */
/* Header Functional Descriptor */
#define     USB_PCDC_DT_SUBTYPE_HEADER_FUNC                     (0x00u)
/* Call Management Functional Descriptor. */
#define     USB_PCDC_DT_SUBTYPE_CALL_MANAGE_FUNC                (0x01u)
/* Abstract Control Management Functional Descriptor. */
#define     USB_PCDC_DT_SUBTYPE_ABSTRACT_CTR_MANAGE_FUNC        (0x02u)
/* Union Functional Descriptor */
#define     USB_PCDC_DT_SUBTYPE_UNION_FUNC                      (0x06u)

/* Communications Class Subclass Codes */
#define     USB_PCDC_CLASS_SUBCLASS_CODE_ABS_CTR_MDL            (0x02u)

/* USB Class Definitions for Communications Devices Specification
 release number in binary-coded decimal. */
#define     USB_PCDC_BCD_CDC          (0x0110u)

/* Descriptor length */
#define USB_PCDC_QD_LEN               (10u)
#define USB_PCDC_CD1_LEN              (67u)
#define STRING_DESCRIPTOR0_LEN        (4u)
#define STRING_DESCRIPTOR1_LEN        (20u)
#define STRING_DESCRIPTOR2_LEN        (44u)
#define STRING_DESCRIPTOR3_LEN        (46u)
#define STRING_DESCRIPTOR4_LEN        (22u)
#define STRING_DESCRIPTOR5_LEN        (18u)
#define STRING_DESCRIPTOR6_LEN        (28u)

/*******************************************************************************
 Typedef definitions
 ******************************************************************************/

/*******************************************************************************
 Exported global variables (to be accessed by other files)
 ******************************************************************************/

/* Standard Device Descriptor */
uint8_t g_apl_device[USB_DD_BLENGTH + ( USB_DD_BLENGTH % 2)] =
{
    USB_DD_BLENGTH,                                     /*  0:bLength */
    USB_DT_DEVICE,                                      /*  1:bDescriptorType */
    (USB_BCDNUM & (uint8_t) 0xffu),                     /*  2:bcdUSB_lo */
    ((uint8_t) (USB_BCDNUM >> 8) & (uint8_t) 0xffu),    /*  3:bcdUSB_hi */
    USB_IFCLS_CDCC,                                     /*  4:bDeviceClass */
    0,                                                  /*  5:bDeviceSubClass */
    0,                                                  /*  6:bDeviceProtocol */
    (uint8_t) USB_DCPMAXP,                              /*  7:bMAXPacketSize(for DCP) */
    (USB_VENDORID & (uint8_t) 0xffu),                   /*  8:idVendor_lo */
    ((uint8_t) (USB_VENDORID >> 8) & (uint8_t) 0xffu),  /*  9:idVendor_hi */
    ((uint16_t) USB_PRODUCTID & (uint8_t) 0xffu),       /* 10:idProduct_lo */
    ((uint8_t) (USB_PRODUCTID >> 8) & (uint8_t) 0xffu), /* 11:idProduct_hi */
    (USB_RELEASE & (uint8_t) 0xffu),                    /* 12:bcdDevice_lo */
    ((uint8_t) (USB_RELEASE >> 8) & (uint8_t) 0xffu),   /* 13:bcdDevice_hi */
    1,                                                  /* 14:iManufacturer */
    2,                                                  /* 15:iProduct */
    6,                                                  /* 16:iSerialNumber */
    USB_CONFIGNUM /* 17:bNumConfigurations */
};

/* Configuration Or Other_Speed_Configuration Descriptor*/
uint8_t g_apl_configuration[USB_PCDC_CD1_LEN + ( USB_PCDC_CD1_LEN % 2)] =
{
    USB_CD_BLENGTH,                 /*  0:bLength */
    USB_DT_CONFIGURATION,           /*  1:bDescriptorType */
    USB_PCDC_CD1_LEN % 256,         /*  2:wTotalLength(L) */
    USB_PCDC_CD1_LEN / 256,         /*  3:wTotalLength(H) */
    2,                              /*  4:bNumInterfaces */
    1,                              /*  5:bConfigurationValue */
    0,                              /*  6:iConfiguration */
    USB_CF_RESERVED | USB_CF_SELFP, /*  7:bmAttributes */
    (10 / 2),                       /*  8:MAXPower (2mA unit) */

    /* Interface Descriptor */
    USB_ID_BLENGTH,                 /*  0:bLength */
    USB_DT_INTERFACE,               /*  1:bDescriptor */
    0,                              /*  2:bInterfaceNumber */
    0,                              /*  3:bAlternateSetting */
    1,                              /*  4:bNumEndpoints */
    USB_IFCLS_CDCC,                 /*  5:bInterfaceClass */
    USB_PCDC_CLASS_SUBCLASS_CODE_ABS_CTR_MDL,   /*  6:bInterfaceSubClass */
    1,                              /*  7:bInterfaceProtocol */
    0,                              /*  8:iInterface */

    /* Communications Class Functional Descriptorss */
    5,                          /*  0:bLength */
    USB_PCDC_CS_INTERFACE,      /*  1:bDescriptorType */
    USB_PCDC_DT_SUBTYPE_HEADER_FUNC,    /*  2:bDescriptorSubtype */
    USB_PCDC_BCD_CDC % 256,     /*  3:bcdCDC_lo */
    USB_PCDC_BCD_CDC / 256,     /*  4:bcdCDC_hi */

    /* Communications Class Functional Descriptorss */
    4,                          /*  0:bLength */
    USB_PCDC_CS_INTERFACE,      /*  1:bDescriptorType */
    USB_PCDC_DT_SUBTYPE_ABSTRACT_CTR_MANAGE_FUNC,   /*  2:bDescriptorSubtype */
    2,                          /*  3:bmCapabilities */

    /* Communications Class Functional Descriptorss */
    5,                          /*  0:bLength */
    USB_PCDC_CS_INTERFACE,      /*  1:bDescriptorType */
    USB_PCDC_DT_SUBTYPE_UNION_FUNC, /*  2:bDescriptorSubtype */
    0,                          /*  3:bMasterInterface */
    1,                          /*  4:bSlaveInterface0 */

    /* Communications Class Functional Descriptorss */
    5,                          /*  0:bLength */
    USB_PCDC_CS_INTERFACE,      /*  1:bDescriptorType */
    USB_PCDC_DT_SUBTYPE_CALL_MANAGE_FUNC,   /*  2:bDescriptorSubtype */
    /* D1:1-Device can send/receive call management
     information over a Data Class interface. */
    /* D0:1-Device handles call management itself. */
    3,                          /*  3:bmCapabilities */
    1,                          /*  4:bDataInterface */

    /* Endpoint Descriptor 0 */
    7,                          /*  0:bLength */
    USB_DT_ENDPOINT,            /*  1:bDescriptorType */
    USB_EP_IN | USB_EP3,        /*  2:bEndpointAddress */
    USB_EP_INT,                 /*  3:bmAttribute */
    16,                         /*  4:wMAXPacketSize_lo */
    0,                          /*  5:wMAXPacketSize_hi */
    0x10,                       /*  6:bInterval */

    /* Interface Descriptor */
    USB_ID_BLENGTH,                 /*  0:bLength */
    USB_DT_INTERFACE,               /*  1:bDescriptor */
    1,                              /*  2:bInterfaceNumber */
    0,                              /*  3:bAlternateSetting */
    2,                              /*  4:bNumEndpoints */
    USB_IFCLS_CDCD,                 /*  5:bInterfaceClass */
    0,                              /*  6:bInterfaceSubClass */
    0,                              /*  7:bInterfaceProtocol */
    0,                              /*  8:iInterface */

    /* Endpoint Descriptor 0 */
    USB_ED_BLENGTH,             /*  0:bLength */
    USB_DT_ENDPOINT,            /*  1:bDescriptorType */
    USB_EP_IN | USB_EP1,        /*  2:bEndpointAddress */
    USB_EP_BULK,                /*  3:bmAttribute */
    64,                         /*  4:wMAXPacketSize_lo */
    0,                          /*  5:wMAXPacketSize_hi */
    0,                          /*  6:bInterval */

    /* Endpoint Descriptor 1 */
    USB_ED_BLENGTH,             /*  0:bLength */
    USB_DT_ENDPOINT,            /*  1:bDescriptorType */
    USB_EP_OUT | USB_EP2,       /*  2:bEndpointAddress */
    USB_EP_BULK,                /*  3:bmAttribute */
    64,                         /*  4:wMAXPacketSize_lo */
    0,                          /*  5:wMAXPacketSize_hi */
    0,                          /*  6:bInterval */
};

/*******************************************************************************
 Private global variables and functions
 ******************************************************************************/

/* String Descriptor */
static uint8_t gs_cdc_string_descriptor0[STRING_DESCRIPTOR0_LEN + ( STRING_DESCRIPTOR0_LEN % 2)] =
{
    /* UNICODE 0x0409 English (United States) */
    STRING_DESCRIPTOR0_LEN,     /*  0:bLength */
    USB_DT_STRING,              /*  1:bDescriptorType */
    0x09, 0x04                  /*  2:wLANGID[0] */
};

/* iManufacturer */
static uint8_t gs_cdc_string_descriptor1[STRING_DESCRIPTOR1_LEN + ( STRING_DESCRIPTOR1_LEN % 2)] =
{
    STRING_DESCRIPTOR1_LEN,     /*  0:bLength */
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

/* iProduct */
static uint8_t gs_cdc_string_descriptor2[STRING_DESCRIPTOR2_LEN + ( STRING_DESCRIPTOR2_LEN % 2)] =
{
    STRING_DESCRIPTOR2_LEN, /*  0:bLength */
    USB_DT_STRING,          /*  1:bDescriptorType */
    'C', 0x00,
    'D', 0x00,
    'C', 0x00,
    ' ', 0x00,
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
static uint8_t gs_cdc_string_descriptor3[STRING_DESCRIPTOR3_LEN + ( STRING_DESCRIPTOR3_LEN % 2)] =
{
    STRING_DESCRIPTOR3_LEN, /*  0:bLength */
    USB_DT_STRING,          /*  1:bDescriptorType */
    'C', 0x00,
    'o', 0x00,
    'm', 0x00,
    'm', 0x00,
    'u', 0x00,
    'n', 0x00,
    'i', 0x00,
    'c', 0x00,
    'a', 0x00,
    't', 0x00,
    'i', 0x00,
    'o', 0x00,
    'n', 0x00,
    's', 0x00,
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
static uint8_t gs_cdc_string_descriptor4[STRING_DESCRIPTOR4_LEN + ( STRING_DESCRIPTOR4_LEN % 2)] =
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
static uint8_t gs_cdc_string_descriptor5[STRING_DESCRIPTOR5_LEN + ( STRING_DESCRIPTOR5_LEN % 2)] =
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
static uint8_t gs_cdc_string_descriptor6[STRING_DESCRIPTOR6_LEN + ( STRING_DESCRIPTOR6_LEN % 2)] =
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

/* String Descriptor */
uint8_t *gp_apl_string_table[] =
{
    gs_cdc_string_descriptor0,
    gs_cdc_string_descriptor1,
    gs_cdc_string_descriptor2,
    gs_cdc_string_descriptor3,
    gs_cdc_string_descriptor4,
    gs_cdc_string_descriptor5,
    gs_cdc_string_descriptor6
};


/******************************************************************************
 End  Of File
 ******************************************************************************/
