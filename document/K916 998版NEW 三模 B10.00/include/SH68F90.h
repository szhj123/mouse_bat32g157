/*--------------------------------------------------------------------------
REG68F90.h
Copyright (c) 1996-2007 Sionwealth Electronic and Sinowealth Software, Inc.
All rights reserved.
--------------------------------------------------------------------------*/

#ifndef REG68F90_H
#define REG68F90_H
/* ------------------- BYTE Register-------------------- */
/* CPU */
sfr ACC = 0xE0;
sfr B = 0xF0;
sfr AUXC = 0xF1;
sfr PSW = 0xD0;
sfr SP = 0x81;
sfr DPL = 0x82;
sfr DPH = 0x83;
sfr DPL1 = 0x84;
sfr DPH1 = 0x85;
sfr INSCON = 0x86;

/*Power*/
sfr PCON = 0x87;
sfr SUSLO = 0x8E;

/* FLASH */
sfr IB_OFFSET	= 0xFB;
sfr IB_DATA	= 0xFC;
sfr IB_CON1	= 0xF2;
sfr IB_CON2	= 0xF3;
sfr IB_CON3	= 0xF4;
sfr IB_CON4	= 0xF5;
sfr IB_CON5	= 0xF6;
sfr XPAGE = 0xF7;
sfr FLASHCON = 0xA7;

/*WDT*/
sfr RSTSTAT = 0xB1;

/* SYSTEM CLOCK*/
sfr CLKCON = 0xB2;
sfr PLLCON = 0xBC;
sfr CLKLO = 0xBD;
sfr CLKRC0L = 0xBE;
sfr CLKRC0H = 0xC6;
sfr CLKRC1L = 0xBF;
sfr CLKRC1H = 0xC7; 

/* INTERRUPT */
sfr IEN0 = 0xA8;
sfr IEN1 = 0xA9;
sfr IPL0 = 0xB8;
sfr IPL1 = 0xB9;
sfr IPH0 = 0xB4;
sfr IPH1 = 0xB5;
sfr EXF0 = 0xB6;
sfr EXF1 = 0xE8;
sfr IENC = 0xBA;
sfr EXCON = 0x8B;  

/* EUART */
sfr SCON = 0xD8;
sfr SBUF = 0xAA;
sfr SADDR = 0xAB;
sfr SADEN = 0xAC;
sfr SBRTH = 0xAD;
sfr SBRTL = 0xAE;
sfr SFINE = 0xAF;

/* TIMER2 */
sfr T2CON = 0xC8;
sfr T2MOD = 0xC9;
sfr RCAP2L = 0xCA;
sfr RCAP2H = 0xCB;
sfr TL2 = 0xCC;
sfr TH2 = 0xCD;

/* SPI */
sfr SPCON = 0xA2;
sfr SPSTA = 0xA1;
sfr SPDAT = 0xA3;

/* REGULATOR */
sfr REGCON = 0x8f;

/* USB */
sfr USBCON = 0x91;//USB控制寄存器
sfr USBIF1 = 0x92;//USB中断向量寄存器1
sfr USBIF2 = 0x93;
sfr USBIE1 = 0x94;//USB中断使能寄存器1
sfr USBIE2 = 0x95;
sfr USBADDR = 0x96;//USB设备地址寄存器
sfr EP0CON = 0x97;//端点0控制寄存器
sfr EP1CON = 0x99;
sfr EP2CON = 0x9a;
sfr IEP0CNT = 0x9b;
sfr IEP1CNT = 0x9c;//端点1输入数据缓冲区长度寄存器
sfr IEP2CNT = 0x9d;
sfr OEP0CNT = 0x9e;//端点0输出数据缓冲区长度寄存器
sfr OEP1CNT = 0x9f;
sfr OEP2CNT = 0xa4;


/* LPD */
sfr LPDCON = 0xb3;
sfr LPDSEL = 0x89;

/* Drive option */
sfr DRVCON = 0x8c;
sfr P1DRV = 0xa5;
sfr P2DRV = 0xa6;
sfr P3DRV = 0xbb;
sfr P5DRV = 0x8d;

/* PWM0 */
#define PWM00CON			*((volatile unsigned char xdata *)0x0FF80)
#define PWM01CON			*((volatile unsigned char xdata *)0x0FF81)
#define PWM02CON			*((volatile unsigned char xdata *)0x0FF82)
#define PWM03CON			*((volatile unsigned char xdata *)0x0FF83)
#define PWM04CON			*((volatile unsigned char xdata *)0x0FF84)
#define PWM05CON			*((volatile unsigned char xdata *)0x0FF85)

#define PWM0PERDL			*((volatile unsigned char xdata *)0x0FF98)
#define PWM0PERDH			*((volatile unsigned char xdata *)0x0FF9c)

#define PWM00DUTY1L			*((volatile unsigned char xdata *)0x0FFA0)
#define PWM00DUTY1H			*((volatile unsigned char xdata *)0x0FFB8)
#define PWM00DUTY2L			*((volatile unsigned char xdata *)0x0FFD0)
#define PWM00DUTY2H			*((volatile unsigned char xdata *)0x0FFE8)

#define PWM01DUTY1L			*((volatile unsigned char xdata *)0x0FFA1)
#define PWM01DUTY1H			*((volatile unsigned char xdata *)0x0FFB9)
#define PWM01DUTY2L			*((volatile unsigned char xdata *)0x0FFD1)
#define PWM01DUTY2H			*((volatile unsigned char xdata *)0x0FFE9)

#define PWM02DUTY1L			*((volatile unsigned char xdata *)0x0FFA2)
#define PWM02DUTY1H			*((volatile unsigned char xdata *)0x0FFBA)
#define PWM02DUTY2L			*((volatile unsigned char xdata *)0x0FFD2)
#define PWM02DUTY2H			*((volatile unsigned char xdata *)0x0FFEA)

#define PWM03DUTY1L			*((volatile unsigned char xdata *)0x0FFA3)
#define PWM03DUTY1H			*((volatile unsigned char xdata *)0x0FFBB)
#define PWM03DUTY2L			*((volatile unsigned char xdata *)0x0FFD3)
#define PWM03DUTY2H			*((volatile unsigned char xdata *)0x0FFEB)

#define PWM04DUTY1L			*((volatile unsigned char xdata *)0x0FFA4)
#define PWM04DUTY1H			*((volatile unsigned char xdata *)0x0FFBC)
#define PWM04DUTY2L			*((volatile unsigned char xdata *)0x0FFD4)
#define PWM04DUTY2H			*((volatile unsigned char xdata *)0x0FFEC)

#define PWM05DUTY1L			*((volatile unsigned char xdata *)0x0FFA5)
#define PWM05DUTY1H			*((volatile unsigned char xdata *)0x0FFBD)
#define PWM05DUTY2L			*((volatile unsigned char xdata *)0x0FFD5)
#define PWM05DUTY2H			*((volatile unsigned char xdata *)0x0FFED)

/* PWM1 */
#define PWM10CON			*((volatile unsigned char xdata *)0x0FF86)
#define PWM11CON			*((volatile unsigned char xdata *)0x0FF87)
#define PWM12CON			*((volatile unsigned char xdata *)0x0FF88)
#define PWM13CON			*((volatile unsigned char xdata *)0x0FF89)
#define PWM14CON			*((volatile unsigned char xdata *)0x0FF8A)
#define PWM15CON			*((volatile unsigned char xdata *)0x0FF8B)

#define PWM1PERDL			*((volatile unsigned char xdata *)0x0FF99)
#define PWM1PERDH			*((volatile unsigned char xdata *)0x0FF9D)

#define PWM10DUTY1L			*((volatile unsigned char xdata *)0x0FFA6)
#define PWM10DUTY1H			*((volatile unsigned char xdata *)0x0FFBE)
#define PWM10DUTY2L			*((volatile unsigned char xdata *)0x0FFD6)
#define PWM10DUTY2H			*((volatile unsigned char xdata *)0x0FFEE)

#define PWM11DUTY1L			*((volatile unsigned char xdata *)0x0FFA7)
#define PWM11DUTY1H			*((volatile unsigned char xdata *)0x0FFBF)
#define PWM11DUTY2L			*((volatile unsigned char xdata *)0x0FFD7)
#define PWM11DUTY2H			*((volatile unsigned char xdata *)0x0FFEF)

#define PWM12DUTY1L			*((volatile unsigned char xdata *)0x0FFA8)
#define PWM12DUTY1H			*((volatile unsigned char xdata *)0x0FFC0)
#define PWM12DUTY2L			*((volatile unsigned char xdata *)0x0FFD8)
#define PWM12DUTY2H			*((volatile unsigned char xdata *)0x0FFF0)

#define PWM13DUTY1L			*((volatile unsigned char xdata *)0x0FFA9)
#define PWM13DUTY1H			*((volatile unsigned char xdata *)0x0FFC1)
#define PWM13DUTY2L			*((volatile unsigned char xdata *)0x0FFD9)
#define PWM13DUTY2H			*((volatile unsigned char xdata *)0x0FFF1)

#define PWM14DUTY1L			*((volatile unsigned char xdata *)0x0FFAA)
#define PWM14DUTY1H			*((volatile unsigned char xdata *)0x0FFC2)
#define PWM14DUTY2L			*((volatile unsigned char xdata *)0x0FFDA)
#define PWM14DUTY2H			*((volatile unsigned char xdata *)0x0FFF2)

#define PWM15DUTY1L			*((volatile unsigned char xdata *)0x0FFAB)
#define PWM15DUTY1H			*((volatile unsigned char xdata *)0x0FFC3)
#define PWM15DUTY2L			*((volatile unsigned char xdata *)0x0FFDB)
#define PWM15DUTY2H			*((volatile unsigned char xdata *)0x0FFF3)

/* PWM2 */
#define PWM20CON			*((volatile unsigned char xdata *)0x0FF8C)
#define PWM21CON			*((volatile unsigned char xdata *)0x0FF8D)
#define PWM22CON			*((volatile unsigned char xdata *)0x0FF8E)
#define PWM23CON			*((volatile unsigned char xdata *)0x0FF8F)
#define PWM24CON			*((volatile unsigned char xdata *)0x0FF90)
#define PWM25CON			*((volatile unsigned char xdata *)0x0FF91)

#define PWM2PERDL			*((volatile unsigned char xdata *)0x0FF9A)
#define PWM2PERDH			*((volatile unsigned char xdata *)0x0FF9E)

#define PWM20DUTY1L			*((volatile unsigned char xdata *)0x0FFAC)
#define PWM20DUTY1H			*((volatile unsigned char xdata *)0x0FFC4)
#define PWM20DUTY2L			*((volatile unsigned char xdata *)0x0FFDC)
#define PWM20DUTY2H			*((volatile unsigned char xdata *)0x0FFF4)

#define PWM21DUTY1L			*((volatile unsigned char xdata *)0x0FFAD)
#define PWM21DUTY1H			*((volatile unsigned char xdata *)0x0FFC5)
#define PWM21DUTY2L			*((volatile unsigned char xdata *)0x0FFDD)
#define PWM21DUTY2H			*((volatile unsigned char xdata *)0x0FFF5)

#define PWM22DUTY1L			*((volatile unsigned char xdata *)0x0FFAE)
#define PWM22DUTY1H			*((volatile unsigned char xdata *)0x0FFC6)
#define PWM22DUTY2L			*((volatile unsigned char xdata *)0x0FFDE)
#define PWM22DUTY2H			*((volatile unsigned char xdata *)0x0FFF6)

#define PWM23DUTY1L			*((volatile unsigned char xdata *)0x0FFAF)
#define PWM23DUTY1H			*((volatile unsigned char xdata *)0x0FFC7)
#define PWM23DUTY2L			*((volatile unsigned char xdata *)0x0FFDF)
#define PWM23DUTY2H			*((volatile unsigned char xdata *)0x0FFF7)

#define PWM24DUTY1L			*((volatile unsigned char xdata *)0x0FFB0)
#define PWM24DUTY1H			*((volatile unsigned char xdata *)0x0FFC8)
#define PWM24DUTY2L			*((volatile unsigned char xdata *)0x0FFE0)
#define PWM24DUTY2H			*((volatile unsigned char xdata *)0x0FFF8)

#define PWM25DUTY1L			*((volatile unsigned char xdata *)0x0FFB1)
#define PWM25DUTY1H			*((volatile unsigned char xdata *)0x0FFC9)
#define PWM25DUTY2L			*((volatile unsigned char xdata *)0x0FFE1)
#define PWM25DUTY2H			*((volatile unsigned char xdata *)0x0FFF9)

/* PWM3 */
#define PWM30CON			*((volatile unsigned char xdata *)0x0FF92)
#define PWM31CON			*((volatile unsigned char xdata *)0x0FF93)
#define PWM32CON			*((volatile unsigned char xdata *)0x0FF94)
#define PWM33CON			*((volatile unsigned char xdata *)0x0FF95)

#define PWM3PERDL			*((volatile unsigned char xdata *)0x0FF9B)
#define PWM3PERDH			*((volatile unsigned char xdata *)0x0FF9F)

#define PWM30DUTY1L			*((volatile unsigned char xdata *)0x0FFB2)
#define PWM30DUTY1H			*((volatile unsigned char xdata *)0x0FFCA)
#define PWM30DUTY2L			*((volatile unsigned char xdata *)0x0FFE2)
#define PWM30DUTY2H			*((volatile unsigned char xdata *)0x0FFFA)

#define PWM31DUTY1L			*((volatile unsigned char xdata *)0x0FFB3)
#define PWM31DUTY1H			*((volatile unsigned char xdata *)0x0FFCB)
#define PWM31DUTY2L			*((volatile unsigned char xdata *)0x0FFE3)
#define PWM31DUTY2H			*((volatile unsigned char xdata *)0x0FFFB)

#define PWM32DUTY1L			*((volatile unsigned char xdata *)0x0FFB4)
#define PWM32DUTY1H			*((volatile unsigned char xdata *)0x0FFCC)
#define PWM32DUTY2L			*((volatile unsigned char xdata *)0x0FFE4)
#define PWM32DUTY2H			*((volatile unsigned char xdata *)0x0FFFC)

#define PWM33DUTY1L			*((volatile unsigned char xdata *)0x0FFB5)
#define PWM33DUTY1H			*((volatile unsigned char xdata *)0x0FFCD)
#define PWM33DUTY2L			*((volatile unsigned char xdata *)0x0FFE5)
#define PWM33DUTY2H			*((volatile unsigned char xdata *)0x0FFFD)

/* PWM4 */
sfr PWM40CON = 0xDA;
sfr PWM41CON = 0xDB;
sfr PWM42CON = 0xDC;

sfr PWM4PERDL = 0xDD;
sfr PWM4PERDH = 0xDE;

sfr PWM40DUTY1L = 0xD2;
sfr PWM41DUTY1L = 0xD3;
sfr PWM42DUTY1L = 0xD4;

sfr PWM40DUTY1H = 0xD5;
sfr PWM41DUTY1H = 0xD6;
sfr PWM42DUTY1H = 0xD7;

sfr PWM40DUTY2L = 0xCE;
sfr PWM41DUTY2L = 0xC1;
sfr PWM42DUTY2L = 0xC2;

sfr PWM40DUTY2H = 0xC3;
sfr PWM41DUTY2H = 0xC4;
sfr PWM42DUTY2H = 0xC5;
/* PORT */
sfr P0 = 0x80;
sfr P1 = 0x90;
sfr P2 = 0x98;
sfr P3 = 0xA0;
sfr P4 = 0xB0;
sfr P5 = 0x88;
sfr P6 = 0xC0;
sfr P7 = 0xF8;

sfr P0CR = 0xE1;
sfr P1CR = 0xE2;
sfr P2CR = 0xE3;
sfr P3CR = 0xE4;
sfr P4CR = 0xE5;
sfr P5CR = 0xE6;
sfr P6CR = 0xE7;
sfr P7CR = 0xD1;

sfr P0PCR = 0xE9;
sfr P1PCR = 0xEA;
sfr P2PCR = 0xEB;
sfr P3PCR = 0xEC;
sfr P4PCR = 0xED;
sfr P5PCR = 0xEE;
sfr P6PCR = 0xEF;
sfr P7PCR = 0xD9;

/*--------------------------  BIT Register -------------------- */
/* P0 */
sbit P0_0 = P0^0;
sbit P0_1 = P0^1;
sbit P0_2 = P0^2;
sbit P0_3 = P0^3;
sbit P0_4 = P0^4;
sbit P0_5 = P0^5;
sbit P0_6 = P0^6;
sbit P0_7 = P0^7;

/* P1 */
sbit P1_0 = P1^0;
sbit P1_1 = P1^1;
sbit P1_2 = P1^2;
sbit P1_3 = P1^3;
sbit P1_4 = P1^4;
sbit P1_5 = P1^5;

/* P2 */
sbit P2_0 = P2^0;
sbit P2_1 = P2^1;
sbit P2_2 = P2^2;
sbit P2_3 = P2^3;
sbit P2_4 = P2^4;
sbit P2_5 = P2^5;

/* P3 */  
sbit P3_0 = P3^0;
sbit P3_1 = P3^1;
sbit P3_2 = P3^2;
sbit P3_3 = P3^3;
sbit P3_4 = P3^4;
sbit P3_5 = P3^5;

/* P4 */
sbit P4_0 = P4^0;
sbit P4_1 = P4^1;
sbit P4_2 = P4^2;
sbit P4_3 = P4^3;
sbit P4_4 = P4^4;
sbit P4_5 = P4^5;
sbit P4_6 = P4^6;
sbit P4_7 = P4^7;

/* P5 */
sbit P5_0 = P5^0;
sbit P5_1 = P5^1;
sbit P5_2 = P5^2;
sbit P5_3 = P5^3;
sbit P5_4 = P5^4;
sbit P5_5 = P5^5;
sbit P5_6 = P5^6;
sbit P5_7 = P5^7;

/* P6 */
sbit P6_0 = P6^0;
sbit P6_1 = P6^1;
sbit P6_2 = P6^2;
sbit P6_3 = P6^3;
sbit P6_4 = P6^4;
sbit P6_5 = P6^5;
sbit P6_6 = P6^6;
sbit P6_7 = P6^7;

/* P7 */
sbit P7_0 = P7^0;
sbit P7_1 = P7^1;
sbit P7_2 = P7^2;
sbit P7_3 = P7^3;
sbit P7_4 = P7^4;
sbit P7_5 = P7^5;
sbit P7_6 = P7^6;
sbit P7_7 = P7^7;

/*  PSW   */
sbit CY = 0xD7;
sbit AC = 0xD6;
sbit F0 = 0xD5;
sbit RS1 = 0xD4;
sbit RS0 = 0xD3;
sbit OV = 0xD2;
sbit F1 = 0XD1;
sbit P = 0xD0;

/*  IEN0   */
sbit EA = 0xAF;
sbit ESPI = 0xAE;
sbit ELPD = 0xAD;
sbit ESCM = 0xAC;
sbit EX2 = 0xAB;
sbit EX3 = 0xAA;
sbit EX4 = 0xA9;
sbit ET2 = 0xA8;

/*  T2CON  */
sbit TF2 = 0xCF;
sbit EXF2 = 0xCE;
sbit EXEN2 = 0xCB;
sbit TR2 = 0xCA;
sbit C_T2 = 0xC9;
sbit CP_RL2 = 0xC8;

/*  SCON  */
sbit SM0_FE = 0xDF;
sbit SM1_RXOV = 0xDE;
sbit SM2_TXCOL = 0xDD;
sbit REN = 0xDC;
sbit TB8 = 0xDB;
sbit RB8 = 0xDA;
sbit TI = 0xD9;
sbit RI = 0xD8;

/*  EXF1  */
sbit IF47 = 0xEF;
sbit IF46 = 0xEE;
sbit IF45 = 0xED;
sbit IF44 = 0xEC;
sbit IF43 = 0xEB;
sbit IF42 = 0xEA;
sbit IF41 = 0xE9;
sbit IF40 = 0xE8;

/*  ACC  */
sbit ACC_7 = 0xE7;
sbit ACC_6 = 0xE6;
sbit ACC_5 = 0xE5;
sbit ACC_4 = 0xE4;
sbit ACC_3 = 0xE3;
sbit ACC_2 = 0xE2;
sbit ACC_1 = 0xE1;
sbit ACC_0 = 0xE0;

/*  B  */
sbit B_7 = 0xF7;
sbit B_6 = 0xF6;
sbit B_5 = 0xF5;
sbit B_4 = 0xF4;
sbit B_3 = 0xF3;
sbit B_2 = 0xF2;
sbit B_1 = 0xF1;
sbit B_0 = 0xF0;

/*  IPL0   */ 
sbit PT2L = 0x88;
sbit PX4L = 0x89;
sbit PX3L = 0x8a;
sbit PX2L = 0x8b;
sbit PSCML = 0x8c;
sbit PLPDL = 0x8d;
sbit PSPIL = 0x8e;


#endif

