#include "..\include\SH68F90.h"
#include "..\include\stdtype.h"
#include "..\include\usb_db.h"
#include "..\include\mcu_def.h"
#include "..\include\usb_def.h"
#include ".\head\Auser.h"
#include <intrins.h>
#include <string.h>
//******************************************************************************

/*
void IN1_IRQ_Prog(U8 *ctr, U8 len)
{																		
	U8 i;
	buffer_addr = IN1_BUFFER_ADDRESS;
	for(i=0;i<len;i++)
	{
		buffer_addr[i] = *ctr;
		ctr++;
	}	
	buffer_addr[0] =0x00;
	buffer_addr[1] =0x00;
	buffer_addr[2] =0x00;
	buffer_addr[3] =0x00;
	buffer_addr[4] =0x00;
	buffer_addr[5] =0x00;
	buffer_addr[6] =0x00;
	buffer_addr[7] =0x00;
	
	IEP1CNT	= len;
	IN1_SET_READY;
}	
*/