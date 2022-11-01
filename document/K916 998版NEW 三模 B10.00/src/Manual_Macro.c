#include "..\include\SH68F90.h"
#include "..\include\stdtype.h"
#include "..\include\CFG.h"
#include "..\include\Auser.h"
/*
U8 xdata	Manual_Record;
U8 xdata Manual_Record_UNM;
U8 xdata Last_Manual_data[7];
U8 xdata Manual_Time_Macro;
U8 xdata Macro2[65];
bit	b_REC_Up;	
bit	REC_Mode;
U8 xdata Delay_Fn2_Times;
U8 xdata Delay_Fn3_Times;
U8 xdata G_Led[4];
void Clear_Macro_Data(void)
{
	U8 i;
	for(i=0; i<65; i++)
	{
		Macro2[i]=0;
	}
	Manual_Time_Macro=0;
}
void Clear_Manual_Record(void)
{
	Manual_Record=0;
}
void JiLu_Macro_NUM(U8 ManualData)		//第几组宏  那个按键
{
	bSpeed_End=1;
	Clear_Macro_Data();			//Clr 该组宏Data
	Clear_Manual_Record();
	//Macro2[ManualData][128]=ManualData2;//记录宏在那个按键
	//Manual_Record=0;						//清记录第几组宏的标记
	Manual_Record=ManualData;		//记录在几组宏的标记
	Manual_Record_UNM=1;				//Set 宏录制开始	
}
//*****************************************
//处理启动录制和结束存储
//*****************************************
void Manual_Macro_Data(void)
{
	U8 i;
	//********************************
	if(bFn)
	{
		if((V_Data[14]&0x08)|(V_Data[16]&0x08)|(V_Data[14]&0x10)|(V_Data[16]&0x10))//进入手动录制模式
		{
			if(b_REC_Up)
			{
				b_REC_Up=0;
				if(!Manual_Record_UNM)
				{	
						if(V_Data[14]&0x08)
							JiLu_Macro_NUM(1);
						else if(V_Data[16]&0x08)
							JiLu_Macro_NUM(2);
						else if(V_Data[14]&0x10)
							JiLu_Macro_NUM(3);	
						else if(V_Data[16]&0x10)
							JiLu_Macro_NUM(4);	
						Delay_Fn2_Times=Delay_Fn3_Times=0;
							
				}
				else
				{	
						if(Macro2[0]|Macro2[1]|Macro2[2]|Macro2[3])
							Macro2[64]=Manual_Record;
						else
							Macro2[64]=0;
						Manual_Record_UNM=0x00;
						Save_Macro2_Data(Manual_Record);	
						//Manual_Record=0;
						REC_Mode=1;
						Delay_Fn2_Times=Delay_Fn3_Times=0;
				}
			}
		}
		else
		b_REC_Up=1;
	}
	//***********************************
	if(Manual_Record_UNM)
	{
			Delay_Fn3_Times++;
		if(Delay_Fn3_Times<40)
			return;
		Delay_Fn3_Times=0;
		
		if(Manual_Record==1)
			i=0;
		else if(Manual_Record==2)
			i=1;
		else if(Manual_Record==3)
			i=2;	
		else if(Manual_Record==4)
			i=3;	
		
		Delay_Fn2_Times++;
		if(Delay_Fn2_Times&0x01)
			G_Led[0]=G_Led[1]=G_Led[2]=G_Led[3]=255;
		else	
			G_Led[i]=0;
	}	
	else if(REC_Mode)
	{
		Delay_Fn3_Times++;
		if(Delay_Fn3_Times<10)
			return;
		Delay_Fn3_Times=0;
		
		if(Manual_Record==1)
			i=0;
		else if(Manual_Record==2)
			i=1;
		else if(Manual_Record==3)
			i=2;	
		else if(Manual_Record==4)
			i=3;	
		
		Delay_Fn2_Times++;
		if(Delay_Fn2_Times&0x01)
			G_Led[0]=G_Led[1]=G_Led[2]=G_Led[3]=255;
		else	
			G_Led[i]=0;
			
		if(Delay_Fn2_Times>8)
			{
				REC_Mode=0;
				Manual_Record=0;
			}	
	}
	else
	{
		G_Led[0]=G_Led[1]=G_Led[2]=G_Led[3]=255;
	}		
}
//*****************************************
//记录MACRO DATA 
void Record_Macro_Data(void)
{
	U8 i,Manual_Data;
	if((bFn)|(V_Data[14]&0x10)|(V_Data[16]&0x10)|(V_Data[14]&0x08)|(V_Data[16]&0x08))
		return;
	//Manual_Data=Manual_Record;	
	if(Send_data[0]!=Last_Manual_data[0])//判断特殊键值
	{
		if(Send_data[0])					//判断特殊键值 1时
		{
			if(Manual_Time_Macro<32)
			{	
				if(!Macro2[Manual_Time_Macro*2+1])
				{	
					Macro2[Manual_Time_Macro*2+0]|=0x40;
					Macro2[Manual_Time_Macro*2+1]=Send_data[0];
				}	
			}
		}
		else								//判断特殊键值 0时
		{
			if(Manual_Time_Macro<32)
			{
				if(!Macro2[Manual_Time_Macro*2+1])
				{	
					Macro2[Manual_Time_Macro*2+0]|=0x80;
					Macro2[Manual_Time_Macro*2+1]=Last_Manual_data[0];	
					Macro2[Manual_Time_Macro*2+0]|=0x40;
				}
			}
		}
		Manual_Time_Macro++;	
	}	
	for(i=1;i<7;i++)
	{
		if((Last_Manual_data[i]!=0)||(Send_data[i]!=0))
		{
			if(Send_data[i]!=Last_Manual_data[i])
			{
				if(Send_data[i])
				{
					if(Manual_Time_Macro<32)
					{					
						if(!Macro2[Manual_Time_Macro*2+1])
						{	
							Macro2[Manual_Time_Macro*2+0]&=~0x40;
							Macro2[Manual_Time_Macro*2+1]=Send_data[i];
						}
					}
				}
				else
				{
					if(Manual_Time_Macro<32)
					{
					if(!Macro2[Manual_Time_Macro*2+1])
						{	
							Macro2[Manual_Time_Macro*2+0]&=~0x40;
							Macro2[Manual_Time_Macro*2+1]=Last_Manual_data[i];	
							Macro2[Manual_Time_Macro*2+0]|=0x80;
						}
					}
					
				}
				Manual_Time_Macro++;	
			}
		}
	}
	for(i=0;i<7;i++)
	{
		Last_Manual_data[i]=Send_data[i];
	}
	if((Macro2[62]|Macro2[63])|(Manual_Time_Macro>=63))
	{
			Macro2[62]=0x80;
			Macro2[63]=0x00;
			Macro2[64]=Manual_Record;
			Manual_Record_UNM=0x00;
			Save_Macro2_Data(Manual_Record);	
			//Manual_Record=0;
			REC_Mode=1;
			Delay_Fn2_Times=Delay_Fn3_Times=0;
	}
}
//*****************************************
void Manual_Mian_Macro(void)
{
		Manual_Macro_Data();//处理启动录制和结束存储
	if(Manual_Record_UNM)
	{	
		if(bSend_IN2|b_04)
			Record_Macro_Data();//记录MACRO DATA TIME
	}
}
*/






