/********************************************************
* @file       hal_rgb.c
* @author     szhj13
* @version    V1.0
* @date       2022-05-18
* @brief      the start address of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "hal_rgb.h"
/* Private typedef --------------------------------------*/
/* Private define ---------------------------------------*/
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
/* Private variables ------------------------------------*/

void Hal_Rgb_Gpio_Init(void )
{
    //pa00, rgb1 enable, output
    PORT_Init(PORTA, PIN0, OUTPUT);
    //pa01, rgb2 enable, output
    PORT_Init(PORTA, PIN1, OUTPUT);
    //pa03, rgb3 enable, output
    PORT_Init(PORTA, PIN3, OUTPUT);
    //pa12, rgb4 enable, output
    PORT_Init(PORTA, PIN12, OUTPUT);
    //pa13, rgb5 enable, output
    PORT_Init(PORTA, PIN13, OUTPUT);
    //pa14, rgb6 enable, output
    PORT_Init(PORTA, PIN14, OUTPUT);
}

void Hal_Rgb_Pwm_Init(void )
{
    CGC->PER0 |= CGC_PER0_TM40EN_Msk;    /* enables input clock supply */
    TM40->TPS0 = _0000_TM4_CKM3_fCLK_8 | _0000_TM4_CKM2_fCLK_1 | _0000_TM4_CKM1_fCLK_0 | _0000_TM4_CKM0_fCLK_0; 

    /* master channel */
    TM40->TMR00 = _0000_TM4_CLOCK_SELECT_CKM0 | _0000_TM4_TRIGGER_SOFTWARE | _0001_TM4_MODE_PWM_MASTER;
    TM40->TDR00 = period - 1;
    TM40->TO0  &= ~_0001_TM4_CH0_OUTPUT_VALUE_1;
    TM40->TOE0 &= ~_0001_TM4_CH0_OUTPUT_ENABLE;
    /* slave channel */
    TM40->TMR01 = _0000_TM4_CLOCK_SELECT_CKM0 | _0400_TM4_TRIGGER_MASTER_INT | _0009_TM4_MODE_PWM_SLAVE;
    TM40->TDR01 = duty1;
    TM40->TOM0 |=  _0002_TM4_CH1_SLAVE_OUTPUT;       /* slave channel output mode */
    TM40->TOL0 &= ~_0002_TM4_CH1_OUTPUT_LEVEL_L;     /* positive logic output (active-high) */
    TM40->TO0  &= ~_0002_TM4_CH1_OUTPUT_VALUE_1;     /* TOmp default output level */
    TM40->TOE0 |=  _0002_TM4_CH1_OUTPUT_ENABLE;      /* Enable TOmp output by counting operation */
    TO01_PORT_SETTING();
    /* slave channel */
    TM40->TMR02 = _0000_TM4_CLOCK_SELECT_CKM0 | _0400_TM4_TRIGGER_MASTER_INT | _0009_TM4_MODE_PWM_SLAVE;
    TM40->TDR02 = duty2;
    TM40->TOM0 |=  _0004_TM4_CH2_SLAVE_OUTPUT;       /* slave channel output mode */
    TM40->TOL0 &= ~_0004_TM4_CH2_OUTPUT_LEVEL_L;     /* positive logic output (active-high) */
    TM40->TO0  &= ~_0004_TM4_CH2_OUTPUT_VALUE_1;     /* TOmp default output level */
    TM40->TOE0 |=  _0004_TM4_CH2_OUTPUT_ENABLE;      /* Enable TOmp output by counting operation */
    TO02_PORT_SETTING();
    /* slave channel */
    TM40->TMR03 = _0000_TM4_CLOCK_SELECT_CKM0 | _0400_TM4_TRIGGER_MASTER_INT | _0009_TM4_MODE_PWM_SLAVE;
    TM40->TDR03 = duty3;
    TM40->TOM0 |=  _0008_TM4_CH3_SLAVE_OUTPUT;       /* slave channel output mode */
    TM40->TOL0 &= ~_0008_TM4_CH3_OUTPUT_LEVEL_L;     /* positive logic output (active-high) */
    TM40->TO0  &= ~_0008_TM4_CH3_OUTPUT_VALUE_1;     /* TOmp default output level */
    TM40->TOE0 |=  _0008_TM4_CH3_OUTPUT_ENABLE;      /* Enable TOmp output by counting operation */
    TO03_PORT_SETTING();
}
