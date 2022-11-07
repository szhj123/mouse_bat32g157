#ifndef _APP_MOUSE_H
#define _APP_MOUSE_H

#include "drv_inter_flash.h"

typedef struct _usb_ctrl_setup_t
{
    uint8_t bmRequestType;
    uint8_t bRequest;
    uint8_t wValue_l;
    uint8_t wValue_h;
    uint8_t wIndex_l;
    uint8_t wIndex_h;
    uint8_t wLength_l;
    uint8_t wLength_h;
}usb_ctrl_setup_t;

typedef struct _key_val_t
{
    uint8_t keyType;
    uint8_t keyFunc;
    uint8_t keyVal_l;
    uint8_t keyVal_h;
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
    uint8_t rgbMode;
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

typedef struct _date_t
{
    uint8_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t min;
    uint8_t sec;
    uint8_t workDay;   
}date_t;


typedef struct _key_mode_t
{
    uint8_t reportId;
    uint8_t isDateFlag;
    uint8_t keyMode;
    date_t  date;
}key_mode_t;

typedef struct _rgb_para_t
{
    uint8_t brightness;
    uint8_t speed;
    uint8_t direction;
    uint8_t colorRandom;
    uint8_t colorNum;
    light_color_t colorBuf[7];
}rgb_para_t;

typedef struct _light_effect_t
{
    uint8_t reportId;
    uint8_t rgbMode;
    rgb_para_t rgbPara;
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


typedef struct _mouse_para_t
{
    uint8_t       keyMode;
    
    key_val_t     keyMode_1_Buf[15];
    key_val_t     keyMode_2_Buf[15];
    key_val_t     keyMode_3_Buf[15];

    uint8_t       picIndex;
    uint8_t       reportRate;
    uint8_t       sensorID;
    
    uint8_t       rgbMode;
    rgb_para_t    rgbParaBuf[10];
    
    uint8_t       dpiIndex;
    uint8_t       dpiNum;
    uint8_t       dpiXbuf[16];
    
    light_color_t dpiColorBuf[8];

    date_t        date;
}mouse_para_t;

void App_Mouse_Init(void );
void App_Mouse_Key_Mode_1_Init(void );
void App_Mouse_Key_Mode_2_Init(void );
void App_Mouse_Key_Mode_3_Init(void );
void App_Mouse_Dpi_Init(void );
void App_Mouse_Light_Init(void );
void App_Mouse_Para_Read(void );
void App_Mouse_Para_Save(void );

void App_Mouse_Set_Key_Mode(uint8_t *buf, uint8_t length );
void App_Mouse_Set_Light_Effect(uint8_t *buf, uint8_t length );

void App_Mouse_Get_Light_Dpi_Rate(uint8_t *buf, uint8_t length );
void App_Mouse_Get_Key_Mode(uint8_t *buf, uint8_t length );


#endif 

