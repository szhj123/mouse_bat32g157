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
#define REPORT_ID_MOUSE                             0x01
#define REPORT_ID_KEYBOARD                          0x02
#define REPORT_ID_CONSUMER                          0x03
#define REPORT_ID_KEY_VALUE                         0x60
#define REPORT_ID_LIGHT_DPI_RATE                    0x61
#define REPORT_ID_KEY_MODE                          0x62
#define REPORT_ID_LIGHT_EFFECT                      0x63
#define REPORT_ID_MACRO                             0x64
#define REPORT_ID_PIC                               0x65
#define REPORT_ID_DPI                               0x66

/*******************************************************************************
 Exported global variables
 ******************************************************************************/

extern  const   uint8_t g_apl_device[];
extern  const   uint8_t g_apl_configuration[];
extern  const   uint8_t *gp_apl_string_table[];

extern  const   uint8_t g_apl_mouse_report[];
extern  const   uint8_t g_apl_keyboard_report[];

extern  const   uint32_t REPORT_MOUSE_SIZE;
extern  const   uint32_t REPORT_KEYBOARD_SIZE;

extern uint8_t g_remote_wakeup_enable;

/*******************************************************************************
 Exported global functions (to be accessed by other files)
 ******************************************************************************/

void Usb_Init (void);
void Usb_Ep0_In(uint8_t *buf, uint8_t length );
void Usb_Ep1_In(uint8_t *buf, uint8_t length );
void Usb_Ep2_In(uint8_t *buf, uint8_t length );
void Usb_Ep3_Out(void );

#endif /* USB_PHID_APL_H */
/******************************************************************************
 End  Of File
 ******************************************************************************/
