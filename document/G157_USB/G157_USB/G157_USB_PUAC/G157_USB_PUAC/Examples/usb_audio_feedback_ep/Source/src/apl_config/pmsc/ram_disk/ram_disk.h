/******************************************************************************
 * File Name    : ram_disk.h
 * Description  : Header file for RAM-disk media driver.
 ******************************************************************************/

/******************************************************************************
 Includes   <System Includes> , "Project Includes"
 ******************************************************************************/

/* Fixed width integers. */
#include <stdint.h>

/* RAM disk configuration */
#include "usb_basic_mini_config.h"
#include "usb_media_driver_mini_if.h"

#ifndef RAM_DISK_H
#define RAM_DISK_H

/******************************************************************************
 Macro definitions
 ******************************************************************************/

#define USB_MEDIA_ADDRESS               (0x20003000ul)              /* Media Head Address */
#define STRG_MEDIASIZE                  (32ul * 1024ul)             /* Media size */
#define STRG_TOTALSECT                  (STRG_MEDIASIZE / STRG_SECTSIZE)

/* #define RAMDISK_MEDIATYPE              (0xF8u)    Fixed media
 * #define RAMDISK_MEDIATYPE              (0xF0u)    Removable media */
#define RAMDISK_MEDIATYPE               (0xF8u)

#define RAMDISK_SIGNATURE               (0xAA55u)

#define RAMDISK_CLSTSIZE                (0x01u)
#define RAMDISK_FATNUM                  (0x02u)

/*
 If the number of data areas of clusters is smaller
 than that of value 4085(4096-11), it is FAT12.
 If the number of data areas of clusters is smaller
 than that of value 65525(65536-11), it is FAT16.
 Otherwise it is FAT32.
 */

#if STRG_TOTALSECT < 4096
    #define RAMDISK_FATLENGTH           (0x155ul)     /* FAT12 */
#else   /* STRG_TOTALSECT < 4096 */
    #if STRG_TOTALSECT < 65536
        #define RAMDISK_FATLENGTH       (0x100ul)     /* FAT16 */
    #else   /* STRG_TOTALSECT < 65536 */
        #define RAMDISK_FATLENGTH       (0x80ul)     /* FAT32 */
    #endif  /* STRG_TOTALSECT < 65536 */
#endif  /* STRG_TOTALSECT < 4096 */

#define RAMDISK_FATSIZE   (((STRG_TOTALSECT - 8) / RAMDISK_FATLENGTH) + 1)


/******************************************************************************
 Typedef definitions
 ******************************************************************************/

/*******************************************************************************
 Exported global variables
 ******************************************************************************/

extern usb_media_driver_t g_ram_mediadriver;
extern const uint8_t g_ram_disk_boot_sector[];
extern const uint8_t g_usb_pmsc_table1[];
extern const uint8_t g_usb_pmsc_tablefat1[];
extern const uint8_t g_usb_pmsc_tablefat2[];
extern const uint8_t g_usb_pmsc_rootdir[];

/*******************************************************************************
 Exported global functions (to be accessed by other files)
 ******************************************************************************/

#endif /* RAM_DISK_H */
/******************************************************************************
 End  Of File
 ******************************************************************************/

