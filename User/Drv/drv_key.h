#ifndef _DRV_KEY_H
#define _DRV_KEY_H

#include "hal_key.h"

#define KEY_DOWN                 0x0100
#define KEY_DOUBLE               0x0200
#define KEY_LONG                 0x0400
#define KEY_CONT                 0x0800
#define KEY_UP                   0x1000


#define KEY_MOUSE_LEFT           0x0001
#define KEY_MOUSE_RIGHT          0x0002
#define KEY_MOUSE_MIDDLE         0x0003
#define KEY_MEDIA_FORWARD        0x0004
#define KEY_MEDIA_BACKWARD       0x0005
#define KEY_MEDIA_DPI_INC        0x0006
#define KEY_MEDIA_DPI_DEC        0x0007
#define KEY_MEDIA_FIRE           0x0008
#define KEY_MEDIA_REPORT_RATE    0x0009

#define KEY_NULL                 0x0000

#define KEY_QUEUE_MAX_NUM        16

#define KEY_SHORT_PRESS_TIME     25//ms
#define KEY_DOUBLE_PRESS_TIME    200//ms
#define KEY_LONG_PRESS_TIME      2000//ms
#define KEY_CONT_PRESS_TIME      50//ms


typedef enum _key_media_state_t
{
    KEY_MEDIA_INIT = 0,
    KEY_MEDIA_SHORT_PRESS,
    KEY_MEDIA_LONG_PRESS,
    KEY_MEDIA_CONT_PRESS,
    KEY_MEDIA_RELEASE
}key_media_state_t;

typedef struct _key_media_ctrl_block_t
{
    PORT_TypeDef port1;
    PIN_TypeDef  pin1;
    PORT_TypeDef port2;
    PIN_TypeDef  pin2;

    key_media_state_t state;

    uint8_t      isCompositeKey;
    uint8_t      isDoubleKey;
    uint8_t      shortPressNum;
    uint8_t      shortPressCnt;

    uint16_t     delayCnt;
    uint16_t     shortPressTime;
    uint16_t     longPressTime;
    
    uint16_t     name;
    
}key_media_ctrl_block_t;

typedef enum _key_mouse_state_t
{
    KEY_MOUSE_INIT = 0,
    KEY_MOUSE_PRESS,
    KEY_MOUSE_RELEASE
}key_mouse_state_t;

typedef struct _key_mouse_ctrl_block_t
{
    PORT_TypeDef port;
    PIN_TypeDef  pin;
    
    key_mouse_state_t state;

    uint16_t  name;
    uint16_t  delayCnt;
    uint16_t  shortPressTime;
    
}key_mouse_ctrl_block_t;

typedef struct _key_queue_t
{
    uint16_t vBuf[KEY_QUEUE_MAX_NUM];

    uint8_t  front;
    uint8_t  rear;
}key_queue_t;

void Drv_Key_Init(void );
void Drv_Key_Mouse_Detect(key_mouse_ctrl_block_t *key );
void Drv_Key_Media_Detect(key_media_ctrl_block_t *key );

void Drv_Key_Queue_Put(uint16_t keyVal );
uint16_t Drv_Key_Queue_Get(void );

#endif

