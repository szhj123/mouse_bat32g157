#include "..\include\SH68F90.h"
#include "..\include\stdtype.h"
#include "..\include\mcu_def.h"
#include "..\include\pwm_control.h"
#include ".\include\Auser.h"
#include "..\include\CFG.h"
#include <intrins.h>
#include <string.h>
bit	b_PaoMa1;
bit	b_PaoMa2;
bit	b_PaoMa3;
bit	b_PaoMa4;
code const U8 Deal_PaoMa_21_Tab0	[139]=
{
	14,13,12,11,10,9,8,7,6,5,4,3,2,1,0,
	21,42,63,84,105,
	106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,
	104,83,62,41,
	40,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,
	43,64,85,
	86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,
	82,61,60,59,58,57,56,55,54,53,52,51,50,49,48,47,46,45,44,
	65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,
	
	60,59,58,57,56,55,54,55,54,53,52,51,
	125,125,125,125,125,125,125,
};
code const U8 Deal_PaoMa_21_Tab2	[30]=
{
	/*
	52,31,30,50,71,72,
	52,31,30,50,71,72,
	51,
	*/
	29,30,51,71,70,49,
	29,30,51,71,70,49,
	29,30,51,71,70,49,
	29,30,51,71,70,49,
	50,125,125,125,125,125,
};
//------------------------------------------------------------------
//------------------------------------------------------------------
code const U8 Deal_PaoMa_21_Tab3_1_U	[9]=
{
	50,49,48,47,46,45,44,43,42,
};
code const U8 Deal_PaoMa_21_Tab3_2_U	[10]=
{
	125,71,70,69,68,67,66,65,64,63,
};
code const U8 Deal_PaoMa_21_Tab3_3_U	[11]=
{
	125,30,29,28,27,26,25,24,23,22,21,
};
code const U8 Deal_PaoMa_21_Tab3_4_U	[11]=
{
	125,125,92,91,90,89,88,87,86,85,84,
};
code const U8 Deal_PaoMa_21_Tab3_5_U	[12]=
{
	125,125,9,8,7,6,5,4,3,2,1,0,
};
code const U8 Deal_PaoMa_21_Tab3_6_U	[11]=
{
	125,125,125,
	113,112,110,109,108,107,106,105,
};
//------------------------------------------------------------------
code const U8 Deal_PaoMa_21_Tab3_1_D	[11]=
{
	52,53,54,55,56,57,58,59,60,61,62,
};
code const U8 Deal_PaoMa_21_Tab3_2_D	[13]=
{
	125,72,73,74,75,76,77,78,79,80,81,82,83,
};
code const U8 Deal_PaoMa_21_Tab3_3_D	[12]=
{
	125,31,32,33,34,35,36,37,38,39,40,41,
};
code const U8 Deal_PaoMa_21_Tab3_4_D	[14]=
{
	125,125,93,94,95,96,97,98,99,100,101,102,103,104,
};
code const U8 Deal_PaoMa_21_Tab3_5_D	[13]=
{
	125,125,10,11,12,13,14,15,16,17,18,19,20,
};
code const U8 Deal_PaoMa_21_Tab3_6_D	[14]=
{
	125,125,125,
	114,115,116,117,118,119,120,121,122,123,124,
};
//***************K801 型跑马*************************
void Deal_PaoMa_2(void)
{
	U8 i,j;
	U8 n;
	if(b_PaoMa2_Mode)
	{
			j=Speed_Data+2;		
		if(b_PaoMa1)		//跑马
		{		
			Temp_Speed++;
			if(Temp_Speed>j)
			{
				Temp_Speed=0;
				if(Run_Time<145)
				{	
					i=Deal_PaoMa_21_Tab0[Run_Time];
					Change_AColor_Time(i);
					Deal_K45_Image();
				}
				Run_Time++;	
				if(Run_Time>139)
				{	
					Run_Time=0;
					b_PaoMa2=1;
					b_PaoMa1=0;
				}
				
			}
		}
		else if(b_PaoMa2)	//花型
		{
			Temp_Speed++;
			if(Temp_Speed>j+4)
			{
				Temp_Speed=0;
				if(Run_Time<30)
				{	
					i=Deal_PaoMa_21_Tab2[Run_Time];
					Change_AColor_Time(i);
					Deal_K45_Image();
				}
				Run_Time++;	
				if(Run_Time>30)
				{	
					Run_Time=0;
					b_PaoMa2=0;
					b_PaoMa1=0;
					b_PaoMa3=1;
				}
			}
		}
		else if(b_PaoMa3)	//散开
		{
			Temp_Speed++;
			if(Temp_Speed>j*3)
			{	
				Temp_Speed=0;
				if(Run_Time<9)
				{	
					i=Deal_PaoMa_21_Tab3_1_U[Run_Time];
					Change_AColor_Time(i);
				}
				if(Run_Time<10)
				{	
					i=Deal_PaoMa_21_Tab3_2_U[Run_Time];
					Change_AColor_Time(i);	
				}
				if(Run_Time<11)
				{	
					i=Deal_PaoMa_21_Tab3_3_U[Run_Time];
					Change_AColor_Time(i);	
					i=Deal_PaoMa_21_Tab3_4_U[Run_Time];
					Change_AColor_Time(i);
					i=Deal_PaoMa_21_Tab3_6_U[Run_Time];
					Change_AColor_Time(i);
					i=Deal_PaoMa_21_Tab3_1_D[Run_Time];
					Change_AColor_Time(i);
				}
				if(Run_Time<12)
				{	
					i=Deal_PaoMa_21_Tab3_5_U[Run_Time];
					Change_AColor_Time(i);
					i=Deal_PaoMa_21_Tab3_3_D[Run_Time];
					Change_AColor_Time(i);
				}
				if(Run_Time<13)
				{	
					i=Deal_PaoMa_21_Tab3_2_D[Run_Time];
					Change_AColor_Time(i);
					i=Deal_PaoMa_21_Tab3_5_D[Run_Time];
					Change_AColor_Time(i);
				}
				if(Run_Time<14)
				{	
					i=Deal_PaoMa_21_Tab3_4_D[Run_Time];
					Change_AColor_Time(i);
					i=Deal_PaoMa_21_Tab3_6_D[Run_Time];
					Change_AColor_Time(i);
				}
				Deal_K45_Image();
				Run_Time++;
				if(Run_Time>25)
				{
					Run_Time=0;
					b_PaoMa4=1;
					b_PaoMa3=0;
					b_PaoMa2=0;
					b_PaoMa1=0;
				}
			}
		}
		else if(b_PaoMa4)	
		{	
			Temp_Speed++;
			if(Temp_Speed>j)
			{
					Temp_Speed=0;
				//---------------------------------
					Run_Time=0;
					b_PaoMa2=0;
					b_PaoMa3=0;
					b_PaoMa4=0;
					b_PaoMa1=1;
			}
		}
	}
}