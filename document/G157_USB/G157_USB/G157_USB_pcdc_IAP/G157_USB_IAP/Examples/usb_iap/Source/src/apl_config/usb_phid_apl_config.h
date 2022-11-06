/******************************************************************************
 * File Name    : usb_phid_apl_config.h
 * Description  : USB Peripheral HID program configuration file.
 ******************************************************************************/

#ifndef USB_PHID_APL_CONFIG_H
#define USB_PHID_APL_CONFIG_H

/*******************************************************************************
 Macro definitions
 ******************************************************************************/

/** [Select PHID Demo sample Application mode]
 *  USB_ECHO              : Loop back(Echo) mode
 *  USB_KEYBOARD          : Keyboard mode
 */
#define OPERATION_MODE      (USB_KEYBOARD)

/** [Select USE power saving control]
 * define               : Use power saving control
 * not define           : Not use power saving control
 */
//#define USE_LPW


#endif  /* USB_PHID_APL_CONFIG_H */
/******************************************************************************
 End  Of File
 ******************************************************************************/

