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
U8 data 	Scan_TimeUp;//���fn�Ƿ��£�����ֵ����0��û����ֵ����0
U16 data 	No_Key_Times;//�а���ֵ�ͻ����㣬����ÿ��1s����
U16 data 	No_Key_Times2;//�ڶ�ʱ��2��ÿ��1sͳ�ư�������ʱ�䣬�а������£����������������˾ͻ�����
U8 	data 	bi;//bi=0x00:������ֵ  bi=0xaa:������ֵ  bi=0x00:�ظ���ֵ
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
bit	bFn;  //fn�Ƿ��±�־��������1��û������0
bit	Ready_6;//=1��һ���԰�����������=0��һ����û����������
bit	b_01;
bit	b_04;
bit	bchange_key;
bit	bWin_Locks;//=1����סwin����=0��û��סwin��
bit	bAll_Key_Lock;
U8 	xdata Sleep_Times;
bit	Wireless_suspend;//�˿�Ϊ�͵�ƽ�ͽ��������ֵ=1 �������ߣ��ɲ������ؾ���
bit	Wire_suspend_1;
bit	b_IOS_Mode;
bit 	Reset_Mode;
//*******************************
bit	bSpeed_End;
code const U8 USB_Tab_Fn[21*6]=//fn+һЩ��ϼ���hid����
{
	0x00,			0x00,		0x00,				0x00,		0x00,	0x00,  //c0 esc-��Ctrl_L
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
void F_Clear_Send_data()//���������������
{
	U8 i;
	for(i=0; i<7; i++)
	{
		Send_data[i] = 0;
	}
}
void F_Clear_USB456(void)//���������usb����,���ý��֮���
{
	U8 i;
	for(i=0; i<16; i++)
	{
		Usb2_Data[i] = 0x00;
	}
	Multimedia_Data[0]=0x00;
	Multimedia_Data[1]=0x00;
}
U8 Deal_IN2_Data(U8 Data_i)//�Ѷ������Ĳ�������1λ���ٷ��س�ȥ
{
	U8 i;
	i=1<<Data_i;	
	return (i);
}
void Deal_Keybord_Data(U8 Data_Temp2)//�ж��Ƿ�һ���Բɼ���6���ļ������ݺ��жϲɼ����ļ�ֵ�Ƿ��ظ�
{
	U8 i,j;
		bi=0x00;
		j=0x01;
		for(i=1; i<7; i++)//ѭ�����Σ�1��6
		{
			if(Send_data[i]==Data_Temp2)
			{
				ALU1|=j;
				bi=0xff;	
				break;
			}
			j=j<<1;
		}
		if((Ready_6)&&(bi!=0xff))//һ���Բɼ���������ֵReady_6=1���Ҽ�ֵû���ظ�
			bi=0xaa;
}
void Deal_Keybord_Data2(U8 Keybord_Data)//��������������
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
void Keyboard_Up_Vale(void)//���������֪��������ʲô��
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
	j=Deal_Tbl_Image2(Key_Index);//�����Ǹ������µİ������ 0~125
	Temp_Key_Index=Key_Index*4;//Key_Index:��������ֵ����0 forѭ���Ӽӵ�125
	if(!bFn)//fn����û����
	{	
		Temp0=CBYTE[0xC600+Temp_Key_Index];
		Temp1=CBYTE[0xC600+Temp_Key_Index+1];
		Temp2=CBYTE[0xC600+Temp_Key_Index+2];
		Temp3=CBYTE[0xC600+Temp_Key_Index+3];
		if(j==17)//ĳ������
			Multimedia_Tab_Data(1);//��һ��
		else if(j==18)
			Multimedia_Tab_Data(3);//����/��ͣ
		else if(j==19)
			Multimedia_Tab_Data(0);//��һ��
		else if(j==20)
			Multimedia_Tab_Data(4);//����	
	}
	else//fn��������
	{
		Temp2=USB_Tab_Fn[Key_Index];//������ŵõ�һ��hid����
		if(Temp2>0)	//˵��fn+��������Ч��ϼ�����
		{	
			Temp0=0x80;
			Temp1=Temp3=0;
			switch(Temp2)
			{
				case C_REST://��λ�������³���һ��ʱ��ͻ�ִ�и�λ
					if((!b_Record_Mode)&&(!b_Feel_Mode))
					{	
						Touch_Long_Delay++;
						if(Touch_Long_Delay>250)
						{
							Touch_Long_Delay=0;
							Clear_Mode_Data();//���ģʽ����
							Reset_Mode=1;//��λģʽ��־����1
						}
					}
				break;	
				//---------------------------------
				case M_Computer:	//F1
					if(!b_IOS_Mode)//��3�е�1�еİ��������ˣ�b_IOS_Mode=0��  ��3�е�2�еİ��������ˣ�b_IOS_Mode=1�����д�0��ʼ  
						Multimedia_Tab_Data(M_Computer&0x7F);
					else
						Temp2=0x3A;	//3a��f1��hid����ֵ
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
				case  G_WIN://fn+win �����⿪win��
					if(break_Data[1]&0x20)
					{
						bWin_Locks=~bWin_Locks;	
					}
				break;		
				//---------------------------------
				case  G_IOS_0:	//��3�е�1�а������� ���д�0��ʼ
					if(break_Data[1]&0x08)
					{
						b_IOS_Mode=0;
						bSpeed_End=1;
					//	Save_KeyIndex_Data();	
					}
				break;
				//---------------------------------
				case  G_IOS_1:	//��3�е�2�а������� ���д�0��ʼ 
					if(break_Data[2]&0x08)
					{
						b_IOS_Mode=1;
						bSpeed_End=1;
					//	Save_KeyIndex_Data();
					}
				break;
				//---------------------------------
				case  H_Mode	:
					if(break_Data[15]&0x01)//�Ƶ�ģʽ++
					{
						Mode_Times++;
						if(Mode_Times>21)//�ӵ�21��ģʽ�ִӵ�һ����ѯ��ʼ
						Mode_Times=1;	
						Change_Mode2();	//ִ��21�ֵ�Чģʽ
					}	
				break;
				//---------------------------------
				case  H_Logo	:
					if(break_Data[14]&0x02)//����ģʽ�л���fn+ins
					{
						Logo_Mode_Times++;
						if(Logo_Mode_Times>3)
						Logo_Mode_Times=0;	
						Int_Logo_Data();//����ģʽ�л�����
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
							Save_Flash_Data();//����flash����
							Save_Mode_Time();//����ģʽʱ��
						}
					}	
				break;
				//---------------------------------
				case  H_S1	:
					if(break_Data[1]&0x02)
					{
						Mode_Times=19;	
						Image_Times=1;//��ȡflash��ͬ��ַ��ֵ
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
				case H_Color://���ƵƵ���ɫ-��ɫģʽ
					if((break_Data[16]&0x01)&&(!b_WASD_Mode))
					{
							if(Color_Times==0)//��--��--��--�̡�����
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
							Let_NUM_Image();	//�����а��� ����ɫ
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
						Brightness_Add();//�������ӵ���
					}	
				break;	
				//---------------------------------
				case H_BDn:	
					if(break_Data[15]&0x20)
					{
						Last_CL_Brightness_Wheels=0xAA;	
						Brightness_Sub();//���ȼ��ٵ���
					}	
				break;	
				//---------------------------------
				case H_SUp:	
					if(break_Data[16]&0x20)
					{
						if(Speed_Data)//��ʾ����ģʽ���ٶȵ��ڣ��ٶȱ���
							Speed_Data--;
						if(Speed_Data==0)
							bSpeed_End=1;	//bSpeed_End=1����Ҫ���ڵ�ģʽ���ٶ�,=0˵����Ҫ���ڵ�ģʽ���ٶ�
					}	
				break;	
				//---------------------------------
				case H_SDn:	
					if(break_Data[14]&0x20)
					{
						if(Speed_Data<4)//��ʾ����ģʽ���ٶȵ��ڣ��ٶȱ��
							Speed_Data++;
						if(Speed_Data==4)
							bSpeed_End=1;
					}	
				break;		
			}
		}
		else//fn+��������Ч��ϼ�
		{
			Temp0=CBYTE[0xC600+Temp_Key_Index];
			Temp1=CBYTE[0xC600+Temp_Key_Index+1];
			Temp2=CBYTE[0xC600+Temp_Key_Index+2];
			Temp3=CBYTE[0xC600+Temp_Key_Index+3];
		}
	}
	//***************FN*****************
	if(Temp0==0x80)//fn+�����ó�һ����Ч��ϼ�ֵ�ͻ����
	{
		if((Temp2&0x80)==0)//Temp2��0λ��Ϊ1�ͳ���  1000 0000  Temp2��=0x8y~0xfy(y��0��f) ����fn+�����õ�����Ч��ϼ�������0x80
		{
			Deal_Keybord_Data(Temp2);
			if(bi==0x00)//��������
			Deal_Keybord_Data2(Temp2);
		}
	}	
	//***********��������ֵ**************
	else if(Temp0==0x00)//û��fn���£�ֻ��������
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
		if(bWin_Locks)//��ס��win��
		{
			if(j==115)
				Temp2=0;
		}	
		Send_data[0]|=Temp1;	//Shift...  �������shift Ctrl Alt win
		if((bWin_Locks)&&(!b_IOS_Mode))//��ס��win��
		{
			Send_data[0]&=~0x88;//0x88:1000 1000     ~0x88:0111 0111,����¼L_Win��R_Win��ֵ������ȥwinû����
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
	//**************��ý��******************
	else if(Temp0==0x01)//��ý��
	{
		Multimedia_Data[0]=Temp2;
		Multimedia_Data[1]=Temp3;
	}
	//*****************��********************
	else if(Temp0==0x02)
	{
		if(Temp2==0x04)	//��סһֱ��
			{	
				i=0x0001;
				i=i<<Temp1;
				fg_Send_Macro|=i;
				Macro_Cycle_Time[Temp1]=1;
			}
		else if(Temp2==0x01)//������
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
void Move_Key_value(void)//�ƶ���ֵ
{ 
	U8 xdata i,i1,y,Key_Count;
	U16 j;
	Key_Count=0;
	Key_Index=0;	//�ս�������
		bFn=0;//�����һ��fn���µĺۼ�
	if(V_Data[9]&0x20)//fn����������
		bFn=1;	
	for(i=0;i<21;i++)
	{
		if(V_Data[i])//����а������£�����ֵ++
			Key_Count++;
	}
	i1=0;
	for(i=0;i<21;i++)//ѭ��21��
	{
		if(V_Data[i]!=Last_V_Data[i])//���ڵļ�ֵ״̬����һ�μ�ֵ״̬��һ��
		{	
			Last_V_Data[i]=V_Data[i];//�����ڵļ�ֵ״̬������һ�μ�ֵ
			i1=1;
		}
	}
	if(i1==1)//�м�ֵ״̬�ı���˳��ú���
		return;
	if(Key_Count)//���µļ�ֵ����0���а�������
	{	
		No_Key_Times=0;
		No_Key_Times2=0;
		if(bFn)//fn��������
			Scan_TimeUp=0;
		else//fn����û����	
			Scan_TimeUp=110;
	}
	else//û���κΰ�������
	{
		F_Clear_Send_data();//�����������
		F_Clear_USB456();//���������usb����,���ý��֮���
		for(i=0;i<21;i++)
			break_Data[i]=0X3F;//0011 1111
		if(Scan_TimeUp)//û��fn��������
			Scan_TimeUp--;
		Ready_6=0;

		/*����ʱ��*/
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
		if(No_Key_Times2>j)//No_Key_Times2:�ڶ�ʱ��2��һ���һ�Σ������趨ʱ�������
		{	
			No_Key_Times2=0;
			if(!Mode_USB)//����˿�Ϊ�͵�ƽ0�ͽ���
				Wireless_suspend=1;
			else if(Mode_USB)//����˿�Ϊ�ߵ�ƽ0�ͽ���
				fg_suspend=1;//Wire_suspend_1=1;
		}	
		return;//û�������˳����������������ִ�����������
	}	
	ALU1=0;	
	F_Clear_USB456();//���������usb����,���ý��֮���
	Send_data[0]=0;
	for(i1=0;i1<21;i1++)
	{
			y=0x01;
		for(i=0;i<6;i++)
		{
			if(V_Data[i1]&y)//y�տ�ʼ��ֵΪ0x01��forѭ�����Σ�ÿ������һλ��ѭ�����ֱ��0x01��  �а�������
			{	//�а�������ʱ����0��V_Data[i1]��ֵ��0x01  ��1��V_Data[i1]��ֵ��0x02  ��2��V_Data[i1]��ֵ��0x04����������5��V_Data[i1]��ֵ��0x20
				Keyboard_Tab_Vale();	
				Deal_KeyDown();	//LED�Ƶ�ģʽ�任��ѡ������ģʽ
				break_Data[i1]&=~y;
			}
			else//û��������
			{
				break_Data[i1]|=y;
				Keyboard_Up_Vale();	//��֪����ʲô�ã��鿴��������Ҳû˵�õ�����
			}
			Key_Index++;//������� ���ӵ�21*6
			y=y<<1;
		}
	}
	if(Mode_USB)//usb����ģʽ��
	{	
		if((Send_data[1])&&(Send_data[2])&&(Send_data[3])&&(Send_data[4])&&(Send_data[5])&&(Send_data[6]))//������ֵ��������
			Ready_6=1;	
	}
	else
	{	
		if((Send_data[1])&&(Send_data[2])&&(Send_data[3])&&(Send_data[4])&&(Send_data[5]))//�����ֵ��������
			Ready_6=1;		
	}
	{	
		if(!(ALU1&0x01))//�вɼ�����ֵ�Ͳ�����
			Send_data[1]=0;//�������İ�������
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
void Send_Usb_value(void)//����USBֵ
{
	U8 i;
	for(i=0;i<7;i++)//�����޳��ֵ
	{
		if(Send_data[i]!=Last_Send_data[i])//��һ�βɼ������ݺ͵�ǰ�ɼ������ݲ����  
		{
			bSend_IN2=1;
			Last_Send_data[i]=Send_data[i];//��ǰ�ɼ����ļ�ֵ��ֵ����һ�βɼ��ļ�ֵ����
		}
	}
	for(i=0;i<16;i++)	//ȫ���޳��ֵ
	{
		if(Usb2_Data[i]!=Last_Usb2_Data[i])
		{
			b_04=1;
			Last_Usb2_Data[i]=Usb2_Data[i];
		}
	}
	for(i=0;i<2;i++)	//��ý������
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