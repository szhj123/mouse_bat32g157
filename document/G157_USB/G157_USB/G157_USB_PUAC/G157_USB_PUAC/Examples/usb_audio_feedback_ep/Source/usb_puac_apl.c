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
#include "userdefine.h"
#include <stdio.h>

#include "dma.h"
#include "ssie.h"
#include "ssi_api_if.h"

#include "usb_basic_mini_if.h"
#include "usb_typedef.h"
#include "usb_extern.h"
#include "usb_reg_access.h"
#include "usb_bitdefine.h"
#include "usb.h"

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

volatile uint8_t g_usbd_RecMute       = 0x00;     /* Record MUTE control. 0 = normal. 1 = MUTE */
volatile int16_t g_usbd_RecVolumeL    = 0x1000;   /* Record left channel volume. Range is -32768 ~ 32767 */
volatile int16_t g_usbd_RecVolumeR    = 0x1000;   /* Record right channel volume. Range is -32768 ~ 32767 */
volatile int16_t g_usbd_RecMaxVolume  = 0x7FFF;
volatile int16_t g_usbd_RecMinVolume  = 0x8000;
volatile int16_t g_usbd_RecResVolume  = 0x400;

volatile uint8_t g_usbd_PlayMute      = 0x00;     /* Play MUTE control. 0 = normal. 1 = MUTE */
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

extern uint8_t iistxbuff[(BUFF_NUM +1) * SINGLE_BUFF_SIZE], iisrxbuff[256], i2semptybuff[EP3_MAX_PKT_SIZE];
extern uint32_t usb_read_pos, iis_send_pos, buff_size;
extern uint8_t audiofeedbackbuffer[3]; 

#if 0
void Set_D0D1Fifo(void)
{
	USBF->D0FIFOSEL = 0x3401;
	USBF->D1FIFOSEL = 0x3402;
	USBF->D0FIFOCTR = 0;
	USBF->D1FIFOCTR = 0;
	
//	DMA_Start(DMA_VECTOR_USB_FIFO1, USB_D1FIFO_DMA_CHANNEL, DMA_MODE_NORMAL, DMA_SIZE_BYTE, EP3_MAX_PKT_SIZE, (uint8_t*)&USBF->D1FIFOL, (uint8_t*)&iistxbuff[0][0]);
	//-------------------------------------------------------
  // USB D1FIFO reception: FIFO --> RAM
  // src address fixed, dst address increment
  //-------------------------------------------------------
  // word transfer
	DMAVEC->VEC[DMA_VECTOR_USB_FIFO1] = USB_D1FIFO_DMA_CHANNEL;  // USB D1FIFO IRQ

  DMAVEC->CTRL[USB_D1FIFO_DMA_CHANNEL].DMACR = ((1 << FIFO_Pos) | (1 << SZ_Pos) | (1 << DAMOD_Pos) | (0 << SAMOD_Pos) | (0 << RPTSEL_Pos) | (0 << MODE_Pos)); 
  DMAVEC->CTRL[USB_D1FIFO_DMA_CHANNEL].DMBLS = EP3_MAX_PKT_SIZE/2;
  DMAVEC->CTRL[USB_D1FIFO_DMA_CHANNEL].DMACT = 1;
  DMAVEC->CTRL[USB_D1FIFO_DMA_CHANNEL].DMRLD = 1;
  DMAVEC->CTRL[USB_D1FIFO_DMA_CHANNEL].DMSAR = (uint32_t)((uint8_t*)&USBF->D1FIFOL);
  DMAVEC->CTRL[USB_D1FIFO_DMA_CHANNEL].DMDAR = (uint32_t)((uint8_t*)&iistxbuff[0][0]);

  /* Initial DMA Register */
  CGC->PER1   |= CGC_PER1_DMAEN_Msk;
  DMA->DMABAR = DMAVEC_BASE;
  DMA->DMAEN4 = 1<<3;
	
	/* PIPE control reg set */
  hw_usb_set_pid(USB_PIPE2, USB_PID_BUF);
	
	INTC_ClearPendingIRQ(D0FIFO_IRQn);
  INTC_DisableIRQ(D0FIFO_IRQn);
	
	INTC_ClearPendingIRQ(D1FIFO_IRQn);
  INTC_EnableIRQ(D1FIFO_IRQn);
	
	
}
#endif
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

void class_req_handle(usb_ctrl_t *p_ctrl); //laidi
void set_feedback_sample_rate(uint32_t rate);

uint8_t read_first_flag, play_flag, read_flag;
uint32_t read_cnt = 1, play_cnt,time_cnt;
/******************************************************************************
  * Function Name: usb_main
  * Description  : Peripheral HID application main process
  * Arguments    : none
  * Return Value : none
 ******************************************************************************/
void usb_main (void)
{
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
								read_flag = 1;
                break;	
						case USB_STS_READ_COMPLETE :
								Ctrl.type = USB_PVND;
								Ctrl.pipe = USB_PIPE2;

								usb_read_pos += Ctrl.size;		//read data from Host, move read pos
								if(usb_read_pos >= BUFF_NUM * SINGLE_BUFF_SIZE)
								{
									buff_size = usb_read_pos;		//ready to send
									usb_read_pos = 0;
									iis_send_pos = (DMAVEC->CTRL[IISTX_DMA_CHANNEL].DMACT) *4;
									//do in STS_NONE
//									if(iis_send_pos > BUFF_NUM/2 * SINGLE_BUFF_SIZE)
//									{
//										set_feedback_sample_rate(46000);
//									}else{
//										set_feedback_sample_rate(48000);
//									}
								}
//								if(usb_read_pos >= (BUFF_NUM * SINGLE_BUFF_SIZE))
//								{
//									iis_send_pos = BUFF_NUM * SINGLE_BUFF_SIZE - (DMAVEC->CTRL[IISTX_DMA_CHANNEL].DMACT) *4;
//									memcpy(&iistxbuff[0], &iistxbuff[usb_read_pos], usb_read_pos - BUFF_NUM * SINGLE_BUFF_SIZE);
//									usb_read_pos = usb_read_pos - BUFF_NUM * SINGLE_BUFF_SIZE;
									//check send pos
//									if(iis_send_pos > BUFF_NUM/2 * SINGLE_BUFF_SIZE)
//									{
//										set_feedback_sample_rate(46000);
////										printf("s:%d\n", iis_send_pos);
//									}else{
//										set_feedback_sample_rate(48000);
////										printf("D:%d\n", iis_send_pos);
//									}
//								}
								USB_PipeRead(&Ctrl, (uint8_t *)&iistxbuff[usb_read_pos], SINGLE_BUFF_SIZE);
								read_flag = 0;
								break;
            case USB_STS_WRITE_COMPLETE :
//								iis_send_pos = (DMAVEC->CTRL[IISTX_DMA_CHANNEL].DMACT) *4;
//								//*****iis_send_pos**********usb_read_pos********
//								if(iis_send_pos < usb_read_pos)
//								{
//									if(usb_read_pos - iis_send_pos > 19 * SINGLE_BUFF_SIZE)
//									{
//											set_feedback_sample_rate(46000);
//									}else if(usb_read_pos - iis_send_pos < 5 * SINGLE_BUFF_SIZE)
//									{
//											set_feedback_sample_rate(48000);
//									}else{
//											set_feedback_sample_rate(46875);
//									}
//								}else{	//*****usb_read_pos***********iis_send_pos*******
//									if(iis_send_pos - usb_read_pos > 19 * SINGLE_BUFF_SIZE)
//									{
//										set_feedback_sample_rate(48000);
//									}
//									else if(iis_send_pos - usb_read_pos < 5 * SINGLE_BUFF_SIZE)
//									{
//										set_feedback_sample_rate(46000);
//									}else{
//											set_feedback_sample_rate(46875);
//									}
//								}
								//laidi print here,delay too long
//								printf("read pos:%d, send pos:%d:\n", usb_read_pos, iis_send_pos);
								Ctrl.pipe = USB_PIPE1;
								USB_PipeWrite(&Ctrl, (uint8_t *)&audiofeedbackbuffer[0], 3);
						
                break;
            case USB_STS_REQUEST : /* Receive Class Request */
								class_req_handle(&Ctrl);
								//laidi SET_INTERFACE
								if(USB_SET_INTERFACE == (Ctrl.setup.type & 0xFF00))
								{
									memset(iistxbuff, 0x00, sizeof(iistxbuff));
									usb_read_pos = 0;
									read_flag = 1;
								}
                break;
            case USB_STS_REQUEST_COMPLETE : /* Complete Class Request */
								
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
								if(read_flag == 1)
								{
										Ctrl.type = USB_PVND;
										Ctrl.pipe = USB_PIPE2;
									
										USB_PipeRead(&Ctrl, (uint8_t *)&iistxbuff[usb_read_pos], SINGLE_BUFF_SIZE);
									
										set_feedback_sample_rate(48000);
										Ctrl.pipe = USB_PIPE1;
										USB_PipeWrite(&Ctrl, (uint8_t *)&audiofeedbackbuffer[0], 3);
										read_flag = 0;
								}
								
								//BUFF_NUM * SINGLE_BUFF_SIZE - iis_send_pos
//								if(iis_send_pos > BUFF_NUM/2 * SINGLE_BUFF_SIZE)	//send a few, quick
//								{
//									set_feedback_sample_rate(48000);
//								}else{
//									set_feedback_sample_rate(46000);
//								}
//								printf("buff size:%d\n", buff_size);
                break;
            default:
                break;
        }
    }
} /* End of function usb_main */



void class_req_handle(usb_ctrl_t *p_ctrl)
{
		//laidi add Note: in "Ctrl.setup.type" struct, bRequest is Byte0, bmRequestType is Byte1
		if (USB_REQUEST_TYPE_CLASS == (Ctrl.setup.type & USB_REQUEST_TYPE_CLASS))
		{
			if((Ctrl.setup.type&0xFF) & 0x80)//(buf[0] & 0x80)    /* request data transfer direction */
			{
					// Device to host
					switch((Ctrl.setup.type & USB_BREQUEST)>>8)//(buf[1])
					{
							case UAC_GET_CUR:
									switch(Ctrl.setup.value>>8)//(buf[3])	//wValue
									{
											case MUTE_CONTROL:
													Ctrl.type = USB_REQUEST;
													if(REC_FEATURE_UNITID == (Ctrl.setup.index>>8))//buf[5])
															USB_Write(&Ctrl, (uint8_t*)&g_usbd_RecMute, 1);//M8(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0)) = g_usbd_RecMute;
													else if(PLAY_FEATURE_UNITID == (Ctrl.setup.index>>8))//buf[5])
															USB_Write(&Ctrl, (uint8_t*)&g_usbd_PlayMute, 1);//M8(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0)) = g_usbd_PlayMute;
													break;
											case VOLUME_CONTROL:
												if(REC_FEATURE_UNITID == (Ctrl.setup.index>>8))//buf[5])
                        {
														Ctrl.type = USB_REQUEST;
                            /* Left or right channel */
                            if((Ctrl.setup.value&0xFF)==1)//if(buf[2] == 1)
                            {
																USB_Write(&Ctrl, (uint8_t*)&g_usbd_RecVolumeL, 2);
                            }
                            else
                            {
																USB_Write(&Ctrl, (uint8_t*)&g_usbd_RecVolumeR, 2);
                            }

                        }
                        else if(PLAY_FEATURE_UNITID == (Ctrl.setup.index>>8))//buf[5])
                        {
														Ctrl.type = USB_REQUEST;
                            /* Left or right channel */
                            if((Ctrl.setup.value&0xFF)==1)//if(buf[2] == 1)
                            {
																USB_Write(&Ctrl, (uint8_t*)&g_usbd_RecVolumeL, 2);
                            }
                            else
                            {
																USB_Write(&Ctrl, (uint8_t*)&g_usbd_RecVolumeR, 2);
                            }
                        }
												break;
											default:
													/* Setup error, stall the device */
													Ctrl.type = USB_REQUEST;
													Ctrl.status = USB_STALL;
													USB_Write(&Ctrl, (uint8_t*)USB_NULL, (uint32_t)USB_NULL);
													break;
										}
									break;
								case UAC_GET_MIN:
									switch(Ctrl.setup.value>>8)//(buf[3])
									{
											case VOLUME_CONTROL:
													Ctrl.type = USB_REQUEST;
													if(REC_FEATURE_UNITID == (Ctrl.setup.index>>8))//buf[5])
													{
																USB_Write(&Ctrl, (uint8_t*)&g_usbd_RecMinVolume, 2);
													}
													else if(PLAY_FEATURE_UNITID == (Ctrl.setup.index>>8))//buf[5])
													{
																USB_Write(&Ctrl, (uint8_t*)&g_usbd_PlayMinVolume, 2);
													}
													break;
											default:
													/* STALL control pipe */
													Ctrl.type = USB_REQUEST;
													Ctrl.status = USB_STALL;
													USB_Write(&Ctrl, (uint8_t*)USB_NULL, (uint32_t)USB_NULL);
													break;
									}
									break;
								case UAC_GET_MAX:
									switch(Ctrl.setup.value>>8)//(buf[3])
									{
                    case VOLUME_CONTROL:
												Ctrl.type = USB_REQUEST;
                        if(REC_FEATURE_UNITID == (Ctrl.setup.index>>8))//buf[5])
                        {
															USB_Write(&Ctrl, (uint8_t*)&g_usbd_RecMaxVolume, 2);
                        }
                        else if(PLAY_FEATURE_UNITID == (Ctrl.setup.index>>8))//buf[5])
                        {
															USB_Write(&Ctrl, (uint8_t*)&g_usbd_PlayMaxVolume, 2);
                        }
                        break;
                    default:
                        /* STALL control pipe */
												Ctrl.type = USB_REQUEST;
                        Ctrl.status = USB_STALL;
                        USB_Write(&Ctrl, (uint8_t*)USB_NULL, (uint32_t)USB_NULL);
											break;
									}
									break;
								case UAC_GET_RES:
									switch(Ctrl.setup.value>>8)//(buf[3])
									{
                    case VOLUME_CONTROL:
												Ctrl.type = USB_REQUEST;
                        if(REC_FEATURE_UNITID == (Ctrl.setup.index>>8))//buf[5])
                        {
															USB_Write(&Ctrl, (uint8_t*)&g_usbd_RecResVolume, 2);
                        }
                        else if(PLAY_FEATURE_UNITID == (Ctrl.setup.index>>8))//buf[5])
                        {
															USB_Write(&Ctrl, (uint8_t*)&g_usbd_PlayResVolume, 2);
                        }
                        break;
                    default:
                        /* STALL control pipe */
													Ctrl.type = USB_REQUEST;
													Ctrl.status = USB_STALL;
													USB_Write(&Ctrl, (uint8_t*)USB_NULL, (uint32_t)USB_NULL);
											break;
									}
                break;
							default:
									/* Setup error, stall the device */
									Ctrl.type = USB_REQUEST;
									Ctrl.status = USB_STALL;
									USB_Write(&Ctrl, (uint8_t*)USB_NULL, (uint32_t)USB_NULL);
									break;
					}
			}
			else
			{
					// Host to device
					switch((Ctrl.setup.type & USB_BREQUEST)>>8)//(buf[1])
					{
							case UAC_SET_CUR:
								switch(Ctrl.setup.value>>8)//(buf[3])
								{
										case MUTE_CONTROL:
												Ctrl.type = USB_REQUEST;
												if(REC_FEATURE_UNITID == (Ctrl.setup.index>>8))//buf[5])
												{
														USB_Read(&Ctrl, (uint8_t*)&g_usbd_RecMute, Ctrl.setup.length&0xFF);
												}
												else if(PLAY_FEATURE_UNITID == (Ctrl.setup.index>>8))//buf[5])
												{
														USB_Read(&Ctrl, (uint8_t*)&g_usbd_PlayMute, Ctrl.setup.length&0xFF);
												}
												break;
										case VOLUME_CONTROL:
												Ctrl.type = USB_REQUEST;
                        if(REC_FEATURE_UNITID == (Ctrl.setup.index>>8))//buf[5])
                        {
                            if((Ctrl.setup.value&0xFF) == 1)//(buf[2] == 1)
                            {
                                /* Prepare the buffer for new record volume of left channel */
																USB_Read(&Ctrl, (uint8_t*)&g_usbd_RecVolumeL, Ctrl.setup.length&0xFF);
                            }
                            else
                            {
                                /* Prepare the buffer for new record volume of right channel */
																USB_Read(&Ctrl, (uint8_t*)&g_usbd_RecVolumeR, Ctrl.setup.length&0xFF);
                            }
                        }
                        else if(PLAY_FEATURE_UNITID == (Ctrl.setup.index>>8))//buf[5])
                        {
                            if((Ctrl.setup.value&0xFF) == 1)//(buf[2] == 1)
                            {
                                /* Prepare the buffer for new play volume of left channel */
																USB_Read(&Ctrl, (uint8_t*)&g_usbd_PlayVolumeL, Ctrl.setup.length&0xFF);

                            }
                            else
                            {
                                /* Prepare the buffer for new play volume of right channel */
																USB_Read(&Ctrl, (uint8_t*)&g_usbd_PlayVolumeR, Ctrl.setup.length&0xFF);

                            }
                        }								
											break;
										default:
												Ctrl.type = USB_REQUEST;
												Ctrl.status = USB_STALL;
												USB_Write(&Ctrl, (uint8_t*)USB_NULL, (uint32_t)USB_NULL);
												break;
									}
									break;
							default:
									Ctrl.type = USB_REQUEST;
									Ctrl.status = USB_STALL;
									USB_Write(&Ctrl, (uint8_t*)USB_NULL, (uint32_t)USB_NULL);
									break;
						}
				}
			}
}


void set_feedback_sample_rate(uint32_t rate)
{
    rate = ((rate / 1000) << 14) | ((rate % 1000) << 4);
    audiofeedbackbuffer[0] = rate;
    audiofeedbackbuffer[1] = rate>>8;
    audiofeedbackbuffer[2] = rate>>16;
}


/******************************************************************************
 End  Of File
 ******************************************************************************/

