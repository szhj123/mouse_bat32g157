/******************************************************************************
 * File Name    : usb_phid_keyboard_apl.c
 * Description  : USB HID application code
 ******************************************************************************/

/*******************************************************************************
 Includes   <System Includes> , "Project Includes"
 ******************************************************************************/

#include "usb_phid_mini_if.h"
#include "usb_basic_mini_if.h"
#include "usb_phid_apl.h"
#include "usb_phid_apl_config.h"
#include "BAT32G157.h"

#if OPERATION_MODE == USB_KEYBOARD

/*******************************************************************************
 Macro definitions
 ******************************************************************************/

#define DATA_LEN                (8)
#define HID_DESCRIPTOR_SIZE     (9)
#define REPORT_DESCRIPTOR_SIZE  (76)
#define REPORT_DESCRIPTOR_CUSTOM_SIZE (32)
#define HID_DESCRIPTOR_INDEX    (18)

/*******************************************************************************
 Typedef definitions
 ******************************************************************************/

/*******************************************************************************
 Exported global variables (to be accessed by other files)
 ******************************************************************************/

/*******************************************************************************
 Private global variables and functions
 ******************************************************************************/
static uint8_t  gs_idle = 0;

static void Usb_Event_Handler(void *arg );

const static usb_descriptor_t gs_usb_descriptor =
{
    /* Device descriptor */
    (uint8_t *)g_apl_device,
    /* Configuration descriptor  */
    (uint8_t *)g_apl_configuration,
    /* Strign descriptor */
    (uint8_t **)gp_apl_string_table,
    NUM_STRING_DESCRIPTOR
};

usb_ctrl_t   ctrl;
usb_cfg_t    cfg;
uint8_t      *p_idle_value;
usb_info_t   info;
usb_err_t    ret_code = USB_SUCCESS;

/******************************************************************************
  * Function Name: Usb_Init
  * Description  : Peripheral HID application main process
  * Arguments    : none
  * Return Value : none
 ******************************************************************************/

void Usb_Init (void)
{
    ctrl.type       = USB_PHID;
    cfg.usb_mode    = USB_PERI;
    /* Descriptor registration */
    cfg.p_usb_reg     = (usb_descriptor_t *)&gs_usb_descriptor;
    USB_Open (&ctrl, &cfg);       /* Initializes the USB module */

    //Drv_Timer_Register_Period(Usb_Event_Handler, 0, 1, NULL);
}

static void Usb_Event_Handler(void *arg )
{    
    switch (USB_GetEvent(&ctrl))
    {
        case USB_STS_CONFIGURED :
            #if defined(USE_LPW)
                /* Do Nothing */
            #endif /* defined(USE_LPW) */
            break;

        case USB_STS_WRITE_COMPLETE :

            break;

        case USB_STS_REQUEST : /* Receive Class Request */
            if (USB_REQUEST_TYPE_CLASS == (ctrl.setup.type & USB_REQUEST_TYPE_CLASS))
            {
                if (USB_SET_REPORT == (ctrl.setup.type & USB_BREQUEST))
                {
                    uint8_t buf[2];

                    /* Get the NumLock data (NumLock data is not used) */
                    USB_Read(&ctrl, (uint8_t *)buf, 2);
                }

                if (USB_SET_IDLE == (ctrl.setup.type & USB_BREQUEST))
                {
                    /* Get SetIdle value */
                    p_idle_value = (uint8_t *)&ctrl.setup.value;
                    #if USB_CFG_ENDIAN == USB_CFG_LITTLE
                    gs_idle = p_idle_value[1];
                    #else   /* USB_CFG_ENDIAN == USB_CFG_LITTLE */
                    gs_idle = p_idle_value[0];
                    #endif  /* USB_CFG_ENDIAN == USB_CFG_LITTLE */
                    ctrl.type = USB_REQUEST;
                    ctrl.status = USB_ACK;
                    USB_Write(&ctrl, (uint8_t*)USB_NULL, (uint32_t)USB_NULL);
                }

                if (USB_GET_IDLE == (ctrl.setup.type & USB_BREQUEST))
                {
                    ctrl.type = USB_REQUEST;
                    USB_Write(&ctrl, &gs_idle, 1);
                }
                else if (USB_SET_PROTOCOL == (ctrl.setup.type & USB_BREQUEST))
                {
                    ctrl.type = USB_REQUEST;
                    ctrl.status = USB_ACK;
                    USB_Write(&ctrl, (uint8_t*)USB_NULL, (uint32_t)USB_NULL);
                }
                else if (USB_GET_PROTOCOL == (ctrl.setup.type & USB_BREQUEST))
                {
                    /* Do Nothing */
                }
                else
                {
                    /* Do Nothing */
                }
            }
            else
            {
                if (USB_GET_DESCRIPTOR == (ctrl.setup.type & USB_BREQUEST))
                {
                    if (USB_GET_REPORT_DESCRIPTOR == ctrl.setup.value)
                    {
                        /* Send Report descriptor */
                        ctrl.type = USB_REQUEST;

                        USB_Write (&ctrl, (uint8_t *)g_apl_report, REPORT_DESCRIPTOR_SIZE);

                    }
                    else if (USB_GET_HID_DESCRIPTOR == ctrl.setup.value)
                    {
                        /* HID Discriptor address set. */
                        ctrl.type = USB_REQUEST;
                        USB_Write (&ctrl, (uint8_t *) &g_apl_configuration[HID_DESCRIPTOR_INDEX],
                                   HID_DESCRIPTOR_SIZE);
                    }
                    else
                    {
                        /* Do Nothing */
                    }
                }

                #if defined(USE_LPW)
                    /* Do Nothing */
                #endif /* defined(USE_LPW) */
            }

            break;

        case USB_STS_REQUEST_COMPLETE : /* Complete Class Request */
            if (USB_REQUEST_TYPE_CLASS == (ctrl.setup.type & USB_REQUEST_TYPE_CLASS))
            {
                if (USB_SET_IDLE == (ctrl.setup.type & USB_BREQUEST))
                {
                    /* Do Nothing */
                }
                else if (USB_SET_PROTOCOL == (ctrl.setup.type & USB_BREQUEST))
                {
                    /* Do Nothing */
                }
                else
                {
                    /* Do Nothing */
                }
            }

            break;

        case USB_STS_SUSPEND:
            #if defined(USE_LPW)
                /* Do Nothing */
            #endif /* defined(USE_LPW) */
            break;

        case USB_STS_DETACH:
            #if defined(USE_LPW)
                /* Do Nothing */
            #endif /* defined(USE_LPW) */
            break;

        case USB_STS_NONE : /* No event */
            ret_code = USB_GetInformation(&info);

            if (USB_SUCCESS == ret_code)
            {
                if (USB_STS_SUSPEND == info.status)
                {
                    #if !defined(USE_LPW)
                        /* Do Nothing */
                    #endif /* !defined(USE_LPW) */
                }
                else if (USB_STS_CONFIGURED == info.status)
                {
                }
                else
                {
                    /* Do Nothing */
                }
            }

            break;

        default:
            break;
    }
} /* End of function Usb_Init */

void usb_cpu_delay_1us (uint16_t time)
{
    uint16_t sf_cnt;
    sf_cnt = time * 20;

    while(sf_cnt)
    {
        sf_cnt --;
    }
}

void usb_cpu_delay_xms(uint32_t n)
{
    while(n--)
    {
        usb_cpu_delay_1us(1000);
    }
}



#endif  /* OPERATION_MODE == USB_KEYBOARD */

/******************************************************************************
 End  Of File
 ******************************************************************************/

