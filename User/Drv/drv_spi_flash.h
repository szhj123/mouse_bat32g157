#ifndef _DRV_SPI_FLASH_H
#define _DRV_SPI_FALSH_H

#include "hal_spi_flash.h"

#define PAGE_SIZE                    256

#define WRITE_ENABLE                 0x06
#define READ_STATUS                  0x05
#define READ_DATA                    0x03
#define PAGE_PROGRAM                 0x02
#define SECTOR_ERASE                 0x20
#define ERASE_BLOCK_32K              0x52
#define ERASE_BLOCK_64K              0xd8
#define ERASE_CHIP                   0x60

void Drv_Spi_Flash_Init(void );
void Drv_Spi_Read_ID(void );
void Drv_Spi_Flash_Wait_Idle(void );
void Drv_Spi_Flash_Write_Enable(void );
void Drv_Spi_Write(uint32_t addr, uint8_t *buf, uint32_t length );
void Drv_Spi_Flash_DMA_Write(uint32_t addr, uint8_t *buf, uint32_t length );
void Drv_Spi_Flash_Loop_Read(uint32_t addr, uint8_t *buf, uint32_t length );

#endif 

