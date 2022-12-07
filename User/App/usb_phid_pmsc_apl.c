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

static uint8_t usbEp0InBuf[64];
static uint8_t usbEp1InBuf[8];
static uint8_t usbEp2InBuf[8];
static uint8_t usbEp3OutBuf[64];

static uint8_t usbEp3OutFlag;

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
            Usb_Ep3_Clr_Out_Flag();
            ctrl.type = USB_PHID;
            USB_Read(&ctrl, usbEp3OutBuf, 64);
            break;
        }
        case USB_STS_WRITE_COMPLETE :
            //USB IN 中断输入完成后，会进入这里
            break;

        case USB_STS_READ_COMPLETE :
            Usb_Ep3_Clr_Out_Flag();
            
            Drv_Event_Put(APP_EVENT_USB_INTERUPT_OUT, usbEp3OutBuf, sizeof(usbEp3OutBuf));
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
                    USB_Read(&ctrl, usbEp0InBuf, 64);
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
                Drv_Event_Put(APP_EVENT_USB_SET_REPORT, usbEp0InBuf, 64);
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

void Usb_Ep0_In(uint8_t *buf, uint8_t length )
{
    uint8_t i;

    if(Usb_Ep3_Get_Out_Flag())
        return ;

    for(i=0;i<length;i++)
    {
        usbEp0InBuf[i] = buf[i];
    }

    ctrl.type = USB_REQUEST;
    
    USB_Write(&ctrl, usbEp0InBuf, length);	
}

void Usb_Ep1_In(uint8_t *buf, uint8_t length )
{    
    uint8_t i;

    if(Usb_Ep3_Get_Out_Flag())
        return ;
    
    for(i=0;i<length;i++)
    {
        usbEp1InBuf[i] = buf[i];
    }
    
    ctrl.type = USB_PHID;
    
    USB_Write(&ctrl, usbEp1InBuf, length);
}

void Usb_Ep2_In(uint8_t *buf, uint8_t length )
{
    uint8_t i;

    if(Usb_Ep3_Get_Out_Flag())
        return ;
    
    for(i=0;i<length;i++)
    {
        usbEp2InBuf[i] = buf[i];
    }
    
    ctrl.type = USB_PHID;
    
    USB_Write(&ctrl, usbEp2InBuf, length);
}

void Usb_Ep3_Out(void )
{    
    Usb_Ep3_Set_Out_Flag();

    ctrl.type = USB_PHID;
    
    USB_Read(&ctrl, usbEp3OutBuf, 64);
}

void Usb_Ep3_Set_Out_Flag(void )
{
    usbEp3OutFlag = 1;
}

uint8_t Usb_Ep3_Get_Out_Flag(void )
{
    return usbEp3OutFlag;
}

void Usb_Ep3_Clr_Out_Flag(void )
{
    usbEp3OutFlag = 0;
}

/******************************************************************************
 End  Of File
 ******************************************************************************/

