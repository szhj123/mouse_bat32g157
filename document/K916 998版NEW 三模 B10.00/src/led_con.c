#include "..\include\SH68F90.h"
#include "..\include\stdtype.h"
#include "..\include\mcu_def.h"
#include "..\include\pwm_control.h"
#include ".\include\Auser.h"
#include ".\include\ABSACC.H"
U8 data Image_Num;
code const U8 Change_Mode_Tab[22]=
{
	0,
	6,//随波逐流
	7,//按键涟漪
	8,//彩虹轮盘
	9,//正旋光波
	20,//两层流动
	11,//繁星点点
	
	10,//流光溢彩	
	
	13,//花开富贵
	14,//跑马
	15,//旋转风暴	
	16,//蛇形跑马
	17,//川流不息
	18,//斜拉变化	
	19,//自定义
	12,//RGB扩散		彩虹轮盘
	21,//随机霓虹
	1,
	2,//呼吸

	3,//霓虹
	4,//踏雪无痕	
	5,//一触即发		
};
U8 Change_Mode_Data(U8 Temp_Imge2)
{
	U8 i;
	i=Change_Mode_Tab[Temp_Imge2];
	return(i);	
}
code const U8 Key_Scan_Port[126] =
{
	0,0,0,	0,0,0,
	1,1,1,	1,1,1,
	2,2,2,	2,2,2,
	3,3,3,	3,3,3,
	4,4,4,	4,4,4,
	5,5,5,	5,5,5,
	6,6,6,	6,6,6,
	7,7,7,	7,7,7,
	8,8,8,	8,8,8,
	9,9,9,	9,9,9,	
	10,10,10,	10,10,10,
	11,11,11,	11,11,11,
	12,12,12,	12,12,12,
	13,13,13,	13,13,13,
	14,14,14,	14,14,14,
	15,15,15,	15,15,15,
	16,16,16,	16,16,16,
	17,17,17,	17,17,17,
	18,18,18,	18,18,18,
	19,19,19,	19,19,19,
	20,20,20,	20,20,20,
};
code const U8 Key_Scan_Pin[126] =
{
	0x01,0x02,0x04,0x08,0x10,0x20,
	0x01,0x02,0x04,0x08,0x10,0x20,
	0x01,0x02,0x04,0x08,0x10,0x20,
	0x01,0x02,0x04,0x08,0x10,0x20,
	0x01,0x02,0x04,0x08,0x10,0x20,
	
	0x01,0x02,0x04,0x08,0x10,0x20,
	0x01,0x02,0x04,0x08,0x10,0x20,
	0x01,0x02,0x04,0x08,0x10,0x20,
	0x01,0x02,0x04,0x08,0x10,0x20,
	0x01,0x02,0x04,0x08,0x10,0x20,
	
	0x01,0x02,0x04,0x08,0x10,0x20,
	0x01,0x02,0x04,0x08,0x10,0x20,
	0x01,0x02,0x04,0x08,0x10,0x20,
	0x01,0x02,0x04,0x08,0x10,0x20,
	0x01,0x02,0x04,0x08,0x10,0x20,
	
	0x01,0x02,0x04,0x08,0x10,0x20,
	0x01,0x02,0x04,0x08,0x10,0x20,
	0x01,0x02,0x04,0x08,0x10,0x20,
	0x01,0x02,0x04,0x08,0x10,0x20,
	0x01,0x02,0x04,0x08,0x10,0x20,
	0x01,0x02,0x04,0x08,0x10,0x20,
};
U8 Port_Data(U8 Temp_Imge2)
{
	U8 i;
	i=Key_Scan_Port[Temp_Imge2];
	return(i);
}
code const U8 Key_PWM_Port[3][126] =
{
	{			/* R */
		39,39,39,39,39,	39,39,39,39,39,	39,39,39,39,39,	39,39,39,39,39,	39,
		42,42,42,42,42,	42,42,42,42,42,	42,42,42,42,42,	42,42,42,42,42,	42,
		45,45,45,45,45,	45,45,45,45,45,	45,45,45,45,45,	45,45,45,45,45,	45,
		48,48,48,48,48,	48,48,48,48,48,	48,48,48,48,48,	48,48,48,48,48,	48,
		51,51,51,51,51,	51,51,51,51,51,	51,51,51,51,51,	51,51,51,51,51,	51,
		54,54,54,54,54,	54,54,54,54,54,	54,54,54,54,54,	54,54,54,54,54,	54,
	},
	{			/* G */
		38,38,38,38,38,	38,38,38,38,38,	38,38,38,38,38,	38,38,38,38,38,	38,
		41,41,41,41,41,	41,41,41,41,41,	41,41,41,41,41,	41,41,41,41,41,	41,
		44,44,44,44,44,	44,44,44,44,44,	44,44,44,44,44,	44,44,44,44,44,	44,
		47,47,47,47,47,	47,47,47,47,47,	47,47,47,47,47,	47,47,47,47,47,	47,
		50,50,50,50,50,	50,50,50,50,50,	50,50,50,50,50,	50,50,50,50,50,	50,
		53,53,53,53,53,	53,53,53,53,53,	53,53,53,53,53,	53,53,53,53,53,	53,
	},
	{			/* B */
		40,40,40,40,40,	40,40,40,40,40,	40,40,40,40,40,	40,40,40,40,40,	40,
		43,43,43,43,43,	43,43,43,43,43,	43,43,43,43,43,	43,43,43,43,43,	43,
		46,46,46,46,46,	46,46,46,46,46,	46,46,46,46,46,	46,46,46,46,46,	46,
		49,49,49,49,49,	49,49,49,49,49,	49,49,49,49,49,	49,49,49,49,49,	49,
		52,52,52,52,52,	52,52,52,52,52,	52,52,52,52,52,	52,52,52,52,52,	52,
		55,55,55,55,55,	55,55,55,55,55,	55,55,55,55,55,	55,55,55,55,55,	55,
	},
	
};
U8 PWM_AddData(U8 Temp_Imge2,Temp_Imge2Data)
{
	U8 i;
	i=Key_PWM_Port[Temp_Imge2][Temp_Imge2Data];
	return(i);
}
U8 Pin_Data(U8 Temp_Imge2)
{
	U8 i;
	i=Key_Scan_Pin[Temp_Imge2];
	return(i);
}
void Deal_WASD_LED(U8 Temp_Im2)	
{
	U16 Temp_WriteEE_Address;
	if(b_Record_Mode)
		return;
	if(Image_Times==1)
		Temp_WriteEE_Address = 0xCA00;
	else if(Image_Times==2)
		Temp_WriteEE_Address = 0xCC00;
	else if(Image_Times==3)
		Temp_WriteEE_Address = 0xCE00;
	//flash_driver.c 需要存FLASH
	{	
		if(CBYTE[Temp_WriteEE_Address+Temp_Im2*3])
			Image[0][Temp_Im2]=255*Brightness_Wheels/Limit_Power*4+PWM_AddData(0,Temp_Im2);
		else
			Image[0][Temp_Im2]=PWM_AddData(0,Temp_Im2);	
			
		if(CBYTE[Temp_WriteEE_Address+Temp_Im2*3+1])
			Image[1][Temp_Im2]=255*Brightness_Wheels/Limit_Power*4+PWM_AddData(1,Temp_Im2);
		else
			Image[1][Temp_Im2]=PWM_AddData(1,Temp_Im2);	
		
		if(CBYTE[Temp_WriteEE_Address+Temp_Im2*3+2])
			Image[2][Temp_Im2]=255*Brightness_Wheels/Limit_Power*4+PWM_AddData(2,Temp_Im2);
		else
			Image[2][Temp_Im2]=PWM_AddData(2,Temp_Im2);
		}

}
U8 Brack_b(U8 Temp_Imge2)
{
	U8 i;
	i=1;
	if(Mode_USB)
		Module_LED_status=LED_status;//LED_status:由驱动发命令控制
	if(Temp_Imge2==17)	//Num
	{
		if(bSpeed_End)
			i=0;
		else if(Module_LED_status&0x01)
		{	
			Image[0][Temp_Imge2]=1020+PWM_AddData(0,Temp_Imge2);
			Image[1][Temp_Imge2]=1020+PWM_AddData(1,Temp_Imge2);
			Image[2][Temp_Imge2]=1020+PWM_AddData(2,Temp_Imge2);
			i=0;
		}
		else
		{	
			Image[0][Temp_Imge2]=0+PWM_AddData(0,Temp_Imge2);
			Image[1][Temp_Imge2]=0+PWM_AddData(1,Temp_Imge2);
			Image[2][Temp_Imge2]=0+PWM_AddData(2,Temp_Imge2);
			i=0;
		}	
	}	
	else if(Temp_Imge2==18)	//CAP
	{
		if(bSpeed_End)
			i=0;
		else if(Module_LED_status&0x02)
		{	
			Image[0][Temp_Imge2]=1020+PWM_AddData(0,Temp_Imge2);
			Image[1][Temp_Imge2]=1020+PWM_AddData(1,Temp_Imge2);
			Image[2][Temp_Imge2]=1020+PWM_AddData(2,Temp_Imge2);
			i=0;
		}
		else
		{	
			Image[0][Temp_Imge2]=0+PWM_AddData(0,Temp_Imge2);
			Image[1][Temp_Imge2]=0+PWM_AddData(1,Temp_Imge2);
			Image[2][Temp_Imge2]=0+PWM_AddData(2,Temp_Imge2);
			i=0;
		}	
	}
	else if(Temp_Imge2==19)//SCL
	{
		if(bSpeed_End)
			i=0;
		else if(Module_LED_status&0x04)
		{	
			Image[0][Temp_Imge2]=1020+PWM_AddData(0,Temp_Imge2);
			Image[1][Temp_Imge2]=1020+PWM_AddData(1,Temp_Imge2);
			Image[2][Temp_Imge2]=1020+PWM_AddData(2,Temp_Imge2);
			i=0;
		}
		else
		{	
			Image[0][Temp_Imge2]=0+PWM_AddData(0,Temp_Imge2);
			Image[1][Temp_Imge2]=0+PWM_AddData(1,Temp_Imge2);
			Image[2][Temp_Imge2]=0+PWM_AddData(2,Temp_Imge2);
			i=0;
		}	
	}
	else if(Temp_Imge2==20)//win
	{
		if(bSpeed_End)
			i=0;
		else if(bWin_Locks)//fn+win按一下翻转一次值，0 1 0 1来回翻转
		{	
			Image[0][Temp_Imge2]=1020+PWM_AddData(0,Temp_Imge2);
			Image[1][Temp_Imge2]=1020+PWM_AddData(1,Temp_Imge2);
			Image[2][Temp_Imge2]=1020+PWM_AddData(2,Temp_Imge2);
			i=0;
		}
		else
		{	
			Image[0][Temp_Imge2]=0+PWM_AddData(0,Temp_Imge2);
			Image[1][Temp_Imge2]=0+PWM_AddData(1,Temp_Imge2);
			Image[2][Temp_Imge2]=0+PWM_AddData(2,Temp_Imge2);
			i=0;
		}	
	}
	//***********************
	else if(Temp_Imge2==43)
	{
		if(Mode_Bluetooth1&&(bSpeed_data!=0xAA))
		{	
			Image[1][Temp_Imge2]=bSpeed_data*4+PWM_AddData(1,Temp_Imge2);
			Image[2][Temp_Imge2]=bSpeed_data*4+PWM_AddData(2,Temp_Imge2);
			Image[0][Temp_Imge2]=bSpeed_data*4+PWM_AddData(0,Temp_Imge2);
			i=0;
		}
		else
		{
			if(b_ChangLiang_Mode)
			{
				Give_NUM_Image(Temp_Imge2,Color_Times,255);
				i=0;	
			}
			else if(b_WASD_Mode)
			{
				Deal_WASD_LED(Temp_Imge2);
				i=0;
			}
			else
			{
				i=1;
			}
		}
	}	
	else if(Temp_Imge2==44)
	{
		if(Mode_Bluetooth2&&(bSpeed_data!=0xAA))
		{	
			Image[1][Temp_Imge2]=bSpeed_data*4+PWM_AddData(1,Temp_Imge2);
			Image[2][Temp_Imge2]=bSpeed_data*4+PWM_AddData(2,Temp_Imge2);
			Image[0][Temp_Imge2]=bSpeed_data*4+PWM_AddData(0,Temp_Imge2);
			i=0;
		}
		else
		{
			if(b_ChangLiang_Mode)
			{
				Give_NUM_Image(Temp_Imge2,Color_Times,255);
				i=0;	
			}
			else if(b_WASD_Mode)
			{
				Deal_WASD_LED(Temp_Imge2);
				i=0;
			}
			else
			{
				i=1;
			}
		}
	}	
	else if(Temp_Imge2==45)
	{
		if(Mode_Bluetooth3&&(bSpeed_data!=0xAA))
		{	
			Image[1][Temp_Imge2]=bSpeed_data*4+PWM_AddData(1,Temp_Imge2);
			Image[2][Temp_Imge2]=bSpeed_data*4+PWM_AddData(2,Temp_Imge2);
			Image[0][Temp_Imge2]=bSpeed_data*4+PWM_AddData(0,Temp_Imge2);
			i=0;
		}
		else
		{
			if(b_ChangLiang_Mode)
			{
				Give_NUM_Image(Temp_Imge2,Color_Times,255);
				i=0;	
			}
			else if(b_WASD_Mode)
			{
				Deal_WASD_LED(Temp_Imge2);
				i=0;
			}
			else
			{
				i=1;
			}
		}	
	}	
	else if(Temp_Imge2==52)
	{
		if(Mode_24G&&(bSpeed_data!=0xAA))
		{	
			Image[2][Temp_Imge2]=bSpeed_data*4+PWM_AddData(2,Temp_Imge2);
			Image[1][Temp_Imge2]=bSpeed_data*4+PWM_AddData(1,Temp_Imge2);
			Image[0][Temp_Imge2]=bSpeed_data*4+PWM_AddData(0,Temp_Imge2);
			i=0;
		}
		else
		{
			if(b_ChangLiang_Mode)
			{
				Give_NUM_Image(Temp_Imge2,Color_Times,255);
				i=0;	
			}
			else if(b_WASD_Mode)
			{
				Deal_WASD_LED(Temp_Imge2);
				i=0;
			}
			else
			{
				i=1;
			}
		}
	}	
	//-----------------------------------
	else if(Temp_Imge2==110)
	{
		if(fg_Power_Led|fg_Power_Led2)
		{
			Image[1][Temp_Imge2]=bSpeed_data2*4+PWM_AddData(1,Temp_Imge2);
			Image[0][Temp_Imge2]=bSpeed_data2*4+PWM_AddData(0,Temp_Imge2);
			Image[2][Temp_Imge2]=bSpeed_data2*4+PWM_AddData(2,Temp_Imge2);
			i=0;
		}
		else
		{
			if(b_ChangLiang_Mode)
			{
				Give_NUM_Image(Temp_Imge2,Color_Times,255);
				i=0;	
			}
			else if(b_WASD_Mode)
			{
				Deal_WASD_LED(Temp_Imge2);
				i=0;
			}
			else
			{
				i=1;
			}
		}
	}
	else if(Temp_Imge2==114)
	{
		if(Power_status_Data!=0xaa)
		{
			Image[1][Temp_Imge2]=0*4+PWM_AddData(1,Temp_Imge2);
			Image[0][Temp_Imge2]=Power_status_Data*4+PWM_AddData(0,Temp_Imge2);
			Image[2][Temp_Imge2]=0*4+PWM_AddData(2,Temp_Imge2);
			i=0;
		}	
		else
		{
			if(b_ChangLiang_Mode)
			{
				Give_NUM_Image(Temp_Imge2,Color_Times,255);
				i=0;	
			}
			else if(b_WASD_Mode)
			{
				Deal_WASD_LED(Temp_Imge2);
				i=0;
			}
			else
			{
				i=1;
			}
		}
	}	
	//--------------Logo------------------------
	else if((Temp_Imge2==108)|(Temp_Imge2==109)|(Temp_Imge2==111)|(Temp_Imge2==112)|(Temp_Imge2==116)|(Temp_Imge2==117)|(Temp_Imge2==123)|(Temp_Imge2==125))
	{
		i=0;
	}
	/*
	else if(Temp_Imge2==108)
	{
		Image[0][Temp_Imge2]=Logo_Image[0]+PWM_AddData(0,Temp_Imge2);
		Image[1][Temp_Imge2]=Logo_Image[0]+PWM_AddData(1,Temp_Imge2);
		Image[2][Temp_Imge2]=Logo_Image[0]+PWM_AddData(2,Temp_Imge2);
		i=0;
	}	
	else if(Temp_Imge2==109)
	{
		Image[0][Temp_Imge2]=Logo_Image[1]+PWM_AddData(0,Temp_Imge2);
		Image[1][Temp_Imge2]=Logo_Image[1]+PWM_AddData(1,Temp_Imge2);
		Image[2][Temp_Imge2]=Logo_Image[1]+PWM_AddData(2,Temp_Imge2);
		i=0;
	}
	else if(Temp_Imge2==111)
	{
		Image[0][Temp_Imge2]=Logo_Image[2]+PWM_AddData(0,Temp_Imge2);
		Image[1][Temp_Imge2]=Logo_Image[2]+PWM_AddData(1,Temp_Imge2);
		Image[2][Temp_Imge2]=Logo_Image[2]+PWM_AddData(2,Temp_Imge2);
		i=0;
	}
	else if(Temp_Imge2==112)
	{
		Image[0][Temp_Imge2]=Logo_Image[3]+PWM_AddData(0,Temp_Imge2);
		Image[1][Temp_Imge2]=Logo_Image[3]+PWM_AddData(1,Temp_Imge2);
		Image[2][Temp_Imge2]=Logo_Image[3]+PWM_AddData(2,Temp_Imge2);
		i=0;
	}
	else if(Temp_Imge2==116)
	{
		Image[0][Temp_Imge2]=Logo_Image[4]+PWM_AddData(0,Temp_Imge2);
		Image[1][Temp_Imge2]=Logo_Image[4]+PWM_AddData(1,Temp_Imge2);
		Image[2][Temp_Imge2]=Logo_Image[4]+PWM_AddData(2,Temp_Imge2);
		i=0;
	}
	else if(Temp_Imge2==117)
	{
		Image[0][Temp_Imge2]=Logo_Image[5]+PWM_AddData(0,Temp_Imge2);
		Image[1][Temp_Imge2]=Logo_Image[5]+PWM_AddData(1,Temp_Imge2);
		Image[2][Temp_Imge2]=Logo_Image[5]+PWM_AddData(2,Temp_Imge2);
		i=0;
	}	
	else if(Temp_Imge2==123)
	{
		Image[0][Temp_Imge2]=Logo_Image[6]+PWM_AddData(0,Temp_Imge2);
		Image[1][Temp_Imge2]=Logo_Image[6]+PWM_AddData(1,Temp_Imge2);
		Image[2][Temp_Imge2]=Logo_Image[6]+PWM_AddData(2,Temp_Imge2);
		i=0;
	}
	else if(Temp_Imge2==125)
	{
		Image[0][Temp_Imge2]=Logo_Image[7]+PWM_AddData(0,Temp_Imge2);
		Image[1][Temp_Imge2]=Logo_Image[7]+PWM_AddData(1,Temp_Imge2);
		Image[2][Temp_Imge2]=Logo_Image[7]+PWM_AddData(2,Temp_Imge2);
		i=0;
	}
	*/
	return(i);
}
code const U8 Image_Num_Tab[126]=
{
	0,21,42,	63,84,105,
	1,22,43,	64,85,106,
	2,23,44,	65,86,107,
	3,24,45,	66,87,108,
	4,25,46,	67,88,109,
	5,26,47,	68,89,110,
	6,27,48,	69,90,111,
	7,28,49,	70,91,112,
	8,29,50,	71,92,113,
	9,30,51,	72,93,114,	//
	10,31,52,	73,94,115,//
	11,32,53,	74,95,116,
	12,33,54,	75,96,117,
	13,34,55,	76,97,118,//,
	14,35,56,	77,98,119,
	15,36,57,	78,99,120,
	16,37,58,	79,100,121,
	17,38,59,	80,101,122,
	18,39,60,	81,102,123,
	19,40,61,	82,103,124,
	20,41,62,	83,104,125,
};
void Deal_K45_Image(void)
{
	
}
U8 Deal_Down_K45_Image(U8 Temp_Imge2)
{
	U8 i;
	i=Temp_Imge2;
	//if(Temp_Imge2==95)
	//	i=85;
	return(i);	
}
void Deal_Tbl_Image(Key_Image)//Image_Num:被按下的按键编号
{
	Image_Num=Image_Num_Tab[Key_Image];
}
U8 Deal_Tbl_Image2(Key_Image2)//返回那个被按下的按键编号  0~125
{
	U8 i;
	i=Image_Num_Tab[Key_Image2];
	return(i);
}
int RandSub(U8 T_RandSub)
{
	U16 tmp;
	U16 tmp2;
	tmp=TL2;
	tmp=(tmp<<8)|TH2;
	tmp=tmp+T_RandSub;
	return rand();				
}
void Let_NUM_Image(void)		//给所有按键 付颜色
{
	U8 i;
	for(i=0; i<126; i++)
	{
		if((i!=17)&&(i!=18)&&(i!=19)&&(i!=20)&&(i!=108)&&(i!=109)&&(i!=111)&&(i!=112)&&(i!=116)&&(i!=117)&&(i!=123)&&(i!=125))
			Change_AColor_Time(i);
	}
}
void Clear_All_Image(void)
{
	U8 i;
	for(i=0; i<126; i++)
	{
		if((i!=17)&&(i!=18)&&(i!=19)&&(i!=20)&&(i!=108)&&(i!=109)&&(i!=111)&&(i!=112)&&(i!=116)&&(i!=117)&&(i!=123)&&(i!=125))
		{	
			Image[0][i]=PWM_AddData(0,i);
			Image[1][i]=PWM_AddData(1,i);
			Image[2][i]=PWM_AddData(2,i);
		}
	}
}
void Give_NUM_Image(U8 Temp_NUM,Temp_Color,Image_Brightness)//wei  Color_Times  值
{
	if(Temp_Color==1)	//R
	{
		Image[R][Temp_NUM]=Image_Brightness*Brightness_Wheels/Limit_Power*4+PWM_AddData(0,Temp_NUM);
		Image[G][Temp_NUM]=PWM_AddData(G,Temp_NUM);
		Image[B][Temp_NUM]=PWM_AddData(B,Temp_NUM);
	}
	else if(Temp_Color==2)	//黄色
	{
		Image[R][Temp_NUM]=Image_Brightness*Brightness_Wheels/Limit_Power*4+PWM_AddData(R,Temp_NUM);
		Image[G][Temp_NUM]=Image_Brightness*Brightness_Wheels/Limit_Power*4+PWM_AddData(G,Temp_NUM);
		Image[B][Temp_NUM]=PWM_AddData(B,Temp_NUM);
	}
	else if(Temp_Color==3)	//绿色
	{
		Image[G][Temp_NUM]=Image_Brightness*Brightness_Wheels/Limit_Power*4+PWM_AddData(G,Temp_NUM);
		Image[R][Temp_NUM]=PWM_AddData(R,Temp_NUM);
		Image[B][Temp_NUM]=PWM_AddData(B,Temp_NUM);
	}
	else if(Temp_Color==4)	//蓝色
	{
		Image[B][Temp_NUM]=Image_Brightness*Brightness_Wheels/Limit_Power*4+PWM_AddData(B,Temp_NUM);
		Image[R][Temp_NUM]=PWM_AddData(R,Temp_NUM);
		Image[G][Temp_NUM]=PWM_AddData(G,Temp_NUM);
	}	
	else if(Temp_Color==5)	//青色
	{
		Image[G][Temp_NUM]=Image_Brightness*Brightness_Wheels/Limit_Power*4+PWM_AddData(G,Temp_NUM);
		Image[B][Temp_NUM]=Image_Brightness*Brightness_Wheels/Limit_Power*4+PWM_AddData(B,Temp_NUM);
		Image[R][Temp_NUM]=PWM_AddData(R,Temp_NUM);
	}
	else if(Temp_Color==6)	//紫色
	{
		Image[B][Temp_NUM]=Image_Brightness*Brightness_Wheels/Limit_Power*4+PWM_AddData(B,Temp_NUM);
		Image[R][Temp_NUM]=Image_Brightness*Brightness_Wheels/Limit_Power*4+PWM_AddData(R,Temp_NUM);
		Image[G][Temp_NUM]=PWM_AddData(G,Temp_NUM);
	}
	else if(Temp_Color==7)	// 白色色
	{
		Image[B][Temp_NUM]=Image_Brightness*Brightness_Wheels/Limit_Power*4+PWM_AddData(B,Temp_NUM);
		Image[R][Temp_NUM]=Image_Brightness*Brightness_Wheels/Limit_Power*4+PWM_AddData(R,Temp_NUM);
		Image[G][Temp_NUM]=Image_Brightness*Brightness_Wheels/Limit_Power*4+PWM_AddData(G,Temp_NUM);
	}
	else if(Temp_Color==8)	//紫色
	{
		Image[B][Temp_NUM]=Image_Brightness*Brightness_Wheels/Limit_Power*4+PWM_AddData(B,Temp_NUM);
		Image[R][Temp_NUM]=Image_Brightness*Brightness_Wheels/Limit_Power*4+PWM_AddData(R,Temp_NUM);
		Image[G][Temp_NUM]=PWM_AddData(G,Temp_NUM);
	}	
}
void KeyDown_Image2(Temp_Image_Num,NUM_Brightness)	//Brightness Max 45	
{
	U8 i;
	i=Temp_Image_Num;
	{
		if(NUM_Brightness==0)
		{
			if((Temp_Image_Num>=0)&&(Temp_Image_Num<21))
			{	
				Change_AColor_Time(Temp_Image_Num);//Give_NUM_Image(Temp_Image_Num,j,255);
			}
		}
		else if(NUM_Brightness==1)
		{
			if((Temp_Image_Num<42)&&(Temp_Image_Num>20))
			{	
				Change_AColor_Time(Temp_Image_Num);//Give_NUM_Image(Temp_Image_Num,j,255);
			}
		}
		else if(NUM_Brightness==2)
		{
			if((Temp_Image_Num<63)&&(Temp_Image_Num>41))	//R2
			{	
				Change_AColor_Time(Temp_Image_Num);//Give_NUM_Image(Temp_Image_Num,j,255);
			}
		}
		else if(NUM_Brightness==3)
		{
			if((Temp_Image_Num<84)&&(Temp_Image_Num>62))	//R3
			{	
				Change_AColor_Time(Temp_Image_Num);//Give_NUM_Image(Temp_Image_Num,j,255);
			}
		}
		else if(NUM_Brightness==4)
		{
			if((Temp_Image_Num<105)&&(Temp_Image_Num>83))	//R4
			{	
				Change_AColor_Time(Temp_Image_Num);//Give_NUM_Image(Temp_Image_Num,j,255);
			}
		}
		else if(NUM_Brightness==5)
		{
			if((Temp_Image_Num<125)&&(Temp_Image_Num>104))//R5
			{	
				Change_AColor_Time(Temp_Image_Num);//Give_NUM_Image(Temp_Image_Num,j,255);
			}
		}	
	}
	Deal_K45_Image();
}
code const U8 Multimedia_Tab6[18]=
{
	0xB5,//0	Next Track       下一曲
	0xB6,//1	Previous Track   上一曲
	0xB7,//2	Stop             停止
	0xCD,//3	Play/ Pause      播放/暂停
	0xE2,//4	Mute 0           静音
	0xE9,//5	Volume Up        增大音量
	0xEA,//6	Volume Down      减小音量
	    
	0x83,//7	Media Select     多媒体选择
	0x8A,//8	Mail             邮箱，邮件
	0x92,//9	Calculator       计算器
	0x94,//10	My Computer	     我的电脑
	    
	0x21,//11	WWW Search       搜索
	0x23,//12	WWW Home         家
	0x24,//13	WWW Back         返回
	0x25,//14	WWW Forward      转发，正向，传送
	0x26,//15	WWW Stop         停止
	0x27,//16	WWW Refresh      刷新
	0x2A,//17	WWW Favorites    收藏夹
	
};
void Multimedia_Tab_Data(U8 No_Multimedia)//根据序号来选择多媒体功能
{
	 Multimedia_Data[1]=Multimedia_Tab6[No_Multimedia];//根据序号来选择多媒体功能
	if(Multimedia_Data[1]<=0x2a)//Multimedia_Data[1]得到的值小于0x2a   No_Multimedia：11~17进入这里
		Multimedia_Data[0]=2;
	else if((Multimedia_Data[1]<=0x94)&&(Multimedia_Data[1]>=0x83)) //No_Multimedia：7~10进入这里
		Multimedia_Data[0]=1;
	else //上面两个条件都不满足  No_Multimedia：0~6进入这里
		Multimedia_Data[0]=0;	
}