/****************************************************************************
 *   $Id:: usbhw.c 7071 2011-04-04 21:28:08Z usb00423                        $
 *   Project: NXP LPC11xx USB example
 *
 *   Description:
 *     This file contains LPC11Uxx USB H/W code example which include USB
 *     initialization, USB interrupt handler, and related APIs for
 *     USB access.
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
#define __USBHW_C__

#include "LPC11Uxx.h"                        /* LPC11Uxx definitions */
#include "type.h"
#include "usb.h"
#include "usbhw.h"
#include "usbcore.h"
#include "usbuser.h"
#include "main.h"
#if POWERDOWN_MODE_USB_WAKEUP
#include "timer16.h"
#endif

#if LPM_SUPPORT
/* LPM Suspend Interrupt Debugging */
volatile uint32_t DevStatusLPMSuspend = 0;
#endif

#if POWERDOWN_MODE_USB_WAKEUP
volatile uint32_t SuspendFlag = 0;
volatile uint32_t USBWakeupInterruptFlag = 0;
extern volatile uint32_t timer16_0_counter;
extern volatile uint32_t WakeupFlag;
#endif

#if USB_SOF_EVENT
volatile uint32_t SOFIRQCount = 0;
#endif

#if USB_FIQ_EVENT
volatile uint32_t SOFFIQCount = 0;
#endif

/*
 *    Based on the logic EP number and direction bit 7,
 *    when bit 7 is set, it's an IN EP, otherwise,
 *    it's an OUT EP. The return value is the
 *    location of the EP in the interrupt(status/enable/
 *    routing, etc) register.
 *    The bit info. of the interrupt register is
 *    bit 0 is EP0 OUT, bit 1 is EP0 IN,...
 *    bit 28 is EP14 OUT, bit 29 is EP14 IN....
 *    e.g. EPNum(0x80) is EP0 IN, the return
 *    value is 1; EPNum(0x8E) is EP14 IN, the return
 *    value is 29.
 *    Parameters:      Logical EP with direction bit
 *    Return Value:    EP address in interrupt status.
 */
static RetU32 EPAdr(U32 EPNum)
{
	U32 val;

	val = (EPNum & 0x0F) << 1;

	if(EPNum & 0x80)
	{
		val += 1;
	}
	return (val);
}

/*
 *    USB and IO Clock configuration only.
 *
 *    Configure clock and I/Os for USB.
 *    Parameters:      None
 *    Return Value:    None
 */
void NDrv_USB_IOClkConfig(void)
{
	/* Enable AHB clock to the GPIO domain. */
	LPC_SYSCON->SYSAHBCLKCTRL |= BIT6;

	/* Enable AHB clock to the USB block and USB RAM. */
	LPC_SYSCON->SYSAHBCLKCTRL |= (BIT14|BIT27);

	/* Pull-down is needed, or internally, VBUS will be floating. This is to
	address the wrong status in VBUSDebouncing bit in CmdStatus register. It
	happens on the NXP Validation Board only that a wrong ESD protection chip is used. */
	LPC_IOCON->PIO0_3 &= ~0x1F;
	LPC_IOCON->PIO0_3 |= (BIT3|BIT0);	/* Secondary function VBUS */
	//  LPC_IOCON->PIO0_3   |= (0x01<<0);			/* Secondary function VBUS */
	LPC_IOCON->PIO0_6 &= ~0x07;
	LPC_IOCON->PIO0_6 |= BIT0;			/* Secondary function SoftConn */

#if POWERDOWN_MODE_USB_WAKEUP
	LPC_USB->DEVCMDSTAT &= ~USB_PLL_ON;	/* NeedClk normal mode(not ALWAYS ON) */
	LPC_SYSCON->USBCLKCTRL = 0x1<<1;  /* USB wakeup interrupt on rising edge of Needclk. */
#endif
}

#if REMOTE_WAKEUP_ENABLE
/*
 *  Remote Wakeup event processing
 *    This routine is called once the remote wakeup event occurs, any
 *    external event such as push button. If REMOTE_WAKEUP feature is
 *    enabled, if the device is connected, and suspended, write SUSP
 *    bit to zero to trigger the remote wakeup event.
 *
 *    Parameters:      None
 *    Return Value:    None
 */

void RemoteWakeupEvent ( void )
{
  if(g_USBCore_Setting.USB_DeviceStatus & USB_GETSTATUS_REMOTE_WAKEUP )
  {
    NDrv_USB_WakeUpCfg( TRUE );
#if LPM_SUPPORT
	if ( LPC_USB->DEVCMDSTAT & USB_LPM_SUS )
	{
	  LPC_USB->DEVCMDSTAT &= ~USB_LPM_SUS;
	}
#endif
	//if ( LPC_USB->DEVCMDSTAT & USB_DSUS )
	//{
	  /* Only clear the SUS bit to initiate the remote wakeup. */
	  LPC_USB->DEVCMDSTAT &= ~USB_DSUS;
	//}
  }
  else
  {
	NDrv_USB_WakeUpCfg( FALSE );
  }
}
#endif

/*
 *  USB Get EP Command/Status Pointer Function
 *    EPNum.0..3: Address
 *    EPNum.7:    Dir
 *    Parameters:      Logical EP with direction bit
 *    Return Value:    Physical Memory location for EP list command/status
 */
RetU32 USB_GetEPCmdStatusPtr(U32 EPNum)
{
	U32 addr;

	addr = (U32)USB_EPLIST_ADDR;
	addr += ((EPAdr(EPNum)*2) << 2);/* Based on EPCommand/Status List, all EPs are double buffered except CTRL EP 0, size is 32-bit. */
	return (addr);
}

/*
 *  USB EP List Initialize Function
 *    Called by the USB_Init to initialize USB EPList memory
 *    The example below is the simpliest case, every location is pre-configured
 *    with fixed length for each EP. See USB chapter, Endpoint Command/Status
 *    List for more details.
 *
 *    Parameters:      None
 *    Return Value:    None
 */
void NDrv_USB_EPInit(void)
{
	U32 *addr, data_ptr,i, j = 0;

	addr = (U32 *)USB_EPLIST_ADDR;
	LPC_USB->EPLISTSTART = USB_EPLIST_ADDR;
	data_ptr = USB_EPDATA_ADDR;
	LPC_USB->DATABUFSTART = USB_EPDATA_PAGE;

	/* CTRL, BULK or Interrupt IN/OUT EPs, max EP size is 64 */
	/* For EP0, double buffer doesn't apply to CTRL EPs, but, EP0OUTBuf0 is
	for EP0OUT, EP0OUTBuf1 is for SETUP, EP0INBuf0 is for EP0IN, EP0INTBuf1 is
	reserved. Also note: ACTIVE bit doesn't apply to SETUP and Reserved EP buffer. */
	*addr++ = (USB_MAX_PACKET0 << 16)|((U16)(data_ptr >> 6));
	g_USBHW_Setting.EPList[j].buf_ptr = data_ptr;
	g_USBHW_Setting.EPList[j++].buf_length = USB_MAX_PACKET0;
	data_ptr += USB_MAX_PACKET0;

	*addr++ = ((U16)(data_ptr >> 6));/* No length field for SETUP */
	g_USBHW_Setting.EPList[j].buf_ptr = data_ptr;
	g_USBHW_Setting.EPList[j++].buf_length = USB_SETUP_PACKET_SIZE;
	/* For easier alignment, the data field is aligned to 64 bytes for all EPs. */
	data_ptr += USB_MAX_PACKET0;

	*addr++ = (USB_MAX_PACKET0 << 16)|((U16)(data_ptr >> 6));
	g_USBHW_Setting.EPList[j].buf_ptr = data_ptr;
	g_USBHW_Setting.EPList[j++].buf_length = USB_MAX_PACKET0;
	data_ptr += USB_MAX_PACKET0;

#if 0
	/* EP0 IN second buffer(buffer1) is reserved. */
	*addr++ = (USB_MAX_PACKET0<<16)|((uint16_t)(data_ptr>>6));
#else
	addr++;
#endif

	g_USBHW_Setting.EPList[j].buf_ptr = data_ptr;
	g_USBHW_Setting.EPList[j++].buf_length = USB_MAX_PACKET0;
	data_ptr += USB_MAX_PACKET0;

	for(i = 2; i < USB_EP_NUM; i++)
	{
		/* Buffer 0 */
#if USB_ISO_COMMUNICATION
		*addr++ = EP_DISABLED|EP_ISO_TYPE|(USB_MAX_ISO_SIZE << 16)|((U16)(data_ptr >> 6));
		g_USBHW_Setting.EPList[j].buf_ptr = data_ptr;
		g_USBHW_Setting.EPList[j++].buf_length = USB_MAX_ISO_SIZE;
		data_ptr += USB_MAX_ISO_SIZE;
#else
		*addr++ = EP_DISABLED|(USB_MAX_NON_ISO_SIZE << 16)|((U16)(data_ptr >> 6));
		g_USBHW_Setting.EPList[j].buf_ptr = data_ptr;
		g_USBHW_Setting.EPList[j++].buf_length = USB_MAX_NON_ISO_SIZE;
		data_ptr += USB_MAX_NON_ISO_SIZE;
#endif
		/* Buffer 1 */
#if USB_ISO_COMMUNICATION
		*addr++ = EP_DISABLED|EP_ISO_TYPE|(USB_MAX_ISO_SIZE << 16)|((U16)(data_ptr >> 6));
		g_USBHW_Setting.EPList[j].buf_ptr = data_ptr;
		g_USBHW_Setting.EPList[j++].buf_length = USB_MAX_ISO_SIZE;
		data_ptr += USB_MAX_ISO_SIZE;
#else
		*addr++ = EP_DISABLED|(USB_MAX_NON_ISO_SIZE << 16)|((U16)(data_ptr >> 6));
		g_USBHW_Setting.EPList[j].buf_ptr = data_ptr;
		g_USBHW_Setting.EPList[j++].buf_length = USB_MAX_NON_ISO_SIZE;
		data_ptr += USB_MAX_NON_ISO_SIZE;
#endif
	}
}

/*
 *  USB Initialize Function
 *   Called by the User to initialize USB
 *    Parameters:      None
 *    Return Value:    None
 */

void nsAPI_USB_Init (void)
{
	NVIC_DisableIRQ(USB_IRQn);
	/* Initialize clock and I/O pins for USB. */
	NDrv_USB_IOClkConfig();

#if LPM_SUPPORT
	/* Link Power Management is supported. */
	LPC_USB->DEVCMDSTAT |= USB_LPM;
	LPC_USB->LPM |= (0x2 << 4);		/* RESUME duration. */
#endif

#if USB_FIQ_EVENT
	/* At present, only FRAME(ISO) is routed to FIQ. */
	LPC_USB->IntRouting = FRAME_INT;		/* SOF uses FIQ */

	/* Enable the USB FIQ Interrupt */
	NVIC_EnableIRQ(USB_FIQn);
#endif

#if USE_DOUBLE_BUFFER
	LPC_USB->EPBUFCFG = 0x3FC;
#endif
	/* Enable the USB Interrupt */
	NVIC_EnableIRQ(USB_IRQn);

	NDrv_USB_Reset();
	NDrv_USB_Connect(TRUE);/* USB Connect */
}


/*
 *  USB Connect Function
 *   Called by the User to Connect/Disconnect USB
 *    Parameters:      con:   Connect/Disconnect
 *    Return Value:    None
 */

void NDrv_USB_Connect(U8 con)
{
	if(con)
	LPC_USB->DEVCMDSTAT |= USB_DCON;
	else
	LPC_USB->DEVCMDSTAT &= ~USB_DCON;
}


/*
 *  USB Reset Function
 *   Called automatically on USB Reset
 *    Parameters:      None
 *    Return Value:    None
 */

void NDrv_USB_Reset(void)
{
	g_USBHW_Setting.BufferUsed = 0;
	g_USBHW_Setting.EPActiveFlag = 0;

	/* Initialize EP Command/Status List. */
	NDrv_USB_EPInit();

	LPC_USB->DEVCMDSTAT |= USB_EN;
	/* Clear all EP interrupts, device status, and SOF interrupts. */
	LPC_USB->INTSTAT = 0xC00003FF;
	/* Enable all ten(10) EPs interrupts including EP0, note: EP won't be
	ready until it's configured/enabled when device sending SetEPStatus command
	to the command engine. */
	LPC_USB->INTEN  = DEV_STAT_INT | 0x3FF | (USB_SOF_EVENT ? FRAME_INT : 0);
}


/*
 *  USB Suspend Function
 *   Called automatically on USB Suspend
 *    Parameters:      None
 *    Return Value:    None
 */

void USB_Suspend (void) {
  /* Performed by Hardware */
#if POWERDOWN_MODE_USB_WAKEUP
  timer16_0_counter = 0;
  NDrv_Timer16_Enable( 0 );

  if ( SuspendFlag == 0 ) {
	SuspendFlag = 1;
  }
#endif
}


/*
 *  USB Resume Function
 *   Called automatically on USB Resume
 *    Parameters:      None
 *    Return Value:    None
 */

void USB_Resume (void) {
  /* Performed by Hardware */
#if POWERDOWN_MODE_USB_WAKEUP
  NDrv_Timer16_Disable( 0 );
  timer16_0_counter = 0;
  if ( SuspendFlag == 1 ) {
	SuspendFlag = 0;
  }
#endif
}


/*
 *  USB Remote Wakeup Function
 *   Called automatically on USB Remote Wakeup
 *    Parameters:      None
 *    Return Value:    None
 */

void USB_WakeUp (void) {

  if (g_USBCore_Setting.USB_DeviceStatus & USB_GETSTATUS_REMOTE_WAKEUP) {
	LPC_USB->DEVCMDSTAT &= ~USB_DSUS;
  }
}


/*
 *  USB Remote Wakeup Configuration Function
 *    Parameters:      cfg:   Enable/Disable
 *    Return Value:    None
 */

void NDrv_USB_WakeUpCfg(U8 cfg)
{
#if REMOTE_WAKEUP_ENABLE
	if(cfg == TRUE)
	{
		LPC_USB->DEVCMDSTAT &= ~USB_PLL_ON;/* NeedClk functional */
		LPC_SYSCON->USBCLKCTRL = 1;
	}
	else
	{
		LPC_USB->DEVCMDSTAT |= USB_PLL_ON;/* NeedClk always "1" */
		LPC_SYSCON->USBCLKCTRL = 0;
	}
#else
	cfg = cfg;  /* Not needed */
#endif
}


/*
 *  USB Set Address Function
 *    Parameters:      adr:   USB Address
 *    Return Value:    None
 */

void nsAPI_USB_SetAddress(U32 adr)
{
	LPC_USB->DEVCMDSTAT &= ~0x7F;
	LPC_USB->DEVCMDSTAT |= (USB_EN | adr);
}


/*
 *  USB Configure Function
 *    Parameters:      cfg:   Configure/Deconfigure
 *    Return Value:    None
 */

void NDrv_USB_Configure(U8 cfg)
{
	if(cfg)
	{
		/* All the non-zero EPs are configured and enabled per configuration
		descriptor. Enable all interrupts. */
		LPC_USB->INTEN  = DEV_STAT_INT | 0x3FF | (USB_SOF_EVENT ? FRAME_INT : 0);
	}
	else
	{
		/* TBD. if the configuration is FALSE, turn off all the non-zero EPs. Only
		CTRL EP interrupts are enabled. */
		LPC_USB->INTEN  = DEV_STAT_INT | 0x03 | (USB_SOF_EVENT ? FRAME_INT : 0);
	}
}


/*
 *  Configure USB Endpoint according to Descriptor
 *    Parameters:      pEPD:  Pointer to Endpoint Descriptor
 *    Return Value:    None
 */

//void USB_ConfigEP (USB_ENDPOINT_DESCRIPTOR *pEPD) {
//  return;
//}



/*
 *  Set Direction for USB Control Endpoint
 *    Parameters:      dir:   Out (dir == 0), In (dir <> 0)
 *    Return Value:    None
 */

//void USB_DirCtrlEP (uint32_t dir) {
//  return;
//}

/*
 *  Deactivate USB Endpoint
 *    Set the EP bits in the SKIP register and until the bits are
 *    cleared by the H/W. Clear the EP interrupts as well.
 *    It's used for non-zero EPs. For EP0 IN and OUT, clear
 *    the ACTIVE bit in EP Command/Status list will serve the purpose.
 *    Parameters:      EPNum: Endpoint Number
 *                       EPNum.0..3: Address
 *                       EPNum.7:    Dir
 *    Return Value:    None
 */

void nsAPI_USB_DeactivateEP(U32 EPNum)
{
	U32 epbit;

	epbit = 0x1U << EPAdr(EPNum);
	LPC_USB->EPSKIP |= epbit;

	while(LPC_USB->EPSKIP & epbit){}

	LPC_USB->INTSTAT = epbit;/* Clear EP interrupt(s). */
}

/*
 *  Enable USB Endpoint
 *    Parameters:      EPNum: Endpoint Number
 *                       EPNum.0..3: Address
 *                       EPNum.7:    Dir
 *    Return Value:    None
 */

void nsAPI_USB_EnableEP(U32 EPNum)
{
	U32 *addr;

	addr = (U32 *)USB_GetEPCmdStatusPtr(EPNum);
	*addr &= ~EP_DISABLED;

	if(EPNum & 0x0F)/* Non-zero EPs */
	{
		if(EPNum & 0x80)/* For non-zero IN */
		{
			if( LPC_USB->EPBUFCFG & (0x1U << EPAdr(EPNum)))
			{
				/* For non-zero double buffer EPs, clear EP_DISABLED to both buffer. */
				addr++;
				*addr &= ~EP_DISABLED;
			}
		}
		else
		{
			/* For non-zero EP OUT, in addition to clear EP_DISABLED bits,
			set the ACTIVE bit indicating that EP is ready to read. For
			double buffered EPs, set ACTIVE bit and clear EP_DISABLED bit
			for both buffer0 and 1. */
			*addr |= BUF_ACTIVE;

			if( LPC_USB->EPBUFCFG & (0x1U << EPAdr(EPNum)) )
			{
				/* For double buffer. */
				addr++;
				*addr &= ~EP_DISABLED;
				*addr |= BUF_ACTIVE;
			}
		}
	}
}


/*
 *  Disable USB Endpoint
 *    Parameters:      EPNum: Endpoint Number
 *                       EPNum.0..3: Address
 *                       EPNum.7:    Dir
 *    Return Value:    None
 */

void nsAPI_USB_DisableEP(U32 EPNum)
{
	U32 *addr;

	addr = (U32 *)USB_GetEPCmdStatusPtr(EPNum);

	if(EPNum & 0x0F)	/* Non-zero EPs only, EP0 should never be disabled. */
	{
		*addr |= EP_DISABLED;
		/* For non-zero EPs, if double buffer is used, disable both EP buffers. */
		if(LPC_USB->EPBUFCFG & (0x1U << EPAdr(EPNum)))
		{
			addr++;
			*addr |= EP_DISABLED;
		}
	}
}


/*
 *  Toggle Reset USB Endpoint
 *    Parameters:      EPNum: Endpoint Number
 *                       EPNum.0..3: Address
 *                       EPNum.7:    Dir
 *    Return Value:    None
 */

void nsAPI_USB_ResetEP(U32 EPNum)
{
	U32 *addr;

	addr = (U32 *)USB_GetEPCmdStatusPtr( EPNum );
	/* Based on EPInUse register to decide which buffer needs to toggle
	reset. When this happens, the STALL bits need to be cleared for both
	buffer 0 and 1. */
	*addr &= ~EP_STALL;
	*(addr+2) &= ~EP_STALL;

	if(LPC_USB->EPINUSE & (0x1U << EPAdr(EPNum)) )
	{
	addr++;
	}
	*addr |= EP_RESET;
}


/*
 *  Set Stall for USB Endpoint
 *    STALL bit(s) can not be set until ACTIVE bit(s) are cleared.
 *    Parameters:      EPNum: Endpoint Number
 *                       EPNum.0..3: Address
 *                       EPNum.7:    Dir
 *    Return Value:    None
 */

void nsAPI_USB_SetStallEP(U32 EPNum)
{
	U32 *addr;

	if((EPNum & 0x0F) == 0)
	{
		/* For EP0 IN or OUT, simply clear the ACTIVE and set the STALL bit. */
		addr = (U32 *)USB_GetEPCmdStatusPtr(EPNum);
		/* STALL bit can't be set until ACTIVE bit is gone. For EP0,
		SKIP register won't do. Force ACTIVE bit to low if it's set. */
		if(*addr & BUF_ACTIVE)
		{
			*addr &= ~BUF_ACTIVE;
		}
		*addr |= EP_STALL;
	}
	else
	{
		/* For non-zero EPs, deactivate the EP first, clear the ACTIVE bit
		before setting the STALL bit. It applies to both buffer 0 and 1 if
		double buffer is enabled. */
		nsAPI_USB_DeactivateEP(EPNum);
		addr = (U32 *)USB_GetEPCmdStatusPtr(EPNum);

		if(*addr & BUF_ACTIVE)
		{
			*addr &= ~BUF_ACTIVE;
		}

		*addr |= EP_STALL;/* STALL on buffer 0. */

		if(LPC_USB->EPBUFCFG & (0x1U << EPAdr(EPNum)))
		{
			/* If double buffer is enabled, STALL on buffer 1. */
			addr++;
			if(*addr & BUF_ACTIVE)
			{
				*addr &= ~BUF_ACTIVE;
			}
			*addr |= EP_STALL;
		}
	}
}


/*
 *  Clear Stall for USB Endpoint
 *    For non-zero EP OUT, Toggle Reset should happen once the STALL bit(s)
 *    are cleared. At mean time, ACTIVE bit(s) and data length need to be
 *    reinitialized for EP read.
 *    For non-zero EP IN, when Write EP occurs while STALL bit is set,
 *    EPActiveFlag will be set, inside ClearSTALL, when this flag is set, it's
 *    time to set the ACTIVE bit so that the data buffer is ready to write data
 *    to the EPs.
 *    Parameters:      EPNum: Endpoint Number
 *                       EPNum.0..3: Address
 *                       EPNum.7:    Dir
 *    Return Value:    None
 */

void nsAPI_USB_ClrStallEP(U32 EPNum)
{
	U32 *addr,index;
	index = EPAdr(EPNum);

	if((EPNum & 0x0F) == 0)
	{
		/* For EP0 IN and OUT, simply clear the STALL bit. */
		addr = (U32 *)USB_GetEPCmdStatusPtr(EPNum);
		*addr &= ~EP_STALL;
	}
	else
	{
		addr = (U32 *)USB_GetEPCmdStatusPtr(EPNum);
		/* For non-zero EPs if double buffer, both STALL bits should be cleared. */
		*addr &= ~EP_STALL;
		*(addr+1) &= ~EP_STALL;

		/* Based on EPInUse register to decide which buffer needs to toggle reset. */
		if(LPC_USB->EPINUSE & (0x1U << index))
		{
			/* Buffer 1 is in use. Toggle Reset Buffer 1, otherwise, toggle Reset
			buffer 0. */
			addr++;
		}

		*addr |= EP_RESET;
		if(!(EPNum & 0x80))
		{
			/* For non-zero EP OUT, ACTIVE bit and length field need to
			be set again after clearing STALL. */
			*addr &= ~(PKT_LNGTH_MASK << 16);
#if USB_ISO_COMMUNICATION
			*addr |= ((USB_MAX_ISO_SIZE << 16) | BUF_ACTIVE);
#else
			*addr |= ((USB_MAX_NON_ISO_SIZE << 16) | BUF_ACTIVE);
#endif
		}
		else
		{
			/* For non-zero EP IN, the EPActiveFlag will be set when WriteEP() happens
			while STALL is set. If so, when ClearSTALL happens, set the ACTIVE bit that
			data buffer is ready to write data to the EPs. */
			if(g_USBHW_Setting.EPActiveFlag & (0x1U << index))
			{
				*addr |= BUF_ACTIVE;
				g_USBHW_Setting.EPActiveFlag &= ~(0x1U << index);
			}
		}
	}
}

/*
 *  Read USB Endpoint SETUP Data
 *    Parameters:      EPNum: Endpoint Number
 *                       EPNum.0..3: Address
 *                       EPNum.7:    Dir
 *                     pData: Pointer to Data Buffer
 *    Return Value:    Number of bytes read
 */

void nsAPI_USB_ReadSetupEP(U32 EPNum, U8 *pData)
{
	U32 cnt, n,*addr,*dataptr;


	addr = (U32 *)USB_GetEPCmdStatusPtr( EPNum );

	/* Check/Clear STALL on both EP0 IN and OUT when SETUP is received. */
	if((*addr & EP_STALL) || ((*addr+2) & EP_STALL))
	{
		*addr &= ~EP_STALL;
		*(addr+2) &= ~EP_STALL;
	}

	cnt = USB_SETUP_PACKET_SIZE;
	dataptr = (U32 *)g_USBHW_Setting.EPList[1].buf_ptr;

	for (n = 0; n < (cnt + 3) / 4; n++)
	{
		*((__packed U32 *)pData) = *((__packed U32 *)dataptr);
		pData += 4;
		dataptr++;
	}

	addr++;		/* Use EP0 buffer 1 for SETUP packet */
	/* Fixed Command/Status location(EPList[1] for SETUP. Reset buffer pointer
	field, SETUP length is fixed with eight bytes. */
	*addr &= ~0x3FFFFFF;
	*addr |= (U16)((g_USBHW_Setting.EPList[1].buf_ptr) >> 6);

	//return (cnt);
}

/*
 *  Read USB Endpoint Data
 *    Parameters:      EPNum: Endpoint Number
 *                       EPNum.0..3: Address
 *                       EPNum.7:    Dir
 *                     pData: Pointer to Data Buffer
 *    Return Value:    Number of bytes read
 */

RetU32 nsAPI_USB_ReadEP(U32 EPNum, U8 *pData)
{
	U32 cnt, n,*addr,buf_flag,*dataptr,index[2] = {0};

	addr = (U32 *)USB_GetEPCmdStatusPtr(EPNum);
	index[0] = EPAdr(EPNum);
	index[1] = EPAdr(EPNum) * 2;/* Double buffer is considered. */
	if(EPNum & 0x0F)
	{
		/* For EP0 IN/OUT, there is no double buffer. For non-zero
		EP, double buffer is considered. If BufferUsed bit mask is set,
		buffer0 is used, switch to buffer 1, index needs to be changed
		accordingly too. */
		buf_flag = g_USBHW_Setting.BufferUsed & (0x1U << index[0]);

		if(buf_flag != 0)
		{
			addr++;/* Use buffer 1 */
			index[1]++;
		}
	}

	cnt = (*addr >> 16) & PKT_LNGTH_MASK;
	/* The NBytes field decrements by H/W with the packet byte each time. */
	cnt = g_USBHW_Setting.EPList[index[1]].buf_length - cnt;
	dataptr = (uint32_t *)g_USBHW_Setting.EPList[index[1]].buf_ptr;
	for(n = 0; n < (cnt + 3) / 4; n++)
	{
		*((__packed uint32_t *)pData) = *((__packed uint32_t *)dataptr);
		pData += 4;
		dataptr++;
	}

	/* Clear buffer after EP read, reset EP length and buffer pointer field */
	*addr &= ~0x3FFFFFF;
	if((EPNum & 0x0F) == 0)
	{
		/* EP0 is single buffer only. */
		*addr |= ((g_USBHW_Setting.EPList[index[1]].buf_length << 16)
		| (uint16_t)((g_USBHW_Setting.EPList[index[1]].buf_ptr) >> 6) | BUF_ACTIVE);
	}
	else
	{
		/* Toggle buffer if double buffer is used for non-zero EPs.  */
		g_USBHW_Setting.BufferUsed ^= (0x1U << index[0]);
		g_USBHW_Setting.BufferUsed &= LPC_USB->EPBUFCFG;

		if(LPC_USB->EPBUFCFG & (0x1U << index[0]))
		{
			if(g_USBHW_Setting.BufferUsed & (0x1U << index[0]))
			{
				addr++;/* Set buffer 1 ACTIVE */
				index[1]++;
			}
			else
			{
				addr--;/* Set buffer 0 ACTIVE */
				index[1]--;
			}
		}
		*addr |= ((g_USBHW_Setting.EPList[index[1]].buf_length << 16)
		| (U16)((g_USBHW_Setting.EPList[index[1]].buf_ptr) >> 6) | BUF_ACTIVE);
	}
	return (cnt);
}


/*
 *  Write USB Endpoint Data
 *    For EP0 OUT, ACTIVE bits will not be set until SETUP and
 *	  EP0 IN have been received.
 *    Parameters:      EPNum: Endpoint Number
 *                       EPNum.0..3: Address
 *                       EPNum.7:    Dir
 *                     pData: Pointer to Data Buffer
 *                     cnt:   Number of bytes to write
 *    Return Value:    Number of bytes written
 */

RetU32 nsAPI_USB_WriteEP(U32 EPNum,U8 *pData,U32 cnt)
{
	U32 n, index[2],*addr,*dataptr;

	addr = (U32*)USB_GetEPCmdStatusPtr( EPNum );

	index[0] = EPAdr(EPNum);
	index[1] = index[0] * 2;/* Double buffer is considered. */

	if(!(EPNum & 0x0F))
	{
		/* When EP0 IN is received, set ACTIVE bit on both EP0 IN
		and OUT. */
		*addr &= ~EP_STALL;
		*(addr-2) |= BUF_ACTIVE;	/* Set ACTIVE bit on EP0 OUT */
	}
	else
	{
		/* For non-zero EPs, if double buffer is used and EPInUse is set, buffer0
		is used, otherwise, buffer1 is used. */
		if(LPC_USB->EPBUFCFG & (0x1U << index[0]) )
		{
			if(LPC_USB->EPINUSE & (0x1U << index[0]) )
			{
				addr++;/* move to buffer1 address in EP command/status list. */
				index[1]++;
			}
		}
	}

	/* Get EP command/status List, update the length field and data pointer. */
	*addr &= ~0x3FFFFFF;
	cnt &= PKT_LNGTH_MASK;
	*addr |= (cnt << 16)|(U16)((g_USBHW_Setting.EPList[index[1]].buf_ptr) >> 6);

	dataptr = (U32 *)g_USBHW_Setting.EPList[index[1]].buf_ptr;
	/* Stuff the data first, whether send out or not(set ACTIVE bit) is based on STALL condition. */
	for (n = 0; n < (cnt + 3) / 4; n++)
	{
		*((__packed U32 *)dataptr) = *((__packed U32 *)pData);
		pData += 4;
		dataptr++;
	}

	if((*addr & EP_STALL) && (EPNum & 0x0F))
	{
	 /* This is for MSC class when STALL occurs and non-zero EPs,
		set the ACTIVE flag, but don't do anything until ClearFeature
		to clear STALL, then tranfer the data. */
		g_USBHW_Setting.EPActiveFlag |= (0x1U << index[0]);
		return (cnt);
	}

	*addr |= BUF_ACTIVE;
	return (cnt);
}

void wnDrv_Usb_ClrGetReqStatus(U32 EPNum)
{
	U32 *addr;

	addr = (U32*)USB_GetEPCmdStatusPtr(EPNum);

	*addr &=~ BUF_ACTIVE;
}
#if USB_FIQ_EVENT
/* USB FIQ Interrupt Service Routine for SOF */
void USB_FIQHandler( void )
{
  uint32_t disr;

  disr = LPC_USB->IntStat;                      /* Device Interrupt Status */
  LPC_USB->IntStat = disr;

  if (disr & FRAME_INT) {
	SOFFIQCount++;
  }
  return;
}
#endif




/*
 *  USB Interrupt Service Routine
 *    All the device status, EP, and SOF interrupts are handled here.
 *    Parameters:      None
 *    Return Value:    None
 */

void USB_IRQHandler (void)
{
  uint32_t disr, val, n, m;

  disr = LPC_USB->INTSTAT;         /* Get Interrupt Status and clear immediately. */
  LPC_USB->INTSTAT = disr;

  /* Device Status Interrupt (Reset, Connect change, Suspend/Resume) */
  if (disr & DEV_STAT_INT) {
    val = LPC_USB->DEVCMDSTAT;       /* Device Status */

    if (val & USB_DRESET_C) {               /* Reset */
      NDrv_USB_Reset();
#if   USB_RESET_EVENT
      USB_Reset_Event();
#endif
    }
    if (val & USB_DCON_C) {                 /* Connect change */
#if   USB_POWER_EVENT
      USB_Power_Event(val & DEV_CON);
#endif
    }
    if (val & USB_DSUS_C) {                 /* Suspend/Resume */
      if (val & USB_DSUS) {                 /* Suspend */
        USB_Suspend();
#if     USB_SUSPEND_EVENT
        USB_Suspend_Event();
#endif
      } else {                              /* Resume */
        USB_Resume();
#if REMOTE_WAKEUP_ENABLE
        LPC_SYSCON->USBCLKCTRL = 0;
#endif
#if     USB_RESUME_EVENT
        USB_Resume_Event();
#endif
      }
    }
#if LPM_SUPPORT
	if (val & USB_LPM_SUS) {                /* LPM Suspend */
      DevStatusLPMSuspend++;
    }
#endif
    goto isr_end;
  }

#if USB_SOF_EVENT
  /* Start of Frame Interrupt */
  if (disr & FRAME_INT) {
    USB_SOF_Event();
	SOFIRQCount++;
  }
#endif


  /* Endpoint's Interrupt */
  if (disr & 0x3FF) {
	/* if any of the EP0 through EP9 is set, or bit 0 through 9 on disr */
    for (n = 0; n < USB_EP_NUM; n++) {      /* Check All Endpoints */
	  if (disr & (1 << n)) {
        m = n >> 1;
        if ((n & 1) == 0) {                 /* OUT Endpoint */
          if (n == 0) {                     /* Control OUT Endpoint */
            if ( LPC_USB->DEVCMDSTAT & USB_SETUP_RCVD ) {
 											/* Setup packet is received. */
              if (USB_P_EP[0]) {
                USB_P_EP[0](USB_EVT_SETUP);
				LPC_USB->DEVCMDSTAT |= USB_SETUP_RCVD;
                continue;
              }
            }
          }
          if (USB_P_EP[m]) {
            USB_P_EP[m](USB_EVT_OUT);
          }
        } else {                            /* IN Endpoint */
          if (USB_P_EP[m]) {
            USB_P_EP[m](USB_EVT_IN);
			if( m == 1)
			{
				m = 1;
			}
          }
        }
      }
    }
  }
isr_end:
  return;
}


Boolean wnDrv_Usb_EP_Status(U32 EPNum)
{
    uint32_t *addr;

    addr = (uint32_t *)USB_GetEPCmdStatusPtr( EPNum );

    /* For non-zero EPs, if double buffer is used and EPInUse is set, buffer0
    is used, otherwise, buffer1 is used. */
    if(LPC_USB->EPBUFCFG & (0x1U << EPAdr(EPNum)))
    {
        if(LPC_USB->EPINUSE & (0x1U << EPAdr(EPNum)))
        {
            addr++;/* move to buffer1 address in EP command/status list. */
        }
    }

    /* Get EP command/status List, update the length field and data pointer. */
    if((*addr & BUF_ACTIVE) ==  BUF_ACTIVE)
    {
        return FALSE;
    }
    return TRUE;
}

#if POWERDOWN_MODE_USB_WAKEUP
/*
 *  USB Wakeup Interrupt Service Routine
 *    A dedicated USB wakeup interrupt is handled in LPC11Uxx.
 *    In earlier version, USB interrupt can only wake up MCU
 *    normal sleep mode. When RESUME occurs from the host, this dedicated
 *    USB wakeup interrupt can be used to wake up MCU from either sleep or
 *    deep sleep mode.
 *    Parameters:      None
 *    Return Value:    None
 */

void USBWakeup_IRQHandler(void)
{

  /* Below clear pending is not needed in C1US as NeedClk can be configured
  as rising or falling edge, not level trigger anymore. */
//  NVIC_ClearPendingIRQ(USBWakeup_IRQn);   /* If pending, clear USB Activity interrupt. */
  NVIC_DisableIRQ(USBWakeup_IRQn);        /* Disable USB activity interrupt */
  if ( WakeupFlag == 1 )
  {
	WakeupFlag = 0;
	USBWakeupInterruptFlag = 1;
  }
  return;
}
#endif

