#include "..\include\SH68F90.h"
#include "..\include\stdtype.h"
#include ".\include\Auser.h"
#include <intrins.h>
#include <string.h>
extern void USB_QueryINT_Prog(void);
extern void key_press_check(void);
extern U8 xdata led_on_change;
extern U8 bdata all_flags_two;
extern bit  timer_scan_flag;
U8 data Cnt_1ms;
U8 data Cnt_2ms;
bit fg_1ms;
bit fg_2ms;
bit fg_4ms;
bit fg_8ms;
bit fg_16ms;
bit	fg_Remote;
/////////////////////////////////////////////////////
void timer2_init(void)
{
	T2CON = 0x00;
	T2MOD = 0x00;
	RCAP2L = (65535-2000);		// 1ms	2000=1MS  1000=500US  500=250us;
	RCAP2H = (65535-2000)>>8;
	TL2 = (65535-2000);
	TH2 = (65535-2000)>>8;
	TR2 = 1;
}
void  T2_ISR(void)	interrupt  0//1ms中断
{
	_push_(INSCON);
	_push_(FLASHCON);
	
		Cnt_2ms++;
		if(Cnt_2ms >= 16)
		{
			Cnt_2ms=0;
			fg_16ms=1;
		}	
			Cnt_1ms++;
		if(Cnt_1ms >= 8)
		{
			Cnt_1ms = 0x00;
			fg_8ms = 1;
			fg_4ms = 1;
			fg_2ms = 1;
		}
		else if(Cnt_1ms == 4)
		{
			fg_4ms = 1;
			fg_2ms = 1;
		}
		else if( (Cnt_1ms == 2) || (Cnt_1ms == 6) )
		{
			fg_2ms = 1;
		}
		fg_1ms = 1;
			No_Key_Times++;		//没按键按下1ms加一次，有按键就清零
		if(No_Key_Times>1000)	//1S  自加累计到1000ms就清零
		{
			No_Key_Times=0;
			No_Key_Times2++;
		}
	TF2 = 0 ;
	_pop_(FLASHCON);
	_pop_(INSCON);
}
void  pwm0_ISR(void)	interrupt  8//8：中断数字序号，数字越低中断等级越高
{
	_push_(INSCON);
	_push_(FLASHCON);
	Display_Mode();
	_pop_(FLASHCON);
	_pop_(INSCON);
}
void  INT4_ISR(void)	interrupt  1
{
	 EXF1 = 0 ;
	 fg_Remote = 1;
}

void  INT3_ISR(void)	interrupt  2
{
	 EXF0 &= 0XFD ;
	fg_Remote = 1;
}

void  INT2_ISR(void)	interrupt  3
{
	 EXF0 &= 0XFE;
	fg_Remote = 1;
}
void USB_IRQ_Prog() interrupt 7
{
	_push_(INSCON);
	_push_(FLASHCON);
	
	USB_QueryINT_Prog();
	
	_pop_(FLASHCON);
	_pop_(INSCON);	
	
}

void USBSOF_BT_1ms(void)
{
	
}
