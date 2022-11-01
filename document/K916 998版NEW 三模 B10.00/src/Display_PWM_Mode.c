#include "..\include\SH68F90.h"
#include "..\include\stdtype.h"
#include "..\include\mcu_def.h"
#include "..\include\pwm_control.h"
#include ".\include\Auser.h"
#include "..\include\CFG.h"
#include <intrins.h>
#include <string.h>
//U8 xdata	TimeTemp1;
U8 xdata	Last_CL_Brightness_Wheels;
//************³£ÁÁÄ£Ê½**********************
void Display_ChangLiang_Mode(void)
{
	U8 j,i;
	
	if(b_ChangLiang_Mode|b_WASD_Mode)//|b_SuiMie_Mode|b_HengMie_Mode)
	{	
		if((Last_CL_Brightness_Wheels==0xaa)&&(b_ChangLiang_Mode))
		{	
			Last_CL_Brightness_Wheels=0;
			Let_NUM_Image();
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
}
