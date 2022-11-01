/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2019        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "ff.h"			/* Obtains integer types */
#include "diskio.h"		/* Declarations of disk functions */
#include "usb_hmsc.h"
#include "usb_hmsc_mini_if.h"

void usb_mini_hmsc_WaitLoop(void);
	
static volatile DSTATUS state = STA_NOINIT; /* disk status */
extern uint32_t g_hmsc_sector_size, g_hmsc_sector_count;


/* Definitions of physical drive number for each drive */
#define DEV_RAM		0	/* Example: Map Ramdisk to physical drive 0 */
#define DEV_MMC		1	/* Example: Map MMC/SD card to physical drive 1 */
#define DEV_USB		2	/* Example: Map USB MSD to physical drive 2 */

/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
	return RES_OK;
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
	uint16_t   res[10];
	usb_hstd_DeviceInformation(0, (uint16_t *)res); /* Get device connect state */
	if ( USB_STS_DETACH == res[1] )    /* Check detach */
	{
			return RES_ERROR;
	}
	state &= ~STA_NOINIT;
	return RES_OK;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	LBA_t sector,	/* Start sector in LBA */
	UINT count		/* Number of sectors to read */
)
{
	uint16_t  res[10];
	uint16_t  result;
	uint32_t  tran_byte;
	usb_tskinfo_t   *p_mess;
	usb_tskinfo_t   *mes;
  usb_er_t    err;
	uint8_t devaddr = 0;

  /* set transfer length */
	tran_byte = (uint32_t)count * g_hmsc_sector_size;
	
	usb_hstd_DeviceInformation(devaddr, res);
	if(USB_STS_DETACH == res[1])
	{
		return RES_ERROR;
	}
	
	result = usb_hmsc_StrgReadSector((uint16_t)pdrv, buff, sector, (uint16_t)count, tran_byte);
	if (USB_OK == result )
	{
			do  /* Wait for complete R_usb_hmsc_StrgReadSector() */
			{
					usb_hstd_DeviceInformation(devaddr, (uint16_t *)res);         /* Get device connect state */
					usb_mini_hmsc_WaitLoop();                                                      /* Task Schedule */
					err = USB_RCV_MSG(USB_HSTRG_MBX, (usb_msg_t**)&p_mess);     /* Receive read complete msg */
			}
			while ( (err != USB_OK) && (res[1] != USB_STS_DETACH) );

			if ( err == USB_OK )
			{   /* Complete usb_hmsc_StrgReadSector() */
					mes = (usb_tskinfo_t *)p_mess;
					err = mes->keyword;
					USB_REL_BLK(p_mess->flag);
			}
			else
			{   /* Device detach */
					usb_mini_hmsc_WaitLoop();                                                      /* Task Schedule */
					err = USB_RCV_MSG(USB_HSTRG_MBX, (usb_msg_t**)&p_mess);     /* Receive read complete msg */
					if ( USB_OK == err )
					{
							USB_REL_BLK(p_mess->flag);
					}
					err = USB_ERROR;
			}
		}

    if ( err != USB_OK )
    {
        return RES_ERROR;
    }

	return RES_OK;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if FF_FS_READONLY == 0

DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	LBA_t sector,		/* Start sector in LBA */
	UINT count			/* Number of sectors to write */
)
{
    uint16_t        res[10];
    usb_tskinfo_t   *p_mess;
    usb_tskinfo_t   *mes;
    uint16_t        err;
    uint32_t        tran_byte;
		uint8_t devaddr = 0;

    /* set transfer length */
    tran_byte = (uint32_t)count * g_hmsc_sector_size;

    usb_hstd_DeviceInformation(devaddr, (uint16_t *)res); /* Get device connect state */
    if ( USB_STS_DETACH == res[1] )    /* Check detach */
    {
        return RES_ERROR;
    }

    /* write function */
    err = USB_HmscStrgWriteSector((uint16_t)pdrv, (uint8_t *)buff
                                     , sector, (uint16_t)count, tran_byte);
    if ( USB_OK == err )
    {
        do  /* Wait for complete R_usb_hmsc_StrgWriteSector() */
        {
            usb_hstd_DeviceInformation(devaddr, (uint16_t *)res); /* Get device connect state */
            usb_mini_hmsc_WaitLoop();                                                      /* Task Schedule */
            err = USB_RCV_MSG(USB_HSTRG_MBX, (usb_msg_t**)&p_mess);    /* Receive write complete msg */
        }
        while ( ( err != USB_OK ) && ( res[1] != USB_STS_DETACH ) );

        if ( err == USB_OK )
        {   /* Complete R_usb_hmsc_StrgReadSector() */
            mes = (usb_tskinfo_t *)p_mess;
            err = mes->keyword;
            USB_REL_BLK(p_mess->flag);
        }
        else
        {   /* Device detach */
            usb_mini_hmsc_WaitLoop();                                                      /* Task Schedule */
            err = USB_RCV_MSG(USB_HSTRG_MBX, (usb_msg_t**)&p_mess);     /* Receive read complete msg */
            if ( USB_OK == err )
            {
                USB_REL_BLK(p_mess->flag);
            }
            err = USB_ERROR;
        }
    }

    if ( err != USB_E_OK )
    {
        return RES_ERROR;
    }
	return RES_OK;
}

#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	  DRESULT res = RES_OK;

    if (pdrv) {
        return RES_PARERR;
    }

    res = RES_ERROR;

    if (state & STA_NOINIT) {
        return RES_NOTRDY;
    }

    switch (cmd) {
    /* make sure that no pending write process */
    case CTRL_SYNC:
        res = RES_OK;
        break;

    /* get number of sectors on the disk (dword) */
    case GET_SECTOR_COUNT:
        *(DWORD*)buff = (DWORD)g_hmsc_sector_count;
        res = RES_OK;
        break;

    /* get r/w sector size (word) */
    case GET_SECTOR_SIZE:
        *(WORD*)buff = (DWORD)g_hmsc_sector_size;
        res = RES_OK;
        break;

    /* get erase block size in unit of sector (dword) */
    case GET_BLOCK_SIZE:
        *(DWORD*)buff = 512;
        break;

    default:
        res = RES_PARERR;
        break;
    }

    return res;
}

/******************************************************************************
Function Name   : usb_mini_hmsc_WaitLoop
Description     : Hmsc wait loop function
Arguments       : none
Return value    : none
******************************************************************************/
void usb_mini_hmsc_WaitLoop(void)
{
    if( usb_hstd_scheduler() == USB_FLGSET )
    {
				usb_hstd_hcd_task();                /* USB Host driver task */
				usb_hstd_mgr_task();                /* USB Manager task */
				usb_hstd_class_task();
    }
}
