//*** <<< Use Configuration Wizard in Context Menu >>> ***

//=============================================================================================================
//systern clock
//=============================================================================================================
//<h>Clock
#define _SYS_CLK_DIV		0
#define _OSC2_EN				8
#define _CLK_SRC				4

#define _PLLON				2
#define _OSCS_SRC			1
/******************************************resigter value**********************************************/
#define CLKCON_INIT		(_SYS_CLK_DIV|_OSC2_EN|_CLK_SRC)
#define PLLCON_INIT		(_PLLON|_OSCS_SRC)
/*****************************************************************************************************/
//=============================================================================================================
#define _TIMER2_EXEN			0
#define _TIMER2_TR2				0
#define _TIMER2_CT2				0
#define _TIMER2_CP2				0

#define _TIMER2_TCLKP2				0
#define _TIMER2_T2OE				0
#define _TIMER2_DCEN				0
#define _SYS_CLOCK   					24
#define _TIMER2_INTERVAL_TIME		200
/******************************************resigter value**********************************************/
#define T2CON_INIT		(_TIMER2_EXEN|_TIMER2_TR2|_TIMER2_CT2|_TIMER2_CP2)
#define T2MOD_INIT		(_TIMER2_TCLKP2|_TIMER2_T2OE|_TIMER2_DCEN)

#define TCLK_DIV    (T2MOD_INIT >> 7)
#if    (TCLK_DIV == 0)
    #define T2_CLK    (_SYS_CLOCK/12)
#else        
    #define T2_CLK    (_SYS_CLOCK)
#endif

#define  T2_INIT_VAL   (0xFFFF-(U32)_TIMER2_INTERVAL_TIME*T2_CLK)
/*****************************************************************************************************/
//=============================================================================================================
//interrupt
//=============================================================================================================
/************ET2*************/
#define _ET2_ENABLE_BIT		1
#define _ET2_PRI0RITY			0
/************EX4*************/
#define _EX4_ENABLE_BIT			    0
#define _EX4_PRIORITY			      0
#define _EX4_TRIGGER_MODE			  0
#define _EXS4_ENABLE_BYTE			  0
/************EX3*************/
#define _EX3_ENABLE_BIT			    0
#define _EX3_PRIORITY			      0
#define _EX3_TRIGGER_MODE			  0
/************EX2*************/
#define _EX2_ENABLE_BIT			    0
#define _EX2_PRIORITY			      0
#define _EX2_TRIGGER_MODE			  0
/************ESCM*************/
#define _ESCM_ENABLE_BIT			    0
#define _ESCM_PRIORITY			      0
/************ELPD*************/
#define _ELPD_ENABLE_BIT			    0
#define _ELPD_PRIORITY			      0
/************ESPI*************/
#define _ESPI_ENABLE_BIT			    0
#define _ESPI_PRIORITY			      0
/************EUSB*************/
#define _EUSB_ENABLE_BIT			    1
#define _EUSB_PRI0RITY			      	0
/************EPWM0*************/
#define _EPWM0_ENABLE_BIT			    1
#define _EPWM0_PRI0RITY			      0
/************EPWM1*************/
#define _EPWM1_ENABLE_BIT			    0
#define _EPWM1_PRI0RITY			      0
/************EPWM2*************/
#define _EPWM2_ENABLE_BIT			    0
#define _EPWM2_PRI0RITY			      0
/************EPWM3*************/
#define _EPWM3_ENABLE_BIT			    0
#define _EPWM3_PRI0RITY			      0
/************EPWM4*************/
#define _EPWM4_ENABLE_BIT			    0
#define _EPWM4_PRI0RITY			      0
/************ES0*************/
#define _ES0_ENABLE_BIT			    0
#define _ES0_PRI0RITY			      0
//</h>
/******************************************resigter value**********************************************/
#define  IEN0_INIT   (_ET2_ENABLE_BIT|_EX4_ENABLE_BIT|_EX3_ENABLE_BIT|_EX2_ENABLE_BIT|_ESCM_ENABLE_BIT|_ELPD_ENABLE_BIT|_ESPI_ENABLE_BIT)
#define  IEN1_INIT   (_EUSB_ENABLE_BIT|_EPWM0_ENABLE_BIT|_EPWM1_ENABLE_BIT|_EPWM2_ENABLE_BIT|_EPWM3_ENABLE_BIT|_EPWM4_ENABLE_BIT|_ES0_ENABLE_BIT)
#define  IENC_INIT   (_EXS4_ENABLE_BYTE)
#define  EXF0_INIT   (_EX4_TRIGGER_MODE|_EX3_TRIGGER_MODE|_EX2_TRIGGER_MODE)

#define  IPH0_INIT   (((_ESPI_PRIORITY&2)<<5)|((_ELPD_PRIORITY&2)<<4)\
                     |((_ESCM_PRIORITY&2)<<3)|((_EX2_PRIORITY&2)<<2)\
										 |((_EX3_PRIORITY&2)<<1)|((_EX4_PRIORITY&2))\
                     |((_ET2_PRI0RITY&2)>>1) )
#define  IPL0_INIT   (((_ESPI_PRIORITY&1)<<6)|((_ELPD_PRIORITY&1)<<5)\
                     |((_ESCM_PRIORITY&1)<<4)|((_EX2_PRIORITY&1)<<3)\
										 |((_EX3_PRIORITY&1)<<2)|((_EX4_PRIORITY&1)<<1)\
                     |(_ET2_PRI0RITY&1) )

#define  IPH1_INIT   (((_ES0_PRI0RITY&2)<<5)|((_EPWM4_PRI0RITY&2)<<4)\
                     |((_EPWM3_PRI0RITY&2)<<3)|((_EPWM2_PRI0RITY&2)<<2)\
										 |((_EPWM1_PRI0RITY&2)<<1)|((_EPWM0_PRI0RITY&2))\
                     |((_EUSB_PRI0RITY&2)>>1) )
#define  IPL1_INIT   (((_ES0_PRI0RITY&1)<<6)|((_EPWM4_PRI0RITY&1)<<5)\
                     |((_EPWM3_PRI0RITY&1)<<4)|((_EPWM2_PRI0RITY&1)<<3)\
										 |((_EPWM1_PRI0RITY&1)<<2)|((_EPWM0_PRI0RITY&1)<<1)\
                     |(_EUSB_PRI0RITY&1) )
/**********************************************************************************************************/
//=============================================================================================================
//GPIO
//=============================================================================================================
//<h>GPIO  {P0, P1, P2, P3, P4, P5,P6,P7}
//			<h>GPIO P0 
#define P00_WORK_MODE    0
#define P00_INPUT_PULL   0
#define P00_OUTPUT_LEV   0

#define P01_WORK_MODE    0
#define P01_INPUT_PULL   0
#define P01_OUTPUT_LEV   0

#define P02_WORK_MODE    4//SPI_MOT
#define P02_INPUT_PULL   0
#define P02_OUTPUT_LEV   4

#define P03_WORK_MODE    0//SPI_MISO
#define P03_INPUT_PULL   0
#define P03_OUTPUT_LEV   0

#define P04_WORK_MODE    16//SPI_MOSI
#define P04_INPUT_PULL   0
#define P04_OUTPUT_LEV   0

#define P05_WORK_MODE    	32
#define P05_INPUT_PULL   	32
#define P05_OUTPUT_LEV   	32

#define P06_WORK_MODE    	64		
#define P06_INPUT_PULL   	64
#define P06_OUTPUT_LEV   	64

#define P07_WORK_MODE    	128
#define P07_INPUT_PULL   	128
#define P07_OUTPUT_LEV   	128

//			<h>GPIO P1 
#define P10_WORK_MODE    1
#define P10_INPUT_PULL   1
#define P10_OUTPUT_LEV   0

#define P11_WORK_MODE    2
#define P11_INPUT_PULL   2
#define P11_OUTPUT_LEV   0

#define P12_WORK_MODE    4
#define P12_INPUT_PULL   4
#define P12_OUTPUT_LEV   0

#define P13_WORK_MODE    8
#define P13_INPUT_PULL   8
#define P13_OUTPUT_LEV   0

#define P14_WORK_MODE    16
#define P14_INPUT_PULL   16
#define P14_OUTPUT_LEV   0

#define P15_WORK_MODE    32
#define P15_INPUT_PULL   32
#define P15_OUTPUT_LEV   0

#define P1_DRIVING_ENABLE   1
#define P1_DRIVING_LEV   0

//			<h>GPIO P2 
#define P20_WORK_MODE    1
#define P20_INPUT_PULL   1
#define P20_OUTPUT_LEV   0

#define P21_WORK_MODE    2
#define P21_INPUT_PULL   2
#define P21_OUTPUT_LEV   0

#define P22_WORK_MODE    4
#define P22_INPUT_PULL   4
#define P22_OUTPUT_LEV   0

#define P23_WORK_MODE    8
#define P23_INPUT_PULL   8
#define P23_OUTPUT_LEV   0

#define P24_WORK_MODE    16
#define P24_INPUT_PULL   16
#define P24_OUTPUT_LEV   0

#define P25_WORK_MODE    32
#define P25_INPUT_PULL   32
#define P25_OUTPUT_LEV   0

#define P2_DRIVING_ENABLE   1
#define P2_DRIVING_LEV   0

//			<h>GPIO P3 
#define P30_WORK_MODE    1
#define P30_INPUT_PULL   1
#define P30_OUTPUT_LEV   0

#define P31_WORK_MODE    2
#define P31_INPUT_PULL   2
#define P31_OUTPUT_LEV   0

#define P32_WORK_MODE    4
#define P32_INPUT_PULL   4
#define P32_OUTPUT_LEV   0

#define P33_WORK_MODE    8
#define P33_INPUT_PULL   8
#define P33_OUTPUT_LEV   0

#define P34_WORK_MODE    16
#define P34_INPUT_PULL   16
#define P34_OUTPUT_LEV   0

#define P35_WORK_MODE    32
#define P35_INPUT_PULL   32
#define P35_OUTPUT_LEV   0

#define P3_DRIVING_ENABLE   1
#define P3_DRIVING_LEV   0

//			<h>GPIO P4 
#define P40_WORK_MODE    	1
#define P40_INPUT_PULL   	1
#define P40_OUTPUT_LEV   	1

#define P41_WORK_MODE    	0//SLEEP_PIN
#define P41_INPUT_PULL   	0
#define P41_OUTPUT_LEV   	0

#define P42_WORK_MODE    	4
#define P42_INPUT_PULL   	4
#define P42_OUTPUT_LEV   	4

#define P43_WORK_MODE    	8
#define P43_INPUT_PULL   	8
#define P43_OUTPUT_LEV   	8

#define P44_WORK_MODE    	0
#define P44_INPUT_PULL   	0
#define P44_OUTPUT_LEV   	0

#define P45_WORK_MODE    	32
#define P45_INPUT_PULL   	32
#define P45_OUTPUT_LEV   	32

#define P46_WORK_MODE    	64
#define P46_INPUT_PULL   	64
#define P46_OUTPUT_LEV   	64

#define P47_WORK_MODE    	128//SPI_SCK
#define P47_INPUT_PULL   	0
#define P47_OUTPUT_LEV   	128
//			<h>GPIO P5 
#define P50_WORK_MODE    	1
#define P50_INPUT_PULL   	1
#define P50_OUTPUT_LEV   	1

#define P51_WORK_MODE    	2
#define P51_INPUT_PULL   	2
#define P51_OUTPUT_LEV   	2

#define P52_WORK_MODE    	4
#define P52_INPUT_PULL   	4
#define P52_OUTPUT_LEV   	4

#define P53_WORK_MODE    	0
#define P53_INPUT_PULL   	8
#define P53_OUTPUT_LEV   	0

#define P54_WORK_MODE    	0
#define P54_INPUT_PULL   	16
#define P54_OUTPUT_LEV   	0

#define P55_WORK_MODE    	0
#define P55_INPUT_PULL   	32
#define P55_OUTPUT_LEV   	0

#define P56_WORK_MODE    	0
#define P56_INPUT_PULL   	64
#define P56_OUTPUT_LEV   	0

#define P57_WORK_MODE    	128
#define P57_INPUT_PULL   	128
#define P57_OUTPUT_LEV   	128

#define P5_DRIVING_ENABLE   0
#define P5_DRIVING_LEV   0

//			<h>GPIO P6 
#define P60_WORK_MODE    	1
#define P60_INPUT_PULL   	1
#define P60_OUTPUT_LEV   	1

#define P61_WORK_MODE    	2
#define P61_INPUT_PULL   	2
#define P61_OUTPUT_LEV   	2

#define P62_WORK_MODE    	4
#define P62_INPUT_PULL   	4
#define P62_OUTPUT_LEV   	4

#define P63_WORK_MODE    	8
#define P63_INPUT_PULL   	8
#define P63_OUTPUT_LEV   	8

#define P64_WORK_MODE    	16
#define P64_INPUT_PULL   	16
#define P64_OUTPUT_LEV   	16

#define P65_WORK_MODE    	32
#define P65_INPUT_PULL   	32
#define P65_OUTPUT_LEV   	32

#define P66_WORK_MODE    	64
#define P66_INPUT_PULL   	64
#define P66_OUTPUT_LEV   	64

#define P67_WORK_MODE    	128
#define P67_INPUT_PULL   	128
#define P67_OUTPUT_LEV   	128


#define P70_WORK_MODE    	0
#define P70_INPUT_PULL   	1
#define P70_OUTPUT_LEV   	0

#define P71_WORK_MODE    	0
#define P71_INPUT_PULL   	2
#define P71_OUTPUT_LEV   	0

#define P72_WORK_MODE    	0
#define P72_INPUT_PULL   	4
#define P72_OUTPUT_LEV   	0

#define P73_WORK_MODE    	0
#define P73_INPUT_PULL  	 	8
#define P73_OUTPUT_LEV   	0

#define P74_WORK_MODE    	16
#define P74_INPUT_PULL   		16
#define P74_OUTPUT_LEV   		16

#define P75_WORK_MODE    	32//SPI_SS
#define P75_INPUT_PULL   		0
#define P75_OUTPUT_LEV   		0

#define P76_WORK_MODE    	64
#define P76_INPUT_PULL   		64	//0x40
#define P76_OUTPUT_LEV   		0

#define P77_WORK_MODE	0
#define P77_INPUT_PULL   	0	//0x80
#define P77_OUTPUT_LEV   	0

//</h>
/******************************************resigter value**********************************************/

#define P0CR_INIT         (P07_WORK_MODE|P06_WORK_MODE|P05_WORK_MODE|P04_WORK_MODE|P03_WORK_MODE|P02_WORK_MODE|P01_WORK_MODE|P00_WORK_MODE)
#define P0PCR_INIT        (P07_INPUT_PULL|P06_INPUT_PULL|P05_INPUT_PULL|P04_INPUT_PULL|P03_INPUT_PULL|P02_INPUT_PULL|P01_INPUT_PULL|P00_INPUT_PULL)
#define P0_OUTPUT_LEVEL   (P07_OUTPUT_LEV|P06_OUTPUT_LEV|P05_OUTPUT_LEV|P04_OUTPUT_LEV|P03_OUTPUT_LEV|P02_OUTPUT_LEV|P01_OUTPUT_LEV|P00_OUTPUT_LEV)

#define P1CR_INIT         (P15_WORK_MODE|P14_WORK_MODE|P13_WORK_MODE|P12_WORK_MODE|P11_WORK_MODE|P10_WORK_MODE)
#define P1PCR_INIT        (P15_INPUT_PULL|P14_INPUT_PULL|P13_INPUT_PULL|P12_INPUT_PULL|P11_INPUT_PULL|P10_INPUT_PULL)
#define P1_OUTPUT_LEVEL   (P15_OUTPUT_LEV|P14_OUTPUT_LEV|P13_OUTPUT_LEV|P12_OUTPUT_LEV|P11_OUTPUT_LEV|P10_OUTPUT_LEV)

#define P2CR_INIT         (P25_WORK_MODE|P24_WORK_MODE|P23_WORK_MODE|P22_WORK_MODE|P21_WORK_MODE|P20_WORK_MODE)
#define P2PCR_INIT        (P25_INPUT_PULL|P24_INPUT_PULL|P23_INPUT_PULL|P22_INPUT_PULL|P21_INPUT_PULL|P20_INPUT_PULL)
#define P2_OUTPUT_LEVEL   (P25_OUTPUT_LEV|P24_OUTPUT_LEV|P23_OUTPUT_LEV|P22_OUTPUT_LEV|P21_OUTPUT_LEV|P20_OUTPUT_LEV)

#define P3CR_INIT         (P35_WORK_MODE|P34_WORK_MODE|P33_WORK_MODE|P32_WORK_MODE|P31_WORK_MODE|P30_WORK_MODE)
#define P3PCR_INIT        (P35_INPUT_PULL|P34_INPUT_PULL|P33_INPUT_PULL|P32_INPUT_PULL|P31_INPUT_PULL|P30_INPUT_PULL)
#define P3_OUTPUT_LEVEL   (P35_OUTPUT_LEV|P34_OUTPUT_LEV|P33_OUTPUT_LEV|P32_OUTPUT_LEV|P31_OUTPUT_LEV|P30_OUTPUT_LEV)

#define P4CR_INIT         (P47_WORK_MODE|P46_WORK_MODE|P45_WORK_MODE|P44_WORK_MODE|P43_WORK_MODE|P42_WORK_MODE|P41_WORK_MODE|P40_WORK_MODE)
#define P4PCR_INIT        (P47_INPUT_PULL|P46_INPUT_PULL|P45_INPUT_PULL|P44_INPUT_PULL|P43_INPUT_PULL|P42_INPUT_PULL|P41_INPUT_PULL|P40_INPUT_PULL)
#define P4_OUTPUT_LEVEL   (P47_OUTPUT_LEV|P46_OUTPUT_LEV|P45_OUTPUT_LEV|P44_OUTPUT_LEV|P43_OUTPUT_LEV|P42_OUTPUT_LEV|P41_OUTPUT_LEV|P40_OUTPUT_LEV)

#define P5CR_INIT         (P57_WORK_MODE|P56_WORK_MODE|P55_WORK_MODE|P54_WORK_MODE|P53_WORK_MODE|P52_WORK_MODE|P51_WORK_MODE|P50_WORK_MODE)
#define P5PCR_INIT        (P57_INPUT_PULL|P56_INPUT_PULL|P55_INPUT_PULL|P54_INPUT_PULL|P53_INPUT_PULL|P52_INPUT_PULL|P51_INPUT_PULL|P50_INPUT_PULL)
#define P5_OUTPUT_LEVEL   (P57_OUTPUT_LEV|P56_OUTPUT_LEV|P55_OUTPUT_LEV|P54_OUTPUT_LEV|P53_OUTPUT_LEV|P52_OUTPUT_LEV|P51_OUTPUT_LEV|P50_OUTPUT_LEV)

#define P6CR_INIT         (P67_WORK_MODE|P66_WORK_MODE|P65_WORK_MODE|P64_WORK_MODE|P63_WORK_MODE|P62_WORK_MODE|P61_WORK_MODE|P60_WORK_MODE)
#define P6PCR_INIT        (P67_INPUT_PULL|P66_INPUT_PULL|P65_INPUT_PULL|P64_INPUT_PULL|P63_INPUT_PULL|P62_INPUT_PULL|P61_INPUT_PULL|P60_INPUT_PULL)
#define P6_OUTPUT_LEVEL   (P67_OUTPUT_LEV|P66_OUTPUT_LEV|P65_OUTPUT_LEV|P64_OUTPUT_LEV|P63_OUTPUT_LEV|P62_OUTPUT_LEV|P61_OUTPUT_LEV|P60_OUTPUT_LEV)

#define P7CR_INIT         (P77_WORK_MODE|P76_WORK_MODE|P75_WORK_MODE|P74_WORK_MODE|P73_WORK_MODE|P72_WORK_MODE|P71_WORK_MODE|P70_WORK_MODE)
#define P7PCR_INIT        (P77_INPUT_PULL|P76_INPUT_PULL|P75_INPUT_PULL|P74_INPUT_PULL|P73_INPUT_PULL|P72_INPUT_PULL|P71_INPUT_PULL|P70_INPUT_PULL)
#define P7_OUTPUT_LEVEL   (P77_OUTPUT_LEV|P76_OUTPUT_LEV|P75_OUTPUT_LEV|P74_OUTPUT_LEV|P73_OUTPUT_LEV|P72_OUTPUT_LEV|P71_OUTPUT_LEV|P70_OUTPUT_LEV)


#define P1_DRIVING_JUDGE  (P1_DRIVING_ENABLE)
#define P2_DRIVING_JUDGE  (P2_DRIVING_ENABLE)
#define P3_DRIVING_JUDGE  (P3_DRIVING_ENABLE)
#define P5_DRIVING_JUDGE  (P5_DRIVING_ENABLE)

#if    (P1_DRIVING_JUDGE == 1)
    #define P_DRV_EN      0X05
#elif  (P2_DRIVING_JUDGE == 1)       
    #define P_DRV_EN      0X45
#elif  (P3_DRIVING_JUDGE == 1)       
    #define P_DRV_EN      0X85
#elif  (P5_DRIVING_JUDGE == 1)       
    #define P_DRV_EN      0XC5
#else
		#define P_DRV_EN      0x00
#endif

#define DRVCON_INIT				(P_DRV_EN)
#define P1DRV_INIT        (P1_DRIVING_LEV)
#define P2DRV_INIT        (P2_DRIVING_LEV)
#define P3DRV_INIT        (P3_DRIVING_LEV)
#define P5DRV_INIT        (P5_DRIVING_LEV)
/**************************************************************************************************************/
//=============================================================================================================
//PWM
#define PWM0_MODE_ENABLE_BIT	0x80	//128
#define PWM0_INT_ENABLE_BIT         	0
#define PWM0PERD_16BIT_VAL          	1080	//1250//		1275//2560	//	3840//3600
#define PWM0CLK_DIV                 		2

#define PWM00MOD_BIT                	0
#define PWM00SS                    	 		8
#define PWM00DUTY1_16BIT_VAL        53
#define PWM00DUTY2_16BIT_VAL        53	

#define PWM01MOD_BIT                	0
#define PWM01SS                     			8
#define PWM01DUTY1_16BIT_VAL        54
#define PWM01DUTY2_16BIT_VAL        54	

#define PWM02MOD_BIT               		0
#define PWM02SS                     			8
#define PWM02DUTY1_16BIT_VAL        55
#define PWM02DUTY2_16BIT_VAL        55	

#define PWM03MOD_BIT                	0
#define PWM03SS                     			8
#define PWM03DUTY1_16BIT_VAL        50
#define PWM03DUTY2_16BIT_VAL        50	

#define PWM04MOD_BIT                	0
#define PWM04SS                    	 		8
#define PWM04DUTY1_16BIT_VAL        51
#define PWM04DUTY2_16BIT_VAL       51	

#define PWM05MOD_BIT                	0
#define PWM05SS                     			8
#define PWM05DUTY1_16BIT_VAL        52
#define PWM05DUTY2_16BIT_VAL        52	
//********************************************
#define PWM1_MODE_ENABLE_BIT	128
#define PWM1_INT_ENABLE_BIT         	0
#define PWM1PERD_16BIT_VAL          	1080	//1250//		1275//2560	//	3840//3600
#define PWM1CLK_DIV                 		2

#define PWM10MOD_BIT                	0
#define PWM10SS                     			8
#define PWM10DUTY1_16BIT_VAL        44
#define PWM10DUTY2_16BIT_VAL        44

#define PWM11MOD_BIT                	0
#define PWM11SS                     			8
#define PWM11DUTY1_16BIT_VAL        45
#define PWM11DUTY2_16BIT_VAL        45

#define PWM12MOD_BIT               	 	0
#define PWM12SS                     			8
#define PWM12DUTY1_16BIT_VAL        46
#define PWM12DUTY2_16BIT_VAL        46

#define PWM13MOD_BIT                	0
#define PWM13SS                     			8
#define PWM13DUTY1_16BIT_VAL        47
#define PWM13DUTY2_16BIT_VAL       47

#define PWM14MOD_BIT                	0
#define PWM14SS                     			8
#define PWM14DUTY1_16BIT_VAL        48
#define PWM14DUTY2_16BIT_VAL        48

#define PWM15MOD_BIT                	0
#define PWM15SS                     			8
#define PWM15DUTY1_16BIT_VAL        49
#define PWM15DUTY2_16BIT_VAL        49

//******************************************
#define PWM2_MODE_ENABLE_BIT	128
#define PWM2_INT_ENABLE_BIT         	0
#define PWM2PERD_16BIT_VAL          	1080	
#define PWM2CLK_DIV                 		2

#define PWM20MOD_BIT                	0
#define PWM20SS                     			8
#define PWM20DUTY1_16BIT_VAL      	 38
#define PWM20DUTY2_16BIT_VAL     	  38

#define PWM21MOD_BIT                	0
#define PWM21SS                     			8
#define PWM21DUTY1_16BIT_VAL      	 39
#define PWM21DUTY2_16BIT_VAL      	  39

#define PWM22MOD_BIT                	0
#define PWM22SS                     			8
#define PWM22DUTY1_16BIT_VAL     	 40
#define PWM22DUTY2_16BIT_VAL        40

#define PWM23MOD_BIT                	0
#define PWM23SS                     			8
#define PWM23DUTY1_16BIT_VAL     	  41
#define PWM23DUTY2_16BIT_VAL      	  41

#define PWM24MOD_BIT                	0
#define PWM24SS                     			8
#define PWM24DUTY1_16BIT_VAL       42
#define PWM24DUTY2_16BIT_VAL      	42

#define PWM25MOD_BIT                	0
#define PWM25SS                     			8
#define PWM25DUTY1_16BIT_VAL    	  43
#define PWM25DUTY2_16BIT_VAL        43
//----------------------------------------------------------

#define PWM3_MODE_ENABLE_BIT	0
#define PWM3_INT_ENABLE_BIT         	0
#define PWM3PERD_16BIT_VAL          	1080	//1250//		1275//2560	//	3840//	3600	//3825	//	3600
#define PWM3CLK_DIV                 		2

#define PWM30MOD_BIT               		0
#define PWM30SS                     			8
#define PWM30DUTY1_16BIT_VAL        0
#define PWM30DUTY2_16BIT_VAL        0

#define PWM31MOD_BIT                	0
#define PWM31SS                     			8
#define PWM31DUTY1_16BIT_VAL        0
#define PWM31DUTY2_16BIT_VAL        0

#define PWM32MOD_BIT                	0
#define PWM32SS                     			8
#define PWM32DUTY1_16BIT_VAL        0
#define PWM32DUTY2_16BIT_VAL        0

#define PWM33MOD_BIT                	0
#define PWM33SS                     			8
#define PWM33DUTY1_16BIT_VAL        0
#define PWM33DUTY2_16BIT_VAL        0

#define PWM4_MODE_ENABLE_BIT	0
#define PWM4_INT_ENABLE_BIT         	0
#define PWM4PERD_16BIT_VAL          	1080	//1250//		1275//2560	//	3840//3600
#define PWM4CLK_DIV                 		2
//

////

//////

//      <e0.7>PWM2: PWM2 mode enable bit


//////


//      <e0.7>PWM3: PWM3 mode enable bit
//////


///////////////////////////////////////////////////////////

//////
#define PWM40MOD_BIT                	0
#define PWM40SS                     			0
#define PWM40DUTY1_16BIT_VAL        0
#define PWM40DUTY2_16BIT_VAL        3000

#define PWM41MOD_BIT                	0
#define PWM41SS                     			0
#define PWM41DUTY1_16BIT_VAL        0
#define PWM41DUTY2_16BIT_VAL        3000

#define PWM42MOD_BIT                	0
#define PWM42SS                    		 	0
#define PWM42DUTY1_16BIT_VAL        0
#define PWM42DUTY2_16BIT_VAL        3000

#define PWM43MOD_BIT                	0
#define PWM43SS                   			0
#define PWM43DUTY1_16BIT_VAL        0
#define PWM43DUTY2_16BIT_VAL        0

/******************************************resigter value**********************************************/
/////////////////////PWM0///////////////////////////////////
#define PWM00CON_INIT        (PWM0_MODE_ENABLE_BIT|PWM0_INT_ENABLE_BIT|PWM00MOD_BIT|PWM00SS|PWM0CLK_DIV)
#define PWM01CON_INIT        (PWM01MOD_BIT|PWM01SS)
#define PWM02CON_INIT        (PWM02MOD_BIT|PWM02SS)
#define PWM03CON_INIT        (PWM03MOD_BIT|PWM03SS)
#define PWM04CON_INIT        (PWM04MOD_BIT|PWM04SS)
#define PWM05CON_INIT        (PWM05MOD_BIT|PWM05SS)
#define PWM0PERDH_INIT       ((U8)(PWM0PERD_16BIT_VAL>>8))
#define PWM0PERDL_INIT       ((U8)(PWM0PERD_16BIT_VAL))
//PWM00 DUTY
#define PWM00DUTY1H_INIT     ((U8)(PWM00DUTY1_16BIT_VAL>>8))
#define PWM00DUTY1L_INIT     ((U8)(PWM00DUTY1_16BIT_VAL))
#define PWM00DUTY2H_INIT     ((U8)(PWM00DUTY2_16BIT_VAL>>8))
#define PWM00DUTY2L_INIT     ((U8)(PWM00DUTY2_16BIT_VAL))
//PWM01 DUTY
#define PWM01DUTY1H_INIT     ((U8)(PWM01DUTY1_16BIT_VAL>>8))
#define PWM01DUTY1L_INIT     ((U8)(PWM01DUTY1_16BIT_VAL))
#define PWM01DUTY2H_INIT     ((U8)(PWM01DUTY2_16BIT_VAL>>8))
#define PWM01DUTY2L_INIT     ((U8)(PWM01DUTY2_16BIT_VAL))
//PWM02 DUTY
#define PWM02DUTY1H_INIT     ((U8)(PWM02DUTY1_16BIT_VAL>>8))
#define PWM02DUTY1L_INIT     ((U8)(PWM02DUTY1_16BIT_VAL))
#define PWM02DUTY2H_INIT     ((U8)(PWM02DUTY2_16BIT_VAL>>8))
#define PWM02DUTY2L_INIT     ((U8)(PWM02DUTY2_16BIT_VAL))
//PWM03 DUTY
#define PWM03DUTY1H_INIT     ((U8)(PWM03DUTY1_16BIT_VAL>>8))
#define PWM03DUTY1L_INIT     ((U8)(PWM03DUTY1_16BIT_VAL))
#define PWM03DUTY2H_INIT     ((U8)(PWM03DUTY2_16BIT_VAL>>8))
#define PWM03DUTY2L_INIT     ((U8)(PWM03DUTY2_16BIT_VAL))
//PWM04 DUTY
#define PWM04DUTY1H_INIT     ((U8)(PWM04DUTY1_16BIT_VAL>>8))
#define PWM04DUTY1L_INIT     ((U8)(PWM04DUTY1_16BIT_VAL))
#define PWM04DUTY2H_INIT     ((U8)(PWM04DUTY2_16BIT_VAL>>8))
#define PWM04DUTY2L_INIT     ((U8)(PWM04DUTY2_16BIT_VAL))
//PWM05 DUTY
#define PWM05DUTY1H_INIT     ((U8)(PWM05DUTY1_16BIT_VAL>>8))
#define PWM05DUTY1L_INIT     ((U8)(PWM05DUTY1_16BIT_VAL))
#define PWM05DUTY2H_INIT     ((U8)(PWM05DUTY2_16BIT_VAL>>8))
#define PWM05DUTY2L_INIT     ((U8)(PWM05DUTY2_16BIT_VAL))


/////////////////////PWM1///////////////////////////////////
#define PWM10CON_INIT        (PWM1_MODE_ENABLE_BIT|PWM1_INT_ENABLE_BIT|PWM10MOD_BIT|PWM10SS|PWM1CLK_DIV)
#define PWM11CON_INIT        (PWM11MOD_BIT|PWM11SS)
#define PWM12CON_INIT        (PWM12MOD_BIT|PWM12SS)
#define PWM13CON_INIT        (PWM13MOD_BIT|PWM13SS)
#define PWM14CON_INIT        (PWM14MOD_BIT|PWM14SS)
#define PWM15CON_INIT        (PWM15MOD_BIT|PWM15SS)
#define PWM1PERDH_INIT       ((U8)(PWM1PERD_16BIT_VAL>>8))
#define PWM1PERDL_INIT       ((U8)(PWM1PERD_16BIT_VAL))
//PWM10 DUTY
#define PWM10DUTY1H_INIT     ((U8)(PWM10DUTY1_16BIT_VAL>>8))
#define PWM10DUTY1L_INIT     ((U8)(PWM10DUTY1_16BIT_VAL))
#define PWM10DUTY2H_INIT     ((U8)(PWM10DUTY2_16BIT_VAL>>8))
#define PWM10DUTY2L_INIT     ((U8)(PWM10DUTY2_16BIT_VAL))
//PWM11 DUTY
#define PWM11DUTY1H_INIT     ((U8)(PWM11DUTY1_16BIT_VAL>>8))
#define PWM11DUTY1L_INIT     ((U8)(PWM11DUTY1_16BIT_VAL))
#define PWM11DUTY2H_INIT     ((U8)(PWM11DUTY2_16BIT_VAL>>8))
#define PWM11DUTY2L_INIT     ((U8)(PWM11DUTY2_16BIT_VAL))
//PWM12 DUTY
#define PWM12DUTY1H_INIT     ((U8)(PWM12DUTY1_16BIT_VAL>>8))
#define PWM12DUTY1L_INIT     ((U8)(PWM12DUTY1_16BIT_VAL))
#define PWM12DUTY2H_INIT     ((U8)(PWM12DUTY2_16BIT_VAL>>8))
#define PWM12DUTY2L_INIT     ((U8)(PWM12DUTY2_16BIT_VAL))
//PWM13 DUTY
#define PWM13DUTY1H_INIT     ((U8)(PWM13DUTY1_16BIT_VAL>>8))
#define PWM13DUTY1L_INIT     ((U8)(PWM13DUTY1_16BIT_VAL))
#define PWM13DUTY2H_INIT     ((U8)(PWM13DUTY2_16BIT_VAL>>8))
#define PWM13DUTY2L_INIT     ((U8)(PWM13DUTY2_16BIT_VAL))
//PWM14 DUTY
#define PWM14DUTY1H_INIT     ((U8)(PWM14DUTY1_16BIT_VAL>>8))
#define PWM14DUTY1L_INIT     ((U8)(PWM14DUTY1_16BIT_VAL))
#define PWM14DUTY2H_INIT     ((U8)(PWM14DUTY2_16BIT_VAL>>8))
#define PWM14DUTY2L_INIT     ((U8)(PWM14DUTY2_16BIT_VAL))
//PWM15 DUTY
#define PWM15DUTY1H_INIT     ((U8)(PWM15DUTY1_16BIT_VAL>>8))
#define PWM15DUTY1L_INIT     ((U8)(PWM15DUTY1_16BIT_VAL))
#define PWM15DUTY2H_INIT     ((U8)(PWM15DUTY2_16BIT_VAL>>8))
#define PWM15DUTY2L_INIT     ((U8)(PWM15DUTY2_16BIT_VAL))

/////////////////////PWM2///////////////////////////////////
#define PWM20CON_INIT        (PWM2_MODE_ENABLE_BIT|PWM2_INT_ENABLE_BIT|PWM20MOD_BIT|PWM20SS|PWM2CLK_DIV)
#define PWM21CON_INIT        (PWM21MOD_BIT|PWM21SS)
#define PWM22CON_INIT        (PWM22MOD_BIT|PWM22SS)
#define PWM23CON_INIT        (PWM23MOD_BIT|PWM23SS)
#define PWM24CON_INIT        (PWM24MOD_BIT|PWM24SS)
#define PWM25CON_INIT        (PWM25MOD_BIT|PWM25SS)
#define PWM2PERDH_INIT       ((U8)(PWM2PERD_16BIT_VAL>>8))
#define PWM2PERDL_INIT       ((U8)(PWM2PERD_16BIT_VAL))
//PWM20 DUTY
#define PWM20DUTY1H_INIT     ((U8)(PWM20DUTY1_16BIT_VAL>>8))
#define PWM20DUTY1L_INIT     ((U8)(PWM20DUTY1_16BIT_VAL))
#define PWM20DUTY2H_INIT     ((U8)(PWM20DUTY2_16BIT_VAL>>8))
#define PWM20DUTY2L_INIT     ((U8)(PWM20DUTY2_16BIT_VAL))
//PWM21 DUTY
#define PWM21DUTY1H_INIT     ((U8)(PWM21DUTY1_16BIT_VAL>>8))
#define PWM21DUTY1L_INIT     ((U8)(PWM21DUTY1_16BIT_VAL))
#define PWM21DUTY2H_INIT     ((U8)(PWM21DUTY2_16BIT_VAL>>8))
#define PWM21DUTY2L_INIT     ((U8)(PWM21DUTY2_16BIT_VAL))
//PWM22 DUTY
#define PWM22DUTY1H_INIT     ((U8)(PWM22DUTY1_16BIT_VAL>>8))
#define PWM22DUTY1L_INIT     ((U8)(PWM22DUTY1_16BIT_VAL))
#define PWM22DUTY2H_INIT     ((U8)(PWM22DUTY2_16BIT_VAL>>8))
#define PWM22DUTY2L_INIT     ((U8)(PWM22DUTY2_16BIT_VAL))
//PWM23 DUTY
#define PWM23DUTY1H_INIT     ((U8)(PWM23DUTY1_16BIT_VAL>>8))
#define PWM23DUTY1L_INIT     ((U8)(PWM23DUTY1_16BIT_VAL))
#define PWM23DUTY2H_INIT     ((U8)(PWM23DUTY2_16BIT_VAL>>8))
#define PWM23DUTY2L_INIT     ((U8)(PWM23DUTY2_16BIT_VAL))
//PWM24 DUTY
#define PWM24DUTY1H_INIT     ((U8)(PWM24DUTY1_16BIT_VAL>>8))
#define PWM24DUTY1L_INIT     ((U8)(PWM24DUTY1_16BIT_VAL))
#define PWM24DUTY2H_INIT     ((U8)(PWM24DUTY2_16BIT_VAL>>8))
#define PWM24DUTY2L_INIT     ((U8)(PWM24DUTY2_16BIT_VAL))
//PWM25 DUTY
#define PWM25DUTY1H_INIT     ((U8)(PWM25DUTY1_16BIT_VAL>>8))
#define PWM25DUTY1L_INIT     ((U8)(PWM25DUTY1_16BIT_VAL))
#define PWM25DUTY2H_INIT     ((U8)(PWM25DUTY2_16BIT_VAL>>8))
#define PWM25DUTY2L_INIT     ((U8)(PWM25DUTY2_16BIT_VAL))

/////////////////////PWM3///////////////////////////////////
#define PWM30CON_INIT        (PWM3_MODE_ENABLE_BIT|PWM3_INT_ENABLE_BIT|PWM30MOD_BIT|PWM30SS|PWM3CLK_DIV)
#define PWM31CON_INIT        (PWM31MOD_BIT|PWM31SS)
#define PWM32CON_INIT        (PWM32MOD_BIT|PWM32SS)
#define PWM33CON_INIT        (PWM33MOD_BIT|PWM33SS)
#define PWM3PERDH_INIT       ((U8)(PWM3PERD_16BIT_VAL>>8))
#define PWM3PERDL_INIT       ((U8)(PWM3PERD_16BIT_VAL))
//PWM30 DUTY
#define PWM30DUTY1H_INIT     ((U8)(PWM30DUTY1_16BIT_VAL>>8))
#define PWM30DUTY1L_INIT     ((U8)(PWM30DUTY1_16BIT_VAL))
#define PWM30DUTY2H_INIT     ((U8)(PWM30DUTY2_16BIT_VAL>>8))
#define PWM30DUTY2L_INIT     ((U8)(PWM30DUTY2_16BIT_VAL))
//PWM31 DUTY
#define PWM31DUTY1H_INIT     ((U8)(PWM31DUTY1_16BIT_VAL>>8))
#define PWM31DUTY1L_INIT     ((U8)(PWM31DUTY1_16BIT_VAL))
#define PWM31DUTY2H_INIT     ((U8)(PWM31DUTY2_16BIT_VAL>>8))
#define PWM31DUTY2L_INIT     ((U8)(PWM31DUTY2_16BIT_VAL))
//PWM32 DUTY
#define PWM32DUTY1H_INIT     ((U8)(PWM32DUTY1_16BIT_VAL>>8))
#define PWM32DUTY1L_INIT     ((U8)(PWM32DUTY1_16BIT_VAL))
#define PWM32DUTY2H_INIT     ((U8)(PWM32DUTY2_16BIT_VAL>>8))
#define PWM32DUTY2L_INIT     ((U8)(PWM32DUTY2_16BIT_VAL))
//PWM33 DUTY
#define PWM33DUTY1H_INIT     ((U8)(PWM33DUTY1_16BIT_VAL>>8))
#define PWM33DUTY1L_INIT     ((U8)(PWM33DUTY1_16BIT_VAL))
#define PWM33DUTY2H_INIT     ((U8)(PWM33DUTY2_16BIT_VAL>>8))
#define PWM33DUTY2L_INIT     ((U8)(PWM33DUTY2_16BIT_VAL))

/////////////////////PWM4///////////////////////////////////
#define PWM40CON_INIT        (PWM4_MODE_ENABLE_BIT|PWM4_INT_ENABLE_BIT|PWM40MOD_BIT|PWM40SS|PWM4CLK_DIV)
#define PWM41CON_INIT        (PWM41MOD_BIT|PWM41SS)
#define PWM42CON_INIT        (PWM42MOD_BIT|PWM42SS)
#define PWM4PERDH_INIT       ((U8)(PWM4PERD_16BIT_VAL>>8))
#define PWM4PERDL_INIT       ((U8)(PWM4PERD_16BIT_VAL))
//PWM40 DUTY
#define PWM40DUTY1H_INIT     ((U8)(PWM40DUTY1_16BIT_VAL>>8))
#define PWM40DUTY1L_INIT     ((U8)(PWM40DUTY1_16BIT_VAL))
#define PWM40DUTY2H_INIT     ((U8)(PWM40DUTY2_16BIT_VAL>>8))
#define PWM40DUTY2L_INIT     ((U8)(PWM40DUTY2_16BIT_VAL))
//PWM41 DUTY
#define PWM41DUTY1H_INIT     ((U8)(PWM41DUTY1_16BIT_VAL>>8))
#define PWM41DUTY1L_INIT     ((U8)(PWM41DUTY1_16BIT_VAL))
#define PWM41DUTY2H_INIT     ((U8)(PWM41DUTY2_16BIT_VAL>>8))
#define PWM41DUTY2L_INIT     ((U8)(PWM41DUTY2_16BIT_VAL))
//PWM42 DUTY
#define PWM42DUTY1H_INIT     ((U8)(PWM42DUTY1_16BIT_VAL>>8))
#define PWM42DUTY1L_INIT     ((U8)(PWM42DUTY1_16BIT_VAL))
#define PWM42DUTY2H_INIT     ((U8)(PWM42DUTY2_16BIT_VAL>>8))
#define PWM42DUTY2L_INIT     ((U8)(PWM42DUTY2_16BIT_VAL))

/***********************************************************************************************************/
//=============================================================================================================
//SPI
//=============================================================================================================

//<h>SPI  
//  <h>SPCON register  
//  <i>A2H    b7   b6   b5   b4   b3    b2   b1   b0
//  <i>SPCON  DIR MSTR CPHA CPOL SSDIS SPR2 SPR1 SPR0
//      <o0.7>DIR: spi transmit director select <0=>MSB <1=>LSB
//      <o0.6>MSTR: spi device select <0=>slave mode <1=>master mode
//      <o0.5>CPHA: clock phase control <0=>SCK first edge sample <1=>SCK second edge sample
//      <o0.4>CPOL: clock polarity control <0=>SCK low during idle <1=>SCK high during idle
//      <o0.3>SSDIS: ss pin control <0=>SS pin enable <1=>SS pin disable
//      <o0.0..2>SPR: clock rate select <0=>Fsys/4   <1=>Fsys/8 <2=>Fsys/16  <3=>Fsys/32 
//                                      <4=>Fsys/64 <5=>Fsys/128 <6=>Fsys/256 <7=>Fsys/512
//  </h>
//  <h>SPSTA register  
//  <i>F8H     b7   b6   b5   b4   b3  b2  b1  b0
//  <i>SPSTA  SPEN SPIF MODF WCOL RXOV --  --  --
//      <o1.7>SPEN: spi control <0=>spi off <1=>spi on
//  </h>
//</h>
/******************************************resigter value**********************************************/
#define     SPCON_INIT      0x00
#define     SPSTA_INIT      0x00
/********************************************************************************************/

//=============================================================================================================
//uart
//=============================================================================================================

//<h>uart  
//  <h>enter in the system clock
//  	 <o0>SYSCLK (KHz)                 <0-24000>
//  </h>
#define     SYSCLK_ENTER       0

//  <h>PCON register  
//  <i>87H   b7   b6    b5    b4  b3  b2  b1  b0
//  <i>PCON SMOD SSTAT SSTAT1 --  GF1 GF0 PD  IDL
//      <o0.7>SMOD: <0=>baudrate=1/64sysclk work as SM2  <1=>baudrate=1/32sysclk work as SM2
//      <o0.6>SSTAT: SCON[7:5] function select <0=>SCON[7:5]operate as SM0,SM1, SM2
//                                             <1=>SCON[7:5]operate as FE, RXOV,TXCOL
//  </h>
#define     PCON_TEMP       0x00

//  <h> SCON  
//  <i>98H  b7     b6       b5        b4  b3  b2  b1 b0
//  <i>SCON SM0/FE SM1/RXOV SM2/TXCOL REN TB8 RB8 TI RI
//      <o0> Uart baudrate: <0-256000>
//      <o1> Uart mode: <0=>mode0 8bit synchronous mode,Half duplex
//                       <1=>mode1 8bit variable baudrate asynchronous mode,full duplex
//                       <2=>mode2 9bit fixed baudrate asynchronous mode,full duplex
//                       <3=>mode3 9bit variable baudrate asynchronous mode,full duplex
//      <q2> Uart receive enable
//      <q3> Uart self-baudrate generator enable
//  </h>
#define     UART_BPS       0
#define     UART_MODE      0
#define     UART_RB_EN     0
#define     UART_SBRT_EN   0

//  <h>slave address register  
//  <i>EUART slave address and check(SADDR register)
//      <o0>slave address: <0x00-0xFF>
//      <h>SADEN register  
//      <i>check the address of slave
//          <q1.7>check the bit7 of slave address
//          <q1.6>check the bit6 of slave address
//          <q1.5>check the bit5 of slave address
//          <q1.4>check the bit4 of slave address
//          <q1.3>check the bit3 of slave address
//          <q1.2>check the bit2 of slave address
//          <q1.1>check the bit1 of slave address
//          <q1.0>check the bit0 of slave address
//      </h>
//  </h>
#define     SADDR_TEMP     0x00
#define     SADEN_TEMP     0x00
//</h>
/******************************************resigter value**********************************************/
#if ( UART_MODE == 1 || UART_MODE == 3)
    #define     SBRT_S          (0x8000-SYSCLK_ENTER*1000/16/UART_BPS)
    #define     SFINE_S         (SYSCLK_ENTER*1000/UART_BPS - 16*SBRT_S)
#else
    #define     SBRT_S          0
    #define     SFINE_S         0
#endif

#define     PCON_INIT      (PCON_TEMP)
#define     SCON_INIT      ((UART_MODE << 6) | (UART_RB_EN << 4))

#define     SBRT_INIT      ((UART_SBRT_EN<<15)|SBRT_S)
#define     SFINE_INIT      (SFINE_S)
#define     SADDR_INIT     (SADDR_TEMP)
#define     SADEN_INIT     (SADEN_TEMP)
/********************************************************************************************/
//=============================================================================================================
//WDT
//=============================================================================================================

//<h>WDT  
//<i>B1H        b7   b6 b5   b4   b3   b2   b1   b0
//<i>RSTSTAT    WDOF -  PORF LVRF CLRF WDT2 WDT1 WDT0
//  <o>WDT overflow period <0=>1024ms <1=>1024ms <2=>256ms <3=>128ms
//                         <4=>64ms   <5=>16ms   <6=>4ms   <7=>1ms
//</h>
//------------------------------------------------------------------------------
/******************************************resigter value**********************************************/

#define     WDT_INIT            0
#define     CLR_WDT()           (RSTSTAT = WDT_INIT)
#define     CLRWDT()           (RSTSTAT = WDT_INIT)
/********************************************************************************************/

/********************************************************************************************/
//=============================================================================================================
//LPD
//=============================================================================================================
//<h>LPD

//  <h>LPDCON 
//      <q0.7>check the bit7 of slave address
//      <o1.3>LPDMD   <0=> Vdd is greater than LPD_Vef => LPDIF=1      <1=>Vdd is less than LPD_Vef => LPDIF=1

//  </h>

#define LPDEN_T         0
#define LPDMD_T         0

//  <h>LPDSEL 
//      <o.0..3>LPDMD:   <0=> LPD_Vef=2.40V        <1=> LPD_Vef=2.55V 
//                       <2=> LPD_Vef=2.70V        <3=> LPD_Vef=2.85V
//                       <4=> LPD_Vef=3.00V        <5=> LPD_Vef=3.15V
//                       <6=> LPD_Vef=3.30V        <7=> LPD_Vef=3.45V
//                       <8=> LPD_Vef=3.60V        <9=> LPD_Vef=3.75V
//                       <10=> LPD_Vef=3.90V       <11=> LPD_Vef=4.05V
//                       <12=> LPD_Vef=4.20V       <13=> LPD_Vef=4.35V
//                       <14=> LPD_Vef=4.50V       <15=> LPD_Vef=4.65V
//  </h>

#define LPDSEL_T         0
//</h>

/******************************************resigter value**********************************************/

#define     LPDCON_INIT         (LPDEN_T|LPDMD_T)
#define     LPDSEL_INIT         (LPDSEL_T)

/********************************************************************************************/
//=============================================================================================================
//Regulator 
//=============================================================================================================
//<h>3.3v LDO

//  <h>REGCON 
//      <q0>open 3.3v ldo
//  </h>

#define REGEN         0x01
//</h>

/******************************************resigter value**********************************************/

#define     REGCON_INIT         (REGEN)

/********************************************************************************************/

/********************************************************************************************/

//=============================================================================================================
//usb
//=============================================================================================================
//<h>USB

//  <h>USBCON 
//      <q0.7>enable usb mode
//      <q1.6>enable internal USB D+ pad 1.5K ohm pull-up
//      <q2.5>reset usb mode
//      <q3.2>enable internal USB D- pad 150K ohm pull-up
//      <q4.1>wake up device
//      <q5.0>enable suspend mode
//  </h>
#define ENUSB_S       128
#define SW1CON_S      64
#define SWRST_S       0
#define SW2CON_S      0
#define WKUP_S        0
#define GOSUSP_S      0
//  <h>USBIE1 
//      <q0.7>enable usb power on interrupt
//      <q0.6>enable usb SETUP over interrupt
//      <q0.4>enable usb SETUP tack interrupt
//      <q0.3>enable usb SOF tack interrupt
//      <q0.2>enable usb RESUME tack interrupt
//      <q0.1>enable usb SUSPEND tack interrupt
//      <q0.0>enable usb BUS RESET tack interrupt
//  </h>
#define USBIE1_TEMP      0x5F

//  <h>USBIE2 
//      <q0.6>enable usb endpoint2 out task interrupt
//      <q0.5>enable usb endpoint1 out task interrupt
//      <q0.4>enable usb endpoint0 out task interrupt
//      <q0.2>enable usb endpoint2 in task interrupt
//      <q0.1>enable usb endpoint1 in task interrupt
//      <q0.0>enable usb endpoint0 in task interrupt
//  </h>
#define USBIE2_TEMP      0x11

//  <h>USBADDR 
//      <i>check the address of slave
//          <q0.6>check the bit6 of usb address
//          <q0.5>check the bit5 of usb address
//          <q0.4>check the bit4 of usb address
//          <q0.3>check the bit3 of usb address
//          <q0.2>check the bit2 of usb address
//          <q0.1>check the bit1 of usb address
//          <q0.0>check the bit0 of usb address
//  </h>
#define USBADDR_TEMP       0X00
//</h>

/******************************************resigter value**********************************************/

#define     USBCON_INIT         (ENUSB_S|SW1CON_S|SWRST_S|SW2CON_S|WKUP_S|GOSUSP_S)
#define     USBADDR_INIT        (USBADDR_TEMP)
#define     USBIE1_INIT         (USBIE1_TEMP)
#define     USBIE2_INIT         (USBIE2_TEMP)
/********************************************************************************************/
//*** <<< end of configuration section >>>    ***
