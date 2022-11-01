#include "..\include\SH68F90.h"
#include "..\include\stdtype.h"
#include "..\include\mcu_def.h"
#include "..\include\pwm_control.h"
#include ".\include\Auser.h"
#include "..\include\CFG.h"
#include <intrins.h>
#include <string.h>
bit	Ready_ok;
U8 xdata Module_Data[32];
U16 xdata Module_DataTimes;
U8 xdata Check_Data;
U8 xdata Module_State_Data[4];
U8 xdata Wirte_State;
U8 xdata Module_LED_status2;
void Clear_Module_Data(void)
{
	U8 i;	
	for(i=0;i<32;i++)
		Module_Data[i]=0;
}
void Write_Module_Data(U8 wdata)
{
	U8 i;	
	SPI_SCK=1;
	for(i=0;i<8;i++)
	{
		SPI_SCK=0;
		 if(wdata & 0x80)
	            SPI_MOSI=1;
	        else
	            SPI_MOSI=0;
	       SPI_SCK=1;
	        wdata <<= 1;
	}
	SPI_MOSI=1;
}
void Clear_All_ModeBit(void)
{
	Mode_24G=0;
	Mode_Bluetooth1=0;
	Mode_Bluetooth2=0;
	Mode_Bluetooth3=0;
	Mode_USB=0;
}
//---------------------------------------------------
void Module_Command_Data(U8 Temp_Module)
{
		Module_Data[0]=0xAA;
		Module_Data[1]=0x03;
		Module_Data[2]=0X01;
	switch(Temp_Module)
	{
		case 0://切换2.4G
			Module_Data[3]=0X00;
			Module_Data[4]=0X00;
		break;	
		case 1://切换2.4G配对
			Module_Data[3]=0X01;
			Module_Data[4]=0X00;
		break;	
		case 2://蓝牙1 切换
			Module_Data[3]=0X00;
			Module_Data[4]=0X01;
		break;	
		case 3://蓝牙1 切换 进入配对
			Module_Data[3]=0X01;
			Module_Data[4]=0X01;
		break;	
		case 4://蓝牙2 切换
			Module_Data[3]=0X00;
			Module_Data[4]=0X02;
		break;	
		case 5://蓝牙2 切换 进入配对
			Module_Data[3]=0X01;
			Module_Data[4]=0X02;
		break;	
		case 6://蓝牙3 切换
			Module_Data[3]=0X00;
			Module_Data[4]=0X03;
		break;	
		case 7://蓝牙3 切换 进入配对
			Module_Data[3]=0X01;
			Module_Data[4]=0X03;
		break;	
		case 8://进入USB
			Module_Data[2]=0X06;	
			Module_Data[3]=0X01;
			Module_Data[4]=0X00;
		break;	
		case 9://退出USB
			Module_Data[2]=0X06;	
			Module_Data[3]=0X01;
			Module_Data[4]=0X00;
		break;	
	}
}
//**********************************
void Send_TextMode_Data(U8 Temp_Module)
{
	Module_Data[0]=0xAA;
	Module_Data[1]=0x03;
	Module_Data[2]=0X03;
	switch(Temp_Module)
	{
		case 0://2.4G	测试模式
			Module_Data[3]=0x00;//0X05;
		break;	
		case 1://BLE 	测试模式
			Module_Data[3]=1;	//	0x01;//
		break;	
		case 2://清除蓝牙配对记录
			Module_Data[3]=0x02;//0X25;
		break;	
		case 3://EMI 测试模式
			Module_Data[3]=0x03;//0X35;
		break;	
		case 4://蓝牙3.0 测试模式
			Module_Data[3]=4;
		break;	
	}
}
//---------------------------------------------------
void Int_Module(void)
{
	Clear_All_ModeBit();
	Clear_Module_Data();
	Ready_ok=1;
	Module_DataTimes=0;
	Check_Data=0;
}
void Send_Module_Data(void)
{
	U8 i;
	if(!Ready_ok)
		return;
	SPI_SCK_Out;
	SPI_MOSI_Out;
	SPI_MOT_Out;
	SPI_SS_Out;
	delay_us(1);
	SPI_MOT=0;
	delay_us(3);
//	if(SLEEP_PIN)
	{
		SPI_SS=0;	
		if(bPower_Up)
		{
			bPower_Up=0;
			return;
		}	
		delay_us(53);
		while(Module_DataTimes!=Module_Data[1]+3)
		{
			if(Module_DataTimes)
			{	
				Write_Module_Data(Module_Data[Module_DataTimes-1]);
				Check_Data=Module_Data[Module_DataTimes-1]+Check_Data;
			}
			Module_DataTimes++;
		}
		Check_Data=0x55-Check_Data;
		Write_Module_Data(Check_Data);
		Module_DataTimes=0;
		Ready_ok=0;	
		SPI_SCK=1;
		SPI_SS=1;	
		SPI_MOT=1;
		SPI_SCK_DirIn;
		SPI_SS_DirIn;
		SPI_MOT_DirIn;
	}
}
//********************************
void Send_Wireless_Data(void)//发送无线数据
{
	if(Ready_ok)
		return;
	if(b_Record_Mode)
		return;	
	if(bSend_IN2|b_04|b_02)
	{
		Clear_Module_Data();
		Module_Data[0]=0xAA;
		Module_Data[1]=0x1D ;
		Module_Data[2]=0X02;
		Module_Data[3]=Send_data[0]|Mcaro_Ctrl_Data;
		Module_Data[4]=Send_data[1];
		Module_Data[5]=Send_data[2];
		Module_Data[6]=Send_data[3];
		Module_Data[7]=Send_data[4];
		Module_Data[8]=Send_data[5];		
		Module_Data[9]=	0;//	Send_data[6];
		if(b_02)
		{
		Module_Data[10]=Macro_Usb2_Data[2];
		Module_Data[11]=Macro_Usb2_Data[3];
		Module_Data[12]=Macro_Usb2_Data[4];
		Module_Data[13]=Macro_Usb2_Data[5];
		Module_Data[14]=Macro_Usb2_Data[6];
		Module_Data[15]=Macro_Usb2_Data[7];		
		Module_Data[16]=Macro_Usb2_Data[8];
		Module_Data[17]=Macro_Usb2_Data[9];
		Module_Data[18]=Macro_Usb2_Data[10];		
		Module_Data[19]=Macro_Usb2_Data[11];
		
		Module_Data[20]=Macro_Usb2_Data[12];
		Module_Data[21]=Macro_Usb2_Data[13];
		Module_Data[22]=Macro_Usb2_Data[14];
		Module_Data[23]=Macro_Usb2_Data[15];
		Module_Data[24]=0;//Macro_Usb2_Data[16];
		Module_Data[25]=0;//Macro_Usb2_Data[17];	
		}
		else
		{
		Module_Data[10]=Usb2_Data[2];
		Module_Data[11]=Usb2_Data[3];
		Module_Data[12]=Usb2_Data[4];
		Module_Data[13]=Usb2_Data[5];
		Module_Data[14]=Usb2_Data[6];
		Module_Data[15]=Usb2_Data[7];		
		Module_Data[16]=Usb2_Data[8];
		Module_Data[17]=Usb2_Data[9];
		Module_Data[18]=Usb2_Data[10];		
		Module_Data[19]=Usb2_Data[11];
		
		Module_Data[20]=Usb2_Data[12];
		Module_Data[21]=Usb2_Data[13];
		Module_Data[22]=Usb2_Data[14];
		Module_Data[23]=Usb2_Data[15];
		Module_Data[24]=0;//Usb2_Data[16];
		Module_Data[25]=0;//Usb2_Data[17];
		}
		Module_Data[26]=0;//		Usb2_Data[17];
		Module_Data[27]=0;//		Usb2_Data[18];
		Module_Data[28]=0;//		Usb2_Data[19];		
		Module_Data[29]=0;//		Usb2_Data[20];
		Module_Data[30]=0;//		Usb2_Data[6];
		Ready_ok=1;
		b_04=bSend_IN2=0;
		b_02=0;
		Module_DataTimes=0;
		Check_Data=0; 
	}
	else if(b_01)
	{
		
		Module_Data[0]=0xAA;
		Module_Data[1]=0x0B ;
		Module_Data[2]=0X05;
		Module_Data[3]=0;
		Module_Data[4]=0;
		Module_Data[5]=0;
		Module_Data[6]=0;
		Module_Data[7]=0;
		Module_Data[8]=0;
		if(b_01)
		{	
			Module_Data[9]=Multimedia_Data[1];
			Module_Data[10]=Multimedia_Data[0];
		}
	
		Module_Data[11]=0;
		Module_Data[12]=0;
		Ready_ok=1;
		Module_DataTimes=0;
		Check_Data=0; 
		Multimedia_Data[0]=0;
		Multimedia_Data[1]=0;
//		Multimedia_Wheel_Data=0;
		b_01=0;
	}	
}	
//***************************************
bit b_Ready_To_Read;
U8 xdata Record_Read_Times;
//U8 xdata Delay_Times_Module;
U8 xdata Delay_Times_Module2;
void Module_Read_Data(U8 Temp_Module)
{
	Module_Data[0]=0xAA;
	Module_Data[1]=0x03;
	Module_Data[2]=0X0A;
	Module_Data[3]=0X00;
	Module_Data[4]=0X00;
}

void Change_Wireless_Name_50(void)
{
	U8 i;
	Check_Data=0;
	Module_Data[0]=0xAA;
	Module_Data[1]=0x1D;
	Module_Data[2]=0X08;
	Module_Data[3]=0X00;
	
	Module_Data[4]=8;
	
	Module_Data[5]='R';
    	Module_Data[6]='K';
    	Module_Data[7]=' ';
    	Module_Data[8]='K';
    	Module_Data[9]='B';
    	Module_Data[10]='5';
    	Module_Data[11]='.';
    	Module_Data[12]='0';
    	Module_Data[13]=0;
    	
}
void Change_Wireless_Name_30(void)
{
	U8 i;
	Check_Data=0;
	Module_Data[0]=0xAA;
	Module_Data[1]=0x1D;
	Module_Data[2]=0X08;
	Module_Data[3]=0X01;
	
	Module_Data[4]=8;
	
	Module_Data[5]='R';
    	Module_Data[6]='K';
    	Module_Data[7]=' ';
    	Module_Data[8]='K';
    	Module_Data[9]='B';
    	Module_Data[10]='3';
    	Module_Data[11]='.';
    	Module_Data[12]='0';
    	Module_Data[13]=0;
}
void Deal_Wireless_Name(void)
{
	Change_Wireless_Name_50();
	Ready_ok=1;
	Send_Module_Data();
	CLR_WDT();
	delay_us(17000);
	CLR_WDT();
	Change_Wireless_Name_30();
	Ready_ok=1;
	Send_Module_Data();
	CLR_WDT();
	delay_us(17000);
	CLR_WDT();
	
}
//***********************************
U8 Read_Module_Data(void)
{
	U8 i,dat;
	dat=0;
	SPI_SCK=0;
	for(i=0;i<8;i++)
	{
		SPI_SCK=0;
		dat<<=1;
		if(SPI_MISO)
			dat|=0X01;
		else
			dat&=0xfe;
		SPI_SCK=1;	
	}
	SPI_SCK=1;
	return dat;
}

void Write_ReadState_Data(void)
{
	if(Ready_ok)
		return;
	if(Mode_USB)
		return;	
	//if(Scan_TimeUp)
	//	return;		
		
	Delay_Times_Module2++;
	if(Delay_Times_Module2<10)
	return;
	Delay_Times_Module2=0;
		
	Ready_ok=1;	
	Module_DataTimes=0;
	Check_Data=0;	
	Module_Read_Data(0);
	Send_Module_Data();
	b_Ready_To_Read=1;
	Record_Read_Times=0;
}
void Read_State_Data(void)
{
	U8 i,j;
	if(!b_Ready_To_Read)
		return;
	b_Ready_To_Read=0;	
	SPI_MOT_Out
	SPI_SCK_Out
	SPI_SS_Out
	delay_us(203);
	SPI_MOT=0;
	SPI_SS=0;	
	delay_us(3);
	EA=0;	
	Module_State_Data[0]=Read_Module_Data();
	Module_State_Data[1]=Read_Module_Data();
	Module_State_Data[3]=Read_Module_Data();
	Module_State_Data[2]=Read_Module_Data();
	EA=1;
	Ready_ok=0;
	b_Ready_To_Read=0;
	SPI_SS=1;	
	SPI_MOT=1;
	SPI_SCK_DirIn;
	SPI_SS_DirIn;
	SPI_MOT_DirIn;
	i=0x55-(Module_State_Data[2]+Module_State_Data[3]);
	if((Module_State_Data[0]==0xBB)&&(Module_State_Data[1]==i))// 处理读出来的正确数据
	{
		Module_LED_status=Module_State_Data[2]&0x07;
		
		Wirte_State=Module_State_Data[2]&0x18;
		Wirte_State=Wirte_State>>3;
		Wirte_State|=0x80;
		
		Module_LED_status2=Module_State_Data[2]&0x60;
		Module_LED_status2|=0X01;
		
		Power_status=0;
		Power_status=Module_State_Data[3]&0x07;
		Power_status=Power_status<<1;
		if(Module_State_Data[2]&0x80)
		Power_status|=0x01;
	}	
	
}
void Lang_KeyDown_ModuleMode(U8 Temp_ModuleMode_Times)
{
	Int_Module();
	Clear_Text_EMI_Data();	
	switch(Temp_ModuleMode_Times)
	{
		case 0:	
			//Mode_24G=1;
			//Module_Command_Data(1);
		break;
		case 1:	
			Mode_24G=1;
			Module_Command_Data(1);
		break;
		case 2:	
			Mode_Bluetooth1=1;
			Module_Command_Data(3);
		break;
		case 3:	
			Mode_Bluetooth2=1;
			Module_Command_Data(5);
		break;
		case 4:	
			Mode_Bluetooth3=1;
			Module_Command_Data(7);
		break;
	}
	Send_Module_Data();
	if(b_WASD_Mode)
	Read_WASD_Image(Image_Times);
}
U16 xdata  Change_ModeTimes;
void Short_KeyDown_ModuleMode(U8 Temp_ModuleMode_Times)
{
	U8 i;
	Int_Module();
	Clear_Text_EMI_Data();
	Change_ModeTimes=250;
	Power_status=9;
	switch(Temp_ModuleMode_Times)
	{
		case 0:	
			Mode_USB=1;
			Save_Mode_Time();
			Module_Command_Data(8);
			Module_State_Data[0]=Module_State_Data[1]=Module_State_Data[2]=Module_State_Data[3]=0;
			//RSTSTAT = 0x07;
			//		while(1);
		break;
		case 1:	
			//USBCON &= ~0xC0;
			Mode_24G=1;
			if(Mode_Bluetooth_Times!=4)
			{	
				Mode_Bluetooth_Times=4;
				Save_Mode_Time();
			}
			Module_Command_Data(0);
//			Lsat_Mode_now=Mode_now;
			Module_LED_status=0;
			bSpeed_data=0;
			Module_State_Data[0]=Module_State_Data[1]=Module_State_Data[2]=Module_State_Data[3]=0;
		break;
		case 2:	
			//USBCON &= ~0xC0;
			Mode_Bluetooth1=1;	
			if(Mode_Bluetooth_Times!=1)
			{	
				Mode_Bluetooth_Times=1;
				Save_Mode_Time();
			}
			Module_Command_Data(2);
			Module_LED_status=0;
			bSpeed_data=0;
			Module_State_Data[0]=Module_State_Data[1]=Module_State_Data[2]=Module_State_Data[3]=0;
		break;
		case 3:	
			Mode_Bluetooth2=1;
			if(Mode_Bluetooth_Times!=2)
			{	
				Mode_Bluetooth_Times=2;
				Save_Mode_Time();
			}
			Module_Command_Data(4);
			Module_LED_status=0;
			bSpeed_data=0;
			Module_State_Data[0]=Module_State_Data[1]=Module_State_Data[2]=Module_State_Data[3]=0;
		break;
		case 4:	
			Mode_Bluetooth3=1;
			if(Mode_Bluetooth_Times!=3)
			{	
				Mode_Bluetooth_Times=3;
				Save_Mode_Time();
			}
			Module_Command_Data(6);
			Module_LED_status=0;
			bSpeed_data=0;
			Module_State_Data[0]=Module_State_Data[1]=Module_State_Data[2]=Module_State_Data[3]=0;
		break;
	}
	if(b_WASD_Mode)
	Read_WASD_Image(Image_Times);
}