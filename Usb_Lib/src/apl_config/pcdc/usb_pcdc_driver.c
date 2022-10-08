/******************************************************************************
 * File Name    : usb_pcdc_driver.c
 * Description  : USB PCDC Driver code
 ******************************************************************************/

/******************************************************************************
 Includes   <System Includes> , "Project Includes"
 ******************************************************************************/

#include "usb_basic_mini_if.h"
#include "usb_pcdc_mini_if.h"
#include "usb_typedef.h"
#include "usb_extern.h"
#include "usb_pcdc.h"
#include "usb_bitdefine.h"

/******************************************************************************
 Macro definitions
 ******************************************************************************/
extern uint16_t g_usb_pstd_is_connected; /* Peri CDC application enable */

/*******************************************************************************
 Typedef definitions
 ******************************************************************************/

/*******************************************************************************
 Exported global variables (to be accessed by other files)
 ******************************************************************************/

/*******************************************************************************
 Private global variables and functions
 ******************************************************************************/

/******************************************************************************
  * Function Name: usb_pcdc_read_complete
  * Description  : CallBack Function
  * Arguments    : usb_utr_t   *p_mess  : Pointer to usb_utr_t structure
                 : uint16_t     data1   : Not used
                 : uint16_t     data2   : Not used
 * Return Value : none
 ******************************************************************************/
void usb_pcdc_read_complete (usb_putr_t *p_mess, uint16_t data1, uint16_t data2)
{
    usb_ctrl_t ctrl;

    if ( USB_TRUE == g_usb_pstd_is_connected)
    {
        /* Set Receive data length */
        ctrl.size = g_usb_read_request_size[p_mess->keyword] - p_mess->tranlen;
        ctrl.pipe = p_mess->keyword;    /* Pipe number setting */
        ctrl.type = USB_PCDC;           /* Device class setting  */

        switch (p_mess->status)
        {
            case USB_DATA_OK :
                ctrl.status = USB_SUCCESS;
                break;

            case USB_DATA_SHT :
                ctrl.status = USB_ERR_SHORT;
                break;

            case USB_DATA_OVR :
                ctrl.status = USB_ERR_OVER;
                break;

            case USB_DATA_ERR :
            default :
                ctrl.status = USB_ERR_NG;
                break;
        }

        usb_cstd_set_event(USB_STS_READ_COMPLETE, &ctrl);
    }
} /* End of function usb_pcdc_read_complete() */

/******************************************************************************
  * Function Name: usb_pcdc_write_complete
  * Description  : CallBack Function
  * Arguments    : usb_utr_t   *p_mess  : Pointer to usb_utr_t structure
                 : uint16_t     data1   : Not used
                 : uint16_t     data2   : Not used
 * Return Value : none
 ******************************************************************************/
void usb_pcdc_write_complete (usb_putr_t *p_mess, uint16_t data1, uint16_t data2)
{
    usb_ctrl_t ctrl;

    if ( USB_TRUE == g_usb_pstd_is_connected)
    {
        ctrl.pipe = p_mess->keyword; /* Pipe number setting */

        if (USB_CFG_PCDC_BULK_IN == ctrl.pipe)
        {
            ctrl.type = USB_PCDC; /* CDC Data class  */
        }

        /* USB_CFG_PCDC_INT_IN */
        else
        {
            ctrl.type = USB_PCDCC; /* CDC Control class  */
        }

        if (USB_DATA_NONE == p_mess->status)
        {
            ctrl.status = USB_SUCCESS;
        }
        else
        {
            ctrl.status = USB_ERR_NG;
        }

        usb_cstd_set_event(USB_STS_WRITE_COMPLETE, &ctrl);
    }
} /* End of function usb_pcdc_write_complete() */

/******************************************************************************
 End  Of File
 ******************************************************************************/
