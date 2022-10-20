
#define __SSP_C__

#include "LPC11Uxx.h"
#include "ssp.h"
#include "uart.h"
#include "Main.h"
#include "I2C.h"
#include "Pixart_Sensor.h"

/*****************************************************************************
** Function name:		SSP0_IRQHandler
**
** Descriptions:		SSP port is used for SPI communication.
**						SSP interrupt handler
**						The algorithm is, if RXFIFO is at least half full, 
**						start receive until it's empty; if TXFIFO is at least
**						half empty, start transmit until it's full.
**						This will maximize the use of both FIFOs and performance.
**
** parameters:			None
** Returned value:		None
** 
****************************************************************************/
void SSP0_IRQHandler(void) 
{
	
}

/*****************************************************************************
** Function name:		SSP1_IRQHandler
**
** Descriptions:		SSP port is used for SPI communication.
**						SSP interrupt handler
**						The algorithm is, if RXFIFO is at least half full, 
**						start receive until it's empty; if TXFIFO is at least
**						half empty, start transmit until it's full.
**						This will maximize the use of both FIFOs and performance.
**
** parameters:			None
** Returned value:		None
** 
*****************************************************************************/
void SSP1_IRQHandler(void) 
{
  
}

/**************************************************************************

    @brief Initialise SSP0

**************************************************************************/
void nsAPI_SSP_Init(void)
{  
	U8 i, Dummy = Dummy;
	
	NVIC_DisableIRQ(SSP0_IRQn); 
	
	LPC_SYSCON->PRESETCTRL |= BIT0;	
	LPC_SYSCON->SYSAHBCLKCTRL |= BIT11;			// Enable AHB clock to the SSP domain
//	LPC_SYSCON->SSP0CLKDIV = SCB_CLKDIV_DIV2;	// Divide by 2 for SSPCLKDIV 	//v0.1
	LPC_SYSCON->SSP0CLKDIV = SCB_CLKDIV_DIV1;	// 4MHz reporting test for alpha test

	// Set P0.8 to SSP MISO 
	LPC_IOCON->PIO0_8 &= ~0x07;
	LPC_IOCON->PIO0_8 |= BIT0;

	// Set P0.9 to SSP MOSI 
	LPC_IOCON->PIO0_9 &= ~0x07;
	LPC_IOCON->PIO0_9 |= BIT0;

	// Set 1.29 to SSP SCK (0.6 is used by USB and 0.10 for SWD) 
	// No LPC_IOCON SCKLOC register on LPC11U14?
	LPC_IOCON->PIO1_29 = BIT0;

	// Set SSEL0 to GPIO P0.2  
	LPC_IOCON->PIO0_2 &= ~0x07;
	LPC_IOCON->PIO0_2 |= BIT4;	

	// Control Register 1 CR0
	// (PCLK / (CPSDVSR * [SCR+1])) = (48,000,000 / (2 * [2 + 1])) = 8.0 MHz 
	// Data size = bits 3:0) : 0x7, 8-bit
	// CPOL = 1(bit 6): SPI controller maintains the bus clock high between frames.
	// CPHA = 1(bit 7): SPI controller captures serial data on the second clock
	// 					transition of the frame, that is, the transition back to the
	// 					inter-frame state of the clock line.
	// Clock rate = 5(bits 15:8)
	LPC_SSP0->CR0 = ( /*SSP_SCR_11*/ SSP_SCR_2 | BIT7 | BIT6 | (BIT2|BIT1|BIT0) ); 
	
	// Clock prescale register must be even and at least 2 in master mode 
	LPC_SSP0->CPSR = 2;

	// SPI Data Register DR
	// Clear the Rx FIFO   
	for(i = 0; i < SSP_FIFOSIZE; i++)    
		Dummy = LPC_SSP0->DR;   

	NVIC_EnableIRQ(SSP0_IRQn); 

	// Control Register 1 CR1
	// Enable device and set it to master mode, no loopback 
	LPC_SSP0->CR1 = SSP_CR1_SSE_ENABLED | SSP_CR1_MS_MASTER | SSP_CR1_LBM_NORMAL;

	NDrv_GPIO_SetBitValue(PORT0,2,HIGH); // Set NCS high
	//nsAPI_SSP_Init();
}

/**************************************************************************

    @brief Sends a block of data using SSP0

    @param[in]  buf
                Pointer to the data buffer
    @param[in]  length
                Block length of the data buffer

*************************************************************************/

void nsAPI_SSP_Send(U8 *buf, U16 length)
{	
	U8 Dummy = Dummy;

	// Move on only if NOT busy and TX FIFO not full. 
	while((LPC_SSP0->SR & (SSP_SR_TNF_NOTFULL | SSP_SR_BSY_BUSY)) != SSP_SR_TNF_NOTFULL){}
	LPC_SSP0->DR = *buf;		       

	while((LPC_SSP0->SR & (SSP_SR_BSY_BUSY|SSP_SR_RNE_NOTEMPTY)) != SSP_SR_RNE_NOTEMPTY){}
	// Whenever a byte is written, MISO FIFO counter increments, Clear FIFO
	//on MISO. Otherwise, when sspReceive is called, previous data byte
	// is left in the FIFO. 
	Dummy = LPC_SSP0->DR;	
}

/*************************************************************************

    @brief Receives a block of data using SSP0

    @param[in]  buf
                Pointer to the data buffer
    @param[in]  length
                Block length of the data buffer

*************************************************************************/
void nsAPI_SSP_Receive(U8 *buf, U16 length)
{	
	// As long as the receive FIFO is not empty, data can be received. 
	LPC_SSP0->DR = 0xFF;

	// Wait until the Busy bit is cleared 
	while((LPC_SSP0->SR & (SSP_SR_BSY_BUSY|SSP_SR_RNE_NOTEMPTY)) != SSP_SR_RNE_NOTEMPTY ){}
	*buf = LPC_SSP0->DR;	
}

