/****************************************************************************
 *   $Id:: uart.c 6957 2011-03-23 23:03:48Z usb00423                        $
 *   Project: NXP LPC11xx UART example
 *
 *   Description:
 *     This file contains UART code example which include UART 
 *     initialization, UART interrupt handler, and related APIs for 
 *     UART access.
 *
 ****************************************************************************
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * products. This software is supplied "AS IS" without any warranties.
 * NXP Semiconductors assumes no responsibility or liability for the
 * use of the software, conveys no license or title under any patent,
 * copyright, or mask work right to the product. NXP Semiconductors
 * reserves the right to make changes in the software without
 * notification. NXP Semiconductors also make no representation or
 * warranty that such application will be suitable for the specified
 * use without further testing or modification.
****************************************************************************/
#define __UART_C__

#include "LPC11Uxx.h"
#include "uart.h"

/*****************************************************************************
** Function name:		UART_IRQHandler
**
** Descriptions:		UART interrupt handler
**
** parameters:			None
** Returned value:		None
** 
*****************************************************************************/
void UART_IRQHandler(void)
{
	U8 IIRValue, LSRValue,Dummy;

	IIRValue = LPC_USART->IIR;

	IIRValue >>= 1;/* skip pending bit in IIR */
	IIRValue &= 0x07;/* check bit 1~3, interrupt identification */
  
	switch(IIRValue)
	{
		case  IIR_RLS:/* Receive Line Status */	
		LSRValue = LPC_USART->LSR;
		/* Receive Line Status */
		if(LSRValue & (LSR_OE | LSR_PE | LSR_FE | LSR_RXFE | LSR_BI))
		{
			/* There are errors or break interrupt */
			/* Read LSR will clear the interrupt */
			g_Uart_Setting.UartStatus = LSRValue;
			Dummy = LPC_USART->RBR;	/* Dummy read on RX to clear 
			interrupt, then bail out */
			break;
		}
		
		if(LSRValue & LSR_RDR)	/* Receive Data Ready */			
		{
			/* If no error on RLS, normal ready, save into the data buffer. */
			/* Note: read RBR will clear the interrupt */
			g_Uart_Setting.UartBuffer[g_Uart_Setting.UartCount] = LPC_USART->RBR;
			g_Uart_Setting.UartCount++;

			if (g_Uart_Setting.UartCount > UARTBUFSIZE)   
			{
				g_Uart_Setting.UartCount = 0;/*buffer overflow*/
				g_Uart_Setting.UartStatus |= LSR_OE;

				for(Dummy = 0; Dummy < UARTBUFSIZE; Dummy++)
				g_Uart_Setting.UartBuffer[Dummy] = 0xFF;	
			}			
		}
		break;
	
		case IIR_RDA:/* Receive Data Available */	
		/* Receive Data Available */
		g_Uart_Setting.UartBuffer[g_Uart_Setting.UartCount] = LPC_USART->RBR;
		g_Uart_Setting.UartCount++;

		if(g_Uart_Setting.UartCount > UARTBUFSIZE)   
		{
			g_Uart_Setting.UartCount = 0;/* buffer overflow */	
			g_Uart_Setting.UartStatus = LSR_OE;

			for(Dummy = 0; Dummy< UARTBUFSIZE; Dummy++)
			g_Uart_Setting.UartBuffer[Dummy] = 0xFF;	
		}
		break;
	
		case IIR_CTI:	/* Character timeout indicator */	
		/* Character Time-out indicator */
		g_Uart_Setting.UartStatus |= 0x100;/* Bit 9 as the CTI error */
		break;
	
		case IIR_THRE:/* THRE, transmit holding register empty */	
		/* THRE interrupt */
		LSRValue = LPC_USART->LSR;/* Check status in the LSR to see if valid data in U0THR or not */

		if(LSRValue & LSR_THRE)   
		g_Uart_Setting.UartStatus = LSR_THRE;	    
		else   
		g_Uart_Setting.UartStatus &= ~LSR_THRE;	 
		break;
	}
}

/*****************************************************************************
** Function name:		UARTInit
**
** Descriptions:		Initialize UART0 port, setup pin select,
**				clock, parity, stop bits, FIFO, etc.
**
** parameters:			UART baudrate
** Returned value:		None
** 
*****************************************************************************/
void nsAPI_UART_Init(U32 baudrate)
{
	U32 Fdiv,regVal;  

	g_Uart_Setting.UartStatus = LSR_THRE;	
	g_Uart_Setting.UartCount = 0;

	for(Fdiv = 0; Fdiv < UARTBUFSIZE; Fdiv++)
	g_Uart_Setting.UartBuffer[Fdiv] = 0xFF;	

	NVIC_DisableIRQ(UART_IRQn);
	/* Select only one location from below. */

	LPC_IOCON->PIO0_18 &= ~0x07;/*UART I/O config*/
	LPC_IOCON->PIO0_18 |= 0x01;/*UART RXD*/
	LPC_IOCON->PIO0_19 &= ~0x07;	
	LPC_IOCON->PIO0_19 |= 0x01;/*UART TXD*/

	/* Enable UART clock */
	LPC_SYSCON->SYSAHBCLKCTRL |= BIT12;
	LPC_SYSCON->UARTCLKDIV = BIT0;/* divided by 1 */

	LPC_USART->LCR = 0x83;/* 8 bits, no Parity, 1 Stop bit */
	regVal = LPC_SYSCON->UARTCLKDIV;
	Fdiv = ((SystemCoreClock/regVal)/16)/baudrate;/*baud rate */

	LPC_USART->DLM = Fdiv >> 8;							
	LPC_USART->DLL = Fdiv % 256;
	LPC_USART->LCR = 0x03;/* DLAB = 0 */
	LPC_USART->FCR = 0x07;/* Enable and reset TX and RX FIFO. */

	/* Read to clear the line status */
	regVal = LPC_USART->LSR;

	/* Ensure a clean start, no data in either TX or RX FIFO. */
	while(( LPC_USART->LSR & (LSR_THRE|LSR_TEMT)) != (LSR_THRE|LSR_TEMT)){}
	while(LPC_USART->LSR & LSR_RDR )
	{
		regVal = LPC_USART->RBR;	/* Dump data from RX FIFO */
	}

	/* Enable the UART Interrupt */
	NVIC_EnableIRQ(UART_IRQn);

#if TX_INTERRUPT
	LPC_USART->IER = IER_RBR | IER_THRE | IER_RLS;/* Enable UART interrupt */
#else
	LPC_USART->IER = IER_RBR | IER_RLS;/* Enable UART interrupt */
#endif
}

/*****************************************************************************
** Function name:		UARTSend
**
** Descriptions:		Send a block of data to the UART 0 port based
**				on the data length
**
** parameters:		buffer pointer, and data length
** Returned value:	None
** 
*****************************************************************************/
void nsAPI_UART_Send(U8 *BufferPtr, U32 Length)
{  
	while(Length != 0)
	{
		/* THRE status, contain valid data */
#if !TX_INTERRUPT
		while(!(LPC_USART->LSR & LSR_THRE)){}
		LPC_USART->THR = *BufferPtr;
#else
		/* Below flag is set inside the interrupt handler when THRE occurs. */
		while (!(g_Uart_Setting.UartStatus & LSR_THRE)){}
		LPC_USART->THR = *BufferPtr;
		g_Uart_Setting.UartStatus &= ~LSR_THRE; /* not empty in the THR until it shifts out */
#endif
		BufferPtr++;
		Length--;
	}
}

void xprintf(U8 *pFmt,U32 wVal,...)
{
	U8 ucBff,ucDisp;
	U8 bHex = FALSE,u8Into = 0,bNotZero = FALSE;   
	U32 wDivider = 10000000;	


	//LPC_USART->IER = IER_THRE | IER_RLS;/* Disable RBR */

	while((ucBff =*(pFmt++)) > 0)
	{	
		if(ucBff == '%') // check special case
		{
			u8Into++;  		 
			switch(*(pFmt++)) // check next character
			{
				case 'x': // hexadecimal number
				case 'X':
				wDivider = 0x10000000;
				bHex = TRUE;
				case 'd': // decimal number
				case 'i':

				if(wVal)
				{
					while(wDivider)
					{
						ucDisp = wVal / wDivider;
						wVal = wVal % wDivider;

						if(ucDisp)
						bNotZero=TRUE;					

						if(bNotZero)
						{
							if(ucDisp > 9)
							ucBff = ucDisp-0x0a+'A';
							else
							ucBff = ucDisp+'0';

							nsAPI_UART_Send(&ucBff,1);
						}					

						if(bHex)
						wDivider /= 0x10;
						else
						wDivider /= 10;
					}
				}
				else
				{
					ucBff = '0';
					nsAPI_UART_Send(&ucBff,1);
				}		   
				break;				
			}
		}
		else // general
		nsAPI_UART_Send(&ucBff,1); 
	} 
}

