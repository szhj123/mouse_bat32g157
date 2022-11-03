#ifndef _HAL_INTER_FLASH_H
#define _HAL_INTER_FLASH_H

#include "hal_bat32g157.h"

int Hal_Inter_Flash_Erase_Chip(uint32_t adr );
int Hal_Inter_Flash_Erase_Sector(uint32_t adr );
int Hal_Inter_Flash_Program_Page (uint32_t adr, uint32_t sz, uint8_t *buf);

#endif 

