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
        buf[i] = *u8DataPtr++
    }
}

void Drv_Inter_Flash_Write(uint32_t adr, uint32_t sz, uint8_t *buf )
{
    Hal_Inter_Flash_Program_Page(adr, sz, buf);
}


void Drv_Inter_Flash_Erase_Sector(uint32_t adr )
{
    Hal_Inter_Flash_Erase_Sector(adr);
}


