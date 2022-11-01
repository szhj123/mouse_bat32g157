/******************************************************************************
 * File Name     : ram_disk.c
 * Description   : Implements top level of API compliant block media driver for 'RAM-disk'.
 ******************************************************************************/

/******************************************************************************
 Includes   <System Includes> , "Project Includes"
 ******************************************************************************/

#include <string.h>
#include "ext_flash_disk.h"
#include "spiflash.h"
#include <stdio.h>

/*******************************************************************************
 Macro definitions
 ******************************************************************************/

/*******************************************************************************
 Typedef definitions
 ******************************************************************************/

/*******************************************************************************
 Private global variables and functions
 ******************************************************************************/

static usb_media_ret_t ext_flash_disk_open (void);
static usb_media_ret_t ext_flash_disk_close (void);
static usb_media_ret_t ext_flash_disk_read (uint8_t* read_buffer, uint32_t sector, uint8_t sector_count);
static usb_media_ret_t ext_flash_disk_write (uint8_t* write_buffer, uint32_t sector, uint8_t sector_count);
static usb_media_ret_t ext_flash_disk_ioctl (uint8_t command_code, uint32_t* data_buffer);

/*******************************************************************************
 Exported global variables (to be accessed by other files)
 ******************************************************************************/

/* to store the filesystem driver function pointers */
usb_media_driver_t g_ext_flash_mediadriver =
{
    &ext_flash_disk_open,
    &ext_flash_disk_close,
    &ext_flash_disk_read,
    &ext_flash_disk_write,
    &ext_flash_disk_ioctl
};

/******************************************************************************
 * Function Name: ram_disk_open
 * Description  : Create FAT File system for Internal RAM.
 * Argument     : none
 * Return value : USB_MEDIA_RET_OK
 ******************************************************************************/
static usb_media_ret_t ext_flash_disk_open (void)
{
    uint32_t adr;
		uint32_t i;
		uint32_t flash_id;
		
		printf("Init disk\n");
		//check Flash ID
		flash_id = FlashReadID();
		if(flash_id != FLASH_ID)	//0x40EF W25Q128JV
		{
			printf("Read Flash Chip ID is: %4x, Return USB_MEDIA_RET_OP_FAIL\n", flash_id);
			return  USB_MEDIA_RET_OP_FAIL;  //USB_MEDIA_RET_DEV_NO_INIT
		}

    return USB_MEDIA_RET_OK;
} /* End of function ram_disk_open */

/******************************************************************************
 * Function Name: ram_disk_close
 * Description  : RAM Disk Close dummy function.
 * Argument     : none
 * Return value : USB_MEDIA_RET_OK
 ******************************************************************************/
static usb_media_ret_t ext_flash_disk_close (void)
{
    return USB_MEDIA_RET_OK;
} /* End of function ram_disk_close */

/******************************************************************************
 * Function Name: ram_disk_read
 * Description  : RAM Disk Read process.
 * Argument     :     * read_buffer : Destination buffer for read data
 *                    sector        : The starting sector number
 *                    sector_count  : Number of sectors to be read
 *
 * Return value :     USB_MEDIA_RET_OK
 * Note:    This function does not check for destination buffer overrun.
 *          Make absolutely sure that enough memory has been allocated to accept
 *          the data that will be read. This is especially important when the
 *          sector count is greater than 1, because typically only 1 sector is
 *          read at a time.
 ******************************************************************************/
static usb_media_ret_t ext_flash_disk_read (uint8_t* p_read_buffer, uint32_t sector, uint8_t sector_count)
{
		uint32_t i, j, k;
		uint32_t page_size = STRG_FLASH_PAGESIZE; //page size =256Byte
		uint32_t page_num = STRG_FLASH_SECTOR_SIZE / page_size;
		uint8_t *ptrs = (uint8_t *)p_read_buffer;

		for(i = 0; i < sector_count; i++){
			for(j = 0; j < page_num; j++)
			{
				FlashCheckBusy();
				FlashFastRead(((sector + i) * STRG_FLASH_SECTOR_SIZE) + (j * page_size), page_size, (void *)ptrs);
				ptrs += page_size;
			}
		}
		printf("Read sector:%d, count:%d\n", sector, sector_count);
	
    return USB_MEDIA_RET_OK;
} /* End of function ram_disk_read */

/******************************************************************************
 * Function Name: ram_disk_write
 * Description  : RAM Disk Write process.
 * Argument     :   * p_write_buffer : Source for data to be written from
 *                    sector         : The starting sector number
 *                    sector_count   : Number of sectors to be written
 * Return value :     USB_MEDIA_RET_OK
 ******************************************************************************/
static usb_media_ret_t ext_flash_disk_write (uint8_t* p_write_buffer, uint32_t sector, uint8_t sector_count)
{
		uint32_t i, j, k;
		uint32_t page_size = STRG_FLASH_PAGESIZE; //page size =256Byte
		uint32_t page_num = STRG_FLASH_SECTOR_SIZE / page_size;
		uint8_t *ptrs = (uint8_t *)p_write_buffer;
	
		for(i = 0; i < sector_count; i++){
			FlashCheckBusy();
			FlashEraseSector((sector + i) * STRG_FLASH_SECTOR_SIZE);
			
			for(j = 0; j < page_num; j++)
			{
				FlashCheckBusy();
				FlashProgramPage(((sector + i) * STRG_FLASH_SECTOR_SIZE) + (j * page_size), page_size, (void *)ptrs);
				ptrs += page_size;
			}
		}
		printf("write sector:%d, count:%d\n", sector, sector_count);
		
    return USB_MEDIA_RET_OK;
} /* End of function ram_disk_write */

/******************************************************************************
 * Function Name: ram_disk_ioctl
 * Description  : RAM Disk control process.
 * Argument     : command_code : Control Command code.
                : *p_data_buffer : Pointer for Data store address.
 * Return value : USB_MEDIA_RET_OK
 ******************************************************************************/
static usb_media_ret_t ext_flash_disk_ioctl (uint8_t command_code, uint32_t* p_data_buffer)
{
    switch (command_code)
    {

        case USB_MEDIA_IOCTL_GET_NUM_BLOCKS :

            /* Gets the number of logical blocks in the RAM disk */
            *p_data_buffer = (uint32_t) STRG_TOTALSECT;

            break;

        case USB_MEDIA_IOCTL_GET_SECTOR_SIZE :
        case USB_MEDIA_IOCTL_GET_BLOCK_SIZE :

            /* Get the size of the logical block in the RAM disk */
            *p_data_buffer = (uint32_t) STRG_FLASH_SECTOR_SIZE;

            break;

        case USB_MEDIA_IOCTL_SYNC :

            /* TODO: Flush write cache if necessary */

            break;

        default :

            return USB_MEDIA_RET_PARERR;

            //break;
    }
		
//		printf("ioctl:%x\n", command_code);

    return USB_MEDIA_RET_OK;
} /* End of function ram_disk_ioctl */
/******************************************************************************
 End  Of File
 ******************************************************************************/

