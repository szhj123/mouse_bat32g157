#include "..\include\SH68F90.h"
#include "..\include\stdtype.h"
#include "..\include\mcu_def.h"
#include "..\include\pwm_control.h"
#include ".\include\Auser.h"

//bit b_PRINT_Up;	在流光模式文件下
//bit b_PRINT_Up2;
//U8 xdata 	Logo_Mode_Times;
/*
U8 xdata 	Logo_Temp_R;
U8 xdata 	Logo_Temp_G;
U8 xdata 	Logo_Temp_B;
U8 xdata 	Logo_Temp_Times;
U8 xdata 	Logo_Brightness;
code const U8 breathe_mode_tab[128+20]=
{
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,		1,		2,		3,		4,		5,		6,		7,
	8,		9,		10,		12,		14,		16,		18,		20,
	22,		24,		27,		30,		33,		36,		39,		42,
	45,		49,		53,		57,		61,		65,		69,		73,
	77,		81,		85,		89,		94,		99,		104,	109,
	114,	119,	124,	129,	134,	140,	146,	152,
	158,	164,	170,	176,	182,	188,	194,	200,
	206,	213,	220,	227,	234,	241,	248,	255,
	
 	255,	248,	241,	234,	227,	220,	213,	206,
	200,	194,	188,	182,	176,	170,	164,	158,
	152,	146,	140,	134,	129,	124,	119,	114,
	109,	104,	99,		94,		89,		85,		81,		77,
	73,		69,		65,		61,		57,		53,		49,		45,
	42,		39,		36,		33,		30,		27,		24,		22,
	20,		18,		16,		14,		12,		10,		9,		8,
	7,		6,		5,		4,		3,		2,		1,		0,	
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
};
void Give_Logo_Data(U8 Temp_Color,Temp_Logo2)
{
	U16 Temp_Logo;
		Temp_Logo=Temp_Logo2*5;
	switch(Temp_Color)
	{
		case 0:	
			PWM30_ENABLE;	
			PWM30DUTY1H = PWM30DUTY1L  = 0x00;
			PWM30DUTY2H = 	(U8)((Temp_Logo)>>8);
			PWM30DUTY2L=	 (U8)(Temp_Logo);
		break;
		case 2:	
			PWM32_ENABLE;	
			PWM32DUTY1H = PWM32DUTY1L  = 0x00;
			PWM32DUTY2H = 	(U8)((Temp_Logo)>>8);
			PWM32DUTY2L=	(U8)(Temp_Logo);
		break;
		case 1:	
			PWM31_ENABLE;	
			PWM31DUTY1H = PWM31DUTY1L  = 0x00;
			PWM31DUTY2H = 	(U8)((Temp_Logo)>>8);
			PWM31DUTY2L=	(U8)(Temp_Logo);
		break;
	}
}
U8 JianbianSub32(U8 LedStage2)
{
	switch(LedStage2)
		{
			case 0:	
				Logo_Temp_R=0;
				Logo_Temp_G++;
				Logo_Temp_B = 0;
				if(Logo_Temp_G >= 250)
					LedStage2++;
			break;
			//--------------------------------
			case 1:
				Logo_Temp_R++;
				Logo_Temp_G--;
				Logo_Temp_B=0;	
				if(Logo_Temp_G==0)
					LedStage2++;
			break;
			//--------------------------------
			case 2:
				Logo_Temp_R--;
				Logo_Temp_G=0;
				Logo_Temp_B++;
				if(Logo_Temp_R == 0)
					LedStage2++;
			break;		
			//--------------------------------
			case 3:
				Logo_Temp_R=0;
				Logo_Temp_G++;
				Logo_Temp_B--;
				if(Logo_Temp_B ==0)
					LedStage2++;
			break;	
			//--------------------------------
			case 4:
				Logo_Temp_R++;
				Logo_Temp_G--;
				Logo_Temp_B=0;
				if(Logo_Temp_G == 0)
					LedStage2++;
			break;		
				//--------------------------------
			case 5:
				Logo_Temp_R--;
				Logo_Temp_G=0;
				Logo_Temp_B++;
				if(Logo_Temp_R == 0)
					LedStage2++;
			break;	
				//--------------------------------
			case 6:
				Logo_Temp_R=0;
				Logo_Temp_G++;
				Logo_Temp_B--;
				if(Logo_Temp_B == 0)
					LedStage2=1;
			break;	
				//--------------------------------
		} 
	return 	LedStage2;
}
void Int_Logo_Data(void)
{
	Logo_Temp_Times=0;	
	Logo_Temp_R=0;	
	Logo_Temp_G=0;	
	Logo_Temp_B=0;	
	Give_Logo_Data(0,0);
	Give_Logo_Data(1,0);
	Give_Logo_Data(2,0);
}
void Deal_Logo_key(void)
{
	
	if(bFn)
	{
		if(V_Data[14]&0x01)
		{
			if(b_PRINT_Up)
			{
				b_PRINT_Up=0;
				Logo_Mode_Times++;
				if(Logo_Mode_Times>9)
					Logo_Mode_Times=0;
				Int_Logo_Data();
				Save_Mode_Time();
			}
		}
		else
			b_PRINT_Up=1;	
//		//---------------------------------------	
//		if((V_Data[15]&0x02)|(V_Data[15]&0x04))
//		{
//			if(b_PRINT_Up2)
//			{
//				b_PRINT_Up2=0;
//				if(Logo_Mode_Times>1)
//				{	
//					if(V_Data[15]&0x02)
//					{
//						if(Logo_Brightness<3)
//							Logo_Brightness++;
//					}	
//					else if(V_Data[15]&0x04)
//					{
//						if(Logo_Brightness>1)
//							Logo_Brightness--;
//					}	
//				}
//			}
//		}
//		else
//			b_PRINT_Up2=1;	
	}
	//----------------------------------------------
}
void Display_Logo_Data(void)
{
	U8 i;
		if(Logo_Brightness>=3)
			i=255;
		if(Logo_Brightness==2)
			i=50;
		if(Logo_Brightness==1)
			i=15;
			
		i=255;	
	//-------------------------------------------------
	if(Logo_Mode_Times==0)//呼吸 霓虹
	{
		Logo_Temp_Times=JianbianSub32(Logo_Temp_Times);
		Give_Logo_Data(0,Logo_Temp_R);
		Give_Logo_Data(1,Logo_Temp_G);
		Give_Logo_Data(2,Logo_Temp_B);
	}
	else if(Logo_Mode_Times==1)	//呼吸
	{
			Logo_Temp_Times++;
			if(Logo_Temp_Times<5)
				return;
				Logo_Temp_Times=0;
			Logo_Temp_B=breathe_mode_tab[Logo_Temp_R];
			Logo_Temp_R++;
			if(Logo_Temp_R>147)
			{	
				Logo_Temp_R=0;
				Logo_Temp_G++;
				if(Logo_Temp_G>5)
					Logo_Temp_G=0;
			}
		
		if(Logo_Temp_G==0)
		{	
			Give_Logo_Data(0,Logo_Temp_B);
		}
		else if(Logo_Temp_G==1)
		{	
			Give_Logo_Data(0,Logo_Temp_B);	
			Give_Logo_Data(1,Logo_Temp_B);	
		}
		else if(Logo_Temp_G==2)
		{	
			Give_Logo_Data(1,Logo_Temp_B);	
		}	
		else if(Logo_Temp_G==3)
		{	
			Give_Logo_Data(1,Logo_Temp_B);	
			Give_Logo_Data(2,Logo_Temp_B);	
		}
		else if(Logo_Temp_G==4)
		{	
			Give_Logo_Data(2,Logo_Temp_B);	
		}
		else if(Logo_Temp_G==5)
		{	
			Give_Logo_Data(0,Logo_Temp_B);	
			Give_Logo_Data(2,Logo_Temp_B);	
		}
	}
	else if(Logo_Mode_Times==2)	
	{
		Give_Logo_Data(0,i);
		Give_Logo_Data(1,0);
		Give_Logo_Data(2,0);
	}
	else if(Logo_Mode_Times==3)	
	{
		Give_Logo_Data(0,i);
		Give_Logo_Data(1,i);
		Give_Logo_Data(2,0);
	}
	else if(Logo_Mode_Times==4)	
	{
		Give_Logo_Data(0,0);
		Give_Logo_Data(1,i);
		Give_Logo_Data(2,0);
	}
	else if(Logo_Mode_Times==5)	
	{
		Give_Logo_Data(0,0);
		Give_Logo_Data(1,i);
		Give_Logo_Data(2,i);
	}
	else if(Logo_Mode_Times==6)	
	{
		Give_Logo_Data(0,0);
		Give_Logo_Data(1,0);
		Give_Logo_Data(2,i);
	}
	else if(Logo_Mode_Times==7)	
	{
		Give_Logo_Data(0,i);
		Give_Logo_Data(1,0);
		Give_Logo_Data(2,i);
	}
	else if(Logo_Mode_Times==8)	
	{
		Give_Logo_Data(0,i);
		Give_Logo_Data(1,i);
		Give_Logo_Data(2,i);
	}
	else if(Logo_Mode_Times==9)	
	{
		Give_Logo_Data(0,0);
		Give_Logo_Data(1,0);
		Give_Logo_Data(2,0);
	}
}
 */