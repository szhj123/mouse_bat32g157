#include "..\include\SH68F90.h"
#include "..\include\stdtype.h"
#include "..\include\mcu_def.h"
#include "..\include\pwm_control.h"
#include ".\include\Auser.h"
#include "..\include\CFG.h"
#include <intrins.h>
#include <string.h>
U8 xdata Temp_Speed;
code const U8 Deal_BoLang_0	[36]=
{
	0,21,42,63,84,105,
	105,84,63,42,21,0,
	0,21,42,63,84,105,
	105,84,63,42,21,0,
	0,21,42,63,84,105,
	105,84,63,42,21,0,
};
void Dispaly_BoLang_Mode(void)//ÏÔÊ¾²¨ÀËÄ£Ê½
{
	U8 i,j,j7;
	if(!b_BoLang_Mode)
		return;
	if(Speed_Data==0)
		j7=6;
	else if(Speed_Data==1)
		j7=8;
	else if(Speed_Data==2)
		j7=10;	
	else if(Speed_Data==3)
		j7=12;		
	else if(Speed_Data>=4)
		j7=14;		
		Temp_Speed++;
	if(Temp_Speed>j7)
	{
		Temp_Speed=0;
		Run_Time++;	
		if(Run_Time>=12)
			Run_Time=0;
		Clear_All_Image();
		for(j=0; j<21; j++)
		{
			Image_Num=Deal_BoLang_0[Run_Time+j+4]+j;
			//if(Brack_b(Image_Num))
			Change_AColor_Time(Image_Num);	
			Deal_K45_Image();	
		}
		
		j=Brack_b(17);
		j=Brack_b(18);
		j=Brack_b(19);
		j=Brack_b(20);
		
		j=Brack_b(43);
		j=Brack_b(44);
		j=Brack_b(45);
		j=Brack_b(52);
		j=Brack_b(110);
		j=Brack_b(114);
		
	}
}


