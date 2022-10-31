/***********************************************************************************************************************
* Copyright (C) . All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : main.c
* Version      :
* Device(s)    : BAT32G135
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
#include "sci.h"
#include "usb.h"

#include "usb_pmsc_apl.h"
#include "spiflash.h"

/***********************************************************************************************************************
Macro Definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
uint32_t g_ticks;

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

/**
usb_atapi_driver.c文件中的缓存
static uint8_t          gs_usb_pmsc_media_buffer[USB_ATAPI_BLOCK_UNIT * USB_CFG_PMSC_TRANS_COUNT];
需要根据实际应用情况进行调整，修改相关的宏定义USB_ATAPI_BLOCK_UNIT和USB_CFG_PMSC_TRANS_COUNT
	
！！！！使用此例程前，请将USB_ATAPI_BLOCK_UNIT定义为：0x1000，USB_CFG_PMSC_TRANS_COUNT定义为：2
	
因Flash的Sector大小为4K，在连接电脑进行格式化时，请选择分配的单元大小为4096
**/
	
		MD_STATUS status;
    uint32_t msCnt; 	// count value of 1ms

//-----------------------------------------------------------------------
// PCLBUZ0 output
//-----------------------------------------------------------------------
    // PCBZ->CKS0  = 0x03;    	// FMAIN/2^3
    // PORT->PMA  &= ~(1 << 0); // PA00 output mode
    // PORT->PMCA  &= ~(1 << 0); // PA00 Digital
    // PCBZ->CKS0  = 0x83;    	// FMAIN/2^3

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
//	CLK_PLL_Setting(PLL_SR_fIH,PLL_DIV_2,PLL_MUL_16);
//	CLK_UPLL_Setting(PLL_SR_fIH,PLL_DIV_2,PLL_MUL_12);
//	CLK_PLL_Start();
//	usb_cpu_delay_xms(2);
//	CLK_UPLL_Start();
//	usb_cpu_delay_xms(2);
//	CLK_Fclk_Select(MAINCLK_FPLL);
  CLK_Fclk_Select(MAINCLK_FIH);

#if 1
	status = UART0_Init(48000000U, 19200);
	if(status == MD_ERROR)
	{
		while(1);
	}
	
	printf("Hello, UART\n");
#endif

	SPI_INIT(SPI_MODE_0);	/* init spi*/
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

