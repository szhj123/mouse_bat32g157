/******************************************************************************
 * File Name    : usb_pcdc_mini_config.h
 * Description  : USB Peripheral CDC configuration
 ******************************************************************************/

#ifndef USB_PCDC_MINI_CONFIG_H
#define USB_PCDC_MINI_CONFIG_H

/*******************************************************************************
 Macro definitions
 ******************************************************************************/

/** [Setting pipe to be used]
 * USB_CFG_PCDC_BULK_IN   : Pipe number (USB_PIPE1 to USB_PIPE5)  CDC Data class Bulk In Pipe
 * USB_CFG_PCDC_BULK_OUT  : Pipe number (USB_PIPE1 to USB_PIPE5)  CDC Data class Bulk Out Pipe
 * USB_CFG_PCDC_INT_IN    : Pipe number (USB_PIPE6 to USB_PIPE9)  CDC Data class Interrupt In Pipe
 */
#define USB_CFG_PCDC_BULK_IN        (USB_PIPE1)
#define USB_CFG_PCDC_BULK_OUT       (USB_PIPE2)
//#define USB_CFG_PCDC_INT_IN         (USB_PIPE6)
#define USB_CFG_PCDC_INT_IN         (USB_PIPE8)	//laidi Composite PCDC and PHID


#endif  /* USB_PCDC_MINI_CONFIG_H */
/******************************************************************************
 End  Of File
 ******************************************************************************/
