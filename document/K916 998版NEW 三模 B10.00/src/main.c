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
	sys_init();//ϵͳ������ʼ��
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
	Read_KeyIndex_Data();//����ֵ����
	CLR_WDT();
	Read_Mode_Time();//������ģʽ��ʱ��
	CLR_WDT();	
	{
		pwm_init();//pwm��ʼ��
		PWM00_ENABLE;//pwm0ʹ�� ʹ����Ӧ��pwm�жϣ�һʹ�ܾͻ����pwm0�жϺ�������
		IEN1|=0X02;
	}	
	while(1)
	{
		CLR_WDT();
		if((fg_suspend)&&(Mode_USB))//������������Ƽ�������
		{
			if(usb_config_ok)
			PowerDown();//ʡ��ģʽ���͹���
			fg_suspend = 0;
		}
		if((Wireless_suspend)&&(!Mode_USB))//�ڶ�ʱ��2��һ���һ�Σ������趨ʱ�������
		{
			Wireless_suspend=0;
			PowerDown();//ʡ��ģʽ���͹���
		}	
		//-----------------------------------------
		CLR_WDT();	
		Wheel_Check();//���������
		if(fhas_change)//��Display_Mode(void)�������Temp_Time1++����21��fhas_change=1��
		{	
			fhas_change=0;
			Move_Key_value();//�ƶ���ֵ
			Deal_Wheel();//�����ֿ���������С
			Send_Usb_value();//����USBֵ
			Send_Macro_USB_Data();//����USB������
			if(Mode_USB)//usb����K,
			{		
				IN1_IRQ_Prog_Data();//���������޳壿
				IN2_IRQ_Prog_Data();//����ȫ���޳壿	
			}
			else//USB����ģʽ
			{
				Send_Wireless_Data();//��������ģʽ����
				Send_Module_Data();
			}
			if(!bSpeed_End)//bSpeed_End=1��00000000000��Ҫ���ڵ�ģʽ���ٶ�,=0˵����Ҫ���ڵ�ģʽ���ٶ�
			{	
				Change_Mode();	//�ı��Чģʽ�͸ı����������ߡ�2.4gģʽ�л�
			}
		}
		if(fg_1ms)	//�ڶ�ʱ��2�ж���1ms����һ��
		{
			fg_1ms=0;
			Sacn_Key_Led_Up();	
			Send_Macro_USB_Data();//����USB������
		}	
		if(fg_8ms)//�ڶ�ʱ��2�ж���8ms����һ��
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
		if(fg_16ms)//�ڶ�ʱ��2�ж���16ms����һ��
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
void PowerDown(void)//�͹���ģʽ
{
	EA = 0;	  
	ET2=0;
	Disenable_Pwm();	
	//-----------C--------------------
	P7PCR	&=~Bin(00010000);	//ȥ������
	P7CR	|=Bin(00010000);		//���
	P7		&=~Bin(00010000);	//0
	
	P6PCR	&=~Bin(00111111);	//ȥ������
	P6CR	|=Bin(00111111);		//���
	P6		&=~Bin(00111111);	//0
	
	P5PCR	&=~Bin(10000111);	//ȥ������
	P5CR	|=Bin(10000111);		//���
	P5		&=~Bin(10000111);	//0
	
	P4PCR	&=~Bin(01101101);	//ȥ������
	P4CR	|=Bin(01101101);		//���
	P4		&=~Bin(01101101);	//0
	
	P0PCR	&=~Bin(00100000);	//ȥ������
	P0CR	|=Bin(00100000);		//���
	P0		&=~Bin(00100000);	//0
	//-----------PWM---------------------
	P1PCR	&=~ Bin(00111111);	//ȥ������
	P1CR	|=Bin(00111111);		//���
	P1		&=~Bin(00111111);	
	
	P2PCR	&=~ Bin(00111111);	//ȥ������
	P2CR	|=Bin(00111111);		//���
	P2		&=~Bin(00111111);	
	
	P3PCR	&=~ Bin(00111111);	//ȥ������
	P3CR	|=Bin(00111111);		//���
	P3		&=~Bin(00111111);	
	//----------------ѡ���-------------------------
	P7PCR	&=~ Bin(10000000);	//ȥ������
	P7CR	&=~Bin(1000000);		//���
	P7	&=~Bin(1000000);		//0
	
	P5PCR	&=~ Bin(01100000);	//ȥ������
	P5CR	&=~Bin(01100000);		//���
	P5&=~Bin(01100000);		//0
	
	P0PCR	&=~Bin(11000000);	//ȥ������
	P0CR	&=~Bin(11000000);		//���
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
		EXF1 = 0xF3;	//�ⲿ�жϱ�־�Ĵ���
		IENC = 0xF3;	// INT 4.0~4.7	�ⲿ�ж�4 ͨ��ѡ��λ
		IEN0|=0X02;	

		EA = 1;
		USBCON |= 0x01;  // 1:come in Suspend mode ??��?1��?e���䨬?
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
			EXF1 = 0x00;	//�ⲿ�жϱ�־�Ĵ���
			IENC = 0xF3;	// INT 4.0~4.7	�ⲿ�ж�4 ͨ��ѡ��λ
			EXF0 = 0xC0;	// EX4 Down-Edge trigger.
			IEN0|=0X02;	
		}
		
		EA = 1;
		 USBCON |= 0x01;  // 1:come in Suspend mode ??��?1��?e���䨬?
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
	IENC = 0x00;	//�ж�ͨ������Ĵ���
	IEN0 &=~0X02;
	
	CLKCON = 0x08;		// OSC2CLK ON.
	delay_us(5);
	PLLCON |= 0x02;		// (OSC2CLK ON), PLLON=1.
	delay_us(33);
	CLR_WDT();
	PLLCON = 0x03;		// turn on the PLL CLOCK, the system clock is Internal RC;PLL�Ķ���Ƶ��ΪOSCSCLK
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