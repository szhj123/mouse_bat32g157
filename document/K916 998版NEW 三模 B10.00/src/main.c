#include "..\include\SH68F90.h"
#include "..\include\stdtype.h"
#include "..\include\CFG.h"
#include "..\include\Auser.h"
#include "..\include\pwm_control.h"
#include "..\include\mcu_def.h"
#include <intrins.h>
#include <string.h>
extern void sys_init(void);
void PowerDown(void);
void Wireless_PowerDown(void);
bit b_ShutDown;
extern bit device_remote_wakeup_f;
extern U16 xdata Suspend_Counter;
extern bit usb_config_ok;
U8 xdata Module_LED_status;
U8 data Power_status;
bit	bPower_Up;
U16 xdata Delay_EFT_Times;
U16 xdata USB_Mode_Times;
U8 bdata Mode_now;//Mode_now=0;
sbit	Mode_24G= Mode_now ^ 0;
sbit	Mode_Bluetooth1= Mode_now ^ 1;
sbit	Mode_Bluetooth2= Mode_now ^ 2;
sbit	Mode_Bluetooth3= Mode_now ^ 3;
sbit	Mode_USB= Mode_now ^ 4; //

///////////////////////////////////////////////////////////
void main(void)
{
	CLR_WDT();
	sys_init();//系统函数初始化
	b_ShutDown=0;
	device_remote_wakeup_f=0;
	ET2 = 1;
	EA = 1;
	for(Speed_Data=0; Speed_Data<8; Speed_Data++)
	{
		CLR_WDT();
		delay_us(50000);
		CLR_WDT();
	}
	Read_KeyIndex_Data();//读键值数据
	CLR_WDT();
	Read_Mode_Time();//读灯亮模式的时间
	CLR_WDT();	
	{
		pwm_init();//pwm初始化
		PWM00_ENABLE;//pwm0使能 使能相应的pwm中断，一使能就会进入pwm0中断函数里面
		IEN1|=0X02;
	}	
	while(1)
	{
		CLR_WDT();
		if((fg_suspend)&&(Mode_USB))//驱动发命令控制键盘休眠
		{
			if(usb_config_ok)
			PowerDown();//省电模式，低功耗
			fg_suspend = 0;
		}
		if((Wireless_suspend)&&(!Mode_USB))//在定时器2里一秒加一次，超过设定时间就休眠
		{
			Wireless_suspend=0;
			PowerDown();//省电模式，低功耗
		}	
		//-----------------------------------------
		CLR_WDT();	
		Wheel_Check();//检查鼠标滚轮
		if(fhas_change)//等Display_Mode(void)函数里的Temp_Time1++大于21就fhas_change=1；
		{	
			fhas_change=0;
			Move_Key_value();//移动键值
			Deal_Wheel();//鼠标滚轮控制音量大小
			Send_Usb_value();//发送USB值
			Send_Macro_USB_Data();//发送USB宏数据
			if(Mode_USB)//usb有线K,
			{		
				IN1_IRQ_Prog_Data();//发送六键无冲？
				IN2_IRQ_Prog_Data();//发送全键无冲？	
			}
			else//USB无线模式
			{
				Send_Wireless_Data();//发送无线模式数据
				Send_Module_Data();
			}
			if(!bSpeed_End)//bSpeed_End=1不00000000000需要调节灯模式的速度,=0说明需要调节灯模式的速度
			{	
				Change_Mode();	//改变灯效模式和改变蓝牙、有线、2.4g模式切换
			}
		}
		if(fg_1ms)	//在定时器2中断里1ms成立一次
		{
			fg_1ms=0;
			Sacn_Key_Led_Up();	
			Send_Macro_USB_Data();//发送USB宏数据
		}	
		if(fg_8ms)//在定时器2中断里8ms成立一次
		{
			fg_8ms = 0;
			if(!b_Record_Mode)
			{	
				Deal_Image2_Data();	
				Display_Logo_Data();	
				Display_ChangLiang_Mode();//1
				Start_PWM_Led();			//2	
				Start_Mode6_Led();		//3
				Deal_Mode_5();
				Deal_Raindrops_Mode();	//7
				Dispaly_BoLang_Mode();
				Deal_Rest();
				Start_Effect_light_Time1();
				Start_Effect_light_Time2();
				Deal_PaoMa_1();			//4
				Deal_PaoMa_2();			//5
				Deal_PaoMa_3();	
				Deal_PaoMa_4();
			}
		}	
		if(fg_16ms)//在定时器2中断里16ms成立一次
		{	
			CLR_WDT();
			F_Text_Opine();
			Deal_Speed_LED_End();
			Write_ReadState_Data();
			Read_State_Data();	
		
			while(Ready_ok)
			{
				CLR_WDT();
				Send_Module_Data();
				Delay_EFT_Times++;
				if(Delay_EFT_Times>1500)
				{	
					Ready_ok=0;
					break;
				}
			}	
			fg_16ms=0;	
		}
	}
}
void delay_us(U16 cnt)
{
	U16 i;
	for(i=0;i<cnt;i++)
	{
		CLR_WDT();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
		_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
	}
}
void PowerDown(void)//低功耗模式
{
	EA = 0;	  
	ET2=0;
	Disenable_Pwm();	
	//-----------C--------------------
	P7PCR	&=~Bin(00010000);	//去掉上拉
	P7CR	|=Bin(00010000);		//输出
	P7		&=~Bin(00010000);	//0
	
	P6PCR	&=~Bin(00111111);	//去掉上拉
	P6CR	|=Bin(00111111);		//输出
	P6		&=~Bin(00111111);	//0
	
	P5PCR	&=~Bin(10000111);	//去掉上拉
	P5CR	|=Bin(10000111);		//输出
	P5		&=~Bin(10000111);	//0
	
	P4PCR	&=~Bin(01101101);	//去掉上拉
	P4CR	|=Bin(01101101);		//输出
	P4		&=~Bin(01101101);	//0
	
	P0PCR	&=~Bin(00100000);	//去掉上拉
	P0CR	|=Bin(00100000);		//输出
	P0		&=~Bin(00100000);	//0
	//-----------PWM---------------------
	P1PCR	&=~ Bin(00111111);	//去掉上拉
	P1CR	|=Bin(00111111);		//输出
	P1		&=~Bin(00111111);	
	
	P2PCR	&=~ Bin(00111111);	//去掉上拉
	P2CR	|=Bin(00111111);		//输出
	P2		&=~Bin(00111111);	
	
	P3PCR	&=~ Bin(00111111);	//去掉上拉
	P3CR	|=Bin(00111111);		//输出
	P3		&=~Bin(00111111);	
	//----------------选项脚-------------------------
	P7PCR	&=~ Bin(10000000);	//去掉上拉
	P7CR	&=~Bin(1000000);		//输出
	P7	&=~Bin(1000000);		//0
	
	P5PCR	&=~ Bin(01100000);	//去掉上拉
	P5CR	&=~Bin(01100000);		//输出
	P5&=~Bin(01100000);		//0
	
	P0PCR	&=~Bin(11000000);	//去掉上拉
	P0CR	&=~Bin(11000000);		//输出
	P0		&=~Bin(11000000);	//0
	
	P7CR	|=Bin(01000000);
	P7		&=~Bin(01000000);
	LDO_D=0;
	SPI_MISO_DirIn;
	SPI_SCK_DirIn;
	SPI_MOSI_DirIn;
	SPI_MOT_DirIn;
	SPI_SS_DirIn;
	b_ShutDown=1;
	if(!Mode_USB)
	{
		//USBCON&=~0X84;
		EXF0 = 0x00;	//0x54; // EX Down-Edge trigger.	
		EXF1 = 0xF3;	//外部中断标志寄存器
		IENC = 0xF3;	// INT 4.0~4.7	外部中断4 通道选择位
		IEN0|=0X02;	

		EA = 1;
		USBCON |= 0x01;  // 1:come in Suspend mode ??è?1ò?e×′ì?
		CLKCON &= ~0x04; // 2:Clear CLKCON^FS 
		PLLCON &= ~0x01; // 3:Clear PLLCON^PLLFS
		PLLCON &= ~0x02; // 4:Clear PLLCON^PLLON
		CLKCON &= ~0x08; // 5:Clear CLKCON^OSC2ON
		
		USBIE1|=0X85;	//6
		USBIF1 &= ~0x85;
		IEN1=0X00;	
		USBCON&=~0XC4;	
		REGCON&= ~0x01;_nop_();_nop_();_nop_();_nop_();
	}	
	else
	{	
		//if(device_remote_wakeup_f)
		{
			EXF1 = 0x00;	//外部中断标志寄存器
			IENC = 0xF3;	// INT 4.0~4.7	外部中断4 通道选择位
			EXF0 = 0xC0;	// EX4 Down-Edge trigger.
			IEN0|=0X02;	
		}
		
		EA = 1;
		 USBCON |= 0x01;  // 1:come in Suspend mode ??è?1ò?e×′ì?
		 CLKCON &= ~0x04; // 2:Clear CLKCON^FS 
		 PLLCON &= ~0x01; // 3:Clear PLLCON^PLLFS
		 PLLCON &= ~0x02; // 4:Clear PLLCON^PLLON
		// CLKCON &= ~0x08; // 5:Clear CLKCON^OSC2ON
		
		USBIE1|=0X85;	//6
		USBIF1 &= ~0x85;
		IEN1=0X01;	
	}
	
	
	_nop_();_nop_();
	_nop_();_nop_();_nop_();
	//////////////////////////////////
	SUSLO = 0x55;
	PCON |= 0x02;		//7 Power-down
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	CLR_WDT();
	EA = 0;
	EXF0 = 0x00;	// EX4 Down-Edge trigger.
	EXF1 = 0x00;
	IENC = 0x00;	//中断通道允许寄存器
	IEN0 &=~0X02;
	
	CLKCON = 0x08;		// OSC2CLK ON.
	delay_us(5);
	PLLCON |= 0x02;		// (OSC2CLK ON), PLLON=1.
	delay_us(33);
	CLR_WDT();
	PLLCON = 0x03;		// turn on the PLL CLOCK, the system clock is Internal RC;PLL的二分频作为OSCSCLK
	CLKCON = 0x0C;		// 24MHz
	
	delay_us(5);
	USBIF1 &= ~0x02;		// SUSPEND Flag
	USBCON &= ~0x01;	// exit Suspend, but Fail because IC.
	
	REGCON= REGCON_INIT;
	//usb_init();
	//if(fg_Remote)
	{	
		USBCON |= 0x02;
		fg_Remote=0;	
	}
	USBIE1=0X5F;	
	IEN1 |= 0x01;
	/////////////////////////////////////////
	IEN1|=0X02;
	PWM00_ENABLE;	
	PWM00DUTY2H = 0;//	(U8)((Temp_Brightness2)>>8);
	PWM00DUTY2L=	1280;//(U8)(Temp_Brightness2);
	//Init_PWM_Duty1();
	gpio_init();
	ldo_init();
	usb_init();
	//---------------------
	fg_suspend = 0;
	b_ShutDown=0;
	Change_Mode2();
	Suspend_Counter = 0;
	bPower_Up=1;
	//Int_Logo_Data();
	EA = 1;
	ET2=1;
	
}