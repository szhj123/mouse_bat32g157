/*******************************************************************************
 * File Name    : usb_phid_mini_config.h
 * Description  : USB Peripheral UAC configuration
 ******************************************************************************/

#ifndef USB_PUAC_MINI_CONFIG_H
#define USB_PUAC_MINI_CONFIG_H

/******************************************************************************
 Macro definitions
 ******************************************************************************/

/** [Setting pipe to be used]
 * USB_CFG_PUAC_INT_IN  : Pipe number (USB_PIPE1 to USB_PIPE2) UAC Interrupt In Pipe
 * USB_CFG_PUAC_INT_OUT : Pipe number (USB_PIPE1 to USB_PIPE2) UAC Interrupt Out Pipe
 */

#define USB_CFG_PUAC_ISO_IN               (USB_PIPE1)
#define USB_CFG_PUAC_ISO_OUT              (USB_PIPE2)

#endif  /* USB_PUAC_MINI_CONFIG_H */
/******************************************************************************
 End  Of File
 ******************************************************************************/
