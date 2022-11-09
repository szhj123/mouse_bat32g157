/********************************************************
* @file       drv_light.c
* @author     szhj13
* @version    V1.0
* @date       2022-05-18
* @brief      the start address of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "drv_light.h"
/* Private typedef --------------------------------------*/
/* Private define ---------------------------------------*/
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
/* Private variables ------------------------------------*/

void Drv_Light_Init(void )
{
    Hal_Light_Gpio_Init();

    Hal_Light_Pwm_Init();

    Hal_Light_Pwm_Set_Duty(255, 0, 0);

    Hal_Light_Gpio_Clr(PORTA, PIN0);
    Hal_Light_Gpio_Clr(PORTA, PIN1);
    Hal_Light_Gpio_Clr(PORTA, PIN3);
    
    Hal_Light_Gpio_Clr(PORTA, PIN12);
    Hal_Light_Gpio_Clr(PORTA, PIN13);
    Hal_Light_Gpio_Clr(PORTA, PIN14);
}

void Drv_Light_Set_On(light_t light )
{
    Hal_Light_Pwm_Set_Duty(light.rVal, light.gVal, light.bVal);

    Hal_Light_Gpio_Clr(light.port, light.pin);
}

void Drv_Light_Set_All_On(uint8_t rVal, uint8_t gVal, uint8_t bVal )
{    
    Hal_Light_Pwm_Set_Duty(rVal, gVal, bVal);

    Hal_Light_Gpio_Clr(PORTA, PIN0);
    Hal_Light_Gpio_Clr(PORTA, PIN1);
    Hal_Light_Gpio_Clr(PORTA, PIN3);
    
    Hal_Light_Gpio_Clr(PORTA, PIN12);
    Hal_Light_Gpio_Clr(PORTA, PIN13);
    Hal_Light_Gpio_Clr(PORTA, PIN14);
}

void Drv_Light_Set_All_Off(void )
{
    Hal_Light_Gpio_Set(PORTA, PIN0);
    Hal_Light_Gpio_Set(PORTA, PIN1);
    Hal_Light_Gpio_Set(PORTA, PIN3);
    
    Hal_Light_Gpio_Set(PORTA, PIN12);
    Hal_Light_Gpio_Set(PORTA, PIN13);
    Hal_Light_Gpio_Set(PORTA, PIN14);
}

