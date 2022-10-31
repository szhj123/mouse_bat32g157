/*******************************************************************************
 * File Name    : r_usb_hmsc_mini_config.h
 * Description  : USB Host MSC configuration
 ******************************************************************************/

#ifndef USB_HMSC_MINI_CONFIG_H
#define USB_HMSC_MINI_CONFIG_H

/*******************************************************************************
 Macro definitions
 ******************************************************************************/

/** [Setting pipe to be used]
 * USB_CFG_PMSC_BULK_IN     : Pipe number (USB_PIPE1 to USB_PIPE5)  MSC Bulk In Pipe
 * USB_CFG_PMSC_BULK_OUT    : Pipe number (USB_PIPE1 to USB_PIPE5)  MSC Bulk Out Pipe
 */
#define USB_CFG_HMSC_BULK_IN        (USB_PIPE1)
#define USB_CFG_HMSC_BULK_OUT       (USB_PIPE2)


#endif  /* USB_HMSC_MINI_CONFIG_H */
/******************************************************************************
 End  Of File
 ******************************************************************************/
