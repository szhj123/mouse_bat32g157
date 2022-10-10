/********************************************************
* @file       hal_spi_flash.c
* @author     szhj13
* @version    V1.0
* @date       2022-05-18
* @brief      the start address of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "hal_spi_flash.h"

/* Private typedef --------------------------------------*/
/* Private define ---------------------------------------*/
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
/* Private variables ------------------------------------*/
static uint8_t *spi1TxDataPtr = NULL;
static uint32_t spi1TxDataLength;
static uint8_t  spi1TxFlag;
static hal_isr_callback_t spi1_tx_end_callback = NULL;

void Hal_Spi_Flash_Init(void )
{
    spi_mode_t mode = SPI_MODE_0;
        
    CGC->PER1 |= 0x80;

    SPIHS1->SPIC1 = _0001_SPI_SCK_fCLK_1 | (mode & 0x03) << 3;    

    SPIHS1->SPIM1 = _0040_SPI_RECEPTION_TRANSMISSION | _0000_SPI_MSB | _0000_SPI_TRANSFER_END | _0000_SPI_LENGTH_8;

    NSS1_PORT_SETTING();
    SCK1_PORT_SETTING();
    MOSI1_PORT_SETTING();
    MISO1_PORT_SETTING();
}

void Hal_Spi_Flash_Write_Single_Data(uint8_t dat )
{
    SPIHS1->SDRO1 = dat;

    while(SPIHS1->SPIS1 & _0001_SPI_UNDER_EXECUTE) 
    {
        ;
    }
}

void Hal_Spi_Flash_Loop_Read(uint8_t *buf, uint32_t length )
{
    uint32_t i;
    uint8_t dummy = 0xff;

    for(i=0;i<length;i++)
    {
        Hal_Spi_Flash_Write_Single_Data(dummy);

        buf[i] = SPIHS1->SDRI1;
    }
}

void Hal_Spi_Flash_DMA_Write(uint8_t *buf, uint32_t length, hal_isr_callback_t callback )
{
    SPIHS1->SPIM1 |= _0040_SPI_RECEPTION_TRANSMISSION | _0000_SPI_TRANSFER_END; /* transmission mode */

    /* write transfer data with DMA */
    DMAVEC->VEC[DMA_VECTOR_SPIHS1] = CTRL_DATA_SPIHS1;
    DMAVEC->CTRL[CTRL_DATA_SPIHS1].DMACR = (0 << CTRL_DMACR_SZ_Pos) | (0 << CTRL_DMACR_CHNE_Pos) |
                                           (0 << CTRL_DMACR_DAMOD_Pos) | (1 << CTRL_DMACR_SAMOD_Pos) |
                                           (0 << CTRL_DMACR_MODE_Pos);
    DMAVEC->CTRL[CTRL_DATA_SPIHS1].DMBLS = 1;
    DMAVEC->CTRL[CTRL_DATA_SPIHS1].DMACT = length - 1;
    DMAVEC->CTRL[CTRL_DATA_SPIHS1].DMRLD = length - 1;
    DMAVEC->CTRL[CTRL_DATA_SPIHS1].DMSAR = (uint32_t)(buf + 1);
    DMAVEC->CTRL[CTRL_DATA_SPIHS1].DMDAR = (uint32_t)&SPIHS1->SDRO1;

    /* init DMA registers */
    CGC->PER1 |= CGC_PER1_DMAEN_Msk;
    DMA->DMABAR = DMAVEC_BASE;
    DMA->DMAEN2 |= (1 << DMA_VECTOR_SPIHS1 % 8);

    spi1TxDataLength = 1;        
    spi1TxDataPtr = buf; 
    spi1TxFlag = 1;

    spi1_tx_end_callback = callback;

    Hal_Spi_Flash_Start();
    
    SPIHS1->SDRO1 = *spi1TxDataPtr;
    
    spi1TxDataPtr++;
    spi1TxDataLength--;
}

void Hal_Spi_Flash_Start(void )
{
    /* clear INTSPI interrupt flag */
    INTC_ClearPendingIRQ(SPI1_IRQn);
    NVIC_ClearPendingIRQ(SPI1_IRQn);
    /* enable INTSPI interrupt */
    INTC_EnableIRQ(SPI1_IRQn);
    NVIC_EnableIRQ(SPI1_IRQn);
    SPIHS1->SPIM1 |= _0080_SPI_START_TRG_ON; 
    /* SSn Active */
    NSS1_PORT_CLR();
}

void Hal_Spi_Flash_Stop(void)
{
    /* SSn Inactive */
    NSS1_PORT_SET();
    SPIHS1->SPIM1 &= ~_0080_SPI_START_TRG_ON; 
    /* disable INTSPI interrupt */
    INTC_DisableIRQ(SPI1_IRQn);
    NVIC_DisableIRQ(SPI1_IRQn);
    /* clear INTSPI interrupt flag */
    INTC_ClearPendingIRQ(SPI1_IRQn);
    NVIC_ClearPendingIRQ(SPI1_IRQn);
}

void Hal_Spi_Flash_Isr_Handler(void )
{
    if(spi1TxFlag)
    {
        if (0U != spi1TxDataPtr)
        {
            while(SPIHS1->SPIS1 & _0001_SPI_UNDER_EXECUTE) 
            {
                ;
            }
            
            if(spi1_tx_end_callback != NULL)
            {
                spi1TxFlag = 0;
                
                spi1_tx_end_callback();
                
                spi1_tx_end_callback = NULL;
            }
        }
    }
}



