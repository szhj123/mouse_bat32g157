/********************************************************
* @file       hal_inter_flash.c
* @author     szhj13
* @version    V1.0
* @date       2022-05-18
* @brief      the start address of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "hal_inter_flash.h"
/* Private typedef --------------------------------------*/
/* Private define ---------------------------------------*/
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
/* Private variables ------------------------------------*/

int Hal_Inter_Flash_Erase_Chip(uint32_t adr )
{
    FMC->FLERMD = 0x08;
    FMC->FLPROT = 0xF1;
    FMC->FLOPMD1 = 0x55;
    FMC->FLOPMD2 = 0xAA;  
    // Write data to start address of sector to trigger Erase Operation
    *(uint32_t *) adr = 0xFFFFFFFF;
    
    // polling OVER Flag
    while((FMC->FLSTS & FMC_FLSTS_OVF_Msk) == 0);
    FMC->FLSTS |= FMC_FLSTS_OVF_Msk;
    FMC->FLERMD = 0x00;
    
    return(0);
}

int Hal_Inter_Flash_Erase_Sector(uint32_t adr )
{
    FMC->FLERMD = 0x10;
    FMC->FLPROT = 0xF1;
    FMC->FLOPMD1 = 0x55;
    FMC->FLOPMD2 = 0xAA;  
    // Write data to start address of sector to trigger Erase Operation
    *(uint32_t *) adr = 0xFFFFFFFF;
    
    // polling Erase Over Flag
    while((FMC->FLSTS & FMC_FLSTS_OVF_Msk) == 0);
    FMC->FLSTS |= FMC_FLSTS_OVF_Msk;
    FMC->FLERMD = 0x00;
    FMC->FLPROT = 0x00;

    if(FMC->FLSTS & FMC_FLSTS_EVF_Msk)
    {
        return(1);  /* verify ng */
    }
    else
    {
        return(0);  /* verify ok */
    }
}

int Hal_Inter_Flash_Program_Page (uint32_t adr, uint32_t sz, uint8_t *buf)
{
    uint32_t i;
    uint8_t *ptr;
    
    ptr = (uint8_t *) adr;
    
    FMC->FLPROT = 0xF1;
    
    for(i=0; i<sz; i++) 
    {
        FMC->FLOPMD1 = 0xAA;
        FMC->FLOPMD2 = 0x55;  
        *ptr++ = *buf++;    
        // polling OVER Flag
        while((FMC->FLSTS & FMC_FLSTS_OVF_Msk) == 0);
        FMC->FLSTS |= FMC_FLSTS_OVF_Msk;
    }

    FMC->FLPROT = 0x00;
    
    return (0);
}


