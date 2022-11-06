/******************************************************************************
 * File Name    : usb_phid_echo_apl.c
 * Description  : USB HID application code
 ******************************************************************************/

/******************************************************************************
 Includes   <System Includes> , "Project Includes"
 ******************************************************************************/

#include "usb_phid_apl.h"
#include "usb_phid_apl_config.h"

#if OPERATION_MODE == USB_ECHO
/******************************************************************************
 Macro definitions
 ***************************************************************************#***/
#define DATA_LEN    (64)

/******************************************************************************
 Private global variables and functions
 ******************************************************************************/
static uint8_t gs_data[DATA_LEN];

const static usb_descriptor_t gs_usb_descriptor =
{
    /* Device descriptor */
    (uint8_t *)g_apl_device,
    /* Configuration descriptor */
    (uint8_t *)g_apl_configuration,
    /* String descriptor */
    (uint8_t **)gp_apl_string_table,
    NUM_STRING_DESCRIPTOR
};

/******************************************************************************
Exported global functions (to be accessed by other files)
 ******************************************************************************/

/******************************************************************************
  * Function Name: usb_main
  * Description  : Peripheral HID application main process
  * Arguments    : none
  * Return Value : none
 ******************************************************************************/
void usb_main (void)
{
    usb_ctrl_t  ctrl;
    usb_cfg_t   cfg;

    ctrl.type       = USB_PHID;
    cfg.usb_mode    = USB_PERI;
    /* Descriptor registration */
    cfg.p_usb_reg   = (usb_descriptor_t *)&gs_usb_descriptor;
    USB_Open(&ctrl, &cfg);    /* Initializes the USB module */

    /* Loop back between PC(TerminalSoft) and USB MCU */
    while (1)
    {
        switch (USB_GetEvent(&ctrl))
            /* Check application state */
        {
            case USB_STS_CONFIGURED :
            case USB_STS_WRITE_COMPLETE :
                ctrl.type = USB_PHID;
                USB_Read(&ctrl, gs_data, DATA_LEN);
                break;

            case USB_STS_READ_COMPLETE :
                ctrl.type = USB_PHID;
                USB_Write(&ctrl, gs_data, ctrl.size);
                break;

            case USB_STS_REQUEST : /* Receive Class Request */
                if (USB_GET_DESCRIPTOR == (ctrl.setup.type & USB_BREQUEST))
                {
                    if (USB_GET_REPORT_DESCRIPTOR == ctrl.setup.value)
                    {
                        /* Send ReportDescriptor */
                        ctrl.type = USB_REQUEST;
                        USB_Write(&ctrl, (uint8_t *)g_apl_report, 34);
                    }
                    else if (USB_GET_HID_DESCRIPTOR == ctrl.setup.value)
                    {
                        /* Configuration Discriptor address set. */
                        ctrl.type = USB_REQUEST;
                        USB_Write(&ctrl, (uint8_t *) &g_apl_configuration[18], 9);
                    }
                    else
                    {
                        ctrl.status = USB_STALL;
                        ctrl.type = USB_REQUEST;
                        USB_Write(&ctrl, (uint8_t*)USB_NULL, (uint32_t)USB_NULL);
                    }
                }
                else
                {
                    ctrl.status = USB_STALL;
                    ctrl.type = USB_REQUEST;
                    USB_Write(&ctrl, (uint8_t*)USB_NULL, (uint32_t)USB_NULL);
                }

                break;

            case USB_STS_REQUEST_COMPLETE : /* Complete Class Request */
                break;

            case USB_STS_SUSPEND :
            case USB_STS_DETACH :
                #if defined(USE_LPW)
                    /* Do Nothing */
                #endif /* defined(USE_LPW) */
                break;

            default :
                break;
        }
    }
} /* End of function usb_main */


#endif  /* OPERATION_MODE == USB_ECHO */

/******************************************************************************
 End  Of File
 ******************************************************************************/

