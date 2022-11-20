#ifndef _HAL_SPI_FLASH_H
#define _HAL_SPI_FLASH_H

#include "hal_bat32g157.h"

typedef void (*spi1_tx_end_callback_t)(void );
typedef void (*spi1_rx_end_callback_t)(void );


void Hal_Spi_Init(void );
void Hal_Spi_Cs_Clr(void );
void Hal_Spi_Cs_Set(void );
void Hal_Spi_Start(void );
void Hal_Spi_Stop(void );
void Hal_Spi_Tx_Single_With_Blocking(uint8_t val );
void Hal_Spi_Tx_Multiple_With_Blocking(uint8_t *buf, uint16_t length );
void Hal_Spi_Tx_Multiple_With_Interrupt(uint8_t *buf, uint16_t length, spi1_tx_end_callback_t callback );
void Hal_Spi_Tx_Multiple_With_DMA(uint8_t *buf, uint16_t length, spi1_tx_end_callback_t callback );
void Hal_Spi_Tx_Isr_Handler(void );

void Hal_Spi_Rx_Multiple_With_Block(uint8_t *buf, uint16_t length );
void Hal_Spi_Rx_Multiple_With_DMA(uint8_t *buf, uint16_t length, spi1_rx_end_callback_t callback );
void Hal_Spi_Rx_Isr_Handler(void );

#endif 

