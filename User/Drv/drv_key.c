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
static uint16_t Drv_Key_Get_Media(key_media_ctrl_block_t *key );
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
                if(key->delayCnt >= key->shortPressTime)
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

void Drv_Key_Media_Detect(key_media_ctrl_block_t *key )
{
    static uint16_t keySave = KEY_NULL;
    uint16_t keyVal = KEY_NULL;
    
    if(key->delayCnt < 0xffff)
    {
        key->delayCnt++;
    }

    keyVal = Drv_Key_Get_Media(key);

    switch(key->state)
    {
        case KEY_MEDIA_INIT:
        {
            if(keyVal != NULL)
            {
                key->shortPressCnt = 0;
                
                key->delayCnt = 0;
                
                key->state = KEY_MEDIA_SHORT_PRESS;
            }
            break;
        }
        case KEY_MEDIA_SHORT_PRESS:
        {
            if(keyVal != NULL)
            {
                if(key->delayCnt > KEY_SHORT_PRESS_TIME)
                {
                    if(key->isDoubleKey)
                    {
                        key->shortPressCnt++;

                        if(key->shortPressCnt == 1)
                        {
                            keySave = keyVal;
                        }
                        else
                        {
                            if(keySave != keyVal)
                            {
                                keySave = keyVal;
                                
                                key->shortPressCnt = 1;
                            }
                        }
                    }
                    else
                    {
                        keySave = keyVal | KEY_DOWN;

                        Drv_Key_Queue_Put(keySave);
                    }

                    key->delayCnt = 0;

                    key->state = KEY_MEDIA_LONG_PRESS;
                }
            }
            else
            {
                if(key->isDoubleKey)
                {
                    if(key->delayCnt > KEY_DOUBLE_PRESS_TIME)
                    {
                        if(key->shortPressCnt == 1)
                        {
                            key->shortPressCnt = 0;

                            keySave |= KEY_DOWN | KEY_UP;

                            Drv_Key_Queue_Put(keySave);
                        }
                        else if(key->shortPressCnt == key->shortPressNum)
                        {
                            key->shortPressCnt = 0;
                            
                            keySave |= KEY_DOUBLE | KEY_UP;
                            
                            Drv_Key_Queue_Put(keySave);
                        }

                        key->state = KEY_MEDIA_INIT;
                    }
                }
                else
                {
                    key->state = KEY_MEDIA_INIT;
                }
            }
            break;
        }
        case KEY_MEDIA_LONG_PRESS:
        {
            if(keyVal != KEY_NULL)
            {
                if(key->delayCnt > KEY_LONG_PRESS_TIME)
                {
                    key->delayCnt = 0;

                    keySave = keyVal | KEY_LONG;
                    
                    Drv_Key_Queue_Put(keySave);

                    key->state = KEY_MEDIA_CONT_PRESS;
                }
            }
            else
            {
                key->delayCnt = 0;

                if(key->isDoubleKey)
                {
                    key->state = KEY_MEDIA_SHORT_PRESS;
                }
                else
                {
                    key->state = KEY_MEDIA_RELEASE;
                }
            }
            
            break;
        }
        case KEY_MEDIA_CONT_PRESS:
        {
            if(keyVal != KEY_NULL)
            {
                if(key->delayCnt > KEY_CONT_PRESS_TIME)
                {
                    key->delayCnt = 0;

                    keySave = keyVal | KEY_CONT;

                    Drv_Key_Queue_Put(keySave);
                }
            }
            else
            {
                key->state = KEY_MEDIA_RELEASE;
            }
            break;
        }
        case KEY_MEDIA_RELEASE:
        {
            keySave |= KEY_UP;

            Drv_Key_Queue_Put(keySave);

            key->state = KEY_MEDIA_INIT;
            
            break;
        }
        default: break;
    }
}

static uint16_t Drv_Key_Get_Media(key_media_ctrl_block_t *key )
{
    if(key->isCompositeKey)
    {
        if(Hal_Key_Get_Value(key->port1, key->pin1) == 0 && Hal_Key_Get_Value(key->port2, key->pin2) == 0)
        {
            return key->name;
        }
    }
    else
    {
        if(Hal_Key_Get_Value(key->port1, key->pin1) == 0)
        {
            return key->name;
        }
    }
    
    return KEY_NULL;
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

