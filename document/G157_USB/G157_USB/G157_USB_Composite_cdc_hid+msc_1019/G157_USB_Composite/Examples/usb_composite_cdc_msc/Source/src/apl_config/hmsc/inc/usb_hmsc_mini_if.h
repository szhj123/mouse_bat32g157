/***********************************************************************************************************************
 * File Name    : usb_hmsc_mini_if.h
 * Description  : Interface file for USB HMSC API
 ***********************************************************************************************************************/

#ifndef USB_HMSC_MINI_IF_H
#define USB_HMSC_MINI_IF_H

/**********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 ***********************************************************************************************************************/
#include "usb_hmsc.h"
#include "usb_hmsc_mini_config.h"

/**********************************************************************************************************************
Macro definitions
 ***********************************************************************************************************************/
#define USB_HMSC_DEV_DET    (0x00)      /* detached device */
#define USB_HMSC_DEV_ATT    (0x01)      /* attached device */

/* subClass code */
#define USB_ATAPI_MMC5      (0x02)     /* ATAPI for CD-ROMs.  SFF-8020i */
#define USB_ATAPI           (0x05)     /* ATAPI for Floppies. SFF-8070i */
#define USB_SCSI            (0x06)     /* SCSI transparent command set */

/* Protocol code */
#define USB_BOTP            (0x50)     /* BOT:Bulk Only Transport */

#define USB_TOTALEP         (0x02)     /* Total EP Num */

/**********************************************************************************************************************
 Typedef definitions
 ***********************************************************************************************************************/
typedef enum
{
    /*--- SFF-8070i command define ---*/
    USB_ATAPI_TEST_UNIT_READY       = (0x00u),
    USB_ATAPI_REQUEST_SENSE         = (0x03u),
    USB_ATAPI_FORMAT_UNIT           = (0x04u),
    USB_ATAPI_INQUIRY               = (0x12u),
    USB_ATAPI_MODE_SELECT6          = (0x15u),
    USB_ATAPI_MODE_SENSE6           = (0x1Au),
    USB_ATAPI_START_STOP_UNIT       = (0x1Bu),
    USB_ATAPI_PREVENT_ALLOW         = (0x1Eu),
    USB_ATAPI_READ_FORMAT_CAPACITY  = (0x23u),
    USB_ATAPI_READ_CAPACITY         = (0x25u),
    USB_ATAPI_READ10                = (0x28u),
    USB_ATAPI_WRITE10               = (0x2Au),
    USB_ATAPI_SEEK                  = (0x2Bu),
    USB_ATAPI_WRITE_AND_VERIFY      = (0x2Eu),
    USB_ATAPI_VERIFY10              = (0x2Fu),
    USB_ATAPI_MODE_SELECT10         = (0x55u),
    USB_ATAPI_MODE_SENSE10          = (0x5Au),
}usb_atapi_t;

typedef enum
{
    USB_CSW_SUCCESS = (0x00u),
    USB_CSW_FAIL    = (0x01u),
    USB_CSW_PHASE   = (0x02u),
}usb_csw_result_t;

/**********************************************************************************************************************
 Exported global functions (to be accessed by other files)
 ***********************************************************************************************************************/
usb_err_t       USB_HmscStrgCmd (uint8_t *p_buf, uint16_t command);
#if (BSP_CFG_RTOS_USED != 0)    /* Use RTOS */
void            USB_HmscGetSem (void);
void            USB_HmscRelSem (void);
#endif /* (BSP_CFG_RTOS_USED != 0) */

uint16_t usb_hmsc_StrgReadSector (uint16_t side, uint8_t *p_buff, uint32_t secno, uint16_t seccnt,
        uint32_t trans_byte);
uint16_t USB_HmscStrgWriteSector (uint16_t side, uint8_t *p_buff, uint32_t secno, uint16_t seccnt,
        uint32_t trans_byte);

#endif  /* USB_HMSC_MINI_IF_H */

/***********************************************************************************************************************
End  Of File
***********************************************************************************************************************/
