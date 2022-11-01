#include "..\include\SH68F90.h"
#include "..\include\stdtype.h"
#include "..\include\mcu_def.h"
#include "..\include\pwm_control.h"
#include ".\include\Auser.h"
#include "..\include\CFG.h"
#include <intrins.h>
#include <string.h>
//U8 xdata Temp_Time;
//U8 xdata Temp_Time2;

//****************************************************
code const U8 Deal_PaoMa_1_Tab1	[55]=
{
	21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,	//21
	62,																		//1
	104,103,102,101,100,99,98,97,96,95,94,93,92,91,90,89,88,87,86,85,84,	//21
	42,43,43,44,45,46,47,48,49,50,51,52,		//12
	
};
code const U8 Deal_PaoMa_1_Tab2	[55]=
{
	125,125,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,			//22
	40,																	//1
	83,82,81,80,79,78,77,76,75,74,73,72,71,70,69,68,67,66,65,64,63,	//21
	21,22,23,24,25,26,27,28,29,30,						//10
	31,														//1	
};
code const U8 Deal_PaoMa_1_Tab3	[55]=
{
	125,125,125,	42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,	//21+3
	125,124,123,122,121,120,119,118,117,116,115,114,113,112,111,110,109,108,107,106,105,//21
	63,64,65,66,67,68,69,70,71,71,				//10
};
//****************************************
code const U8 Deal_PaoMa_2_Tab1	[30]=
{
	29,30,51,71,70,49,
	29,30,51,71,70,49,
	29,30,51,71,70,49,
	29,30,51,71,70,49,
	50,125,125,125,125,125,
	/*
	30,31,52,72,71,50,	//6
	30,31,52,72,71,50,	//6
	30,31,52,72,71,50,	//6
	30,31,52,72,71,50,	//6
	51,125,125,125,125,125,
	*/
	
};
//****************************************
code const U8 Deal_PaoMa_3_Tab1	[6]=
{
	8,29,49,70,91,113,
};
code const U8 Deal_PaoMa_3_Tab2	[6]=
{
	10,32,53,73,93,114,
};
//****************************************
void Deal_PaoMa_1(void)
{
	U8 i,i1,j;
	U8 j1,j2,j3,n;
	if(!b_PaoMa1_Mode)
		return;
			j=Speed_Data;	
	if(b_PaoMa2)
		j=j*3;
	Temp_Speed++;
	if(Temp_Speed>j)
	{
		Temp_Speed=0;
		if(b_PaoMa1)		//ÅÜÂí
		{	
			i=Deal_PaoMa_1_Tab1[Run_Time];
			Change_AColor_Time(i);	//Give_NUM_Image(i,Color_Times,50*Brightness_Wheels);
			i=Deal_PaoMa_1_Tab2[Run_Time];
			Change_AColor_Time(i);	//Give_NUM_Image(i,Color_Times,50*Brightness_Wheels);
			i=Deal_PaoMa_1_Tab3[Run_Time];
			Change_AColor_Time(i);	//Give_NUM_Image(i,Color_Times,50*Brightness_Wheels);
			
			Deal_K45_Image();
			Run_Time++;	
			if(Run_Time>55)
			{	
				Run_Time=0;	
				b_PaoMa2=1;
				b_PaoMa1=0;
			}
		}
		else if(b_PaoMa2)
		{
			i=Deal_PaoMa_2_Tab1[Run_Time];
			Change_AColor_Time(i);	//Give_NUM_Image(i,Color_Times,50*Brightness_Wheels);
			Run_Time++;	
			if(Run_Time>30)
			{	
				Run_Time=0;	
				b_PaoMa2=0;
				b_PaoMa1=0;
				b_PaoMa3=1;	
				PaoHeng_Image_Num[9]=50;
				Image_Num_Times[9]=0;
			}
			
		}
		else if(b_PaoMa3)
		{
			Image_Num_Times[9]++;
			if(Image_Num_Times[9]>27)
			{
				Image_Num_Times[9]=0;
				PaoHeng_Image_Num[9]=0;
				Run_Time=0;	
				b_PaoMa2=0;
				b_PaoMa1=1;
				b_PaoMa3=0;	
			}
			else
			{
				Heng_Temp_NUM=PaoHeng_Image_Num[9];
				Temp_Image_Time=Image_Num_Times[9];
				Deal_Pao_Heng_Data();
			}
		}
	}
}
