/******************************************************************************
 * File Name    : usb_phid_apl.h
 * Description  : USB Phelipheral HID Sample Code
 ******************************************************************************/

/******************************************************************************
 Includes   <System Includes> , "Project Includes"
 ******************************************************************************/

#include "usb_phid_mini_if.h"

#include <string.h>
#include "usb_basic_mini_if.h"

#ifndef USB_PHID_APL_H
#define USB_PHID_APL_H

/*******************************************************************************
 Macro definitions
 ******************************************************************************/

#define NUM_STRING_DESCRIPTOR (7u)

#define USB_ECHO                (0)                 /* Loop back(Echo) mode */
#define USB_KEYBOARD            (1)                 /* Keyboard mode */

#define NO_WRITING              (0)
#define DATA_WRITING            (1)
#define ZERO_WRITING            (2)

#define KBD_CODE_A              (0x04)      /* a */
#define KBD_CODE_Z              (0x1D)      /* z */
#define KBD_CODE_1              (0x1E)      /* 1 */
#define KBD_CODE_0              (0x27)      /* 0 */
#define KBD_CODE_ENTER          (0x28)      /* '\n' */

/*******************************************************************************
 Typedef definitions
 ******************************************************************************/

/*******************************************************************************
 Exported global variables
 ******************************************************************************/

extern  const   uint8_t g_apl_device[];
extern  const   uint8_t g_apl_configuration[];
extern  const   uint8_t *gp_apl_string_table[];
extern  const   uint8_t g_apl_report[];

extern const uint8_t g_apl_mouse_report[];
extern const uint8_t g_apl_keyboard_report[];

extern uint8_t g_remote_wakeup_enable;
extern uint32_t REPORT_MOUSE_SIZE;
extern uint32_t REPORT_KEYBOARD_SIZE;

/*******************************************************************************
 Exported global functions (to be accessed by other files)
 ******************************************************************************/

void usb_main (void);

#endif /* USB_PHID_APL_H */
/******************************************************************************
 End  Of File
 ******************************************************************************/
