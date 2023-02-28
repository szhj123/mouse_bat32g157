#ifndef _APP_LCD_H
#define _APP_LCD_H

#include "drv_lcd.h"

#include "app_mouse_protocol.h"

#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE         	 0x1F00  
#define BRED             0X1FF8
#define GRED 			 0XE0FF
#define GBLUE			 0XFF07
#define RED           	 0x00F8
#define MAGENTA       	 0x1FF8
#define GREEN         	 0xE007
#define CYAN          	 0xFF7F
#define YELLOW        	 0xE0FF
#define BROWN 			 0X40BC
#define BRRED 			 0X07FC 
#define GRAY  			 0X3084


void App_Lcd_Init(void );
void App_Lcd_Show_Pic(uint8_t picId );

#endif 

