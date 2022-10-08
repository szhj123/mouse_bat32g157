/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    userdefine.h
* @brief   This file includes user definition.
* @version 1.0.0
* @date    2020/10/24
***********************************************************************************************************************/
#ifndef _USER_DEF_H
#define _USER_DEF_H

/***********************************************************************************************************************
User definitions
***********************************************************************************************************************/
#ifndef __TYPEDEF__

typedef unsigned short 	MD_STATUS;
/* Status list definition */
#define MD_STATUSBASE        (0x00U)
#define MD_OK                (MD_STATUSBASE + 0x00U) /* register setting OK */
#define MD_SPT               (MD_STATUSBASE + 0x01U) /* IIC stop */
#define MD_NACK              (MD_STATUSBASE + 0x02U) /* IIC no ACK */
#define MD_BUSY1             (MD_STATUSBASE + 0x03U) /* busy 1 */
#define MD_BUSY2             (MD_STATUSBASE + 0x04U) /* busy 2 */
#define MD_OVERRUN           (MD_STATUSBASE + 0x05U) /* IIC OVERRUN occur */

/* Error list definition */
#define MD_ERRORBASE         (0x80U)
#define MD_ERROR             (MD_ERRORBASE + 0x00U)  /* error */
#define MD_ARGERROR          (MD_ERRORBASE + 0x01U)  /* error agrument input error */
#define MD_ERROR1            (MD_ERRORBASE + 0x02U)  /* error 1 */
#define MD_ERROR2            (MD_ERRORBASE + 0x03U)  /* error 2 */
#define MD_ERROR3            (MD_ERRORBASE + 0x04U)  /* error 3 */
#define MD_ERROR4            (MD_ERRORBASE + 0x05U)  /* error 4 */
#define MD_ERROR5            (MD_ERRORBASE + 0x06U)  /* error 5 */
#endif

/* IO Alternative definition */
#define PTCFG_DFT             (0x00U)
/* Group 0 output function */
#define PTCFG_TO00            (0x01U)
#define PTCFG_TO01            (0x02U)
#define PTCFG_TO02            (0x03U)
#define PTCFG_TO03            (0x04U)
#define PTCFG_TXD0            (0x05U)
#define PTCFG_SDO00           (0x05U)

/* Group 1 output function */
#define PTCFG_TO10            (0x01U)
#define PTCFG_TO11            (0x02U)
#define PTCFG_TO12            (0x03U)
#define PTCFG_TO13            (0x04U)
#define PTCFG_TXD1            (0x05U)
#define PTCFG_SPIHS0_SCKO     (0x06U)
#define PTCFG_SPIHS0_MO       (0x07U)
#define PTCFG_SPIHS0_SO       (0x08U)

/* Group 2 output function */
#define PTCFG_TO14            (0x01U)
#define PTCFG_TO15            (0x02U)
#define PTCFG_TO16            (0x03U)
#define PTCFG_TO17            (0x04U)
#define PTCFG_TXD2            (0x05U)
#define PTCFG_CLKBUZ1         (0x06U)

/* Group 0 input function */
#define PTCFG_UNDEF           (0x00U)
#define PTCFG_PB00            (0x01U)
#define PTCFG_PH04            (0x02U)
#define PTCFG_PH03            (0x03U)
#define PTCFG_PH02            (0x04U)
#define PTCFG_PH01            (0x05U)
#define PTCFG_PC14            (0x06U)
#define PTCFG_PC15            (0x07U)
#define PTCFG_PC08            (0x08U)
#define PTCFG_PC09            (0x09U)
#define PTCFG_PC10            (0x0AU)
#define PTCFG_PC11            (0x0BU)
#define PTCFG_PA00            (0x0CU)
#define PTCFG_PA01            (0x0DU)
#define PTCFG_PA02            (0x0EU)
#define PTCFG_PA03            (0x0FU)
#define PTCFG_PD07            (0x10U)
#define PTCFG_PD08            (0x11U)
#define PTCFG_PD09            (0x12U)
#define PTCFG_PD10            (0x13U)
#define PTCFG_PD11            (0x14U)

/* Group 1 input function */
#define PTCFG_UNDEF           (0x00U)
#define PTCFG_PC03            (0x01U)
#define PTCFG_PC04            (0x02U)
#define PTCFG_PC05            (0x03U)
#define PTCFG_PC06            (0x04U)
#define PTCFG_PC07            (0x05U)
#define PTCFG_PC12            (0x06U)
#define PTCFG_PC13            (0x07U)
#define PTCFG_PA04            (0x08U)
#define PTCFG_PA05            (0x09U)
#define PTCFG_PA06            (0x0AU)
#define PTCFG_PA07            (0x0BU)
#define PTCFG_PA08            (0x0CU)
#define PTCFG_PA09            (0x0DU)
#define PTCFG_PA10            (0x0EU)
#define PTCFG_PD00            (0x0FU)
#define PTCFG_PD01            (0x10U)
#define PTCFG_PD12            (0x11U)
#define PTCFG_PD13            (0x12U)
#define PTCFG_PD14            (0x13U)
#define PTCFG_PD15            (0x14U)

/* Group 2 input function */
#define PTCFG_UNDEF           (0x00U)
#define PTCFG_PB01            (0x01U)
#define PTCFG_PB02            (0x02U)
#define PTCFG_PB03            (0x03U)
#define PTCFG_PB04            (0x04U)
#define PTCFG_PB05            (0x05U)
#define PTCFG_PB06            (0x06U)
#define PTCFG_PB07            (0x07U)
#define PTCFG_PB08            (0x08U)
#define PTCFG_PC00            (0x09U)
#define PTCFG_PC01            (0x0AU)
#define PTCFG_PC02            (0x0BU)
#define PTCFG_PA11            (0x0CU)
#define PTCFG_PA12            (0x0DU)
#define PTCFG_PA13            (0x0EU)
#define PTCFG_PA14            (0x0FU)
#define PTCFG_PD02            (0x10U)
#define PTCFG_PD03            (0x11U)
#define PTCFG_PD04            (0x12U)
#define PTCFG_PD05            (0x13U)
#define PTCFG_PD06            (0x14U)

#define TESOPT  *((volatile uint8_t *)(0x4004384C))  /*!< (@ 0x4004384C) PGA protect register                          */
#define TESCTL 	*((volatile uint8_t *)(0x4004384D))  /*!< (@ 0x4004384D) PGA output control register                   */
#define TRMW    *((volatile uint8_t *)(0x40021C08))
#define TRMR    *((volatile uint8_t *)(0x40021C09))
#define TRMT    *((volatile uint8_t *)(0x40021C0A))
#define CNTLD   *((volatile uint16_t *)(0x40021C28)) /*!< (@ 0x40021C28) counter load value of wakeup time             */
#define USBTRMSEL *((volatile uint16_t *)(0x40080400))
#define USBRTRIM *((volatile uint16_t *)(0x40080408))
#define USBVDATSRC *((volatile uint16_t *)(0x4008040C))

//#define RTL_SIMULATION

/***********************************************************************************************************************
Macro definitions of SCI usage:
Each channel of SCI has three functions: UART, SPI, and IIC. You can only choose one function to use.
***********************************************************************************************************************/
/* ToDo: You can only define ONE of the following THREE MACROs according to your application */
//#define USE_SCI_UART0_TX      /*! Using CH0 of SCI0 as UART Transmitter */
//#define USE_SCI_SPI00         /*! Using CH0 of SCI0 as SPI Transmitter or Receiver */
//#define USE_SCI_IIC00         /*! Using CH0 of SCI0 as IIC Transmitter or Receiver */

/* ToDo: You can only define ONE of the following THREE MACROs according to your application */
//#define USE_SCI_UART0_RX      /*! Using CH1 of SCI0 as UART Receiver */
//#define USE_SCI_SPI01         /*! Using CH1 of SCI0 as SPI Transmitter or Receiver */
//#define USE_SCI_IIC01         /*! Using CH1 of SCI0 as IIC Transmitter or Receiver */

/* ToDo: You can only define ONE of the following THREE MACROs according to your application */
//#define USE_SCI_UART1_TX      /*! Using CH0 of SCI1 as UART Transmitter */
//#define USE_SCI_SPI10         /*! Using CH0 of SCI1 as SPI Transmitter or Receiver */
//#define USE_SCI_IIC10         /*! Using CH0 of SCI1 as IIC Transmitter or Receiver */

/* ToDo: You can only define ONE of the following THREE MACROs according to your application */
//#define USE_SCI_UART1_RX      /*! Using CH1 of SCI1 as UART Receiver */
//#define USE_SCI_SPI11         /*! Using CH1 of SCI1 as SPI Transmitter or Receiver */
//#define USE_SCI_IIC11         /*! Using CH1 of SCI1 as IIC Transmitter or Receiver */

/* ToDo: You can only define ONE of the following THREE MACROs according to your application */
//#define USE_SCI_UART2_TX      /*! Using CH0 of SCI2 as UART Transmitter */
//#define USE_SCI_SPI20         /*! Using CH0 of SCI2 as SPI Transmitter or Receiver */
//#define USE_SCI_IIC20         /*! Using CH0 of SCI2 as IIC Transmitter or Receiver */

/* ToDo: You can only define ONE of the following THREE MACROs according to your application */
//#define USE_SCI_UART2_RX      /*! Using CH1 of SCI2 as UART Receiver */
//#define USE_SCI_SPI21         /*! Using CH1 of SCI2 as SPI Transmitter or Receiver */
//#define USE_SCI_IIC21         /*! Using CH1 of SCI2 as IIC Transmitter or Receiver */

/***********************************************************************************************************************
DMA Control Data Set definitions
***********************************************************************************************************************/
#define SPI00_WITH_DMA
#define CTRL_DATA_SPI00 0

//#define SPI01_WITH_DMA
//#define CTRL_DATA_SPI01 2

//#define SPI10_WITH_DMA
//#define CTRL_DATA_SPI10 4

#define SPI11_WITH_DMA
#define CTRL_DATA_SPI11 6

//#define SPI20_WITH_DMA
//#define CTRL_DATA_SPI20 8

//#define SPI21_WITH_DMA
//#define CTRL_DATA_SPI21 10

#define SPIHS0_WITH_DMA
#define CTRL_DATA_SPIHS0 12

#define SPIHS1_WITH_DMA
#define CTRL_DATA_SPIHS1 14

#define ADC_WITH_DMA
#define CTRL_DATA_ADC   16

#define SPI_DMA_CHANNEL 0

#define IISTX_DMA_CHANNEL 2
#define IISRX_DMA_CHANNEL 3

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef enum 
{
    SPI_MODE_0 = 0,  // Mode 0: CPOL = 0, CPHA = 0; i.e. CKP = 1, DAP = 1 
    SPI_MODE_1 = 1,  // Mode 1: CPOL = 0, CPHA = 1; i.e. CKP = 1, DAP = 0 
    SPI_MODE_2 = 2,  // Mode 2: CPOL = 1, CPHA = 0; i.e. CKP = 0, DAP = 1 
    SPI_MODE_3 = 3,  // Mode 3: CPOL = 1, CPHA = 1; i.e. CKP = 0, DAP = 0 
} spi_mode_t;

/** @addtogroup Peripherals_Port_Setting_Definations
  * @{
  */

/* ================================================================================================================== */
/* ================                                       TM40                                       ================ */
/* ================================================================================================================== */
/**
  * @brief TM40 TI00~3 and TO00~3 Port Setting (Alternative to any)
  */

/* ToDo: You can allocate the TI00 to any desired pins with TI10PCFG register */
#define TI00_PORT_SETTING() do{ \
        PORT->TI00PCFG = PTCFG_PC08;/* allocate TI00 to PC08 */ \
        PORT->PMC  |=  (1 << 8);    /* PC08 is used as TI00 input */ \
        PORT->PMCC &= ~(1 << 8);    /* PC08 digital function */ \
}while(0)

#define TI01_PORT_SETTING() do{ \
        PORT->TI01PCFG = PTCFG_PC09;/* allocate TI01 to PC09 */ \
        PORT->PMC  |=  (1 << 9);    /* PC09 is used as TI01 input */ \
        PORT->PMCC &= ~(1 << 9);    /* PC09 digital function */ \
}while(0)

#define TI02_PORT_SETTING() do{ \
        PORT->TI02PCFG = PTCFG_PC10;/* allocate TI02 to PC10 */ \
        PORT->PMC  |=  (1 << 10);   /* PC10 is used as TI02 input */ \
        PORT->PMCC &= ~(1 << 10);   /* PC10 digital function */ \
}while(0)

#define TI03_PORT_SETTING() do{ \
        PORT->TI03PCFG = PTCFG_PC11;/* allocate TI03 to PC11 */ \
        PORT->PMC  |=  (1 << 11);   /* PC11 is used as TI03 input */ \
        PORT->PMCC &= ~(1 << 11);   /* PC11 digital function */ \
}while(0)

#define TO00_PORT_SETTING() do{ \
        PORT->PC08CFG = PTCFG_TO00; /* allocate TO00 to PC08 */ \
        PORT->PCLRC =  (1 << 8);    /* PC08 output low level */ \
        PORT->PMC  &= ~(1 << 8);    /* PC08 is used as TO00 output */ \
        PORT->POMC &= ~(1 << 8);    /* PC08 is normal output mode */ \
        PORT->PMCC &= ~(1 << 8);    /* PC08 digital function */ \
}while(0)

#define TO01_PORT_SETTING() do{ \
        PORT->PC09CFG = PTCFG_TO01; /* allocate TO01 to PC09 */ \
        PORT->PCLRC =  (1 << 9);    /* PC09 output low level */ \
        PORT->PMC  &= ~(1 << 9);    /* PC09 is used as TO00 output */ \
        PORT->POMC &= ~(1 << 9);    /* PC09 is normal output mode */ \
        PORT->PMCC &= ~(1 << 9);    /* PC09 digital function */ \
}while(0)

#define TO02_PORT_SETTING() do{ \
        PORT->PC10CFG = PTCFG_TO02; /* allocate TO02 to PC10 */ \
        PORT->PCLRC =  (1 << 10);   /* PC10 output low level */ \
        PORT->PMC  &= ~(1 << 10);   /* PC10 is used as TO02 output */ \
        PORT->POMC &= ~(1 << 10);   /* PC10 is normal output mode */ \
        PORT->PMCC &= ~(1 << 10);   /* PC10 digital function */ \
}while(0)

#define TO03_PORT_SETTING() do{ \
        PORT->PC11CFG = PTCFG_TO03; /* allocate TO03 to PC11 */ \
        PORT->PCLRC =  (1 << 11);   /* PC11 output low level */ \
        PORT->PMC  &= ~(1 << 11);   /* PC11 is used as TO03 output */ \
        PORT->POMC &= ~(1 << 11);   /* PC11 is normal output mode */ \
        PORT->PMCC &= ~(1 << 11);   /* PC11 digital function */ \
}while(0)

/* ================================================================================================================== */
/* ================                                       TM80                                       ================ */
/* ================================================================================================================== */

/**
  * @brief TM8 TI10~7 and TO10~7 Port Setting 
  */

/* ToDo: You can allocate the TI10 to any desired pins with TI10PCFG register */
#define TI10_PORT_SETTING() do{ \
        PORT->TI10PCFG = PTCFG_PD12; /* allocate TI10 to PD12 */ \
        PORT->PMD  |=  (1 << 12);    /* PD12 is used as TI10 input */ \
        PORT->PMCD &= ~(1 << 12);    /* PD12 digital function */ \
}while(0)

/* ToDo: You can allocate the TI11 to any desired pins with TI11PCFG register */
#define TI11_PORT_SETTING() do{ \
        PORT->TI11PCFG = PTCFG_PD13; /* allocate TI11 to PD13 */ \
        PORT->PMD  |=  (1 << 13);    /* PD13 is used as TI11 input */ \
        PORT->PMCD &= ~(1 << 13);    /* PD13 digital function */ \
}while(0)

/* ToDo: You can allocate the TI12 to any desired pins with TI12PCFG register */
#define TI12_PORT_SETTING() do{ \
        PORT->TI12PCFG = PTCFG_PD14; /* allocate TI12 to PD14 */ \
        PORT->PMD  |=  (1 << 14);    /* PD14 is used as TI12 input */ \
        PORT->PMCD &= ~(1 << 14);    /* PD14 digital function */ \
}while(0)

/* ToDo: You can allocate the TI13 to any desired pins with TI13PCFG register */
#define TI13_PORT_SETTING() do{ \
        PORT->TI13PCFG = PTCFG_PD15; /* allocate TI13 to PD15 */ \
        PORT->PMD  |=  (1 << 15);    /* PD15 is used as TI13 input */ \
        PORT->PMCD &= ~(1 << 15);    /* PD15 digital function */ \
}while(0)

/* ToDo: You can allocate the TO10 to any desired pins with PxxCFG register */
#define TO10_PORT_SETTING() do{ \
        PORT->PD12CFG = PTCFG_TO10;  /* allocate TO10 to PD12 */ \
        PORT->PCLRD =  (1 << 12);    /* PD12 output low level */ \
        PORT->PMD  &= ~(1 << 12);    /* PD12 is used as TO10 output */ \
        PORT->POMD &= ~(1 << 12);    /* PD12 is normal output mode */ \
        PORT->PMCD &= ~(1 << 12);    /* PD12 digital function */ \
}while(0)

/* ToDo: You can allocate the TO11 to any desired pins with PxxCFG register */
#define TO11_PORT_SETTING() do{ \
        PORT->PD13CFG = PTCFG_TO11;  /* allocate TO11 to PD13 */ \
        PORT->PCLRD =  (1 << 13);    /* PD13 output low level */ \
        PORT->PMD  &= ~(1 << 13);    /* PD13 is used as TO11 output */ \
        PORT->POMD &= ~(1 << 13);    /* PD13 is normal output mode */ \
        PORT->PMCD &= ~(1 << 13);    /* PD13 digital function */ \
}while(0)

/* ToDo: You can allocate the TO12 to any desired pins with PxxCFG register */
#define TO12_PORT_SETTING() do{ \
        PORT->PD14CFG = PTCFG_TO12;  /* allocate TO12 to PD14 */ \
        PORT->PCLRD =  (1 << 14);    /* PD14 output low level */ \
        PORT->PMD  &= ~(1 << 14);    /* PD14 is used as TO12 output */ \
        PORT->POMD &= ~(1 << 14);    /* PD14 is normal output mode */ \
        PORT->PMCD &= ~(1 << 14);    /* PD14 digital function */ \
}while(0)

/* ToDo: You can allocate the TO13 to any desired pins with PxxCFG register */
#define TO13_PORT_SETTING() do{ \
        PORT->PD15CFG = PTCFG_TO13;  /* allocate TO13 to PD15 */ \
        PORT->PCLRD =  (1 << 15);    /* PD15 output low level */ \
        PORT->PMD  &= ~(1 << 15);    /* PD15 is used as TO13 output */ \
        PORT->POMD &= ~(1 << 15);    /* PD15 is normal output mode */ \
        PORT->PMCD &= ~(1 << 15);    /* PD15 digital function */ \
}while(0)

/* ToDo: You can allocate the TI14 to any desired pins with TI14PCFG register */
#define TI14_PORT_SETTING() do{ \
        PORT->TI14PCFG = PTCFG_PA11; /* allocate TI10 to PA11 */ \
        PORT->PMA  |=  (1 << 11);    /* PA11 is used as TI14 input */ \
        PORT->PMCA &= ~(1 << 11);    /* PA11 digital function */ \
}while(0)

/* ToDo: You can allocate the TI15 to any desired pins with TI15PCFG register */
#define TI15_PORT_SETTING() do{ \
        PORT->TI15PCFG = PTCFG_PA12; /* allocate TI11 to PA12 */ \
        PORT->PMA  |=  (1 << 12);    /* PA12 is used as TI11 input */ \
        PORT->PMCA &= ~(1 << 12);    /* PA12 digital function */ \
}while(0)

/* ToDo: You can allocate the TI16 to any desired pins with TI16PCFG register */
#define TI16_PORT_SETTING() do{ \
        PORT->TI16PCFG = PTCFG_PA13; /* allocate TI12 to PA13 */ \
        PORT->PMA  |=  (1 << 13);    /* PA13 is used as TI12 input */ \
        PORT->PMCA &= ~(1 << 13);    /* PA13 digital function */ \
}while(0)

/* ToDo: You can allocate the TI17 to any desired pins with TI17PCFG register */
#define TI17_PORT_SETTING() do{ \
        PORT->TI17PCFG = PTCFG_PA14; /* allocate TI13 to PA14 */ \
        PORT->PMA  |=  (1 << 14);    /* PA14 is used as TI13 input */ \
        PORT->PMCA &= ~(1 << 14);    /* PA14 digital function */ \
}while(0)

/* ToDo: You can allocate the TO14 to any desired pins with PxxCFG register */
#define TO14_PORT_SETTING() do{ \
        PORT->PA11CFG = PTCFG_TO14;  /* allocate TO10 to PA11 */ \
        PORT->PCLRA =  (1 << 11);    /* PA11 output low level */ \
        PORT->PMA  &= ~(1 << 11);    /* PA11 is used as TO10 output */ \
        PORT->POMA &= ~(1 << 11);    /* PA11 is normal output mode */ \
        PORT->PMCA &= ~(1 << 11);    /* PA11 digital function */ \
}while(0)

/* ToDo: You can allocate the TO15 to any desired pins with PxxCFG register */
#define TO15_PORT_SETTING() do{ \
        PORT->PA12CFG = PTCFG_TO15;  /* allocate TO11 to PA12 */ \
        PORT->PCLRA =  (1 << 12);    /* PA12 output low level */ \
        PORT->PMA  &= ~(1 << 12);    /* PA12 is used as TO11 output */ \
        PORT->POMA &= ~(1 << 12);    /* PA12 is normal output mode */ \
        PORT->PMCA &= ~(1 << 12);    /* PA12 digital function */ \
}while(0)

/* ToDo: You can allocate the TO16 to any desired pins with PxxCFG register */
#define TO16_PORT_SETTING() do{ \
        PORT->PA13CFG = PTCFG_TO16;  /* allocate TO12 to PA13 */ \
        PORT->PCLRA =  (1 << 13);    /* PA13 output low level */ \
        PORT->PMA  &= ~(1 << 13);    /* PA13 is used as TO12 output */ \
        PORT->POMA &= ~(1 << 13);    /* PA13 is normal output mode */ \
        PORT->PMCA &= ~(1 << 13);    /* PA13 digital function */ \
}while(0)

/* ToDo: You can allocate the TO17 to any desired pins with PxxCFG register */
#define TO17_PORT_SETTING() do{ \
        PORT->PA14CFG = PTCFG_TO17;  /* allocate TO13 to PA14 */ \
        PORT->PCLRA =  (1 << 14);    /* PA14 output low level */ \
        PORT->PMA  &= ~(1 << 14);    /* PA14 is used as TO13 output */ \
        PORT->POMA &= ~(1 << 14);    /* PA14 is normal output mode */ \
        PORT->PMCA &= ~(1 << 14);    /* PA14 digital function */ \
}while(0)

/* ================================================================================================================== */
/* ================                                       EPWM                                       ================ */
/* ================================================================================================================== */

/**
  * @brief EPWM Port Setting（Alternative to fixed port)
  */

/* ToDo: You should modify the defination according to your application */
#define EPWM_PORT_SETTING() do{ \
        EPWMO00_PORT_SETTING(); \
        EPWMO01_PORT_SETTING(); \
        EPWMO02_PORT_SETTING(); \
        EPWMO03_PORT_SETTING(); \
        EPWMO04_PORT_SETTING(); \
        EPWMO05_PORT_SETTING(); \
        EPWMO06_PORT_SETTING(); \
        EPWMO07_PORT_SETTING(); \
}while(0)

#define EPWMO00_PORT_SETTING() do{ \
        PORT->PD04CFG = PTCFG_DFT;  /* PD04 default Alternate function */ \
        PORT->PCLRD =  (1 << 4);    /* PD04 output low level */ \
        PORT->PMD  &= ~(1 << 4);    /* PD04 is used as EPWMO00 output */ \
        PORT->PMCD &= ~(1 << 4);    /* PD04 digital function */ \
}while(0)

#define EPWMO01_PORT_SETTING() do{ \
        PORT->PD05CFG = PTCFG_DFT;  /* PD05 default Alternate function */ \
        PORT->PCLRD =  (1 << 5);    /* PD05 output low level */ \
        PORT->PMD  &= ~(1 << 5);    /* PD05 is used as EPWMO01 output */ \
        PORT->PMCD &= ~(1 << 5);    /* PD05 digital function */ \
}while(0)

#define EPWMO02_PORT_SETTING() do{ \
        PORT->PD06CFG = PTCFG_DFT;  /* PD06 default Alternate function */ \
        PORT->PCLRD =  (1 << 6);    /* PD06 output low level */ \
        PORT->PMD  &= ~(1 << 6);    /* PD06 is used as EPWMO02 output */ \
        PORT->PMCD &= ~(1 << 6);    /* PD06 digital function */ \
}while(0)

#define EPWMO03_PORT_SETTING() do{ \
        PORT->PD07CFG = PTCFG_DFT;  /* PD07 default Alternate function */ \
        PORT->PCLRD =  (1 << 7);    /* PD07 output low level */ \
        PORT->PMD  &= ~(1 << 7);    /* PD07 is used as EPWMO03 output */ \
        PORT->PMCD &= ~(1 << 7);    /* PD07 digital function */ \
}while(0)

#define EPWMO04_PORT_SETTING() do{ \
        PORT->PD08CFG = PTCFG_DFT;  /* PD08 default Alternate function */ \
        PORT->PCLRD =  (1 << 8);    /* PD08 output low level */ \
        PORT->PMD  &= ~(1 << 8);    /* PD08 is used as EPWMO04 output */ \
        PORT->PMCD &= ~(1 << 8);    /* PD08 digital function */ \
}while(0)

#define EPWMO05_PORT_SETTING() do{ \
        PORT->PD09CFG = PTCFG_DFT;  /* PD09 default Alternate function */ \
        PORT->PCLRD =  (1 << 9);    /* PD09 output low level */ \
        PORT->PMD  &= ~(1 << 9);    /* PD09 is used as EPWMO05 output */ \
        PORT->PMCD &= ~(1 << 9);    /* PD09 digital function */ \
}while(0)

#define EPWMO06_PORT_SETTING() do{ \
        PORT->PD10CFG = PTCFG_DFT;   /* PD10 default Alternate function */ \
        PORT->PCLRD =  (1 << 10);    /* PD10 output low level */ \
        PORT->PMD  &= ~(1 << 10);    /* PD10 is used as EPWMO06 output */ \
        PORT->PMCD &= ~(1 << 10);    /* PD10 digital function */ \
}while(0)

#define EPWMO07_PORT_SETTING() do{ \
        PORT->PD11CFG = PTCFG_DFT;   /* PD11 default Alternate function */ \
        PORT->PCLRD =  (1 << 11);    /* PD11 output low level */ \
        PORT->PMD  &= ~(1 << 11);    /* PD11 is used as EPWMO07 output */ \
        PORT->PMCD &= ~(1 << 11);    /* PD11 digital function */ \
}while(0)

/* ================================================================================================================== */
/* ================                                      RTC1HZ                                      ================ */
/* ================================================================================================================== */

/**
  * @brief RTC1HZ Port Setting (Alternative to fixed port)
  */

#define RTC1HZ_PORT_SETTING() do{ \
        PORT->PB00CFG = PTCFG_DFT;  /* PB00 default Alternate function */ \
        PORT->PCLRB =  (1 << 0);    /* PB00 output low level */ \
        PORT->PMB  &= ~(1 << 0);    /* PB00 is used as RTC1HZ output */ \
        PORT->PMCB &= ~(1 << 0);    /* PB00 digital function */ \
}while(0)

/* ================================================================================================================== */
/* ================                                      CLKBUZ                                      ================ */
/* ================================================================================================================== */

/**
  * @brief CLKBUZ0 Port Setting (CLKBUZ0 alternative to fixed port, CLKBUZ1 alternative to any group2 port)
  */

#define CLKBUZ0_PORT_SETTING() do{ \
        PORT->PA00CFG = PTCFG_DFT;  /* allocate CLKBUZ0 to PA00 */ \
        PORT->PCLRA  =  (1 << 0);   /* PA00 output low level */ \
        PORT->PMA   &= ~(1 << 0);   /* PA00 is used as CLKBUZ0 output */ \
        PORT->PMCA  &= ~(1 << 0);   /* PA00 digital function */ \
}while(0)

/* ToDo: You can allocate the CLKBUZ1 to any desired group2 pins with PxxCFG register */
#define CLKBUZ1_PORT_SETTING() do{ \
        PORT->PB06CFG = PTCFG_CLKBUZ1;/* allocate CLKBUZ1 to PB06 */ \
        PORT->PCLRB =  (1 << 6);   /* PB06 output low level */ \
        PORT->PMB   &= ~(1 << 6);   /* PB06 is used as CLKBUZ1 output */ \
        PORT->PMCB  &= ~(1 << 6);   /* PB06 digital function */ \
}while(0)

/* ================================================================================================================== */
/* ================                                        ADC                                       ================ */
/* ================================================================================================================== */

/**
  * @brief ADC Port Setting
  */

/* ToDo: Please comment out the following unused ANIx setting according to your application needs. */
#define ADC_PORT_SETTING() do{ \
        PORT->PMCA |= (1 << 0);   /* Set ANI0(PA00) pin */ \
        PORT->PMCA |= (1 << 1);   /* Set ANI1(PA01) pin */ \
        PORT->PMCA |= (1 << 2);   /* Set ANI2(PA02) pin: It is necessary for ADC_VREF_AVREFP_AVREFM, used as AVREFP */ \
        PORT->PMCA |= (1 << 3);   /* Set ANI3(PA03) pin: It is necessary for ADC_VREF_AVREFP_AVREFM, used as AVREFM */ \
        PORT->PMCA |= (1 << 4);   /* Set ANI4(PA04) pin */ \
        PORT->PMCA |= (1 << 5);   /* Set ANI5(PA05) pin */ \
        PORT->PMCA |= (1 << 6);   /* Set ANI6(PA06) pin */ \
}while(0)

/* ================================================================================================================== */
/* ================                                        CMP                                       ================ */
/* ================================================================================================================== */

/**
  * @brief CMP Port Setting
  */

#define VCOUT0_PORT_SETTING() do { \
        PORT->PMH  &= ~(1 << 1);  /* VCOUT0 output to PH01 */ \
}while(0)

#define VCOUT1_PORT_SETTING() do { \
        PORT->PMH   &= ~(1 << 2);  /* VCOUT1 output to PH02 */ \
}while(0)

/* ToDo: Please comment out the VREF0 setting if don't used VREF0 as negative(-) side input of CMP */
#define CMP0_PORT_SETTING() do{ \
        PORT->PMCA  |= (1 << 4);  /* Set VCIN0(PA04) pin */ \
        PORT->PMCA  |= (1 << 5);  /* Set VREF0(PA05) pin */ \
        VCOUT0_PORT_SETTING();    /* ToDo: Please delete me if you don't output VCOUT0 signal to port */ \
}while(0)

/* ToDo: Please comment out the VCINxx setting if don't used it as positive(+) side input of CMP */
#define CMP1_PORT_SETTING() do{ \
        PORT->PMCA  |= (1 << 0);  /* Set VCIN10(PA00) pin */ \
        PORT->PMCA  |= (1 << 1);  /* Set VCIN11(PA01) pin */ \
        PORT->PMCA  |= (1 << 2);  /* Set VCIN12(PA02) pin */ \
        PORT->PMCA  |= (1 << 3);  /* Set VCIN13(PA03) pin */ \
        VCOUT1_PORT_SETTING();    /* ToDo: Please delete me if you don't output VCOUT1 signal to port */ \
}while(0)

/* ================================================================================================================== */
/* ================                                        PGA                                       ================ */
/* ================================================================================================================== */

/**
  * @brief PGA Port Setting
  */

#define PGA0O_PORT_SETTING() do { \
        PORT->PMCA |= (1 << 3);   /* PGA0O output to PA03 */ \
}while(0)

#define PGA0IN_PORT_SETTING() do { \
        PORT->PMCA |= (1 << 5);  /* PGA0IN input from PA05 */ \
}while(0)

#define PGA0GND_PORT_SETTING() do { \
        PORT->PMCA |= (1 << 6);  /* PGA0GND input from PA06 */ \
}while(0)

/* ================================================================================================================== */
/* ================                                       SCI0                                       ================ */
/* ================================================================================================================== */

/**
  * @brief UART0 Port Setting（Alternative to any group1 port) 
  */

/* ToDo: You can allocate the TXD0 to any desired pins with PxxCFG register */
#if 0
#define TXD0_PORT_SETTING() do{ \
        PORT->PD11CFG = PTCFG_TXD0;  /* allocate TXD0 to PD11 */ \
        PORT->PSETD =  (1 << 11);    /* PD11 output high level */ \
        PORT->PMD  &= ~(1 << 11);    /* PD11 is used as TXD0 output */ \
        PORT->POMD &= ~(1 << 11);    /* PD11 is normal output mode */ \
        PORT->PMCD &= ~(1 << 11);    /* PD11 digital function */ \
}while(0)
#else
#define TXD0_PORT_SETTING() do{ \
        PORT->PD08CFG = PTCFG_TXD0;  /* allocate TXD0 to PD08 */ \
        PORT->PSETD =  (1 << 8);    /* PD11 output high level */ \
        PORT->PMD  &= ~(1 << 8);    /* PD11 is used as TXD0 output */ \
        PORT->POMD &= ~(1 << 8);    /* PD11 is normal output mode */ \
        PORT->PMCD &= ~(1 << 8);    /* PD11 digital function */ \
}while(0)

#endif 

/* ToDo: You can allocate the RXD0 to any desired pins with RXD0PCFG register */
#if 0
#define RXD0_PORT_SETTING() do{ \
        PORT->RXD0PCFG = PTCFG_PD10;/* allocate RXD0 to PD10 */ \
        PORT->PMD  |=  (1 << 10);   /* PD10 is used as RXD0 input */ \
        PORT->PMCD &= ~(1 << 10);   /* PD10 digital function */ \
}while(0)
#else
#define RXD0_PORT_SETTING() do{ \
        PORT->RXD0PCFG = PTCFG_PD07;/* allocate RXD0 to PD07 */ \
        PORT->PMD  |=  (1 << 7);   /* PD10 is used as RXD0 input */ \
        PORT->PMCD &= ~(1 << 7);   /* PD10 digital function */ \
}while(0)

#endif 
/**
  * @brief SPI00 Port Setting（Alternative to any port)
  */

/* ToDo: You can allocate the SS00 to any desired pins with SS00PCFG register */
#define SS00_PORT_SETTING() //do{ \
        PORT->SS00PCFG = 0x1B;       /* allocate SS00 to P62 */ \
        PORT->PM6  |=  (1 << 2);     /* P62 is used as SS00 input */ \
        PORT->PU6  |=  (1 << 2);     /* P62 pull up resistor enable */ \
        PORT->PMC6 &= ~(1 << 2);     /* P62 digital function */ \
}while(0)

/* ToDo: You can allocate the SS00 to any desired pins */
#define SS00_PORT_SET() //do{ \
        PORT->PSET6 = (1 << 2);      /* P62 output high level */ \
}while(0)

/* ToDo: You can allocate the SS00 to any desired pins */
#define SS00_PORT_CLR() //do{ \
        PORT->PCLR6 = (1 << 2);      /* P62 output low level */ \
}while(0)

/* ToDo: You can allocate the SCLKI00 to any desired pins with SCLKI00PCFG register (Alternative to fixed port)  */
#define SCLKI00_PORT_SETTING() do{ \
        PORT->PMA  |=  (1 << 1);     /* PA11 is used as SCLK00 input */ \
        PORT->PMCA &= ~(1 << 1);     /* PA11 digital function */ \
}while(0)

/* ToDo: You can allocate the SCLKO00 to any desired pins with PxxCFG register (Alternative to fixed port) */ 
#define SCLKO00_PORT_SETTING() do{ \
        PORT->PA11CFG = PTCFG_DFT;  /* allocate SCLKO00 to PA11 */ \
        PORT->PSETA =  (1 << 1);    /* PA11 output high level */ \
        PORT->PMA  &= ~(1 << 1);    /* PA11 is used as SCLK00 output */ \
        PORT->POMA &= ~(1 << 1);    /* PA11 is normal output mode */ \
        PORT->PMCA &= ~(1 << 1);    /* PA11 digital function */ \
}while(0)

/* ToDo: You can allocate the SDO00 to any desired pins with PxxCFG register */
#define SDO00_PORT_SETTING() do{ \
        PORT->PD10CFG = PTCFG_SDO00;  /* allocate SDO00 to PD10 */ \
        PORT->PSETD =  (1 << 10);    /* PD10 output high level */ \
        PORT->PMD  &= ~(1 << 10);    /* PD10 is used as TXD0 output */ \
        PORT->POMD &= ~(1 << 10);    /* PD10 is normal output mode */ \
        PORT->PMCD &= ~(1 << 10);    /* PD10 digital function */ \
}while(0)

/* ToDo: You can allocate the SDI00 to any desired pins with SDI00PCFG register */
#define SDI00_PORT_SETTING() do{ \
        PORT->SDI00PCFG = PTCFG_PD11;/* allocate SDI00 to PD11 */ \
        PORT->PMD  |=  (1 << 11);   /* PD11 is used as RXD0 input */ \
        PORT->PMCD &= ~(1 << 11);   /* PD11 digital function */ \
}while(0)

/**
  * @brief IIC00 Port Setting（Alternative to any port)
  */

/* ToDo: You can allocate the SCL00 to any desired pins with PxxCFG register */
#define SCL00_PORT_SETTING() //do{ \
        PORT->P30CFG = 0x08;        /* allocate SCL00 to P30 */ \
        PORT->PSET3 =  (1 << 0);    /* P30 output high level */ \
        PORT->PM3  &= ~(1 << 0);    /* P30 is used as SCL00 output */ \
        PORT->POM3 |=  (1 << 0);    /* P30 is N-ch open-drain output mode */ \
        PORT->PMC3 &= ~(1 << 0);    /* P30 digital function */ \
}while(0)

/* ToDo: You can allocate the SDA00 to any desired pins with SDA00PCFG register */
#define SDA00_PORT_SETTING() //do{ \
        PORT->SDA00PCFG = 0x17;     /* allocate SDA00 to P50 */ \
        PORT->PSET5 =  (1 << 0);    /* P50 output high level */ \
        PORT->PM5  &= ~(1 << 0);    /* P50 is used as SDA00 inout */ \
        PORT->POM5 |=  (1 << 0);    /* P50 is N-ch open-drain output mode */ \
        PORT->PMC5 &= ~(1 << 0);    /* P50 digital function */ \
}while(0)

/**
  * @brief SPI01 Port Setting (Alternative to fixed port)
  */

/* ToDo: You can allocate the SS01 to any desired pins */
#define SS01_PORT_SETTING() //do{ \
        PORT->P62CFG = 0x00;         /* P62 default GPIO function */ \
        PORT->PSET6 =  (1 << 2);     /* P62 output high level */ \
        PORT->PM6  &= ~(1 << 2);     /* P62 is used as SS01 output */ \
        PORT->PMC6 &= ~(1 << 2);     /* P62 digital function */ \
}while(0)

/* ToDo: You can allocate the SS01 to any desired pins */
#define SS01_PORT_SET() //do{ \
        PORT->PSET6 = (1 << 2);      /* P62 output high level */ \
}while(0)

/* ToDo: You can allocate the SS01 to any desired pins */
#define SS01_PORT_CLR() //do{ \
        PORT->PCLR6 = (1 << 2);      /* P62 output low level */ \
}while(0)

#define SCLKI01_PORT_SETTING() do{ \
        PORT->PA14CFG = PTCFG_DFT;   /* PA14 default Alternate function */ \
        PORT->PMA  |=  (1 << 14);    /* PA14 is used as SCLK00 input */ \
        PORT->PMCA &= ~(1 << 14);    /* PA14 digital function */ \
}while(0)

#define SCLKO01_PORT_SETTING() do{ \
        PORT->PA14CFG = PTCFG_DFT;   /* PA14 default Alternate function */ \
        PORT->PSETA =  (1 << 14);    /* PA14 output high level */ \
        PORT->PMA  &= ~(1 << 14);    /* PA14 is used as SCLK00 output */ \
        PORT->POMA &= ~(1 << 14);    /* PA14 is normal output mode */ \
        PORT->PMCA &= ~(1 << 14);    /* PA14 digital function */ \
}while(0)

#define SDO01_PORT_SETTING() do{ \
        PORT->PA12CFG = PTCFG_DFT;   /* PA12 default Alternate function */ \
        PORT->PSETA =  (1 << 12);    /* PA12 output high level */ \
        PORT->PMA  &= ~(1 << 12);    /* PA12 is used as SDO01 output */ \
        PORT->POMA &= ~(1 << 12);    /* PA12 is normal output mode */ \
        PORT->PMCA &= ~(1 << 12);    /* PA12 digital function */ \
}while(0)

#define SDI01_PORT_SETTING() do{ \
        PORT->PA13CFG = PTCFG_DFT;   /* PA13 default Alternate function */ \
        PORT->PMA  |=  (1 << 13);    /* PA13 is used as SDI01 input */ \
        PORT->PMCA &= ~(1 << 13);    /* PA13 digital function */ \
}while(0)

/**
  * @brief IIC01 Port Setting (Alternative to fixed port)
  */

#define SCL01_PORT_SETTING() do{ \
        PORT->PA14CFG = PTCFG_DFT;   /* PA14 default Alternate function */ \
        PORT->PSETA =  (1 << 14);    /* PA14 output high level */ \
        PORT->PMA  &= ~(1 << 14);    /* PA14 is used as SCL01 output */ \
        PORT->POMA |=  (1 << 14);    /* PA14 is N-ch open-drain output mode */ \
        PORT->PMCA &= ~(1 << 14);    /* PA14 digital function */ \
}while(0)

#define SDA01_PORT_SETTING() do{ \
        PORT->PA13CFG = PTCFG_DFT;   /* PA13 default Alternate function */ \
        PORT->PSETA =  (1 << 13);    /* PA13 output high level */ \
        PORT->PMA  &= ~(1 << 13);    /* PA13 is used as SDA01 inout */ \
        PORT->POMA |=  (1 << 13);    /* PA13 is N-ch open-drain output mode */ \
        PORT->PMCA &= ~(1 << 13);    /* PA13 digital function */ \
}while(0)

/* ================================================================================================================== */
/* ================                                       SCI1                                       ================ */
/* ================================================================================================================== */

/**
  * @brief UART1 Port Setting (Alternative to any port)
  */

/* ToDo: You can allocate the TXD1 to any desired pins with PxxCFG register */
#define TXD1_PORT_SETTING() do{ \
        PORT->PC06CFG = PTCFG_TXD1; /* allocate TXD1 to PC06 */ \
        PORT->PSETC =  (1 << 6);    /* PC06 output high level */ \
        PORT->PMC  &= ~(1 << 6);    /* PC06 is used as TXD1 output */ \
        PORT->POMC &= ~(1 << 6);    /* PC06 is normal output mode */ \
        PORT->PMCC &= ~(1 << 6);    /* PC06 digital function */ \
}while(0)

/* ToDo: You can allocate the RXD1 to any desired pins with RXD1PCFG register */
#define RXD1_PORT_SETTING() do{ \
        PORT->RXD1PCFG = PTCFG_PC07;/* allocate RXD1 to PC07 */ \
        PORT->PMC  |=  (1 << 7);    /* PC07 is used as RXD1 input */ \
        PORT->PMCC &= ~(1 << 7);    /* PC07 digital function */ \
}while(0)

/**
  * @brief SPI10 Port Setting (SCLK10 alternative to fixed port, SDI10/SDO10 alternative to any port)
  */

/* ToDo: You can allocate the SS10 to any desired pins */
#define SS10_PORT_SETTING() //do{ \
        PORT->P62CFG = 0x00;         /* P62 default GPIO function */ \
        PORT->PSET6 =  (1 << 2);     /* P62 output high level */ \
        PORT->PM6  &= ~(1 << 2);     /* P62 is used as SS10 output */ \
        PORT->PMC6 &= ~(1 << 2);     /* P62 digital function */ \
}while(0)

/* ToDo: You can allocate the SS10 to any desired pins */
#define SS10_PORT_SET() //do{ \
        PORT->PSET6 =  (1 << 2);      /* P62 output high level */ \
}while(0)

/* ToDo: You can allocate the SS10 to any desired pins */
#define SS10_PORT_CLR() //do{ \
        PORT->PCLR6 = (1 << 2);      /* P62 output low level */ \
}while(0)

#define SCLKI10_PORT_SETTING() do{ \
        PORT->PA10CFG = PTCFG_DFT;   /* PA10 default Alternate function */ \
        PORT->PMA  |=  (1 << 10);   /* PA10 is used as SCLK10 input */ \
        PORT->PMCA &= ~(1 << 10);   /* PA10 digital function */ \
}while(0)

#define SCLKO10_PORT_SETTING() do{ \
        PORT->PA10CFG = PTCFG_DFT;   /* PA10 default Alternate function */ \
        PORT->PSETA =  (1 << 10);   /* PA10 output high level */ \
        PORT->PMA  &= ~(1 << 10);   /* PA10 is used as SCLK10 output */ \
        PORT->POMA &= ~(1 << 10);   /* PA10 is normal output mode */ \
        PORT->PMCA &= ~(1 << 10);   /* PA10 digital function */ \
}while(0)

/* ToDo: You can allocate the SDO10 to any desired pins with PxxCFG register */
#define SDO10_PORT_SETTING() //do{ \
        PORT->P00CFG = 0x0A;        /* allocate SDO10 to P00 */ \
        PORT->PSET0 =  (1 << 0);    /* P00 output high level */ \
        PORT->PM0  &= ~(1 << 0);    /* P00 is used as SDO10 output */ \
        PORT->POM0 &= ~(1 << 0);    /* P00 is normal output mode */ \
        PORT->PMC0 &= ~(1 << 0);    /* P00 digital function */ \
}while(0)

/* ToDo: You can allocate the SDI10 to any desired pins with SDI10PCFG register */
#define SDI10_PORT_SETTING() //do{ \
        PORT->SDI10PCFG = 0x02;     /* allocate SDI10 to P01 */ \
        PORT->PM0  |=  (1 << 1);    /* P01 is used as SDI10 input */ \
        PORT->PMC0 &= ~(1 << 1);    /* P01 digital function */ \
}while(0)

/**
  * @brief IIC10 Port Setting (SCL10 alternative to fixed port, SDA10 alternative to any port)
  */

#define SCL10_PORT_SETTING() //do{ \
        PORT->P130CFG = 0x00;       /* P130 default Alternate function */ \
        PORT->P13   |=  (1 << 0);   /* P130 output  */ \
        PORT->PM13  &= ~(1 << 0);   /* P130 is used as SCL10 output */ \
        PORT->POM13 |=  (1 << 0);   /* P130 is N-ch open-drain output mode */ \
        PORT->PMC13 &= ~(1 << 0);   /* P130 digital function */ \
}while(0)

/* ToDo: You can allocate the SDA10 to any desired pins with SDA10PCFG register */
#define SDA10_PORT_SETTING() //do{ \
        PORT->SDA10PCFG = 0x02;     /* allocate SDA10 to P01 */ \
        PORT->PSET0 =  (1 << 1);    /* P01 output high level */ \
        PORT->PM0  &= ~(1 << 1);    /* P01 is used as SDA10 inout */ \
        PORT->POM0 |=  (1 << 1);    /* P01 is N-ch open-drain output mode */ \
        PORT->PMC0 &= ~(1 << 1);    /* P01 digital function */ \
}while(0)

/**
  * @brief SPI11 Port Setting (Alternative to fixed port)
  */

/* ToDo: You can allocate the SS11 to any desired pins */
#define SS11_PORT_SETTING() //do{ \
        PORT->P62CFG = 0x00;         /* P62 default GPIO function */ \
        PORT->PSET6 =  (1 << 2);     /* P62 output high level */ \
        PORT->PM6  &= ~(1 << 2);     /* P62 is used as SS11 output */ \
        PORT->PMC6 &= ~(1 << 2);     /* P62 digital function */ \
}while(0)

/* ToDo: You can allocate the SS11 to any desired pins */
#define SS11_PORT_SET() //do{ \
        PORT->PSET6 =  (1 << 2);     /* P62 output high level */ \
}while(0)

/* ToDo: You can allocate the SS11 to any desired pins */
#define SS11_PORT_CLR() //do{ \
        PORT->PCLR6 = (1 << 2);      /* P62 output low level */ \
}while(0)

#define SCLKI11_PORT_SETTING() do{ \
        PORT->PC03CFG = PTCFG_DFT;   /* PC03 default Alternate function */ \
        PORT->PMC  |=  (1 << 3);     /* PC03 is used as SCLK11 input */ \
        PORT->PMCC &= ~(1 << 3);     /* PC03 digital function */ \
}while(0)

#define SCLKO11_PORT_SETTING() do{ \
        PORT->PC03CFG = PTCFG_DFT;   /* PC03 default Alternate function */ \
        PORT->PSETC =  (1 << 3);     /* PC03 output high level */ \
        PORT->PMC  &= ~(1 << 3);     /* PC03 is used as SCLK11 output */ \
        PORT->POMC &= ~(1 << 3);     /* PC03 is normal output mode */ \
        PORT->PMCC &= ~(1 << 3);     /* PC03 digital function */ \
}while(0)

#define SDO11_PORT_SETTING() do{ \
        PORT->PC04CFG = PTCFG_DFT;   /* PC04 default Alternate function */ \
        PORT->PSETC =  (1 << 4);     /* PC04 output high level */ \
        PORT->PMC  &= ~(1 << 4);     /* PC04 is used as SDO11 output */ \
        PORT->POMC &= ~(1 << 4);     /* PC04 is normal output mode */ \
        PORT->PMCC &= ~(1 << 4);     /* PC04 digital function */ \
}while(0)

#define SDI11_PORT_SETTING() do{ \
        PORT->PC05CFG = PTCFG_DFT;   /* PC05 default Alternate function */ \
        PORT->PMC  |=  (1 << 5);     /* PC05 is used as SDI11 input */ \
        PORT->PMCC &= ~(1 << 5);     /* PC05 digital function */ \
}while(0)

/**
  * @brief IIC11 Port Setting (Alternative to fixed port)
  */

#define SCL11_PORT_SETTING() do{ \
        PORT->PC03CFG = PTCFG_DFT;   /* PC03 default Alternate function */ \
        PORT->PSETC =  (1 << 3);     /* PC03 output high level */ \
        PORT->PMC  &= ~(1 << 3);     /* PC03 is used as SCL11 output */ \
        PORT->POMC |=  (1 << 3);     /* PC03 is N-ch open-drain output mode */ \
        PORT->PMCC &= ~(1 << 3);     /* PC03 digital function */ \
}while(0)

#define SDA11_PORT_SETTING() do{ \
        PORT->PC05CFG = PTCFG_DFT;   /* PC05 default Alternate function */ \
        PORT->PSETC =  (1 << 5);     /* PC05 output high level */ \
        PORT->PMC  &= ~(1 << 5);     /* PC05 is used as SDA11 inout */ \
        PORT->POMC |=  (1 << 5);     /* PC05 is N-ch open-drain output mode */ \
        PORT->PMCC &= ~(1 << 5);     /* PC05 digital function */ \
}while(0)

/* ================================================================================================================== */
/* ================                                       SCI2                                       ================ */
/* ================================================================================================================== */

/**
  * @brief UART2 Port Setting（Alternative to any port) 
  */

/* ToDo: You can allocate the TXD2 to any desired pins with PxxCFG register */
#define TXD2_PORT_SETTING() do{ \
        PORT->PB05CFG = PTCFG_TXD2;   /* allocate TXD2 to PB05 */ \
        PORT->PSETB =  (1 << 5);    /* PB05 output high level */ \
        PORT->PMB  &= ~(1 << 5);    /* PB05 is used as TXD2 output */ \
        PORT->POMB &= ~(1 << 5);    /* PB05 is normal output mode */ \
        PORT->PMCB &= ~(1 << 5);    /* PB05 digital function */ \
}while(0)

/* ToDo: You can allocate the RXD2 to any desired pins with RXD2PCFG register */
#define RXD2_PORT_SETTING() do{ \
        PORT->RXD2PCFG = PTCFG_PB04;/* allocate RXD2 to PB04 */ \
        PORT->PMB  |=  (1 << 4);    /* PB04 is used as RXD2 input */ \
        PORT->PMCB &= ~(1 << 4);    /* PB04 digital function */ \
}while(0)

/**
  * @brief SPI20 Port Setting（Alternative to any port)
  */

/* ToDo: You can allocate the SS20 to any desired pins */
#define SS20_PORT_SETTING() //do{ \
        PORT->P63CFG = 0x00;         /* P63 default GPIO function */ \
        PORT->PSET6 =  (1 << 3);     /* P63 output high level */ \
        PORT->PM6  &= ~(1 << 3);     /* P63 is used as SS20 output */ \
        PORT->PMC6 &= ~(1 << 3);     /* P63 digital function */ \
}while(0)

/* ToDo: You can allocate the SS20 to any desired pins */
#define SS20_PORT_SET() //do{ \
        PORT->PSET6 = (1 << 3);      /* P63 output high level */ \
}while(0)

/* ToDo: You can allocate the SS20 to any desired pins */
#define SS20_PORT_CLR() //do{ \
        PORT->PCLR6 = (1 << 3);      /* P63 output low level */ \
}while(0)

/* ToDo: You can allocate the SCLKI20 to any desired pins with SCLKI20PCFG register */
#define SCLKI20_PORT_SETTING() //do{ \
        PORT->SCLKI20PCFG = 0x08;    /* allocate SCLK20 to P15 */ \
        PORT->PM1  |=  (1 << 5);     /* P15 is used as SCLK20 input */ \
        PORT->PMC1 &= ~(1 << 5);     /* P15 digital function */ \
}while(0)

/* ToDo: You can allocate the SCLKO20 to any desired pins with PxxCFG register */
#define SCLKO20_PORT_SETTING() //do{ \
        PORT->P15CFG = 0x09;        /* allocate SCLK20 to P15 */ \
        PORT->PSET1 =  (1 << 5);    /* P15 output high level */ \
        PORT->PM1  &= ~(1 << 5);    /* P15 is used as SCLK20 output */ \
        PORT->POM1 &= ~(1 << 5);    /* P15 is normal output mode */ \
        PORT->PMC1 &= ~(1 << 5);    /* P15 digital function */ \
}while(0)

/* ToDo: You can allocate the SDO20 to any desired pins with PxxCFG register */
#define SDO20_PORT_SETTING() //do{ \
        PORT->P13CFG = 0x06;        /* allocate SDO20 to P13 */ \
        PORT->PSET1 =  (1 << 3);    /* P13 output high level */ \
        PORT->PM1  &= ~(1 << 3);    /* P13 is used as SDO20 output */ \
        PORT->POM1 &= ~(1 << 3);    /* P13 is normal output mode */ \
        PORT->PMC1 &= ~(1 << 3);    /* P13 digital function */ \
}while(0)

/* ToDo: You can allocate the SDI20 to any desired pins with SDI20PCFG register */
#define SDI20_PORT_SETTING() //do{ \
        PORT->SDI20PCFG = 0x07;     /* allocate SDI20 to P14 */ \
        PORT->PM1  |=  (1 << 4);    /* P14 is used as SDI20 input */ \
        PORT->PMC1 &= ~(1 << 4);    /* P14 digital function */ \
}while(0)

/**
  * @brief IIC20 Port Setting（SCL20 alternative to any port, SDA20 alternative to fixed port)
  */

/* ToDo: You can allocate the SCL20 to any desired pins with PxxCFG register */
#define SCL20_PORT_SETTING() //do{ \
        PORT->P15CFG = 0x09;        /* allocate SCL20 to P15 */ \
        PORT->PSET1 =  (1 << 5);    /* P15 output high level */ \
        PORT->PM1  &= ~(1 << 5);    /* P15 is used as SCL20 output */ \
        PORT->POM1 |=  (1 << 5);    /* P15 is N-ch open-drain output mode */ \
        PORT->PMC1 &= ~(1 << 5);    /* P15 digital function */ \
}while(0)

#define SDA20_PORT_SETTING() //do{ \
        PORT->P14CFG = 0x00;        /* allocate SDA20 to P14 */ \
        PORT->PSET1 =  (1 << 4);    /* P14 output high level */ \
        PORT->PM1  &= ~(1 << 4);    /* P14 is used as SDA20 inout */ \
        PORT->POM1 |=  (1 << 4);    /* P14 is N-ch open-drain output mode */ \
        PORT->PMC1 &= ~(1 << 4);    /* P14 digital function */ \
}while(0)

/**
  * @brief SPI21 Port Setting (Alternative to fixed port)
  */

/* ToDo: You can allocate the SS21 to any desired pins */
#define SS21_PORT_SETTING() //do{ \
        PORT->P63CFG = 0x00;         /* P63 default GPIO function */ \
        PORT->PSET6 =  (1 << 3);     /* P63 output high level */ \
        PORT->PM6  &= ~(1 << 3);     /* P63 is used as SS21 output */ \
        PORT->PMC6 &= ~(1 << 3);     /* P63 digital function */ \
}while(0)

/* ToDo: You can allocate the SS21 to any desired pins */
#define SS21_PORT_SET() //do{ \
        PORT->PSET6 = (1 << 3);      /* P63 output high level */ \
}while(0)

/* ToDo: You can allocate the SS21 to any desired pins */
#define SS21_PORT_CLR() //do{ \
        PORT->PCLR6 = (1 << 3);      /* P63 output low level */ \
}while(0)

#define SCLKI21_PORT_SETTING() do{ \
        PORT->PB03CFG = PTCFG_DFT;   /* PB03 default Alternate function */ \
        PORT->PMB  |=  (1 << 3);    /* PB03 is used as SCLK21 input */ \
        PORT->PMCB &= ~(1 << 3);    /* PB03 digital function */ \
}while(0)

#define SCLKO21_PORT_SETTING() do{ \
        PORT->PB03CFG = PTCFG_DFT;   /* PB03 default Alternate function */ \
        PORT->PSETB =  (1 << 3);    /* PB03 output high level */ \
        PORT->PMB  &= ~(1 << 3);    /* PB03 is used as SCLK21 output */ \
        PORT->POMB &= ~(1 << 3);    /* PB03 is normal output mode */ \
        PORT->PMCB &= ~(1 << 3);    /* PB03 digital function */ \
}while(0)

#define SDO21_PORT_SETTING() do{ \
        PORT->PB05CFG = PTCFG_DFT;   /* PB05 default Alternate function */ \
        PORT->PSETB =  (1 << 5);    /* PB05 output high level */ \
        PORT->PMB  &= ~(1 << 5);    /* PB05 is used as SDO21 output */ \
        PORT->POMB &= ~(1 << 5);    /* PB05 is normal output mode */ \
        PORT->PMCB &= ~(1 << 5);    /* PB05 digital function */ \
}while(0)

#define SDI21_PORT_SETTING() do{ \
        PORT->PB04CFG = PTCFG_DFT;   /* PB04 default Alternate function */ \
        PORT->PMB  |=  (1 << 4);    /* PB04 is used as SDI21 input */ \
        PORT->PMCB &= ~(1 << 4);    /* PB04 digital function */ \
}while(0)

/**
  * @brief IIC21 Port Setting (Alternative to fixed port)
  */

#define SCL21_PORT_SETTING() do{ \
        PORT->PB03CFG = PTCFG_DFT;   /* PB03 default Alternate function */ \
        PORT->PSETB =  (1 << 3);    /* PB03 output high level */ \
        PORT->PMB  &= ~(1 << 3);    /* PB03 is used as SCL21 output */ \
        PORT->POMB |=  (1 << 3);    /* PB03 is N-ch open-drain output mode */ \
        PORT->PMCB &= ~(1 << 3);    /* PB03 digital function */ \
}while(0)

#define SDA21_PORT_SETTING() do{ \
        PORT->PB04CFG = PTCFG_DFT;   /* PB04 default Alternate function */ \
        PORT->PSETB =  (1 << 4);    /* PB04 output high level */ \
        PORT->PMB  &= ~(1 << 4);    /* PB04 is used as SDA21 inout */ \
        PORT->POMB |=  (1 << 4);    /* PB04 is N-ch open-drain output mode */ \
        PORT->PMCB &= ~(1 << 4);    /* PB04 digital function */ \
}while(0)

/* ================================================================================================================== */
/* ================                                       SPI                                        ================ */
/* ================================================================================================================== */

/**
  * @brief SPI Port Setting（Alternative to three group port)
  */

/* ToDo: Please define one of the following macro and comment out others accroding to your application */
#define SPIHS0_SLAVE_PORT
//#define SPIHS0_MASTER_PORT
//#define SPIHS1_SLAVE_PORT
#define SPIHS1_MASTER_PORT

#ifdef SPIHS0_SLAVE_PORT
#define NSS0_PORT_SETTING() do{ \
        PORT->PMC  |=  (1 << 6);    /* PC06 is used as NSS0 input */ \
        PORT->PMCC &= ~(1 << 6);    /* PC06 digital function */ \
}while(0)

#define NSS0_PORT_SET() do{ \
        __NOP(); \
}while(0)

#define NSS0_PORT_CLR() do{ \
        __NOP(); \
}while(0)

#define SCK0_PORT_SETTING() do{ \
        PORT->SPIHS0_SCKIPCFG = PTCFG_PC03; /* SCK0 alternate to PC03 */ \
        PORT->PMC  |=  (1 << 3);      /* PC03 is used as SCK0 input */ \
        PORT->PMCC &= ~(1 << 3);      /* PC03 digital function */ \
}while(0)

#define MOSI0_PORT_SETTING() do{ \
        PORT->SPIHS0_SIPCFG = PTCFG_PC04; /* MOSI0 alternate to PC04 */ \
        PORT->PMC  |=  (1 << 4);    /* PC04 is used as MOSI input */ \
        PORT->PMCC &= ~(1 << 4);    /* PC04 digital function */ \
}while(0)

#define MISO0_PORT_SETTING() do{ \
        PORT->PC05CFG = PTCFG_SPIHS0_SO;  /* MISO0 alternate to PC05 */ \
        PORT->PCLRC =  (1 << 5);    /* PC05 output low level */ \
        PORT->PMC  &= ~(1 << 5);    /* PC05 is used as MISO output */ \
        PORT->POMC &= ~(1 << 5);    /* PC05 is normal output mode */ \
        PORT->PMCC &= ~(1 << 5);    /* PC05 digital function */ \
}while(0)
#endif

#ifdef SPIHS0_MASTER_PORT
#define NSS0_PORT_SETTING() do{ \
        PORT->PSETC =  (1 << 6);    /* PC06 output high level */ \
        PORT->PMC  &= ~(1 << 6);    /* PC06 is used as NSS0 output */ \
        PORT->PMCC &= ~(1 << 6);    /* PC06 digital function */ \
}while(0)

#define NSS0_PORT_SET() do{ \
        PORT->PSETC =  (1 << 6);    /* PC06 output high level */ \
}while(0)

#define NSS0_PORT_CLR() do{ \
        PORT->PCLRC =  (1 << 6);    /* PC06 output low level */ \
}while(0)

#define SCK0_PORT_SETTING() do{ \
        PORT->PC03CFG = PTCFG_SPIHS0_SCKO; /* SCK0 alternate to PC03 */ \
        PORT->PCLRC =  (1 << 3);    /* PC03 output low level */ \
        PORT->PMC  &= ~(1 << 3);    /* PC03 is used as SCK output */ \
        PORT->POMC &= ~(1 << 3);    /* PC03 is normal output mode */ \
        PORT->PMCC &= ~(1 << 3);    /* PC03 digital function */ \
}while(0)

#define MOSI0_PORT_SETTING() do{ \
        PORT->PC04CFG = PTCFG_SPIHS0_MO; /* MOSI0 alternate to PC04 */ \
        PORT->PCLRC =  (1 << 4);    /* PC04 output low level */ \
        PORT->PMC  &= ~(1 << 4);    /* PC04 is used as MOSI output */ \
        PORT->POMC &= ~(1 << 4);    /* PC04 is normal output mode */ \
        PORT->PMCC &= ~(1 << 4);    /* PC04 digital function */ \
}while(0)

#define MISO0_PORT_SETTING() do{ \
        PORT->SPIHS0_MICFG = PTCFG_PC05;  /* MISO0 alternate to PC05 */ \
        PORT->PMC  |=  (1 << 5);    /* PC05 is used as MISO input */ \
        PORT->PMCC &= ~(1 << 5);    /* PC05 digital function */ \
}while(0)
#endif

#ifdef SPIHS1_SLAVE_PORT
#define NSS1_PORT_SETTING() do{ \
        PORT->SPIHS1_NSSPCFG  = PTCFG_PB06;  /* PB06 is used as NSS1 input */ \
        PORT->PMB  |=  (1 << 6);    /* PB06 is used as NSS1 input */ \
        PORT->PMCB &= ~(1 << 6);    /* PB06 digital function */ \
}while(0)

#define NSS1_PORT_SET() do{ \
        __NOP(); \
}while(0)

#define NSS1_PORT_CLR() do{ \
        __NOP(); \
}while(0)

#define SCK1_PORT_SETTING() do{ \
        PORT->PMC  |=  (1 << 0);    /* PC00 is used as SCK input */ \
        PORT->PMCC &= ~(1 << 0);    /* PC00 digital function */ \
}while(0)

#define MOSI1_PORT_SETTING() do{ \
        PORT->PMC  |=  (1 << 1);    /* PC01 is used as MOSI input */ \
        PORT->PMCC &= ~(1 << 1);    /* PC01 digital function */ \
}while(0)

#define MISO1_PORT_SETTING() do{ \
        PORT->PCLRC =  (1 << 2);    /* PC02 output low level */ \
        PORT->PMC  &= ~(1 << 2);    /* PC02 is used as MISO output */ \
        PORT->POMC &= ~(1 << 2);    /* PC02 is normal output mode */ \
        PORT->PMCC &= ~(1 << 2);    /* PC02 digital function */ \
}while(0)
#endif

#ifdef SPIHS1_MASTER_PORT
#define NSS1_PORT_SETTING() do{ \
        PORT->PSETB =  (1 << 6);    /* PB06 output high level */ \
        PORT->PMB  &= ~(1 << 6);    /* PB06 is used as NSS output */ \
        PORT->PMCB &= ~(1 << 6);    /* PB06 digital function */ \
}while(0)

#define NSS1_PORT_SET() do{ \
        PORT->PSETB =  (1 << 6);    /* PB06 output high level */ \
}while(0)

#define NSS1_PORT_CLR() do{ \
        PORT->PCLRB =  (1 << 6);    /* PB06 output low level */ \
}while(0)

#define SCK1_PORT_SETTING() do{ \
        PORT->PCLRC =  (1 << 0);    /* PC00 output low level */ \
        PORT->PMC  &= ~(1 << 0);    /* PC00 is used as SCK1 output */ \
        PORT->POMC &= ~(1 << 0);    /* PC00 is normal output mode */ \
        PORT->PMCC &= ~(1 << 0);    /* PC00 digital function */ \
}while(0)

#define MOSI1_PORT_SETTING() do{ \
        PORT->PCLRC =  (1 << 1);    /* PC01 output low level */ \
        PORT->PMC  &= ~(1 << 1);    /* PC01 is used as MOSI1 output */ \
        PORT->POMC &= ~(1 << 1);    /* PC01 is normal output mode */ \
        PORT->PMCC &= ~(1 << 1);    /* PC01 digital function */ \
}while(0)

#define MISO1_PORT_SETTING() do{ \
        PORT->PMC  |=  (1 << 2);    /* PC02 is used as MISO1 input */ \
        PORT->PMCC &= ~(1 << 2);    /* PC02 digital function */ \
}while(0)
#endif

/* ================================================================================================================== */
/* ================                                       IICA                                       ================ */
/* ================================================================================================================== */

/**
  * @brief IICA0 Port Setting（Alternative to any group0 port)
  */

/* ToDo: You can allocate the SCLA0 to any desired pins with SCLA0PCFG register */
#define SCLA0_PORT_SETTING() do{ \
        PORT->SCLA0PCFG = PTCFG_PD08;/* allocate SCLA0 to PD08 */ \
        PORT->PCLRD =  (1 << 8);    /* PD08 output low level */ \
        PORT->PMD  &= ~(1 << 8);    /* PD08 is used as SCLA0 output */ \
        PORT->PUD  |=  (1 << 8);    /* PD08 pullup enable */ \
        PORT->POMD |=  (1 << 8);    /* PD08 is used as Open Drain output */ \
        PORT->PMCD &= ~(1 << 8);    /* PD08 digital function */ \
}while(0)

/* ToDo: You can allocate the SDAA0 to any desired pins with SDAA0PCFG register */
#define SDAA0_PORT_SETTING() do{ \
        PORT->SDAA0PCFG = PTCFG_PD09;/* allocate SDAA0 to PD09 */ \
        PORT->PCLRD =  (1 << 9);    /* PD09 output low level */ \
        PORT->PMD  &= ~(1 << 9);    /* PD09 is used as SDAA0 inout */ \
        PORT->PUD  |=  (1 << 9);    /* PD09 pullup enable */ \
        PORT->POMD |=  (1 << 9);    /* PD09 is used as Open Drain output */ \
        PORT->PMCD &= ~(1 << 9);    /* PD09 digital function */ \
}while(0)

/**
  * @brief IICA1 Port Setting（Alternative to any group2 port)
  */

/* ToDo: You can allocate the SCLA1 to any desired pins with SCLA1PCFG register */
#define SCLA1_PORT_SETTING() do{ \
        PORT->SCLA1PCFG = PTCFG_PD05;/* allocate SCLA1 to PD05 */ \
        PORT->PCLRD =  (1 << 5);    /* PD05 output low level */ \
        PORT->PMD  &= ~(1 << 5);    /* PD05 is used as SCLA1 output */ \
        PORT->PUD  |=  (1 << 5);    /* PD05 pullup enable */ \
        PORT->POMD |=  (1 << 5);    /* PD05 is used as Open Drain output */ \
        PORT->PMCD &= ~(1 << 5);    /* PD05 digital function */ \
}while(0)

/* ToDo: You can allocate the SDAA1 to any desired pins with SDAA1PCFG register */
#define SDAA1_PORT_SETTING() do{ \
        PORT->SDAA1PCFG = PTCFG_PD06;/* allocate SDAA1 to PD06 */ \
        PORT->PCLRD =  (1 << 6);    /* PD06 output low level */ \
        PORT->PMD  &= ~(1 << 6);    /* PD06 is used as SDAA1 inout */ \
        PORT->PUD  |=  (1 << 6);    /* PD06 pullup enable */ \
        PORT->POMD |=  (1 << 6);    /* PD06 is used as Open Drain output */ \
        PORT->PMCD &= ~(1 << 6);    /* PD06 digital function */ \
}while(0)

/* ================================================================================================================== */
/* ================                                       INTP                                       ================ */
/* ================================================================================================================== */
/**
  * @brief INTP Port Setting 
  */
/* ToDo: You can allocate the INTP0 to any desired pins with INTP0PCFG register */
#define INTP0_PORT_SETTING() do{ \
        PORT->INTP0PCFG = 0x07;    /* allocate INTP0 to PC07 */ \
        PORT->PMC  |=  (1 << 7);   /* PC07 is used as INTP0 input */ \
        PORT->PMCC &= ~(1 << 7);   /* PC07 digital function */ \
}while(0)

/* ToDo: You can allocate the INTP1 to any desired pins with INTP1PCFG register */
#define INTP1_PORT_SETTING() do{ \
        PORT->INTP1PCFG = 0x04;     /* allocate INTP1 to PC08 */ \
        PORT->PMC  |=  (1 << 8);    /* PC08 is used as INTP1 input */ \
        PORT->PMCC &= ~(1 << 8);    /* PC08 digital function */ \
}while(0)

/* ToDo: You can allocate the INTP2 to any desired pins with INTP2PCFG register */
#define INTP2_PORT_SETTING() do{ \
        PORT->INTP2PCFG = 0x02;     /* allocate INTP2 to PA02 */ \
        PORT->PMA  |=  (1 << 2);    /* PA02 is used as INTP2 input */ \
        PORT->PMCA &= ~(1 << 2);    /* PA02 digital function */ \
}while(0)

/* ToDo: You can allocate the INTP3 to any desired pins with INTP3PCFG register */
#define INTP3_PORT_SETTING() do{ \
        PORT->INTP3PCFG = 0x00;     /* allocate INTP3 to PA04 */ \
        PORT->PMA  |=  (1 << 4);    /* PA04 is used as INTP3 input */ \
        PORT->PMCA &= ~(1 << 4);    /* PA04 digital function */ \
}while(0)

/* ToDo: You can allocate the INTP4 to any desired pins with INTP4PCFG register */
#define INTP4_PORT_SETTING() do{ \
        PORT->INTP4PCFG = 0x01;     /* allocate INTP4 to PD01 */ \
        PORT->PMD  |=  (1 << 1);    /* PD01 is used as INTP4 input */ \
        PORT->PMCD &= ~(1 << 1);    /* PD01 digital function */ \
}while(0)

/* ToDo: You can allocate the INTP5 to any desired pins with INTP5PCFG register */
#define INTP5_PORT_SETTING() do{ \
        PORT->INTP5PCFG = 0x04;     /* allocate INTP5 to PD08 */ \
        PORT->PMD  |=  (1 << 8);    /* PD08 is used as INTP5 input */ \
        PORT->PMCD &= ~(1 << 8);    /* PD08 digital function */ \
}while(0)

/* ToDo: You can allocate the INTP6 to any desired pins with INTP6PCFG register */
#define INTP6_PORT_SETTING() do{ \
        PORT->INTP6PCFG = 0x00;     /* allocate INTP6 to PB00 */ \
        PORT->PMB  |=  (1 << 0);    /* PB00 is used as INTP6 input */ \
        PORT->PMCB &= ~(1 << 0);    /* PB00 digital function */ \
}while(0)

/* ToDo: You can allocate the INTP7 to any desired pins with INTP7PCFG register */
#define INTP7_PORT_SETTING() do{ \
        PORT->INTP7PCFG = 0x01;     /* allocate INTP7 to PB06 */ \
        PORT->PMB  |=  (1 << 6);    /* PB06 is used as INTP7 input */ \
        PORT->PMCB &= ~(1 << 6);    /* PB06 digital function */ \
}while(0)

/** @} */ /* End of group Peripherals_Port_Setting_Definations */

#endif
