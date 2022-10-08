/******************************************************************************
 * File Name    : usb_pmsc_apl.h
 * Description  : USB Phelipheral MSC Sample Code
 ******************************************************************************/

/******************************************************************************
 Includes   <System Includes> , "Project Includes"
 ******************************************************************************/

//#include "Pin.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "usb_basic_mini_if.h"

#include "usb_pmsc_mini_if.h"
#include "usb_media_driver_mini_if.h"
#include "ram_disk.h"
#include "usb_pmsc_apl_config.h"

#if defined(USE_LPW)
#include "usb_rsk_lowpower.h"
#endif /* defined(USE_LPW) */

#if USB_CFG_DTC == USB_CFG_ENABLE
#include "r_dtc_rx_if.h"
#endif /* USB_CFG_DTC == USB_CFG_ENABLE */

#if USB_CFG_DMA == USB_CFG_ENABLE
#include "r_dmaca_rx_if.h"
#endif /* USB_CFG_DMA == USB_CFG_ENABLE */

#ifndef USB_PMSC_APL_H
    #define USB_PMSC_APL_H


/******************************************************************************
 Macro definitions
 ******************************************************************************/

#define NUM_STRING_DESCRIPTOR (7u)

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

extern void Usb_Init (void);
extern void USB_PinSet_USB0_PERI (void);

#endif /* USB_PMSC_APL_H */
/******************************************************************************
 End  Of File
 ******************************************************************************/
