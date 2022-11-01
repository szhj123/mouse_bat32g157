/******************************************************************************
 * File Name    : usb_clibusbip.c
 * Description  : USB IP Host and Peripheral low level library
 ******************************************************************************/

/******************************************************************************
 Includes   <System Includes> , "Project Includes"
 ******************************************************************************/
#include "usb_basic_mini_if.h"
#include "usb_bitdefine.h"
#include "usb_typedef.h"
#include "usb_reg_access.h"   /* Definition of the USB register access macro */
#include "usb_extern.h"

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
 Function Name   : usb_cstd_nrdy_enable
 Description     : Enable NRDY interrupt of the specified pipe.
 Arguments       : uint16_t pipe  : Pipe number.
 Return value    : none
 ******************************************************************************/
void usb_cstd_nrdy_enable (uint16_t pipe)
{
    if (USB_MAX_PIPE_NO < pipe)
    {
        return; /* Error */
    }

    /* Enable NRDY */
    hw_usb_set_nrdyenb(pipe);
} /* End of function usb_cstd_nrdy_enable */

/******************************************************************************
 Function Name   : usb_cstd_get_pid
 Description     : Fetch specified pipe's PID.
 Arguments       : uint16_t pipe  : Pipe number.
 Return value    : uint16_t PID-bit status
 ******************************************************************************/
uint16_t usb_cstd_get_pid (uint16_t pipe)
{
    uint16_t buf;

    if (USB_MAX_PIPE_NO < pipe)
    {
        return USB_NULL; /* Error */
    }

    /* PIPE control reg read */
    buf = hw_usb_read_pipectr(pipe);
    return (uint16_t) (buf & USB_PID);
} /* End of function usb_cstd_get_pid */

/******************************************************************************
 Function Name   : usb_cstd_get_pipe_dir
 Description     : Get PIPE DIR
 Arguments       : uint16_t pipe  : Pipe number.
 Return value    : uint16_t pipe direction.
 ******************************************************************************/
uint16_t usb_cstd_get_pipe_dir (uint16_t pipe)
{
    uint16_t buffer;

    if (USB_MAX_PIPE_NO < pipe)
    {
        return USB_NULL; /* Error */
    }

    /* Pipe select */
    hw_usb_write_pipesel(pipe);

    /* Read Pipe direction */
    buffer = hw_usb_read_pipecfg();
    return (uint16_t) (buffer & USB_DIRFIELD);
}/* End of function usb_cstd_get_pipe_dir */

/******************************************************************************
 Function Name   : usb_cstd_get_pipe_type
 Description     : Fetch and return PIPE TYPE.
 Arguments       : uint16_t pipe  : Pipe number.
 Return value    : uint16_t pipe type
 ******************************************************************************/
uint16_t usb_cstd_get_pipe_type (uint16_t pipe)
{
    uint16_t buffer;

    if (USB_MAX_PIPE_NO < pipe)
    {
        return USB_NULL; /* Error */
    }

    /* Pipe select */
    hw_usb_write_pipesel(pipe);

    /* Read Pipe direction */
    buffer = hw_usb_read_pipecfg();
    return (uint16_t) (buffer & USB_TYPFIELD);
} /* End of function usb_cstd_get_pipe_type */

/******************************************************************************
 Function Name   : usb_cstd_do_aclrm
 Description     : Set the ACLRM-bit (Auto Buffer Clear Mode) of the specified
                 : pipe.
 Arguments       : uint16_t pipe  : Pipe number.
 Return value    : none
 ******************************************************************************/
void usb_cstd_do_aclrm (uint16_t pipe)
{
    if (USB_MAX_PIPE_NO < pipe)
    {
        return; /* Error */
    }

    /* Control ACLRM */
    hw_usb_set_aclrm(pipe);
    hw_usb_clear_aclrm(pipe);
} /* End of function usb_cstd_do_aclrm */

/******************************************************************************
 Function Name   : usb_cstd_set_buf
 Description     : Set PID (packet ID) of the specified pipe to BUF.
 Arguments       : uint16_t pipe  : Pipe number.
 Return value    : none
 ******************************************************************************/
void usb_cstd_set_buf (uint16_t pipe)
{
    if (USB_MAX_PIPE_NO < pipe)
    {
        return; /* Error */
    }

    /* PIPE control reg set */
    hw_usb_set_pid(pipe, USB_PID_BUF);
} /* End of function usb_cstd_set_buf */

/******************************************************************************
 Function Name   : usb_cstd_clr_stall
 Description     : Set up to NAK the specified pipe, and clear the STALL-bit set
                 : to the PID of the specified pipe.
 Arguments       : uint16_t pipe  : Pipe number.
 Return value    : none
 Note            : PID is set to NAK.
 ******************************************************************************/
void usb_cstd_clr_stall (uint16_t pipe)
{
    if (USB_MAX_PIPE_NO < pipe)
    {
        return; /* Error */
    }

    /* Set NAK */
    usb_cstd_set_nak(pipe);

    /* Clear STALL */
    hw_usb_clear_pid(pipe, USB_PID_STALL);
} /* End of function usb_cstd_clr_stall */

/******************************************************************************
Function Name   : usb_cstd_port_speed
Description     : Check current port speed
Arguments       : none
Return value    : uint16_t          ; FSCONNECT : Full-Speed
               :                   ; LSCONNECT : Low-Speed
               :                   ; NOCONNECT : not connect
******************************************************************************/
uint16_t usb_cstd_port_speed(void)
{
    uint16_t    buf;

    /* Reset handshake status get */
    buf = hw_usb_read_dvstctr();
    buf = (uint16_t) (buf & USB_RHST);

    /* Check RHST */
    if (USB_FSMODE == buf)
    {
        return  (USB_FSCONNECT);
    }

    if (USB_LSMODE == buf)
    {
        return  (USB_LSCONNECT);
    }

    return  (USB_NOCONNECT);
} /* End of function usb_cstd_port_speed */

/******************************************************************************
 End  Of File
 ******************************************************************************/
