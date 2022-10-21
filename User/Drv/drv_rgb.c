/********************************************************
* @file       drv_rgb.c
* @author     szhj13
* @version    V1.0
* @date       2022-05-18
* @brief      the start address of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "drv_rgb.h"
/* Private typedef --------------------------------------*/
/* Private define ---------------------------------------*/
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
/* Private variables ------------------------------------*/

void Drv_Rgb_Init(void )
{
    Hal_Rgb_Gpio_Init();

    Hal_Rgb_Pwm_Init();

    Hal_Rgb_Pwm_Set_Duty(255, 0, 0);

    Hal_Rgb_Gpio_Clr(PORTA, PIN0);
    Hal_Rgb_Gpio_Clr(PORTA, PIN1);
    Hal_Rgb_Gpio_Clr(PORTA, PIN3);
    
    Hal_Rgb_Gpio_Clr(PORTA, PIN12);
    Hal_Rgb_Gpio_Clr(PORTA, PIN13);
    Hal_Rgb_Gpio_Clr(PORTA, PIN14);
}

