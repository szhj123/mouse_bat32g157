#ifndef		_PWM_CONTROL_H
#define	_PWM_CONTROL_H
///////////////////////enable led pwm output////////////////////////////////////////////////////
#define PWM00_ENABLE		(PWM00CON = 0xCA)//(PWM00CON |= 0X08)   
#define PWM01_ENABLE		(PWM01CON = 0x8A)
#define PWM02_ENABLE		(PWM02CON = 0x8A)
#define PWM03_ENABLE		(PWM03CON = 0x8A)
#define PWM04_ENABLE		(PWM04CON = 0x8A)
#define PWM05_ENABLE		(PWM05CON = 0x8A)
                      
#define PWM10_ENABLE		(PWM10CON = 0x8A)
#define PWM11_ENABLE		(PWM11CON = 0x8A)
#define PWM12_ENABLE		(PWM12CON = 0x8A)
#define PWM13_ENABLE		(PWM13CON = 0x8A)
#define PWM14_ENABLE		(PWM14CON = 0x8A)
#define PWM15_ENABLE		(PWM15CON = 0x8A)    
                     
#define PWM20_ENABLE		(PWM20CON = 0x8A)
#define PWM21_ENABLE		(PWM21CON = 0x8A)
#define PWM22_ENABLE		(PWM22CON = 0x8A)
#define PWM23_ENABLE		(PWM23CON = 0x8A)
#define PWM24_ENABLE		(PWM24CON = 0x8A)
#define PWM25_ENABLE		(PWM25CON = 0x8A)   
                      
#define PWM30_ENABLE		(PWM30CON = 0x02)
#define PWM31_ENABLE		(PWM31CON = 0x02)
#define PWM32_ENABLE		(PWM32CON = 0x02)
#define PWM33_ENABLE		(PWM33CON = 0x02)  

#define PWM40_ENABLE		(PWM40CON = 0x02)
#define PWM41_ENABLE		(PWM41CON = 0x02)
#define PWM42_ENABLE		(PWM42CON = 0x02)
///////////////////////disable led pwm output////////////////////////////////////////////////////
#define PWM00_DISABLE		(PWM00CON = 0x12)//(PWM00CON = 0xC2)//(PWM00CON &= (~0X08))
#define PWM01_DISABLE		(PWM01CON = 0x12)
#define PWM02_DISABLE		(PWM02CON = 0x12)
#define PWM03_DISABLE		(PWM03CON = 0x12)
#define PWM04_DISABLE		(PWM04CON = 0x12)
#define PWM05_DISABLE		(PWM05CON = 0x12)          
             
#define PWM10_DISABLE		(PWM10CON = 0x12)
#define PWM11_DISABLE		(PWM11CON = 0x12)
#define PWM12_DISABLE		(PWM12CON = 0x12)
#define PWM13_DISABLE		(PWM13CON = 0x12)
#define PWM14_DISABLE		(PWM14CON = 0x12)
#define PWM15_DISABLE		(PWM15CON = 0x12)      
               
#define PWM20_DISABLE		(PWM20CON = 0x12)
#define PWM21_DISABLE		(PWM21CON = 0x12)
#define PWM22_DISABLE		(PWM22CON = 0x12)
#define PWM23_DISABLE		(PWM23CON = 0x12)
#define PWM24_DISABLE		(PWM24CON = 0x12)
#define PWM25_DISABLE		(PWM25CON = 0x12)       
                 
#define PWM30_DISABLE		(PWM30CON = 0x02)
#define PWM31_DISABLE		(PWM31CON = 0x00)
#define PWM32_DISABLE		(PWM32CON = 0x00)
#define PWM33_DISABLE		(PWM33CON = 0x00)     
                 
#define PWM40_DISABLE		(PWM40CON = 0x02)
#define PWM41_DISABLE		(PWM41CON = 0x00)
#define PWM42_DISABLE		(PWM42CON = 0x00)
/*
#define CAPS_LED_ON	(P0_3=0)
#define NUM_LED_ON	(P0_4=0)
#define SCR_LED_ON		(P0_2=0)
#define WIN_LED_ON	(PWM30_ENABLE)

#define CAPS_LED_OFF	(P0_3=1)
#define NUM_LED_OFF	(P0_4=1)
#define SCR_LED_OFF	(P0_2=1)
#define WIN_LED_OFF	(PWM30_DISABLE)
*/
#endif
                                                                                                                                                                                                                                                                                                                                                                                                             