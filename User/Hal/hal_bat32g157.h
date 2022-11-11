#ifndef _HAL_BAT32G157_H
#define _HAL_BAT32G157_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BAT32G157.h"
#include "userdefine.h"
#include "clk.h"
#include "gpio.h"
#include "usb.h"
#include "dma.h"
#include "spi.h"
#include "tim4.h"
#include "tim8.h"
#include "sci.h"
#include "flash.h"

#include "usb_pmsc_apl.h"

typedef union
{
    uint8_t val;

    struct 
    {
        uint8_t val_0:1;
        uint8_t val_1:1;
        uint8_t val_2:1;
        uint8_t val_3:1;
        uint8_t val_4:1;
        uint8_t val_5:1;
        uint8_t val_6:1;
        uint8_t val_7:1;
    }val_b;
}val_t;

typedef void (*hal_isr_callback_t)(void );

#endif 
