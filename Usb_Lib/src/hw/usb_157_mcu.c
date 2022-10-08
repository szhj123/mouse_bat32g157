/*******************************************************************************
 * File Name    : usb_157_mcu.c
 * Description  : MCU processing
 *****************************************************************************/


/******************************************************************************
 Includes   <System Includes> , "Project Includes"
 ******************************************************************************/
#include "usb_basic_mini_if.h"
#include "usb_bitdefine.h"
#include "usb_typedef.h"
#include "usb_reg_access.h"            /* Definition of the USB register access macro */
#include "usb_extern.h"
#include "usb.h"

#if ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE))
//#include "usb_dmac.h"
#endif  /* ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE)) */

/******************************************************************************
 Macro definitions
 ******************************************************************************/

#if defined(USB_CFG_HHID_USE) || defined(USB_CFG_PHID_USE)
  #if USB_CFG_DTC == USB_CFG_ENABLE
    #error  In HID class, can not set USB_CFG_ENABLE to USB_CFG_DTC in usb_basic_config.h.
  #endif /* USB_CFG_DTC == USB_CFG_ENABLE */

  #if USB_CFG_DMA == USB_CFG_ENABLE
    #error  In HID class, can not set USB_CFG_ENABLE to USB_CFG_DMA in usb_basic_config.h.
  #endif /* USB_CFG_DMA == USB_CFG_ENABLE */

#endif /* defined(USB_CFG_HHID_USE) || defined(USB_CFG_PHID_USE) */


#if USB_CFG_BC == USB_CFG_DISABLE
  #if USB_CFG_DCP == USB_CFG_ENABLE
    #error  Can not set USB_CFG_DISABLE to USB_CFG_BC when setting USB_CFG_ENABLE to USB_CFG_DCP \
         in usb_basic_config.h.

  #endif /* USB_CFG_DCP == USB_CFG_ENABLE */
#endif /* USB_CFG_BC == USB_CFG_DISABLE */


#if USB_CFG_DMA == USB_CFG_ENABLE
  #if USB_CFG_DTC == USB_CFG_ENABLE
    #error  Can not set USB_CFG_ENABLE to the definitions (USB_CFG_DMA and USB_CFG_DTC) at the same time \
         in usb_basic_config.h.

  #endif /* USB_CFG_DTC == USB_CFG_ENABLE */
#endif /* USB_CFG_DMA == USB_CFG_ENABLE */


#if USB_CFG_MODE == USB_CFG_HOST
  #if defined(USB_CFG_PCDC_USE) || defined(USB_CFG_PHID_USE) || defined(USB_CFG_PMSC_USE) || defined(USB_CFG_PVNDR_USE)
    #error  Can not enable these definitions(USB_CFG_PCDC_USE/USB_CFG_PHID_USE/USB_CFG_PMSC_USE/USB_CFG_PVNDR_USE) \
        when setting USB_HOST to USB_CFG_MODE in usb_basic_config.h.

  #endif /* defined(USB_CFG_PCDC_USE || USB_CFG_PHID_USE || USB_CFG_PMSC_USE || USB_CFG_PVNDR_USE) */
#endif /* USB_CFG_MODE == USB_HOST */


#if USB_CFG_MODE == USB_CFG_PERI
  #if defined(USB_CFG_HCDC_USE) || defined(USB_CFG_HHID_USE) || defined(USB_CFG_HMSC_USE) || defined(USB_CFG_HVNDR_USE)
    #error  Can not enable these definitions(USB_CFG_HCDC_USE/USB_CFG_HHID_USE/USB_CFG_HMSC_USE/USB_CFG_HVNDR_USE) \
        when setting USB_PERI to USB_CFG_MODE in usb_basic_config.h.

  #endif /* defined(USB_CFG_HCDC_USE || USB_CFG_HHID_USE || USB_CFG_HMSC_USE || USB_CFG_HVNDR_USE) */
#endif /* USB_CFG_MODE == USB_PERI */

/*******************************************************************************
 Typedef definitions
 ******************************************************************************/

/******************************************************************************
 Exported global variables (to be accessed by other files)
 ******************************************************************************/

/******************************************************************************
 Private global variables and functions
 ******************************************************************************/
static void usb_cpu_usb_interrupt (void);
static void usb_cpu_usb_resume_interrupt (void);
#if USB_CFG_DTC == USB_CFG_ENABLE
static void usb_cpu_d0fifo_isr (void);
static void usb_cpu_d1fifo_isr (void);
#endif  /* USB_CFG_DTC == USB_CFG_ENABLE */

//R_BSP_PRAGMA_STATIC_INTERRUPT(usb_cpu_usb_interrupt, VECT(USB0, USBI0))
void IRQ05_Handler (void) __attribute__((alias("intp_5_37_interrupt")));
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
//R_BSP_PRAGMA_STATIC_INTERRUPT(usb_cpu_usb_resume_interrupt, VECT(USB0, USBR0))
void IRQ06_Handler (void) __attribute__((alias("intp_6_38_interrupt")));
#endif

/***********************************************************************************************************************
* Function Name: intp_5_37_interrupt
* @brief  USBI or D0FIFO interrupt entry
* @param  None
* @return None
***********************************************************************************************************************/
void intp_5_37_interrupt(void)
{
    volatile uint8_t ifl, ifh;

    ifl = INTC_GetPendingIRQ(USBI_IRQn);
    ifh = INTC_GetPendingIRQ(D0FIFO_IRQn);

    if(ifl)
    {
        INTC_ClearPendingIRQ(USBI_IRQn);
        usb_cpu_usb_interrupt();
    }

#if USB_CFG_DTC == USB_CFG_ENABLE
    if(ifh)
    {
        INTC_ClearPendingIRQ(D0FIFO_IRQn);
        usb_cpu_d0fifo_isr();   
    }
#endif /* USB_CFG_DTC == USB_CFG_ENABLE */

    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: intp_5_37_interrupt
* @brief  USBI or D0FIFO interrupt entry
* @param  None
* @return None
***********************************************************************************************************************/
void intp_6_38_interrupt(void)
{
    volatile uint8_t ifl, ifh;

    ifl = INTC_GetPendingIRQ(USBR_IRQn);
    ifh = INTC_GetPendingIRQ(D1FIFO_IRQn);

    if(ifl)
    {
        INTC_ClearPendingIRQ(USBR_IRQn);
        usb_cpu_usb_resume_interrupt();
    }

#if USB_CFG_DTC == USB_CFG_ENABLE
    if(ifh)
    {
        INTC_ClearPendingIRQ(D1FIFO_IRQn);
        usb_cpu_d1fifo_isr();   
    }
#endif /* USB_CFG_DTC == USB_CFG_ENABLE */

    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/******************************************************************************
 Function Name   : usb_module_start
 Description     : USB module start
 Arguments       : none
 Return value    : none
 ******************************************************************************/
usb_err_t usb_module_start (void)
{
    if (1 == (CGC->PER2 & CGC_PER2_USBEN_Msk))
    {
        return USB_ERR_BUSY;
    }

    /* Enable power for USB0 */
		CGC->PER2 |= CGC_PER2_USBEN_Msk;

#if 0
	USBF->SYSCFG |= USBF_SYSCFG_SCKE_Msk + USBF_SYSCFG_USBE_Msk;
	USBF->USBMC |= USBF_USBMC_VDCEN_Msk + USBF_USBMC_VDDUSBE_Msk;
	//USBF->USBMC = 0x83;
	USBF->USBBCCTRL |= USBF_USBBCCTRL_BATCHGE0_Msk;
	USBF->SYSCFG |= USBF_SYSCFG_CNEN_Msk;
	USBF->USBBCCTRL |= USBF_USBBCCTRL_VDPSRCE0_Msk+USBF_USBBCCTRL_VDMSRCE0_Msk;
	USBTRMSEL = 0xC306;
	USBRTRIM = 0x7F;
	//USBTRMSEL = 0xC304;
	USBVDATSRC = 0x7F;
	while(1){}
#endif

    hw_usb_set_vdcen();

#if USB_CFG_BC == USB_CFG_ENABLE
    hw_usb_set_vddusbe();
#endif  /* USB_CFG_BC == USB_CFG_ENABLE */

    return USB_SUCCESS;
} /*End of function usb_module_start */

/******************************************************************************
 Function Name   : usb_module_stop
 Description     : USB module stop
 Arguments       : none
 Return value    : none
 ******************************************************************************/
usb_err_t usb_module_stop (void)
{
    if (0 == (CGC->PER2 & CGC_PER2_USBEN_Msk))
    {
        return USB_ERR_NOT_OPEN;
    }

    USB0.DVSTCTR0.WORD = 0;
    USB0.DCPCTR.WORD = USB_SQSET;
    USB0.PIPE1CTR.WORD = 0;
    USB0.PIPE2CTR.WORD = 0;
    USB0.PIPE3CTR.WORD = 0;
    USB0.PIPE4CTR.WORD = 0;
    USB0.PIPE5CTR.WORD = 0;
    USB0.PIPE6CTR.WORD = 0;
    USB0.PIPE7CTR.WORD = 0;
    USB0.PIPE8CTR.WORD = 0;
    USB0.PIPE9CTR.WORD = 0;
    USB0.BRDYENB.WORD = 0;
    USB0.NRDYENB.WORD = 0;
    USB0.BEMPENB.WORD = 0;
    USB0.INTENB0.WORD = 0;
    USB0.INTENB1.WORD = 0;
    USB0.SYSCFG.WORD &= (~USB_DPRPU);
    USB0.SYSCFG.WORD &= (~USB_DRPD);
    USB0.SYSCFG.WORD &= (~USB_USBE);
    USB0.SYSCFG.WORD &= (~USB_DCFM);
    USB0.BRDYSTS.WORD = 0;
    USB0.NRDYSTS.WORD = 0;
    USB0.BEMPSTS.WORD = 0;

    /* Disable power for USB0 */
		CGC->PER2 &= ~CGC_PER2_USBEN_Msk;

    return USB_SUCCESS;
} /*End of function usb_module_stop */

/******************************************************************************
 Function Name   : usb_cpu_usbint_init
 Description     : USB interrupt Initialize
 Arguments       : none
 Return value    : none
 ******************************************************************************/
void usb_cpu_usbint_init (void)
{
    /* Interrupt enable register
     b0 IEN0 Interrupt enable bit
     b1 IEN1 Interrupt enable bit
     b2 IEN2 Interrupt enable bit
     b3 IEN3 Interrupt enable bit
     b4 IEN4 Interrupt enable bit
     b5 IEN5 Interrupt enable bit
     b6 IEN6 Interrupt enable bit
     b7 IEN7 Interrupt enable bit
     */
#if ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE))
    //R_BSP_InterruptRequestEnable(VECT(USB0, D0FIFO0));    /* D0FIFO0 Enable */
    //R_BSP_InterruptRequestEnable(VECT(USB0, D1FIFO0));    /* D1FIFO0 Enable */
		INTC_ClearPendingIRQ(D0FIFO_IRQn); /* clear D0FIFO interrupt flag */
		INTC_EnableIRQ(D0FIFO_IRQn);       /* enable D0FIFO interrupt */

		INTC_ClearPendingIRQ(D1FIFO_IRQn); /* clear D1FIFO interrupt flag */
		INTC_EnableIRQ(D1FIFO_IRQn);       /* enable D1FIFO interrupt */


#endif  /* ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE)) */

    /* Interrupt priority register
     b3-b0 IPR      Interrupt priority
     b7-b4 Reserved 0
     */
//    IPR (USB0, USBI0)= USB_CFG_INTERRUPT_PRIORITY; /* USBI0 in vector 128 */
//    R_BSP_InterruptRequestEnable(VECT(USB0, USBI0)); /* USBI0 enable in vector 128 */
		INTC_ClearPendingIRQ(USBI_IRQn); /* clear USBI interrupt flag */
		INTC_EnableIRQ(USBI_IRQn);       /* enable USBI interrupt */

} /*End of function usb_cpu_usbint_init */

/******************************************************************************
 Function Name   : usb_cpu_delay_1us
 Description     : 1us Delay timer
 Arguments       : uint16_t  time        ; Delay time(*1us)
 Return value    : none
 ******************************************************************************/
//void usb_cpu_delay_1us (uint16_t time)
//{
////    R_BSP_SoftwareDelay((uint32_t)time, BSP_DELAY_MICROSECS);
//} /*End of function usb_cpu_delay_1us */

/******************************************************************************
 Function Name   : usb_cpu_delay_xms
 Description     : xms Delay timer
 Arguments       : uint16_t  time        ; Delay time(*1ms)
 Return value    : none
 ******************************************************************************/
//void usb_cpu_delay_xms (uint16_t time)
//{
//    R_BSP_SoftwareDelay((uint32_t)time, BSP_DELAY_MILLISECS);
//} /*End of function usb_cpu_delay_xms */

#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
/******************************************************************************
 Function Name   : usb_cpu_int_enable
 Description     : USB Interrupt Enable
 Arguments       : none
 Return value    : none
 ******************************************************************************/
void usb_cpu_int_enable (void)
{
    /* Interrupt enable register (USB0 USBIO enable)
     b0 IEN0 Interrupt enable bit
     b1 IEN1 Interrupt enable bit
     b2 IEN2 Interrupt enable bit
     b3 IEN3 Interrupt enable bit
     b4 IEN4 Interrupt enable bit
     b5 IEN5 Interrupt enable bit
     b6 IEN6 Interrupt enable bit
     b7 IEN7 Interrupt enable bit
     */
    R_BSP_InterruptRequestEnable(VECT(USB0, USBI0)); /* Enable USB0 interrupt */
} /*End of function usb_cpu_int_enable */

/******************************************************************************
 Function Name   : usb_cpu_int_disable
 Description     : USB Interrupt disable
 Arguments       : none
 Return value    : none
 ******************************************************************************/
void usb_cpu_int_disable (void)
{
    /* Interrupt enable register (USB0 USBIO disable)
     b0 IEN0 Interrupt enable bit
     b1 IEN1 Interrupt enable bit
     b2 IEN2 Interrupt enable bit
     b3 IEN3 Interrupt enable bit
     b4 IEN4 Interrupt enable bit
     b5 IEN5 Interrupt enable bit
     b6 IEN6 Interrupt enable bit
     b7 IEN7 Interrupt enable bit
     */
    R_BSP_InterruptRequestDisable(VECT(USB0, USBI0)); /* Disable USB0 interrupt */
} /*End of function usb_cpu_int_disable */

#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */



/******************************************************************************
 Function Name   : usb_chattering
 Description     : Remove chattering processing
 Arguments       : uint16_t *p_syssts : SYSSTS register value
 Return value    : LNST bit value
 ******************************************************************************/
uint16_t usb_chattering (uint16_t *p_syssts)
{
    uint16_t lnst[4];

    /* WAIT_LOOP */
    while (1)
    {
        lnst[0] = (*p_syssts) & USB_LNST;
        usb_cpu_delay_xms((uint16_t) 1); /* 1ms wait */
        lnst[1] = (*p_syssts) & USB_LNST;
        usb_cpu_delay_xms((uint16_t) 1); /* 1ms wait */
        lnst[2] = (*p_syssts) & USB_LNST;
        if ((lnst[0] == lnst[1]) && (lnst[0] == lnst[2]))
        {
            break;
        }
    }
    return lnst[0];
} /*End of function usb_chattering */


/******************************************************************************
 Function Name   : usb_cpu_usb_interrupt
 Description     : USB interrupt Handler																										
 Arguments       : none
 Return value    : none
 ******************************************************************************/
static void usb_cpu_usb_interrupt (void)
{
    /* Call USB interrupt routine */
    if (USB_HOST == g_usb_cstd_usb_mode)
    {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
    usb_hstd_interrupt_handler();

#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }
    else
    {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        usb_pstd_usb_handler(); /* Call interrupt routine */

#endif  /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
    }
} /*End of function usb_cpu_usb_interrupt */


#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
/******************************************************************************
 Function Name   : usb_cpu_usb_resume_interrupt
 Description     :
 Arguments       : none
 Return value    : none
 ******************************************************************************/
static void usb_cpu_usb_resume_interrupt (void)
{
    hw_usb_pclear_sts_resm();
//    IPR(USB0,USBR0) = 0x00; /* Priority Resume1=0 */
//    IR(USB0, USBR0) = 0; /* Interrupt Request USB_resume USBR1 Clear */
} /* End of function usb_cpu_usb_resume_interrupt */
#endif

#if USB_CFG_DTC == USB_CFG_ENABLE
/******************************************************************************
Function Name   : usb_cpu_d0fifo_isr
Description     : D0FIFO interrupt Handler
Arguments       : none
Return value    : none
******************************************************************************/
static void usb_cpu_d0fifo_isr(void)
{
    IPR(USB0,D0FIFO0) = 0;
    usb_cstd_dma_send_complete(USB_D0USE);
} /*End of function usb_cpu_d0fifo_isr */


/******************************************************************************
Function Name   : usb_cpu_d1fifo_isr
Description     : D0FIFO interrupt Handler
Arguments       : none
Return value    : none
******************************************************************************/
static void usb_cpu_d1fifo_isr(void)
{
    IPR(USB0,D1FIFO0) = 0;
    usb_cstd_dma_send_complete(USB_D1USE);
}/*End of function usb_cpu_d1fifo_isr */

#endif /* USB_CFG_DTC == USB_CFG_ENABLE */



/******************************************************************************
End Of File
******************************************************************************/

