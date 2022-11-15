#ifndef _APP_MOUSE_H
#define _APP_MOUSE_H

#include "drv_inter_flash.h"
#include "hal_bat32g157.h"

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

typedef enum _key_type_t
{
    KEY_TYPE_NULL = 0,
    KEY_TYPE_MOUSE,
    KEY_TYPE_KEYBOARD,
    KEY_TYPE_RESERVE1,
    KEY_TYPE_MULTIMEDIA,
    KEY_TYPE_DPI,
    KEY_TYPE_MACRO,
    KEY_TYPE_OTHER
}key_type_t;

typedef enum _key_mouse_func_t
{
    KEY_MOUSE_FUNC_LEFT   = 0xf0,
    KEY_MOUSE_FUNC_RIGHT  = 0xf1,
    KEY_MOUSE_FUNC_MIDDLE = 0xf2,
    KEY_MOUSE_FUNC_FRONT  = 0xf3,
    KEY_MOUSE_FUNC_BACK   = 0xf4
}key_mouse_func_t;

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
    key_val_t keyBuf[15];
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
    uint8_t picShowMask_l;
    uint8_t picShowMask_h;
    uint8_t picIndex;
    uint8_t reserve[6];
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

typedef struct _light_para_t
{
    uint8_t brightness;
    uint8_t speed;
    uint8_t direction;
    uint8_t colorRandom;
    uint8_t colorNum;
    light_color_t colorBuf[7];
}light_para_t;

typedef struct _light_effect_t
{
    uint8_t reportId;
    uint8_t lightMode;
    light_para_t lightPara;
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

    uint8_t       reportRate;
    uint8_t       sensorID;
    
    uint8_t       lightMode;
    light_para_t  lightParaBuf[10];
    
    uint8_t       dpiIndex;
    uint8_t       dpiNum;
    uint8_t       dpiXbuf[16];
    
    light_color_t dpiColorBuf[8];

    uint8_t       picShowMask_l;
    uint8_t       picShowMask_h;
    uint8_t       picIndex;

    date_t        date;
}mouse_para_t;

void App_Mouse_Init(void );
void App_Mouse_Key_Mode_1_Init(void );
void App_Mouse_Key_Mode_2_Init(void );
void App_Mouse_Key_Mode_3_Init(void );
void App_Mouse_Key_Default_Mode_Init(void );
void App_Mouse_Dpi_Init(void );
void App_Mouse_Light_Init(void );
void App_Mouse_Pic_Show_Init(void );

void App_Mouse_Para_Read(void );
void App_Mouse_Para_Save(void );

void App_Mouse_Set_Light_Dpi_Rate(uint8_t *buf, uint8_t length );
void App_Mouse_Set_Key_Mode(uint8_t *buf, uint8_t length );
void App_Mouse_Set_Light_Effect(uint8_t *buf, uint8_t length );
uint8_t App_Mouse_Get_Light_Mode(void );
void App_Mouse_Get_Light_Dpi_Rate(uint8_t *buf, uint8_t length );
void App_Mouse_Get_Key_Mode(uint8_t *buf, uint8_t length );

void App_Mouse_Set_Key_Value(uint8_t *buf, uint8_t length );

uint8_t App_Mouse_Get_Rainbow_Speed(void );
uint8_t App_Mouse_Get_Rainbow_Direction(void );

uint8_t App_Mouse_Get_Solid_On_Brightness(void );
light_color_t App_Mouse_Get_Solid_On_Color(void );

uint8_t App_Mouse_Get_Breah_Speed(void );
void App_Mouse_Get_Breath_Color(light_color_t *lightColor, uint8_t length );

uint8_t App_Mouse_Get_Neon_Speed(void );

void App_Mouse_Get_Flash_Color(light_color_t *lightColor, uint8_t length );

uint8_t App_Mouse_Get_Monochroma_Drag_Speed(void );
uint8_t App_Mouse_Get_Monochroma_Drag_Direction(void );
void App_Mouse_Get_Monochroma_Drag_Color(light_color_t *lightColor );

void App_Mouse_Get_Key_1(key_val_t *keyVal );
void App_Mouse_Get_Key_2(key_val_t *keyVal );
void App_Mouse_Get_Key_3(key_val_t *keyVal );
void App_Mouse_Get_Key_4(key_val_t *keyVal );
void App_Mouse_Get_Key_5(key_val_t *keyVal );
void App_Mouse_Get_Key_6(key_val_t *keyVal );
void App_Mouse_Get_Key_7(key_val_t *keyVal );
void App_Mouse_Get_Key_8(key_val_t *keyVal );
void App_Mouse_Get_Key_9(key_val_t *keyVal );

uint8_t App_Mouse_Get_Dpi_Num(void );
uint8_t App_Mouse_Get_Dpi_Index(void );
void App_Mouse_Set_Dpi_Index(uint8_t dpiIndex );
void App_Mouse_Get_Dpi_Color(uint8_t dpiIndex, light_color_t *dpiColor );

#endif 

