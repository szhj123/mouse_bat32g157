/********************************************************
* @file       hal_spi_flash.c
* @author     szhj13
* @version    V1.0
* @date       2021-08-12
* @brief      the entry of program
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
static uint8_t spiTxReqFlag;
static uint8_t *spiTxPtr = NULL;
static uint16_t spiTxLength;

static uint8_t spiRxReqFlag;
static uint8_t *spiRxPtr = NULL;
static uint16_t spiRxLength;

spi1_tx_end_callback_t spi1_tx_end_callback = NULL;
spi1_rx_end_callback_t spi1_rx_end_callback = NULL;

void Hal_Spi_Init(void )
{
    SPI1_MasterInit(SPI_MODE_0);
}

void Hal_Spi_Cs_Clr(void )
{
    NSS1_PORT_CLR();
}

void Hal_Spi_Cs_Set(void )
{
    NSS1_PORT_SET();
}

void Hal_Spi_Start(void )
{
    SPIHS1->SPIM1 |= _0040_SPI_RECEPTION_TRANSMISSION;
    SPI1_Start();
}

void Hal_Spi_Stop(void )
{
    SPI1_Stop();

    SPIHS1->SPIM1 |= _0040_SPI_RECEPTION_TRANSMISSION; //将状态从接收，改成发送，因为下一次接收之前，需要传输命令和地址；
}

void Hal_Spi_Tx_Single_With_Blocking(uint8_t val )
{
    SPIHS1->SDRO1 = val; 

    while(SPIHS1->SPIS1 & _0001_SPI_UNDER_EXECUTE) 
    {
        ;
    }
}

void Hal_Spi_Tx_Multiple_With_Blocking(uint8_t *buf, uint16_t length )
{    
    uint16_t i;

    for(i=0;i<length;i++)
    {
        SPIHS1->SDRO1 = buf[i]; 

        while(SPIHS1->SPIS1 & _0001_SPI_UNDER_EXECUTE) 
        {
            ;
        }
    }
}

void Hal_Spi_Tx_Multiple_With_Interrupt(uint8_t *buf, uint16_t length, spi1_tx_end_callback_t callback )
{
    SPI1_Start();

    spiTxPtr = buf;

    spiTxLength = length;

    spi1_tx_end_callback = callback;

    SPIHS1->SDRO1 = buf[0]; 

    spiTxPtr++;

    spiTxLength--;
}

void Hal_Spi_Tx_Multiple_With_DMA(uint8_t *buf, uint16_t length, spi1_tx_end_callback_t callback )
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

    spi1_tx_end_callback = callback;

    spiTxPtr = buf;

    spiTxReqFlag = 1;
    spiTxLength = 1;

    SPI1_Start();

    SPIHS1->SDRO1 = buf[0]; 

    spiTxPtr++;

    spiTxLength--;
}


void Hal_Spi_Rx_Multiple_With_Block(uint8_t *buf, uint16_t length )
{
    uint16_t i;
    uint8_t dummy = 0xff;

    for(i=0;i<length;i++)
    {
        SPIHS1->SDRO1 = dummy; 
        while(SPIHS1->SPIS1 & _0001_SPI_UNDER_EXECUTE) 
        {
            ;
        }

        buf[i] = SPIHS1->SDRI1;
    }
}

void Hal_Spi_Rx_Multiple_With_DMA(uint8_t *buf, uint16_t length, spi1_rx_end_callback_t callback )
{
    uint32_t dummy_sdr;

    INTC_DisableIRQ(SPI1_IRQn);
    NVIC_DisableIRQ(SPI1_IRQn);
    
    SPIHS1->SPIM1 &= ~(_0040_SPI_RECEPTION_TRANSMISSION | _0008_SPI_BUFFER_EMPTY); /* reception mode */
    /* read receive data with DMA */
    DMAVEC->VEC[DMA_VECTOR_SPIHS1] = CTRL_DATA_SPIHS1;
    DMAVEC->CTRL[CTRL_DATA_SPIHS1].DMACR = (0 << CTRL_DMACR_SZ_Pos) | (0 << CTRL_DMACR_CHNE_Pos) |
                                           (1 << CTRL_DMACR_DAMOD_Pos) | (0 << CTRL_DMACR_SAMOD_Pos) |
                                           (0 << CTRL_DMACR_MODE_Pos);
    DMAVEC->CTRL[CTRL_DATA_SPIHS1].DMBLS = 1;
    DMAVEC->CTRL[CTRL_DATA_SPIHS1].DMACT = length;
    DMAVEC->CTRL[CTRL_DATA_SPIHS1].DMRLD = length;
    DMAVEC->CTRL[CTRL_DATA_SPIHS1].DMSAR = (uint32_t)&SPIHS1->SDRI1;
    DMAVEC->CTRL[CTRL_DATA_SPIHS1].DMDAR = (uint32_t)buf;

    /* init DMA registers */
    CGC->PER1 |= CGC_PER1_DMAEN_Msk;
    DMA->DMABAR = DMAVEC_BASE;
    DMA->DMAEN2 |= (1 << DMA_VECTOR_SPIHS1 % 8);
        
    spi1_rx_end_callback = callback;

    spiRxPtr = buf + length;

    spiRxLength = 0;

    spiRxReqFlag = 1;

    SPI1_Start();

    dummy_sdr = SPIHS1->SDRI1;
}

void Hal_Spi_Tx_Isr_Handler(void )
{
    if(spiTxReqFlag)
    {
        if(spiTxLength)
        {
            SPIHS1->SDRO1 = *spiTxPtr++; 

            spiTxLength--;
        }
        else
        {    
            spiTxLength = 0;
            
            if(spi1_tx_end_callback != NULL)
            {
                while(SPIHS1->SPIS1 & _0001_SPI_UNDER_EXECUTE) 
                {
                    ;
                }
                
                spi1_tx_end_callback();

                spi1_tx_end_callback = NULL;
            }
        }
    }
}


void Hal_Spi_Rx_Isr_Handler(void )
{
    if(spiRxReqFlag)
    {
        spiRxReqFlag = 0;
        
        if(spi1_rx_end_callback != NULL)
        {
            spi1_rx_end_callback();

            spi1_rx_end_callback = NULL;
        }
    }
    
}


