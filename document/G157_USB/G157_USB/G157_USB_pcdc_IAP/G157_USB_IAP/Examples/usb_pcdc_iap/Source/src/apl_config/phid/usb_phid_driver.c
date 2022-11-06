/******************************************************************************
 * File Name    : usb_phid_driver.c
 * Description  : USB HID application code
 ******************************************************************************/

/******************************************************************************
 Includes   <System Includes> , "Project Includes"
 ******************************************************************************/

#include "usb_phid_mini_if.h"
#include "usb_basic_mini_if.h"
#include "usb_typedef.h"
#include "usb_extern.h"
#include "usb_bitdefine.h"
//#include "usb_reg_access.h"
#include "usb_phid.h"

/*******************************************************************************
 Macro definitions
 ******************************************************************************/

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
  * Function Name: usb_phid_write_complete
  * Description  : CallBack Function
  * Arguments    : usb_utr_t   *p_mess  : Pointer to usb_utr_t structure
                 : uint16_t     data1   : Not used
                 : uint16_t     data2   : Not used
 * Return Value : none
 ******************************************************************************/
void usb_phid_write_complete (usb_putr_t *p_mess, uint16_t data1, uint16_t data2)
{
    usb_ctrl_t ctrl;

    ctrl.pipe   = p_mess->keyword;                    /* Pipe number setting */
    ctrl.type   = USB_PHID;                           /* PHID class  */
    ctrl.type   = USB_PHID;                           /* HID Data class  */

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
/******************************************************************************
 End of function usb_phid_write_complete
 ******************************************************************************/

/******************************************************************************
  * Function Name: usb_phid_read_complete
  * Description  : CallBack Function
  * Arguments    : usb_utr_t   *p_mess  : Pointer to usb_utr_t structure
                 : uint16_t     data1   : Not used
                 : uint16_t     data2   : Not used
 * Return Value : none
 ******************************************************************************/
void usb_phid_read_complete (usb_putr_t *p_mess, uint16_t data1, uint16_t data2)
{
    usb_ctrl_t ctrl;

    /* Set Receive data length */
    ctrl.size   = g_usb_read_request_size[p_mess->keyword] - p_mess->tranlen;
    ctrl.pipe   = p_mess->keyword;                  /* Pipe number setting */

    ctrl.type   = USB_PHID;                         /* Device class setting  */

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
/******************************************************************************
 End of function usb_phid_read_complete
 ******************************************************************************/


/******************************************************************************
 End  Of File
 ******************************************************************************/
