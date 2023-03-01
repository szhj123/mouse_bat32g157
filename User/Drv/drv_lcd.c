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
    Drv_Lcd_Delay_US(1000*25);
	LCD_RST_LOW();
	Drv_Lcd_Delay_US(10000*25);
	LCD_RST_HIGH();
	Drv_Lcd_Delay_US(120000*25);

    Drv_Lcd_Wr_Cmd(0x36); 
    Drv_Lcd_Wr_Data(0x00);

    Drv_Lcd_Wr_Cmd(0x3A); 
    Drv_Lcd_Wr_Data(0x55);

    Drv_Lcd_Wr_Cmd(0xB2);
    Drv_Lcd_Wr_Data(0x0C);
    Drv_Lcd_Wr_Data(0x0C);
    Drv_Lcd_Wr_Data(0x00);
    Drv_Lcd_Wr_Data(0x33);
    Drv_Lcd_Wr_Data(0x33);

    Drv_Lcd_Wr_Cmd(0xB7); 
    Drv_Lcd_Wr_Data(0x02);  

    Drv_Lcd_Wr_Cmd(0xBB);
    Drv_Lcd_Wr_Data(0x35);

    Drv_Lcd_Wr_Cmd(0xC0);
    Drv_Lcd_Wr_Data(0x2C);

    Drv_Lcd_Wr_Cmd(0xC2);
    Drv_Lcd_Wr_Data(0x01);

    Drv_Lcd_Wr_Cmd(0xC3);
    Drv_Lcd_Wr_Data(0x12);   

    Drv_Lcd_Wr_Cmd(0xC4);
    Drv_Lcd_Wr_Data(0x20);  

    Drv_Lcd_Wr_Cmd(0xC6); 
    Drv_Lcd_Wr_Data(0x0F);    

    Drv_Lcd_Wr_Cmd(0xD0); 
    Drv_Lcd_Wr_Data(0xA4);
    Drv_Lcd_Wr_Data(0xA2);

    Drv_Lcd_Wr_Cmd(0xE0);
    Drv_Lcd_Wr_Data(0xD0);   //V0[7-4] & V63[3-0]
    Drv_Lcd_Wr_Data(0x06);   //V62[5-0]
    Drv_Lcd_Wr_Data(0x0C);   //V61[5-0]
    Drv_Lcd_Wr_Data(0x09);   //V59[4-0]
    Drv_Lcd_Wr_Data(0x09);   //V57[4-0]
    Drv_Lcd_Wr_Data(0x25);   //J1[5-4] & V50[3-0]
    Drv_Lcd_Wr_Data(0x2E);   //V43[6-0]
    Drv_Lcd_Wr_Data(0x33);   //V27[6-4] & V36[2-0]
    Drv_Lcd_Wr_Data(0x45);   //V20[6-0]
    Drv_Lcd_Wr_Data(0x36);   //J0[5-4] & V13[3-0]
    Drv_Lcd_Wr_Data(0x12);   //V6[4-0]
    Drv_Lcd_Wr_Data(0x12);   //V4[4-0]
    Drv_Lcd_Wr_Data(0x2E);   //V2[5-0]
    Drv_Lcd_Wr_Data(0x34);   //V1[5-0]

    Drv_Lcd_Wr_Cmd(0xE1);
    Drv_Lcd_Wr_Data(0xD0);   //V0[7-4] & V63[3-0]
    Drv_Lcd_Wr_Data(0x06);   //V62[5-0]
    Drv_Lcd_Wr_Data(0x0C);   //V61[5-0]
    Drv_Lcd_Wr_Data(0x09);   //V59[4-0]
    Drv_Lcd_Wr_Data(0x09);   //V57[4-0]
    Drv_Lcd_Wr_Data(0x25);   //J1[5-4] & V50[3-0]
    Drv_Lcd_Wr_Data(0x2E);   //V43[6-0]
    Drv_Lcd_Wr_Data(0x33);   //V27[6-4] & V36[2-0]
    Drv_Lcd_Wr_Data(0x45);   //V20[6-0]
    Drv_Lcd_Wr_Data(0x36);   //J0[5-4] & V13[3-0]
    Drv_Lcd_Wr_Data(0x12);   //V6[4-0]
    Drv_Lcd_Wr_Data(0x12);   //V4[4-0]
    Drv_Lcd_Wr_Data(0x2E);   //V2[5-0]
    Drv_Lcd_Wr_Data(0x34);   //V1[5-0]

    Drv_Lcd_Wr_Cmd(0x21); 

    Drv_Lcd_Wr_Cmd(0x11); 
    Drv_Lcd_Delay_US(120000*25);

    Drv_Lcd_Wr_Cmd(0x29);     
}

void Drv_Lcd_Read_Id(void )
{
    uint8_t buf[4] = {0};
    
    Drv_Lcd_Wr_Cmd(0x04);

    Drv_Lcd_Rd_Data(buf, 4);
}

void Drv_Lcd_Clr(uint16_t color, lcd_isr_callback_t callback )
{
    Drv_Lcd_Set_Position(0, 0, LCD_W-1,LCD_H-1);

    Hal_Lcd_Set_BgColor(color, callback);
}


void Drv_Lcd_Show_Pic(uint8_t picId, lcd_isr_callback_t callback )
{
    uint32_t flashAddr = picId * ERASE_64K_BLOCK_SIZE * 2;
    
    Drv_Lcd_Set_Position(0, 0, LCD_W-1,LCD_H-1);

    Hal_Lcd_Show_Pic(flashAddr, callback);
}


void Drv_Lcd_Set_Position(uint16_t startX, uint16_t startY, uint16_t endX, uint16_t endY )
{
	Drv_Lcd_Wr_Cmd(0x2A);
	Drv_Lcd_Wr_Data(startX>>8);
	Drv_Lcd_Wr_Data(startX&0xff);
	Drv_Lcd_Wr_Data(endX>>8);
	Drv_Lcd_Wr_Data(endX&0xff);
    
	Drv_Lcd_Wr_Cmd(0x2B);
	Drv_Lcd_Wr_Data(startY>>8);
	Drv_Lcd_Wr_Data(startY&0xff);
	Drv_Lcd_Wr_Data(endY>>8);
	Drv_Lcd_Wr_Data(endY&0xff);
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

void Drv_Lcd_Write_Multi_Data(uint16_t *buf, uint16_t size )
{
	uint16_t i;
    
    LCD_CS_LOW();
	LCD_DC_HIGH();

    for(i = 0; i < size; i++)
	{        
		Write_LBDATA(buf[i]);
	}

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


