/********************************************************
* @file       hal_lcd.c
* @author     szhj13
* @version    V1.0
* @date       2022-05-18
* @brief      the start address of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "hal_lcd.h"

/* Private typedef --------------------------------------*/
/* Private define ---------------------------------------*/
#define DMA_CTRL_DATA_LCDB 0
#define SPI_DMA_CHANNEL 1

/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
/* Private variables ------------------------------------*/
LCDB_Typedef Lcdb;
static lcd_isr_callback_t lcd_isr_callback = NULL;
static uint8_t lcdRxReqFlag;
static uint8_t lcd_interrupt_cnt;
static uint8_t spihs1dmacount;
static uint16_t backcolor;


void Hal_Lcd_Init(void )
{
    //pa02, output, lcd reset
    PORT_Init(PORTA, PIN2, OUTPUT);
    //pa10, output, lcd cs
    PORT_Init(PORTA, PIN10, OUTPUT);
    //pd00, output, lcd RS
    PORT_Init(PORTD, PIN0, OUTPUT);

    Lcdb.mode = LCDB_MODE_TYPE_8080;	/* 8080 Mode */
	Lcdb.clock_div = LCDB_CLOCK_DIV_1;	/* 1 divider */
	Lcdb.cycle = LDB_CYCLE_8T;//LDB_CYCLE_6T;	/* 6T cycles */
	Lcdb.wait_cycle = LDB_WAIT_CYCLE_2T;	/* 2T wait cycles */

    LCDB_Init(&Lcdb);
}

/***********************************************************************************************************************
* Function Name: LCDB_Init
* @brief  This function initializes the LCDB module.
* @param  pinMsk - 
* @return None
***********************************************************************************************************************/
void LCDB_Init(LCDB_Typedef* pLcdb)
{
    CGC->PER1 |= CGC_PER1_LCDBEN_Msk;	/*enable lcdb clock*/
	
	if(LCDB_MODE_TYPE_8080 == pLcdb->mode)
	{
		LCDB->LBCTL &= ~LCDB_LBCTL_IMD_Msk;
	}
	else
	{
		LCDB->LBCTL |= LCDB_LBCTL_IMD_Msk;
		if(LCDB_MODE_6800_CNTL_ENABLE_HIGH == pLcdb->mode_6800_E_level)
		{
			LCDB->LBCTL &= ~LCDB_LBCTL_EL_Msk;
		}
		else
		{
			LCDB->LBCTL |= LCDB_LBCTL_EL_Msk;
		}
	}
	
	LCDB->LBCTL &= ~LCDB_LBCTL_LBC_Msk;//lcdb clock divider
	LCDB->LBCTL |= (pLcdb->clock_div)<<LCDB_LBCTL_LBC_Pos;
	
	LCDB->LBCYC = pLcdb->cycle;
	
	LCDB->LBWST = pLcdb->wait_cycle;
	
    /* Set LCDB pin */
	PORT->PC &= ~0xF3C0;//PC6-9 PC12-15
	PORT->PC |= 0x0C00;//PC10-11
	
    PORT->PMCC &= ~(0x3FF<<6);//PC6-15 digital function
    PORT->PMC &= ~0x0C00;//PC10-11 output mode
	PORT->PMC |= 0xF3C0;//PC6-9 PC12-15 input mode
	
    INTC_DisableIRQ(LCDB_IRQn);      /* disable LCDB interrupt */
    INTC_ClearPendingIRQ(LCDB_IRQn); /* clear LCDB interrupt flag */
}

/***********************************************************************************************************************
* Function Name: LCDB_Start
* @brief  This function clears LCDB interrupt flag and enables interrupt.
* @param  None
* @return None
***********************************************************************************************************************/
void LCDB_Start(void)
{
    INTC_ClearPendingIRQ(LCDB_IRQn); /* clear LCDB interrupt flag */
    INTC_EnableIRQ(LCDB_IRQn);/* enable LCDB interrupt */
}

/***********************************************************************************************************************
* Function Name: LCDB_Stop
* @brief  This function disables LCDB interrupt and clears interrupt flag.
* @param  None
* @return None
***********************************************************************************************************************/
void LCDB_Stop(void)
{
    INTC_DisableIRQ(LCDB_IRQn);      /* disable LCDB interrupt */
    INTC_ClearPendingIRQ(LCDB_IRQn); /* clear LCDB interrupt flag */
}


void Hal_Lcd_Set_BgColor(uint16_t color, lcd_isr_callback_t callback )
{
    backcolor = color;

    LCD_CS_LOW();

	LCD_DC_LOW();

	Write_LBDATAL(0x2C);
	
	LCD_DC_HIGH();
    
    DMAVEC->VEC[DMA_VECTOR_LCDB] = DMA_CTRL_DATA_LCDB;
    DMAVEC->CTRL[DMA_CTRL_DATA_LCDB].DMACR = (DMA_SIZE_HALF << CTRL_DMACR_SZ_Pos) | (1 << CTRL_DMACR_RPTINT_Pos) |
                                             (0 << CTRL_DMACR_DAMOD_Pos)  | (0 << CTRL_DMACR_SAMOD_Pos) |
                                             (0 << CTRL_DMACR_RPTSEL_Pos)| (DMA_MODE_NORMAL << CTRL_DMACR_MODE_Pos);
    DMAVEC->CTRL[DMA_CTRL_DATA_LCDB].DMBLS = 1;
    DMAVEC->CTRL[DMA_CTRL_DATA_LCDB].DMACT = (LCD_W*LCD_H)/2-1;
    DMAVEC->CTRL[DMA_CTRL_DATA_LCDB].DMRLD = (LCD_W*LCD_H)/2-1;
    DMAVEC->CTRL[DMA_CTRL_DATA_LCDB].DMSAR = (uint32_t)((uint16_t*)&backcolor);
    DMAVEC->CTRL[DMA_CTRL_DATA_LCDB].DMDAR = (uint32_t)((uint16_t*)&LCDB->LBDATA);

    /* init DMA registers */
    CGC->PER1   |= CGC_PER1_DMAEN_Msk;
    DMA->DMABAR  = DMAVEC_BASE;
    
	DMA_Enable(DMA_VECTOR_LCDB);

    LCDB_Start();

    lcd_isr_callback = callback;

    lcd_interrupt_cnt = 0;

    lcdRxReqFlag = 1;

    LCDB->LBDATA = color;
}

void Hal_Lcd_Show_Pic(uint32_t flashAddr, lcd_isr_callback_t callback )
{
    uint16_t  dummy;

    SPIHS1->SPIM1 &= ~_0004_SPI_LENGTH_16;
	SPIHS1->SPIM1 &= ~_0002_SPI_CONTINOUS_RECEPTION;
	SPIHS1->SPIM1 |= _0040_SPI_RECEPTION_TRANSMISSION;

    /* /CS: active */
    Hal_Spi_Start();    
    /* Send command 0x0B: Read data */
    //SPIHS1_Send(0x0B);
    Hal_Spi_Tx_Single_With_Blocking(0x0B);
    /* Send 24-bit start address */
    Hal_Spi_Tx_Single_With_Blocking((uint8_t )(flashAddr >> 16));
    Hal_Spi_Tx_Single_With_Blocking((uint8_t )(flashAddr >> 8));
    Hal_Spi_Tx_Single_With_Blocking((uint8_t ) flashAddr);
    Hal_Spi_Tx_Single_With_Blocking(0xff);//dummy

    LCD_CS_LOW();

	LCD_DC_LOW();

	Write_LBDATAL(0x2C);
	
	LCD_DC_HIGH();

    SPIHS1->SPIM1 |= _0004_SPI_LENGTH_16;

	SPIHS1->SPIM1 &= ~_0040_SPI_RECEPTION_TRANSMISSION;
	
    DMAVEC->VEC[DMA_VECTOR_SPIHS1] = SPI_DMA_CHANNEL;
    
    DMAVEC->CTRL[SPI_DMA_CHANNEL].DMACR = (DMA_SIZE_HALF << CTRL_DMACR_SZ_Pos)  | (0<<CTRL_DMACR_CHNE_Pos) | (0 << CTRL_DMACR_RPTINT_Pos) |
                                        (0 << CTRL_DMACR_DAMOD_Pos)  | (0 << CTRL_DMACR_SAMOD_Pos) |
                                        (0 << CTRL_DMACR_RPTSEL_Pos)| (DMA_MODE_NORMAL << CTRL_DMACR_MODE_Pos);
    DMAVEC->CTRL[SPI_DMA_CHANNEL].DMBLS = 1;
    DMAVEC->CTRL[SPI_DMA_CHANNEL].DMACT = (LCD_W*LCD_H)/2;
    DMAVEC->CTRL[SPI_DMA_CHANNEL].DMRLD = (LCD_W*LCD_H)/2;
    DMAVEC->CTRL[SPI_DMA_CHANNEL].DMSAR = (uint32_t)(&SPIHS1->SDRI1);
    DMAVEC->CTRL[SPI_DMA_CHANNEL].DMDAR = (uint32_t)((uint16_t*)&LCDB->LBDATA);

    /* init DMA registers */
    CGC->PER1   |= CGC_PER1_DMAEN_Msk;
    DMA->DMABAR  = DMAVEC_BASE;
	DMA_Enable(DMA_VECTOR_SPIHS1);

    lcd_isr_callback = callback;
    
    lcd_interrupt_cnt = 0;
    
    lcdRxReqFlag = 1;

    dummy = SPIHS1->SDRI1;
	
	INTC_ClearPendingIRQ(SPI1_IRQn);
	INTC_EnableIRQ(SPI1_IRQn);
}

void Hal_Lcd_Clr_Isr_Handler(void )
{
    if(lcdRxReqFlag)
    {
    	if(++lcd_interrupt_cnt==1)
    	{
    		DMAVEC->CTRL[DMA_CTRL_DATA_LCDB].DMACT = (LCD_W*LCD_H)/2-1;
    		DMA_Enable(DMA_VECTOR_LCDB);
    		LCDB->LBDATA = backcolor;
    	}
    	else
    	{
            lcdRxReqFlag = 0;
            
    		LCD_CS_HIGH();

            //因为图片数据从外部flash写入LCDB的时候，SPI配置的是16bit, 接收模式，
            //所以，接收完成后，需要将SPI配置成8bit, 发送模式，以便可以通过SPI读写外部flash
            SPIHS1->SPIM1 |= _0040_SPI_RECEPTION_TRANSMISSION;
            
            SPIHS1->SPIM1 &= ~_0004_SPI_LENGTH_16;

            lcd_interrupt_cnt = 0;

            if(lcd_isr_callback != NULL)
            {
                lcd_isr_callback();
            }
    		
    		LCDB_Stop();
    	}
    }
}

void Hal_Lcd_Pic_Isr_Handler(void)
{
    volatile uint8_t sio_dummy;

    if(lcdRxReqFlag)
    {
    	if(++lcd_interrupt_cnt == 1)
    	{
    		DMAVEC->CTRL[SPI_DMA_CHANNEL].DMACT = (LCD_W*LCD_H)/2-1;
    		
    		DMA_Enable(DMA_VECTOR_SPIHS1);
    		LCDB->LBDATA = SPIHS1->SDRI1;
    	}
    	else
    	{
            lcdRxReqFlag = 0;
            
    		LCD_CS_HIGH();
            //因为图片数据从外部flash写入LCDB的时候，SPI配置的是16bit, 接收模式，
            //所以，接收完成后，需要将SPI配置成8bit, 发送模式，以便可以通过SPI读写外部flash
            SPIHS1->SPIM1 |= _0040_SPI_RECEPTION_TRANSMISSION;
            
            SPIHS1->SPIM1 &= ~_0004_SPI_LENGTH_16;
            
            Hal_Spi_Cs_Set();

            if(lcd_isr_callback != NULL)
            {
                lcd_isr_callback();
            }
            
    		INTC_DisableIRQ(SPI1_IRQn);
    	}
    }
}




