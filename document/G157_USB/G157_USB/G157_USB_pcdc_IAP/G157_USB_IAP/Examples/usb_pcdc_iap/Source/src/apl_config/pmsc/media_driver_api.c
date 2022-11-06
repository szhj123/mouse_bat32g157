/******************************************************************************
 * File Name     : r_media_driver_api.c
 * Description   : This is the API interface between the application and
 *                 block media device drivers.
 ******************************************************************************/
/******************************************************************************
 Includes   <System Includes> , "Project Includes"
 ******************************************************************************/
#include <stdint.h>
#include <stddef.h>

#include "usb_basic_mini_if.h"
#include "usb_typedef.h"
#include "usb_extern.h"
#include "usb_bitdefine.h"
//#include "usb_reg_access.h"
#include "usb.h"

#include "usb_media_driver_mini_if.h"
#include "usb_patapi.h"

/*******************************************************************************
 Macro definitions
 ******************************************************************************/

/*******************************************************************************
 Typedef definitions
 ******************************************************************************/

/*******************************************************************************
 Exported global variables (to be accessed by other files)
 ******************************************************************************/

/******************************************************************************
Private global variables and functions
 ******************************************************************************/
/*
 Media driver list
 This array is defined to hold a set of pointers to media_driver_t type structures.
 This provides a means to manage multiple media device drivers in the same system.
 An individual media driver is accessed by means of indexing into this array by use of the logical unit number (lun)
 parameter of the media driver API function call.
 The maximum number of drivers loaded at any given time is limited by the user configurable value MAX_NUM_LUNS.
 This list may contain duplicate pointers to the same driver in order to support multiple media devices of the same type.
 */
static usb_media_driver_t * gsp_usb_pmsc_media_driver_list = USB_NULL;


/******************************************************************************
 * Function Name: USB_media_initialize
 * Description  : This function initializes data structures and variables that
 *                are used by the media device to support its operation for the
 *                first time.
 * Arguments    : usb_media_driver_t * p_media_driver -
 *                    initializes data structures
 * Return value : result -
 *                    USB_MEDIA_RET_OK:      Success
 *                    USB_MEDIA_RET_PARERR:  Invalid parameter error.
 *                    USB_MEDIA_RET_OP_FAIL: Any other failures
 ******************************************************************************/
bool USB_media_initialize (usb_media_driver_t * p_media_driver)
{
    bool result;

    if (USB_NULL != p_media_driver)
    {
        gsp_usb_pmsc_media_driver_list = p_media_driver;
        result = true;
    }
    else
    {
        result = false;
    }

    return result;
} /* End of function USB_media_initialize() */


/******************************************************************************
 * Function Name: USB_media_open
 * Description  : This function
 * Arguments    : none
 * Return value : result -
 *                    USB_MEDIA_RET_OK:      Success
 *                    USB_MEDIA_RET_PARERR:  Invalid parameter error.
 *                    USB_MEDIA_RET_OP_FAIL: Any other failures
 ******************************************************************************/
usb_media_ret_t USB_media_open(void)
{
    usb_media_ret_t result;

    result = gsp_usb_pmsc_media_driver_list->pf_media_open();

    return result;
} /* End of function USB_media_open() */

/******************************************************************************
 * Function Name: USB_media_close
 * Description  : This function
 * Arguments    : none
 * Return value : result -
 *                    USB_MEDIA_RET_OK:      Success
 *                    USB_MEDIA_RET_PARERR:  Invalid parameter error.
 *                    USB_MEDIA_RET_OP_FAIL: Any other failures
 ******************************************************************************/
usb_media_ret_t USB_media_close(void)
{
    usb_media_ret_t result;

    result = gsp_usb_pmsc_media_driver_list->pf_media_close();

    return result;
} /* End of function USB_media_close() */

/******************************************************************************
 * Function Name: USB_media_read
 * Description  : This function reads data from a specified location of the
 *                storage medium
 * Arguments    : p_wbuffer -
 *                    Pointer to the read data buffer.
 *              : start_block -
 *                    Start block number.
 *              : block_count -
 *                    Number of blocks to read.
 * Return value : result -
 *                    USB_MEDIA_RET_OK:      Success
 *                    USB_MEDIA_RET_PARERR:  Invalid parameter error
 *                    USB_MEDIA_RET_RWERR:   Read/Write Error
 *                    USB_MEDIA_RET_NOTRDY:  Not Ready
 *                    USB_MEDIA_RET_OP_FAIL: Any other failures
 ******************************************************************************/
usb_media_ret_t USB_media_read(uint8_t* p_rbuffer, uint32_t start_block, uint8_t block_count)
{
    usb_media_ret_t result;

    result = gsp_usb_pmsc_media_driver_list->pf_media_read(p_rbuffer, start_block, block_count);
    return result;
} /* End of function USB_media_read() */

/******************************************************************************
 * Function Name: USB_media_write
 * Description  : This function writes data to a specified location of the
 *                storage medium
 * Arguments    : p_wbuffer -
 *                    Pointer to the write data buffer.
 *              : start_block -
 *                    Start block number.
 *              : block_count -
 *                    Number of blocks to write.
 * Return value : result -
 *                    USB_MEDIA_RET_OK:      Success
 *                    USB_MEDIA_RET_PARERR:  Invalid parameter error
 *                    USB_MEDIA_RET_RWERR:   Read/Write Error
 *                    USB_MEDIA_RET_WRPRT:   Write Protected
 *                    USB_MEDIA_RET_NOTRDY:  Not Ready
 *                    USB_MEDIA_RET_OP_FAIL: Any other failures
 ******************************************************************************/
usb_media_ret_t USB_media_write(uint8_t* p_wbuffer, uint32_t start_block, uint8_t block_count)
{
    usb_media_ret_t result;

    result = gsp_usb_pmsc_media_driver_list->pf_media_write(p_wbuffer, start_block, block_count);
    return result;
} /* End of function USB_media_write() */

/******************************************************************************
 * Function Name: USB_media_ioctl
 * Description  : This function provides a generalized means to pass special
 *                command and control instructions to the media driver and for
 *                the driver to return information.
 * Arguments    : ioctl_cmd -
 *                    Control command code.
 *              : ioctl_data -
 *                    Data transfer buffer
 * Return value : result -
 *                   USB_MEDIA_RET_OK:       Success
 *                   USB_MEDIA_RET_PARERR:   Invalid parameter error
 *                   USB_MEDIA_RET_NOTRDY:   Not Ready
 *                   USB_MEDIA_RET_OP_FAIL:  Any other failures
 ******************************************************************************/
usb_media_ret_t USB_media_ioctl(usb_ioctl_cmd_t ioctl_cmd, void * ioctl_data)
{
    usb_media_ret_t result;

    result = gsp_usb_pmsc_media_driver_list->pf_media_ctrl(ioctl_cmd, ioctl_data);

    return result;
} /* End of function USB_media_ioctl() */

/******************************************************************************
 End Of File
 ******************************************************************************/
