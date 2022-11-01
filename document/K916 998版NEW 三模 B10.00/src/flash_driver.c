#include "..\include\SH68F90.h"
#include "..\include\stdtype.h"
#include "..\include\mcu_def.h"
#include "..\include\pwm_control.h"
#include ".\include\Auser.h"
#include "..\include\CFG.h"
#include ".\include\ABSACC.H"
#include <intrins.h>
#include <string.h>
U16 xdata WriteEE_Address;
U16 xdata WriteEE_Address2;
static void Save_Mode_Time(void);
static void Read_KeyIndex_Data(void);
static void Read_Mode_Time(void);
static void Save_Macro_Data(void);
static void Save_Flash_Data(void);
#define switch_info()		FLASHCON |= 0x01
#define switch_main()   	FLASHCON &= ~0x01
#define S_Macro_1			94		//	0xBC00
#define S_Macro_2			95		//	0xBE00
#define S_Macro_3			96		//	0xC000
#define S_Macro_4			97		//	0xC200
#define S_Macro_5			98		//	0xC400

#define S_FLASH_Key 				99		//<<2	//0xC600	99*512
#define S_FLASH_Mode_SECTOR2 	100	//<<2	//0xC800	100*512

#define S_FLASH_Mode_1 			101	//<<2	//0xCA00	101*512
#define S_FLASH_Mode_2 			102	//<<2	//0xCC00	102*512
#define S_FLASH_Mode_3			103	//		0xCE00		103*512


bit	b_Start_Change_Mode2;
code const U8 USB_Tab6[21*6]=
{
	0x29,0x35,0x2b,0x39,		0x00,0x00,//c0
	0x00,0x1e,0x14,0x04,		0x1d,0x00,//c1
	0x3a,0x1f,0x1a,0x16,		0x1b,0x00,//c2	
	0x3b,0x20,0x08,0x07,		0x06,0x00,//c3
	0x3c,0x21,0x15,0x09,		0x19,0x00,//c4	
	0x3d,0x22,0x17,0x0a,		0x05,0x2c,//c5
	0x3e,0x23,0x1c,0x0b, 		0x11,0x00,//c6
	0x3f,0x24,0x18,0x0d,		0x10,0x00,//c7
	0x40,0x25,0x0c,0x0e,		0x36,0x00,//c8
	
	0x41,0x26,0x12,0x0f,		0x37,0x00,//c9	
	0x42,0x27,0x13,0x33,		0x38,0x65,//c10
	0x43,0x2d,0x2f,0x34, 		0x87,0x00,//c11
	0x44,0x2e,0x30,0x32,		0x64,0x00,//c12
	0x45,0x2a,0x31,0x28,		0x00,0x00,//c13
	
	0x46,0x49,0x4c,0X00,		0X00,0x50,//c14
	0x47,0x4a,0x4d,0X00,		0x52,0x51,//c15
	0x48,0x4b,0x4e,0X00,		0x00,0x4F,//c16
	
	0x00,0x53,0x5F,0x5C, 		0x59,0x62,//c17
	0x00,0x54,0x60,0x5D,		0x5a,0x00,//c18
	0x00,0x55,0x61,0x5e,		0x5b,0x63,//c19
	0x00,0x56,0x57,0X85,		0x58,0x00,//c20
};
void sector_erase(U8 data sec_num)
{
	CLR_WDT();
	EA = 0;
	XPAGE = sec_num<<1;
	IB_CON1 = 0xe6;
	IB_CON2 = 0x05;
	IB_CON3 = 0x0A;
	IB_CON4 = 0x09;
	IB_CON5 = 0x06;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	IB_CON1 = 0;
	IB_CON2 = 0;
	IB_CON3 = 0;
	IB_CON4 = 0;
	IB_CON5 = 0;
	EA = 1;
}
//***************************************
void sector_prog(U16 data sec_addr, U8 data prog_data)
{
	EA = 0;
	CLR_WDT();
	XPAGE = sec_addr>>8;
	IB_OFFSET = sec_addr;
	IB_DATA = prog_data;
	IB_CON1 = 0x6e;
	IB_CON2 = 0x05;
	IB_CON3 = 0x0A;
	IB_CON4 = 0x09;
	IB_CON5 = 0x06;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	IB_CON1 = 0;
	IB_CON2 = 0;
	IB_CON3 = 0;
	IB_CON4 = 0;
	IB_CON5 = 0;
	EA = 1;
}
//************************************************
void Clear_Flash_Data(void)
{
	sector_erase(S_FLASH_Mode_1);
	sector_erase(S_FLASH_Mode_2);
	sector_erase(S_FLASH_Mode_3);
	
	sector_erase(S_Macro_1);
	sector_erase(S_Macro_2);
	sector_erase(S_Macro_3);
	sector_erase(S_Macro_4);
	sector_erase(S_Macro_5);
}
code const U8 Image_Times_Tab2[28]={2,3,4,22,23,24,25,26,42,43,44,45,46,64,65,66,68,84,89,105,107,110,14,15,37,36,58,57,};
code const U8 Image_Times_Tab3[]={22,23,24,25,26,27,28,43,44,45,46,47,64,65,66,67,68,84,87,88,105,};
void Read_WASD_Image(U8 Temp_Images)
{
	U8 i,j,n,k;
	Clear_Mode_Data();
	b_WASD_Mode=1;
	Mode_Times=19;
	if(Image_Times==1)
		WriteEE_Address = 0xCA00;
	else if(Image_Times==2)
		WriteEE_Address = 0xCC00;
	else if(Image_Times==3)
		WriteEE_Address = 0xCE00;
			
	for(i=0; i<126; i++)	
	{
		if(CBYTE[WriteEE_Address])
			Image[0][i]=255*Brightness_Wheels/Limit_Power*4+PWM_AddData(0,i);
		else
			Image[0][i]=PWM_AddData(0,i);	
		WriteEE_Address ++;		
			
		if(CBYTE[WriteEE_Address])
			Image[1][i]=255*Brightness_Wheels/Limit_Power*4+PWM_AddData(1,i);
		else
			Image[1][i]=PWM_AddData(1,i);	
		WriteEE_Address ++;	
		
		if(CBYTE[WriteEE_Address])
			Image[2][i]=255*Brightness_Wheels/Limit_Power*4+PWM_AddData(2,i);
		else
			Image[2][i]=PWM_AddData(2,i);
		WriteEE_Address ++;			
	}
	n=CBYTE[WriteEE_Address];
	if(n!=0xAA)
	{
		if(Image_Times==1)
		{	
		Image[0][1]=Image[0][44]=Image[0][64]=Image[0][65]=250*Brightness_Wheels/Limit_Power*4+PWM_AddData(0,i);
		Image[0][66]=Image[0][99]=Image[0][119]=Image[0][120]=Image[0][121]=250*Brightness_Wheels/Limit_Power*4+PWM_AddData(0,i);
		}
		else if(Image_Times==2)
		{
			for(i=0; i<sizeof(Image_Times_Tab2); i++)
				Image[1][Image_Times_Tab2[i]]=250*Brightness_Wheels/Limit_Power*4+PWM_AddData(0,i);
		}	
		else if(Image_Times==3)
		{
			for(i=0; i<sizeof(Image_Times_Tab3); i++)
				Image[2][Image_Times_Tab3[i]]=250*Brightness_Wheels/Limit_Power*4+PWM_AddData(0,i);
		}
		Save_Flash_Data();
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
void Save_Flash_Data(void)
{
	U8 i;
	if(Image_Times==1)
	{
		sector_erase(S_FLASH_Mode_1);
		WriteEE_Address = 0xCA00;	
	}
	else if(Image_Times==2)
	{
		sector_erase(S_FLASH_Mode_2);
		WriteEE_Address = 0xCC00;	
	}
	else if(Image_Times==3)
	{
		sector_erase(S_FLASH_Mode_3);
		WriteEE_Address = 0xCE00;	
	}
		for(i=0; i<126; i++)
		{
			if((Image[0][i]!=PWM_AddData(0,i))&&(Image[0][i]))
				sector_prog(WriteEE_Address, 255);
			else
				sector_prog(WriteEE_Address, 0);	
			WriteEE_Address += 0x0001;	
			
			if((Image[1][i]!=PWM_AddData(1,i))&&(Image[1][i]))
				sector_prog(WriteEE_Address, 255);
			else
				sector_prog(WriteEE_Address, 0);	
			WriteEE_Address += 0x0001;	
			
			if((Image[2][i]!=PWM_AddData(2,i))&&(Image[2][i]))
				sector_prog(WriteEE_Address, 255);
			else
				sector_prog(WriteEE_Address, 0);	
			WriteEE_Address += 0x0001;	
		}	
		sector_prog(WriteEE_Address,0XAA);
		WriteEE_Address += 0x0001;	
}
//****************************************************
//****************************************************
U8 xdata USB_Ind_Num;
U16 xdata Usb_Ind_Length;
U8 xdata Usb_Ind_Times;
//bit USB_Data_Start;
U8 xdata Data8_cnt1;
U8 xdata Data8_cnt2;
U8 data RLT_Index;
U8 data RLT2_Index;
U16 xdata Image2[3][126];
bit b_Image2_Ok;
bit b_Feel_Mode;
void Deal_Macro_Cnt(void)
{
		Data8_cnt1++;
		if(Data8_cnt1>191)
		{
			Data8_cnt1=0;
			Data8_cnt2++;
		}
		if(Data8_cnt2==0)
			WriteEE_Address2 = 0xBC00+Data8_cnt1;	
		else if(Data8_cnt2==1)
			WriteEE_Address2 = 0xBCC0+Data8_cnt1;		
		else if(Data8_cnt2==2)
			WriteEE_Address2 = 0xBE00+Data8_cnt1;	
		else if(Data8_cnt2==3)
			WriteEE_Address2 = 0xBEC0+Data8_cnt1;	
		else if(Data8_cnt2==4)
			WriteEE_Address2 = 0xC000+Data8_cnt1;		
		else if(Data8_cnt2==5)
			WriteEE_Address2 = 0xC0C0+Data8_cnt1;		
		else if(Data8_cnt2==6)
			WriteEE_Address2 = 0xC200+Data8_cnt1;	
		else if(Data8_cnt2==7)
			WriteEE_Address2 = 0xC2C0+Data8_cnt1;	
		else if(Data8_cnt2==8)
			WriteEE_Address2 = 0xC400+Data8_cnt1;	
		else if(Data8_cnt2==9)
			WriteEE_Address2 = 0xC4C0+Data8_cnt1;		
}
void Deal_Feel_Data(void)
{
	Data8_cnt2++;
	if(Data8_cnt2>2)
	{
		Data8_cnt2=0;
		Data8_cnt1++;
		if(Data8_cnt1>=126)
		Data8_cnt1=0;
	}	
}
void Deal_Image2_Data(void)
{
	U8 i;
	if(Usb_Ind_Times)
	{
		Usb_Ind_Times--;
		if(Usb_Ind_Times==0)
		{	
			b_Feel_Mode=0;
			b_Image2_Ok=0;
			Change_Mode2();	
		}
	}
}
void Save_Imaging_Data(U8 Temp_USB_Data)//实时灯效
{
	
	if(RLT_Index==0x01)//键盘键值	504
	{
		if(RLT2_Index==1)
		{
			if(Usb_ImageID==0)
			{
				IPH1 = 0x01;//IPH1_INIT;
				IPL1 =  0x01;
				Usb_Ind_Length=504;
				sector_erase(S_FLASH_Key);
				WriteEE_Address2=0xC600;
			}
			else if(Usb_ImageID>3)
			{
				sector_prog(WriteEE_Address2, Temp_USB_Data);
				WriteEE_Address2 += 0x0001;	
				
				Usb_Ind_Length--;
			}
		}
		else
		{
			if(Usb_ImageID>=2)
			{
				if(Usb_Ind_Length)
				{	
				sector_prog(WriteEE_Address2, Temp_USB_Data);
				WriteEE_Address2 += 0x0001;	
				Usb_Ind_Length--;
				}
			}
		}
	}	
	else if(RLT_Index==0x02)//模式灯效等	41长度，现在有效数据4个
	{
		if(Usb_ImageID==0)
		{
			IPH1 = 0x01;//IPH1_INIT;
			IPL1 =  0x01;
			Clear_Mode_Data();
		}
		else if(Usb_ImageID==4)
		{
			Mode_Times=Change_Mode_Data(Temp_USB_Data);
		}
		else if(Usb_ImageID==6)
		{
			Speed_Data=5-Temp_USB_Data;
		}
		else if(Usb_ImageID==7)
		{
			Brightness_Wheels=Temp_USB_Data;
		}
		else if(Usb_ImageID==8)
		{
			Color_Times=0;
			R_Color=Temp_USB_Data;		
		}
		else if(Usb_ImageID==9)
		{
			G_Color=Temp_USB_Data;
		}
		else if(Usb_ImageID==10)
		{
			B_Color=Temp_USB_Data;
		}
		else if(Usb_ImageID==11)
		{
			if(Temp_USB_Data==1)
				Color_Times=8;
			else
				Color_Times=0;
		}
		else if(Usb_ImageID==12)
		{
			Sleep_Times=Temp_USB_Data;
		}	
		else if(Usb_ImageID==60)
		{
			b_Start_Change_Mode2=1;
			Change_Mode2();
		}		
	}
	else if(RLT_Index==0x04)//Macro
	{
		if(RLT2_Index==1)
		{
			if(Usb_ImageID==0)
			{
				IPH1 = 0x01;//IPH1_INIT;
				IPL1 =  0x01;
				Usb_Ind_Length=192*10;
				sector_erase(S_Macro_1);
				sector_erase(S_Macro_2);
				sector_erase(S_Macro_3);
				sector_erase(S_Macro_4);
				sector_erase(S_Macro_5);
				Data8_cnt1=Data8_cnt2=0;
				WriteEE_Address2 = 0xBC00;	
			}
			else if(Usb_ImageID>3)
			{
				if(Usb_Ind_Length)
				{	
					Usb_Ind_Length--;
					sector_prog(WriteEE_Address2, Temp_USB_Data);
					Deal_Macro_Cnt();	
				}	
			}
		}
		else 
		{
			if(Usb_ImageID>=2)
			{
				if(Usb_Ind_Length)
				{	
					Usb_Ind_Length--;
					sector_prog(WriteEE_Address2, Temp_USB_Data);
					Deal_Macro_Cnt();	
				}	
			}
		}
	}
	else if(RLT_Index==0x03)//游戏高手
	{
		if(RLT2_Index==1)
		{
			if(Usb_ImageID==0)
			{
				IPH1 = 0x01;//IPH1_INIT;
				IPL1 =  0x01;
			}	
			else if(Usb_ImageID==4)
			{
				Image_Times=Temp_USB_Data;
				Mode_Times=19;
				Change_Mode2();	
				Data8_cnt1=0;
				Data8_cnt2=0;
				Usb_Ind_Length=126*3;
			}	
			if(Usb_ImageID>4)
			{
				if(Usb_Ind_Length)
				{	
					Usb_Ind_Length--;
					Image[Data8_cnt2][Deal_Tbl_Image2(Data8_cnt1)]=Temp_USB_Data*4+PWM_AddData(Data8_cnt2,Deal_Tbl_Image2(Data8_cnt1));
					Deal_Feel_Data();
				}
			}
		}
		else
		{
			if(Usb_ImageID>=2)
			{
				if(Usb_Ind_Length)
				{	
					Usb_Ind_Length--;
					Image[Data8_cnt2][Deal_Tbl_Image2(Data8_cnt1)]=Temp_USB_Data*4+PWM_AddData(Data8_cnt2,Deal_Tbl_Image2(Data8_cnt1));
					Deal_Feel_Data();
					if(Usb_Ind_Length==0)
						Save_Flash_Data();
				}
			}
		}
	}
	else if(RLT_Index==0x06)
	{
		if(RLT2_Index==1)
		{
			if(Usb_ImageID==0)
			{
				Usb_Ind_Length=126*3;
				Data8_cnt1=Data8_cnt2=0;
				b_ChangLiang_Mode=0;
				b_SuiMie_Mode=b_HuXi_Mode=b_WASD_Mode=0;
				b_LiuGuang_Mode6=b_LiuGuang_Mode=b_LiuGuang_Mode2=b_LiuGuang_Mode3=b_LiuGuang_Mode4=0;
				b_Pao_Heng=b_HangPao_Mode=b_SuiLiang_Mode=b_HengMie_Mode=b_PaoMa1_Mode=0;
				b_PaoMa2_Mode=b_PaoMa3_Mode=b_PaoMa4_Mode=b_Raindrops_Mode=0;
				b_Effect_light_1=b_Effect_light_2=b_BoLang_Mode=0;
				b_LiuGuang_Mode5=b_LiuGuang_Mode7=0;
				b_Feel_Mode=1;
			}
			else if(Usb_ImageID>3)
			{
				if(Usb_Ind_Length)
				{	
					Usb_Ind_Length--;
					Image2[Data8_cnt2][Deal_Tbl_Image2(Data8_cnt1)]=Temp_USB_Data*4+PWM_AddData(Data8_cnt2,Deal_Tbl_Image2(Data8_cnt1));
					if(Temp_USB_Data)
						CLR_WDT();		
					Deal_Feel_Data();
				}
			}
		}
		else if(RLT2_Index>1)
		{
			if(Usb_ImageID>=2)
			{
				if(Usb_Ind_Length)
				{	
					Usb_Ind_Length--;
					Image2[Data8_cnt2][Deal_Tbl_Image2(Data8_cnt1)]=Temp_USB_Data*4+PWM_AddData(Data8_cnt2,Deal_Tbl_Image2(Data8_cnt1));
					Deal_Feel_Data();
					if(Usb_Ind_Length==0)
					{	
						b_Image2_Ok=1;
						Usb_Ind_Times=200;
					}
				}
			}
		}
	}
	Usb_ImageID++;
}
//****************************************************
/*
0(esc)|         6 |
1|	            7 |
2|	            8 |
3|	            9 |
4|	            10|
5(ctrl_l)|	    11|
*/
void Read_KeyIndex_Data(void)
{
	U16 i;
	U16 i1;
	U16 b_General_Data;
	b_General_Data=0;
	WriteEE_Address=0xC600;
	for(i=0; i<504; i++)
	{
		if(CBYTE[WriteEE_Address+i])
			b_General_Data++;
	}
	if(Reset_Mode)//复位模式按下
		b_General_Data=0;
	WriteEE_Address=0xC600;
	if((b_General_Data<50)|Reset_Mode)	//写Flash
	{	
		sector_erase(S_FLASH_Key);
		for(i=0; i<126; i++)
		{
			i1=WriteEE_Address+i*4;
			if(i==5)
			{
				sector_prog(i1, 0x00);
				sector_prog(i1+1, 0x01);//Ctrl_L
				sector_prog(i1+2, 0);
				sector_prog(i1+3, 0x00);
			}
			else if(i==4)
			{
				sector_prog(i1, 0x00);
				sector_prog(i1+1, 0x02);//SHIFT_L	
				sector_prog(i1+2, 0);
				sector_prog(i1+3, 0x00);
			}
			else if(i==17)
			{
				sector_prog(i1, 0x00);
				sector_prog(i1+1, 0x04);//ALT_L
				sector_prog(i1+2, 0);
				sector_prog(i1+3, 0x00);
			}
			else if(i==11)
			{
				sector_prog(i1, 0x00);
				sector_prog(i1+1, 0x08);//Win_L
				sector_prog(i1+2, 0);
				sector_prog(i1+3, 0x00);
			}
			else if(i==83)		
			{
				sector_prog(i1, 0x00);
				sector_prog(i1+1, 0x10);//Ctrl_R
				sector_prog(i1+2, 0);
				sector_prog(i1+3, 0x00);
			}
			else if(i==82)
			{
				sector_prog(i1, 0x00);
				sector_prog(i1+1, 0x20);//SHIFT_R	
				sector_prog(i1+2, 0);
				sector_prog(i1+3, 0x00);
			}
			else if(i==53)
			{
				sector_prog(i1, 0x00);
				sector_prog(i1+1, 0x40);//ALT_R
				sector_prog(i1+2, 0);
				sector_prog(i1+3, 0x00);
			}
			else
			{
				sector_prog(i1, 0x00);
				sector_prog(i1+1, 0x00);
				sector_prog(i1+2, USB_Tab6[i]);
				sector_prog(i1+3, 0x00);
			}
		}
	}
}
//****************************************************
void Save_Mode_Time(void)
{
	sector_erase(S_FLASH_Mode_SECTOR2);
	sector_prog(0xC800, 0x5A);
	sector_prog(0xC801, Mode_Times);
	sector_prog(0xC802, Image_Times);
	sector_prog(0xC803, Color_Times);
	sector_prog(0xC804, Sleep_Times);
	sector_prog(0xC805, Mode_Bluetooth_Times);	
	sector_prog(0xC806, R_Color);
	sector_prog(0xC807, G_Color);
	sector_prog(0xC808, B_Color);
	sector_prog(0xC809, Brightness_Wheels);
	sector_prog(0xC80A, Logo_Mode_Times);
}
void Read_Mode_Time(void)
{
	U8 i,n,j;
	n=i=j=0;
	i= CBYTE[0xC800];
	Mode_Times= CBYTE[0xC801];
	Image_Times= CBYTE[0xC802];
	Color_Times= CBYTE[0xC803];
	Sleep_Times= CBYTE[0xC804];
	Mode_Bluetooth_Times= CBYTE[0xC805];
	R_Color= CBYTE[0xC806];
	G_Color= CBYTE[0xC807];
	B_Color= CBYTE[0xC808];
	Brightness_Wheels= CBYTE[0xC809];
	Logo_Mode_Times= CBYTE[0xC80A];
	if(i!=0x5A)
		{
			Mode_Times=6;
			Image_Times=1;
			Color_Times=8;
			Sleep_Times=1;
			Mode_now=0;
			Mode_Bluetooth_Times=1;
			Deal_Wireless_Name();
			Brightness_Wheels=4;
		}	
	Speed_Data=3;	
	Last_CL_Brightness_Wheels=0xAA;	
	Power_status_Data=0xAA;
	Clear_All_Image();	
	Int_Logo_Data();
	Change_Mode2();
}









