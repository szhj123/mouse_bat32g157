#ifndef FMC_USER_H
#define FMC_USER_H

#include "BAT32G157.h"

#define FMC_APROM_BASE          0x8006000					/*!< APROM  Base Address         */
#define FMC_FLASH_PAGE_SIZE     0x200           /*!< Flash Page Size (512 Bytes) */
//#define FMC_CONFIG_BASE         0x00500000UL    /*!< CONFIG Base Address         */
#define FMC_DATAFLASH_BASE      0x0500200				/*!< DATAFLASH  Base Address         */

#define APROM_SIZE          (0x40000 - (FMC_APROM_BASE & 0x7FFFFFF)) //256K
#define DATAFLASH_SIZE      (2048+512)//1.5K


/*---------------------------------------------------------------------------------------------------------*/
/*  FMC Macro Definitions                                                                                  */
/*---------------------------------------------------------------------------------------------------------*/

void EraseAP(unsigned int addr_start, unsigned int addr_end);
void ReadData(unsigned int addr_start, unsigned int addr_end, unsigned int* data);
void WriteData(unsigned int addr_start, unsigned int addr_end, unsigned int *data);
void GetDataFlashInfo(uint32_t *addr, uint32_t *size);
int FMC_Write_User(unsigned int u32Addr, unsigned int u32Data);
int FMC_Read_User(unsigned int u32Addr, unsigned int * data);
int FMC_Erase_User(unsigned int u32Addr);

#endif

