#include "..\include\SH68F90.h"
#include "..\include\stdtype.h"
#include "..\include\mcu_def.h"
#include "..\include\pwm_control.h"
#include ".\include\Auser.h"
#include "..\include\CFG.h"
#include <intrins.h>
#include <string.h>
U8	xdata	PaoHeng_Image_Num[10];
U8	xdata	Image_Num_Times[10];//5
U16 xdata	b_Heng_Mode;
U8	xdata	Temp_Image_Time;
U8 xdata 	Heng_Temp_NUM;
U8 xdata 	Data_10;
//*******************************************
void Deal_Image_Num2(U8 PaoHeng_Index)
{
	U8 i,j;
	U32 i1;
	i1=0x0001;
	for(i=0;i<10;i++)		
	{
		if((b_Heng_Mode&i1)==0)
		{
			Deal_Tbl_Image(PaoHeng_Index);
			j=Deal_Down_K45_Image(Image_Num);
			PaoHeng_Image_Num[i]=j;
			b_Heng_Mode|=i1;
			Image_Num_Times[i]=0;
			break;
		}
		i1=i1<<1;
	}	
}
//***********************************************
void Deal_Pao_Heng_Data(void)
{
	U8 i,j,n;
	//for(i=0;i<6;i++)		
	if((Heng_Temp_NUM>=0)&&(Heng_Temp_NUM<=20))	
		n=0;
	else if((Heng_Temp_NUM>=21)&&(Heng_Temp_NUM<=41))	
		n=1;
	else if((Heng_Temp_NUM>=42)&&(Heng_Temp_NUM<=62))	
		n=2;
	else if((Heng_Temp_NUM>=63)&&(Heng_Temp_NUM<=83))		
		n=3;
	else if((Heng_Temp_NUM>=84)&&(Heng_Temp_NUM<=104))		
		n=4;
	else if((Heng_Temp_NUM>=105)&&(Heng_Temp_NUM<=125))	
		n=5;
	//LR	
	if(Temp_Image_Time==1)
	{
		i=Heng_Temp_NUM;
		j=Heng_Temp_NUM;
		KeyDown_Image2(i,n);
		KeyDown_Image2(j,n);
	}	
	{
		i=Heng_Temp_NUM-Temp_Image_Time;
		j=Heng_Temp_NUM+Temp_Image_Time;
		KeyDown_Image2(i,n);
		KeyDown_Image2(j,n);
	}
	//Up 
	if(b_Pao_Heng|b_HengMie_Mode|b_PaoMa3_Mode|b_PaoMa1_Mode)
	{
		if(Temp_Image_Time>1)
		{	
			i=(Heng_Temp_NUM-21)-Temp_Image_Time+2;
			KeyDown_Image2(i,n-1);
			j=(Heng_Temp_NUM-21)+Temp_Image_Time-2;
			KeyDown_Image2(j,n-1);
			
			i=(Heng_Temp_NUM+21)-Temp_Image_Time+2;
			KeyDown_Image2(i,n+1);
			j=(Heng_Temp_NUM+21)+Temp_Image_Time-2;
			KeyDown_Image2(j,n+1);
		}
		if(Temp_Image_Time>2)
		{	
			i=(Heng_Temp_NUM-42)-Temp_Image_Time+3;
			KeyDown_Image2(i,n-2);
			j=(Heng_Temp_NUM-42)+Temp_Image_Time-3;
			KeyDown_Image2(j,n-2);
			
			i=(Heng_Temp_NUM+42)-Temp_Image_Time+3;
			KeyDown_Image2(i,n+2);
			j=(Heng_Temp_NUM+42)+Temp_Image_Time-3;
			KeyDown_Image2(j,n+2);
		}
		if(Temp_Image_Time>3)
		{	
			i=(Heng_Temp_NUM-63)-Temp_Image_Time+4;
			KeyDown_Image2(i,n-3);
			j=(Heng_Temp_NUM-63)+Temp_Image_Time-4;
			KeyDown_Image2(j,n-3);
			
			i=(Heng_Temp_NUM+63)-Temp_Image_Time+4;
			KeyDown_Image2(i,n+3);
			j=(Heng_Temp_NUM+63)+Temp_Image_Time-4;
			KeyDown_Image2(j,n+3);
		}
		if(Temp_Image_Time>4)
		{	
			i=(Heng_Temp_NUM-84)-Temp_Image_Time+5;
			KeyDown_Image2(i,n-4);
			j=(Heng_Temp_NUM-84)+Temp_Image_Time-5;
			KeyDown_Image2(j,n-4);
			
			i=(Heng_Temp_NUM+84)-Temp_Image_Time+5;
			KeyDown_Image2(i,n+4);
			j=(Heng_Temp_NUM+84)+Temp_Image_Time-5;
			KeyDown_Image2(j,n+4);
		}
		if(Temp_Image_Time>5)
		{	
			i=(Heng_Temp_NUM-105)-Temp_Image_Time+6;
			KeyDown_Image2(i,n-5);
			j=(Heng_Temp_NUM-105)+Temp_Image_Time-6;
			KeyDown_Image2(j,n-5);
			
			i=(Heng_Temp_NUM+105)-Temp_Image_Time+6;
			KeyDown_Image2(i,n+5);
			j=(Heng_Temp_NUM+105)+Temp_Image_Time-6;
			KeyDown_Image2(j,n+5);
		}
	}
	
}
//**************************************************
void Deal_Mode_5(void)
{
	//U8	i,j;
	U8	i1;
	U8 	i3;
	U16 i2;
	if(b_Pao_Heng|b_HangPao_Mode|b_Flower_Mode|b_HengMie_Mode)
	{
			Temp_Speed++;	
		if(Temp_Speed>Speed_Data+2)	
		{
			Temp_Speed=0;
			i2=0x0001;	
			for(i3=0;i3<10;i3++)		
			{
				if(b_Heng_Mode&i2)
				{
					Image_Num_Times[i3]++;
					if(Image_Num_Times[i3]>28)
					{
						Image_Num_Times[i3]=0;
						b_Heng_Mode&=~i2;
						PaoHeng_Image_Num[i3]=0;
					}
					else
					{
						Heng_Temp_NUM=PaoHeng_Image_Num[i3];
						Temp_Image_Time=Image_Num_Times[i3];
						Deal_Pao_Heng_Data();
					}
				}
				i2=i2<<1;
			}		
		}
	}
}