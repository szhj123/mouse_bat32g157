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
#include "usb.h"

#include "usb_pcdc_apl.h"
#include "fmc_user.h"


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
//  MD_STATUS status;
    uint32_t msCnt; 	// count value of 1ms
		uint32_t i, cnt = 0;
//-----------------------------------------------------------------------
// PCLBUZ0 output
//-----------------------------------------------------------------------
//    PCBZ->CKS0  = 0x03;    	// FMAIN/2^3
//    PORT->PMA  &= ~(1 << 0); // PA00 output mode
//    PORT->PMCA  &= ~(1 << 0); // PA00 Digital
//    PCBZ->CKS0  = 0x83;    	// FMAIN/2^3

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

		//set PB4 as input
		PORT->PMB |= 1 << 4;
		PORT->PUB |= 1 << 4;
		PORT->PMCB &= ~(1 << 4);
		for(i = 0; i < 100; i++)
		{
			if((PORT->PREADB & (1 << 4)) != 0x10)//key pressed
			{
				cnt++;
			}
		}
//		if(cnt < 20)	//if PB04 not pressed(input low), jump to APP
		if(0)
		{
				__disable_irq();
				//jump to APP
				__set_MSP(*(__IO uint32_t*) FMC_APROM_BASE);
				((void (*)()) (*(volatile unsigned long *)(FMC_APROM_BASE+0x04)))();//to APP
				while(1)
				{}
		}
		//stay in boot
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

