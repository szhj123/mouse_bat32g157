/******************************************************************************
 * File Name    : usb_puac_apl.c
 * Description  : USB UAC application code
 ******************************************************************************/

/*******************************************************************************
 Includes   <System Includes> , "Project Includes"
 ******************************************************************************/

#include "usb_puac_mini_if.h"
#include "usb_basic_mini_if.h"
#include "usb_puac_apl.h"
#include "usb_puac_apl_config.h"
#include "usbd_audio.h"

#include "BAT32G157.h"


/*******************************************************************************
 Macro definitions
 ******************************************************************************/

//#define DATA_LEN                (8)
//#define HID_DESCRIPTOR_SIZE     (9)
//#define REPORT_DESCRIPTOR_SIZE  (76)
//#define HID_DESCRIPTOR_INDEX    (18)

/*******************************************************************************
 Typedef definitions
 ******************************************************************************/

/*******************************************************************************
 Exported global variables (to be accessed by other files)
 ******************************************************************************/

/*******************************************************************************
 Private global variables and functions
 ******************************************************************************/
/* Global variables for Audio class */
volatile uint32_t g_usbd_UsbAudioState = 0;

volatile uint8_t g_usbd_RecMute       = 0x01;     /* Record MUTE control. 0 = normal. 1 = MUTE */
volatile int16_t g_usbd_RecVolumeL    = 0x1000;   /* Record left channel volume. Range is -32768 ~ 32767 */
volatile int16_t g_usbd_RecVolumeR    = 0x1000;   /* Record right channel volume. Range is -32768 ~ 32767 */
volatile int16_t g_usbd_RecMaxVolume  = 0x7FFF;
volatile int16_t g_usbd_RecMinVolume  = 0x8000;
volatile int16_t g_usbd_RecResVolume  = 0x400;

volatile uint8_t g_usbd_PlayMute      = 0x01;     /* Play MUTE control. 0 = normal. 1 = MUTE */
volatile int16_t g_usbd_PlayVolumeL   = 0x1000;   /* Play left channel volume. Range is -32768 ~ 32767 */
volatile int16_t g_usbd_PlayVolumeR   = 0x1000;   /* PLay right channel volume. Range is -32768 ~ 32767 */
volatile int16_t g_usbd_PlayMaxVolume = 0x7FFF;
volatile int16_t g_usbd_PlayMinVolume = 0x8000;
volatile int16_t g_usbd_PlayResVolume = 0x400;

//static volatile uint8_t g_u8RecEn = 0;
//static volatile uint8_t g_u8PlayEn = 0;      /* To indicate data is output to I2S */
//static volatile int32_t g_i32AdjFlag = 0;    /* To indicate current I2S frequency adjustment status */



usb_ctrl_t  Ctrl;
usb_cfg_t   Cfg;

uint8_t iistxbuff[2][512],iisrxbuff[512];
extern volatile uint32_t iisdmacount;


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

/******************************************************************************
  * Function Name: usb_main
  * Description  : Peripheral HID application main process
  * Arguments    : none
  * Return Value : none
 ******************************************************************************/
void usb_main (void)
{
//    usb_ctrl_t  Ctrl;
//    usb_cfg_t   cfg;
//    display_type     dsp_type;
//    uint8_t     *p_idle_value;
//    usb_info_t  info;
//    usb_err_t   ret_code = USB_SUCCESS;

//    key_input_init();
    Ctrl.type       = USB_PUAC;//USB_PHID;
    Cfg.usb_mode    = USB_PERI;
    /* Descriptor registration */
    Cfg.p_usb_reg     = (usb_descriptor_t *)&gs_usb_descriptor;
    USB_Open (&Ctrl, &Cfg);       /* Initializes the USB module */

    while (1)
    {
        switch (USB_GetEvent(&Ctrl))
        {
            case USB_STS_CONFIGURED :
								
                break;
						
						case USB_STS_READ_COMPLETE :
								
								Ctrl.type = USB_PUAC;
                
								if(iisdmacount&0x01)
								{
									
									USB_Read(&Ctrl, (uint8_t *)&iistxbuff[0][0], EP3_MAX_PKT_SIZE);
								}
								else
								{
									
									USB_Read(&Ctrl, (uint8_t *)&iistxbuff[1][0], EP3_MAX_PKT_SIZE);
								}
								break;
						
            case USB_STS_WRITE_COMPLETE :

                Ctrl.type = USB_PUAC;
                USB_Write(&Ctrl, (uint8_t *)iisrxbuff, EP3_MAX_PKT_SIZE);
								
                break;

            case USB_STS_REQUEST : /* Receive Class Request */
                if (USB_REQUEST_TYPE_CLASS == (Ctrl.setup.type & USB_REQUEST_TYPE_CLASS))
                {


		if((Ctrl.setup.type&0xFF) & 0x80)//(buf[0] & 0x80)    /* request data transfer direction */
    {
        // Device to host
        switch((Ctrl.setup.type & USB_BREQUEST)>>8)//(buf[1])
        {
            case UAC_GET_CUR:
            {
                switch(Ctrl.setup.value>>8)//(buf[3])
                {
                    case MUTE_CONTROL:
                    {
												Ctrl.type = USB_REQUEST;
                        if(REC_FEATURE_UNITID == (Ctrl.setup.index>>8))//buf[5])
                            USB_Write(&Ctrl, (uint8_t*)&g_usbd_RecMute, 1);//M8(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0)) = g_usbd_RecMute;
                        else if(PLAY_FEATURE_UNITID == (Ctrl.setup.index>>8))//buf[5])
                            USB_Write(&Ctrl, (uint8_t*)&g_usbd_PlayMute, 1);//M8(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0)) = g_usbd_PlayMute;
												
                        /* Data stage */
//                        USBD_SET_DATA1(EP0);
//                        USBD_SET_PAYLOAD_LEN(EP0, 1);
                        break;
                    }
                    case VOLUME_CONTROL:
                    {
                        if(REC_FEATURE_UNITID == (Ctrl.setup.index>>8))//buf[5])
                        {
														Ctrl.type = USB_REQUEST;
                            /* Left or right channel */
                            if((Ctrl.setup.value&0xFF)==1)//if(buf[2] == 1)
                            {
//                                M8(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0)) = g_usbd_RecVolumeL;
//                                M8(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0) + 1) = g_usbd_RecVolumeL >> 8;
																	USB_Write(&Ctrl, (uint8_t*)&g_usbd_RecVolumeL, 2);
                            }
                            else
                            {
//                                M8(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0)) = g_usbd_RecVolumeR;
//                                M8(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0) + 1) = g_usbd_RecVolumeR >> 8;
																	USB_Write(&Ctrl, (uint8_t*)&g_usbd_RecVolumeR, 2);
                            }

                        }
                        else if(PLAY_FEATURE_UNITID == (Ctrl.setup.index>>8))//buf[5])
                        {
														Ctrl.type = USB_REQUEST;
                            /* Left or right channel */
                            if((Ctrl.setup.value&0xFF)==1)//if(buf[2] == 1)
                            {
//                                M8(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0)) = g_usbd_PlayVolumeL;
//                                M8(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0) + 1) = g_usbd_PlayVolumeL >> 8;
																	USB_Write(&Ctrl, (uint8_t*)&g_usbd_RecVolumeL, 2);
                            }
                            else
                            {
//                                M8(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0)) = g_usbd_PlayVolumeR;
//                                M8(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0) + 1) = g_usbd_PlayVolumeR >> 8;
																	USB_Write(&Ctrl, (uint8_t*)&g_usbd_RecVolumeR, 2);
                            }
                        }
                        /* Data stage */
//                        USBD_SET_DATA1(EP0);
//                        USBD_SET_PAYLOAD_LEN(EP0, 2);
                        break;
                    }
                    default:
                    {
                        /* Setup error, stall the device */
//                        USBD_SetStall(0);
												Ctrl.type = USB_REQUEST;
                        Ctrl.status = USB_STALL;
                        USB_Write(&Ctrl, (uint8_t*)USB_NULL, (uint32_t)USB_NULL);
												break;
                    }
                }
                // Trigger next Control Out DATA1 Transaction.
                /* Status stage */
//                USBD_PrepareCtrlOut(0, 0);
                break;
            }

            case UAC_GET_MIN:
            {
                switch(Ctrl.setup.value>>8)//(buf[3])
                {
										
                    case VOLUME_CONTROL:
                    {
												Ctrl.type = USB_REQUEST;
                        if(REC_FEATURE_UNITID == (Ctrl.setup.index>>8))//buf[5])
                        {
//                            M8(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0)) = g_usbd_RecMinVolume;
//                            M8(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0) + 1) = g_usbd_RecMinVolume >> 8;
															USB_Write(&Ctrl, (uint8_t*)&g_usbd_RecMinVolume, 2);
                        }
                        else if(PLAY_FEATURE_UNITID == (Ctrl.setup.index>>8))//buf[5])
                        {
//                            M8(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0)) = g_usbd_PlayMinVolume;
//                            M8(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0) + 1) = g_usbd_PlayMinVolume >> 8;
															USB_Write(&Ctrl, (uint8_t*)&g_usbd_PlayMinVolume, 2);
                        }
                        /* Data stage */
//                        USBD_SET_DATA1(EP0);
//                        USBD_SET_PAYLOAD_LEN(EP0, 2);
                        break;
                    }
                    default:
                        /* STALL control pipe */
//                        USBD_SetStall(0);
												Ctrl.type = USB_REQUEST;
                        Ctrl.status = USB_STALL;
                        USB_Write(&Ctrl, (uint8_t*)USB_NULL, (uint32_t)USB_NULL);
												break;
                }
                // Trigger next Control Out DATA1 Transaction.
                /* Status stage */
//                USBD_PrepareCtrlOut(0, 0);
                break;
            }

            case UAC_GET_MAX:
            {
                switch(Ctrl.setup.value>>8)//(buf[3])
                {
										
                    case VOLUME_CONTROL:
                    {
												Ctrl.type = USB_REQUEST;
                        if(REC_FEATURE_UNITID == (Ctrl.setup.index>>8))//buf[5])
                        {
//                            M8(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0)) = g_usbd_RecMaxVolume;
//                            M8(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0) + 1) = g_usbd_RecMaxVolume >> 8;
															USB_Write(&Ctrl, (uint8_t*)&g_usbd_RecMaxVolume, 2);
                        }
                        else if(PLAY_FEATURE_UNITID == (Ctrl.setup.index>>8))//buf[5])
                        {
//                            M8(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0)) = g_usbd_PlayMaxVolume;
//                            M8(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0) + 1) = g_usbd_PlayMaxVolume >> 8;
															USB_Write(&Ctrl, (uint8_t*)&g_usbd_PlayMaxVolume, 2);
                        }
                        /* Data stage */
//                        USBD_SET_DATA1(EP0);
//                        USBD_SET_PAYLOAD_LEN(EP0, 2);
                        break;
                    }
                    default:
                        /* STALL control pipe */
//                        USBD_SetStall(0);
												Ctrl.type = USB_REQUEST;
                        Ctrl.status = USB_STALL;
                        USB_Write(&Ctrl, (uint8_t*)USB_NULL, (uint32_t)USB_NULL);
											break;
                }
                // Trigger next Control Out DATA1 Transaction.
                /* Status stage */
//                USBD_PrepareCtrlOut(0, 0);
                break;
            }

            case UAC_GET_RES:
            {
								
                switch(Ctrl.setup.value>>8)//(buf[3])
                {
                    case VOLUME_CONTROL:
                    {
												Ctrl.type = USB_REQUEST;
                        if(REC_FEATURE_UNITID == (Ctrl.setup.index>>8))//buf[5])
                        {
//                            M8(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0)) = g_usbd_RecResVolume;
//                            M8(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0) + 1) = g_usbd_RecResVolume >> 8;
															USB_Write(&Ctrl, (uint8_t*)&g_usbd_RecResVolume, 2);
                        }
                        else if(PLAY_FEATURE_UNITID == (Ctrl.setup.index>>8))//buf[5])
                        {
//                            M8(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0)) = g_usbd_PlayResVolume;
//                            M8(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0) + 1) = g_usbd_PlayResVolume >> 8;
															USB_Write(&Ctrl, (uint8_t*)&g_usbd_PlayResVolume, 2);
                        }
                        /* Data stage */
//                        USBD_SET_DATA1(EP0);
//                        USBD_SET_PAYLOAD_LEN(EP0, 2);
                        break;
                    }
                    default:
                        /* STALL control pipe */
//                        USBD_SetStall(0);
													Ctrl.type = USB_REQUEST;
													Ctrl.status = USB_STALL;
													USB_Write(&Ctrl, (uint8_t*)USB_NULL, (uint32_t)USB_NULL);
											break;
                }
                // Trigger next Control Out DATA1 Transaction.
                /* Status stage */
//                USBD_PrepareCtrlOut(0, 0);
                break;
            }

            default:
            {
                /* Setup error, stall the device */
//                USBD_SetStall(0);
									Ctrl.type = USB_REQUEST;
                  Ctrl.status = USB_STALL;
                  USB_Write(&Ctrl, (uint8_t*)USB_NULL, (uint32_t)USB_NULL);
            }
        }
    }
    else
    {
        // Host to device
        switch((Ctrl.setup.type & USB_BREQUEST)>>8)//(buf[1])
        {
            case UAC_SET_CUR:
            {
                switch(Ctrl.setup.value>>8)//(buf[3])
                {
                    case MUTE_CONTROL:
												Ctrl.type = USB_PUAC;
												USB_Read(&Ctrl, (uint8_t *)&iistxbuff[0][0], EP3_MAX_PKT_SIZE);
												
												Ctrl.type = USB_REQUEST;
                        if(REC_FEATURE_UNITID == (Ctrl.setup.index>>8))//buf[5])
												{
//                            USBD_PrepareCtrlOut((uint8_t *)&g_usbd_RecMute, buf[6]);
															USB_Write(&Ctrl, (uint8_t*)&g_usbd_RecMute, Ctrl.setup.length&0xFF);
												}
                        else if(PLAY_FEATURE_UNITID == (Ctrl.setup.index>>8))//buf[5])
                        {
//                            USBD_PrepareCtrlOut((uint8_t *)&g_usbd_PlayMute, buf[6]);
															USB_Write(&Ctrl, (uint8_t*)&g_usbd_PlayMute, Ctrl.setup.length&0xFF);
                        }
                        /* Status stage */
//                        USBD_SET_DATA1(EP0);
//                        USBD_SET_PAYLOAD_LEN(EP0, 0);
												
                        break;

                    case VOLUME_CONTROL:
												Ctrl.type = USB_REQUEST;
                        if(REC_FEATURE_UNITID == (Ctrl.setup.index>>8))//buf[5])
                        {
                            if((Ctrl.setup.value&0xFF) == 1)//(buf[2] == 1)
                            {
                                /* Prepare the buffer for new record volume of left channel */
//                                USBD_PrepareCtrlOut((uint8_t *)&g_usbd_RecVolumeL, buf[6]);
																	USB_Write(&Ctrl, (uint8_t*)&g_usbd_RecVolumeL, Ctrl.setup.length&0xFF);
                            }
                            else
                            {
                                /* Prepare the buffer for new record volume of right channel */
//                                USBD_PrepareCtrlOut((uint8_t *)&g_usbd_RecVolumeR, buf[6]);
																	USB_Write(&Ctrl, (uint8_t*)&g_usbd_RecVolumeR, Ctrl.setup.length&0xFF);
                            }
                        }
                        else if(PLAY_FEATURE_UNITID == (Ctrl.setup.index>>8))//buf[5])
                        {
                            if((Ctrl.setup.value&0xFF) == 1)//(buf[2] == 1)
                            {
                                /* Prepare the buffer for new play volume of left channel */
//                                USBD_PrepareCtrlOut((uint8_t *)&g_usbd_PlayVolumeL, buf[6]);
																	USB_Write(&Ctrl, (uint8_t*)&g_usbd_PlayVolumeL, Ctrl.setup.length&0xFF);

                            }
                            else
                            {
                                /* Prepare the buffer for new play volume of right channel */
//                                USBD_PrepareCtrlOut((uint8_t *)&g_usbd_PlayVolumeR, buf[6]);
																	USB_Write(&Ctrl, (uint8_t*)&g_usbd_PlayVolumeR, Ctrl.setup.length&0xFF);

                            }
                        }
                        /* Status stage */
//                        USBD_SET_DATA1(EP0);
//                        USBD_SET_PAYLOAD_LEN(EP0, 0);
												
                        break;

                    default:
                        /* STALL control pipe */
//                        USBD_SetStall(0);
												Ctrl.type = USB_REQUEST;
                        Ctrl.status = USB_STALL;
                        USB_Write(&Ctrl, (uint8_t*)USB_NULL, (uint32_t)USB_NULL);
                        break;
                }
                break;
            }

            default:
            {
                /* Setup error, stall the device */
//                USBD_SetStall(0);
								Ctrl.type = USB_REQUEST;
                Ctrl.status = USB_STALL;
                USB_Write(&Ctrl, (uint8_t*)USB_NULL, (uint32_t)USB_NULL);
                break;
            }
        }
    }
										
                }


                break;

            case USB_STS_REQUEST_COMPLETE : /* Complete Class Request */
                if (USB_REQUEST_TYPE_CLASS == (Ctrl.setup.type & USB_REQUEST_TYPE_CLASS))
                {
                    if (USB_SET_IDLE == (Ctrl.setup.type & USB_BREQUEST))
                    {
                        /* Do Nothing */
											
                    }
                    else if (USB_SET_PROTOCOL == (Ctrl.setup.type & USB_BREQUEST))
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
								
                break;

            default:
                break;
        }
    }
} /* End of function usb_main */

/******************************************************************************
 End  Of File
 ******************************************************************************/

