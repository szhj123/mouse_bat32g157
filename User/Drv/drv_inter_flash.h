#ifndef _DRV_INTER_FLASH_H
#define _DRV_INTER_FLASH_H

#include "hal_inter_flash.h"

#define INTER_PAGE_SIZE                       0x200
#define FLASH_MOUSE_START_ADDR                0x08500200
#define FLASH_MACRO1_START_ADDR               (FLASH_MOUSE_START_ADDR + INTER_PAGE_SIZE)
#define FLASH_MACRO2_START_ADDR               (FLASH_MACRO1_START_ADDR + INTER_PAGE_SIZE)
#define FLASH_MACRO3_START_ADDR               (FLASH_MACRO2_START_ADDR + INTER_PAGE_SIZE)
#define FLASH_MACRO4_START_ADDR               (FLASH_MACRO3_START_ADDR + INTER_PAGE_SIZE)


void Drv_Inter_Flash_Read (uint32_t adr, uint32_t sz, uint8_t *buf);
void Drv_Inter_Flash_Write(uint32_t adr, uint32_t sz, uint8_t *buf );
void Drv_Inter_Flash_Erase_Sector(uint32_t adr );



#endif 

