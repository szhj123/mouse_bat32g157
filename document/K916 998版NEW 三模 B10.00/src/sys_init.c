#include "..\include\SH68F90.h"
#include "..\include\stdtype.h"
#include "..\include\mcu_def.h"
#include "..\include\pwm_control.h"
#include ".\include\Auser.h"
#include "..\include\CFG.h"
#include <intrins.h>
#include <string.h>
void clock_init(void);
void timer2_init(void);
void gpio_init(void);
void interrupt_init(void);
void pwm_init(void);
void spi_init(void);
void uart_init(void);
void lpd_init(void);
void ldo_init(void);
void usb_init(void);
////////////////////////
extern void delay_us(U16 cnt);
extern U16 xdata Suspend_Counter;
//////////////////////////////////////////////////////////////////////
void sys_init(void)
{
	ldo_init();
	clock_init();
	CLR_WDT();
	delay_us(250);
	CLR_WDT();
	gpio_init();
	timer2_init();
	spi_init();
	uart_init();
	lpd_init();	
	usb_init();
	interrupt_init();
}
///////////////////////////clock/////////////////////////////////////////
void clock_init(void)
{
	CLR_WDT();
	CLKCON = (CLKCON_INIT & 0x08);  //open high clock  �򿪸���ʱ��
	delay_us(350);
	PLLCON = (PLLCON_INIT & 0x02);//pll���໷ʱ������
	delay_us(533);
	CLR_WDT();
	PLLCON = PLLCON_INIT;
	CLKCON = CLKCON_INIT; //sys clock = high clock  ϵͳʱ��=����ʱ��
}
///////////////////////////timer2/////////////////////////////////////////
///////////////////////////gpio////////////////////////////////////////
void gpio_init(void)
{		//CR=0Ϊ����ģʽ��CR=1Ϊ���ģʽ��PCR=1�������ڲ�������PCR=0�ǲ������ڲ�����
	P0CR = P0CR_INIT;//1111 0100   p0_0 p0_1 p0_3����Ϊ����
	P1CR = P1CR_INIT;//11 1111     P1_0~P1~5ȫ������Ϊ���
	P2CR = P2CR_INIT;//11 1111
	P3CR = P3CR_INIT;//11 1111
	P4CR = P4CR_INIT;//1110 1101   p4_1 p4_4 ����Ϊ����
	P5CR = P5CR_INIT;//1000 0111   p5_3 p5_4 p5_5 p5_6����Ϊ����
	P6CR = P6CR_INIT;//1111 1111
	P7CR = P7CR_INIT;//0111 0000   p7_0 p7_1 p7_2 p7_3  p7_7����Ϊ����

	P0PCR = P0PCR_INIT;//1110 0000  P0_5 P0_6 P0_7����Ϊ�����ڲ�����
	P1PCR = P1PCR_INIT;//11 1111
	P2PCR = P2PCR_INIT;//11 1111
	P3PCR = P3PCR_INIT;//11 1111
	P4PCR = P4PCR_INIT;//0110 1101
	P5PCR = P5PCR_INIT;//1111 1111
	P6PCR = P6PCR_INIT;//1111 1111
	P7PCR = P7PCR_INIT;//0101 1111

	P0 = P0_OUTPUT_LEVEL;//1110 0100  ����p0_0��1��3��4Ϊ�͵�ƽ��p0_2��5��6��7Ϊ�ߵ�ƽ
	P1 = P1_OUTPUT_LEVEL;//00 0000
	P2 = P2_OUTPUT_LEVEL;//00 0000
	P3 = P3_OUTPUT_LEVEL;//00 0000
	P4 = P4_OUTPUT_LEVEL;//1110 1101  ����p4_1��4Ϊ�͵�ƽ��p4_0��2��3��5��6��7Ϊ�ߵ�ƽ
	P5 = P5_OUTPUT_LEVEL;//1000 0111  ����p5_3��4��5��6Ϊ�͵�ƽ��p5_0��1��2��7Ϊ�ߵ�ƽ
	P6 = P6_OUTPUT_LEVEL;//1111 1111  ����p6_0��1��2��3��4��5��6��7Ϊ�ߵ�ƽ
	P7 = P7_OUTPUT_LEVEL;//0001 0000  ����p7_0��1��2��3��4��5��7Ϊ�͵�ƽ��p7_4Ϊ�ߵ�ƽ

	DRVCON = 0X05;//ֻ�е�DRVCON[3��0] = 0x5����������Ĵ����޸���Ӧport��������С  0000 0101������������bit�� 00������port1�ڸı���������
	P1DRV = P1DRV_INIT;//ֻ�����úüĴ���DRVCON�󣬽�����д����ѡ��Ĵ����������ı����Ч  PxDRV:����ѡ��Ĵ���

	DRVCON = 0X45;//0100 0101������������bit�� 01������port2�ڸı���������  
	P2DRV = P2DRV_INIT;

	DRVCON = 0X85;//1000 0101������������bit�� 10������port3�ڸı���������
	P3DRV = P3DRV_INIT;

	DRVCON = 0Xc5;//1100 0101������������bit�� 11������port5�ڸı���������
	P5DRV = P5DRV_INIT;
}
///////////////////////////interrupt/////////////////////////////////////////
void interrupt_init(void)
{
	IEN0 |= IEN0_INIT;
	IEN1 = IEN1_INIT;
	IENC = IENC_INIT;
	EXF0 = EXF0_INIT;
	IPH0 = IPH0_INIT;
	IPL0 = IPL0_INIT;
	IPH1 = 0x02;//IPH1_INIT;
	IPL1 = 0x02;//IPL1_INIT;
}
///////////////////////////pwm/////////////////////////////////////////
void pwm_init(void)
{
	/*
	PWM0_MODE_ENABLE_BIT:=0����ֹPWMxyģ�飻 =1������PWMxyģ��
	PWM0_INT_ENABLE_BIT:=0����ֹPWMxy����ж� ��=1������PWMxy����ж�
	PWM00MOD_BIT: =0:����������͵�ƽ�� =1������������ߵ�ƽ
	PWM00SS:=0��PWMxy���������ֹ��=1��PWMxy�����������
	PWM0CLK_DIV:0��ϵͳʱ��/1�� 1��ϵͳʱ��/2��  2��ϵͳʱ��/4

	//T�����ڣ�=1/f��Ƶ�ʣ�--->Ƶ��=1/���ڣ�PERD��������һ��������60ms ��ôһ���Ӿ���16.6��PWM����
	*/
//PWM0
	PWM00CON = PWM00CON_INIT;//10011
	PWM01CON = PWM01CON_INIT;
	PWM02CON = PWM02CON_INIT;
	PWM03CON = PWM03CON_INIT;
	PWM04CON = PWM04CON_INIT;
	PWM05CON = PWM05CON_INIT;
	PWM0PERDH = PWM0PERDH_INIT;//PWM���ڼ������ֽ�  ���ڵ��ڸ��ֽ�+���ֽڣ�unsigned char���͵ģ�
	PWM0PERDL = PWM0PERDL_INIT;//PWM���ڼ������ֽ�  0x38+0x04=0x3c=60

	PWM00DUTY1H = PWM00DUTY1H_INIT;//ռ�ձ�=���ֽ�+���ֽ�  53
	PWM00DUTY1L = PWM00DUTY1L_INIT;
	PWM00DUTY2H = PWM00DUTY2H_INIT;//53
	PWM00DUTY2L = PWM00DUTY2L_INIT;

	PWM01DUTY1H = PWM01DUTY1H_INIT;
	PWM01DUTY1L = PWM01DUTY1L_INIT;//54
	PWM01DUTY2H = PWM01DUTY2H_INIT;
	PWM01DUTY2L = PWM01DUTY2L_INIT;//54

	PWM02DUTY1H = PWM02DUTY1H_INIT;
	PWM02DUTY1L = PWM02DUTY1L_INIT;//55
	PWM02DUTY2H = PWM02DUTY2H_INIT;
	PWM02DUTY2L = PWM02DUTY2L_INIT;//55

	PWM03DUTY1H = PWM03DUTY1H_INIT;
	PWM03DUTY1L = PWM03DUTY1L_INIT;//50
	PWM03DUTY2H = PWM03DUTY2H_INIT;
	PWM03DUTY2L = PWM03DUTY2L_INIT;//50

	PWM04DUTY1H = PWM04DUTY1H_INIT;
	PWM04DUTY1L = PWM04DUTY1L_INIT;//51
	PWM04DUTY2H = PWM04DUTY2H_INIT;
	PWM04DUTY2L = PWM04DUTY2L_INIT;//51

	PWM05DUTY1H = PWM05DUTY1H_INIT;
	PWM05DUTY1L = PWM05DUTY1L_INIT;//52
	PWM05DUTY2H = PWM05DUTY2H_INIT;
	PWM05DUTY2L = PWM05DUTY2L_INIT;//52

	//PWM1
	PWM10CON = PWM10CON_INIT;
	PWM11CON = PWM11CON_INIT;
	PWM12CON = PWM12CON_INIT;
	PWM13CON = PWM13CON_INIT;
	PWM14CON = PWM14CON_INIT;
	PWM15CON = PWM15CON_INIT;
	PWM1PERDH = PWM1PERDH_INIT;//���ռ�ձ�ֵ60
	PWM1PERDL = PWM1PERDL_INIT;

	PWM10DUTY1H = PWM10DUTY1H_INIT;
	PWM10DUTY1L = PWM10DUTY1L_INIT;//44
	PWM10DUTY2H = PWM10DUTY2H_INIT;
	PWM10DUTY2L = PWM10DUTY2L_INIT;//44

	PWM11DUTY1H = PWM11DUTY1H_INIT;
	PWM11DUTY1L = PWM11DUTY1L_INIT;//45
	PWM11DUTY2H = PWM11DUTY2H_INIT;
	PWM11DUTY2L = PWM11DUTY2L_INIT;//45

	PWM12DUTY1H = PWM12DUTY1H_INIT;
	PWM12DUTY1L = PWM12DUTY1L_INIT;//46
	PWM12DUTY2H = PWM12DUTY2H_INIT;
	PWM12DUTY2L = PWM12DUTY2L_INIT;//46

	PWM13DUTY1H = PWM13DUTY1H_INIT;
	PWM13DUTY1L = PWM13DUTY1L_INIT;//47
	PWM13DUTY2H = PWM13DUTY2H_INIT;
	PWM13DUTY2L = PWM13DUTY2L_INIT;//47

	PWM14DUTY1H = PWM14DUTY1H_INIT;
	PWM14DUTY1L = PWM14DUTY1L_INIT;//48
	PWM14DUTY2H = PWM14DUTY2H_INIT;
	PWM14DUTY2L = PWM14DUTY2L_INIT;//48

	PWM15DUTY1H = PWM15DUTY1H_INIT;
	PWM15DUTY1L = PWM15DUTY1L_INIT;//49
	PWM15DUTY2H = PWM15DUTY2H_INIT;
	PWM15DUTY2L = PWM15DUTY2L_INIT;//49

		//PWM2
	PWM20CON = PWM20CON_INIT;
	PWM21CON = PWM21CON_INIT;
	PWM22CON = PWM22CON_INIT;
	PWM23CON = PWM23CON_INIT;
	PWM24CON = PWM24CON_INIT;
	PWM25CON = PWM25CON_INIT;
	PWM2PERDH = PWM2PERDH_INIT;//���ռ�ձ�ֵ60
	PWM2PERDL = PWM2PERDL_INIT;

	PWM20DUTY1H = PWM20DUTY1H_INIT;
	PWM20DUTY1L = PWM20DUTY1L_INIT;//38
	PWM20DUTY2H = PWM20DUTY2H_INIT;
	PWM20DUTY2L = PWM20DUTY2L_INIT;//38

	PWM21DUTY1H = PWM21DUTY1H_INIT;
	PWM21DUTY1L = PWM21DUTY1L_INIT;//39
	PWM21DUTY2H = PWM21DUTY2H_INIT;
	PWM21DUTY2L = PWM21DUTY2L_INIT;//39

	PWM22DUTY1H = PWM22DUTY1H_INIT;
	PWM22DUTY1L = PWM22DUTY1L_INIT;//40
	PWM22DUTY2H = PWM22DUTY2H_INIT;
	PWM22DUTY2L = PWM22DUTY2L_INIT;//40

	PWM23DUTY1H = PWM23DUTY1H_INIT;
	PWM23DUTY1L = PWM23DUTY1L_INIT;//41
	PWM23DUTY2H = PWM23DUTY2H_INIT;
	PWM23DUTY2L = PWM23DUTY2L_INIT;//41

	PWM24DUTY1H = PWM24DUTY1H_INIT;
	PWM24DUTY1L = PWM24DUTY1L_INIT;//42
	PWM24DUTY2H = PWM24DUTY2H_INIT;
	PWM24DUTY2L = PWM24DUTY2L_INIT;//42

	PWM25DUTY1H = PWM25DUTY1H_INIT;//43
	PWM25DUTY1L = PWM25DUTY1L_INIT;
	PWM25DUTY2H = PWM25DUTY2H_INIT;//43
	PWM25DUTY2L = PWM25DUTY2L_INIT;
	
		
}
///////////////////////////spi/////////////////////////////////////////

void spi_init(void)
{
	SPCON = SPCON_INIT;
	SPSTA = SPSTA_INIT;
}
///////////////////////////uart/////////////////////////////////////////
void uart_init(void)
{
	PCON = PCON_INIT;
	SCON = SCON_INIT;
	SBRTH = (U8)(SBRT_INIT>>8);
	SBRTL = (U8)(SBRT_INIT);
	SFINE = SFINE_INIT;
	SADDR = SADDR_INIT;
	SADEN = SADEN_INIT;
}
///////////////////////////lpd/////////////////////////////////////////
void lpd_init(void)
{
	LPDCON = 	0;	//�͵�ѹ�����ƼĴ���
	LPDSEL = 	0;
}
///////////////////////////3.3V LDO/////////////////////////////////////////
void ldo_init(void)
{
		REGCON = REGCON_INIT;//0:�رյ�Դ��ѹ��  1��������Դ��ѹ��
}
///////////////////////////USB init/////////////////////////////////////////
void usb_init(void)
{
	USBADDR =USBADDR_INIT;
	USBIE1 = USBIE1_INIT;
	USBIE2 = USBIE2_INIT;
	USBCON = USBCON_INIT;
	Suspend_Counter = 0x00;
}



