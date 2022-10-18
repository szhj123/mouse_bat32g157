/********************************************************
* @file       drv_key.c
* @author     szhj13
* @version    V1.0
* @date       2022-05-18
* @brief      the start address of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "drv_key.h"
/* Private typedef --------------------------------------*/
/* Private define ---------------------------------------*/
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
/* Private variables ------------------------------------*/
key_queue_t keyQueue;

void Drv_Key_Init(void )
{
    Hal_Key_Init();
}

void Drv_Key_Mouse_Detect(key_mouse_ctrl_block_t *key )
{
    uint16_t keyVal = KEY_NULL;
    
    if(key->delayCnt < 0xffff)
    {
        key->delayCnt++;
    }

    switch(key->state)
    {
        case KEY_MOUSE_INIT:
        {
            if(Hal_Key_Get_Value(key->port, key->pin) == 0)
            {
                key->delayCnt = 0;
                
                key->state = KEY_MOUSE_PRESS;
            }

            break;
        }
        case KEY_MOUSE_PRESS:
        {
            if(Hal_Key_Get_Value(key->port, key->pin) == 0)
            {
                if(key->delayCnt >= 25)
                {
                    keyVal = key->name | KEY_DOWN;

                    Drv_Key_Queue_Put(keyVal);

                    key->state = KEY_MOUSE_RELEASE;
                }
            }
            else
            {
                key->state = KEY_MOUSE_INIT;
            }
            break;
        }
        case KEY_MOUSE_RELEASE:
        {
            if(Hal_Key_Get_Value(key->port, key->pin))
            {
                keyVal = key->name | KEY_UP;
                
                Drv_Key_Queue_Put(keyVal);

                key->state = KEY_MOUSE_INIT;
            }

            break;
        }
    }
}

void Drv_Key_Queue_Put(uint16_t keyVal )
{
    keyQueue.vBuf[keyQueue.rear] = keyVal;

    keyQueue.rear = (keyQueue.rear + 1) % KEY_QUEUE_MAX_NUM;
}

uint16_t Drv_Key_Queue_Get(void )
{
    uint16_t keyVal = KEY_NULL;
    
    if(keyQueue.front != keyQueue.rear)
    {
        keyVal = keyQueue.vBuf[keyQueue.front];

        keyQueue.front = (keyQueue.front + 1) % KEY_QUEUE_MAX_NUM;
    }

    return keyVal;
}

