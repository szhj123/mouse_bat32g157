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
    PORT_Init(PORTD, PIN14, PULLUP_INPUT);
    //pd15, input, key2
    PORT_Init(PORTD, PIN15, PULLUP_INPUT);
    //pd02, input, key3
    PORT_Init(PORTD, PIN2, PULLUP_INPUT);
    //pd03, input, key4
    PORT_Init(PORTD, PIN3, PULLUP_INPUT);
    //pd04, input, key5
    PORT_Init(PORTD, PIN4, PULLUP_INPUT);
    //pd05, input, key6
    PORT_Init(PORTD, PIN5, PULLUP_INPUT);
    //pd06, input, key7
    PORT_Init(PORTD, PIN6, PULLUP_INPUT);
    //pd07, input, key8
    PORT_Init(PORTD, PIN7, PULLUP_INPUT);
    //pd08, input, key9
    PORT_Init(PORTD, PIN8, PULLUP_INPUT);
}

uint8_t Hal_Key_Get_Value(PORT_TypeDef port, PIN_TypeDef pin )
{
    if(PORT_GetBit(port, pin))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}



