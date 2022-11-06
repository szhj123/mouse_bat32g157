/******************************************************************************
 * File Name    : usb_pmsc_mini_if.h
 * Description  : Interface file for USB vendor class API for RX
 ******************************************************************************/

/******************************************************************************
 Includes   <System Includes> , "Project Includes"
 ******************************************************************************/

/* Used to get which MCU is currently being used. */
/* User specific options for Flash API */
#include "usb_basic_mini_config.h"
#include "usb_pmsc_mini_config.h"

#ifndef USB_PMSC_MINI_IF_H
#define USB_PMSC_MINI_IF_H

/******************************************************************************
 Macro definitions
 ******************************************************************************/

/* MSC Class Request code define. */
#define USB_MASS_STORAGE_RESET          (0xFF00)    /* Mass storage reset request */
#define USB_GET_MAX_LUN                 (0xFE00)    /* Get max logical unit number */

/*******************************************************************************
 Typedef definitions
 ******************************************************************************/

/*******************************************************************************
 Exported global variables
 ******************************************************************************/

/******************************************************************************
 Exported global functions (to be accessed by other files)
 ******************************************************************************/

#endif  /* USB_PMSC_MINI_IF_H */
/******************************************************************************
 End  Of File
 ******************************************************************************/

