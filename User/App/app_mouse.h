#ifndef _APP_MOUSE_H
#define _APP_MOUSE_H

#include "hal_bat32g157.h"


typedef struct _key_val_t
{
    uint8_t keyType;
    uint8_t keyFunc;
    uint8_t keyVal_h;
    uint8_t keyVal_l;
}key_val_t;

typedef struct _key_data_t
{
    uint8_t   reportId;
    uint8_t   keyMode;
    key_val_t key[15];
    uint8_t   reserve[2];
}key_data_t;

typedef struct _light_color_t
{
    uint8_t rVal;
    uint8_t gVal;
    uint8_t bVal;
}light_color_t;

typedef struct _light_dpi_rate_t
{
    uint8_t reportId;
    uint8_t rate;
    uint8_t sensorId;
    uint8_t lightMode;
    uint8_t reserve0;
    uint8_t dpiIndex;
    uint8_t dpiNum;
    uint8_t dpiXBuf[16];
    uint8_t dpiColorBuf[24];
    uint8_t dipYBuf[8];
    uint8_t reserv1;
    uint8_t picShowMask_l;
    uint8_t picShowMask_h;
    uint8_t picIndex;
}light_dpi_rate_t;

typedef struct _key_mode_t
{
    uint8_t reportId;
    uint8_t isDateFlag;
    uint8_t keyMode;
    uint8_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t min;
    uint8_t sec;
    uint8_t workDay;
}key_mode_t;

typedef struct _light_effect_t
{
    uint8_t reportId;
    uint8_t lightMode;
    uint8_t brightness;
    uint8_t speed;
    uint8_t direction;
    uint8_t colorRandom;
    uint8_t colorNum;
    light_color_t colorBuf[7];
    uint8_t reserve[36];
}light_effect_t;

typedef struct _macro_data_t
{
    uint8_t reportId;
    uint8_t memoryId;
    uint8_t offsetAddr;
    uint8_t length;
    uint8_t buf[60];
}macroPara_Typedef;

#endif 

