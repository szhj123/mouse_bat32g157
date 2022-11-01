/******************************************************************************
 * File Name    : usb_phid_mini_if.h
 * Description  : Interface file for USB Peripheral HID class API
 ******************************************************************************/
/******************************************************************************
 Includes   <System Includes> , "Project Includes"
 ******************************************************************************/

#include "usb_phid_mini_config.h"

#ifndef USB_PHID_MINI_IF_H
#define USB_PHID_MINI_IF_H

/******************************************************************************
 Macro definitions
 ******************************************************************************/

#define USB_PHID_ECHO_MODE          (0)           /*  Peripheral HID Application echo mode */
#define USB_PHID_KEYBOARD_MODE      (1)           /* Peripheral HID Application keyboard mode */
#define USB_PHID_MOUSE_MODE         (2)           /* Peripheral HID Application mouse mode */

/*----- HID Mouse Class Request Defines --------*/
/* HID Class Request codes */
#define USB_GET_REPORT                  (0x0100u)
#define USB_GET_IDLE                    (0x0200u)
#define USB_GET_PROTOCOL                (0x0300u)
#define USB_SET_IDLE                    (0x0A00u)
#define USB_SET_REPORT                  (0x0900u)
#define USB_SET_PROTOCOL                (0x0B00u)

/* PHID reception message type definition */
#define USB_GET_REPORT_DESCRIPTOR       (0x2200u)
#define USB_GET_HID_DESCRIPTOR          (0x2100u)

/* ----- DESCRIPTOR Types ----- */
#define USB_DT_TYPE_GETREPORT           ((uint8_t)0x01)   /* Report Type Input */
#define USB_DT_TYPE_SETREPORT           ((uint8_t)0x02)   /* Report Type Output */
#define USB_DT_TYPE_HIDDESCRIPTOR       ((uint8_t)0x21)   /* HID descriptor type */
#define USB_DT_TYPE_RPTDESCRIPTOR       ((uint8_t)0x22)   /* Report descriptor type */

/* ----- Subclass Codes ----- */
#define USB_IFSUB_NOBOOT                ((uint8_t)0x00)   /* No Subclass */
#define USB_IFSUB_BOOT                  ((uint8_t)0x01)   /* Boot Interface Subclass */

/* ----- Protocol Codes ----- */
#define USB_IFPRO_NONE                  ((uint8_t)0x00)   /* Demonstration */
#define USB_IFPRO_KBD                   ((uint8_t)0x01)   /* Keyboard */
#define USB_IFPRO_MSE                   ((uint8_t)0x02)   /* Mouse */

/* Peripheral HID Max Packet Size */
#define USB_PHID_MXPS_KBD               (8u)
#define USB_PHID_MXPS_MSE               (3u)
#define USB_PHID_MXPS_ECHO              (64u)

/*******************************************************************************
 Typedef definitions
 ******************************************************************************/

/*******************************************************************************
 Exported global variables
 ******************************************************************************/

/*******************************************************************************
 Exported global functions (to be accessed by other files)
 ******************************************************************************/

#endif /* USB_PHID_MINI_IF_H */
/******************************************************************************
 End  Of File
 ******************************************************************************/
