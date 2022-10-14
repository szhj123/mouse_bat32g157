#ifndef _DRV_KEY_H
#define _DRV_KEY_H

#include "hal_key.h"

typedef struct _key_ctrl_block_t
{
    PORT_TypeDef port1;
    PIN_TypeDef  pin1;
    PORT_TypeDef port2;
    PIN_TypeDef  pin2;

    uint16_t     pressDelayCnt;
    uint16_t     pressShortTime;
    uint16_t     pressLongTime;

    uint8_t      
}

void Drv_Key_Init(void );

#endif

