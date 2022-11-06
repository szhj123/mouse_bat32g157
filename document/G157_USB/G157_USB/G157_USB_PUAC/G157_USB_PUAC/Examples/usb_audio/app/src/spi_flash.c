/***********************************************************************************************************************
* Copyright (C) . All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : spi_flash.c
* Version      :  
* Device(s)    : BAT32G137
* Tool-Chain   : MDK(armcc)
* Description  : lcd driver function.
* Creation Date: 2019/12/01
***********************************************************************************************************************/

/***********************************************************************************************************************
Macro Definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/

#include <stdio.h>
#include "BAT32G157.h"
#include "userdefine.h"
#include "dma.h"
#include "spi.h"

#include "spi_flash.h"

/***********************************************************************************************************************
* Function Name: SPIHS1_Send
* Description  : This function sends SPIHS1 data.
* Arguments    : ch -
*                    transfer char
* Return Value : receive data
***********************************************************************************************************************/
uint8_t SPIHS1_Send(uint8_t ch)
{
    SPIHS1->SDRO1 = ch;
	while(!INTC_GetPendingIRQ(SPI1_IRQn));
	INTC_ClearPendingIRQ(SPI1_IRQn);
    return SPIHS1->SDRI1;
}

/***********************************************************************************************************************
* Function Name: SPIHS1_SendWord
* Description  : This function sends SPIHS1 data.
* Arguments    : ch -
*                    transfer unsigned int
* Return Value : receive data
***********************************************************************************************************************/
uint16_t SPIHS1_SendWord(uint16_t ch)
{
    SPIHS1->SDRO1 = ch;
	while(!INTC_GetPendingIRQ(SPI1_IRQn));
	INTC_ClearPendingIRQ(SPI1_IRQn);
    return SPIHS1->SDRI1;
}

/**
  * @brief  Read SPI flash manufacturer ID and device ID.
  * @param  spi is the base address of SPI module.
  * @return High byte is manufacturer ID; low byte is device ID.
  * @note   Before calling this function, the transaction length (data width) must be configured as 8 bits.
  */
uint32_t SpiFlash_ReadMidDid(void)
{
    uint32_t u32MID_DID;

    /* /CS: active */
    SPI_CS_LOW();

    /* Send command 0x90: Read Manufacturer/Device ID */
    SPIHS1_Send(0x90);
    /* Send 24 '0' dummy bits */
    SPIHS1_Send(0x00);
    SPIHS1_Send(0x00);
    SPIHS1_Send(0x00);
    
    /* Get the MID & DID */
    
    u32MID_DID = SPIHS1_Send(0x00)<<8;
    u32MID_DID |= SPIHS1_Send(0x00);

    /* /CS: inactive */
    SPI_CS_HIGH();

    return u32MID_DID;
}


/**
  * @brief  Erase whole SPI flash memory.
  * @param  spi is the base address of SPI module.
  * @return None.
  * @note   Before calling this function, the transaction length (data width) must be configured as 8 bits.
  */
void SpiFlash_ChipErase(void)
{

    /* /CS: active */
    SPI_CS_LOW();

    /* Send command 0x06: Write enable */
    SPIHS1_Send(0x06);
    
    /* /CS: inactive */
    SPI_CS_HIGH();

    __NOP();

    /* /CS: active */
    SPI_CS_LOW();

    /* Send command 0xC7: Chip erase */
    SPIHS1_Send(0xc7);
    
    /* /CS: inactive */
    SPI_CS_HIGH();

    /* Clear RX FIFO */
    
}

/**
  * @brief  Read SPI flash status register.
  * @param  spi is the base address of SPI module.
  * @return Status register value.
  * @note   Before calling this function, the transaction length (data width) must be configured as 8 bits.
  */
uint8_t SpiFlash_ReadStatusReg(void)
{
    uint8_t sta;
    /* /CS: active */
    SPI_CS_LOW();

    /* Send command 0x05: Read status register */
    SPIHS1_Send(0x05);
    sta = SPIHS1_Send(0x00);
    
    /* /CS: inactive */
    SPI_CS_HIGH();

    /* Return the status register value */
    return sta;
}

/**
  * @brief  Write SPI flash status register.
  * @param  spi is the base address of SPI module.
  * @param  u32Value is the value attempt to write to status register.
  * @return None.
  * @note   Before calling this function, the transaction length (data width) must be configured as 8 bits.
  */
void SpiFlash_WriteStatusReg(uint32_t u32Value)
{
    /* /CS: active */
    SPI_CS_LOW();
    /* Send command 0x06: Write enable */
    SPIHS1_Send(0x06);
   
    /* /CS: inactive */
    SPI_CS_HIGH();

    __NOP();

    /* /CS: active */
    SPI_CS_LOW();
    /* Send command 0x01: Write status register */
    SPIHS1_Send(0x01);
    /* write to status register 1 */
    SPIHS1_Send(u32Value & 0xFF);
    /* write to status register 2 */
    SPIHS1_Send( (u32Value >> 8) & 0xFF);

    /* /CS: inactive */
    SPI_CS_HIGH();
}

/**
  * @brief  Perform SPI flash page program.
  * @param  spi is the base address of SPI module.
  * @param  u32StartAddress is the start address.
  * @param  au8DataBuffer is the pointer of source data.
  * @param  u32ByteCount is the total data count. The maximum number is 256.
  * @return None.
  * @note   Before calling this function, the transaction length (data width) must be configured as 8 bits.
  */
void SpiFlash_PageProgram(uint32_t u32StartAddress, uint8_t *au8DataBuffer, uint32_t u32ByteCount)
{
    uint32_t u32Counter;

    /* /CS: active */
    SPI_CS_LOW();

    /* Send command 0x06: Write enable */
    SPIHS1_Send(0x06);
    
    /* /CS: inactive */
    SPI_CS_HIGH();

    __NOP();

    /* /CS: active */
    SPI_CS_LOW();

    /* Send command 0x02: Page program */
    SPIHS1_Send(0x02);
    /* Send 24-bit start address */
    SPIHS1_Send( (u32StartAddress >> 16) & 0xFF);
    SPIHS1_Send( (u32StartAddress >> 8) & 0xFF);
    SPIHS1_Send(u32StartAddress & 0xFF);

    u32Counter = 0;
    while(u32Counter < u32ByteCount)
    {
        
        SPIHS1_Send(au8DataBuffer[u32Counter++]);
    }
    
    /* /CS: inactive */
    SPI_CS_HIGH();
}

/**
  * @brief  Read SPI flash memory.
  * @param  spi is the base address of SPI module.
  * @param  u32StartAddress is the start address.
  * @param  au8DataBuffer is the pointer of destination buffer.
  * @param  u32ByteCount is the total data count.
  * @return None.
  * @note   Before calling this function, the transaction length (data width) must be configured as 8 bits.
  */
void SpiFlash_ReadData(uint32_t u32StartAddress, uint8_t *au8DataBuffer, uint32_t u32ByteCount)
{
    uint32_t u32RxCounter, u32TxCounter;

    /* /CS: active */
    SPI_CS_LOW();

    /* Send command 0x03: Read data */
    SPIHS1_Send(0x03);
    /* Send 24-bit start address */
    SPIHS1_Send( (u32StartAddress >> 16) & 0xFF);
    SPIHS1_Send( (u32StartAddress >> 8) & 0xFF);
    SPIHS1_Send(u32StartAddress & 0xFF);
    
		for(u32RxCounter=0;u32RxCounter<u32ByteCount;u32RxCounter++)
		{
			
			au8DataBuffer[u32RxCounter] = SPIHS1_Send(0x00);
		}
    /* /CS: inactive */
    SPI_CS_HIGH();
}

/**
  * @brief  Fast Read SPI flash memory.
  * @param  spi is the base address of SPI module.
  * @param  u32StartAddress is the start address.
  * @param  au8DataBuffer is the pointer of destination buffer.
  * @param  u32ByteCount is the total data count.
  * @return None.
  * @note   Before calling this function, the transaction length (data width) must be configured as 8 bits.
  */
void SpiFlash_FastReadData(uint32_t u32StartAddress, uint8_t *au8DataBuffer, uint32_t u32ByteCount)
{
    uint32_t u32RxCounter, u32TxCounter;

    /* /CS: active */
    SPI_CS_LOW();

    /* Send command 0x0B: Read data */
    SPIHS1_Send(0x0B);
    /* Send 24-bit start address */
    SPIHS1_Send( (u32StartAddress >> 16) & 0xFF);
    SPIHS1_Send( (u32StartAddress >> 8) & 0xFF);
    SPIHS1_Send(u32StartAddress & 0xFF);
    SPIHS1_Send(0x00);//dummy
		for(u32RxCounter=0;u32RxCounter<u32ByteCount;u32RxCounter++)
		{
			
			au8DataBuffer[u32RxCounter] = SPIHS1_Send(0x00);
		}
    /* /CS: inactive */
    SPI_CS_HIGH();
}

