#include "..\include\SH68F90.h"
#include "..\include\stdtype.h"
#include "..\include\mcu_def.h"
#include "..\include\pwm_control.h"
#include ".\include\Auser.h"
#include "..\include\CFG.h"
#include <intrins.h>
#include <string.h>
U8 xdata	b_Effect_light_1_Cpl;
code const U8 Effect1_Tab[21]=
{
	0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,
};
code const U8 Effect1_Tab2[21]=
{
	20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0,
};
void Start_Effect_light_Time1(void)	
{
	U8 j,n;
	U8 i,i2;
	if(!b_Effect_light_1)
		return;
	Temp_Speed++;
	if(Temp_Speed>Speed_Data+5)
	{
		Temp_Speed=0;	
		i=Effect1_Tab[Run_Time];
		i2=Effect1_Tab2[Run_Time];
			
			Change_AColor_Time(i);	//Give_NUM_Image(i,n,50*Brightness_Wheels);	
			Change_AColor_Time(i2+21);	//Give_NUM_Image(i2+21,n,50*Brightness_Wheels);		
			Change_AColor_Time(i+42);	//Give_NUM_Image(i+42,n,50*Brightness_Wheels);	
			Change_AColor_Time(i2+63);	//Give_NUM_Image(i2+63,n,50*Brightness_Wheels);
			Change_AColor_Time(i+84);	//Give_NUM_Image(i+84,n,50*Brightness_Wheels);	
			Change_AColor_Time(i2+105);	//Give_NUM_Image(i2+105,n,50*Brightness_Wheels);
			
			Deal_K45_Image();
		if(b_Effect_light_1_Cpl)
			Run_Time--;	
		else
			Run_Time++;	
		if(Run_Time>=21)
		{
			b_Effect_light_1_Cpl=0xff; 
			 Run_Time=20;
		}
		if(Run_Time==0)
		{
			b_Effect_light_1_Cpl=0;
		}		
	}
}












