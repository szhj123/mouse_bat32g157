/* Generated configuration header file - do not edit */

/*****************************************************************************
 * File Name    : usb_pmsc_mini_config.h
 * Description  : USB Peripheral MSC configuration
 ******************************************************************************/
/*****************************************************************************
 * History : DD.MM.YYYY Version Description
 *         : 01.09.2014 1.00    First Release
 *         : 30.11.2018 1.10    Supporting Smart Configurator
 ******************************************************************************/

#ifndef USB_PMSC_MINI_CONFIG_H
#define USB_PMSC_MINI_CONFIG_H

/******************************************************************************
 Macro definitions
 ******************************************************************************/

/** [Setting pipe to be used]
 * USB_CFG_PMSC_BULK_IN     : Pipe number (USB_PIPE1 to USB_PIPE5)  MSC Bulk In Pipe
 * USB_CFG_PMSC_BULK_OUT    : Pipe number (USB_PIPE1 to USB_PIPE5)  MSC Bulk Out Pipe
 */
#define USB_CFG_PMSC_BULK_IN        (USB_PIPE1)
#define USB_CFG_PMSC_BULK_OUT       (USB_PIPE2)

/* Vendor Information in INQUIRY Data Format */
/* Note : Be sure to specify 8 bytes of data in double quotation marks. */
#define USB_CFG_PMSC_VENDOR             ("CMSemicon ")

/* Product Identification in INQUIRY Data Format */
/* Note : Be sure to specify 16 bytes of data in double quotation marks. */
#define USB_CFG_PMSC_PRODUCT            ("Mass Storage    ")

/* Product Revision Level in INQUIRY Data Format */
/* Note : Be sure to specify 4 bytes of data in double quotation marks. */
#define USB_CFG_PMSC_REVISION           ("1.00")

/* Number of data blocks transferred at one time (512 * N) */
#define USB_CFG_PMSC_TRANS_COUNT        (8)


#endif  /* USB_PMSC_MINI_CONFIG_H */
/******************************************************************************
 End  Of File
 ******************************************************************************/
