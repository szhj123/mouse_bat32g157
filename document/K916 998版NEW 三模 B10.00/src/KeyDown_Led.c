#include "..\include\SH68F90.h"
#include "..\include\stdtype.h"
#include "..\include\mcu_def.h"
#include "..\include\pwm_control.h"
#include ".\include\Auser.h"
#include "..\include\CFG.h"
#include <intrins.h>
#include <string.h>
U8 xdata 	KeyDown_Time[126];
void Deal_KeyDown(void)//灯的模式变换
{
	if(b_SuiLiang_Mode)	//灯的随亮模式=1（踏雪无痕模式）
	{	
			Deal_Tbl_Image(Key_Index);
		if(Brack_b(Image_Num))
		{	
			Change_AColor_Time(Image_Num);
		}
	}
	else if(b_Pao_Heng|b_HangPao_Mode|b_Flower_Mode|b_HengMie_Mode)
	{
		if(break_Data[Port_Data(Key_Index)]&Pin_Data(Key_Index))
		{	
			if(Brack_b(Image_Num))
				Deal_Image_Num2(Key_Index);
		}
	}
	else if(b_Record_Mode)
	{
		if(!bFn)//fn按键没按下
		{	
			Deal_Tbl_Image(Key_Index);
			if(break_Data[Port_Data(Key_Index)]&Pin_Data(Key_Index))
			{
				KeyDown_Time[Image_Num]++;
				if(KeyDown_Time[Image_Num]>7)
					KeyDown_Time[Image_Num]=1;
				if(KeyDown_Time[Image_Num]==7)
					Give_NUM_Image(Image_Num,KeyDown_Time[Image_Num],0);
				else
					Give_NUM_Image(Image_Num,KeyDown_Time[Image_Num],255);
			}	
		}
	}	
}
//**************************************
void Sacn_Key_Led_Up(void)
{
	U8 i,j,n;
			j=10;
	if(bSpeed_End)
		return;		
	if(b_SuiLiang_Mode)
	{	
		Temp_Speed++;
		if(Temp_Speed>Speed_Data)
		{
			Temp_Speed=0;	
			for(i=0;i<126;i++)
			{
				if(Brack_b(i))
				{
					if(Image[0][i]>PWM_AddData(0,i))
						Image[0][i]=Image[0][i]-Brightness_Wheels;
					if(Image[1][i]>PWM_AddData(1,i))
						Image[1][i]=Image[1][i]-Brightness_Wheels;
					if(Image[2][i]>PWM_AddData(2,i))
						Image[2][i]=Image[2][i]-Brightness_Wheels;
						
					if(Image[0][i]<PWM_AddData(0,i))	
						Image[0][i]=PWM_AddData(0,i);
					if(Image[1][i]<PWM_AddData(1,i))	
						Image[1][i]=PWM_AddData(1,i);	
					if(Image[2][i]<PWM_AddData(2,i))	
						Image[2][i]=PWM_AddData(2,i);	
						
				}	
			}
		}	
	}	
	else  if(b_Pao_Heng|b_HangPao_Mode|b_Flower_Mode|b_HengMie_Mode)
	{
		for(i=0;i<126;i++)
		{
			if(Brack_b(i))
			{	
				if(Image[0][i]>PWM_AddData(0,i))
					Image[0][i]=Image[0][i]-(Brightness_Wheels+9);
				if(Image[1][i]>PWM_AddData(1,i))
					Image[1][i]=Image[1][i]-(Brightness_Wheels+9);
				if(Image[2][i]>PWM_AddData(2,i))
					Image[2][i]=Image[2][i]-(Brightness_Wheels+9);
						
						
						
					if(Image[0][i]<PWM_AddData(0,i))	
						Image[0][i]=PWM_AddData(0,i);
					if(Image[1][i]<PWM_AddData(1,i))	
						Image[1][i]=PWM_AddData(1,i);	
					if(Image[2][i]<PWM_AddData(2,i))	
						Image[2][i]=PWM_AddData(2,i);	
			}
		}
	}	
	else if(b_PaoMa1_Mode|b_PaoMa2_Mode|b_PaoMa3_Mode|b_PaoMa4_Mode|b_Effect_light_1|b_Effect_light_2|b_Raindrops_Mode)
	{
		for(i=0;i<126;i++)
		{
			if(Brack_b(i))
			{	
				if(Image[0][i]>PWM_AddData(0,i))
						Image[0][i]=Image[0][i]-Brightness_Wheels-5;
					if(Image[1][i]>PWM_AddData(1,i))
						Image[1][i]=Image[1][i]-Brightness_Wheels-5;
					if(Image[2][i]>PWM_AddData(2,i))
						Image[2][i]=Image[2][i]-Brightness_Wheels-5;
						
					if(Image[0][i]<PWM_AddData(0,i))	
						Image[0][i]=PWM_AddData(0,i);
					if(Image[1][i]<PWM_AddData(1,i))	
						Image[1][i]=PWM_AddData(1,i);	
					if(Image[2][i]<PWM_AddData(2,i))	
						Image[2][i]=PWM_AddData(2,i);	
			}
		}
	}	
}