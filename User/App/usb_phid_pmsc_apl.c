/*******************************************************************************
 * File Name    : usb_pcdc_echo_apl.c
 * Description  : USB Peripheral Communications Devices Class Sample Code
 *******************************************************************************/

/*******************************************************************************
 Includes   <System Includes> , "Project Includes"
 ******************************************************************************/
#include <stdio.h>
#include "usb.h"
#include "usb_phid_apl.h"
#include "usb_phid_apl_config.h"

#include "app_event.h"

#include "drv_task.h"
/*******************************************************************************
 Macro definitions
 ******************************************************************************/
#define DATA_LEN    (64)

/*******************************************************************************
 Typedef definitions
 ******************************************************************************/

/*******************************************************************************
 Exported global variables (to be accessed by other files)
 ******************************************************************************/

/*******************************************************************************
 Private global variables and functions
 ******************************************************************************/
static void Usb_Event_Handler(void *arg );

static usb_ctrl_t  ctrl;
static usb_cfg_t   cfg;

static uint8_t gs_data[DATA_LEN];

static uint8_t usbEp0Buf[64];

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
  * Function Name: Usb_Init
  * Description  : Peripheral CDC application main process
  * Arguments    : none
  * Return Value : none
 ******************************************************************************/
void Usb_Init (void)
{
    ctrl.type       = USB_PHID;
    cfg.usb_mode    = USB_PERI;
    /* Descriptor registration */
    cfg.p_usb_reg   = (usb_descriptor_t *)&gs_usb_descriptor;
    USB_Open(&ctrl, &cfg);    /* Initializes the USB module */

    Drv_Task_Regist_Period(0, 1, Usb_Event_Handler, NULL);
}

static void Usb_Event_Handler(void *arg )
{
    /* Loop back between PC(TerminalSoft) and USB MCU */
    switch (USB_GetEvent(&ctrl))
        /* Check application state */
    {
        case USB_STS_CONFIGURED :
        {
            break;
        }
        case USB_STS_WRITE_COMPLETE :
            ctrl.type = USB_PHID;
            USB_Read(&ctrl, gs_data, 64);
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

                    if((uint8_t )ctrl.setup.index == 0x00)
                    {
                        USB_Write(&ctrl, (uint8_t *)g_apl_mouse_report, REPORT_MOUSE_SIZE);
                    }
                    else if((uint8_t )ctrl.setup.index == 0x01)
                    {
                        USB_Write(&ctrl, (uint8_t *)g_apl_keyboard_report, REPORT_KEYBOARD_SIZE);
                    }
                }
                else if (USB_GET_HID_DESCRIPTOR == ctrl.setup.value)
                {
                    /* Configuration Discriptor address set. */
                    ctrl.type = USB_REQUEST;
                    USB_Write(&ctrl, (uint8_t *) &g_apl_configuration[18], 9);	//18, laidi HID Descriptor offset in config Descriptor
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
                if((uint8_t )(ctrl.setup.type >> 8) == 0x09)
                {
                    ctrl.type = USB_REQUEST;
                    USB_Read(&ctrl, usbEp0Buf, 64);
                }
                else if((uint8_t )(ctrl.setup.type >> 8) == 0x01)
                {
                    Drv_Event_Put(APP_EVENT_USB_GET_REPORT, (uint8_t *)&ctrl.setup, sizeof(usb_setup_t));
                }
                else
                {
                    ctrl.status = USB_ACK;
                    ctrl.type = USB_REQUEST;
                    USB_Write(&ctrl, (uint8_t*)USB_NULL, (uint32_t)USB_NULL);
                }
            }

            break;

        case USB_STS_REQUEST_COMPLETE : /* Complete Class Request */
            if((uint8_t )(ctrl.setup.type >> 8) == 0x09)
            {
                Drv_Event_Put(APP_EVENT_USB_SET_REPORT, usbEp0Buf, 64);
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
} /* End of function Usb_Init */

void Usb_Ctrl_Send(uint8_t *buf, uint8_t length )
{
    uint8_t i;

    for(i=0;i<length;i++)
    {
        usbEp0Buf[i] = buf[i];
    }

    ctrl.type = USB_REQUEST;
    
    USB_Write(&ctrl, usbEp0Buf, length);	
}

void Usb_Interupt_Send(void )
{
    static uint8_t sendBuf[64] = {0};
    
    for(int i=0;i<8;i++)
    {
        sendBuf[i] = 0;
    }
    sendBuf[0] = REPORT_ID_MOUSE;
    ctrl.type = USB_PHID;
    USB_Write(&ctrl, sendBuf, 7);
}

/******************************************************************************
 End  Of File
 ******************************************************************************/

