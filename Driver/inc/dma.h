/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    dma.h
* @brief   This file implements device driver for DTC module.
* @version 1.0.0  
* @date    2019/12/24
***********************************************************************************************************************/
#ifndef DMA_H
#define DMA_H

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/
/*
    Bit Position of DMACR
*/
#define FIFO_Pos     8
#define SZ_Pos       6
#define RPTINT_Pos   5
#define CHNE_Pos     4
#define DAMOD_Pos    3
#define SAMOD_Pos    2
#define RPTSEL_Pos   1
#define MODE_Pos     0

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef enum {
   DMA_VECTOR_FLASH     =  0U,  /* Flash擦除/写入结束 */
   DMA_VECTOR_INTP0 	=  1U,  /* 外部中断INTP0 */
   DMA_VECTOR_INTP1 	=  2U,  /* 外部中断INTP1 */
   DMA_VECTOR_INTP2 	=  3U,  /* 外部中断INTP2 */
   DMA_VECTOR_INTP3 	=  4U,  /* 外部中断INTP3 */
   DMA_VECTOR_INTP4 	=  5U,  /* 外部中断INTP4 */
   DMA_VECTOR_INTP5 	=  6U,  /* 外部中断INTP5 */
   DMA_VECTOR_INTP6 	=  7U,  /* 外部中断INTP6 */
   DMA_VECTOR_INTP7 	=  8U,  /* 外部中断INTP7 */
   DMA_VECTOR_KEY   	=  9U,  /* KEY中断 */
   DMA_VECTOR_ADC   	= 10U,  /* A/D 转换结束 */
   DMA_VECTOR_ST0       = 11U,  /* UART0发送传送结束/SPI00传送结束或者缓冲器空/IIC00传送结束 */
   DMA_VECTOR_SPI00     = 11U,  /* UART0发送传送结束/SPI00传送结束或者缓冲器空/IIC00传送结束 */
   DMA_VECTOR_IIC00     = 11U,  /* UART0发送传送结束/SPI00传送结束或者缓冲器空/IIC00传送结束 */
   DMA_VECTOR_SR0       = 12U,  /* UART0接收传送结束/SPI01传送结束或者缓冲器空/IIC01传送结束 */
   DMA_VECTOR_SPI01     = 12U,  /* UART0接收传送结束/SPI01传送结束或者缓冲器空/IIC01传送结束 */
   DMA_VECTOR_IIC01     = 12U,  /* UART0接收传送结束/SPI01传送结束或者缓冲器空/IIC01传送结束 */
   DMA_VECTOR_ST1       = 13U,  /* UART1发送传送结束/SPI10传送结束或者缓冲器空/IIC10传送结束 */
   DMA_VECTOR_SPI10     = 13U,  /* UART1发送传送结束/SPI10传送结束或者缓冲器空/IIC10传送结束 */
   DMA_VECTOR_IIC10     = 13U,  /* UART1发送传送结束/SPI10传送结束或者缓冲器空/IIC10传送结束 */
   DMA_VECTOR_SR1       = 14U,  /* UART1接收传送结束/SPI11传送结束或者缓冲器空/IIC11传送结束 */
   DMA_VECTOR_SPI11     = 14U,  /* UART1接收传送结束/SPI11传送结束或者缓冲器空/IIC11传送结束 */
   DMA_VECTOR_IIC11     = 14U,  /* UART1接收传送结束/SPI11传送结束或者缓冲器空/IIC11传送结束 */
   DMA_VECTOR_ST2       = 15U,  /* UART2发送传送结束/SPI20传送结束或者缓冲器空/IIC20传送结束 */
   DMA_VECTOR_SPI20     = 15U,  /* UART2发送传送结束/SPI20传送结束或者缓冲器空/IIC20传送结束 */
   DMA_VECTOR_IIC20     = 15U,  /* UART2发送传送结束/SPI20传送结束或者缓冲器空/IIC20传送结束 */
   DMA_VECTOR_SR2       = 16U,  /* UART2接收传送结束/SPI21传送结束或者缓冲器空/IIC21传送结束 */
   DMA_VECTOR_SPI21     = 16U,  /* UART2接收传送结束/SPI21传送结束或者缓冲器空/IIC21传送结束 */
   DMA_VECTOR_IIC21     = 16U,  /* UART2接收传送结束/SPI21传送结束或者缓冲器空/IIC21传送结束 */
   DMA_VECTOR_IICA0     = 17U,  /* IICA通信结束 */
   DMA_VECTOR_IICA1     = 18U,  /* IICA通信结束 */
   DMA_VECTOR_SPIHS0    = 19U,  /* SPI0传送结束或者缓冲器空 */
   DMA_VECTOR_SPIHS1    = 20U,  /* SPI1传送结束或者缓冲器空 */
   DMA_VECTOR_TM40_CH0  = 21U,  /* 定时器阵列单元0的通道0的计数结束或者捕获结束 */
   DMA_VECTOR_TM40_CH1  = 22U,  /* 定时器阵列单元0的通道1的计数结束或者捕获结束 */ 
   DMA_VECTOR_TM40_CH2  = 23U,  /* 定时器阵列单元0的通道2的计数结束或者捕获结束 */
   DMA_VECTOR_TM40_CH3  = 24U,  /* 定时器阵列单元0的通道3的计数结束或者捕获结束 */
   DMA_VECTOR_TM80_CH0  = 25U,  /* 定时器阵列单元1的通道0的计数结束或者捕获结束 */
   DMA_VECTOR_TM80_CH1  = 26U,  /* 定时器阵列单元1的通道1的计数结束或者捕获结束 */ 
   DMA_VECTOR_TM80_CH2  = 27U,  /* 定时器阵列单元1的通道2的计数结束或者捕获结束 */
   DMA_VECTOR_TM80_CH3  = 28U,  /* 定时器阵列单元1的通道3的计数结束或者捕获结束 */
   DMA_VECTOR_TM80_CH4  = 29U,  /* 定时器阵列单元1的通道4的计数结束或者捕获结束 */
   DMA_VECTOR_SSI_TX    = 30U,  /* SSI 发送DMA请求 */
   DMA_VECTOR_SSI_RX    = 31U,  /* SSI 接收DMA请求 */
   DMA_VECTOR_SSI_RT    = 32U,  /* SSI 收发DMA请求 */
   DMA_VECTOR_IT        = 33U,  /* 间隔定时器中断 */
   DMA_VECTOR_USB_FIFO0 = 34U,  /* USB FIFO0 DMA请求 */
   DMA_VECTOR_USB_FIFO1 = 35U,  /* USB FIFO1 DMA请求 */
   DMA_VECTOR_CMP0      = 36U,  /* 比较器0 */
   DMA_VECTOR_CMP1      = 37U,  /* 比较器1 */
   DMA_VECTOR_QSPI      = 38U,  /* QSPI DMA请求 */
   DMA_VECTOR_LCDB      = 39U,  /* LCDB DMA请求 */

} dma_vector_t;

typedef enum {
	DMA_SIZE_BYTE, 				/*  8bits transfer */ 
	DMA_SIZE_HALF,  			/* 16bits transfer */
	DMA_SIZE_WORD   			/* 32bits transfer */
} dma_size_t;

typedef enum {
	DMA_MODE_NORMAL, 			/* Normal mode */ 
	DMA_MODE_REPEAT   			/* Repeat mode */
} dma_mode_t;

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
#if 1
void DMA_Start(dma_vector_t vect_num, uint8_t ctrl_data_num, dma_mode_t mode, dma_size_t size, uint16_t count, void *src_adr, void *dst_adr);
#else
void DMA_Start(dma_vector_t vect_num, uint8_t ctrl_data_num, DMAVEC_CTRL_Type ctrl_data);
#endif
void DMA_Enable(dma_vector_t vect_num);
void DMA_Stop(dma_vector_t vect_num);
/* Start user code for function. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#endif
