/*******************************************************************************
 * File Name    : usb_preg_access.c
 * Description  : USB IP Peripheral control register access code
 *****************************************************************************/
/******************************************************************************
 Includes   <System Includes> , "Project Includes"
 ******************************************************************************/
#include "usb_basic_mini_if.h"
#include "usb_typedef.h"
#include "usb_reg_access.h"
#include "usb_bitdefine.h"
#include "usb_extern.h"
#include "usb.h"

#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
/*******************************************************************************
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

/******************************************************************************
 Function Name   : hw_usb_pset_dprpu
 Description     : Set DPRPU-bit SYSCFG0 register.
                 : (Enable D+Line pullup when PeripheralController function is selected)
 Arguments       : none
 Return value    : none
 ******************************************************************************/
void hw_usb_pset_dprpu(void)
{
    USB0.SYSCFG.WORD |= USB_DPRPU;
} /* End of function hw_usb_pset_dprpu */

/******************************************************************************
 Function Name   : hw_usb_pclear_dprpu
 Description     : Clear DPRPU-bit of the SYSCFG0 register.
                 : (Disable D+Line pullup when PeripheralController function is
                 : selected.)
 Arguments       : none
 Return value    : none
 ******************************************************************************/
void hw_usb_pclear_dprpu(void)
{
    USB0.SYSCFG.WORD &= (~USB_DPRPU);
} /* End of function hw_usb_pclear_dprpu */

/******************************************************************************
 Function Name   : hw_usb_pset_wkup
 Description     : Set WKUP-bit DVSTCTR register.
                 : (Output Remote wakeup signal when PeripheralController function is selected)
 Arguments       : none
 Return value    : none
 ******************************************************************************/
void hw_usb_pset_wkup(void)
{
    USB0.DVSTCTR0.WORD |= USB_WKUP;
} /* End of function hw_usb_pset_dprpu */
/******************************************************************************
 End of function hw_usb_pset_wkup
 ******************************************************************************/

/******************************************************************************
 Function Name   : hw_usb_pset_enb_rsme
 Description     : Enable interrupt from RESUME
 Arguments       : none
 Return value    : none
 ******************************************************************************/
void hw_usb_pset_enb_rsme(void)
{
    USB0.INTENB0.WORD |= USB_RSME;
} /* End of function hw_usb_pset_enb_rsme */

/******************************************************************************
 Function Name   : hw_usb_pclear_enb_rsme
 Description     : Disable interrupt from RESUME
 Arguments       : none
 Return value    : none
 ******************************************************************************/
void hw_usb_pclear_enb_rsme(void)
{
    USB0.INTENB0.WORD &= (~USB_RSME);
} /* End of function hw_usb_pclear_enb_rsme */

/******************************************************************************
 Function Name   : hw_usb_pclear_sts_resm
 Description     : Clear interrupt status of RESUME.
 Arguments       : none
 Return value    : none
 ******************************************************************************/
void hw_usb_pclear_sts_resm(void)
{
    USB0.INTSTS0.WORD = (uint16_t)~USB_RESM;
} /* End of function hw_usb_pclear_sts_resm */

/******************************************************************************
 Function Name   : hw_usb_pclear_sts_valid
 Description     : Clear the Setup Packet Reception interrupt flag.
 Arguments       : none
 Return value    : none
 ******************************************************************************/
void hw_usb_pclear_sts_valid(void)
{
    USB0.INTSTS0.WORD = (uint16_t)~USB_VALID;
} /* End of function hw_usb_pclear_sts_valid */

/******************************************************************************
 Function Name   : hw_usb_pset_ccpl
 Description     : Enable termination of control transfer status stage.
 Arguments       : none
 Return value    : none
 ******************************************************************************/
void hw_usb_pset_ccpl(void)
{
    USB0.DCPCTR.WORD |= USB_CCPL;
} /* End of function hw_usb_pset_ccpl */

/******************************************************************************
 Function Name   : hw_usb_pmodule_init
 Description     : 
 Arguments       : none
 Return value    : none
 ******************************************************************************/
void hw_usb_pmodule_init( void )
{

    USB0.SYSCFG.WORD |= USB_SCKE;
    /* WAIT_LOOP */
    while (USB_SCKE != (USB0.SYSCFG.WORD & USB_SCKE))
    {
        /* Wait for Set of SCKE */
    }

    USB0.SYSCFG.WORD &= (~USB_DRPD);

    USB0.SYSCFG.WORD |= USB_USBE;
    USB0.CFIFOSEL.WORD  = USB0_CFIFO_MBW;
    USB0.D0FIFOSEL.WORD = USB0_D0FIFO_MBW;
    USB0.D1FIFOSEL.WORD = USB0_D1FIFO_MBW;
#if USB_CFG_ENDIAN == USB_CFG_BIG
    USB0.CFIFOSEL.WORD  |= USB_BIGEND;
    USB0.D0FIFOSEL.WORD |= USB_BIGEND;
    USB0.D1FIFOSEL.WORD |= USB_BIGEND;
#endif  /* USB_CFG_ENDIAN == USB_CFG_BIG */
    USB0.INTENB0.WORD = (USB_BEMPE | USB_BRDYE | USB_VBSE | USB_DVSE | USB_CTRE);

} /* End of function hw_usb_pmodule_init */

#endif  /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */

/******************************************************************************
 End of file
 ******************************************************************************/

