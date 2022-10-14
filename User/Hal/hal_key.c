/********************************************************
* @file       hal_key.c
* @author     szhj13
* @version    V1.0
* @date       2022-05-18
* @brief      the start address of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "hal_key.h"
/* Private typedef --------------------------------------*/
/* Private define ---------------------------------------*/
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
/* Private variables ------------------------------------*/

void Hal_Key_Init(void )
{
    //pd14, input, key1
    PORT_Init(PORTD, PIN14, INPUT);
    //pd15, input, key2
    PORT_Init(PORTD, PIN15, INPUT);
    //pd02, input, key3
    PORT_Init(PORTD, PIN2, INPUT);
    //pd03, input, key4
    PORT_Init(PORTD, PIN3, INPUT);
    //pd04, input, key5
    PORT_Init(PORTD, PIN4, INPUT);
    //pd05, input, key6
    PORT_Init(PORTD, PIN5, INPUT);
    //pd06, input, key7
    PORT_Init(PORTD, PIN6, INPUT);
    //pd07, input, key8
    PORT_Init(PORTD, PIN7, INPUT);
    //pd08, input, key9
    PORT_Init(PORTD, PIN8, INPUT);
}

void Hal_Key_Get_Value(PORT_TypeDef port, PIN_TypeDef pin )
{
    return PORT_GetBit(port, pin);
}



