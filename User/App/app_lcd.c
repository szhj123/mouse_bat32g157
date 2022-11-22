/********************************************************
* @file       app_lcd.c
* @author     szhj13
* @version    V1.0
* @date       2022-05-18
* @brief      the start address of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "app_lcd.h"

/* Private typedef --------------------------------------*/
/* Private define ---------------------------------------*/
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
static void App_Lcd_Clr_Callback(void );
/* Private variables ------------------------------------*/
uint8_t rxBuf[60] = {0};
static uint8_t lcdTestFlag;

void App_Lcd_Init(void )
{
    Drv_Lcd_Init();    

    Drv_Lcd_Clr(YELLOW, App_Lcd_Clr_Callback);
    while(!lcdTestFlag);
        lcdTestFlag = 0;

    Drv_Lcd_Show_Pic(5, App_Lcd_Clr_Callback);
    while(!lcdTestFlag);
        lcdTestFlag = 0;

    

    
    #if 0
    uint32_t addr = 0xa0000;
    
    Drv_Lcd_Set_Position(0, 0, LCD_W-1,LCD_H-1);

    Drv_Lcd_Wr_Cmd(0x2c);

    do{
        Drv_Spi_Read(addr, rxBuf, sizeof(rxBuf));

        Drv_Lcd_Write_Multi_Data(rxBuf, 30);
        addr += 60;

        if(addr > 0xa0000+115000)
            addr = addr;
        
    }while(addr < (0xa0000+115200));

    #endif 
}

static void App_Lcd_Clr_Callback(void )
{
    lcdTestFlag = 1;
}

