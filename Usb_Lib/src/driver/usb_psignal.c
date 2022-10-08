/******************************************************************************
 * File Name    : usb_psignal.c
 * Description  : USB Peripheral signal control code
 ******************************************************************************/

/******************************************************************************
 Includes   <System Includes> , "Project Includes"
 ******************************************************************************/

#include "usb_basic_mini_if.h"
#include "usb_typedef.h"
#include "usb_extern.h"
#include "usb_bitdefine.h"
#include "usb_reg_access.h"

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
 Function Name   : usb_pstd_bus_reset
 Description     : A USB bus reset was issued by the host. Execute relevant pro-
                 : cessing.
 Arguments       : none
 Return value    : none
 ******************************************************************************/
void usb_pstd_bus_reset (void)
{
    uint16_t connect_info;

    /* Bus Reset */
    usb_pstd_busreset_function();

    /* Memory clear */
    usb_pstd_clr_mem();
    connect_info = usb_cstd_port_speed();

    /* Callback */
    if (USB_NULL != g_usb_pstd_driver.devdefault)
    {
        #if USB_CFG_BC == USB_CFG_ENABLE
        (*g_usb_pstd_driver.devdefault)(USB_NULL, connect_info, g_usb_pstd_bc_detect);
        #else   /* USB_CFG_BC == USB_CFG_ENABLE */
        (*g_usb_pstd_driver.devdefault)(USB_NULL, connect_info, USB_NULL);
        #endif  /* USB_CFG_BC == USB_CFG_ENABLE */
    }

    /* DCP configuration register  (0x5C) */
    hw_usb_write_dcpcfg(0);

    /* DCP maxpacket size register (0x5E) */
    hw_usb_write_dcpmxps(g_usb_pstd_driver.p_devicetbl[USB_DEV_B_MAX_PACKET_SIZE_0]);

} /* End of function usb_pstd_bus_reset */

/******************************************************************************
 Function Name   : usb_pstd_attach_process
 Description     : USB attach setting.
 Arguments       : none
 Return value    : none
 ******************************************************************************/
void usb_pstd_attach_process (void)
{
    usb_cpu_delay_xms((uint16_t) 10);
    #if USB_CFG_BC == USB_CFG_ENABLE
    usb_pstd_bc_detect_process();

    #endif  /* USB_CFG_BC == USB_CFG_ENABLE */
    hw_usb_pset_dprpu();

} /* End of function usb_pstd_attach_process */


/******************************************************************************
 Function Name   : usb_pstd_detach_process
 Description     : Initialize USB registers for detaching, and call the callback
                 : function that completes the detach.
 Arguments       : none
 Return value    : none
 ******************************************************************************/
void usb_pstd_detach_process (void)
{
    uint16_t i;

    /* Pull-up disable */
    hw_usb_pclear_dprpu();

    /* Configuration number */
    g_usb_pstd_config_no = 0;

    /* Remote wakeup enable flag */
    g_usb_pstd_remote_wakeup = USB_FALSE;

    /* INTSTS0 clear */
    /*g_usb_pstd_intsts0 = 0;*/

    /* WAIT_LOOP */
    for (i = USB_MIN_PIPE_NO; i < (USB_MAXPIPE_NUM + 1); i++)
    {
        if (USB_TRUE == g_usb_cstd_pipe_tbl[i].use_flag)
        {
            usb_pstd_forced_termination(i, (uint16_t) USB_DATA_STOP);
            usb_cstd_clr_pipe_config(i);
        }
    }

    /* Callback */
    if (USB_NULL != g_usb_pstd_driver.devdetach)
    {
        (*g_usb_pstd_driver.devdetach)(USB_NULL, USB_NO_ARG, USB_NULL);
    }
} /* End of function usb_pstd_detach_process */

/******************************************************************************
 Function Name   : usb_pstd_suspend_process
 Description     : Perform a USB peripheral suspend.
 Arguments       : none
 Return value    : none
 ******************************************************************************/
void usb_pstd_suspend_process (void)
{
    uint16_t intsts0;
    uint16_t buf;

    /* Resume interrupt enable */
    hw_usb_pset_enb_rsme();

    intsts0 = hw_usb_read_intsts();
    buf = hw_usb_read_syssts();

    if (((uint16_t)0 != (intsts0 & USB_DS_SUSP)) && (USB_FS_JSTS == (buf & USB_LNST)))
    {
        /* Suspend */
        usb_pstd_suspend_function();

        /* Callback */
        if (USB_NULL != g_usb_pstd_driver.devsuspend)
        {
            (*g_usb_pstd_driver.devsuspend)(USB_NULL, g_usb_pstd_remote_wakeup, USB_NULL);
        }
    }

    /* --- SUSPEND -> RESUME --- */
    else
    {
        /* RESM status clear */
        hw_usb_pclear_sts_resm();

        /* RESM interrupt disable */
        hw_usb_pclear_enb_rsme();
    }
} /* End of function usb_pstd_suspend_process */

#endif  /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */

/******************************************************************************
 End  Of File
 ******************************************************************************/
