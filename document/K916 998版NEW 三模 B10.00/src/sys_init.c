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
	CLKCON = (CLKCON_INIT & 0x08);  //open high clock  打开高速时钟
	delay_us(350);
	PLLCON = (PLLCON_INIT & 0x02);//pll锁相环时钟配置
	delay_us(533);
	CLR_WDT();
	PLLCON = PLLCON_INIT;
	CLKCON = CLKCON_INIT; //sys clock = high clock  系统时钟=高速时钟
}
///////////////////////////timer2/////////////////////////////////////////
///////////////////////////gpio////////////////////////////////////////
void gpio_init(void)
{		//CR=0为输入模式，CR=1为输出模式，PCR=1是允许内部上拉，PCR=0是不允许内部上拉
	P0CR = P0CR_INIT;//1111 0100   p0_0 p0_1 p0_3设置为输入
	P1CR = P1CR_INIT;//11 1111     P1_0~P1~5全部设置为输出
	P2CR = P2CR_INIT;//11 1111
	P3CR = P3CR_INIT;//11 1111
	P4CR = P4CR_INIT;//1110 1101   p4_1 p4_4 设置为输入
	P5CR = P5CR_INIT;//1000 0111   p5_3 p5_4 p5_5 p5_6设置为输入
	P6CR = P6CR_INIT;//1111 1111
	P7CR = P7CR_INIT;//0111 0000   p7_0 p7_1 p7_2 p7_3  p7_7设置为输入

	P0PCR = P0PCR_INIT;//1110 0000  P0_5 P0_6 P0_7设置为允许内部上拉
	P1PCR = P1PCR_INIT;//11 1111
	P2PCR = P2PCR_INIT;//11 1111
	P3PCR = P3PCR_INIT;//11 1111
	P4PCR = P4PCR_INIT;//0110 1101
	P5PCR = P5PCR_INIT;//1111 1111
	P6PCR = P6PCR_INIT;//1111 1111
	P7PCR = P7PCR_INIT;//0101 1111

	P0 = P0_OUTPUT_LEVEL;//1110 0100  设置p0_0、1、3、4为低电平，p0_2、5、6、7为高电平
	P1 = P1_OUTPUT_LEVEL;//00 0000
	P2 = P2_OUTPUT_LEVEL;//00 0000
	P3 = P3_OUTPUT_LEVEL;//00 0000
	P4 = P4_OUTPUT_LEVEL;//1110 1101  设置p4_1、4为低电平，p4_0、2、3、5、6、7为高电平
	P5 = P5_OUTPUT_LEVEL;//1000 0111  设置p5_3、4、5、6为低电平，p5_0、1、2、7为高电平
	P6 = P6_OUTPUT_LEVEL;//1111 1111  设置p6_0、1、2、3、4、5、6、7为高电平
	P7 = P7_OUTPUT_LEVEL;//0001 0000  设置p7_0、1、2、3、4、5、7为低电平，p7_4为高电平

	DRVCON = 0X05;//只有当DRVCON[3：0] = 0x5，才能允许寄存器修改相应port口驱动大小  0000 0101，看第六第七bit， 00：允许port1口改变驱动能力
	P1DRV = P1DRV_INIT;//只有配置好寄存器DRVCON后，紧接着写驱动选择寄存器，驱动改变才有效  PxDRV:驱动选择寄存器

	DRVCON = 0X45;//0100 0101，看第六第七bit， 01：允许port2口改变驱动能力  
	P2DRV = P2DRV_INIT;

	DRVCON = 0X85;//1000 0101，看第六第七bit， 10：允许port3口改变驱动能力
	P3DRV = P3DRV_INIT;

	DRVCON = 0Xc5;//1100 0101，看第六第七bit， 11：允许port5口改变驱动能力
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
	PWM0_MODE_ENABLE_BIT:=0：禁止PWMxy模块； =1：允许PWMxy模块
	PWM0_INT_ENABLE_BIT:=0：禁止PWMxy溢出中断 ；=1：允许PWMxy溢出中断
	PWM00MOD_BIT: =0:周期内输出低电平； =1：周期内输出高电平
	PWM00SS:=0：PWMxy引脚输出禁止；=1：PWMxy引脚输出允许
	PWM0CLK_DIV:0：系统时钟/1； 1：系统时钟/2；  2：系统时钟/4

	//T（周期）=1/f（频率）--->频率=1/周期（PERD），现在一个周期是60ms 那么一秒钟就有16.6次PWM周期
	*/
//PWM0
	PWM00CON = PWM00CON_INIT;//10011
	PWM01CON = PWM01CON_INIT;
	PWM02CON = PWM02CON_INIT;
	PWM03CON = PWM03CON_INIT;
	PWM04CON = PWM04CON_INIT;
	PWM05CON = PWM05CON_INIT;
	PWM0PERDH = PWM0PERDH_INIT;//PWM周期计数高字节  周期等于高字节+低字节（unsigned char类型的）
	PWM0PERDL = PWM0PERDL_INIT;//PWM周期计数低字节  0x38+0x04=0x3c=60

	PWM00DUTY1H = PWM00DUTY1H_INIT;//占空比=高字节+低字节  53
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
	PWM1PERDH = PWM1PERDH_INIT;//最大占空比值60
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
	PWM2PERDH = PWM2PERDH_INIT;//最大占空比值60
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
	LPDCON = 	0;	//低电压检测控制寄存器
	LPDSEL = 	0;
}
///////////////////////////3.3V LDO/////////////////////////////////////////
void ldo_init(void)
{
		REGCON = REGCON_INIT;//0:关闭电源稳压器  1：开启电源稳压器
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



