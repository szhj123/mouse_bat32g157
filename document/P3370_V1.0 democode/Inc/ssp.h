#ifndef __SSP_H__
#define __SSP_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "Type.h"
#include "Gpio.h"

#ifdef  __SSP_C__
#define INTERFACE
#else
#define INTERFACE extern
#endif

#if 0
#define _DEBUG_SSP_(x) x
#else
#define _DEBUG_SSP_(x) 
#endif


/* SSP Clock div (0..255) */
#define SCB_CLKDIV_DISABLE (0x00000000)
#define SCB_CLKDIV_DIV1 (0x00000001)
#define SCB_CLKDIV_DIV2 (0x00000002)
#define SCB_CLKDIV_DIV3 (0x00000003)
#define SCB_CLKDIV_DIV4 (0x00000004)
#define SCB_CLKDIV_DIV5 (0x00000005)
#define SCB_CLKDIV_DIV6 (0x00000006)
#define SCB_CLKDIV_DIV7 (0x00000007)
#define SCB_CLKDIV_DIV8 (0x00000008)
#define SCB_CLKDIV_DIV9 (0x00000009)
#define SCB_CLKDIV_DIV10 (0x0000000A)
#define SCB_CLKDIV_DIV11 (0x0000000B)
#define SCB_CLKDIV_DIV12 (0x0000000C)
#define SCB_CLKDIV_DIV13 (0x0000000D)
#define SCB_CLKDIV_DIV14 (0x0000000E)
#define SCB_CLKDIV_DIV15 (0x0000000F)
#define SCB_CLKDIV_DIV20 (0x00000014)
#define SCB_CLKDIV_DIV25 (0x00000019)
#define SCB_CLKDIV_DIV30 (0x0000001E)
#define SCB_CLKDIV_DIV35 (0x00000033)
#define SCB_CLKDIV_DIV40 (0x00000028)
#define SCB_CLKDIV_DIV45 (0x0000002D)
#define SCB_CLKDIV_MASK (0x000000FF)

/* SSP Serial Clock Rate Values */
#define SSP_SCR_1 (0x00000100)
#define SSP_SCR_2 (0x00000200)
#define SSP_SCR_3 (0x00000300)
#define SSP_SCR_4 (0x00000400)
#define SSP_SCR_5 (0x00000500)
#define SSP_SCR_6 (0x00000600)
#define SSP_SCR_7 (0x00000700)
#define SSP_SCR_8 (0x00000800)
#define SSP_SCR_9 (0x00000900)
#define SSP_SCR_10 (0x00000A00)
#define SSP_SCR_11 (0x00000B00)
#define SSP_SCR_12 (0x00000C00)
#define SSP_SCR_13 (0x00000D00)
#define SSP_SCR_14 (0x00000E00)
#define SSP_SCR_15 (0x00000F00)
#define SSP_SCR_16 (0x00001000)
#define SSP_SCR_23 (0x00001700)
#define SSP_SCR_47 (0x00003F00)



/*  Current status of the SSP controller.  */
#define SSP_SR_TFE_MASK (0x00000001) // Transmit FIFO empty
#define SSP_SR_TFE_EMPTY (0x00000001)
#define SSP_SR_TFE_NOTEMPTY (0x00000000)
#define SSP_SR_TNF_MASK (0x00000002) // Transmit FIFO not full
#define SSP_SR_TNF_NOTFULL (0x00000002)
#define SSP_SR_TNF_FULL (0x00000000)
#define SSP_SR_RNE_MASK (0x00000004) // Receive FIFO not empty
#define SSP_SR_RNE_NOTEMPTY (0x00000004)
#define SSP_SR_RNE_EMPTY (0x00000000)
#define SSP_SR_RFF_MASK (0x00000008) // Receive FIFO full
#define SSP_SR_RFF_FULL (0x00000008)
#define SSP_SR_RFF_NOTFULL (0x00000000)
#define SSP_SR_BSY_MASK (0x00000010) // Busy Flag
#define SSP_SR_BSY_IDLE (0x00000000)
#define SSP_SR_BSY_BUSY (0x00000010)

/* Control Register 1 */
#define SSP_CR1_LBM_MASK BIT0 // Loop back mode
#define SSP_CR1_LBM_NORMAL (0)
#define SSP_CR1_LBM_INVERTED BIT0 // MISO/MOSI are reversed
#define SSP_CR1_SSE_MASK BIT1 // SSP enable
#define SSP_CR1_SSE_DISABLED (0)
#define SSP_CR1_SSE_ENABLED BIT1
#define SSP_CR1_MS_MASK BIT2 // Master/Slave Mode
#define SSP_CR1_MS_MASTER (0)
#define SSP_CR1_MS_SLAVE BIT2
#define SSP_CR1_SOD_MASK BIT2 // Slave output disable


 

INTERFACE void SSP0_IRQHandler(void); 
INTERFACE void SSP1_IRQHandler(void); 
INTERFACE void nsAPI_SSP_Init(void);
INTERFACE void nsAPI_SSP_Send(U8 *buf, U16 length);
INTERFACE void nsAPI_SSP_Receive(U8 *buf, U16 length);

 
#undef INTERFACE
#ifdef __cplusplus
}
#endif
#endif
