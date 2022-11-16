/********************************************************
* @file       drv_inter_flash.c
* @author     szhj13
* @version    V1.0
* @date       2022-05-18
* @brief      the start address of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "drv_inter_flash.h"
/* Private typedef --------------------------------------*/
/* Private define ---------------------------------------*/
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
/* Private variables ------------------------------------*/

void Drv_Inter_Flash_Read (uint32_t adr, uint32_t sz, uint8_t *buf)
{
    uint32_t i;
    
    uint8_t *u8DataPtr = (uint8_t *)adr;

    for(i=0;i<sz;i++)
    {
        buf[i] = *u8DataPtr++;
    }
}

void Drv_Inter_Flash_Write(uint32_t adr, uint32_t sz, uint8_t *buf )
{
    uint16_t firstPageRemianByte;
    uint16_t lastPageRemainByte;
    uint16_t totalPageNum;

    firstPageRemianByte = INTER_PAGE_SIZE - adr % INTER_PAGE_SIZE;    

    if(sz <= firstPageRemianByte)
    {
        totalPageNum = 0;

        lastPageRemainByte = 0;
    }
    else
    {
        totalPageNum = (sz- firstPageRemianByte) / INTER_PAGE_SIZE;

        lastPageRemainByte = (sz- firstPageRemianByte) % INTER_PAGE_SIZE;        
    }

    if(firstPageRemianByte != 0)
    {
        Hal_Inter_Flash_Program_Page(adr, sz, buf);
    }

    adr += sz;

    for(uint16_t i=0;i<totalPageNum;i++)
    {
        Hal_Inter_Flash_Program_Page(adr, INTER_PAGE_SIZE, buf);

        adr += INTER_PAGE_SIZE;
    }

    if(lastPageRemainByte != 0)
    {
        Hal_Inter_Flash_Program_Page(adr, lastPageRemainByte, buf);
    }
    
    adr += lastPageRemainByte;
}


void Drv_Inter_Flash_Erase_Sector(uint32_t adr )
{
    Hal_Inter_Flash_Erase_Sector(adr);
}


