#include "..\include\SH68F90.h"
#include "..\include\stdtype.h"
#include "..\include\CFG.h"
#include "..\include\Auser.h"
U8 xdata 	Mode_Times;
U8 xdata	Long_Push_Times;
U8 data 	Brightness_Wheels;
U8 data	Speed_Data;
U8 data	Color_Times;
U16 xdata Run_Time;
bit	b_Cloes_Mode;
bit	b_Home_Up;
bit	b_Home_Up2;
bit	b_Cap_Up;
bit	b_ChangLiang_Mode;
bit	b_HuXi_Mode;
bit	b_PaoMa1_Mode;
bit	b_PaoMa2_Mode;
bit	b_SuiLiang_Mode;
bit	b_SuiMie_Mode;
bit	b_Raindrops_Mode;
bit	b_BoLang_Mode;
bit	b_WASD_Mode;
bit	b_Effect_light_1;
bit	b_Effect_light_2;
bit	b_Pao_Heng;
bit	b_LiuGuang_Mode;
bit	b_LiuGuang_Mode2;
bit	b_LiuGuang_Mode3;
bit	b_LiuGuang_Mode4;
bit	b_LiuGuang_Mode5;
bit	b_LiuGuang_Mode6;
bit	b_LiuGuang_Mode7;
bit	b_HengMie_Mode;
bit	b_HangPao_Mode;
bit	b_PaoMa3_Mode;
bit	b_PaoMa4_Mode;
bit	b_Flower_Mode;
bit	b_HuXi_Mode2;
bit	b_Text_Mode;
bit	mode_change_flag;
U8 xdata Mode_Bluetooth_Times;
U8 xdata Opine_times;
U8 xdata Opine_Data;
bit fg_Power_Led;
bit fg_Power_Led2;
//**********************************
void Clear_Mode_Data(void)//清除模式数据
{
	U8 i;
	for(i=0; i<126; i++)
	{
		NUM_Image[0][i]=NUM_Image[1][i]=NUM_Image[2][i]=0;
	}
	b_ChangLiang_Mode=b_HuXi_Mode=0;
	b_LiuGuang_Mode=b_PaoMa1_Mode=0;
	b_Flower_Mode=b_PaoMa2_Mode=b_SuiLiang_Mode=0;
	b_SuiMie_Mode=b_Raindrops_Mode=0;
	b_HangPao_Mode=b_Pao_Heng=b_BoLang_Mode=0;
	b_PaoMa4_Mode=b_Effect_light_1=b_Effect_light_2=0;
	b_HuXi_Mode2=b_LiuGuang_Mode2=b_WASD_Mode=0;
	b_LiuGuang_Mode3=b_LiuGuang_Mode4=0;
	Clear_All_Image();
	b_HengMie_Mode=0;
	b_LiuGuang_Mode5=b_LiuGuang_Mode6=0;
	Temp_Speed=Run_Time=0;
	Last_CL_Brightness_Wheels=0xAA;
	b_Effect_light_1_Cpl=0x00;
	b_PaoMa3_Mode=b_Record_Mode=0;
	b_PaoMa1=1;
	b_Text_Mode=0;
	b_LiuGuang_Mode7=b_PaoMa2=b_PaoMa3=b_PaoMa4=0;
	b_PaoMa1=1;
}
void Change_Mode2(void)//执行21种灯效
{
	Clear_Mode_Data();
	if(Mode_Times==1)		//常亮	1
		{
			Last_CL_Brightness_Wheels=0xAA;
			b_ChangLiang_Mode=1;
			Let_NUM_Image();
		}
	else  if(Mode_Times==2)	
		{
			b_HuXi_Mode=1;//呼吸	16
			Let_NUM_Image();
		}
	else  if(Mode_Times==3)	
		{
			b_LiuGuang_Mode=1;	//霓虹	18
			Int_Mode6_Data();
		}	
		/////////////////////////////////////////
	else  if(Mode_Times==4)	
		{
			b_SuiLiang_Mode=1;//踏雪无痕	17
		}	
	else  if(Mode_Times==5)	
		{
			b_HangPao_Mode=1;//一触即发	6
		}		
	else  if(Mode_Times==6)		
		{
			b_LiuGuang_Mode2=1;//随波逐流	Color v
			Int_Mode6_Data();
		}		
	else  if(Mode_Times==7)	
		{
			b_Pao_Heng=1;		//涟漪扩散	5按键涟漪
		}	
	else  if(Mode_Times==8)		
		{
			b_LiuGuang_Mode3=1;//彩虹轮盘	2流光异彩
			Int_Mode6_Data();
		}	
	else  if(Mode_Times==9)	
		{
			b_BoLang_Mode=1;//正旋光波	14
		}		
	else  if(Mode_Times==10)	
		{
			b_LiuGuang_Mode4=1;//Color v
			Int_Mode6_Data();
		}	
	else  if(Mode_Times==11)	
		{
			b_Raindrops_Mode=1;//繁星点点	11
		}	
	else  if(Mode_Times==12)	
		{
			b_LiuGuang_Mode6=1;//Color v
			Int_Mode6_Data();
		}	
		///////////////////////////////////////////
	else  if(Mode_Times==13)	
		{
			b_PaoMa1_Mode=1;//花开富贵	9
		}			
	else  if(Mode_Times==14)	
		{
			b_PaoMa2_Mode=1;//跑马	8
		}		
	else  if(Mode_Times==15)	
		{
			b_PaoMa3_Mode=1;//旋转风暴	7
		}	
	else  if(Mode_Times==16)	
		{
			b_PaoMa4_Mode=1;//蛇形跑马	10
		}	
		////////////////////////////////////////
	else  if(Mode_Times==17)	
		{
			b_Effect_light_1=1;//穿插对跑	12川流不息
		}	
	else  if(Mode_Times==18)	
		{
			b_Effect_light_2=1;//斜拉变化	13
		}		
	else  if(Mode_Times==19)	//  指点江山
		{
			b_WASD_Mode=1;
			Read_WASD_Image(Image_Times);
		}		
	///////////////////////////////////////////
	else  if(Mode_Times==20)	//两层流动
		{
			b_LiuGuang_Mode5=1;
			Int_Mode6_Data();
		}		
	else  if(Mode_Times==21)	//随机霓虹
		{
			b_LiuGuang_Mode7=1;
			Int_Mode6_Data();
		}		
	else  if(Mode_Times==30)	
		{
			b_Text_Mode=1;
		}		
		Save_Mode_Time();
}
//-------------------------------------------
void Change_Mode(void)
{
	if(V_Data[0]&0x08)
	{
		if(b_Cap_Up)
		{	
			b_Cap_Up=0;
			if(!Mode_USB)
			{
				if(Module_LED_status&0x02)
					Module_LED_status&=~0x02;
				else
					Module_LED_status|=0x02;	
			}	
		}
	}
	else
		b_Cap_Up=1;
	if(!bFn)//fn按键没按下
		return;
	if((V_Data[9]&0x04)&&(V_Data[9]&0x08))
	{
		if(b_Home_Up2)
		{
			b_Home_Up2=0;	
			Mode_Times=1;	
			Color_Times=7;
			Change_Mode2();	
		}
	}
	else
		b_Home_Up2=1;		
	//---------------------------------------------------------------------------------------------
	if((V_Data[1]&0x04)|(V_Data[2]&0x04)|(V_Data[3]&0x04)|(V_Data[10]&0x04)|(V_Data[5]&0x04))
		{
			if(b_Home_Up)
			{
				Long_Push_Times++;
				if(Long_Push_Times>150)//长按 进入配对
				{
					Long_Push_Times=0;
					b_Home_Up=0;
					if(Mode_Bluetooth1|Mode_Bluetooth2|Mode_Bluetooth3|Mode_24G)
					{	
						if(V_Data[1]&0x04)	//Q	BLE1
						{
							Lang_KeyDown_ModuleMode(2);
						}
						else if(V_Data[2]&0x04)//W	BLE2
						{
							Lang_KeyDown_ModuleMode(3);
						}	
						else if(V_Data[3]&0x04)//E	BLE3
						{
							Lang_KeyDown_ModuleMode(4);
						}	
						else if(V_Data[10]&0x04)//E	2.4G
						{
							Lang_KeyDown_ModuleMode(1);
						}	
					}
				}
				else		//短按
				{	
					if(Long_Push_Times==2)
					{
						if(Mode_Bluetooth1|Mode_Bluetooth2|Mode_Bluetooth3|Mode_24G)
						{	
							if(V_Data[1]&0x04)	//Q	BLE1
							{
								Short_KeyDown_ModuleMode(2);
							}
							else if(V_Data[2]&0x04)//W	BLE2
							{
								Short_KeyDown_ModuleMode(3);
							}	
							else if(V_Data[3]&0x04)//E	BLE3
							{
								Short_KeyDown_ModuleMode(4);
							}
							else if(V_Data[10]&0x04)//E	2.4
							{
								Short_KeyDown_ModuleMode(1);
							}	
						}
					}
				}
			}
		}
	else
		{	
			b_Home_Up=1;	
			Long_Push_Times=0;
		}	
}
//---------------------------------------------
void Brightness_Sub(void)
{
	if(Brightness_Wheels>0)
	{	
		Brightness_Wheels--;
		Int_Mode6_Data();
		if(b_WASD_Mode)
			Read_WASD_Image(Image_Times);
		Save_Mode_Time();
	}
	if(Brightness_Wheels==0)
		bSpeed_End=1;
}
void Brightness_Add(void)
{
	U8 i;
	if(Brightness_Wheels<5)
	{	
		Brightness_Wheels++;
		Int_Mode6_Data();
		if(b_WASD_Mode)
			Read_WASD_Image(Image_Times);
		Save_Mode_Time();
	}
	if(Brightness_Wheels==5)
		bSpeed_End=1;	
}

//***************************************
U8 xdata USB_Opine_Times;
U8 xdata USB_Opine_Times2;
U8 xdata USB_Opine_Times3;
U8	xdata	Last_Time1;
U8	xdata	Last_Time2;
bit	USB_Opine_Up;
bit	Power_All_Up;
bit	b_PowerLow;
U8	xdata	Power_status_Data;
U8	xdata	Power_status_Delay;
void F_Text_Opine(void)
{
	U8 i;
	if(USB_Opine)
	{
		LDO_D=0;
		b_PowerLow=0;
		Power_status_Data=0xAA;
		USB_Opine_Times++;
		if(USB_Opine_Times>5)
		{	
			USB_Opine_Times=6;
			/*
			if(Power_In)	//充满
			{
				USB_Opine_Times2++;
				if(USB_Opine_Times2>220)
				{	
					if(Power_All_Up)
					{	
						Power_All_Up=0;
						if(!fg_Power_Led2)
						{
							fg_Power_Led2=1;
							 Last_Time2=0;
							Last_Time1=0;
						}
					}
				}
			}
			else
			{
				Power_All_Up=1;
				USB_Opine_Times2=0;
			}
			//----------------------------
			if(USB_Opine_Up)
			{	
				USB_Opine_Up=0;
				if(!fg_Power_Led)
				{
					fg_Power_Led=1;
					   Last_Time2=0;
					Last_Time1=0;
				}
			}
			*/
		}
	}
	else
	{
		USB_Opine_Up=1;
		LDO_D=1;
		fg_Power_Led2=0;
		USB_Opine_Times=0;
		if((Power_status<3)&&(!Mode_USB))
		{
			Power_status_Delay++;
			if(Power_status_Delay>30)
			{
				Power_status_Delay=0;
				if(Power_status_Data)
					Power_status_Data=0;
				else
					Power_status_Data=255;
			}
			if(Power_status<2)
			{	
				b_PowerLow=1;
			}
		}	
		if(Power_status>3)
		{
			Power_status_Data=0xAA;
			b_PowerLow=0;
		}
	}			
	Opine_times++;
	if(Opine_times>15)
	{
		Opine_times=0;
		if(Usb_In)
		{
			//mode_change_flag=0;
			if(!Mode_USB)
			{
				Short_KeyDown_ModuleMode(0);
				USB_Opine_Times3=2;
			}
			else if(USB_Opine_Times3)
			{
				Short_KeyDown_ModuleMode(0);
				USB_Opine_Times3--;
			}	
		}	
		else
		{
			if(Mode_Bluetooth_Times==1)
				{	
					if(!Mode_Bluetooth1)
					Short_KeyDown_ModuleMode(2);
				}
			else if(Mode_Bluetooth_Times==2)
				{	
					if(!Mode_Bluetooth2)
					Short_KeyDown_ModuleMode(3);
				}
			else if(Mode_Bluetooth_Times==3)
				{	
					if(!Mode_Bluetooth3)
					Short_KeyDown_ModuleMode(4);
				}
			else if(Mode_Bluetooth_Times==4)
				{
					if(!Mode_24G)
					Short_KeyDown_ModuleMode(1);
				}
		}
	}
			
}
//*******************************************
U8	xdata	Last_Time3;
U8  xdata	bSpeed_data;
U8  xdata	bSpeed_data2;
U8	xdata	Last_Time11;
U8	xdata	Last_Time22;
U8 Pair_State(U8 Temp_Imge2)
{
	U8 i;
		i=0;
	if(Temp_Imge2==0x81)		//对码
		i=1;	//快闪
	else if(Temp_Imge2==0x82)	//回连
		i=2;	//慢闪
	else if(Temp_Imge2==0x83)	//连接
		i=0;	//常亮
	else if(Temp_Imge2==0x80)	//断开
		i=3;	//灭
	return(i);
}
void Deal_Speed_LED_End(void)
{
	//0 常亮  1快闪   2慢闪   3关
	U8 i,j,n,i2;
	U16 i1;
	if(Change_ModeTimes)
		Change_ModeTimes--;
	i=0;
	if(bSpeed_End)
	{
		Last_Time11++;
		if(Last_Time11<15)
		{
			for(i2=17; i2<21; i2++)
			{
				Image[0][i2]=0+PWM_AddData(0,i2);
				Image[1][i2]=0+PWM_AddData(1,i2);
				Image[2][i2]=0+PWM_AddData(2,i2);
			}
		}
		else if(Last_Time11<30)	//R
		{
			for(i2=17; i2<21; i2++)
			{
				Image[0][i2]=1020+PWM_AddData(0,i2);
				Image[1][i2]=1020+PWM_AddData(1,i2);
				Image[2][i2]=1020+PWM_AddData(2,i2);
			}
		}
		else if(Last_Time11<45)
		{
			for(i2=17; i2<21; i2++)
			{
				Image[0][i2]=0+PWM_AddData(0,i2);
				Image[1][i2]=0+PWM_AddData(1,i2);
				Image[2][i2]=0+PWM_AddData(2,i2);
			}
		}
		else if(Last_Time11<60)	//G
		{
			for(i2=17; i2<21; i2++)
			{
				Image[1][i2]=1020+PWM_AddData(1,i2);
				Image[0][i2]=1020+PWM_AddData(0,i2);
				Image[2][i2]=1020+PWM_AddData(2,i2);
			}
		}
		else if(Last_Time11<75)
		{
			for(i2=17; i2<21; i2++)
			{
				Image[0][i2]=0+PWM_AddData(0,i2);
				Image[1][i2]=0+PWM_AddData(1,i2);
				Image[2][i2]=0+PWM_AddData(2,i2);
			}
		}
		else if(Last_Time11<90)	//B
		{
			for(i2=17; i2<21; i2++)
			{
				Image[2][i2]=1020+PWM_AddData(2,i2);
				Image[1][i2]=1020+PWM_AddData(1,i2);
				Image[0][i2]=1020+PWM_AddData(0,i2);
			}
		}
		else if(Last_Time11>90)
		{
			//Clear_All_Image();
			Last_Time11=0;
			if(!b_Record_Mode)
				bSpeed_End=0;
			//Last_CL_Brightness_Wheels=0xAA;
		}
	}		
	else if(fg_Power_Led|fg_Power_Led2)
	{
		Last_Time11++;
		if(Last_Time11>30)
		{
			Last_Time11=0;
			
			if(Last_Time22==0)
				bSpeed_data2=0;
			else if(Last_Time22==1)
				bSpeed_data2=250;
				
			else if(Last_Time22==2)
				bSpeed_data2=0;	
			else if(Last_Time22==3)
				bSpeed_data2=250;
				
			else if(Last_Time22==4)
				bSpeed_data2=0;		
			else if(Last_Time22==5)
				bSpeed_data2=250;	
				
			else if(Last_Time22==6)
				bSpeed_data2=0;	
			else if(Last_Time22==7)
				bSpeed_data2=250;
				
			else if(Last_Time22==8)
				bSpeed_data2=0;		
			else if(Last_Time22==9)
				bSpeed_data2=250;	
			else if(Last_Time22==10)
				bSpeed_data2=0;		
				i2=6;
			if(fg_Power_Led2)
				i2=10;	
			Last_Time22++;
			if(Last_Time22>i2)
				{
					Last_Time22=0;
					fg_Power_Led=fg_Power_Led2=0;
					Last_CL_Brightness_Wheels=0xAA;
				}		
		}	
	}	
	if(Mode_24G)
	{
		if(Module_LED_status2==1)
		{	
			fg_suspend = 0;
			USB_Mode_Times=0;
			i=Pair_State(Wirte_State);
		}
		else if(Change_ModeTimes==0)
		{
			Short_KeyDown_ModuleMode(1);
		}
	}
	else if(Mode_Bluetooth1)
	{
		if(Module_LED_status2==0x21)
		{	
			fg_suspend = 0;
			USB_Mode_Times=0;
			i=Pair_State(Wirte_State);
		}
		else if(Change_ModeTimes==0)
		{
			Short_KeyDown_ModuleMode(2);
		}
	}
	else if(Mode_Bluetooth2)
	{
		if(Module_LED_status2==0x41)
		{	
			fg_suspend = 0;
			USB_Mode_Times=0;
			i=Pair_State(Wirte_State);
		}
		else if(Change_ModeTimes==0)
		{
			Short_KeyDown_ModuleMode(3);
		}
			
	}
	else if(Mode_Bluetooth3)
	{
		if(Module_LED_status2==0x61)	
		{	
			fg_suspend = 0;
			USB_Mode_Times=0;
			i=Pair_State(Wirte_State);
		}
		else if(Change_ModeTimes==0)
		{
			Short_KeyDown_ModuleMode(4);
		}
	}
	//---------------------------------------------
	switch(i)
	{
		case 0:	
			bSpeed_data=0XAA;
			//Last_CL_Brightness_Wheels=0XAA;
		break;
		//--------------------------------
		case 1:		//快闪
			Last_Time2++;
			if(Last_Time2>12)
			{
				Last_Time2=0;
				if(Last_Time1)
				{	
					Last_Time1=0;
					bSpeed_data=0;
				}
				else
				{	
					Last_Time1=1;
					bSpeed_data=250;	
				}	
			}	
		break;
		//--------------------------------
		case 2:		//慢闪
			Last_Time2++;
			if(Last_Time2>50)
			{
				Last_Time2=0;
				if(Last_Time1)
				{	
					Last_Time1=0;
					bSpeed_data=0;
				}
				else
				{	
					Last_Time1=1;
					bSpeed_data=250;	
				}	
			}	
		break;
		//--------------------------------
		case 3:		//关灯
			bSpeed_data=0XAA;
		break;
		//--------------------------------
	}
	
		
}