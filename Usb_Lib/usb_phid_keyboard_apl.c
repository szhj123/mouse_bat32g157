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

#if OPERATION_MODE == USB_KEYBOARD

/*******************************************************************************
 Macro definitions
 ******************************************************************************/

#define DATA_LEN                (8)
#define HID_DESCRIPTOR_SIZE     (9)
#define REPORT_DESCRIPTOR_SIZE  (76)
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

static  uint8_t         gs_data[]    = {0, 0, 0, 0, 0, 0, 0, 0}; /* HID data */
static  uint8_t         gs_status    = NO_WRITING;           /* HID device is the HID data transfer status or not */
static  uint16_t        gs_numlock   = 0;
static  uint8_t         gs_idle      = 0;

const static uint8_t    gs_zero_data[] = {0, 0, 0, 0, 0, 0, 0, 0}; /* zero data */
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

typedef enum
{
    LETTER = 0,
    NUMBER,
} display_type;
display_type dsp_type;
static void get_hid_data (display_type dsp_type, uint8_t *p_buf);

uint16_t g_key_flag = 0;
void key_input_init(void);
uint16_t key_input_check(void);


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
    display_type     dsp_type;
    uint8_t     *p_idle_value;
    usb_info_t  info;
    usb_err_t   ret_code = USB_SUCCESS;

    key_input_init();
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
                gs_status = NO_WRITING;
                #if defined(USE_LPW)
                    /* Do Nothing */
                #endif /* defined(USE_LPW) */
                break;

            case USB_STS_WRITE_COMPLETE :
                if(DATA_WRITING == gs_status)
                {
                    gs_status = ZERO_WRITING;
                    /* Sending the zero data (8 bytes) */
                    ctrl.type = USB_PHID;
                    USB_Write(&ctrl, (uint8_t *)gs_zero_data, DATA_LEN);
                }
                else
                {
                    gs_status = NO_WRITING;
                }

                break;

            case USB_STS_REQUEST : /* Receive Class Request */
                if (USB_REQUEST_TYPE_CLASS == (ctrl.setup.type & USB_REQUEST_TYPE_CLASS))
                {
                    if (USB_SET_REPORT == (ctrl.setup.type & USB_BREQUEST))
                    {
                        /* Get the NumLock data (NumLock data is not used) */
                        USB_Read(&ctrl, (uint8_t *)&gs_numlock, 2);
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
                        if (1 <= key_input_check())
                        {
                            g_key_flag = 0;

                            if (NO_WRITING == gs_status)
                            {
                                dsp_type = LETTER;
                                get_hid_data(dsp_type, gs_data);
                                gs_status = DATA_WRITING;
                                ctrl.type = USB_PHID;
                                USB_Write(&ctrl, gs_data, DATA_LEN);
                            }
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


/******************************************************************************
  * Function Name: get_hid_data
  * Description  : Keyborad mode data update by the RSK Switch input.
  * Arguments    : display_type dsp_type  : Display character or number
                 : uint8_t *p_buf   : Buffer area for storing the HID data
  * Return Value : none
 ******************************************************************************/
static void get_hid_data (display_type dsp_type, uint8_t *p_buf)
{
    static  uint8_t     key_data;

    /* Branch by the RSK Switch Input. */
    switch (dsp_type)
    {
        case LETTER :     /* a - z */
            if (KBD_CODE_Z == key_data) /* Keyboard data check == "Z" */
            {
                key_data = KBD_CODE_ENTER; /* Keyboard data "Enter" set. */
            }
            else if (((KBD_CODE_A - 1) < key_data) && (key_data < KBD_CODE_Z))
            {
                /* Keyboard data update A to Y => B to Z */
                key_data++;
            }
            else
            {
                key_data = KBD_CODE_A; /* Keyboard data "A" set. */
            }

            break;

        case NUMBER :     /* 0 - 9 */
            if (KBD_CODE_0 == key_data) /* keyboard data check == "0" */
            {
                key_data = KBD_CODE_ENTER; /* keyboard data "Enter" set. */
            }
            else if (((KBD_CODE_1 - 1) < key_data) && (key_data < KBD_CODE_0))
            {
                /* Keyboard data update 1 to 9 => 2 to 0 */
                key_data++;
            }
            else
            {
                key_data = KBD_CODE_1; /* keyboard data "1" set. */
            }

            break;

        default :
            if (KBD_CODE_0 == key_data) /* keyboard data check == "0" */
            {
                key_data = KBD_CODE_ENTER; /* keyboard data "Enter" set. */
            }
            else if (((KBD_CODE_1 - 1) < key_data) && (key_data < KBD_CODE_0))
            {
                /* Keyboard data update 1 to 9 => 2 to 0 */
                key_data++;
            }
            else
            {
                key_data = KBD_CODE_1; /* keyboard data "1" set. */
            }

            break;
    }

    *(p_buf + 2) = key_data;
} /* End of function get_hid_data */

void key_input_init(void)
{
    PORT->PMCA &= ~(1 << 2);	  // PA02 digital IO
    PORT->PMA |= (1 << 2);		  // PA02 intput
    PORT->PUA |= (1 << 2);		  // PA02 pullup enable
}

uint16_t g_key_counter;
uint16_t key_input_check(void)
{
    /* Check PA02 */
    if (0 == (PORT->PA & 0x0004))
    {
        if (g_key_counter < 3)
        {
            g_key_counter++;
        }
    }
    else
    {
        if (g_key_counter >= 3)
        {
            g_key_flag = 1;
        }
        else
        {
        }

        g_key_counter = 0;
    }

    return g_key_flag;
}

#endif  /* OPERATION_MODE == USB_KEYBOARD */

/******************************************************************************
 End  Of File
 ******************************************************************************/

