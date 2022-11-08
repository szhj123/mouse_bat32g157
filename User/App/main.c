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

#include "drv_spi_flash.h"
#include "drv_mouse_sensor.h"

#include "app_mouse_protocol.h"
#include "app_key.h"
#include "app_light.h"
#include "app_lcd.h"
#include "app_event.h"
/* Private typedef --------------------------------------*/
/* Private define ---------------------------------------*/
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
void Clk_Init(void );
/* Private variables ------------------------------------*/

uint32_t buf[128];


int main (void)
{
    //Clk_Init();

    SystemCoreClockUpdate();

    Drv_Task_Init();

    Drv_Timer_Init();

    App_Mouse_Init();

    //Drv_Mouse_Sensor_Init();

    //Drv_Spi_Flash_Init();

    ///App_Lcd_Init();

    App_Light_Init();

    App_Key_Init();

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


void usb_cpu_delay_1us (uint16_t time)
{
    uint16_t sf_cnt;
    sf_cnt = time * 20;

    while(sf_cnt)
    {
        sf_cnt --;
    }
}

void usb_cpu_delay_xms(uint32_t n)
{
    uint32_t i;

    for(i=0;i<n;i++)
    {
        usb_cpu_delay_1us(1000);
    }
}


