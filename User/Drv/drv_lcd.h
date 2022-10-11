#ifndef _DRV_LCD_H
#define _DRV_LCD_H

#include "hal_lcd.h"

void Drv_Lcd_Init(void );
void Drv_Lcd_Read_Id(void );
void Drv_Lcd_Wr_Cmd(uint8_t reg );
void Drv_Lcd_Wr_Data(uint8_t dat );
void Drv_Lcd_Rd_Data(uint8_t *buf, uint8_t length );


void Drv_Lcd_Delay_US(uint32_t us );

#endif 

