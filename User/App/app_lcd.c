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
static uint8_t lcdTestFlag;

void App_Lcd_Init(void )
{
    Drv_Lcd_Init();    

    Drv_Lcd_Clr(YELLOW, App_Lcd_Clr_Callback);
    while(!lcdTestFlag);
        lcdTestFlag = 0;
    
    #if 1
    Drv_Lcd_Show_Pic(5, App_Lcd_Clr_Callback);
    while(!lcdTestFlag);
    lcdTestFlag = 0;
    #endif 
    
}

static void App_Lcd_Clr_Callback(void )
{
    lcdTestFlag = 1;
}

