/*******************************************************************************
 * File Name    : usb_pcdc_apl.c
 * Description  : USB Peripheral Communications Devices Class Sample Code
 *******************************************************************************/

/*******************************************************************************
 Includes   <System Includes> , "Project Includes"
 ******************************************************************************/

//#include "Pin.h"

#include <string.h>

#include "usb_basic_mini_if.h"
#include "usb_pcdc_mini_if.h"
#include "usb_pcdc_apl_config.h"

#if defined(USE_LPW)
//#include "usb_lowpower.h"
#endif /* defined(USE_LPW) */

#ifndef USB_PCDC_APL_H
#define USB_PCDC_APL_H


/******************************************************************************
 Macro definitions
 ******************************************************************************/
#define NUM_STRING_DESCRIPTOR   (7u)

#define USB_ECHO                (0)             /* Loop back(Echo) mode */
#define USB_UART                (1)             /* USB Serial(VCOM) converter mode */

#define DATA_LEN                (64)

/* LINE_CODING request wLength */
#define LINE_CODING_LENGTH      (0x07u)


/*******************************************************************************
 Typedef definitions
 ******************************************************************************/

/*******************************************************************************
 Exported global variables
 ******************************************************************************/

extern uint8_t g_apl_device[];
extern uint8_t g_apl_configuration[];
extern uint8_t *gp_apl_string_table[];

/*******************************************************************************
 Exported global functions (to be accessed by other files)
 ******************************************************************************/

void    Usb_Init (void);

#endif /* USB_PCDC_APL_H */
/******************************************************************************
End  Of File
 ******************************************************************************/

