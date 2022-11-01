/***********************************************************************************************************************
 * File Name    : usb_hstorage_driver_api.c
 * Description  : USB Host Storage Driver API
 ***********************************************************************************************************************/

/**********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 ***********************************************************************************************************************/

#include "usb_hmsc_mini_if.h"

#if defined(USB_CFG_HMSC_USE)

/***********************************************************************************************************************
Macro definitions
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 Private global variables and functions
 ***********************************************************************************************************************/


/***********************************************************************************************************************
 Exported global variables (to be accessed by other files)
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 Private global variables and functions
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: usb_hmsc_StrgReadSector
 * Description  : Releases drive
 * Arguments    : uint16_t side        : Side(no use)
                : uint8_t  *p_buff     : Buffer address
                : uint32_t secno       : Sector number
                : uint16_t seccnt      : Sector count
                : uint32_t trans_byte  : Trans byte
 * Return Value : uint16_t             : [DONE/ERROR]
 ***********************************************************************************************************************/
uint16_t usb_hmsc_StrgReadSector (uint16_t side, uint8_t *p_buff, uint32_t secno, uint16_t seccnt,
        uint32_t trans_byte)
{
    uint16_t result;

    /* Device Status */
    if (USB_HMSC_DEV_ATT != usb_hmsc_get_device_status())
    {
        return (USB_ERROR);
    }

    result = usb_hmsc_read10(p_buff, secno, seccnt, trans_byte);
#if (BSP_CFG_RTOS_USED != 0)    /* Use RTOS */
    if (USB_HMSC_OK == result)
    {
        result = USB_OK;
    }
    else
    {
        usb_hmsc_error_process(result);

        result = USB_ERROR;
    }
#endif /* (BSP_CFG_RTOS_USED != 0) */

    return (result);
}
/***********************************************************************************************************************
 End of function usb_hmsc_StrgReadSector
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: USB_HmscStrgWriteSector
 * Description  : Writes sector information
 * Arguments    : uint16_t side        : Side(no use)
                : uint8_t  *p_buff     : Buffer address
                : uint32_t secno       : Sector number
                : uint16_t seccnt      : Sector count
                : uint32_t trans_byte  : Trans byte
 * Return Value : uint16_t             : [DONE/ERROR]
 ***********************************************************************************************************************/
uint16_t USB_HmscStrgWriteSector (uint16_t side, uint8_t *p_buff, uint32_t secno, uint16_t seccnt,
        uint32_t trans_byte)
{
    uint16_t result;

    /* Device Status */
    if (USB_HMSC_DEV_ATT != usb_hmsc_get_device_status())
    {
        return (USB_ERROR);
    }

    result = usb_hmsc_write10(p_buff, secno, seccnt, trans_byte);
#if (BSP_CFG_RTOS_USED != 0)    /* Use RTOS */
    if (USB_HMSC_OK == result)
    {
        result = USB_OK;
    }
    else
    {
        usb_hmsc_error_process(result);

        result = USB_ERROR;
    }
#endif /* (BSP_CFG_RTOS_USED != 0) */

    return (result);
}
/***********************************************************************************************************************
 End of function USB_HmscStrgWriteSector
 ***********************************************************************************************************************/

#endif /* defined(USB_CFG_HMSC_USE) */
/***********************************************************************************************************************
 End  Of File
 ***********************************************************************************************************************/
