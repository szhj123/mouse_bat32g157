/******************************************************************************
 * File Name    : usb_iap_apl.h
 * Description  : USB Phelipheral HID Sample Code
 ******************************************************************************/

/******************************************************************************
 Includes   <System Includes> , "Project Includes"
 ******************************************************************************/

#include "usb_phid_mini_if.h"

#include <string.h>
#include "usb_basic_mini_if.h"

#ifndef USB_IAP_APL_H
#define USB_IAP_APL_H

/*******************************************************************************
 Macro definitions
 ******************************************************************************/
 //ISP COMMAND SET
#define FW_VERSION					0x31

#define CMD_UPDATE_APROM			0x000000A0
#define CMD_UPDATE_CONFIG			0x000000A1
#define CMD_READ_CONFIG				0x000000A2
#define CMD_ERASE_ALL				0x000000A3
#define CMD_SYNC_PACKNO				0x000000A4
#define CMD_GET_FWVER				0x000000A6
#define CMD_SET_APPINFO     		0x000000A7
#define CMD_GET_APPINFO     		0x000000A8
#define CMD_RUN_APROM				0x000000AB
#define CMD_RUN_LDROM				0x000000AC
#define CMD_RESET					0x000000AD
#define CMD_CONNECT					0x000000AE
#define CMD_DISCONNECT				0x000000AF

#define CMD_GET_DEVICEID			0x000000B1

#define CMD_UPDATE_DATAFLASH 		0x000000C3
#define CMD_WRITE_CHECKSUM 	 		0x000000C9
#define CMD_GET_FLASHMODE 	 		0x000000CA

#define CMD_RESEND_PACKET       	0x000000FF

#define	V6M_AIRCR_VECTKEY_DATA		0x05FA0000UL
#define V6M_AIRCR_SYSRESETREQ		0x00000004UL


/*******************************************************************************
 Typedef definitions
 ******************************************************************************/

/*******************************************************************************
 Exported global variables
 ******************************************************************************/

/*******************************************************************************
 Exported global functions (to be accessed by other files)
 ******************************************************************************/

#endif /* USB_IAP_APL_H */
/******************************************************************************
 End  Of File
 ******************************************************************************/
