/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    spi.c
* @brief   This file implements device driver for SPI module.
* @version 1.0.0
* @date    2020/10/24
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "BAT32G157.h"
#include "userdefine.h"
#include "spi.h"
#include "dma.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
volatile uint8_t *gp_spi0_rx_address;       /* spi receive buffer address */
volatile uint16_t g_spi0_rx_length;         /* spi receive data length */
volatile uint16_t g_spi0_rx_count;          /* spi receive data count */
volatile uint8_t *gp_spi0_tx_address;       /* spi send buffer address */
volatile uint16_t g_spi0_tx_length;         /* spi send data length */
volatile uint16_t g_spi0_tx_count;          /* spi send data count */
volatile uint8_t *gp_spi1_rx_address;       /* spi receive buffer address */
volatile uint16_t g_spi1_rx_length;         /* spi receive data length */
volatile uint16_t g_spi1_rx_count;          /* spi receive data count */
volatile uint8_t *gp_spi1_tx_address;       /* spi send buffer address */
volatile uint16_t g_spi1_tx_length;         /* spi send data length */
volatile uint16_t g_spi1_tx_count;          /* spi send data count */

/***********************************************************************************************************************
* Function Name: SPI0_MasterInit
* @brief  This function restarts the SPI0 module.
* @param  mode
*             - SPI_MODE_0: CPOL = 0, CPHA = 0; i.e. CKP = 1, DAP = 1
*             - SPI_MODE_1: CPOL = 0, CPHA = 1; i.e. CKP = 1, DAP = 0
*             - SPI_MODE_2: CPOL = 1, CPHA = 0; i.e. CKP = 0, DAP = 1
*             - SPI_MODE_3: CPOL = 1, CPHA = 1; i.e. CKP = 0, DAP = 0
* @return None
***********************************************************************************************************************/
void SPI0_MasterInit(spi_mode_t mode)
{
    CGC->PER1 |= 0x40;
#ifdef SPIHS0_WITH_DMA
    SPIHS0->SPIC0 = _0001_SPI_SCK_fCLK_1 | (mode & 0x03) << 3;    
#else
    SPIHS0->SPIC0 = _0006_SPI_SCK_fCLK_6 | (mode & 0x03) << 3;    
#endif
    SPIHS0->SPIM0 = _0040_SPI_RECEPTION_TRANSMISSION | _0000_SPI_MSB | _0000_SPI_TRANSFER_END | _0000_SPI_LENGTH_8;
    NSS0_PORT_SETTING();
    SCK0_PORT_SETTING();
    MOSI0_PORT_SETTING();
    MISO0_PORT_SETTING();
}

/***********************************************************************************************************************
* Function Name: SPI0_Start
* @brief  This function starts the SPI0 module operation.
* @param  None
* @return None
***********************************************************************************************************************/
void SPI0_Start(void)
{
    /* clear INTSPI interrupt flag */
    INTC_ClearPendingIRQ(SPI0_IRQn);
    NVIC_ClearPendingIRQ(SPI0_IRQn);
    /* enable INTSPI interrupt */
    INTC_EnableIRQ(SPI0_IRQn);
    NVIC_EnableIRQ(SPI0_IRQn);
    SPIHS0->SPIM0 |= _0080_SPI_START_TRG_ON; 
    /* SSn Active */
    NSS0_PORT_CLR();
}
/***********************************************************************************************************************
* Function Name: SPI0_Stop
* @brief  This function stops the SPI0 module operation.
* @param  None
* @return None
***********************************************************************************************************************/
void SPI0_Stop(void)
{
    /* SSn Inactive */
    NSS0_PORT_SET();
    SPIHS0->SPIM0 &= ~_0080_SPI_START_TRG_ON; 
    /* disable INTSPI interrupt */
    INTC_DisableIRQ(SPI0_IRQn);
    NVIC_DisableIRQ(SPI0_IRQn);
    /* clear INTSPI interrupt flag */
    INTC_ClearPendingIRQ(SPI0_IRQn);
    NVIC_ClearPendingIRQ(SPI0_IRQn);
}
/***********************************************************************************************************************
* Function Name: SPI0_MasterSend
* @brief  This function sends SPI data.
* @param  tx_buf - transfer buffer pointer
* @param  tx_num - buffer size
* @return status - MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS SPI0_MasterSend(uint8_t *const tx_buf, uint16_t tx_num)
{
    MD_STATUS status = MD_OK;

    if (tx_num < 1U)
    {
        status = MD_ERROR;
    }
    else
    {
        SPIHS0->SPIM0 |= _0040_SPI_RECEPTION_TRANSMISSION | _0008_SPI_BUFFER_EMPTY; /* transmission mode */
#ifdef SPIHS0_WITH_DMA
        /* write transfer data with DMA */
        DMAVEC->VEC[DMA_VECTOR_SPIHS0] = CTRL_DATA_SPIHS0;
        DMAVEC->CTRL[CTRL_DATA_SPIHS0].DMACR = (0 << CTRL_DMACR_SZ_Pos) | (0 << CTRL_DMACR_CHNE_Pos) |
                                               (0 << CTRL_DMACR_DAMOD_Pos) | (1 << CTRL_DMACR_SAMOD_Pos) |
                                               (0 << CTRL_DMACR_MODE_Pos);
        DMAVEC->CTRL[CTRL_DATA_SPIHS0].DMBLS = 1;
        DMAVEC->CTRL[CTRL_DATA_SPIHS0].DMACT = tx_num - 1;
        DMAVEC->CTRL[CTRL_DATA_SPIHS0].DMRLD = tx_num - 1;
        DMAVEC->CTRL[CTRL_DATA_SPIHS0].DMSAR = (uint32_t)(tx_buf + 1);
        DMAVEC->CTRL[CTRL_DATA_SPIHS0].DMDAR = (uint32_t)&SPIHS0->SDRO0;

        /* init DMA registers */
        CGC->PER1 |= CGC_PER1_DMAEN_Msk;
        DMA->DMABAR = DMAVEC_BASE;
        DMA->DMAEN2 |= (1 << DMA_VECTOR_SPIHS0 % 8);
#endif
#ifdef SPIHS0_WITH_DMA
        g_spi0_tx_count = 1;         /* send data count */
        gp_spi0_tx_address = tx_buf; /* send buffer pointer */
#else
        g_spi0_tx_count = tx_num;    /* send data count */
        gp_spi0_tx_address = tx_buf; /* send buffer pointer */
#endif
        SPI0_Start();
        SPIHS0->SDRO0 = *gp_spi0_tx_address; /* started by writing data to SDRO */
        gp_spi0_tx_address++;
        g_spi0_tx_count--;
    }

    return (status);
}

/***********************************************************************************************************************
* Function Name: SPI0_MasterReceive
* @brief  This function receives SPI0 data.
* @param  rx_buf - receive buffer pointer
* @param  rx_num - buffer size
* @return status - MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS SPI0_MasterReceive(uint8_t *const rx_buf, uint16_t rx_num)
{
    MD_STATUS status = MD_OK;
    uint32_t dummy_sdr;

    if (rx_num < 1U)
    {
        status = MD_ERROR;
    }
    else
    {
        SPIHS0->SPIM0 &= ~(_0040_SPI_RECEPTION_TRANSMISSION | _0008_SPI_BUFFER_EMPTY); /* reception mode */
#ifdef SPIHS0_WITH_DMA
        /* read receive data with DMA */
        DMAVEC->VEC[DMA_VECTOR_SPIHS0] = CTRL_DATA_SPIHS0;
        DMAVEC->CTRL[CTRL_DATA_SPIHS0].DMACR = (0 << CTRL_DMACR_SZ_Pos) | (0 << CTRL_DMACR_CHNE_Pos) |
                                               (1 << CTRL_DMACR_DAMOD_Pos) | (0 << CTRL_DMACR_SAMOD_Pos) |
                                               (0 << CTRL_DMACR_MODE_Pos);
        DMAVEC->CTRL[CTRL_DATA_SPIHS0].DMBLS = 1;
        DMAVEC->CTRL[CTRL_DATA_SPIHS0].DMACT = rx_num;
        DMAVEC->CTRL[CTRL_DATA_SPIHS0].DMRLD = rx_num;
        DMAVEC->CTRL[CTRL_DATA_SPIHS0].DMSAR = (uint32_t)&SPIHS0->SDRI0;
        DMAVEC->CTRL[CTRL_DATA_SPIHS0].DMDAR = (uint32_t)rx_buf;

        /* init DMA registers */
        CGC->PER1 |= CGC_PER1_DMAEN_Msk;
        DMA->DMABAR = DMAVEC_BASE;
        DMA->DMAEN2 |= (1 << DMA_VECTOR_SPIHS0 % 8);
#endif
#ifdef SPIHS0_WITH_DMA
        g_spi0_rx_count = 0;                      /* receive data count */
        gp_spi0_rx_address = rx_buf + rx_num ;    /* receive buffer pointer */
#else
        g_spi0_rx_count = rx_num;    /* receive data count */
        gp_spi0_rx_address = rx_buf; /* receive buffer pointer */
#endif

        SPI0_Start();
        dummy_sdr = SPIHS0->SDRI0;
    }

    return (status);
}
/***********************************************************************************************************************
* Function Name: SPI0_SlaveInit
* @brief  This function restarts the SPI module.
* @param  mode
*             - SPI_MODE_0: CPOL = 0, CPHA = 0; i.e. CKP = 1, DAP = 1
*             - SPI_MODE_1: CPOL = 0, CPHA = 1; i.e. CKP = 1, DAP = 0
*             - SPI_MODE_2: CPOL = 1, CPHA = 0; i.e. CKP = 0, DAP = 1
*             - SPI_MODE_3: CPOL = 1, CPHA = 1; i.e. CKP = 0, DAP = 0
* @return None
***********************************************************************************************************************/
void SPI0_SlaveInit(spi_mode_t mode)
{
    CGC->PER1 |= 0x40;
    SPIHS0->SPIC0 = _0007_SPI_SLAVE_MODE | (mode & 0x03) << 3;    
    SPIHS0->SPIM0 = _0040_SPI_RECEPTION_TRANSMISSION | _0020_SPI_NSS_ENABLE | 
	                  _0000_SPI_MSB | _0000_SPI_TRANSFER_END | _0000_SPI_LENGTH_8;
    NSS0_PORT_SETTING();
    SCK0_PORT_SETTING();
    MOSI0_PORT_SETTING();
    MISO0_PORT_SETTING();
}
/***********************************************************************************************************************
* Function Name: SPI0_SlaveSend
* @brief  This function sends SPI data.
* @param  tx_buf - transfer buffer pointer
* @param  tx_num - buffer size
* @return status - MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS SPI0_SlaveSend(uint8_t *const tx_buf, uint16_t tx_num)
{
    MD_STATUS status = MD_OK;

    if (tx_num < 1U)
    {
        status = MD_ERROR;
    }
    else
    {
        SPIHS0->SPIM0 |= _0040_SPI_RECEPTION_TRANSMISSION | _0000_SPI_TRANSFER_END; /* transmission mode */
#ifdef SPIHS0_WITH_DMA
        /* write transfer data with DMA */
        DMAVEC->VEC[DMA_VECTOR_SPIHS0] = CTRL_DATA_SPIHS0;
        DMAVEC->CTRL[CTRL_DATA_SPIHS0].DMACR = (0 << CTRL_DMACR_SZ_Pos) | (0 << CTRL_DMACR_CHNE_Pos) |
                                               (0 << CTRL_DMACR_DAMOD_Pos) | (1 << CTRL_DMACR_SAMOD_Pos) |
                                               (0 << CTRL_DMACR_MODE_Pos);
        DMAVEC->CTRL[CTRL_DATA_SPIHS0].DMBLS = 1;
        DMAVEC->CTRL[CTRL_DATA_SPIHS0].DMACT = tx_num - 1;
        DMAVEC->CTRL[CTRL_DATA_SPIHS0].DMRLD = tx_num - 1;
        DMAVEC->CTRL[CTRL_DATA_SPIHS0].DMSAR = (uint32_t)(tx_buf + 1);
        DMAVEC->CTRL[CTRL_DATA_SPIHS0].DMDAR = (uint32_t)&SPIHS0->SDRO0;

        /* init DMA registers */
        CGC->PER1 |= CGC_PER1_DMAEN_Msk;
        DMA->DMABAR = DMAVEC_BASE;
        DMA->DMAEN2 |= (1 << DMA_VECTOR_SPIHS0 % 8);
#endif
#ifdef SPIHS0_WITH_DMA
        g_spi0_tx_count = 1;         /* send data count */
        gp_spi0_tx_address = tx_buf; /* send buffer pointer */
#else
        g_spi0_tx_count = tx_num;    /* send data count */
        gp_spi0_tx_address = tx_buf; /* send buffer pointer */
#endif
        SPI0_Start();
        SPIHS0->SDRO0 = *gp_spi0_tx_address; /* started by writing data to SDRO */
        gp_spi0_tx_address++;
        g_spi0_tx_count--;
    }

    return (status);
}

/***********************************************************************************************************************
* Function Name: SPI0_SlaveReceive
* @brief  This function receives SPI data.
* @param  rx_buf - receive buffer pointer
* @param  rx_num - buffer size
* @return status - MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS SPI0_SlaveReceive(uint8_t *const rx_buf, uint16_t rx_num)
{
    MD_STATUS status = MD_OK;
    uint32_t dummy_sdr;

    if (rx_num < 1U)
    {
        status = MD_ERROR;
    }
    else
    {
        SPIHS0->SPIM0 &= ~(_0040_SPI_RECEPTION_TRANSMISSION | _0008_SPI_BUFFER_EMPTY); /* reception mode */
#ifdef SPIHS0_WITH_DMA
        /* read receive data with DMA */
        DMAVEC->VEC[DMA_VECTOR_SPIHS0] = CTRL_DATA_SPIHS0;
        DMAVEC->CTRL[CTRL_DATA_SPIHS0].DMACR = (0 << CTRL_DMACR_SZ_Pos) | (0 << CTRL_DMACR_CHNE_Pos) |
                                               (1 << CTRL_DMACR_DAMOD_Pos) | (0 << CTRL_DMACR_SAMOD_Pos) |
                                               (0 << CTRL_DMACR_MODE_Pos);
        DMAVEC->CTRL[CTRL_DATA_SPIHS0].DMBLS = 1;
        DMAVEC->CTRL[CTRL_DATA_SPIHS0].DMACT = rx_num;
        DMAVEC->CTRL[CTRL_DATA_SPIHS0].DMRLD = rx_num;
        DMAVEC->CTRL[CTRL_DATA_SPIHS0].DMSAR = (uint32_t)&SPIHS0->SDRI0;
        DMAVEC->CTRL[CTRL_DATA_SPIHS0].DMDAR = (uint32_t)rx_buf;

        /* init DMA registers */
        CGC->PER1 |= CGC_PER1_DMAEN_Msk;
        DMA->DMABAR = DMAVEC_BASE;
        DMA->DMAEN2 |= (1 << DMA_VECTOR_SPIHS0 % 8);
#endif
#ifdef SPIHS0_WITH_DMA
        g_spi0_rx_count = 0;                      /* receive data count */
        gp_spi0_rx_address = rx_buf + rx_num; /* receive buffer pointer */
#else
        g_spi0_rx_count = rx_num;    /* receive data count */
        gp_spi0_rx_address = rx_buf; /* receive buffer pointer */
#endif

        SPI0_Start();
        dummy_sdr = SPIHS0->SDRI0;
    }

    return (status);
}

/***********************************************************************************************************************
* Function Name: SPI1_MasterInit
* @brief  This function restarts the SPI1 module.
* @param  mode
*             - SPI_MODE_0: CPOL = 0, CPHA = 0; i.e. CKP = 1, DAP = 1
*             - SPI_MODE_1: CPOL = 0, CPHA = 1; i.e. CKP = 1, DAP = 0
*             - SPI_MODE_2: CPOL = 1, CPHA = 0; i.e. CKP = 0, DAP = 1
*             - SPI_MODE_3: CPOL = 1, CPHA = 1; i.e. CKP = 0, DAP = 0
* @return None
***********************************************************************************************************************/
void SPI1_MasterInit(spi_mode_t mode)
{
    CGC->PER1 |= 0x80;
#ifdef SPIHS1_WITH_DMA
    SPIHS1->SPIC1 = _0001_SPI_SCK_fCLK_1 | (mode & 0x03) << 3;    
#else
    SPIHS1->SPIC1 = _0006_SPI_SCK_fCLK_6 | (mode & 0x03) << 3;    
#endif
    SPIHS1->SPIM1 = _0040_SPI_RECEPTION_TRANSMISSION | _0000_SPI_MSB | _0000_SPI_TRANSFER_END | _0000_SPI_LENGTH_8;
    NSS1_PORT_SETTING();
    SCK1_PORT_SETTING();
    MOSI1_PORT_SETTING();
    MISO1_PORT_SETTING();
}

/***********************************************************************************************************************
* Function Name: SPI1_Start
* @brief  This function starts the SPI1 module operation.
* @param  None
* @return None
***********************************************************************************************************************/
void SPI1_Start(void)
{
    /* clear INTSPI interrupt flag */
    INTC_ClearPendingIRQ(SPI1_IRQn);
    NVIC_ClearPendingIRQ(SPI1_IRQn);
    /* enable INTSPI interrupt */
    //INTC_EnableIRQ(SPI1_IRQn);
    NVIC_EnableIRQ(SPI1_IRQn);
    SPIHS1->SPIM1 |= _0080_SPI_START_TRG_ON; 
    /* SSn Active */
    NSS1_PORT_CLR();
}
/***********************************************************************************************************************
* Function Name: SPI1_Stop
* @brief  This function stops the SPI1 module operation.
* @param  None
* @return None
***********************************************************************************************************************/
void SPI1_Stop(void)
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
/***********************************************************************************************************************
* Function Name: SPI1_MasterSend
* @brief  This function sends SPI data.
* @param  tx_buf - transfer buffer pointer
* @param  tx_num - buffer size
* @return status - MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS SPI1_MasterSend(uint8_t *const tx_buf, uint16_t tx_num)
{
    MD_STATUS status = MD_OK;

    if (tx_num < 1U)
    {
        status = MD_ERROR;
    }
    else
    {
        SPIHS1->SPIM1 |= _0040_SPI_RECEPTION_TRANSMISSION | _0000_SPI_TRANSFER_END; /* transmission mode */
#ifdef SPIHS1_WITH_DMA
        /* write transfer data with DMA */
        DMAVEC->VEC[DMA_VECTOR_SPIHS1] = CTRL_DATA_SPIHS1;
        DMAVEC->CTRL[CTRL_DATA_SPIHS1].DMACR = (0 << CTRL_DMACR_SZ_Pos) | (0 << CTRL_DMACR_CHNE_Pos) |
                                               (0 << CTRL_DMACR_DAMOD_Pos) | (1 << CTRL_DMACR_SAMOD_Pos) |
                                               (0 << CTRL_DMACR_MODE_Pos);
        DMAVEC->CTRL[CTRL_DATA_SPIHS1].DMBLS = 1;
        DMAVEC->CTRL[CTRL_DATA_SPIHS1].DMACT = tx_num - 1;
        DMAVEC->CTRL[CTRL_DATA_SPIHS1].DMRLD = tx_num - 1;
        DMAVEC->CTRL[CTRL_DATA_SPIHS1].DMSAR = (uint32_t)(tx_buf + 1);
        DMAVEC->CTRL[CTRL_DATA_SPIHS1].DMDAR = (uint32_t)&SPIHS1->SDRO1;

        /* init DMA registers */
        CGC->PER1 |= CGC_PER1_DMAEN_Msk;
        DMA->DMABAR = DMAVEC_BASE;
        DMA->DMAEN2 |= (1 << DMA_VECTOR_SPIHS1 % 8);
#endif
#ifdef SPIHS1_WITH_DMA
        g_spi1_tx_count = 1;         /* send data count */
        gp_spi1_tx_address = tx_buf; /* send buffer pointer */
#else
        g_spi1_tx_count = tx_num;    /* send data count */
        gp_spi1_tx_address = tx_buf; /* send buffer pointer */
#endif
        SPI1_Start();
        SPIHS1->SDRO1 = *gp_spi1_tx_address; /* started by writing data to SDRO */
        gp_spi1_tx_address++;
        g_spi1_tx_count--;
    }

    return (status);
}

/***********************************************************************************************************************
* Function Name: SPI1_MasterReceive
* @brief  This function receives SPI1 data.
* @param  rx_buf - receive buffer pointer
* @param  rx_num - buffer size
* @return status - MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS SPI1_MasterReceive(uint8_t *const rx_buf, uint16_t rx_num)
{
    MD_STATUS status = MD_OK;
    uint32_t dummy_sdr;

    if (rx_num < 1U)
    {
        status = MD_ERROR;
    }
    else
    {
        SPIHS1->SPIM1 &= ~(_0040_SPI_RECEPTION_TRANSMISSION | _0008_SPI_BUFFER_EMPTY); /* reception mode */
#ifdef SPIHS1_WITH_DMA
        /* read receive data with DMA */
        DMAVEC->VEC[DMA_VECTOR_SPIHS1] = CTRL_DATA_SPIHS1;
        DMAVEC->CTRL[CTRL_DATA_SPIHS1].DMACR = (0 << CTRL_DMACR_SZ_Pos) | (0 << CTRL_DMACR_CHNE_Pos) |
                                               (1 << CTRL_DMACR_DAMOD_Pos) | (0 << CTRL_DMACR_SAMOD_Pos) |
                                               (0 << CTRL_DMACR_MODE_Pos);
        DMAVEC->CTRL[CTRL_DATA_SPIHS1].DMBLS = 1;
        DMAVEC->CTRL[CTRL_DATA_SPIHS1].DMACT = rx_num;
        DMAVEC->CTRL[CTRL_DATA_SPIHS1].DMRLD = rx_num;
        DMAVEC->CTRL[CTRL_DATA_SPIHS1].DMSAR = (uint32_t)&SPIHS1->SDRI1;
        DMAVEC->CTRL[CTRL_DATA_SPIHS1].DMDAR = (uint32_t)rx_buf;

        /* init DMA registers */
        CGC->PER1 |= CGC_PER1_DMAEN_Msk;
        DMA->DMABAR = DMAVEC_BASE;
        DMA->DMAEN2 |= (1 << DMA_VECTOR_SPIHS1 % 8);
#endif
#ifdef SPIHS1_WITH_DMA
        g_spi1_rx_count = 0;                      /* receive data count */
        gp_spi1_rx_address = rx_buf + rx_num ;    /* receive buffer pointer */
#else
        g_spi1_rx_count = rx_num;    /* receive data count */
        gp_spi1_rx_address = rx_buf; /* receive buffer pointer */
#endif

        SPI1_Start();
        dummy_sdr = SPIHS1->SDRI1;
    }

    return (status);
}
/***********************************************************************************************************************
* Function Name: SPI1_SlaveInit
* @brief  This function restarts the SPI module.
* @param  mode
*             - SPI_MODE_0: CPOL = 0, CPHA = 0; i.e. CKP = 1, DAP = 1
*             - SPI_MODE_1: CPOL = 0, CPHA = 1; i.e. CKP = 1, DAP = 0
*             - SPI_MODE_2: CPOL = 1, CPHA = 0; i.e. CKP = 0, DAP = 1
*             - SPI_MODE_3: CPOL = 1, CPHA = 1; i.e. CKP = 0, DAP = 0
* @return None
***********************************************************************************************************************/
void SPI1_SlaveInit(spi_mode_t mode)
{
    CGC->PER1 |= 0x80;
    SPIHS1->SPIC1 = _0007_SPI_SLAVE_MODE | (mode & 0x03) << 3;    
    SPIHS1->SPIM1 = _0040_SPI_RECEPTION_TRANSMISSION | _0000_SPI_MSB | _0000_SPI_TRANSFER_END | _0000_SPI_LENGTH_8;
    NSS1_PORT_SETTING();
    SCK1_PORT_SETTING();
    MOSI1_PORT_SETTING();
    MISO1_PORT_SETTING();
}
/***********************************************************************************************************************
* Function Name: SPI1_SlaveSend
* @brief  This function sends SPI data.
* @param  tx_buf - transfer buffer pointer
* @param  tx_num - buffer size
* @return status - MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS SPI1_SlaveSend(uint8_t *const tx_buf, uint16_t tx_num)
{
    MD_STATUS status = MD_OK;

    if (tx_num < 1U)
    {
        status = MD_ERROR;
    }
    else
    {
        SPIHS1->SPIM1 |= _0040_SPI_RECEPTION_TRANSMISSION | _0008_SPI_BUFFER_EMPTY; /* transmission mode */
#ifdef SPIHS1_WITH_DMA
        /* write transfer data with DMA */
        DMAVEC->VEC[DMA_VECTOR_SPIHS1] = CTRL_DATA_SPIHS1;
        DMAVEC->CTRL[CTRL_DATA_SPIHS1].DMACR = (0 << CTRL_DMACR_SZ_Pos) | (0 << CTRL_DMACR_CHNE_Pos) |
                                               (0 << CTRL_DMACR_DAMOD_Pos) | (1 << CTRL_DMACR_SAMOD_Pos) |
                                               (0 << CTRL_DMACR_MODE_Pos);
        DMAVEC->CTRL[CTRL_DATA_SPIHS1].DMBLS = 1;
        DMAVEC->CTRL[CTRL_DATA_SPIHS1].DMACT = tx_num - 1;
        DMAVEC->CTRL[CTRL_DATA_SPIHS1].DMRLD = tx_num - 1;
        DMAVEC->CTRL[CTRL_DATA_SPIHS1].DMSAR = (uint32_t)(tx_buf + 1);
        DMAVEC->CTRL[CTRL_DATA_SPIHS1].DMDAR = (uint32_t)&SPIHS1->SDRO1;

        /* init DMA registers */
        CGC->PER1 |= CGC_PER1_DMAEN_Msk;
        DMA->DMABAR = DMAVEC_BASE;
        DMA->DMAEN2 |= (1 << DMA_VECTOR_SPIHS1 % 8);
#endif
#ifdef SPIHS1_WITH_DMA
        g_spi1_tx_count = 1;         /* send data count */
        gp_spi1_tx_address = tx_buf; /* send buffer pointer */
#else
        g_spi1_tx_count = tx_num;    /* send data count */
        gp_spi1_tx_address = tx_buf; /* send buffer pointer */
#endif
        SPI1_Start();
        SPIHS1->SDRO1 = *gp_spi1_tx_address; /* started by writing data to SDRO */
        gp_spi1_tx_address++;
        g_spi1_tx_count--;
    }

    return (status);
}

/***********************************************************************************************************************
* Function Name: SPI1_SlaveReceive
* @brief  This function receives SPI data.
* @param  rx_buf - receive buffer pointer
* @param  rx_num - buffer size
* @return status - MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS SPI1_SlaveReceive(uint8_t *const rx_buf, uint16_t rx_num)
{
    MD_STATUS status = MD_OK;
    uint32_t dummy_sdr;

    if (rx_num < 1U)
    {
        status = MD_ERROR;
    }
    else
    {
        SPIHS1->SPIM1 &= ~(_0040_SPI_RECEPTION_TRANSMISSION | _0008_SPI_BUFFER_EMPTY); /* reception mode */
#ifdef SPIHS1_WITH_DMA
        /* read receive data with DMA */
        DMAVEC->VEC[DMA_VECTOR_SPIHS1] = CTRL_DATA_SPIHS1;
        DMAVEC->CTRL[CTRL_DATA_SPIHS1].DMACR = (0 << CTRL_DMACR_SZ_Pos) | (0 << CTRL_DMACR_CHNE_Pos) |
                                               (1 << CTRL_DMACR_DAMOD_Pos) | (0 << CTRL_DMACR_SAMOD_Pos) |
                                               (0 << CTRL_DMACR_MODE_Pos);
        DMAVEC->CTRL[CTRL_DATA_SPIHS1].DMBLS = 1;
        DMAVEC->CTRL[CTRL_DATA_SPIHS1].DMACT = rx_num;
        DMAVEC->CTRL[CTRL_DATA_SPIHS1].DMRLD = rx_num;
        DMAVEC->CTRL[CTRL_DATA_SPIHS1].DMSAR = (uint32_t)&SPIHS1->SDRI1;
        DMAVEC->CTRL[CTRL_DATA_SPIHS1].DMDAR = (uint32_t)rx_buf;

        /* init DMA registers */
        CGC->PER1 |= CGC_PER1_DMAEN_Msk;
        DMA->DMABAR = DMAVEC_BASE;
        DMA->DMAEN2 |= (1 << DMA_VECTOR_SPIHS1 % 8);
#endif
#ifdef SPIHS1_WITH_DMA
        g_spi1_rx_count = 0;                      /* receive data count */
        gp_spi1_rx_address = rx_buf + rx_num; /* receive buffer pointer */
#else
        g_spi1_rx_count = rx_num;    /* receive data count */
        gp_spi1_rx_address = rx_buf; /* receive buffer pointer */
#endif

        SPI1_Start();
        dummy_sdr = SPIHS1->SDRI1;
    }

    return (status);
}
/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
