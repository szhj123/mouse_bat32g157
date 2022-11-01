#include "..\include\SH68F90.h"
#include "..\include\stdtype.h"
#include "..\include\mcu_def.h"
#include "..\include\pwm_control.h"
#include ".\include\Auser.h"
#include "..\include\CFG.h"
//****************************************
void Deal_Raindrops_Mode(void)
{
	U8 i;
	U16 randtmp;
	if(!b_Raindrops_Mode)
		return;	
		Temp_Speed++;
	if(Temp_Speed>Speed_Data+1)
	{
		Temp_Speed=0;
		Run_Time++;
		if(Run_Time>5)
			Run_Time=0;
			
		for(i=0;i<6;i++)
		{
			randtmp=RandSub(i);
			randtmp=randtmp%125;
			if(((Image[R][randtmp]<=PWM_AddData(R,randtmp))&&	\
				(Image[G][randtmp]<=PWM_AddData(G,randtmp))&&		\
				(Image[B][randtmp])<=PWM_AddData(B,randtmp)))
			{	
				Change_AColor_Time(randtmp);
			}
		}	
	}
}
//****************************************