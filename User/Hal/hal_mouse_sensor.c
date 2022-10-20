/********************************************************
* @file       hal_mouse_sensor.c
* @author     szhj13
* @version    V1.0
* @date       2022-05-18
* @brief      the start address of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "hal_mouse_sensor.h"
/* Private typedef --------------------------------------*/
/* Private define ---------------------------------------*/
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/

/* Private variables ------------------------------------*/

void Hal_Mouse_Sensor_Spi_Init(void )
{
    uint8_t dap, ckp;
    spi_mode_t mode = SPI_MODE_3;
    
    dap = ~mode & 0x01;
    ckp = (~mode & 0x02) >> 1;
    CGC->PER0 |= CGC_PER0_SCI1EN_Msk;
    SCI1->ST1 |= _0002_SCI_CH1_STOP_TRG_ON;
    SCI1->SPS1 &= ~SCI0_SPS0_PRS01_Msk;
    SCI1->SPS1 |= (0 << SCI0_SPS0_PRS01_Pos);
    SCI1->SIR11 = _0004_SCI_SIRMN_FECTMN | _0002_SCI_SIRMN_PECTMN | _0001_SCI_SIRMN_OVCTMN;
    SCI1->SMR11 = _0020_SMRMN_DEFAULT_VALUE | _8000_SCI_CLOCK_SELECT_CK01 | _0000_SCI_CLOCK_MODE_CKS |
                  _0000_SCI_TRIGGER_SOFTWARE | _0000_SCI_MODE_SPI | _0000_SCI_TRANSFER_END;
    SCI1->SCR11 = _0004_SCRMN_DEFAULT_VALUE | _C000_SCI_RECEPTION_TRANSMISSION | dap << 13 | ckp << 12 | _0000_SCI_INTSRE_MASK |
                  _0000_SCI_PARITY_NONE | _0000_SCI_MSB | _0000_SCI_STOP_NONE | _0007_SCI_LENGTH_8;

    SCI1->SDR11 = 3 << 9;		// fMCK/(1+n)x2 = fMCK/8  

    /* Set output enable */
    if ((mode == SPI_MODE_0) || (mode == SPI_MODE_1))
    {
        SCI1->SO1 &= ~_0200_SCI_CH1_CLOCK_OUTPUT_1;
    }
    if ((mode == SPI_MODE_2) || (mode == SPI_MODE_3))
    {
        SCI1->SO1 |= _0200_SCI_CH1_CLOCK_OUTPUT_1;
    }
    SCI1->SOE1 |= _0002_SCI_CH1_OUTPUT_ENABLE;

    /* Set SSn pin */
    SS11_PORT_SETTING();
    /* Set SCLK11 pin */
    SCLKO11_PORT_SETTING();
    /* Set SDI11 pin */
    SDI11_PORT_SETTING();
    /* Set SDO11 pin */
    SDO11_PORT_SETTING();
}

void Hal_Mouse_Sensor_Spi_Start(void )
{
    SS11_PORT_CLR();
        
    SCI1->SOE1 |= _0002_SCI_CH1_OUTPUT_ENABLE;
    SCI1->SS1 |= _0002_SCI_CH1_START_TRG_ON;
}

void Hal_Mouse_Sensor_Spi_Stop(void )
{
    SCI1->ST1 |= _0002_SCI_CH1_STOP_TRG_ON;
    SCI1->SOE1 &= (uint16_t)~_0002_SCI_CH1_OUTPUT_ENABLE;

    SS11_PORT_SET();
}

void Hal_Mouse_Sensor_Spi_Write_One_Data(uint8_t dat )
{
    SCI1->SIO11 = dat;
    
    while (SCI1->SSR11 & _0040_SCI_UNDER_EXECUTE)
    {
        ;
    }
}

uint8_t Hal_Mouse_Sensor_Spi_Read_One_Data(void )
{
    uint8_t sio_dummy = 0xff;

    Hal_Mouse_Sensor_Spi_Write_One_Data(sio_dummy);
    
    sio_dummy = SCI1->SIO11;

    return sio_dummy;
}



