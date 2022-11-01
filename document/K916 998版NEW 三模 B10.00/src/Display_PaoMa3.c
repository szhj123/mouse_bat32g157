#include "..\include\SH68F90.h"
#include "..\include\stdtype.h"
#include "..\include\mcu_def.h"
#include "..\include\pwm_control.h"
#include ".\include\Auser.h"
#include "..\include\CFG.h"
#include <intrins.h>
#include <string.h>
//****************************************************
code const U8 Deal_PaoMa_3_U_Tab1	[37]=
{	
	21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,	//21	
	62,61,60,59,58,57,56,55,54,53,		//10
	31,30,50,71,72,						//5
	52,
};
code const U8 Deal_PaoMa_3_U_Tab2	[37]=
{
	125,125,															//2
	0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,		//21
	41,40,39,38,37,36,35,34,33,32,31,30,50,71,					//14
};
code const U8 Deal_PaoMa_3_U_Tab3	[37]=
{
	125,125,																	//2
	42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,	//21
	83,82,81,80,79,78,77,76,75,74,73,72,71,50,							//14
};
//-----------------------------------------------------------
code const U8 Deal_PaoMa_3_D_Tab1	[37]=
{
	104,103,102,101,100,99,98,97,96,95,94,93,92,91,90,89,88,87,86,85,84,	//21
	63,64,65,66,67,68,69,70,71,72,		//10
	52,31,30,71,72,			//5
	52,							//1
};
code const U8 Deal_PaoMa_3_D_Tab2	[37]=
{
	125,125,																			//2
	125,124,123,122,121,120,119,118,117,116,115,114,113,112,111,110,109,108,107,106,105,	//21
	84,85,86,87,88,89,90,91,92,93,		//10
	125,125,125,125,					//1
};
code const U8 Deal_PaoMa_3_D_Tab3	[37]=
{
	125,125,																			//2
	83,82,81,80,79,78,77,76,75,74,73,72,71,70,69,68,67,66,65,64,63,			//21
	42,43,44,45,46,47,48,49,50,30,31,52,72,71,	//14
};
//--------------------------------------------------------------
code const U8 Deal_PaoMa_3_2_Tab1	[18]=
{
	52,72,71,50,30,31,	//6
	52,72,71,50,30,31,	//6
	52,125,125,125,125,125,			//6
};
code const U8 Deal_PaoMa_3_2_Tab2	[18]=
{
	125,125,		//2
	53,73,93,92,91,70,49,29,8,9,10,32,	//	11
	53,73,93,92,			//5
};
//******************************************
void Deal_PaoMa_3(void)
{
	U8 i,i1,j;
	if(!b_PaoMa3_Mode)
		return;
		Temp_Speed++;
	if(Temp_Speed>Speed_Data+3)
	{
		Temp_Speed=0;
		if(b_PaoMa1)		//ÅÜÂí
		{	
			i=Deal_PaoMa_3_U_Tab1[Run_Time];
			Change_AColor_Time(i);
			i=Deal_PaoMa_3_U_Tab2[Run_Time];
			Change_AColor_Time(i);
			i=Deal_PaoMa_3_U_Tab3[Run_Time];
			Change_AColor_Time(i);
			
			i=Deal_PaoMa_3_D_Tab1[Run_Time];
			Change_AColor_Time(i);
			i=Deal_PaoMa_3_D_Tab2[Run_Time];
			Change_AColor_Time(i);
			i=Deal_PaoMa_3_D_Tab3[Run_Time];
			Change_AColor_Time(i);
			Deal_K45_Image();
			Run_Time++;	
			if(Run_Time>36)
			{	
				Run_Time=0;	
				b_PaoMa2=1;
				b_PaoMa1=0;
			}
		}
		else if(b_PaoMa2)
		{
			i=Deal_PaoMa_3_2_Tab1[Run_Time];
			Change_AColor_Time(i);	
			i=Deal_PaoMa_3_2_Tab2[Run_Time];
			Change_AColor_Time(i);	
			Deal_K45_Image();
			Run_Time++;	
			if(Run_Time>18)
			{	
				Run_Time=0;	
				b_PaoMa2=0;
				b_PaoMa1=0;
				b_PaoMa3=1;	
				PaoHeng_Image_Num[9]=51;
				Image_Num_Times[9]=0;
			}
			
		}
		else if(b_PaoMa3)
		{
			Image_Num_Times[9]++;
			if(Image_Num_Times[9]>28)
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
//********************************************
code const U8 Deal_PaoMa_4_Tab1	[126]=
{
	0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,
	41,40,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,
	42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,
	83,82,81,80,79,78,77,76,75,74,73,72,71,70,69,68,67,66,65,64,63,
	84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,
	125,124,123,122,121,120,119,118,117,116,115,114,113,112,111,110,109,108,107,106,105,
};
void Deal_PaoMa_4(void)
{
	U8 i,i1,j;
	if(!b_PaoMa4_Mode)
		return;
		Temp_Speed++;
	if(Temp_Speed>Speed_Data+3)
	{
		Temp_Speed=0;
		if(b_PaoMa1)		//ÅÜÂí
		{	
			i=Deal_PaoMa_4_Tab1[Run_Time];
			Change_AColor_Time(i);
			Run_Time++;	
			if(Run_Time>125)
			{	
				Run_Time=0;	
				b_PaoMa2=0;
				b_PaoMa1=1;
			}
		}
	}
}








