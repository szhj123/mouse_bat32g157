#include "..\include\SH68F90.h"
#include "..\include\stdtype.h"
#include "..\include\mcu_def.h"
#include "..\include\pwm_control.h"
#include ".\include\Auser.h"
#include "..\include\CFG.h"
U16 data	Temp_Brightness2;
U8 data	Temp_Time1;
U16 xdata 	Image[3][126];
void Disenable_Pwm(void)
{	 
	PWM01_DISABLE;  
	PWM02_DISABLE;  
	PWM03_DISABLE;  
	PWM04_DISABLE;  
	PWM05_DISABLE;  
	PWM10_DISABLE;  
	PWM11_DISABLE;  
	PWM12_DISABLE;  
	PWM13_DISABLE;  
	PWM14_DISABLE;  
	PWM15_DISABLE;	
	PWM20_DISABLE;  
	PWM21_DISABLE;  
	PWM22_DISABLE;	
	PWM23_DISABLE;  
	PWM24_DISABLE;  
	PWM25_DISABLE;  
	PWM00_DISABLE; 
//	PWM40_DISABLE; 
}
void Enable_all_pwm(void)
{
	PWM00CON=PWM00CON_INIT|0x40;
	PWM01CON=PWM01CON_INIT;
	PWM02CON=PWM02CON_INIT;

	PWM03CON=PWM03CON_INIT;
	PWM04CON=PWM04CON_INIT;
	PWM05CON=PWM05CON_INIT;

	PWM10CON=PWM10CON_INIT;
	PWM11CON=PWM11CON_INIT;
	PWM12CON=PWM12CON_INIT;

	PWM13CON=PWM13CON_INIT;
	PWM14CON=PWM14CON_INIT;
	PWM15CON=PWM15CON_INIT;
					
	PWM20CON=PWM20CON_INIT;
	PWM21CON=PWM21CON_INIT;
	PWM22CON=PWM22CON_INIT;

	PWM23CON=PWM23CON_INIT;
	PWM24CON=PWM24CON_INIT;
	PWM25CON=PWM25CON_INIT;
}
void Deal_Data_Go3(void)
{	
	PWM20DUTY2H =	(U8)((Image[1][0+Temp_Time1])>>8);
	PWM20DUTY2L=	(U8) Image[1][0+Temp_Time1];
	
	PWM21DUTY2H =(U8)((Image[0][0+Temp_Time1])>>8);
	PWM21DUTY2L=	(U8) Image[0][0+Temp_Time1];
	
	PWM22DUTY2H =	(U8)((Image[2][0+Temp_Time1])>>8);
	PWM22DUTY2L=	 (U8)Image[2][0+Temp_Time1];
//-----------------------------1-------------------------------------------
	PWM23DUTY2H = 	(U8) ((Image[1][21+Temp_Time1])>>8);	//41	
	PWM23DUTY2L=	(U8)Image[1][21+Temp_Time1];
	
	PWM24DUTY2H =(U8) ((Image[0][21+Temp_Time1])>>8);		//42
	PWM24DUTY2L=	(U8)Image[0][21+Temp_Time1];
	
	PWM25DUTY2H =(U8)((Image[2][21+Temp_Time1])>>8);		//43
	PWM25DUTY2L=	(U8)Image[2][21+Temp_Time1];
	
	
//-----------------------------2-------------------------------------------
	PWM10DUTY2H =(U8)((Image[1][42+Temp_Time1])>>8);
	PWM10DUTY2L=	(U8)Image[1][42+Temp_Time1];
	
	PWM11DUTY2H =(U8) ((Image[0][42+Temp_Time1])>>8);
	PWM11DUTY2L=	(U8)Image[0][42+Temp_Time1];
	
	PWM12DUTY2H =(U8) ((Image[2][42+Temp_Time1])>>8);
	PWM12DUTY2L=	(U8)Image[2][42+Temp_Time1];
//-------------------------------3-------------------------------------------
	PWM13DUTY2H =(U8)((Image[1][63+Temp_Time1])>>8);
	PWM13DUTY2L=	(U8)Image[1][63+Temp_Time1];
	
	PWM14DUTY2H = (U8)((Image[0][63+Temp_Time1])>>8);
	PWM14DUTY2L=	(U8)Image[0][63+Temp_Time1];
	
	PWM15DUTY2H = (U8) ((Image[2][63+Temp_Time1])>>8);
	PWM15DUTY2L=	(U8)Image[2][63+Temp_Time1];
//-------------------------------4-------------------------------------------
	PWM03DUTY2H =(U8) ((Image[1][84+Temp_Time1])>>8);
	PWM03DUTY2L=	(U8)Image[1][84+Temp_Time1];
	
	PWM04DUTY2H =(U8) ((Image[0][84+Temp_Time1])>>8);
	PWM04DUTY2L=	(U8)Image[0][84+Temp_Time1];
	
	PWM05DUTY2H =(U8) ((Image[2][84+Temp_Time1])>>8);
	PWM05DUTY2L=	(U8)Image[2][84+Temp_Time1];
//--------------------------------5------------------------------------------
	PWM00DUTY2H =(U8)  ((Image[1][105+Temp_Time1])>>8);
	PWM00DUTY2L=	(U8)Image[1][105+Temp_Time1];
	
	PWM01DUTY2H =(U8)   ((Image[0][105+Temp_Time1])>>8);
	PWM01DUTY2L=	(U8)Image[0][105+Temp_Time1];
	
	PWM02DUTY2H =(U8) ((Image[2][105+Temp_Time1])>>8);
	PWM02DUTY2L=	(U8)Image[2][105+Temp_Time1];
	
	
}
void Deal_Data_Go2(void)
{	
	
	PWM20DUTY2H =	(U8)((Image2[1][0+Temp_Time1])>>8);			//38
	PWM20DUTY2L=	(U8) Image2[1][0+Temp_Time1];
	
	PWM21DUTY2H =(U8)((Image2[0][0+Temp_Time1])>>8);			//39
	PWM21DUTY2L=	(U8) Image2[0][0+Temp_Time1];
	
	PWM22DUTY2H =	(U8)((Image2[2][0+Temp_Time1])>>8);			//40
	PWM22DUTY2L=	 (U8)Image2[2][0+Temp_Time1];
//-----------------------------1-------------------------------------------
	PWM23DUTY2H =	(U8)((Image2[0][21+Temp_Time1])>>8);	 	//41	
	PWM23DUTY2L=	(U8)Image2[0][21+Temp_Time1];		
	
	PWM24DUTY2H =(U8) ((Image2[2][21+Temp_Time1])>>8);		//42
	PWM24DUTY2L=	(U8)Image2[2][21+Temp_Time1];
	
	PWM25DUTY2H =	(U8) ((Image2[1][21+Temp_Time1])>>8);		//43
	PWM25DUTY2L=	(U8)Image2[1][21+Temp_Time1];
	
	
//-----------------------------2-------------------------------------------
	PWM10DUTY2H =(U8)((Image2[1][42+Temp_Time1])>>8);
	PWM10DUTY2L=	(U8)Image2[1][42+Temp_Time1];
	
	PWM11DUTY2H =(U8) ((Image2[0][42+Temp_Time1])>>8);
	PWM11DUTY2L=	(U8)Image2[0][42+Temp_Time1];
	
	PWM12DUTY2H =(U8) ((Image2[2][42+Temp_Time1])>>8);
	PWM12DUTY2L=	(U8)Image2[2][42+Temp_Time1];
//-------------------------------3-------------------------------------------
	PWM13DUTY2H =(U8)((Image2[1][63+Temp_Time1])>>8);
	PWM13DUTY2L=	(U8)Image2[1][63+Temp_Time1];
	
	PWM14DUTY2H = (U8)((Image2[0][63+Temp_Time1])>>8);
	PWM14DUTY2L=	(U8)Image2[0][63+Temp_Time1];
	
	PWM15DUTY2H = (U8) ((Image2[2][63+Temp_Time1])>>8);
	PWM15DUTY2L=	(U8)Image2[2][63+Temp_Time1];
//-------------------------------4-------------------------------------------
	PWM03DUTY2H =(U8) ((Image2[1][84+Temp_Time1])>>8);
	PWM03DUTY2L=	(U8)Image2[1][84+Temp_Time1];
	
	PWM04DUTY2H =(U8) ((Image2[0][84+Temp_Time1])>>8);
	PWM04DUTY2L=	(U8)Image2[0][84+Temp_Time1];
	
	PWM05DUTY2H =(U8) ((Image2[2][84+Temp_Time1])>>8);
	PWM05DUTY2L=	(U8)Image2[2][84+Temp_Time1];
//--------------------------------5------------------------------------------
	PWM00DUTY2H =(U8)  ((Image2[1][105+Temp_Time1])>>8);
	PWM00DUTY2L=	(U8)Image2[1][105+Temp_Time1];
	
	PWM01DUTY2H =(U8)   ((Image2[0][105+Temp_Time1])>>8);
	PWM01DUTY2L=	(U8)Image2[0][105+Temp_Time1];
	
	PWM02DUTY2H =(U8) ((Image2[2][105+Temp_Time1])>>8);
	PWM02DUTY2L=	(U8)Image2[2][105+Temp_Time1];
	
}
void Deal_Data_Go1(void)
{	
	PWM20DUTY2H =	0;
	PWM20DUTY2L=	38;
	
	PWM21DUTY2H =0;
	PWM21DUTY2L=	39;
	
	PWM22DUTY2H =	0;
	PWM22DUTY2L=	  40;
//-----------------------------1-------------------------------------------
	PWM23DUTY2H = 0;
	PWM23DUTY2L=	41;
	
	PWM24DUTY2H =0;
	PWM24DUTY2L=	42;
	
	PWM25DUTY2H =0;
	PWM25DUTY2L=	43;
	
	
//-----------------------------2-------------------------------------------
	PWM10DUTY2H =0;
	PWM10DUTY2L=	44;
	
	PWM11DUTY2H =0;
	PWM11DUTY2L=	45;
	
	PWM12DUTY2H =0;
	PWM12DUTY2L=	46;
//-------------------------------3-------------------------------------------
	PWM13DUTY2H =0;
	PWM13DUTY2L=	47;
	
	PWM14DUTY2H =0;
	PWM14DUTY2L=	48;
	
	PWM15DUTY2H =0;
	PWM15DUTY2L=	49;
//-------------------------------4-------------------------------------------
	PWM03DUTY2H =0;
	PWM03DUTY2L=	50;
	
	PWM04DUTY2H =0;
	PWM04DUTY2L=	51;
	
	PWM05DUTY2H =0;
	PWM05DUTY2L=	52;
//--------------------------------5------------------------------------------
	PWM00DUTY2H =0;
	PWM00DUTY2L=	53;
	
	PWM01DUTY2H =0;
	PWM01DUTY2L=	54;
	
	PWM02DUTY2H =0;
	PWM02DUTY2L=	55;
	
}
void Display_Mode(void)
{
	U8 i;
	U8 RtnPort,RtnPort1;
//	LDO_D=0;
	Disenable_Pwm();//pwm失能	
	P6 |= 0xff;//P6=0XC0   0XFF 
	P5 |= 0x87;//P5=0X88   0X8F
	P4 |= 0x6d;//P4=0XB0   0XFD
	P7 |= 0x10;//P7=0XF8   0XF8
	P0 |= 0xE0;//P0=0X80   0XE0  为什么要或上这些值？
	switch(Temp_Time1)
	{
			case 0:		
					C0=0;	//C20=1;//	P3_0 = 0;
			break;
			case 1:
					C1 = 0;	//C0=1;		
			break;	
			case 2:
					C2 = 0;	//C1 = 1;				
			break;		
			case 3:
					C3 = 0;	//C2 = 1;				
			break;		
			case 4:
					C4 = 0;	//C3 = 1;			
			break;		
			case 5:
					C5 = 0;	//C4 = 1;				
			break;	
			case 6:
					C6 = 0;	//C5 = 1;	
			break;
			case 7:
					C7 = 0;	//C6 = 1;			
			break;	
			case 8:
					C8 = 0;	//C7 = 1;				
			break;		
			case 9:
					C9 = 0;	//C8 = 1;				
			break;		
			case 10:
					C10 = 0;	//C9 = 1;				
			break;		
			case 11:
					C11 = 0;	//C10 = 1;			
			break;		
			case 12:
					C12 = 0;	//C11 = 1;			
			break;	
			case 13:
					C13 = 0;	//C12 = 1;			
			break;		
			case 14:
					C14 = 0;	//C13 = 1;			
			break;		
			case 15:
					C15 = 0;	//C14 = 1;				
			break;		
			case 16:
					C16 = 0;	//C15 = 1;			
			break;	
			case 17:
					C17 = 0;	//C16 = 1;
			break;
			case 18:
					C18 = 0;	//C17 = 1;			
			break;	
			case 19:
					C19 = 0;	//C18 = 1;			
			break;		
			case 20:
					C20 = 0;	//C19 = 1;			
			break;		
	}
	RtnPort = ((P7&0x0f) |((P5<<1)&0x30))|0xc0;//R0用于仿真先屏蔽R0		
	PWM00CON &= 0xdf;          //clr flag	
	if(b_PowerLow)
		Deal_Data_Go1();		
	else if(b_Image2_Ok)
		Deal_Data_Go2();		
	else	
		Deal_Data_Go3();		
	RtnPort1 = ((P7&0x0f) |((P5<<1)&0x30))|0xc0;//R0用于仿真先屏蔽R0	
	if(RtnPort==RtnPort1)
	{
		V_Data[Temp_Time1]=~RtnPort;//Temp_Time1：这个值的范围：0~20，刚好21个按键
	//	V_Data[Temp_Time1]&=~1;
	}
	Temp_Time1++;
	if(Temp_Time1>21)
	{	
		Temp_Time1=0;	
		fhas_change=1;	
	}
	
	Enable_all_pwm();//使能所有pwm
}





