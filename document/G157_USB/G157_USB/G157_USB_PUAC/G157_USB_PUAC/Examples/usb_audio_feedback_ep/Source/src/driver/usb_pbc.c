/*******************************************************************************
*  File Name    : usb_pbc.c
* Description  : This is the USB peripheral battery charging code.
 ******************************************************************************/
/******************************************************************************
Includes <System Includes> , "Project Includes"
******************************************************************************/
#include "usb_basic_mini_if.h"
#include "usb_typedef.h"
#include "usb_extern.h"
#include "usb_reg_access.h"
#include "usb_bitdefine.h"

#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)

#if USB_CFG_BC == USB_CFG_ENABLE
/*******************************************************************************
 Macro definitions
 ******************************************************************************/
#define USB_BC_DCD_TIME         (600)
#define USB_BC_DCD_DBNC         (11)
#define USB_BC_VDPSRC_ON        (42)
#define USB_BC_VDMSRC_DIS       (22)
#define USB_BC_VDMSRC_ON        (42)

#define USB_BC_DCD_TIMEOUT      (0)
#define USB_BC_DCD_COMP_SE0     (1)


/*******************************************************************************
 Typedef definitions
 ******************************************************************************/


/*******************************************************************************
 Exported global variables (to be accessed by other files)
 ******************************************************************************/
/* variables */
uint16_t g_usb_pstd_bc_detect;

/* functions */


/*******************************************************************************
 Private global variables and functions
 ******************************************************************************/
/* variables */

/* functions */
USB_STATIC uint8_t usb_pstd_bc_data_contact_detect(void);
USB_STATIC uint8_t usb_pstd_bc_primary_detection(void);
USB_STATIC uint8_t usb_pstd_bc_secondary_detection(void);


/******************************************************************************
Function Name   : usb_pstd_bc_detect_process
Description     : Charging Port Detect Process
Arguments       : none
Return value    : none
******************************************************************************/
void usb_pstd_bc_detect_process(void)
{
    usb_ctrl_t ctrl;

    hw_usb_set_batchge();
    usb_pstd_bc_data_contact_detect ();

    if (usb_pstd_bc_primary_detection())
    {
        if (usb_pstd_bc_secondary_detection())
        {
            g_usb_pstd_bc_detect = USB_DCP;
        }
        else
        {
            g_usb_pstd_bc_detect = USB_CDP;
        }

        usb_cstd_set_event(USB_STS_BC, &ctrl);

    }
    else
    {
        g_usb_pstd_bc_detect = USB_SDP;
    }

    hw_usb_clear_batchge();
}   /* End of function usb_pstd_bc_detect_process() */


/******************************************************************************
Function Name   : usb_pstd_bc_data_contact_detect
Description     : Data Contact Detect
Arguments       : none
Return value    : uint8_t : DCD Complete Status
******************************************************************************/
USB_STATIC uint8_t usb_pstd_bc_data_contact_detect (void)
{
    uint16_t    buf;
    uint16_t    timer = 0;


    hw_usb_set_cnen();
    hw_usb_set_bcctrl(USB_IDPSRCE | USB_RPDME);
    usb_cpu_delay_xms((uint16_t)5);                                 /* wait stabilization */

    /* WAIT_LOOP */
    while (timer < USB_BC_DCD_TIME)                               /* [BC1.2 Spec] DCD_TIMEOUT (300-900ms) */
    {
        buf = hw_usb_read_syssts ();

        if ((buf & USB_LNST) == USB_SE0)
        {
            usb_cpu_delay_xms ((uint16_t)USB_BC_DCD_DBNC);           /* [BC1.2 Spec] DCD_DBNC (min:10ms) */
            timer += USB_BC_DCD_DBNC;
            buf = hw_usb_read_syssts ();

            if ((buf & USB_LNST) == USB_SE0)
            {
                hw_usb_clear_bcctrl (USB_IDPSRCE | USB_RPDME);
                hw_usb_clear_cnen();
                return USB_BC_DCD_COMP_SE0;                         /* Connected Data Line */
            }
        }

        usb_cpu_delay_xms ((uint16_t)1);
        timer++;
    }

    hw_usb_clear_bcctrl (USB_IDPSRCE | USB_RPDME);
    hw_usb_clear_cnen();

    return USB_BC_DCD_TIMEOUT;                                      /* DCD Timeout */
}   /* End of function usb_pstd_bc_data_contact_detect() */


/******************************************************************************
Function Name   : usb_pstd_bc_primary_detection
Description     : Primary Detection
Arguments       : none
Return value    : uint8_t : Detection Port
******************************************************************************/
USB_STATIC uint8_t usb_pstd_bc_primary_detection (void)
{
    uint16_t    buf;

    hw_usb_set_bcctrl ((USB_VDPSRCE | USB_IDMSINKE));

    usb_cpu_delay_xms ((uint16_t)USB_BC_VDPSRC_ON);          /* [BC1.2 Spec] TVDPSRC_ON (min:40ms) */
    buf = hw_usb_read_bcctrl ();
    hw_usb_clear_bcctrl ((USB_VDPSRCE | USB_IDMSINKE));
    usb_cpu_delay_xms ((uint16_t)USB_BC_VDMSRC_DIS);         /* [BC1.2 Spec] TVDMSRC_DIS (max:20ms) */

    if (buf & USB_CHGDETSTS)
    {
        return 1;                                           /* Detected Charging Port */
    }
    else
    {
        return 0;                                           /* Detected SDP */
    }
}   /* End of function usb_pstd_bc_primary_detection() */


/******************************************************************************
Function Name   : usb_pstd_bc_secondary_detection
Description     : Secondary Detection
Arguments       : none
Return value    : uint8_t : Detection Port
******************************************************************************/
USB_STATIC uint8_t usb_pstd_bc_secondary_detection(void)
{
    uint16_t    buf;

    hw_usb_set_bcctrl ((USB_VDMSRCE | USB_IDPSINKE));
    usb_cpu_delay_xms ((uint16_t)USB_BC_VDMSRC_ON);          /* [BC1.2 Spec] TVDMSRC_ON (min:40ms) */
    buf = hw_usb_read_bcctrl ();
    hw_usb_clear_bcctrl ((USB_VDMSRCE | USB_IDPSINKE));

    if (buf & USB_PDDETSTS)
    {
        return 1;                                           /* Detected DCP */
    }
    else
    {
        return 0;                                           /* Detected CDP */
    }
}   /* End of function usb_pstd_bc_secondary_detection() */

#endif /* USB_CFG_BC == USB_CFG_ENABLE */

#endif  /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */

/******************************************************************************
End of file
******************************************************************************/
