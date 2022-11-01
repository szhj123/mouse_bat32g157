#include "..\include\SH68F90.h"
#include "..\include\stdtype.h"
#include "..\include\mcu_def.h"
#include "..\include\pwm_control.h"
#include ".\include\Auser.h"
#include "..\include\CFG.h"
#include <intrins.h>
#include <string.h>

U8 Text_EMI_Times;
U8 Text_BT30_Times;
//bit	b_EMI_24Mode;
//bit	b_EMI_30Mode;
bit	b_Mode24_Up;
bit	b_ModeBT30_Up;
void Clear_Text_EMI_Data(void)
{
//	b_EMI_24Mode=0;
//	b_EMI_30Mode=0;
}
void Text_EMI_Mode(void)
{
	if((V_Data[5]&0x08)&&(bFn))
	{
		if(b_Mode24_Up)
		{
			Text_EMI_Times++;
			if(Text_EMI_Times>250)
			{	
				b_Mode24_Up=0;
				Text_EMI_Times=0;
				
				Mode_Times=0;	
				Change_Mode2();	
				
				Int_Module();
				Send_TextMode_Data(3);
				Mode_24G=1;
			}
		}
	}
	else
	{
		Text_EMI_Times=0;
		b_Mode24_Up=1;
	}	
	 /*
	if(((Mode_Bluetooth1)|(Mode_Bluetooth2)|(Mode_Bluetooth3))&&(V_Data[5]&0x08)&&(bFn))
	{
		if(b_ModeBT30_Up)
		{
			Text_BT30_Times++;
			if(Text_BT30_Times>250)
			{	
				b_ModeBT30_Up=0;
				Text_BT30_Times=0;
				
				Mode_Times=0;	
				Change_Mode2();	
				
//				b_EMI_30Mode=1;
				Int_Module();
				Send_TextMode_Data(1);
				Mode_Bluetooth1=1;
			}
		}
	}
	else
	{
		Text_BT30_Times=0;
		b_ModeBT30_Up=1;
	}	
	*/
	
}
