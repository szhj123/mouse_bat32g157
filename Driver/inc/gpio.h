/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    gpio.h
* @brief   This file implements device driver for GPIO module.
* @version 1.0.0
* @date    2020/10/24
***********************************************************************************************************************/
#ifndef GPIO_H
#define GPIO_H
#ifndef __CORE_CM0PLUS_H_GENERIC
#include "core_cm0plus.h"
#endif

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef enum {
	PORTA = 0,
	PORTB = 1,
	PORTC = 2,
	PORTD = 3,
	PORTH = 7,
}PORT_TypeDef;

typedef enum {
	PIN0 = 0,
	PIN1,
	PIN2,
	PIN3,
	PIN4,
	PIN5,
	PIN6,
	PIN7,
	PIN8,
	PIN9,
	PIN10,
	PIN11,
	PIN12,
	PIN13,
	PIN14,
	PIN15,
	
}PIN_TypeDef;

typedef enum {
	INPUT = 0,
	PULLUP_INPUT,
	TTL_INPUT,
	ANALOG_INPUT,
	OUTPUT,
	OPENDRAIN_OUTPUT,
	PULLDOWN_INPUT,
}PIN_ModeDef;

typedef enum {
  PB00_CFG = 0x00,
  PH04_CFG = 0x01,
  PH03_CFG = 0x02,
  PH02_CFG = 0x03,
  PH01_CFG = 0x04,
  PC14_CFG = 0x05,
  PC15_CFG = 0x06,
  PC08_CFG = 0x07,
  PC09_CFG = 0x08,
  PC10_CFG = 0x09,
  PC11_CFG = 0x0a,
  PA00_CFG = 0x0b,
  PA01_CFG = 0x0c,
  PA02_CFG = 0x0d,
  PA03_CFG = 0x0e,
  PD07_CFG = 0x0f,
  PD08_CFG = 0x10,
  PD09_CFG = 0x11,
  PD10_CFG = 0x12,
  PD11_CFG = 0x13,
  PC03_CFG = 0x20,
  PC04_CFG = 0x21,
  PC05_CFG = 0x22,
  PC06_CFG = 0x23,
  PC07_CFG = 0x24,
  PC12_CFG = 0x25,
  PC13_CFG = 0x26,
  PA04_CFG = 0x27,
  PA05_CFG = 0x28,
  PA06_CFG = 0x29,
  PA07_CFG = 0x2A,
  PA08_CFG = 0x2B,
  PA09_CFG = 0x2C,
  PA10_CFG = 0x2D,
  PD00_CFG = 0x2E,
  PD01_CFG = 0x2F,
  PD12_CFG = 0x30,
  PD13_CFG = 0x31,
  PD14_CFG = 0x32,
  PD15_CFG = 0x33,
  PB01_CFG = 0x40,
  PB02_CFG = 0x41,
  PB03_CFG = 0x42,
  PB04_CFG = 0x43,
  PB05_CFG = 0x44,
  PB06_CFG = 0x45,
  PB07_CFG = 0x46,
  PB08_CFG = 0x47,
  PC00_CFG = 0x48,
  PC01_CFG = 0x49,
  PC02_CFG = 0x4a,
  PA11_CFG = 0x4b,
  PA12_CFG = 0x4c,
  PA13_CFG = 0x4d,
  PA14_CFG = 0x4e,
  PD02_CFG = 0x4f,
  PD03_CFG = 0x50,
  PD04_CFG = 0x51,
  PD05_CFG = 0x52,
  PD06_CFG = 0x53,
}IO_CfgType;

typedef enum {
  IOCFG_GPIO  = 0x00,
  IOCFG_TO00  = 0x01,
	IOCFG_TO10  = 0x01,
  IOCFG_TO01  = 0x02,
	IOCFG_TO11  = 0x02,
  IOCFG_TO02  = 0x03,
	IOCFG_TO12  = 0x03,
  IOCFG_TO03  = 0x04,
	IOCFG_TO13  = 0x04,
  IOCFG_SDO00 = 0x05,
  IOCFG_TXD0  = 0x05,
	IOCFG_TXD1  = 0x05,
  IOCFG_SDO10 = 0x05,
  IOCFG_TXD2  = 0x05,
	IOCFG_SDO20 = 0x05,
  IOCFG_CLKBUZ1 = 0x06,
  IOCFG_SPIHS0SCLKO = 0x06,
  IOCFG_SPIHS0MO    = 0x07,
  IOCFG_SPIHS0SO    = 0x08,
}IO_CfgDef;

typedef enum {
  TI00_PCFG  = 0x00,                     /*!< (@ 0x00000980) TI10 alternate function pin configuration register         */
  TI01_PCFG  = 0x01,                     /*!< (@ 0x00000981) TI11 alternate function pin configuration register         */
  TI02_PCFG  = 0x02,                     /*!< (@ 0x00000982) TI12 alternate function pin configuration register         */
  TI03_PCFG  = 0x03,                     /*!< (@ 0x00000983) TI13 alternate function pin configuration register         */	
  RXD0_PCFG  = 0x04,                     /*!< (@ 0x00000984) INTP0 alternate function pin configuration register        */
  SCLA0_PCFG = 0x05,                     /*!< (@ 0x00000985) INTP1 alternate function pin configuration register        */	
  SDAA0_PCFG = 0x06,                     /*!< (@ 0x00000986) INTP2 alternate function pin configuration register        */	
	
  TI10_PCFG  = 0x20,                     /*!< (@ 0x000009a0) TI10 alternate function pin configuration register         */
  TI11_PCFG  = 0x21,                     /*!< (@ 0x000009a1) TI11 alternate function pin configuration register         */
  TI12_PCFG  = 0x22,                     /*!< (@ 0x000009a2) TI12 alternate function pin configuration register         */
  TI13_PCFG  = 0x23,                     /*!< (@ 0x000009a3) TI13 alternate function pin configuration register         */
  RXD1_PCFG  = 0x24,                     /*!< (@ 0x000009a4) INTP0 alternate function pin configuration register        */
  SPIHS0_SCKIPCFG = 0x25,                /*!< (@ 0x000009a5) INTP1 alternate function pin configuration register        */
  SPIHS0_SIPCFG   = 0x26,                /*!< (@ 0x000009a5) INTP1 alternate function pin configuration register        */	
  SPIHS0_MIPCFG   = 0x27,                /*!< (@ 0x000009a5) INTP1 alternate function pin configuration register        */	
	
  TI14_PCFG  = 0x40,                     /*!< (@ 0x000009c0) TI10 alternate function pin configuration register         */
  TI15_PCFG  = 0x41,                     /*!< (@ 0x000009c1) TI11 alternate function pin configuration register         */
  TI16_PCFG  = 0x42,                     /*!< (@ 0x000009c2) TI12 alternate function pin configuration register         */
  TI17_PCFG  = 0x43,                     /*!< (@ 0x000009c3) TI13 alternate function pin configuration register         */	
  RXD2_PCFG  = 0x44,                     /*!< (@ 0x000009c4) INTP0 alternate function pin configuration register        */
  SPIHS1_NSSPCFG = 0x45,                 /*!< (@ 0x000009c5) INTP1 alternate function pin configuration register        */
  SCLA1_PCFG = 0x46,                     /*!< (@ 0x000009c6) INTP1 alternate function pin configuration register        */	
  SDAA1_PCFG = 0x47,                     /*!< (@ 0x000009c7) INTP2 alternate function pin configuration register        */	
	
}PortInput_CfgType;

typedef enum {
	
	PORTINPUT_CFG_GPIO = 0x00,
  PORTINPUT_CFG_PB00 = 0x01,
  PORTINPUT_CFG_PH04 = 0x02,
  PORTINPUT_CFG_PH03 = 0x03,
  PORTINPUT_CFG_PH02 = 0x04,
  PORTINPUT_CFG_PH01 = 0x05,
  PORTINPUT_CFG_PC14 = 0x06,
  PORTINPUT_CFG_PC15 = 0x07,
  PORTINPUT_CFG_PC08 = 0x08,
  PORTINPUT_CFG_PC09 = 0x09,
  PORTINPUT_CFG_PC10 = 0x0a,
  PORTINPUT_CFG_PC11 = 0x0b,
  PORTINPUT_CFG_PA00 = 0x0c,
  PORTINPUT_CFG_PA01 = 0x0d,
  PORTINPUT_CFG_PA02 = 0x0e,
  PORTINPUT_CFG_PA03 = 0x0f,
  PORTINPUT_CFG_PD07 = 0x10,
  PORTINPUT_CFG_PD08 = 0x11,
  PORTINPUT_CFG_PD09 = 0x12,
  PORTINPUT_CFG_PD10 = 0x13,
  PORTINPUT_CFG_PD11 = 0x14,
	
  PORTINPUT_CFG_PC03 = 0x01,
  PORTINPUT_CFG_PC04 = 0x02,
  PORTINPUT_CFG_PC05 = 0x03,
  PORTINPUT_CFG_PC06 = 0x04,
  PORTINPUT_CFG_PC07 = 0x05,
  PORTINPUT_CFG_PC12 = 0x06,
  PORTINPUT_CFG_PC13 = 0x07,
  PORTINPUT_CFG_PA04 = 0x08,
  PORTINPUT_CFG_PA05 = 0x09,
  PORTINPUT_CFG_PA06 = 0x0a,
  PORTINPUT_CFG_PA07 = 0x0b,
  PORTINPUT_CFG_PA08 = 0x0c,
  PORTINPUT_CFG_PA09 = 0x0d,
  PORTINPUT_CFG_PA10 = 0x0e,
  PORTINPUT_CFG_PD00 = 0x0f,
  PORTINPUT_CFG_PD01 = 0x10,
  PORTINPUT_CFG_PD12 = 0x11,
  PORTINPUT_CFG_PD13 = 0x12,
  PORTINPUT_CFG_PD14 = 0x13,
  PORTINPUT_CFG_PD15 = 0x14,
	                     
  PORTINPUT_CFG_PB01 = 0x01,
  PORTINPUT_CFG_PB02 = 0x02,
  PORTINPUT_CFG_PB03 = 0x03,
  PORTINPUT_CFG_PB04 = 0x04,
  PORTINPUT_CFG_PB05 = 0x05,
  PORTINPUT_CFG_PB06 = 0x06,	
  PORTINPUT_CFG_PB07 = 0x07,	
  PORTINPUT_CFG_PB08 = 0x08,	
  PORTINPUT_CFG_PC00 = 0x09,	
  PORTINPUT_CFG_PC01 = 0x0a,	
  PORTINPUT_CFG_PC02 = 0x0b,	
  PORTINPUT_CFG_PA11 = 0x0c,	
  PORTINPUT_CFG_PA12 = 0x0d,	
  PORTINPUT_CFG_PA13 = 0x0e,	
  PORTINPUT_CFG_PA14 = 0x0f,	
  PORTINPUT_CFG_PD02 = 0x10,	
  PORTINPUT_CFG_PD03 = 0x11,	
  PORTINPUT_CFG_PD04 = 0x12,	
  PORTINPUT_CFG_PD05 = 0x13,	
  PORTINPUT_CFG_PD06 = 0x14,	
	
}PortInput_CfgDef;

//typedef enum {
//	SPI_REMAP_NOPORT = 0,
//	SPI_REMAP_GROUP1 = 1,//P50=>NSS P51=>SCK P17=>MISO P16=>MOSI 
//	SPI_REMAP_GROUP2 = 2,//P63=>NSS P31=>SCK P75=>MISO P74=>MOSI 
//	SPI_REMAP_GROUP3 = 3,//P25=>NSS P24=>SCK P23=>MISO P22=>MOSI 
//	
//}SPI_CfgDef;

#define PIN_MASK_0                 ((uint16_t)(0x0001))  /*!< Pin 0 selected    */
#define PIN_MASK_1                 ((uint16_t)(0x0002))  /*!< Pin 1 selected    */
#define PIN_MASK_2                 ((uint16_t)(0x0004))  /*!< Pin 2 selected    */
#define PIN_MASK_3                 ((uint16_t)(0x0008))  /*!< Pin 3 selected    */
#define PIN_MASK_4                 ((uint16_t)(0x0010))  /*!< Pin 4 selected    */
#define PIN_MASK_5                 ((uint16_t)(0x0020))  /*!< Pin 5 selected    */
#define PIN_MASK_6                 ((uint16_t)(0x0040))  /*!< Pin 6 selected    */
#define PIN_MASK_7                 ((uint16_t)(0x0080))  /*!< Pin 7 selected    */
#define PIN_MASK_8                 ((uint16_t)(0x0100))  /*!< Pin 8 selected    */
#define PIN_MASK_9                 ((uint16_t)(0x0200))  /*!< Pin 9 selected    */
#define PIN_MASK_10                ((uint16_t)(0x0400))  /*!< Pin 10 selected    */
#define PIN_MASK_11                ((uint16_t)(0x0800))  /*!< Pin 11 selected    */
#define PIN_MASK_12                ((uint16_t)(0x1000))  /*!< Pin 12 selected    */
#define PIN_MASK_13                ((uint16_t)(0x2000))  /*!< Pin 13 selected    */
#define PIN_MASK_14                ((uint16_t)(0x4000))  /*!< Pin 14 selected    */
#define PIN_MASK_15                ((uint16_t)(0x8000))  /*!< Pin 15 selected    */

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
void GPIO_Output_Enable(__IO uint16_t *port, uint16_t pinMsk);
void GPIO_Output_Disable(__IO uint16_t *port, uint16_t pinMsk);
void GPIO_Input_Enable(__IO uint16_t *port, uint16_t pinMsk);
void GPIO_PullUp_Enable(__IO uint16_t *port, uint16_t pinMsk);
void GPIO_PullUp_Disable(__IO uint16_t *port, uint16_t pinMsk);
void GPIO_PullDown_Enable(__IO uint16_t *port, uint16_t pinMsk);
void GPIO_PullDown_Disable(__IO uint16_t *port, uint16_t pinMsk);
void GPIO_Nch_OpenDrain(__IO uint16_t *port, uint16_t pinMsk);
void GPIO_Set_Value(__IO uint16_t *port, uint16_t value);
uint16_t GPIO_Get_Value(__IO uint16_t *port);


void PORT_Init(PORT_TypeDef PORTx,PIN_TypeDef PINx,PIN_ModeDef MODEx);
void PORT_SetBit(PORT_TypeDef PORTx,PIN_TypeDef PINx);
void PORT_ClrBit(PORT_TypeDef PORTx,PIN_TypeDef PINx);
void PORT_ToggleBit(PORT_TypeDef PORTx,PIN_TypeDef PINx);
uint16_t PORT_GetBit(PORT_TypeDef PORTx,PIN_TypeDef PINx);
void PORT_Output_Cfg(IO_CfgType PORT_CFGx, IO_CfgDef CFGx);
void PORT_Input_Cfg(PortInput_CfgType PORT_CFGx, PortInput_CfgDef CFGx);
//void SPI_Cfg(SPI_CfgDef CFGx);

#endif
