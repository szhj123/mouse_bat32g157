/********************************************************
* @file       drv_spi_flash.c
* @author     szhj13
* @version    V1.0
* @date       2022-05-18
* @brief      the start address of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "drv_spi_flash.h"

/* Private typedef --------------------------------------*/
/* Private define ---------------------------------------*/
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
static void Drv_Spi_Flash_Read_End_Callback(void );
static void Drv_Spi_Flash_Write_End_Callback(void );

/* Private variables ------------------------------------*/
static uint8_t spi_read_end_flag = 0;
static uint8_t spi_write_end_flag = 0;

uint8_t txBuf[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
uint8_t rxBuf[10] = {0};


void Drv_Spi_Flash_Init(void )
{
    Hal_Spi_Flash_Init();

    Drv_Spi_Read_ID();

    //Drv_Spi_Flash_Erase_64Kb(100);
    
    //Drv_Spi_Flash_Loop_Read(100, rxBuf, sizeof(rxBuf));

    //Drv_Spi_Flash_Write(100, txBuf, sizeof(txBuf));

    //Drv_Spi_Flash_DMA_Read(100, rxBuf, sizeof(rxBuf));
}

void Drv_Spi_Read_ID(void )
{
    static uint8_t buf[3] = {0};
    
    Hal_Spi_Flash_Start();
    
    Hal_Spi_Flash_Write_Single_Data(0x9f);

    Hal_Spi_Flash_Loop_Read(buf, 3);

    Hal_Spi_Flash_Stop();
}

void Drv_Spi_Flash_Erase_64Kb(uint32_t addr )
{
    Drv_Spi_Flash_Write_Enable();
    
    Hal_Spi_Flash_Start();
    
    Hal_Spi_Flash_Write_Single_Data(ERASE_BLOCK_64K);
    
    Hal_Spi_Flash_Write_Single_Data((uint8_t )(addr >> 16));
    Hal_Spi_Flash_Write_Single_Data((uint8_t )(addr >> 8));
    Hal_Spi_Flash_Write_Single_Data((uint8_t )addr);
    
    Hal_Spi_Flash_Stop();

    Drv_Spi_Flash_Wait_Idle();
}

void Drv_Spi_Flash_Write_Enable(void )
{
    uint8_t status;

    Hal_Spi_Flash_Start();
    
    Hal_Spi_Flash_Write_Single_Data(WRITE_ENABLE);

    Hal_Spi_Flash_Stop();
    
    Hal_Spi_Flash_Start();
    
    Hal_Spi_Flash_Write_Single_Data(READ_STATUS);

    do{
        Hal_Spi_Flash_Loop_Read(&status, 1);
    }while(!(status & 0x02));

    Hal_Spi_Flash_Stop();
}


void Drv_Spi_Flash_Loop_Read(uint32_t addr, uint8_t *buf, uint32_t length )
{
    Hal_Spi_Flash_Start();
    
    Hal_Spi_Flash_Write_Single_Data(READ_DATA);
    
    Hal_Spi_Flash_Write_Single_Data((uint8_t )(addr >> 16));
    Hal_Spi_Flash_Write_Single_Data((uint8_t )(addr >> 8));
    Hal_Spi_Flash_Write_Single_Data((uint8_t )addr);

    Hal_Spi_Flash_Loop_Read(buf, length);
    
    Hal_Spi_Flash_Stop();
}

void Drv_Spi_Flash_DMA_Read(uint32_t addr, uint8_t *buf, uint32_t length )
{
    Hal_Spi_Flash_Start();

    Hal_Spi_Flash_Write_Single_Data(READ_DATA);
    
    Hal_Spi_Flash_Write_Single_Data((uint8_t )(addr >> 16));
    Hal_Spi_Flash_Write_Single_Data((uint8_t )(addr >> 8));
    Hal_Spi_Flash_Write_Single_Data((uint8_t )addr);

    Hal_Spi_Flash_DMA_Read(buf, length, Drv_Spi_Flash_Read_End_Callback);

    while(!spi_read_end_flag);
    spi_read_end_flag = 0;
    
    Hal_Spi_Flash_Stop();
}

void Drv_Spi_Flash_DMA_Write(uint32_t addr, uint8_t *buf, uint32_t length )
{
    Drv_Spi_Flash_Write_Enable();

    Hal_Spi_Flash_Start();

    Hal_Spi_Flash_Write_Single_Data(PAGE_PROGRAM);

    Hal_Spi_Flash_Write_Single_Data((uint8_t )(addr >> 16));
    Hal_Spi_Flash_Write_Single_Data((uint8_t )(addr >> 8));
    Hal_Spi_Flash_Write_Single_Data((uint8_t )addr);

    Hal_Spi_Flash_DMA_Write(buf, length, Drv_Spi_Flash_Write_End_Callback);

    while(!spi_write_end_flag);

    spi_write_end_flag = 0;
    
    Hal_Spi_Flash_Stop();

    Drv_Spi_Flash_Wait_Idle();
}


void Drv_Spi_Flash_Wait_Idle(void )
{
    uint8_t status;
    
    Hal_Spi_Flash_Start();
    
    Hal_Spi_Flash_Write_Single_Data(READ_STATUS);

    do{
        Hal_Spi_Flash_Loop_Read(&status, 1);
    }while(status & 0x01);

    Hal_Spi_Flash_Stop();
}

void Drv_Spi_Flash_Read(uint32_t addr, uint8_t *buf, uint32_t length )
{
    Drv_Spi_Flash_DMA_Read(addr, buf, length );
}

void Drv_Spi_Flash_Write(uint32_t addr, uint8_t *buf, uint32_t length )
{
    uint8_t firstPageRemainByte;
    uint8_t lastPageRemainByte;
    uint32_t pageNum;
    uint32_t i;

    if((addr % 256) == 0)
    {
        firstPageRemainByte = 0;
    }
    else
    {
        firstPageRemainByte = 256- (addr % 256);
    }

    if(length > firstPageRemainByte)
    {
        pageNum = (length - firstPageRemainByte) / 256;
    }
    else
    {
        pageNum = 0;
    }

    lastPageRemainByte = (length - firstPageRemainByte) % 256;

    if(firstPageRemainByte)
    {
        if(length > firstPageRemainByte)
        {
            Drv_Spi_Flash_DMA_Write(addr, buf, firstPageRemainByte);

            buf += firstPageRemainByte;

            addr += firstPageRemainByte;
            
        }
        else
        {
            Drv_Spi_Flash_DMA_Write(addr, buf, length);

            buf += length;

            addr += length;
        }
    }

    for(i=0;i<pageNum;i++)
    {
        Drv_Spi_Flash_DMA_Write(addr, buf, PAGE_SIZE);

        buf += PAGE_SIZE;

        addr += PAGE_SIZE;
    }

    if(lastPageRemainByte)
    {
        Drv_Spi_Flash_DMA_Write(addr, buf, lastPageRemainByte);

        buf += lastPageRemainByte;

        addr += lastPageRemainByte;
    }
}

static void Drv_Spi_Flash_Read_End_Callback(void )
{
    spi_read_end_flag = 1;
}

static void Drv_Spi_Flash_Write_End_Callback(void )
{
    spi_write_end_flag = 1;
}


