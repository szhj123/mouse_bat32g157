/*******************************************************************************
 * File Name    : usb_pcdc_echo_apl.c
 * Description  : USB Peripheral Communications Devices Class Sample Code
 *******************************************************************************/

/*******************************************************************************
 Includes   <System Includes> , "Project Includes"
 ******************************************************************************/
#include <stdio.h>
#include "usb.h"
#include "usb_pcdc_apl.h"
#include "usb_pcdc_apl_config.h"
#include "usb_pmsc_apl.h"

#if OPERATION_MODE == USB_ECHO
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

//static void usb_pin_setting (void);
static uint8_t  gs_buf[DATA_LEN];
static usb_pcdc_linecoding_t gs_line_coding;

const static usb_descriptor_t gs_usb_descriptor =
{
    g_apl_device,                   /* Pointer to the device descriptor */
    g_apl_configuration,            /* Pointer to the configuration descriptor for Full-speed */
    gp_apl_string_table,             /* Pointer to the string descriptor table */
    NUM_STRING_DESCRIPTOR
};

static void     media_driver_init(void);

/******************************************************************************
  * Function Name: usb_main
  * Description  : Peripheral CDC application main process
  * Arguments    : none
  * Return Value : none
 ******************************************************************************/
usb_ctrl_t  ctrl;
usb_cfg_t   cfg;
void usb_main (void)
{
    media_driver_init ();
	
    ctrl.type       = USB_PCDC;
    cfg.usb_mode    = USB_PERI;
    /* Descriptor registration */
    cfg.p_usb_reg   = (usb_descriptor_t *)&gs_usb_descriptor;
    USB_Open(&ctrl, &cfg);

    /* Loop back between PC(TerminalSoft) and USB MCU */
    while (1)
    {
        switch (USB_GetEvent(&ctrl))
        {
            case USB_STS_CONFIGURED :
            case USB_STS_WRITE_COMPLETE :
                ctrl.type = USB_PCDC;
                USB_Read(&ctrl, gs_buf, DATA_LEN);
                break;

            case USB_STS_READ_COMPLETE :
                ctrl.type = USB_PCDC;
                USB_Write(&ctrl, gs_buf, ctrl.size);
                break;

            case USB_STS_REQUEST : /* Receive Class Request */
                if (USB_PCDC_SET_LINE_CODING == (ctrl.setup.type & USB_BREQUEST))
                {
                    ctrl.type = USB_REQUEST;
                    /* Receive Line coding parameter */
                    USB_Read(&ctrl, (uint8_t *) &gs_line_coding, LINE_CODING_LENGTH);
                }
                else if (USB_PCDC_GET_LINE_CODING == (ctrl.setup.type & USB_BREQUEST))
                {
                    ctrl.type = USB_REQUEST;
                    /* Send Line coding parameter */
                    USB_Write(&ctrl, (uint8_t *) &gs_line_coding, LINE_CODING_LENGTH);
                }else if(USB_PCDC_SET_CONTROL_LINE_STATE == (ctrl.setup.type & USB_BREQUEST))
								{
                    ctrl.type = USB_REQUEST;
                    ctrl.status = USB_ACK;
                    USB_Write(&ctrl, (uint8_t*)USB_NULL, (uint32_t)USB_NULL);
								}
                else
                {
                    ctrl.type = USB_REQUEST;
                    ctrl.status = USB_ACK;
                    USB_Write(&ctrl, (uint8_t*)USB_NULL, (uint32_t)USB_NULL);
                }

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
} /* End of function usb_main() */

#endif  /* OPERATION_MODE == USB_ECHO */


/******************************************************************************
  * Function Name: media_driver_init
  * Description  : Initializeation Media driver
  * Arguments    : none
  * Return Value : none
 ******************************************************************************/
static void media_driver_init (void)
{
    USB_media_initialize(&g_ram_mediadriver); /* Register the media device driver. */
    USB_media_open();                         /* Start up the  media device hardware. */

} /* End of function media_driver_init */


/******************************************************************************
 End  Of File
 ******************************************************************************/

