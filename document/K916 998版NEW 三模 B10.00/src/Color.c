#include "..\include\SH68F90.h"
#include "..\include\stdtype.h"
#include "..\include\CFG.h"
#include "..\include\Auser.h"
U8 data	R_Color;
U8 data	G_Color;
U8 data	B_Color;

void Change_AColor_Time(U8 TempNUM)
{
	U8 i;
	U16 tmp;
	U16 tmp2;	
	if(Brack_b(TempNUM))
	{	
		if(Color_Times==0)	
		{
			Image[0][TempNUM]=R_Color*Brightness_Wheels/Limit_Power*4+PWM_AddData(0,TempNUM);
			Image[1][TempNUM]=G_Color*Brightness_Wheels/Limit_Power*4+PWM_AddData(1,TempNUM);
			Image[2][TempNUM]=B_Color*Brightness_Wheels/Limit_Power*4+PWM_AddData(2,TempNUM);	
		}
		else if(Color_Times==8)//»ìÉ«Ä£Ê½
		{
			if(b_SuiLiang_Mode)
			{
				if(break_Data[Port_Data(Key_Index)]&Pin_Data(Key_Index))
				{
							Run_Time++;
						if(Run_Time>5)
							Run_Time=0;
					Image[0][TempNUM]=PWM_AddData(0,TempNUM);	
					Image[1][TempNUM]=PWM_AddData(1,TempNUM);	
					Image[2][TempNUM]=PWM_AddData(2,TempNUM);	
					if(Run_Time==0)
							Image[0][TempNUM]=255*Brightness_Wheels/Limit_Power*4+PWM_AddData(0,TempNUM);
					else if(Run_Time==1)
							Image[1][TempNUM]=255*Brightness_Wheels/Limit_Power*4+PWM_AddData(1,TempNUM);
					else if(Run_Time==2)
							Image[2][TempNUM]=255*Brightness_Wheels/Limit_Power*4+PWM_AddData(2,TempNUM);	
					else if(Run_Time==3)
					{	
							Image[0][TempNUM]=255*Brightness_Wheels/Limit_Power*4+PWM_AddData(0,TempNUM);		
							Image[1][TempNUM]=255*Brightness_Wheels/Limit_Power*4+PWM_AddData(1,TempNUM);		
					}
					else if(Run_Time==4)
					{	
							Image[2][TempNUM]=255*Brightness_Wheels/Limit_Power*4+PWM_AddData(2,TempNUM);
							Image[1][TempNUM]=255*Brightness_Wheels/Limit_Power*4+PWM_AddData(1,TempNUM);	
					}
					else if(Run_Time==5)
					{	
							Image[2][TempNUM]=255*Brightness_Wheels/Limit_Power*4+PWM_AddData(2,TempNUM);
							Image[0][TempNUM]=255*Brightness_Wheels/Limit_Power*4+PWM_AddData(0,TempNUM);	
					}		
					
				}
			}	
			else if(b_ChangLiang_Mode)
			{
				Image[0][TempNUM]=PWM_AddData(0,TempNUM);	
				Image[1][TempNUM]=PWM_AddData(1,TempNUM);	
				Image[2][TempNUM]=PWM_AddData(2,TempNUM);	
				tmp=TempNUM%5;
				if(tmp==0)
						Image[0][TempNUM]=255*Brightness_Wheels/Limit_Power*4+PWM_AddData(0,TempNUM);
				else if(tmp==1)
						Image[1][TempNUM]=255*Brightness_Wheels/Limit_Power*4+PWM_AddData(1,TempNUM);
				else if(tmp==2)
						Image[2][TempNUM]=255*Brightness_Wheels/Limit_Power*4+PWM_AddData(2,TempNUM);	
				else if(tmp==3)
				{	
						Image[0][TempNUM]=255*Brightness_Wheels/Limit_Power*4+PWM_AddData(0,TempNUM);		
						Image[1][TempNUM]=255*Brightness_Wheels/Limit_Power*4+PWM_AddData(1,TempNUM);		
				}
				else if(tmp==4)
				{	
						Image[2][TempNUM]=255*Brightness_Wheels/Limit_Power*4+PWM_AddData(2,TempNUM);
						Image[1][TempNUM]=255*Brightness_Wheels/Limit_Power*4+PWM_AddData(1,TempNUM);	
				}
				else if(tmp==5)
				{	
						Image[2][TempNUM]=255*Brightness_Wheels/Limit_Power*4+PWM_AddData(2,TempNUM);
						Image[0][TempNUM]=255*Brightness_Wheels/Limit_Power*4+PWM_AddData(0,TempNUM);	
				}			
			}	
			else
			{
				tmp=TL2;
				tmp=(tmp<<8)|TH2;
				tmp=tmp+TempNUM;
				tmp=tmp%5;
				
				Image[0][TempNUM]=PWM_AddData(0,TempNUM);	
				Image[1][TempNUM]=PWM_AddData(1,TempNUM);	
				Image[2][TempNUM]=PWM_AddData(2,TempNUM);	
				
				if(tmp==0)
						Image[0][TempNUM]=255*Brightness_Wheels/Limit_Power*4+PWM_AddData(0,TempNUM);
				else if(tmp==1)
						Image[1][TempNUM]=255*Brightness_Wheels/Limit_Power*4+PWM_AddData(1,TempNUM);
				else if(tmp==2)
						Image[2][TempNUM]=255*Brightness_Wheels/Limit_Power*4+PWM_AddData(2,TempNUM);	
				else if(tmp==3)
				{	
						Image[0][TempNUM]=255*Brightness_Wheels/Limit_Power*4+PWM_AddData(0,TempNUM);		
						Image[1][TempNUM]=255*Brightness_Wheels/Limit_Power*4+PWM_AddData(1,TempNUM);		
				}
				else if(tmp==4)
				{	
						Image[2][TempNUM]=255*Brightness_Wheels/Limit_Power*4+PWM_AddData(2,TempNUM);
						Image[1][TempNUM]=255*Brightness_Wheels/Limit_Power*4+PWM_AddData(1,TempNUM);	
				}
				else if(tmp==5)
				{	
						Image[2][TempNUM]=255*Brightness_Wheels/Limit_Power*4+PWM_AddData(2,TempNUM);
						Image[0][TempNUM]=255*Brightness_Wheels/Limit_Power*4+PWM_AddData(0,TempNUM);	
				}		
			}	
		}
		else
		{
			Give_NUM_Image(TempNUM,Color_Times,255);
		}
	}
}















