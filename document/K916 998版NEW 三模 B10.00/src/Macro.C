#include "..\include\SH68F90.h"
#include "..\include\stdtype.h"
#include "..\include\CFG.h"
#include "..\include\Auser.h"
#include ".\include\ABSACC.H"
//*************************************
U8 xdata Macro_Time[10];
U8 xdata Macro_Cycle_Time[10];
U8	xdata	Macro_Usb2_Data[16];
U8	xdata	Last_Macro_Usb2_Data[16];
U16 xdata Temp_Macro_Time;
U16 xdata  Delay_Macro_Time[10];
U32 xdata	fg_Next_Time;
bit b_02;
U32 xdata fg_Send_Macro;
U8 xdata Mcaro_Ctrl_Data=0;
U8	xdata	Last_Mcaro_Ctrl_Data;
void F_Clear_Macro_USB456(void)
{
	U8 i;
	for(i=0; i<16; i++)
	{
		Macro_Usb2_Data[i] = 0x00;
	}
}
//********************************************
void Judge_Macro_Data(void)
{
	U8 i;
	if(Mcaro_Ctrl_Data!=Last_Mcaro_Ctrl_Data)
	{
		bSend_IN2=1;
		Last_Mcaro_Ctrl_Data=Mcaro_Ctrl_Data;
	}
	else
	{
		for(i=0;i<16;i++)	
		{
			if(Macro_Usb2_Data[i]!=Last_Macro_Usb2_Data[i])
			{
				b_02=1;
				Last_Macro_Usb2_Data[i]=Macro_Usb2_Data[i];
			}
		}
	}
}
void Deal_Macro_Time(U8 V_Macro_TimeL,V_Macro_TimeH)
{
	U8 i1;
	U32 i2;
	i1=i2=0;
	
	Temp_Macro_Time=0x0000;
	Temp_Macro_Time|=V_Macro_TimeH&0X0F;
	Temp_Macro_Time=Temp_Macro_Time<<7;
	Temp_Macro_Time|=V_Macro_TimeL&0x7f;
	Temp_Macro_Time++;
	
		fg_Next_Time|=fg_Send_Macro;		
}
void Down_MacroKey_value(U8 V_MacroKey_2,V_MacroKey_0,V_MacroKey_1)
{
	U8 i2,i3,i;
	if(V_MacroKey_1&0xf0)
		{
			if(V_MacroKey_0&0x80)
				Mcaro_Ctrl_Data&=~V_MacroKey_2;
			else	
				Mcaro_Ctrl_Data|=V_MacroKey_2;
		}	
	else
		{
				if(Mode_USB)
				{
					i2=(V_MacroKey_2-4)/8;
					i3=(V_MacroKey_2-4)%8;
					//Deal_IN2_Data(i3);	
					if(V_MacroKey_0&0x80)
						Macro_Usb2_Data[i2+1]&=~Deal_IN2_Data(i3);	
					else
						Macro_Usb2_Data[i2+1]|=Deal_IN2_Data(i3);	
				}
				else
				{	
					i2=V_MacroKey_2/8;
					i3=V_MacroKey_2%8;
					//Deal_IN2_Data(i3);	
					if(V_MacroKey_0&0x80)
						Macro_Usb2_Data[i2+2]&=~Deal_IN2_Data(i3);	
					else
						Macro_Usb2_Data[i2+2]|=Deal_IN2_Data(i3);	
				}
		}
		Judge_Macro_Data();
}
//*************************************
U8 xdata  Double_Time_Macro;
void Send_Macro_USB_Data(void)
{
	U8 i,i1=0;
	U32 i2;
	U8 i3;
	Double_Time_Macro++;
	if(Double_Time_Macro<2)
		return;
		Double_Time_Macro=0;
	//******************************
		i2=0x01;
	for(i=0; i<10; i++)
	{		
		if(i==0)
			WriteEE_Address=0xBC00;	
		else if(i==1)
			WriteEE_Address=0xBCC0;	
		else if(i==2)
			WriteEE_Address=0xBE00;	
		else if(i==3)
			WriteEE_Address=0xBEC0;		
		else if(i==4)
			WriteEE_Address=0xC000;	
		else if(i==5)
			WriteEE_Address=0xC0C0;		
		else if(i==6)
			WriteEE_Address=0xC200;	
		else if(i==7)
			WriteEE_Address=0xC2C0;			
		else if(i==8)
			WriteEE_Address=0xC400;	
		else if(i==9)
			WriteEE_Address=0xC4C0;		
		i3=0;
		if(fg_Send_Macro&i2)
		{
			i1=Macro_Time[i]*3;
			//if((Macro[i][i1+2])!=0x00)
			if(CBYTE[WriteEE_Address+i1+2]!=0x00)	
			{	
				if((fg_Next_Time&i2)==0)//处理时间
				{	
					//Deal_Macro_Time(Macro[i][i1],Macro[i][i1+1]);
					Deal_Macro_Time(CBYTE[WriteEE_Address+i1],CBYTE[WriteEE_Address+i1+1]);
					Delay_Macro_Time[i]=Temp_Macro_Time;
				}
					//Down_MacroKey_value(Macro[i][i1+2],Macro[i][i1],Macro[i][i1+1]);//键值
					Down_MacroKey_value(CBYTE[WriteEE_Address+i1+2],CBYTE[WriteEE_Address+i1],CBYTE[WriteEE_Address+i1+1]);
				if(Delay_Macro_Time[i]>0)//防止时间溢出
					Delay_Macro_Time[i]--;
				if(Delay_Macro_Time[i]==0)//时间结束出来下一次键动作
					{	
						Macro_Time[i]++;
						fg_Next_Time&=~i2;
						if(i1>=189)
						{
							Macro_Time[i]=0x00;
							fg_Next_Time&=~i2;
							Macro_Cycle_Time[i]--;
							if(Macro_Cycle_Time[i]==0)
							{
								fg_Send_Macro&=~i2;
							}
							F_Clear_Macro_USB456();
							Mcaro_Ctrl_Data=0;
						}
					}
				
			}
			else
			{
				Macro_Time[i]=0x00;
				fg_Next_Time&=~i2;
				Macro_Cycle_Time[i]--;
				if(Macro_Cycle_Time[i]==0)
				{
					fg_Send_Macro&=~i2;
				}
				F_Clear_Macro_USB456();
				Mcaro_Ctrl_Data=0;
			}
			break;//return;
		}
		i2=i2<<1;
	}
	if(!fg_Send_Macro)
	{
		for(i=0;i<16;i++)
			Macro_Usb2_Data[i]=0;
		Mcaro_Ctrl_Data=0;
	}	
}
