#include "..\include\SH68F90.h"
#include "..\include\stdtype.h"
#include "..\include\mcu_def.h"
#include "..\include\pwm_control.h"
#include ".\include\Auser.h"
#include "..\include\CFG.h"
#include <intrins.h>
#include <string.h>

code const U8 Effect2_Tab0	[21]=
{
	0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,
};
code const U8 Effect2_Tab1	[22]=
{
	125,
	21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,
};
code const U8 Effect2_Tab2	[23]=
{
	125,125,
	42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,	
};
code const U8 Effect2_Tab3	[24]=
{
	125,125,125,
	63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,
};
code const U8 Effect2_Tab4	[25]=
{
	125,125,125,125,
	84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,
};
code const U8 Effect2_Tab5	[26]=
{
	125,125,125,125,125,
	105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,
};
///----------------------------------------------------------------------
code const U8 Effect2_Tab20	[21]=
{
	20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0,
};
code const U8 Effect2_Tab21	[23]=
{
	125,125,
	41,40,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,
};
code const U8 Effect2_Tab22	[24]=
{
	125,125,125,
	62,61,60,59,58,57,56,55,54,53,52,51,50,49,48,47,46,45,44,43,42,
};
code const U8 Effect2_Tab23	[25]=
{
	125,125,125,125,
	83,82,81,80,79,78,77,76,75,74,73,72,71,70,69,68,67,66,65,64,63,
};
code const U8 Effect2_Tab24	[26]=
{
	125,125,125,125,125,
	104,103,102,101,100,99,98,97,96,95,94,93,92,91,90,89,88,87,86,85,84,	
};
code const U8 Effect2_Tab25	[27]=
{
	125,125,125,125,125,125,
	125,124,123,122,121,120,119,118,117,116,115,114,113,112,111,110,109,108,107,106,105,	
};
//*****************************************
void Start_Effect_light_Time2(void)
{
		U8 i,i1,j,j1;
	if(!b_Effect_light_2)
		return;
	if(Speed_Data==0)
	{	
		j=1;
		j1=5;
	}
	else if(Speed_Data==1)
	{	
		j=2;
		j1=4;
	}
	else if(Speed_Data==2)
	{	
		j=3;	
		j1=3;
	}
	else if(Speed_Data==3)
	{	
		j=4;	
		j1=2;
	}	
	else if(Speed_Data>=4)
	{	
		j=5;	
		j1=1;
	}
	Temp_Speed++;
	if(Temp_Speed>j+2)
	{
		Temp_Speed=0;	
		if(b_PaoMa1)
		{		
			if(Run_Time<21)
			{	
				i=Effect2_Tab0[Run_Time];
				Change_AColor_Time(i);	//Deal_P7_Data(i,Run_Time);
			}
			////////////////////////////////////
			if(Run_Time<22)
			{	
				i=Effect2_Tab1[Run_Time];
				Change_AColor_Time(i);	//Deal_P7_Data(i,Run_Time);
			}
			////////////////////////////////////
			if(Run_Time<23)
			{	
				i=Effect2_Tab2[Run_Time];
				Change_AColor_Time(i);	//Deal_P7_Data(i,Run_Time);
			}
			////////////////////////////////////
			if(Run_Time<24)
			{	
				i=Effect2_Tab3[Run_Time];
				Change_AColor_Time(i);	//Deal_P7_Data(i,Run_Time);
			}
			////////////////////////////////////
			if(Run_Time<25)
			{	
				i=Effect2_Tab4[Run_Time];
				Change_AColor_Time(i);	//Deal_P7_Data(i,Run_Time);
			}
			////////////////////////////////////
			if(Run_Time<26)
			{	
				i=Effect2_Tab5[Run_Time];
				Change_AColor_Time(i);	//Deal_P7_Data(i,Run_Time);
			}
			////////////////////////////////////
			Deal_K45_Image();
			Run_Time++;	
			if(Run_Time>40+j1)
			{	
				Run_Time=0;	
				b_PaoMa2=1;
				b_PaoMa1=0;
			}
		}
		else if(b_PaoMa2)
		{
			if(Run_Time<21)
			{	
				i=Effect2_Tab20[Run_Time];
				Change_AColor_Time(i);	//Deal_P7_Data(i,Run_Time);
			}
			////////////////////////////////////
			if(Run_Time<23)
			{	
				i=Effect2_Tab21[Run_Time];
				Change_AColor_Time(i);	//Deal_P7_Data(i,Run_Time);
			}
			////////////////////////////////////
			if(Run_Time<24)
			{	
				i=Effect2_Tab22[Run_Time];
				Change_AColor_Time(i);	//Deal_P7_Data(i,Run_Time);
			}
			////////////////////////////////////
			if(Run_Time<25)
			{	
				i=Effect2_Tab23[Run_Time];
				Change_AColor_Time(i);	//Deal_P7_Data(i,Run_Time);
			}
			////////////////////////////////////
			if(Run_Time<26)
			{	
				i=Effect2_Tab24[Run_Time];
				Change_AColor_Time(i);	//Deal_P7_Data(i,Run_Time);
			}
			////////////////////////////////////
			if(Run_Time<27)
			{	
				i=Effect2_Tab25[Run_Time];
				Change_AColor_Time(i);	//Deal_P7_Data(i,Run_Time);
			}
			////////////////////////////////////
			Deal_K45_Image();
			Run_Time++;	
			if(Run_Time>40+j1)
			{	
				Run_Time=0;	
				b_PaoMa2=0;
				b_PaoMa1=1;
			}
		}
	}
}
