/********************************************************
* @file       drv_lcd.c
* @author     szhj13
* @version    V1.0
* @date       2022-05-18
* @brief      the start address of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "drv_lcd.h"

/* Private typedef --------------------------------------*/
/* Private define ---------------------------------------*/
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
/* Private variables ------------------------------------*/

void Drv_Lcd_Init(void )
{
    Hal_Lcd_Init();

    LCD_RST_HIGH();
    Drv_Lcd_Delay_US(1000*35);
	LCD_RST_LOW();
	Drv_Lcd_Delay_US(10000*35);
	LCD_RST_HIGH();
	Drv_Lcd_Delay_US(120000*35);

    Drv_Lcd_Read_Id();

}

void Drv_Lcd_Read_Id(void )
{
    uint8_t buf[4] = {0};
    
    Drv_Lcd_Wr_Cmd(0x04);

    Drv_Lcd_Rd_Data(buf, 4);
}

void Drv_Lcd_Wr_Cmd(uint8_t reg )
{
    LCD_CS_LOW();
	LCD_DC_LOW();
	
	Write_LBDATAL(reg);

	LCD_CS_HIGH();
}

void Drv_Lcd_Wr_Data(uint8_t dat )
{
    LCD_CS_LOW();
	LCD_DC_HIGH();
	
	Write_LBDATAL(dat);

	LCD_CS_HIGH();
}

void Drv_Lcd_Rd_Data(uint8_t *buf, uint8_t length )
{
    uint8_t i;
    
    LCD_CS_LOW();
	LCD_DC_HIGH();
    
    for(i=0;i<length;i++)
    {
        while(Read_LBCTL_BYF());
        buf[i] = LCDB->LBDATAL;
        while(Read_LBCTL_TPF());/* write LBDATAL */
    }
}

void Drv_Lcd_Delay_US(uint32_t us )
{
    while(--us);
}


