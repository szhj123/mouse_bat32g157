/********************************************************
* @file       drv_spi.c
* @author     szhj13
* @version    V1.0
* @date       2021-08-12
* @brief      the entry of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "drv_spi_flash.h"

/* Private typedef --------------------------------------*/
/* Private define ---------------------------------------*/
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
void Drv_Spi_Wait_Bus_Idle(void );
static void Drv_Spi_Tx_End_Callback(void );
static void Drv_Spi_Rx_End_Callback(void ); 
/* Private variables ------------------------------------*/
static flash_id_t flash_id;
static uint8_t spi_tx_end_flag;
static uint8_t spi_rx_end_flag;


void Drv_Spi_Flash_Init(void )
{
    Hal_Spi_Init();

    Drv_Spi_Read_Jedec_Id();

    #if 0
    static uint16_t rxBuf[32] = {0};
    uint32_t addr = 0xa0000;
    uint8_t i;
    
    Drv_Spi_64K_Block_Erase(addr);
    Drv_Spi_64K_Block_Erase(addr+ERASE_64K_BLOCK_SIZE);

    do{
        for(i=0;i<32;i++)
            rxBuf[i] = 0xf800;
        Drv_Spi_Write(addr, (uint8_t *)rxBuf, sizeof(rxBuf));
        for(i=0;i<32;i++)
            rxBuf[i] = 0;
        Drv_Spi_Read(addr, (uint8_t *)rxBuf, sizeof(rxBuf));
        addr += 64;

        if(addr > 0xa0000+115000)
            addr = addr;
        
    }while(addr < (0xa0000+115200));
    #endif 
}

void Drv_Spi_Read_Jedec_Id(void )
{    
    uint8_t dummy[3] = {0x00};
    
    Hal_Spi_Start();

    Hal_Spi_Tx_Single_With_Blocking(READ_JEDEC_ID);

    Hal_Spi_Rx_Multiple_With_Block((uint8_t *)&flash_id, sizeof(flash_id_t));

    Hal_Spi_Stop();
}

void Drv_Spi_Write_Enable(void )
{
    Hal_Spi_Start();

    Hal_Spi_Tx_Single_With_Blocking(WRITE_ENABLE);

    Hal_Spi_Stop();

    Drv_Spi_Wait_Bus_Idle();
}

uint8_t Drv_Spi_Read_Status(void )
{
    uint8_t status[2] = {0};
    
    Hal_Spi_Tx_Single_With_Blocking(READ_STATUS_REGISTER);

    Hal_Spi_Rx_Multiple_With_Block((uint8_t *)status, 2);

    return status[0];
}

void Drv_Spi_Wait_Bus_Idle(void )
{
    uint8_t status;
    
    Hal_Spi_Start();

    do{
        status = Drv_Spi_Read_Status();
    }while(status & 0x01);

    Hal_Spi_Stop();
}

void Drv_Spi_Sector_Erase(uint32_t addr )
{
    Drv_Spi_Write_Enable();

    Hal_Spi_Start();
    
    Hal_Spi_Tx_Single_With_Blocking(SECTOR_ERASE);

    Hal_Spi_Tx_Single_With_Blocking((uint8_t )(addr >> 16));
    Hal_Spi_Tx_Single_With_Blocking((uint8_t )(addr >> 8));
    Hal_Spi_Tx_Single_With_Blocking((uint8_t )(addr));

    Hal_Spi_Stop();
    
    Drv_Spi_Wait_Bus_Idle();
}

void Drv_Spi_32K_Block_Erase(uint32_t addr )
{
    Drv_Spi_Write_Enable();

    Hal_Spi_Start();
    
    Hal_Spi_Tx_Single_With_Blocking(BLOCK_ERASE_32K);

    Hal_Spi_Tx_Single_With_Blocking((uint8_t )(addr >> 16));
    Hal_Spi_Tx_Single_With_Blocking((uint8_t )(addr >> 8));
    Hal_Spi_Tx_Single_With_Blocking((uint8_t )(addr));

    Hal_Spi_Stop();
    
    Drv_Spi_Wait_Bus_Idle();
}


void Drv_Spi_64K_Block_Erase(uint32_t addr )
{
    Drv_Spi_Write_Enable();

    Hal_Spi_Start();
    
    Hal_Spi_Tx_Single_With_Blocking(BLOCK_ERASE_64K);

    Hal_Spi_Tx_Single_With_Blocking((uint8_t )(addr >> 16));
    Hal_Spi_Tx_Single_With_Blocking((uint8_t )(addr >> 8));
    Hal_Spi_Tx_Single_With_Blocking((uint8_t )(addr));

    Hal_Spi_Stop();
    
    Drv_Spi_Wait_Bus_Idle();
}

void Drv_Spi_Write_Page(uint32_t addr, uint8_t *buf, uint16_t length )
{
    Drv_Spi_Write_Enable();
    
    Hal_Spi_Start();

    Hal_Spi_Tx_Single_With_Blocking(PAGE_PROGRAM);

    Hal_Spi_Tx_Single_With_Blocking((uint8_t )(addr >> 16));
    Hal_Spi_Tx_Single_With_Blocking((uint8_t )(addr >> 8));
    Hal_Spi_Tx_Single_With_Blocking((uint8_t )(addr));
    
    Hal_Spi_Tx_Multiple_With_Blocking(buf, length);
    
    Hal_Spi_Stop();
    
    Drv_Spi_Wait_Bus_Idle();
}

void Drv_Spi_Write(uint32_t addr, uint8_t *buf, uint32_t length )
{   
    uint32_t pageNum = 0;
    uint32_t lastPageRemainByte = 0;
    uint32_t firstPageRemainByte = 0;
    uint32_t i;
		
		 firstPageRemainByte = PAGE_SIZE - addr % PAGE_SIZE;
		
	   if(length < firstPageRemainByte)
		 {
			    firstPageRemainByte = length;
			    pageNum = 0;
			    lastPageRemainByte = 0;
		 }
		 else
		 {
			    pageNum = (length-firstPageRemainByte) / PAGE_SIZE;
					lastPageRemainByte =  (length-firstPageRemainByte) %PAGE_SIZE;
		 }
   
    if(firstPageRemainByte)
    {
        Drv_Spi_Write_With_DMA(addr, buf, firstPageRemainByte, Drv_Spi_Tx_End_Callback);

        addr += firstPageRemainByte;
        buf += firstPageRemainByte;
    }

    for(i=0;i<pageNum;i++)
    {
        Drv_Spi_Write_With_DMA(addr, buf, PAGE_SIZE, Drv_Spi_Tx_End_Callback);

        addr += PAGE_SIZE;
        buf += PAGE_SIZE;
    }

    if(lastPageRemainByte)
    {
        Drv_Spi_Write_With_DMA(addr, buf, lastPageRemainByte, Drv_Spi_Tx_End_Callback);
    }
}

void Drv_Spi_Read(uint32_t addr, uint8_t *buf, uint32_t length )
{
    Drv_Spi_Read_With_DMA(addr, buf, length, Drv_Spi_Rx_End_Callback);
}

void Drv_Spi_Write_With_Interrupt(uint32_t addr, uint8_t *buf, uint16_t length, spi1_tx_end_callback_t callback )
{    
    Drv_Spi_Write_Enable();
    
    Hal_Spi_Start();

    Hal_Spi_Tx_Single_With_Blocking(PAGE_PROGRAM);

    Hal_Spi_Tx_Single_With_Blocking((uint8_t )(addr >> 16));
    Hal_Spi_Tx_Single_With_Blocking((uint8_t )(addr >> 8));
    Hal_Spi_Tx_Single_With_Blocking((uint8_t )(addr));
    
    Hal_Spi_Tx_Multiple_With_Interrupt(buf, length, callback);
}


void Drv_Spi_Write_With_DMA(uint32_t addr, uint8_t *buf, uint16_t length, spi1_tx_end_callback_t callback )
{    
    Drv_Spi_Write_Enable();
    
    Hal_Spi_Start();

    Hal_Spi_Tx_Single_With_Blocking(PAGE_PROGRAM);

    Hal_Spi_Tx_Single_With_Blocking((uint8_t )(addr >> 16));
    Hal_Spi_Tx_Single_With_Blocking((uint8_t )(addr >> 8));
    Hal_Spi_Tx_Single_With_Blocking((uint8_t )(addr));
    
    Hal_Spi_Tx_Multiple_With_DMA(buf, length, callback);

    while(!spi_tx_end_flag);
    spi_tx_end_flag = 0;
}

void Drv_Spi_Read_With_Blocking(uint32_t addr, uint8_t *buf, uint16_t length )
{    
    Hal_Spi_Start();

    Hal_Spi_Tx_Single_With_Blocking(READ_DATA);

    Hal_Spi_Tx_Single_With_Blocking((uint8_t )(addr >> 16));
    Hal_Spi_Tx_Single_With_Blocking((uint8_t )(addr >> 8));
    Hal_Spi_Tx_Single_With_Blocking((uint8_t )(addr));

    Hal_Spi_Rx_Multiple_With_Block(buf, length);
    
    Hal_Spi_Stop();
}

void Drv_Spi_Read_With_DMA(uint32_t addr, uint8_t *buf, uint32_t length, spi1_rx_end_callback_t callback )
{
    Hal_Spi_Start();
    
    Hal_Spi_Tx_Single_With_Blocking(READ_DATA);

    Hal_Spi_Tx_Single_With_Blocking((uint8_t )(addr >> 16));
    Hal_Spi_Tx_Single_With_Blocking((uint8_t )(addr >> 8));
    Hal_Spi_Tx_Single_With_Blocking((uint8_t )(addr));
    
    Hal_Spi_Rx_Multiple_With_DMA(buf, length, callback);

    while(!spi_rx_end_flag);
    spi_rx_end_flag = 0;
}


static void Drv_Spi_Tx_End_Callback(void ) 
{
    spi_tx_end_flag = 1;
    
    Hal_Spi_Stop();

    Drv_Spi_Wait_Bus_Idle();
}

static void Drv_Spi_Rx_End_Callback(void ) 
{
    spi_rx_end_flag = 1;

    Hal_Spi_Stop();
}
