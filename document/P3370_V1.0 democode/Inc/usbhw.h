/****************************************************************************
 *   $Id:: usbhw.h 6446 2011-02-12 03:00:16Z usb00423                        $
 *   Project: NXP LPC11Uxx USB example
 *
 *   Description:
 *     This file contains LPC11Uxx USB H/W layer definitions, data structure,
 *     and USB hardware API prototyping.
 *
 ****************************************************************************
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * products. This software is supplied "AS IS" without any warranties.
 * NXP Semiconductors assumes no responsibility or liability for the
 * use of the software, conveys no license or title under any patent,
 * copyright, or mask work right to the product. NXP Semiconductors
 * reserves the right to make changes in the software without
 * notification. NXP Semiconductors also make no representation or
 * warranty that such application will be suitable for the specified
 * use without further testing or modification.
****************************************************************************/
#ifndef __USBHW_H__
#define __USBHW_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "Type.h"
#include "Usb.h"
#include "usbcfg.h"

#ifdef  __USBHW_C__
#define INTERFACE
#else
#define INTERFACE extern
#endif


typedef struct _EP_LIST
{
	U32 buf_ptr;
	U32 buf_length;
} EP_LIST;

typedef struct _LPC11Uxx_USBHW_SETTING_
{
	/* The BufferUsed flag is to deal with double buffer situation, This is a bit mask
	flag for non-zero EPs. If BufferUsed bit is set, buffer 0 is used, switch to buffer 1.
	If BufferUsed flag is not set, buffer 0 can be used. */
	volatile U32 BufferUsed;

	/* The ActiveFlag is to deal with STALL situation, if STALL happens during
	WriteEP(), don't set the ACTIVE bit in EPList CommandStatus immediately but
	this flag only, ACTIVE bit will be set after ClearStallEP() that data is ready
	to be sent. This is a bit mask flag for non-zero EPs. */
	volatile U32 EPActiveFlag;

	/* EP buffer address and length default setting */
	volatile EP_LIST EPList[USB_EP_NUM*2];/* Consider double buffer for non zero EPs */
}LPC11Uxx_USBHW_SETTING;

INTERFACE LPC11Uxx_USBHW_SETTING g_USBHW_Setting;

#define USB_EPLIST_ADDR 0x10001800
#define USB_EPDATA_ADDR (USB_EPLIST_ADDR + 0x100)
#define USB_EPDATA_PAGE (USB_EPDATA_ADDR&0xFFC00000)/* Bit 22~31 is the page */
#define USB_RAM_LIMIT 0x800/* maximum USB RAM size is 2K */

#if 0
/* Be careful if ISO communication is used that it could allocate more than 64 bytes. */
#define USB_EP0DATA_OUT		(USB_EPDATA_ADDR + 0x00)
#define USB_SETUP_BUF		(USB_EPDATA_ADDR + 0x40)
#define USB_EP0DATA_IN		(USB_EPDATA_ADDR + 0x80)

#define USB_EP1DATA_OUT0	(USB_EPDATA_ADDR + 0x100)		/* INT/BULK EPs, max EP 64 bytes */
#define USB_EP1DATA_OUT1	(USB_EPDATA_ADDR + 0x140)
#define USB_EP1DATA_IN0		(USB_EPDATA_ADDR + 0x180)
#define USB_EP1DATA_IN1		(USB_EPDATA_ADDR + 0x1C0)

#define USB_EP2DATA_OUT0	(USB_EPDATA_ADDR + 0x200)
#define USB_EP2DATA_OUT1	(USB_EPDATA_ADDR + 0x240)
#define USB_EP2DATA_IN0		(USB_EPDATA_ADDR + 0x280)
#define USB_EP2DATA_IN1		(USB_EPDATA_ADDR + 0x2C0)

#define USB_EP3DATA_OUT0	(USB_EPDATA_ADDR + 0x300)
#define USB_EP3DATA_OUT1	(USB_EPDATA_ADDR + 0x340)
#define USB_EP3DATA_IN0		(USB_EPDATA_ADDR + 0x380)
#define USB_EP3DATA_IN1		(USB_EPDATA_ADDR + 0x3C0)

#define USB_EP4DATA_OUT0	(USB_EPDATA_ADDR + 0x400)
#define USB_EP4DATA_OUT1	(USB_EPDATA_ADDR + 0x440)
#define USB_EP4DATA_IN0		(USB_EPDATA_ADDR + 0x480)
#define USB_EP4DATA_IN1		(USB_EPDATA_ADDR + 0x4C0)
#endif

#define BUF_ACTIVE BIT31
#define EP_DISABLED BIT30
#define EP_STALL BIT29
#define EP_RESET BIT28
#define EP_ISO_TYPE BIT26

/* USB Device Command Status */
#define USB_EN BIT7/* Device Enable */
#define USB_SETUP_RCVD BIT8/* SETUP token received */
#define USB_PLL_ON BIT9/* PLL is always ON */
#define USB_LPM BIT11/* LPM is supported */
#define USB_IntOnNAK_AO BIT12/* Device Interrupt on NAK BULK OUT */
#define USB_IntOnNAK_AI BIT13/* Device Interrupt on NAK BULK IN */
#define USB_IntOnNAK_CO BIT14/* Device Interrupt on NAK CTRL OUT */
#define USB_IntOnNAK_CI BIT15/* Device Interrupt on NAK CTRL IN */
#define USB_DCON BIT16/* Device connect */
#define USB_DSUS BIT17/* Device Suspend */
#define USB_LPM_SUS BIT19/* LPM suspend */
#define USB_REMOTE_WAKE BIT20/* LPM Remote Wakeup */
#define USB_DCON_C BIT24/* Device connection change */
#define USB_DSUS_C BIT25/* Device SUSPEND change */
#define USB_DRESET_C BIT26/* Device RESET */
#define USB_VBUS_DBOUNCE BIT28/* Device VBUS detect */

/* Device Interrupt Bit Definitions */
#define EP0_INT BIT0
#define EP1_INT BIT1
#define EP2_INT BIT2
#define EP3_INT BIT3
#define EP4_INT BIT4
#define EP5_INT BIT5
#define EP6_INT BIT6
#define EP7_INT BIT7
#define EP8_INT BIT8
#define EP9_INT BIT9
#define FRAME_INT BIT30
#define DEV_STAT_INT (0x80000000)

/* Rx & Tx Packet Length Definitions */
#define PKT_LNGTH_MASK 0x000003FF

/* Error Status Register Definitions */
#define ERR_NOERROR 0x00
#define ERR_PID_ENCODE 0x01
#define ERR_UNKNOWN_PID 0x02
#define ERR_UNEXPECT_PKT 0x03
#define ERR_TCRC 0x04
#define ERR_DCRC 0x05
#define ERR_TIMEOUT 0x06
#define ERR_BABBIE 0x07
#define ERR_EOF_PKT 0x08
#define ERR_TX_RX_NAK 0x09
#define ERR_SENT_STALL 0x0A
#define ERR_BUF_OVERRUN 0x0B
#define ERR_SENT_EPT_PKT 0x0C
#define ERR_BIT_STUFF 0x0D
#define ERR_SYNC 0x0E
#define ERR_TOGGLE_BIT 0x0F

/* USB Hardware Functions */
INTERFACE void NDrv_USB_IOClkConfig(void);
INTERFACE void nsAPI_USB_Init(void);
INTERFACE void NDrv_USB_EPInit(void);
INTERFACE void NDrv_USB_Connect(U8 con);
INTERFACE void NDrv_USB_Reset(void);
INTERFACE void USB_Suspend(void);
INTERFACE void USB_Resume(void);
INTERFACE void USB_WakeUp(void);
INTERFACE void NDrv_USB_WakeUpCfg(U8 cfg);
INTERFACE void nsAPI_USB_SetAddress(U32 adr);
INTERFACE void NDrv_USB_Configure(U8 cfg);
//INTERFACE void  nsAPI_USB_ConfigEP(USB_ENDPOINT_DESCRIPTOR *pEPD);
//INTERFACE void  USB_DirCtrlEP  (uint32_t dir);
INTERFACE void  nsAPI_USB_EnableEP(U32 EPNum);
INTERFACE void  nsAPI_USB_DisableEP(U32 EPNum);
INTERFACE void  nsAPI_USB_ResetEP(U32 EPNum);
INTERFACE void  nsAPI_USB_SetStallEP(U32 EPNum);
INTERFACE void  nsAPI_USB_ClrStallEP(U32 EPNum);
//INTERFACE void  USB_ClearEPBuf (uint32_t EPNum);
INTERFACE void nsAPI_USB_ReadSetupEP(U32 EPNum, U8 *pData);
INTERFACE RetU32 nsAPI_USB_ReadEP(U32 EPNum, U8 *pData);
INTERFACE RetU32 nsAPI_USB_WriteEP(U32 EPNum, U8 *pData, U32 cnt);
INTERFACE void  USB_IRQHandler (void);
INTERFACE void  USBWakeup_IRQHandler(void);
INTERFACE void RemoteWakeupEvent ( void );
INTERFACE void wnDrv_Usb_ClrGetReqStatus(U32 EPNum);
INTERFACE Boolean wnDrv_Usb_EP_Status(U32 EPNum);

#undef INTERFACE
#ifdef __cplusplus
}
#endif
#endif  /* __USBHW_H__ */
