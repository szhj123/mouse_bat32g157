#ifndef _HAL_SPI_FLASH_H
#define _HAL_SPI_FLASH_H

#include "hal_bat32g157.h"

void Hal_Spi_Flash_Init(void );
void Hal_Spi_Flash_Write_Single_Data(uint8_t dat );
void Hal_Spi_Flash_Loop_Read(uint8_t *buf, uint32_t length );
void Hal_Spi_Flash_DMA_Write(uint8_t *buf, uint32_t length, hal_isr_callback_t callback );
void Hal_Spi_Flash_Start(void );
void Hal_Spi_Flash_Stop(void);
void Hal_Spi_Flash_Isr_Handler(void );

#endif 

