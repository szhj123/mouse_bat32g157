/***********************************************************************************************************************
* Copyright (C) . All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : main.c
* Version      :
* Device(s)    : BAT32G157
* Tool-Chain   : MDK(armcc)
* Description  : This file is a template.
* Creation Date: 2019/12/25
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include <stdbool.h>
#include <stdio.h>
#include "BAT32G157.h"
#include "userdefine.h"
#include "clk.h"
#include "usb.h"
#include "dma.h"
#include "sci.h"
#include "pcbz.h"
#include "wm8978.h"
#include "ssie.h"
#include "ssi_api_if.h"
#include "usbd_audio.h"

#include "usb_puac_apl.h"

/***********************************************************************************************************************
Macro Definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
uint32_t g_ticks;

extern volatile uint32_t iisdmacount;
extern uint8_t iistxbuff[2][512],iisrxbuff[512];

//======================================================================================================================
void usb_cpu_delay_xms(uint32_t n)
{
    g_ticks = n;

    while(g_ticks);
}

void usb_cpu_delay_1us (uint16_t time)
{
    uint16_t sf_cnt;
    sf_cnt = time * 20;

    while(sf_cnt)
    {
        sf_cnt --;
    }
}


/******************************************************************************
 * Function Name: main
 * Description  : Main task
 * Arguments    : none
 * Return Value : none
 ******************************************************************************/
int main (void)
{
//  MD_STATUS status;
    uint32_t msCnt; 	// count value of 1ms

//-----------------------------------------------------------------------
// Systick setting
//-----------------------------------------------------------------------
    g_ticks = 1000; 	// 1000ms
    //SystemCoreClockUpdate();
    //msCnt = SystemCoreClock / 1000;
    msCnt = 48000000U / 1000;				// USB use 48MHz
    SysTick_Config(msCnt);

//-----------------------------------------------------------------------
// MainOSC and SubOSC enable
//-----------------------------------------------------------------------
    //CLK_Osc_Setting(OSC_OSCILLATOR, OSC_OSCILLATOR);
    //CLK_SubOsc_Setting(OSC_OSCILLATOR, OSC_LOW_POWER);

//-----------------------------------------------------------------------
// HOCO = 32MHz / fIH = 8MHz, UPLL = 48MHz, fclk = 32MHz
//-----------------------------------------------------------------------
//	CLK_Osc_Setting(OSC_EXCLK,OSC_PORT);
//	CLK_PLL_Setting(PLL_SR_fMX,PLL_DIV_4,PLL_MUL_16);
//	CLK_UPLL_Setting(PLL_SR_fMX,PLL_DIV_2,PLL_MUL_12);
//	CLK_PLL_Start();
//	usb_cpu_delay_xms(2);
//	CLK_UPLL_Start();
//	usb_cpu_delay_xms(2);
//	CLK_Fclk_Select(MAINCLK_FPLL);
    CLK_Fclk_Select(MAINCLK_FIH);
		
//-----------------------------------------------------------------------
// WM8978 setting 
//-----------------------------------------------------------------------
	IIC11_Init();
	
	WM8978_Init();				//初始化WM8978
	WM8978_HPvol_Set(40,40);	//耳机音量设置
	WM8978_SPKvol_Set(60);		//喇叭音量设置
	WM8978_ADDA_Cfg(1,1);		//开启ADC, DAC
	WM8978_Input_Cfg(1,1,0);	//开启输入通道(MIC&LINE IN)
	WM8978_Output_Cfg(1,0);		//开启DAC输出 
	WM8978_MIC_Gain(46);		//MIC增益设置 
	WM8978_I2S_Cfg(2,0);		//飞利浦标准,16位数据长度
	
//-----------------------------------------------------------------------
// SSI I2S Format transceive
//-----------------------------------------------------------------------
	PCBZ_Init(PCBZ_CHANNEL_0, PCBZ_FMAIN_2); // PA00/CLKBUZ0 Output AUDIO MCK 12MHz		
	
#if 1
	//-------------------------------------------------------
  // Initial DMA Vector Table
  //-------------------------------------------------------
  DMAVEC->VEC[DMA_VECTOR_SSI_TX] = IISTX_DMA_CHANNEL;  // SSI TX IRQ
  DMAVEC->VEC[DMA_VECTOR_SSI_RX] = IISRX_DMA_CHANNEL;  // SSI RX IRQ

  //-------------------------------------------------------
  // SSI transmission: RAM --> FIFO
  // src address increment, dst address fixed
  //-------------------------------------------------------
  // word transfer
  DMAVEC->CTRL[IISTX_DMA_CHANNEL].DMACR = ((1 << FIFO_Pos) | (1 << SZ_Pos) | (0 << DAMOD_Pos) | (1 << SAMOD_Pos) | (0 << RPTSEL_Pos) | (0 << MODE_Pos)); 
  DMAVEC->CTRL[IISTX_DMA_CHANNEL].DMBLS = 8;
  DMAVEC->CTRL[IISTX_DMA_CHANNEL].DMACT = EP3_MAX_PKT_SIZE/(8*2);
  DMAVEC->CTRL[IISTX_DMA_CHANNEL].DMRLD = EP3_MAX_PKT_SIZE/(8*2);
  DMAVEC->CTRL[IISTX_DMA_CHANNEL].DMSAR = (uint32_t)((uint16_t*)&iistxbuff[0][0]);//(uint32_t)txbuf;
  DMAVEC->CTRL[IISTX_DMA_CHANNEL].DMDAR = (uint32_t)((uint16_t*)(&SSI->SSIFTDR));//(uint32_t)&SSIE0.SSIFTDR.HALF;

  //-------------------------------------------------------
  // SSI reception: FIFO --> RAM
  // src address fixed, dst address increment
  //-------------------------------------------------------
  // word transfer
  DMAVEC->CTRL[IISRX_DMA_CHANNEL].DMACR = ((1 << FIFO_Pos) | (1 << SZ_Pos) | (1 << DAMOD_Pos) | (0 << SAMOD_Pos) | (0 << RPTSEL_Pos) | (0 << MODE_Pos)); 
  DMAVEC->CTRL[IISRX_DMA_CHANNEL].DMBLS = 8;
  DMAVEC->CTRL[IISRX_DMA_CHANNEL].DMACT = EP3_MAX_PKT_SIZE/(8*2);
  DMAVEC->CTRL[IISRX_DMA_CHANNEL].DMRLD = EP3_MAX_PKT_SIZE/(8*2);
  DMAVEC->CTRL[IISRX_DMA_CHANNEL].DMSAR = (uint32_t)((uint16_t*)(&SSI->SSIFRDR));//(uint32_t)&SSIE0.SSIFRDR.HALF;
  DMAVEC->CTRL[IISRX_DMA_CHANNEL].DMDAR = (uint32_t)((uint16_t*)&iisrxbuff);

  /* Initial DMA Register */
  CGC->PER1   |= CGC_PER1_DMAEN_Msk;
  DMA->DMABAR = DMAVEC_BASE;
  DMA->DMAEN3 = 3<<6;
  
  iisdmacount = 0;//block 0
  INTC_ClearPendingIRQ(SSIDMATX_IRQn);
  INTC_EnableIRQ(SSIDMATX_IRQn);
  
#endif	
	
  SSI_Open(SSI_CH0);
  SSI_Start(SSI_CH0);
	
  usb_main(); /* USB sample application */

} /* End of function main() */

/***********************************************************************************************************************
* Function Name: SysTick Handler
* Description  : Decreament the g_ticks value
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void SysTick_Handler(void)
{
    g_ticks--;
}

/******************************************************************************
 End  Of File
 ******************************************************************************/

