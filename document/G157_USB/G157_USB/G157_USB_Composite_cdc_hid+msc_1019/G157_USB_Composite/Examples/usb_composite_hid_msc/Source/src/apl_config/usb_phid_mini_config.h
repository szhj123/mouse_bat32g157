/*******************************************************************************
 * File Name    : usb_phid_mini_config.h
 * Description  : USB Peripheral HID configuration
 ******************************************************************************/

#ifndef USB_PHID_MINI_CONFIG_H
#define USB_PHID_MINI_CONFIG_H

/******************************************************************************
 Macro definitions
 ******************************************************************************/

/** [Setting pipe to be used]
 * USB_CFG_PHID_INT_IN  : Pipe number (USB_PIPE6 to USB_PIPE9) HID Interrupt In Pipe
 * USB_CFG_PHID_INT_OUT : Pipe number (USB_PIPE6 to USB_PIPE9) HID Interrupt Out Pipe
 */
#define USB_CFG_PHID_INT_IN               (USB_PIPE6)
#define USB_CFG_PHID_INT_OUT              (USB_PIPE7)

#endif  /* USB_PHID_MINI_CONFIG_H */
/******************************************************************************
 End  Of File
 ******************************************************************************/
