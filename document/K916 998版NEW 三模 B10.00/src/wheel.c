#include "..\include\SH68F90.h"
#include "..\include\stdtype.h"
#include "..\include\CFG.h"
#include "..\include\Auser.h"
#include "..\include\pwm_control.h"
#include "..\include\mcu_def.h"
#include <intrins.h>
#include <string.h>

U8 bdata wheel_now;
	sbit  wheel_now1 = wheel_now ^ 0;
	sbit  wheel_now2 = wheel_now ^ 1; 
U8 idata wheel_pre;
U8 idata wheel_status;
U8 xdata	Multimedia_Wheel_Data;
U8 xdata	Multimedia_Wheel_Data2;

U8 data	Multimedia_Add;
U8 data	Multimedia_Sub;
void Wheel_Check(void)
{
	
	WHEEL_DirIn;	// wheel direction input
	WHEEL_PullEn;	// enable wheel pull high 
	delay_us(5);
	wheel_now = 0x00;
	Multimedia_Wheel_Data=0x00;
		wheel_now1 = WHEEL1;
		wheel_now2 = WHEEL2;
		if(wheel_now != wheel_pre)
		{
			wheel_status = ((wheel_status << 2) & 0x3C) | (wheel_now & 0x03);
			switch(wheel_status)
			{
				case 0x38:
				case 0x07:
						Multimedia_Wheel_Data=0xE9;
						break;
				case 0x34:
				case 0x0b:
						Multimedia_Wheel_Data=0xEA;
						break;
			}
			wheel_pre = wheel_now;
		}

		if(Multimedia_Wheel_Data!=Multimedia_Wheel_Data2)
		{
			if(Multimedia_Wheel_Data==0xEA)
				{
					Multimedia_Sub++;	//Brightness_Sub();
				}	
				else if(Multimedia_Wheel_Data==0xE9)
				{
					Multimedia_Add++;	//Brightness_Add();
				}
		}
} 
void Deal_Wheel(void)//鼠标滚轮控制音量大小
{
	if(Multimedia_Add)
	{
		Multimedia_Add--;
		Multimedia_Tab_Data(5);//增大音量
	}
	else if(Multimedia_Sub)
	{
		Multimedia_Sub--;
		Multimedia_Tab_Data(6);//减小音量
	}
}

