/********************************************************
* @file       main.c
* @author     szhj13
* @version    V1.0
* @date       2022-05-18
* @brief      the start address of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "hal_bat32g157.h"
#include "drv_task.h"
#include "drv_timer.h"
#include "drv_lcd.h"

#include "drv_spi_flash.h"

#include "app_event.h"
/* Private typedef --------------------------------------*/
/* Private define ---------------------------------------*/
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
void Clk_Init(void );
/* Private variables ------------------------------------*/

int main (void)
{
	Clk_Init();

    Drv_Task_Init();

    Drv_Timer_Init();

    Drv_Spi_Flash_Init();

    Drv_Lcd_Init();

    App_Event_Init();
	
    Usb_Init(); 

    while(1)
    {
        Drv_Task_Schedule();
    }
} 

void Clk_Init(void )
{
    uint32_t waitCnt;
    
    //HOCO = 32MHz / fIH = 8MHz, UPLL = 48MHz, fclk = 64MHz
    CLK_Fclk_Select(MAINCLK_FIH);
    CLK_PLL_Setting(PLL_SR_fIH,PLL_DIV_2,PLL_MUL_16);
    CLK_UPLL_Setting(PLL_SR_fIH,PLL_DIV_2,PLL_MUL_12);
    CLK_PLL_Start();
    waitCnt = 10000;
    while(waitCnt--);
    CLK_UPLL_Start();
    waitCnt = 10000;
    while(waitCnt--);
    CLK_Fclk_Select(MAINCLK_FPLL);

    SystemCoreClock = 64000000;
}

