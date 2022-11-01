/***********************************************************************************************************************
 * File Name    : usb_hmsc.h
 * Description  : USB Host MSC header file
 ***********************************************************************************************************************/

#ifndef USB_HMSC_H
#define USB_HMSC_H

/******************************************************************************
 Includes   <System Includes> , "Project Includes"
 ******************************************************************************/

#include "usb_basic_mini_if.h"
#include "usb_bitdefine.h"
#include "usb_typedef.h"
#include "usb_extern.h"

/*****************************************************************************
 Macro definitions
 ******************************************************************************/
/* CBW CSW definitions */
#define     USB_MSC_CBWLENGTH       (31u)
#define     USB_MSC_CBWCB_LENGTH    (12u)
#define     USB_MSC_CSW_LENGTH      (13u)

/* CPU bit endian select (BIT_LITTLE:little, BIT_BIG:big) */
#if USB_CFG_ENDIAN == USB_CFG_BIG
#define    USB_MSC_CBW_SIGNATURE   ((uint32_t)0x55534243u)
#define    USB_MSC_CSW_SIGNATURE   ((uint32_t)0x55534253u)
#else   /* USB_CFG_ENDIAN == USB_CFG_BIG */
#define    USB_MSC_CBW_SIGNATURE   ((uint32_t)0x43425355u)
#define    USB_MSC_CSW_SIGNATURE   ((uint32_t)0x53425355u)
#endif  /* USB_CFG_ENDIAN == USB_CFG_BIG */

/* Message code */
#define USB_MSG_HMSC_NO_DATA                (0x51u)
#define USB_MSG_HMSC_DATA_IN                (0x52u)
#define USB_MSG_HMSC_DATA_OUT               (0x53u)
#define USB_MSG_HMSC_CSW_PHASE_ERR          (0x55u)

#define USB_MSG_HMSC_STRG_DRIVE_SEARCH      (0x61u)
#define USB_MSG_HMSC_STRG_DRIVE_SEARCH_END  (0x62u)
#define USB_MSG_HMSC_STRG_USER_COMMAND      (0x67u)

#define usb_hstd_DeviceInformation    (usb_hstd_device_information)
#define usb_ghmsc_RootDevaddr           (g_usb_hmsc_root_devaddr)
#define usb_hmsc_Task                 (usb_hstd_class_task)
#define usb_hstd_HcdTask              (usb_hstd_hcd_task)
#define usb_hstd_MgrTask              (usb_hstd_mgr_task)

/* Host Sample Task */
#define USB_HSTRG_TSK                   (USB_TID_3)           /* Task ID */
#define USB_HSTRG_MBX                   (USB_HSTRG_TSK)       /* Mailbox ID */

/* Class Request Buffer Size */
#define USB_HMSC_CLSDATASIZE                (512u)
#define USB_HMSC_STRG_SECTSIZE              (512u) /* 512 bytes per sector */

/*****************************************************************************
 Typedef definitions
 ******************************************************************************/

typedef void    (*usb_hmsc_cb_t)(usb_tskinfo_t * p_complete);

/* CBW Structure define.    */
//R_BSP_PRAGMA_UNPACK	
typedef struct
{
    uint32_t    dcbw_signature;
    uint32_t    dcbw_tag;
    uint8_t     dcbw_dtl_lo;
    uint8_t     dcbw_dtl_ml;
    uint8_t     dcbw_dtl_mh;
    uint8_t     dcbw_dtl_hi;
//    union {
//        uint8_t    BYTE;
//        R_BSP_ATTRIB_STRUCT_BIT_ORDER_RIGHT_2(
//            uint8_t reserved7:7,
//            uint8_t cbw_dir:1
//        )BIT;
//    } bm_cbw_flags;
//    union {
//        uint8_t    BYTE;
//        R_BSP_ATTRIB_STRUCT_BIT_ORDER_RIGHT_2(
//            uint8_t bcbw_lun:4,
//            uint8_t reserved4:4
//        )BIT;
//    } bcbw_lun;
//    union {
//        uint8_t    BYTE;
//        R_BSP_ATTRIB_STRUCT_BIT_ORDER_RIGHT_2(
//            uint8_t bcbwcb_length:5,
//            uint8_t reserved3:3
//        )BIT;
//    } bcbwcb_length;

		//laidi
    union {
        uint8_t    BYTE;
        struct{
            uint8_t reserved7:7;
            uint8_t cbw_dir:1;
        }BIT;
    } bm_cbw_flags;
    union {
        uint8_t    BYTE;
       struct{
            uint8_t bcbw_lun:4;
            uint8_t reserved4:4;
			 }BIT;
    } bcbw_lun;
    union {
        uint8_t    BYTE;
        struct{
            uint8_t bcbwcb_length:5;
            uint8_t reserved3:3;
        }BIT;
    } bcbwcb_length;
    uint8_t cbwcb[(16 + 33)];
}
USB_MSC_CBW_t;
//R_BSP_PRAGMA_PACKOPTION

/* CSW Structure define define. */
typedef struct
{
    uint32_t dcsw_signature;
    uint32_t dcsw_tag;
    uint8_t  dcsw_data_residue_lo;
    uint8_t  dcsw_data_residue_ml;
    uint8_t  dcsw_data_residue_mh;
    uint8_t  dcsw_data_residue_hi;
    uint8_t  dcsw_status;
    uint8_t  dummy[(64 - 13)];      /* DTC Receive Size dummy (MAX Packet size = 64Byte) */
}
USB_MSC_CSW_t;


/* ERROR CODE */
typedef enum
{
    USB_HMSC_OK             = (0),
    USB_HMSC_STALL          = (0xff),
    USB_HMSC_CBW_ERR        = (0xfe),     /* CBR error */
    USB_HMSC_DAT_RD_ERR     = (0xfd),     /* Data IN error */
    USB_HMSC_DAT_WR_ERR     = (0xfc),     /* Data OUT error */
    USB_HMSC_CSW_ERR        = (0xfb),     /* CSW error */
    USB_HMSC_CSW_PHASE_ERR  = (0xfa),     /* Phase error */
    USB_HMSC_SUBMIT_ERR     = (0xf9),     /* submit error */
}usb_hmsc_error_t;

/* CSW STATUS */
typedef enum
{
    USB_MSC_CSW_OK          = (0x00u),
    USB_MSC_CSW_NG          = (0x01u),
    USB_MSC_CSW_PHASE_ERR   = (0x02u)
}usb_gcmsc_cswsts_t;

/* USB Mass Storage Device Class Request code define. */
typedef enum
{
    USB_MASS_STORAGE_RESET  = (0xFF00u), /* Mass dtorage reset request. */
    USB_GET_MAX_LUN         = (0xFE00u), /* Get max logical unit number */
}
usb_msc_request_t;

/*****************************************************************************
 Private global variables and functions
 ******************************************************************************/
extern uint8_t g_usb_hmsc_data[];

/*****************************************************************************
 Exported global functions (to be accessed by other files)
 ******************************************************************************/

uint16_t usb_hmsc_get_device_status (void);
uint16_t usb_hmsc_read10 (uint8_t *p_buff, uint32_t secno, uint16_t seccnt, uint32_t trans_byte);
uint16_t usb_hmsc_write10 (uint8_t *p_buff, uint32_t secno, uint16_t seccnt, uint32_t trans_byte);
uint16_t usb_hmsc_strg_drive_close (void);
uint16_t usb_hmsc_inquiry (uint8_t *p_buff);
uint16_t usb_hmsc_mode_select10 (uint8_t *p_buff);
uint16_t usb_hmsc_mode_sense10 (uint8_t *p_buff);
uint16_t usb_hmsc_prevent_allow (uint8_t *p_buff);
uint16_t usb_hmsc_read_capacity (uint8_t *p_buff);
uint16_t usb_hmsc_read_format_capacity (uint8_t *p_buff);
uint16_t usb_hmsc_request_sense (uint8_t *p_buff);
uint16_t usb_hmsc_test_unit (void);
#if (BSP_CFG_RTOS_USED != 0)    /* Use RTOS */
uint16_t usb_hmsc_set_device_status (uint16_t data);
uint16_t usb_hmsc_strg_drive_search (void);
usb_er_t usb_hmsc_get_max_unit (void);
uint16_t usb_hmsc_strg_user_command (uint16_t command, uint8_t *p_buff);
uint16_t usb_hmsc_strg_drive_open (void);
uint16_t usb_hmsc_error_process (uint16_t err_code);
#else  /* (BSP_CFG_RTOS_USED != 0) */
uint16_t usb_hmsc_strg_drive_search (usb_hmsc_cb_t complete);
usb_er_t usb_hmsc_get_max_unit (usb_hcb_t complete);
uint16_t usb_hmsc_strg_user_command (uint16_t command, uint8_t *p_buff, usb_hmsc_cb_t complete);
void     usb_hstd_device_information (usb_addr_t addr, uint16_t *p_table);
void     usb_hmsc_strg_cmd_complete (usb_tskinfo_t *p_mess);
#endif /* (BSP_CFG_RTOS_USED != 0) */

#endif  /* USB_HMSC_H */
/******************************************************************************
 End  Of File
 ******************************************************************************/
