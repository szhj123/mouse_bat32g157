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
#include "fmc_user.h"

/*******************************************************************************
 Macro definitions
 ******************************************************************************/

#define DATA_LEN                (8)
#define HID_DESCRIPTOR_SIZE     (9)
#define REPORT_DESCRIPTOR_SIZE  (27)
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

static  uint8_t         gs_idle      = 0;

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

//laidi
#define outpw(port,value)   (*((volatile unsigned int *)(port))=(value))
#define inpw(port)          ((*((volatile unsigned int *)(port))))
#define outpb(port,value)   (*((volatile unsigned char *)(port))=(value))
#define inpb(port)          ((*((volatile unsigned char *)(port))))
#define outps(port,value)   (*((volatile unsigned short *)(port))=(value))
#define inps(port)          ((*((volatile unsigned short *)(port))))
	
uint8_t parse_usb_cmd(uint8_t* buf, uint8_t len);

__align(4) uint8_t usb_rcvbuf[OUT_EP_MAX_PKT_SIZE], response_buff[IN_EP_MAX_PKT_SIZE];
uint8_t usb_data_ready;

uint32_t bUpdateApromCmd;
__align(4) static uint8_t aprom_buf[FMC_FLASH_PAGE_SIZE];


static uint16_t Checksum(unsigned char *buf, int len)
{
    int i;
    uint16_t c;

    for(c = 0 , i = 0 ; i < len; i++) {
        c += buf[i];
    }

    return (c);
}

static uint16_t CalCheckSum(uint32_t start, uint32_t len)
{
    int i;
    register uint16_t lcksum = 0;

    for(i = 0; i < len; i+=FMC_FLASH_PAGE_SIZE) {
        ReadData(start + i, start + i + FMC_FLASH_PAGE_SIZE, (uint32_t*)aprom_buf);
        if(len - i >= FMC_FLASH_PAGE_SIZE)
            lcksum += Checksum(aprom_buf, FMC_FLASH_PAGE_SIZE);
        else
            lcksum += Checksum(aprom_buf, len - i);
    }

    return lcksum;

}

void EraseAP(unsigned int addr_start, unsigned int addr_end)
{
    unsigned int eraseLoop = addr_start;

    for(; eraseLoop < addr_end; eraseLoop += FMC_FLASH_PAGE_SIZE ) {
        FMC_Erase_User(eraseLoop);
    }
    return;
}


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
    uint8_t     *p_idle_value;
    usb_info_t  info;
    usb_err_t   ret_code = USB_SUCCESS;

    ctrl.type       = USB_PHID;
    cfg.usb_mode    = USB_PERI;
    /* Descriptor registration */
    cfg.p_usb_reg     = (usb_descriptor_t *)&gs_usb_descriptor;
    USB_Open (&ctrl, &cfg);       /* Initializes the USB module */

    while (1)
    {
        switch (USB_GetEvent(&ctrl))
        {
            case USB_STS_CONFIGURED :
                #if defined(USE_LPW)
                    /* Do Nothing */
                #endif /* defined(USE_LPW) */
                break;
						
						case USB_STS_READ_COMPLETE :
								usb_data_ready = 1;
								break;
						
            case USB_STS_WRITE_COMPLETE :

                break;

            case USB_STS_REQUEST : /* Receive Class Request */
                if (USB_REQUEST_TYPE_CLASS == (ctrl.setup.type & USB_REQUEST_TYPE_CLASS))
                {
                    if (USB_SET_REPORT == (ctrl.setup.type & USB_BREQUEST))
                    {
											if(ctrl.setup.value>>8 == 3) //(buf[3])	//wValue
											{
//                        /* Get the NumLock data (NumLock data is not used) */
//                        USB_Read(&ctrl, (uint8_t *)&gs_numlock, 2);
											}
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
											if(usb_data_ready == 0)
											{
													ctrl.type = USB_PHID;
//													USB_Write(&ctrl, NULL, 0);
													USB_Read(&ctrl, usb_rcvbuf, OUT_EP_MAX_PKT_SIZE);
											}else{
													parse_usb_cmd(usb_rcvbuf, OUT_EP_MAX_PKT_SIZE);
													USB_Write(&ctrl, response_buff, IN_EP_MAX_PKT_SIZE);
													usb_data_ready = 0;
											}
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
    }
} /* End of function usb_main */

uint8_t parse_usb_cmd(uint8_t* buf, uint8_t len)
{
	  static uint32_t StartAddress, StartAddress_bak, TotalLen, TotalLen_bak, LastDataLen, g_packno = 1;
    uint8_t *response;
    uint16_t lcksum;
    uint32_t lcmd, srclen, i, regcnf0, security;
    unsigned char *pSrc;
    static uint32_t	gcmd;

    response = response_buff;

    pSrc = buf;
    srclen = len;
    lcmd = inpw(pSrc);

    outpw(response + 4, 0);

    pSrc += 8;
    srclen -= 8;

//    ReadData(Config0, Config0 + 8, (uint32_t*)(response + 8));//read config
		outpw(response + 8, 0xabcd);	//in this demo, Doesn't Mean Anything!
		outpw(response + 12, 0x1234);
	
    regcnf0 = *(uint32_t*)(response + 8);
    security = regcnf0 & 0x2;


    if(lcmd == CMD_SYNC_PACKNO) {
        g_packno = inpw(pSrc);
    }

    if((lcmd) && (lcmd!=CMD_RESEND_PACKET))
        gcmd = lcmd;

    if(lcmd == CMD_GET_FWVER) {
        response[8] = FW_VERSION;//version 2.3
    } else if(lcmd == CMD_GET_DEVICEID) {
        //outpw(response+8, SYS->PDID);
				outpw(response+8, UID->UID3); // UID base address: 0x08500E4C+0x0C
        goto out;
    } else if(lcmd == CMD_RUN_APROM || lcmd == CMD_RUN_LDROM || lcmd == CMD_RESET) {
        if(lcmd == CMD_RUN_APROM) {
						 //run APP
//						__disable_irq();
//						__set_MSP(*(__IO uint32_t*) FMC_APROM_BASE);
//						((void (*)()) (*(volatile unsigned long *)(FMC_APROM_BASE+0x04)))();//to APP
						__NVIC_SystemReset();
        } else if(lcmd == CMD_RUN_LDROM) {
							//do nothing
        } else if(lcmd == CMD_RESET) {
							
        }else{
				}
        while(1);
    } else if(lcmd == CMD_CONNECT) {
        g_packno = 1;
        goto out;
    } else if(lcmd == CMD_DISCONNECT) {
        return 0;
    } else if((lcmd == CMD_UPDATE_APROM) || (lcmd == CMD_ERASE_ALL)) {
        EraseAP(FMC_APROM_BASE, (FMC_APROM_BASE + APROM_SIZE));

        if(lcmd == CMD_ERASE_ALL) { //erase data flash
            EraseAP(FMC_DATAFLASH_BASE, FMC_DATAFLASH_BASE + DATAFLASH_SIZE);
            *(uint32_t*)(response + 8) = regcnf0|0x02;
//            //UpdateConfig((uint32_t*)(response + 8), NULL);
        }
        bUpdateApromCmd = 1;
    } else if(lcmd == CMD_GET_FLASHMODE) {
//        //return 1: APROM, 2: LDROM
//        //outpw(response+8, (FMC->ISPCTL&0x2)? 2 : 1);
				outpw(response+8, 1);
    }

    if((lcmd == CMD_UPDATE_APROM) || (lcmd == CMD_UPDATE_DATAFLASH)) {
        if(lcmd == CMD_UPDATE_DATAFLASH) {
            StartAddress = FMC_DATAFLASH_BASE;
            if(DATAFLASH_SIZE) { //g_dataFlashAddr
                EraseAP(FMC_DATAFLASH_BASE, FMC_DATAFLASH_BASE + DATAFLASH_SIZE);
            } else
                goto out;
        } else {
            StartAddress = FMC_APROM_BASE;
        }
//        //StartAddress = inpw(pSrc);
        TotalLen = inpw(pSrc+4);
        pSrc += 8;
        srclen -= 8;
        StartAddress_bak = StartAddress;
        TotalLen_bak = TotalLen;
    } else if(lcmd == CMD_UPDATE_CONFIG) {
//        if((security == 0) && (!bUpdateApromCmd))//security lock
//            goto out;
//        UpdateConfig((uint32_t*)(pSrc), (uint32_t*)(response+8));
//        GetDataFlashInfo(&g_dataFlashAddr, &g_dataFlashSize);
        goto out;
    } else if(lcmd == CMD_RESEND_PACKET) { //for APROM&Data flash only
        StartAddress -= LastDataLen;
        TotalLen += LastDataLen;
//        if((StartAddress & 0xFFE00) >= Config0)
				if(StartAddress > FMC_APROM_BASE + APROM_SIZE)
            goto out;
        ReadData(StartAddress & 0xFFE00, StartAddress, (uint32_t*)aprom_buf);		//page size 0x200
        FMC_Erase_User(StartAddress & 0xFFE00);
        WriteData(StartAddress & 0xFFE00, StartAddress, (uint32_t*)aprom_buf);
        if((StartAddress%FMC_FLASH_PAGE_SIZE) >= (FMC_FLASH_PAGE_SIZE-LastDataLen))
            FMC_Erase_User((StartAddress & 0xFFE00)+FMC_FLASH_PAGE_SIZE);
        goto out;

    }

    if((gcmd == CMD_UPDATE_APROM) || (gcmd == CMD_UPDATE_DATAFLASH)) {
        if(TotalLen < srclen) {
            srclen = TotalLen;//prevent last package from over writing
        }

        TotalLen -= srclen;

        WriteData(StartAddress, StartAddress + srclen, (uint32_t*)pSrc); //WriteData(StartAddress, StartAddress + srclen, (uint32_t*)pSrc);
        memset(pSrc, 0, srclen);

        ReadData(StartAddress, StartAddress + srclen, (uint32_t*)pSrc);
        StartAddress += srclen;
        LastDataLen =  srclen;

        if(TotalLen == 0) {
            lcksum = CalCheckSum(StartAddress_bak, TotalLen_bak);
            outps(response + 8, lcksum);
        }
    }
out:
    lcksum = Checksum(buf, len);
    outps(response, lcksum);
    ++g_packno;
    outpw(response+4, g_packno);
    g_packno++;

    return 0;
}
		

/******************************************************************************
 End  Of File
 ******************************************************************************/

