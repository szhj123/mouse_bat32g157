/******************************************************************************
 * File Name    : usb_pmsc_apl.c
 * Description  : USB Peripheral Mass-Storage Sample Code
 ******************************************************************************/
/*******************************************************************************
 * History : DD.MM.YYYY Version  Description
 *         : 01.09.2014 1.00     First Release
 *         : 01.06.2015 1.01     Added RX231.
 *         : 30.11.2018 1.10     Supporting Smart Configurator
 ******************************************************************************/

/******************************************************************************
 Includes   <System Includes> , "Project Includes"
 ******************************************************************************/
#include "usb_pmsc_apl.h"

/******************************************************************************
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

static usb_descriptor_t gs_usb_descriptor =
{
    g_apl_device,
    g_apl_configuration,
    gp_apl_string_table,
    NUM_STRING_DESCRIPTOR
};

static void     usb_pin_setting(void);
static void     media_driver_init(void);
static void     apl_init(void);


/******************************************************************************
  * Function Name: usb_main
  * Description  : Start task CSTD; "common" basic USB low level task.
  * Arguments    : none
  * Return Value : none
 ******************************************************************************/
void usb_main (void)
{
    usb_ctrl_t  ctrl;
    usb_cfg_t   cfg;

    apl_init();                 /* Application program initialization */
    usb_pin_setting ();         /* USB MCU pin setting */

    media_driver_init ();

    ctrl.type       = USB_PMSC;
    cfg.usb_mode    = USB_PERI;
    cfg.p_usb_reg     = &gs_usb_descriptor;
    USB_Open (&ctrl, &cfg);   /* Initializes the USB module */

    while (1)
    {
        switch (USB_GetEvent (&ctrl))
        {
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

/******************************************************************************
  * Function Name: usb_pin_setting
  * Description  : USB port mode and Switch mode Initialize
  * Arguments    : none
  * Return Value : none
 ******************************************************************************/
static void usb_pin_setting (void)
{
} /* End of function usb_pin_setting */

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
 * Function Name: apl_init
 * Description  : Application Initialize
 * Argument     : none
 * Return Value : none
 ******************************************************************************/
static void apl_init (void)
{
    /* Do Nothing */
} /* End of function apl_init */


/******************************************************************************
 End  Of File
 ******************************************************************************/
