#include "..\include\SH68F90.h"
#include "..\include\stdtype.h"
#include "..\include\mcu_def.h"
#include "..\include\pwm_control.h"
#include "..\include\key_decode.h"
#include ".\include\Auser.h"
#include "..\include\CFG.h"
#include ".\include\ABSACC.H"
#include <intrins.h>
#include <string.h>
//*******************************
bit fhas_change;	
U8	idata	V_Data[21];
U8	xdata	Last_V_Data[21];
U8	idata	break_Data[21];
U8 data 	Scan_TimeUp;//检测fn是否按下，按下值等于0，没按下值大于0
U16 data 	No_Key_Times;//有按键值就会清零，或者每隔1s清零
U16 data 	No_Key_Times2;//在定时器2里每隔1s统计按键空闲时间，有按键按下，或者驱动发命令了就会清零
U8 	data 	bi;//bi=0x00:单个键值  bi=0xaa:六个键值  bi=0x00:重复键值
U8	idata	Multimedia_Data[2];
U8	idata	Last_Multimedia_Data[2];
U8	idata	Usb2_Data[16];
U8	idata	Last_Usb2_Data[16];
U8	idata	Send_data[7];
U8	idata	Last_Send_data[7];
U8	data	Touch_Long_Delay;
U8	data	ALU1;
U8	data	Key_Index;
bit	bSend_IN2;
bit	bFn;  //fn是否按下标志，按下是1，没按下是0
bit	Ready_6;//=1是一次性按下六个键，=0是一次性没按下六个键
bit	b_01;
bit	b_04;
bit	bchange_key;
bit	bWin_Locks;//=1是锁住win键，=0是没锁住win键
bit	bAll_Key_Lock;
U8 	xdata Sleep_Times;
bit	Wireless_suspend;//端口为低电平就进来，这个值=1 控制休眠，由拨动开关决定
bit	Wire_suspend_1;
bit	b_IOS_Mode;
bit 	Reset_Mode;
//*******************************
bit	bSpeed_End;
code const U8 USB_Tab_Fn[21*6]=//fn+一些组合键的hid键码
{
	0x00,			0x00,		0x00,				0x00,		0x00,	0x00,  //c0 esc-》Ctrl_L
	0x00,			H_S1,		M_Nop,				G_IOS_0,	0x00,	G_WIN, //c1
	M_Computer,		H_S2,		M_Nop,				G_IOS_1,	0x00,	0x00,  //c2	
	M_Home,			H_S3,		M_Nop,				0x00,		0x00,	0x00,  //c3
	M_Mail,			0x00,		0x00,				0x00,		0x00,	0x00,  //c4	
	M_Calculator,	0x00,		0x00,				0x00,		0x00,	C_REST,//c5
	M_Media,		0x00,		0x48,				0x00, 		0x00,	0x00,  //c6
	M_Stop,			0x00,		KEY_HOME,KEY_END,	0x00,		0x00,		   //c7
	M_Previous,		0x00,		KEY_PGUP,KEY_PGDN,	0x00,		0x00,		   //c8	     	
	M_Play,			0x00,		0x00,				0x00,		0x00,	0x00,  //c9	
	M_Next,			0x00,		M_Nop,				0x00,		0x00,	0x00,  //c10
	M_Mute,			0x00,		0x00,				0x00, 		0x00,	0x00,  //c11
	M_VDn,			0x00,		0x00,				0x00,		0x00,	0x00,  //c12
	M_VUp,			0x00,		0x00,				0x00,		0x00,	0x00,  //c13
	H_Record,		H_Logo,		0x00,				0x00,		0x00,	H_SDn, //c14	
	H_Mode,			0x00,		0x00,				0X00,		H_BUp,	H_BDn, //c15
	H_Color,		0x00,		0x00,				0X00,		0x00,	H_SUp, //c16
	0x00,			0x00,		0x00,				0X00,		0x00,	0x00,  //c17
	0x00,			0x00,		0x00,				0X00,		0x00,	0x00,  //c18
	0x00,			0x00,		0x00,				0X00,		0x00,	0x00,  //c19
	0x00,			0x00,		0x00,				0X00,		0x00,	0x00,  //c20
};
//****************************************
void F_Clear_Send_data()//清除发送数据数组
{
	U8 i;
	for(i=0; i<7; i++)
	{
		Send_data[i] = 0;
	}
}
void F_Clear_USB456(void)//清除待发送usb数据,像多媒体之类的
{
	U8 i;
	for(i=0; i<16; i++)
	{
		Usb2_Data[i] = 0x00;
	}
	Multimedia_Data[0]=0x00;
	Multimedia_Data[1]=0x00;
}
U8 Deal_IN2_Data(U8 Data_i)//把读进来的参数左移1位，再返回出去
{
	U8 i;
	i=1<<Data_i;	
	return (i);
}
void Deal_Keybord_Data(U8 Data_Temp2)//判断是否一次性采集到6个的键盘数据和判断采集到的键值是否重复
{
	U8 i,j;
		bi=0x00;
		j=0x01;
		for(i=1; i<7; i++)//循环六次，1到6
		{
			if(Send_data[i]==Data_Temp2)
			{
				ALU1|=j;
				bi=0xff;	
				break;
			}
			j=j<<1;
		}
		if((Ready_6)&&(bi!=0xff))//一次性采集到六个键值Ready_6=1并且键值没有重复
			bi=0xaa;
}
void Deal_Keybord_Data2(U8 Keybord_Data)//处理单个键盘数据
{
	U8 i,j;
	j=0x01;
	for(i=1; i<7; i++)
	{
		if(!Send_data[i])
		{
			Send_data[i]=Keybord_Data;
			ALU1|=j;
			break;
		}
		j=j<<1;
	}
}
void Keyboard_Up_Vale(void)//这个函数不知道具体有什么用
{
	U8 i2,i3,j;
	U32 i;
	U8 Temp0,Temp1,Temp2,Temp3;
	U16 Temp_Key_Index;
	Temp_Key_Index=Key_Index*4;
	Temp0=CBYTE[0xC600+Temp_Key_Index];
	Temp1=CBYTE[0xC600+Temp_Key_Index+1];
	Temp2=CBYTE[0xC600+Temp_Key_Index+2];
	Temp3=CBYTE[0xC600+Temp_Key_Index+3];
}
void Keyboard_Tab_Vale(void)
{
	U8 i2,i3,j;
	U32 i;
	U8 	Temp0,Temp1,Temp2,Temp3;
	U16 Temp_Key_Index;
	j=Deal_Tbl_Image2(Key_Index);//返回那个被按下的按键编号 0~125
	Temp_Key_Index=Key_Index*4;//Key_Index:按键索引值，从0 for循环加加到125
	if(!bFn)//fn按键没按下
	{	
		Temp0=CBYTE[0xC600+Temp_Key_Index];
		Temp1=CBYTE[0xC600+Temp_Key_Index+1];
		Temp2=CBYTE[0xC600+Temp_Key_Index+2];
		Temp3=CBYTE[0xC600+Temp_Key_Index+3];
		if(j==17)//某个按键
			Multimedia_Tab_Data(1);//上一曲
		else if(j==18)
			Multimedia_Tab_Data(3);//播放/暂停
		else if(j==19)
			Multimedia_Tab_Data(0);//下一曲
		else if(j==20)
			Multimedia_Tab_Data(4);//静音	
	}
	else//fn按键按下
	{
		Temp2=USB_Tab_Fn[Key_Index];//根据序号得到一个hid键码
		if(Temp2>0)	//说明fn+按键是有效组合键功能
		{	
			Temp0=0x80;
			Temp1=Temp3=0;
			switch(Temp2)
			{
				case C_REST://复位键，按下超过一定时间就会执行复位
					if((!b_Record_Mode)&&(!b_Feel_Mode))
					{	
						Touch_Long_Delay++;
						if(Touch_Long_Delay>250)
						{
							Touch_Long_Delay=0;
							Clear_Mode_Data();//清除模式数据
							Reset_Mode=1;//复位模式标志等于1
						}
					}
				break;	
				//---------------------------------
				case M_Computer:	//F1
					if(!b_IOS_Mode)//第3行第1列的按键按下了，b_IOS_Mode=0，  第3行第2列的按键按下了，b_IOS_Mode=1，行列从0开始  
						Multimedia_Tab_Data(M_Computer&0x7F);
					else
						Temp2=0x3A;	//3a：f1的hid键码值
				break;
				//---------------------------------
				case M_Home:
					if(!b_IOS_Mode)	//F2
						Multimedia_Tab_Data(M_Home&0x7F);
					else
						Temp2=0x3B;		
				break;	
				//---------------------------------
				case M_Mail:
					if(!b_IOS_Mode)	//F3
						Multimedia_Tab_Data(M_Mail&0x7F);
					else
						Temp2=0x3C;		
				break;	
				//---------------------------------
				case M_Calculator:
					if(!b_IOS_Mode)	//F4
						Multimedia_Tab_Data(M_Calculator&0x7F);
					else
						Temp2=0x3D;		
				break;	
				//---------------------------------
				case M_Media:
					if(!b_IOS_Mode)	//F5
						Multimedia_Tab_Data(M_Media&0x7F);
					else
						Temp2=0x3E;		
				break;
				//---------------------------------
				case M_Stop:
					if(!b_IOS_Mode)	//F6
						Multimedia_Tab_Data(M_Stop&0x7F);
					else
						Temp2=0x3F;	
				break;	
				//---------------------------------
				case M_Previous://F7
					Multimedia_Tab_Data(M_Previous&0x7F);
				break;	
				//---------------------------------
				case M_Play://F8
					Multimedia_Tab_Data(M_Play&0x7F);
				break;	
				//---------------------------------
				case M_Next://F9
					Multimedia_Tab_Data(M_Next&0x7F);
				break;
				//---------------------------------
				case M_Mute://F10
					Multimedia_Tab_Data(M_Mute&0x7F);
				break;	
				//---------------------------------
				case M_VDn://F11
					Multimedia_Tab_Data(M_VDn&0x7F);
				break;	
				//---------------------------------
				case M_VUp://F12
					Multimedia_Tab_Data(M_VUp&0x7F);
				break;	
				//---------------------------------	
				case  G_WIN://fn+win 锁定解开win键
					if(break_Data[1]&0x20)
					{
						bWin_Locks=~bWin_Locks;	
					}
				break;		
				//---------------------------------
				case  G_IOS_0:	//第3行第1列按键按下 行列从0开始
					if(break_Data[1]&0x08)
					{
						b_IOS_Mode=0;
						bSpeed_End=1;
					//	Save_KeyIndex_Data();	
					}
				break;
				//---------------------------------
				case  G_IOS_1:	//第3行第2列按键按下 行列从0开始 
					if(break_Data[2]&0x08)
					{
						b_IOS_Mode=1;
						bSpeed_End=1;
					//	Save_KeyIndex_Data();
					}
				break;
				//---------------------------------
				case  H_Mode	:
					if(break_Data[15]&0x01)//灯的模式++
					{
						Mode_Times++;
						if(Mode_Times>21)//加到21个模式又从第一个轮询开始
						Mode_Times=1;	
						Change_Mode2();	//执行21种灯效模式
					}	
				break;
				//---------------------------------
				case  H_Logo	:
					if(break_Data[14]&0x02)//侧光灯模式切换，fn+ins
					{
						Logo_Mode_Times++;
						if(Logo_Mode_Times>3)
						Logo_Mode_Times=0;	
						Int_Logo_Data();//侧光灯模式切换函数
					}	
				break;
				//---------------------------------
				case  H_Record:
					if((break_Data[14]&0x01)&&(b_WASD_Mode))
					{
						if(!b_Record_Mode)
						{
							b_Record_Mode=1;
							Clear_All_Image();
							bSpeed_End=1;
						}	
						else
						{
							b_Record_Mode=0;
							bSpeed_End=0;
							Save_Flash_Data();//保存flash数据
							Save_Mode_Time();//保存模式时间
						}
					}	
				break;
				//---------------------------------
				case  H_S1	:
					if(break_Data[1]&0x02)
					{
						Mode_Times=19;	
						Image_Times=1;//读取flash不同地址的值
						Change_Mode2();	
					}	
				break;
				//---------------------------------
				case  H_S2	:
					if(break_Data[2]&0x02)
					{
						Mode_Times=19;	
						Image_Times=2;
						Change_Mode2();	
					}	
				break;
				//---------------------------------
				case  H_S3	:
					if(break_Data[3]&0x02)
					{
						Mode_Times=19;	
						Image_Times=3;
						Change_Mode2();	
					}	
				break;
				//---------------------------------
				case H_Color://控制灯的颜色-单色模式
					if((break_Data[16]&0x01)&&(!b_WASD_Mode))
					{
							if(Color_Times==0)//红--黄--蓝--绿。。。
								Color_Times=7;
							Color_Times++;
							if(Color_Times>8)
								Color_Times=1;
							Last_CL_Brightness_Wheels=0xAA;	
							b_Cloes_Mode=0;
							Clear_All_Image();	
							if((!b_SuiLiang_Mode)&&(!b_HangPao_Mode)&&(!b_PaoMa1_Mode)	\
								&&(!b_PaoMa2_Mode)&&(!b_PaoMa3_Mode)&&(!b_PaoMa4_Mode)	\
								&&(!b_Effect_light_1)&&(!b_Effect_light_2))
							Let_NUM_Image();	//给所有按键 付颜色
							Int_Mode6_Data();
							if(b_WASD_Mode)
								Read_WASD_Image(Image_Times);
							Save_Mode_Time();
					}
				break;
				//---------------------------------
				case H_BUp:
					if(break_Data[15]&0x10)
					{
						Last_CL_Brightness_Wheels=0xAA;	
						Brightness_Add();//亮度增加调节
					}	
				break;	
				//---------------------------------
				case H_BDn:	
					if(break_Data[15]&0x20)
					{
						Last_CL_Brightness_Wheels=0xAA;	
						Brightness_Sub();//亮度减少调节
					}	
				break;	
				//---------------------------------
				case H_SUp:	
					if(break_Data[16]&0x20)
					{
						if(Speed_Data)//显示波浪模式的速度调节，速度变慢
							Speed_Data--;
						if(Speed_Data==0)
							bSpeed_End=1;	//bSpeed_End=1不需要调节灯模式的速度,=0说明需要调节灯模式的速度
					}	
				break;	
				//---------------------------------
				case H_SDn:	
					if(break_Data[14]&0x20)
					{
						if(Speed_Data<4)//显示波浪模式的速度调节，速度变快
							Speed_Data++;
						if(Speed_Data==4)
							bSpeed_End=1;
					}	
				break;		
			}
		}
		else//fn+按键是无效组合键
		{
			Temp0=CBYTE[0xC600+Temp_Key_Index];
			Temp1=CBYTE[0xC600+Temp_Key_Index+1];
			Temp2=CBYTE[0xC600+Temp_Key_Index+2];
			Temp3=CBYTE[0xC600+Temp_Key_Index+3];
		}
	}
	//***************FN*****************
	if(Temp0==0x80)//fn+按键得出一个有效组合键值就会成立
	{
		if((Temp2&0x80)==0)//Temp2第0位不为1就成立  1000 0000  Temp2！=0x8y~0xfy(y是0到f) 按了fn+按键得到的有效组合键都大于0x80
		{
			Deal_Keybord_Data(Temp2);
			if(bi==0x00)//单个按键
			Deal_Keybord_Data2(Temp2);
		}
	}	
	//***********正常按键值**************
	else if(Temp0==0x00)//没有fn按下，只有其它键
	{	
		if(b_IOS_Mode)
		{
			if(Temp1==0x08)
				Temp1=0x04;//L_Alt
			else if(Temp1==0x04)
				Temp1=0x08;//L_win
			else if(Temp1==0x40)
				Temp1=0x80;//R_WIN
		}	
		if(bWin_Locks)//锁住了win键
		{
			if(j==115)
				Temp2=0;
		}	
		Send_data[0]|=Temp1;	//Shift...  特殊键：shift Ctrl Alt win
		if((bWin_Locks)&&(!b_IOS_Mode))//锁住了win键
		{
			Send_data[0]&=~0x88;//0x88:1000 1000     ~0x88:0111 0111,不记录L_Win和R_Win的值，按下去win没有用
		}
		if(Temp2)	
		{	
			Deal_Keybord_Data(Temp2);
			if(bi==0x00)
			Deal_Keybord_Data2(Temp2);
		}
		if(Temp3)	
		{	
			Deal_Keybord_Data(Temp3);
			if(bi==0x00)
			Deal_Keybord_Data2(Temp3);
		}
		//--------------------
		if(bi==0xaa)
		{	
			if(Mode_USB)
			{	
				if(Temp2)
				{	
					if(Temp2!=0xb0)//1011 0000
					{	
						i2=(Temp2-4)/8;
						i3=(Temp2-4)%8;
						Usb2_Data[i2+1]|=Deal_IN2_Data(i3);
					}
				}
				if(Temp3)
				{	
					if(Temp3!=0xb0)
					{
						i2=(Temp3-4)/8;
						i3=(Temp3-4)%8;
						Usb2_Data[i2+1]|=Deal_IN2_Data(i3);
					}
				}
			}
			else
			{
				if(Temp2)
				{	
					if(Temp2!=0xb0)
					{	
						i2=Temp2/8;
						i3=Temp2%8;
						Usb2_Data[i2+2]|=Deal_IN2_Data(i3);
					}
				}
				if(Temp3)
				{	
					if(Temp3!=0xb0)
					{
						i2=Temp3/8;
						i3=Temp3%8;
						Usb2_Data[i2+2]|=Deal_IN2_Data(i3);
					}
				}
			}
		}
	}
	//**************多媒体******************
	else if(Temp0==0x01)//多媒体
	{
		Multimedia_Data[0]=Temp2;
		Multimedia_Data[1]=Temp3;
	}
	//*****************宏********************
	else if(Temp0==0x02)
	{
		if(Temp2==0x04)	//按住一直发
			{	
				i=0x0001;
				i=i<<Temp1;
				fg_Send_Macro|=i;
				Macro_Cycle_Time[Temp1]=1;
			}
		else if(Temp2==0x01)//发几次
			{	
				i=0x000001;
				i=i<<Temp1;
				if(break_Data[Port_Data(Key_Index)]&Pin_Data(Key_Index))
				{
					fg_Send_Macro|=i;
					Macro_Cycle_Time[Temp1]=Temp3;
				}	
			}
	}
}
void Move_Key_value(void)//移动键值
{ 
	U8 xdata i,i1,y,Key_Count;
	U16 j;
	Key_Count=0;
	Key_Index=0;	//刚进来清零
		bFn=0;//清除上一次fn按下的痕迹
	if(V_Data[9]&0x20)//fn按键被按下
		bFn=1;	
	for(i=0;i<21;i++)
	{
		if(V_Data[i])//如果有按键按下，按键值++
			Key_Count++;
	}
	i1=0;
	for(i=0;i<21;i++)//循环21列
	{
		if(V_Data[i]!=Last_V_Data[i])//现在的键值状态和上一次键值状态不一致
		{	
			Last_V_Data[i]=V_Data[i];//把现在的键值状态赋给上一次键值
			i1=1;
		}
	}
	if(i1==1)//有键值状态改变就退出该函数
		return;
	if(Key_Count)//按下的键值大于0，有按键按下
	{	
		No_Key_Times=0;
		No_Key_Times2=0;
		if(bFn)//fn按键按下
			Scan_TimeUp=0;
		else//fn按键没按下	
			Scan_TimeUp=110;
	}
	else//没有任何按键按下
	{
		F_Clear_Send_data();//清除发送数据
		F_Clear_USB456();//清除待发送usb数据,像多媒体之类的
		for(i=0;i<21;i++)
			break_Data[i]=0X3F;//0011 1111
		if(Scan_TimeUp)//没有fn按键按下
			Scan_TimeUp--;
		Ready_6=0;

		/*休眠时间*/
		if(Sleep_Times==1)			//5min
			j=300;
		else if(Sleep_Times==2)	//10min
			j=600;	
		else if(Sleep_Times==3)	//20min
			j=1200;
		else if(Sleep_Times==4)	//30min
			j=1800;	
		else if(Sleep_Times==5)	//Mac min
			j=0xFFFF;		
		else
			j=300;	
		if(No_Key_Times2>j)//No_Key_Times2:在定时器2里一秒加一次，超过设定时间就休眠
		{	
			No_Key_Times2=0;
			if(!Mode_USB)//这个端口为低电平0就进来
				Wireless_suspend=1;
			else if(Mode_USB)//这个端口为高电平0就进来
				fg_suspend=1;//Wire_suspend_1=1;
		}	
		return;//没按键就退出这个函数，不继续执行下面的内容
	}	
	ALU1=0;	
	F_Clear_USB456();//清除待发送usb数据,像多媒体之类的
	Send_data[0]=0;
	for(i1=0;i1<21;i1++)
	{
			y=0x01;
		for(i=0;i<6;i++)
		{
			if(V_Data[i1]&y)//y刚开始的值为0x01，for循环六次，每次左移一位，循环完又变成0x01；  有按键按下
			{	//有按键按下时，第0行V_Data[i1]的值是0x01  第1行V_Data[i1]的值是0x02  第2行V_Data[i1]的值是0x04。。。。第5行V_Data[i1]的值是0x20
				Keyboard_Tab_Vale();	
				Deal_KeyDown();	//LED灯的模式变换，选择哪种模式
				break_Data[i1]&=~y;
			}
			else//没按键按下
			{
				break_Data[i1]|=y;
				Keyboard_Up_Vale();	//不知道有什么用，查看函数具体也没说用到哪里
			}
			Key_Index++;//按键序号 最多加到21*6
			y=y<<1;
		}
	}
	if(Mode_USB)//usb有线模式下
	{	
		if((Send_data[1])&&(Send_data[2])&&(Send_data[3])&&(Send_data[4])&&(Send_data[5])&&(Send_data[6]))//六个键值都有数据
			Ready_6=1;	
	}
	else
	{	
		if((Send_data[1])&&(Send_data[2])&&(Send_data[3])&&(Send_data[4])&&(Send_data[5]))//五个键值都有数据
			Ready_6=1;		
	}
	{	
		if(!(ALU1&0x01))//有采集到键值就不进来
			Send_data[1]=0;//清空数组的按键数据
		if(!(ALU1&0x02))
			Send_data[2]=0;	
		if(!(ALU1&0x04))
			Send_data[3]=0;
		if(!(ALU1&0x08))
			Send_data[4]=0;
		if(!(ALU1&0x10))
			Send_data[5]=0;	
		if(!(ALU1&0x20))
			Send_data[6]=0;	
	}	
	//------------------------------------	
}
void Send_Usb_value(void)//发送USB值
{
	U8 i;
	for(i=0;i<7;i++)//六键无冲键值
	{
		if(Send_data[i]!=Last_Send_data[i])//上一次采集的数据和当前采集的数据不相等  
		{
			bSend_IN2=1;
			Last_Send_data[i]=Send_data[i];//当前采集到的键值赋值给上一次采集的键值数组
		}
	}
	for(i=0;i<16;i++)	//全键无冲键值
	{
		if(Usb2_Data[i]!=Last_Usb2_Data[i])
		{
			b_04=1;
			Last_Usb2_Data[i]=Usb2_Data[i];
		}
	}
	for(i=0;i<2;i++)	//多媒体数据
	{
		if(Multimedia_Data[i]!=Last_Multimedia_Data[i])
			{
				b_01=1;
				Last_Multimedia_Data[i]=Multimedia_Data[i];
			}
	}
}
//--------------------------------------
void Deal_Rest_Data(void)
{
	Clear_Mode_Data();
	Read_KeyIndex_Data();
	b_IOS_Mode=0;
	Mode_Times=6;
	Image_Times=1;
	Color_Times=8; 
	bWin_Locks=bAll_Key_Lock=bchange_key=0;
	Brightness_Wheels=5;
	Speed_Data=2;
	Sleep_Times=1;
	Clear_Flash_Data();
	Change_Mode2();	
	Reset_Mode=0;
}
void Deal_Rest(void)
{
	U8 i;
	if(Reset_Mode)
	{	
		Run_Time++;
		if(Run_Time<100)
			{
				for(i=0; i<126; i++)
				{
					Image[0][i]=1024;
					Image[1][i]=0;
					Image[2][i]=0;
				}
			}
		else if(Run_Time==100)
			{
				for(i=0; i<126; i++)
				{
					Image[1][i]=1024;
					Image[0][i]=0;
					Image[2][i]=0;
				}
			}
		else if(Run_Time==200)
			{
				for(i=0; i<126; i++)
				{
					Image[2][i]=1024;
					Image[1][i]=0;
					Image[0][i]=0;
				}
			}	
		else if(Run_Time>300)
			{
				Run_Time=310;
				
				Deal_Rest_Data();
			}	
	}
}