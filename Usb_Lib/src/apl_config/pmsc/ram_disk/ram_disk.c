/******************************************************************************
 * File Name     : ram_disk.c
 * Description   : Implements top level of API compliant block media driver for 'RAM-disk'.
 ******************************************************************************/

/******************************************************************************
 Includes   <System Includes> , "Project Includes"
 ******************************************************************************/

#include <string.h>
#include "ram_disk.h"

/*******************************************************************************
 Macro definitions
 ******************************************************************************/

/*******************************************************************************
 Typedef definitions
 ******************************************************************************/

/*******************************************************************************
 Private global variables and functions
 ******************************************************************************/

static usb_media_ret_t ram_disk_open (void);
static usb_media_ret_t ram_disk_close (void);
static usb_media_ret_t ram_disk_read (uint8_t* read_buffer, uint32_t sector, uint8_t sector_count);
static usb_media_ret_t ram_disk_write (uint8_t* write_buffer, uint32_t sector, uint8_t sector_count);
static usb_media_ret_t ram_disk_ioctl (uint8_t command_code, uint32_t* data_buffer);

/*******************************************************************************
 Exported global variables (to be accessed by other files)
 ******************************************************************************/

/* to store the filesystem driver function pointers */
usb_media_driver_t g_ram_mediadriver =
{
    &ram_disk_open,
    &ram_disk_close,
    &ram_disk_read,
    &ram_disk_write,
    &ram_disk_ioctl
};


/******************************************************************************
 * Function Name: ram_disk_open
 * Description  : Create FAT File system for Internal RAM.
 * Argument     : none
 * Return value : USB_MEDIA_RET_OK
 ******************************************************************************/
static usb_media_ret_t ram_disk_open (void)
{
    uint32_t adr;

    adr = USB_MEDIA_ADDRESS;
    /* Set Master boot record */
    memcpy((void *)adr, (void *)&g_ram_disk_boot_sector, STRG_SECTSIZE);

    adr += (STRG_SECTSIZE);
    /* Set reserved area */
    memcpy((void *)adr, (void *)&g_usb_pmsc_table1, STRG_SECTSIZE);

    adr += (STRG_SECTSIZE);
    /* Set FAT1 */
    memcpy((void *)adr, (void *)&g_usb_pmsc_tablefat1, (STRG_SECTSIZE * RAMDISK_FATSIZE));

    adr += (STRG_SECTSIZE * RAMDISK_FATSIZE);
    /* Set FAT2 */
    memcpy((void *)adr, (void *)&g_usb_pmsc_tablefat2, (STRG_SECTSIZE * RAMDISK_FATSIZE));

    adr += (STRG_SECTSIZE * RAMDISK_FATSIZE);
    /* Set directory entry */
    memcpy((void *)adr, (void *)&g_usb_pmsc_rootdir, (STRG_SECTSIZE * 16ul));

    return USB_MEDIA_RET_OK;
} /* End of function ram_disk_open */

/******************************************************************************
 * Function Name: ram_disk_close
 * Description  : RAM Disk Close dummy function.
 * Argument     : none
 * Return value : USB_MEDIA_RET_OK
 ******************************************************************************/
static usb_media_ret_t ram_disk_close (void)
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
static usb_media_ret_t ram_disk_read (uint8_t* p_read_buffer, uint32_t sector, uint8_t sector_count)
{
    /* Copy 1 block from specified ram disk block address to p_read_buffer. */
    memcpy (p_read_buffer, (void *)(USB_MEDIA_ADDRESS + (sector * STRG_SECTSIZE)), (STRG_SECTSIZE * sector_count));

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
static usb_media_ret_t ram_disk_write (uint8_t* p_write_buffer, uint32_t sector, uint8_t sector_count)
{
    /* Copy 1 block from write_buffer to appropriate block address in ram disk. */
    memcpy((void *)(USB_MEDIA_ADDRESS + (sector * STRG_SECTSIZE)), p_write_buffer, (STRG_SECTSIZE * sector_count));

    return USB_MEDIA_RET_OK;
} /* End of function ram_disk_write */

/******************************************************************************
 * Function Name: ram_disk_ioctl
 * Description  : RAM Disk control process.
 * Argument     : command_code : Control Command code.
                : *p_data_buffer : Pointer for Data store address.
 * Return value : USB_MEDIA_RET_OK
 ******************************************************************************/
static usb_media_ret_t ram_disk_ioctl (uint8_t command_code, uint32_t* p_data_buffer)
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
            *p_data_buffer = (uint32_t) STRG_SECTSIZE;

            break;

        case USB_MEDIA_IOCTL_SYNC :

            /* TODO: Flush write cache if necessary */

            break;

        default :

            return USB_MEDIA_RET_PARERR;

            //break;
    }

    return USB_MEDIA_RET_OK;
} /* End of function ram_disk_ioctl */
/******************************************************************************
 End  Of File
 ******************************************************************************/

