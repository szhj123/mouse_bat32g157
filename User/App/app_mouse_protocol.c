/********************************************************
* @file       app_usb_protocol.c
* @author     szhj13
* @version    V1.0
* @date       2022-05-18
* @brief      the start address of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "app_mouse_protocol.h"
#include "usb_phid_apl.h"

/* Private typedef --------------------------------------*/
typedef enum
{
    PIC_FLASH_STATE_ERASE = 0,
    PIC_FLASH_STATE_WRITE
}pic_flash_state_t;

typedef struct _pic_ctrl_block_t
{
    uint16_t picTotalNum;
    uint32_t picMask;
    uint32_t picFlashAddr;
    uint32_t picRecvLength;
    uint8_t  timerId;

    pic_flash_state_t picFlashState;
}pic_ctrl_block_t;


/* Private define ---------------------------------------*/
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
/* Private variables ------------------------------------*/
static mouse_para_t mousePara;
static key_val_t    mouseKeyModeBuf[15] = {0};

static macro_key_val_t macroKeyBuf[128] = {0};
static uint8_t     macroKeyLength;

static usb_ctrl_setup_t usbCtrlSetup;
static uint8_t      usbCtrlSendBuf[64] = {0};
static uint8_t      usbCtrlSendLen; 

static pic_ctrl_block_t picCtrl;

static uint8_t picIdBuf[16];


void App_Mouse_Init(void )
{            
    App_Mouse_Para_Read();
    
    if(mousePara.keyMode > 3)
    {   
        mousePara.keyMode = 1;

        mousePara.reportRate = 4;

        mousePara.sensorID = 2;
        
        App_Mouse_Key_Mode_1_Init();

        App_Mouse_Key_Mode_2_Init();

        App_Mouse_Key_Mode_3_Init();

        App_Mouse_Dpi_Init();

        App_Mouse_Light_Init();

        App_Mouse_Pic_Show_Init();

        App_Mouse_Para_Save();
    }

    App_Mouse_Key_Default_Mode_Init();

    mousePara.date.year = 20;
    mousePara.date.month = 11;
    mousePara.date.day = 5;
    mousePara.date.hour = 0;
    mousePara.date.min = 0;
    mousePara.date.sec = 0;
    mousePara.date.workDay = 1;
}

void App_Mouse_Key_Mode_1_Init(void )
{
    mousePara.keyMode_1_Buf[0].keyType  = 0x01;
    mousePara.keyMode_1_Buf[0].keyFunc  = 0xf0;
    mousePara.keyMode_1_Buf[0].keyVal_l = 0;
    mousePara.keyMode_1_Buf[0].keyVal_h = 0;

    mousePara.keyMode_1_Buf[1].keyType  = 0x01;
    mousePara.keyMode_1_Buf[1].keyFunc  = 0xf1;
    mousePara.keyMode_1_Buf[1].keyVal_l = 0;
    mousePara.keyMode_1_Buf[1].keyVal_h = 0;

    mousePara.keyMode_1_Buf[2].keyType  = 0x01;
    mousePara.keyMode_1_Buf[2].keyFunc  = 0xf2;
    mousePara.keyMode_1_Buf[2].keyVal_l = 0;
    mousePara.keyMode_1_Buf[2].keyVal_h = 0;

    mousePara.keyMode_1_Buf[3].keyType  = 0x01;
    mousePara.keyMode_1_Buf[3].keyFunc  = 0xf3;
    mousePara.keyMode_1_Buf[3].keyVal_l = 0;
    mousePara.keyMode_1_Buf[3].keyVal_h = 0;

    mousePara.keyMode_1_Buf[4].keyType  = 0x01;
    mousePara.keyMode_1_Buf[4].keyFunc  = 0xf4;
    mousePara.keyMode_1_Buf[4].keyVal_l = 0;
    mousePara.keyMode_1_Buf[4].keyVal_h = 0;

    mousePara.keyMode_1_Buf[5].keyType  = 0x05;
    mousePara.keyMode_1_Buf[5].keyFunc  = 0x01;
    mousePara.keyMode_1_Buf[5].keyVal_l = 0;
    mousePara.keyMode_1_Buf[5].keyVal_h = 0;

    mousePara.keyMode_1_Buf[6].keyType  = 0x05;
    mousePara.keyMode_1_Buf[6].keyFunc  = 0x02;
    mousePara.keyMode_1_Buf[6].keyVal_l = 0;
    mousePara.keyMode_1_Buf[6].keyVal_h = 0;

    mousePara.keyMode_1_Buf[7].keyType  = 0x07;
    mousePara.keyMode_1_Buf[7].keyFunc  = 0x04;
    mousePara.keyMode_1_Buf[7].keyVal_l = 0;
    mousePara.keyMode_1_Buf[7].keyVal_h = 50;

    mousePara.keyMode_1_Buf[8].keyType  = 0x07;
    mousePara.keyMode_1_Buf[8].keyFunc  = 0x05;
    mousePara.keyMode_1_Buf[8].keyVal_l = 0;
    mousePara.keyMode_1_Buf[8].keyVal_h = 0;
}

void App_Mouse_Key_Mode_2_Init(void )
{
    mousePara.keyMode_2_Buf[0].keyType  = 0x01;
    mousePara.keyMode_2_Buf[0].keyFunc  = 0xf0;
    mousePara.keyMode_2_Buf[0].keyVal_l = 0;
    mousePara.keyMode_2_Buf[0].keyVal_h = 0;

    mousePara.keyMode_2_Buf[1].keyType  = 0x01;
    mousePara.keyMode_2_Buf[1].keyFunc  = 0xf1;
    mousePara.keyMode_2_Buf[1].keyVal_l = 0;
    mousePara.keyMode_2_Buf[1].keyVal_h = 0;

    mousePara.keyMode_2_Buf[2].keyType  = 0x01;
    mousePara.keyMode_2_Buf[2].keyFunc  = 0xf2;
    mousePara.keyMode_2_Buf[2].keyVal_l = 0;
    mousePara.keyMode_2_Buf[2].keyVal_h = 0;

    mousePara.keyMode_2_Buf[3].keyType  = 0x04;
    mousePara.keyMode_2_Buf[3].keyFunc  = 0x00;
    mousePara.keyMode_2_Buf[3].keyVal_l = 0xb6;
    mousePara.keyMode_2_Buf[3].keyVal_h = 0x00;

    mousePara.keyMode_2_Buf[4].keyType  = 0x04;
    mousePara.keyMode_2_Buf[4].keyFunc  = 0x00;
    mousePara.keyMode_2_Buf[4].keyVal_l = 0xb5;
    mousePara.keyMode_2_Buf[4].keyVal_h = 0;

    mousePara.keyMode_2_Buf[5].keyType  = 0x04;
    mousePara.keyMode_2_Buf[5].keyFunc  = 0x01;
    mousePara.keyMode_2_Buf[5].keyVal_l = 0xe9;
    mousePara.keyMode_2_Buf[5].keyVal_h = 0x00;

    mousePara.keyMode_2_Buf[6].keyType  = 0x04;
    mousePara.keyMode_2_Buf[6].keyFunc  = 0x00;
    mousePara.keyMode_2_Buf[6].keyVal_l = 0xea;
    mousePara.keyMode_2_Buf[6].keyVal_h = 0x00;

    mousePara.keyMode_2_Buf[7].keyType  = 0x04;
    mousePara.keyMode_2_Buf[7].keyFunc  = 0x00;
    mousePara.keyMode_2_Buf[7].keyVal_l = 0xcd;
    mousePara.keyMode_2_Buf[7].keyVal_h = 0x00;
}

void App_Mouse_Key_Mode_3_Init(void )
{
    mousePara.keyMode_3_Buf[0].keyType = 0x01;
    mousePara.keyMode_3_Buf[0].keyFunc = 0xf0;
    mousePara.keyMode_3_Buf[0].keyVal_l = 0;
    mousePara.keyMode_3_Buf[0].keyVal_h = 0;

    mousePara.keyMode_3_Buf[1].keyType = 0x01;
    mousePara.keyMode_3_Buf[1].keyFunc = 0xf1;
    mousePara.keyMode_3_Buf[1].keyVal_l = 0;
    mousePara.keyMode_3_Buf[1].keyVal_h = 0;

    mousePara.keyMode_3_Buf[2].keyType = 0x01;
    mousePara.keyMode_3_Buf[2].keyFunc = 0xf2;
    mousePara.keyMode_3_Buf[2].keyVal_l = 0;
    mousePara.keyMode_3_Buf[2].keyVal_h = 0;

    mousePara.keyMode_3_Buf[3].keyType = 0x01;
    mousePara.keyMode_3_Buf[3].keyFunc = 0xf3;
    mousePara.keyMode_3_Buf[3].keyVal_l = 0;
    mousePara.keyMode_3_Buf[3].keyVal_h = 0;

    mousePara.keyMode_3_Buf[4].keyType = 0x01;
    mousePara.keyMode_3_Buf[4].keyFunc = 0xf4;
    mousePara.keyMode_3_Buf[4].keyVal_l = 0;
    mousePara.keyMode_3_Buf[4].keyVal_h = 0;

    mousePara.keyMode_3_Buf[5].keyType = 0x05;
    mousePara.keyMode_3_Buf[5].keyFunc = 0x01;
    mousePara.keyMode_3_Buf[5].keyVal_l = 0;
    mousePara.keyMode_3_Buf[5].keyVal_h = 0;

    mousePara.keyMode_3_Buf[6].keyType = 0x05;
    mousePara.keyMode_3_Buf[6].keyFunc = 0x02;
    mousePara.keyMode_3_Buf[6].keyVal_l = 0;
    mousePara.keyMode_3_Buf[6].keyVal_h = 0;

    mousePara.keyMode_3_Buf[7].keyType = 0x07;
    mousePara.keyMode_3_Buf[7].keyFunc = 0x04;
    mousePara.keyMode_3_Buf[7].keyVal_l = 0;
    mousePara.keyMode_3_Buf[7].keyVal_h = 0;
}

void App_Mouse_Key_Default_Mode_Init(void )
{
    uint8_t i;
    
    for(i=0;i<15;i++)
    {
        if(mousePara.keyMode == 1)
        {
            mouseKeyModeBuf[i] = mousePara.keyMode_1_Buf[i];
        }
        else if(mousePara.keyMode == 2)
        {
            mouseKeyModeBuf[i] = mousePara.keyMode_2_Buf[i];
        }
        else if(mousePara.keyMode == 3)
        {
            mouseKeyModeBuf[i] = mousePara.keyMode_3_Buf[i];
        }
        else
        {
            mouseKeyModeBuf[i] = mousePara.keyMode_1_Buf[i];
        }
    }
}


void App_Mouse_Dpi_Init(void )
{
    uint8_t i;
    
    mousePara.dpiIndex = 1;
    
    mousePara.dpiNum = 6;

    mousePara.dpiXbuf[0] = 0x16;        //1000
    mousePara.dpiXbuf[1] = 0x2e;        //2000
    mousePara.dpiXbuf[2] = 0x45;        //3000
    mousePara.dpiXbuf[3] = 0x73;        //5000
    mousePara.dpiXbuf[4] = 0x50 | 0x80; //7000
    mousePara.dpiXbuf[5] = 0x73 | 0x80; //10000

    for(i=0;i<8;i++)
    {
        switch(i)
        {
            case 0: mousePara.dpiColorBuf[i].rVal = 0xff;mousePara.dpiColorBuf[i].gVal = 0x00;mousePara.dpiColorBuf[i].bVal = 0x00;break;
            case 1: mousePara.dpiColorBuf[i].rVal = 0x00;mousePara.dpiColorBuf[i].gVal = 0x00;mousePara.dpiColorBuf[i].bVal = 0xff;break;
            case 2: mousePara.dpiColorBuf[i].rVal = 0x00;mousePara.dpiColorBuf[i].gVal = 0xff;mousePara.dpiColorBuf[i].bVal = 0x00;break;
            case 3: mousePara.dpiColorBuf[i].rVal = 0x80;mousePara.dpiColorBuf[i].gVal = 0x00;mousePara.dpiColorBuf[i].bVal = 0xff;break;
            case 4: mousePara.dpiColorBuf[i].rVal = 0x00;mousePara.dpiColorBuf[i].gVal = 0xff;mousePara.dpiColorBuf[i].bVal = 0xff;break;
            case 5: mousePara.dpiColorBuf[i].rVal = 0xff;mousePara.dpiColorBuf[i].gVal = 0xff;mousePara.dpiColorBuf[i].bVal = 0x00;break;
            case 6: mousePara.dpiColorBuf[i].rVal = 0xff;mousePara.dpiColorBuf[i].gVal = 0xff;mousePara.dpiColorBuf[i].bVal = 0xff;break;
            case 7: mousePara.dpiColorBuf[i].rVal = 0xff;mousePara.dpiColorBuf[i].gVal = 0x80;mousePara.dpiColorBuf[i].bVal = 0x00;break;
            default: break;
        }
    }
}

void App_Mouse_Light_Init(void )
{
    uint8_t i,j;
    
    mousePara.lightMode = 1;

    for(i=0;i<10;i++)
    {
        mousePara.lightParaBuf[i].brightness = 2;
        mousePara.lightParaBuf[i].speed = 1;
        mousePara.lightParaBuf[i].direction = 1;
        mousePara.lightParaBuf[i].colorNum = 7;
        
        for(j=0;j<7;j++)
        {
            switch(j)
            {
                case 0: mousePara.lightParaBuf[i].colorBuf[j].rVal = 0xff;mousePara.lightParaBuf[i].colorBuf[j].gVal = 0x00;mousePara.lightParaBuf[i].colorBuf[j].bVal = 0x00;break;
                case 1: mousePara.lightParaBuf[i].colorBuf[j].rVal = 0x00;mousePara.lightParaBuf[i].colorBuf[j].gVal = 0x00;mousePara.lightParaBuf[i].colorBuf[j].bVal = 0xff;break;
                case 2: mousePara.lightParaBuf[i].colorBuf[j].rVal = 0x00;mousePara.lightParaBuf[i].colorBuf[j].gVal = 0xff;mousePara.lightParaBuf[i].colorBuf[j].bVal = 0x00;break;
                case 3: mousePara.lightParaBuf[i].colorBuf[j].rVal = 0x80;mousePara.lightParaBuf[i].colorBuf[j].gVal = 0x00;mousePara.lightParaBuf[i].colorBuf[j].bVal = 0xff;break;
                case 4: mousePara.lightParaBuf[i].colorBuf[j].rVal = 0x00;mousePara.lightParaBuf[i].colorBuf[j].gVal = 0xff;mousePara.lightParaBuf[i].colorBuf[j].bVal = 0xff;break;
                case 5: mousePara.lightParaBuf[i].colorBuf[j].rVal = 0xff;mousePara.lightParaBuf[i].colorBuf[j].gVal = 0xff;mousePara.lightParaBuf[i].colorBuf[j].bVal = 0x00;break;
                case 6: mousePara.lightParaBuf[i].colorBuf[j].rVal = 0xff;mousePara.lightParaBuf[i].colorBuf[j].gVal = 0xff;mousePara.lightParaBuf[i].colorBuf[j].bVal = 0xff;break;
                case 7: mousePara.lightParaBuf[i].colorBuf[j].rVal = 0xff;mousePara.lightParaBuf[i].colorBuf[j].gVal = 0x80;mousePara.lightParaBuf[i].colorBuf[j].bVal = 0x00;break;
                default: break;
            }
        }
            
    }
}

void App_Mouse_Pic_Show_Init(void )
{
    mousePara.picShowMask_l = 0xff;
    mousePara.picShowMask_h = 0xff;
    mousePara.picIndex = 0;
}

void App_Mouse_Set_Key_Value(uint8_t *buf, uint8_t length )
{
    uint8_t i;
    
    key_data_t keyData = *(key_data_t *)buf;

    for(i=0;i<15;i++)
    {
        if(keyData.keyMode == 0)
        {
            mousePara.keyMode_1_Buf[i] = keyData.keyBuf[i];
        }
        else if(keyData.keyMode == 1)
        {
            mousePara.keyMode_2_Buf[i] = keyData.keyBuf[i];
        }
        else if(keyData.keyMode == 3)
        {
            mousePara.keyMode_3_Buf[i] = keyData.keyBuf[i];
        }
    }
}

void App_Mouse_Set_Light_Dpi_Rate(uint8_t *buf, uint8_t length )
{
    uint8_t i;
    
    light_dpi_rate_t lightDpiRate = *(light_dpi_rate_t *)buf;
    
    mousePara.reportRate = lightDpiRate.rate;
    mousePara.sensorID = lightDpiRate.sensorId;
    mousePara.lightMode = lightDpiRate.lightMode;
    mousePara.dpiIndex = lightDpiRate.dpiIndex;
    mousePara.dpiNum = lightDpiRate.dpiNum;
    
    for(i=0;i<16;i++)
    {
        mousePara.dpiXbuf[i] = lightDpiRate.dpiXBuf[i];
    }

    for(i=0;i<24;i++)
    {
        *((uint8_t *)&mousePara.dpiColorBuf[0] + i) = lightDpiRate.dpiColorBuf[i];
    }

    mousePara.picShowMask_l = lightDpiRate.picShowMask_l;
    mousePara.picShowMask_h = lightDpiRate.picShowMask_h;
    mousePara.picIndex = lightDpiRate.picIndex;

    App_Mouse_Para_Save();
}

uint8_t App_Mouse_Get_Light_Mode(void )
{
    return mousePara.lightMode;
}

void App_Mouse_Set_Key_Mode(uint8_t *buf, uint8_t length )
{
    uint8_t i;

    uint8_t *datePtr = (uint8_t *)&mousePara.date;

    uint8_t isDateFlag = buf[1];

    if(buf[2] > 0 && buf[2] <= 3)
    {
        mousePara.keyMode = buf[2];
    }
    
    if((isDateFlag & 0x1) == 0x1)
    {       
        for(i=0;i<15;i++)
        {
            if(mousePara.keyMode == 1)
            {
                mouseKeyModeBuf[i] = mousePara.keyMode_1_Buf[i];
            }
            else if(mousePara.keyMode == 2)
            {
                mouseKeyModeBuf[i] = mousePara.keyMode_2_Buf[i];
            }
            else if(mousePara.keyMode == 3)
            {
                mouseKeyModeBuf[i] = mousePara.keyMode_3_Buf[i];
            }
            else
            {
                break;
            }
                
        }
    }
    else if((isDateFlag & 0x2) == 0x2)
    {
        for(i=0;i<sizeof(date_t);i++)
        {
            *datePtr++ = buf[3+i]; 
        }
    }

    App_Mouse_Para_Save();
}

void App_Mouse_Set_Light_Effect(uint8_t *buf, uint8_t length )
{
    light_effect_t lightEffect = *(light_effect_t *)buf;
    
    mousePara.lightMode = lightEffect.lightMode;

    mousePara.lightParaBuf[mousePara.lightMode] = lightEffect.lightPara;    
}

static void App_Mouse_Macro_Data_Save(void *arg )
{
    uint32_t macroId = (uint32_t )arg;
    uint32_t flashAddr;

    switch(macroId)
    {
        case 1: flashAddr = FLASH_MACRO1_START_ADDR; break;
        case 2: flashAddr = FLASH_MACRO2_START_ADDR; break;
        case 3: flashAddr = FLASH_MACRO3_START_ADDR; break;
        case 4: flashAddr = FLASH_MACRO4_START_ADDR; break;
        default: flashAddr = FLASH_MACRO1_START_ADDR; break;
    }
    
    Drv_Inter_Flash_Erase_Sector(flashAddr);

    Drv_Inter_Flash_Write(flashAddr, 1, &macroKeyLength);

    Drv_Inter_Flash_Write(flashAddr+1, macroKeyLength * sizeof(macro_key_val_t), (uint8_t *)macroKeyBuf);
}

void App_Mouse_Set_Macro(uint8_t *buf, uint8_t length )
{
    static uint8_t timerId = TIMER_NULL;
    uint16_t i;
    uint32_t flashAddr = 0;
    
    
    macro_para_t macroPara = *(macro_para_t *)buf;

    if(macroPara.macroId > 4)
    {
        macroPara.macroId = 4;
    }
    
    for(i=0;i<macroPara.length;i++)
    {
        *((uint8_t * )macroKeyBuf + macroPara.offsetAddr + i) = macroPara.buf[i];
    }

    macroKeyLength = (macroPara.offsetAddr + macroPara.length) / 3;

    Drv_Timer_Delete(timerId);

    timerId = Drv_Timer_Regist_Oneshot(50, App_Mouse_Macro_Data_Save, (void *)macroPara.macroId);
}

void App_Mouse_Get_Light_Dpi_Rate(uint8_t *buf, uint8_t length )
{
    uint8_t i;
    
    usbCtrlSetup = *(usb_ctrl_setup_t *)buf;

    usbCtrlSendLen = usbCtrlSetup.wLength_l; //usb request length
    
    usbCtrlSendBuf[0] = usbCtrlSetup.wValue_l; //report ID
    usbCtrlSendBuf[1] = mousePara.reportRate;
    usbCtrlSendBuf[2] = mousePara.sensorID;
    usbCtrlSendBuf[3] = mousePara.lightMode;
    usbCtrlSendBuf[4] = 0;
    usbCtrlSendBuf[5] = mousePara.dpiIndex;
    usbCtrlSendBuf[6] = mousePara.dpiNum;

    for(i=0;i<16;i++)
    {
        usbCtrlSendBuf[7+i] = mousePara.dpiXbuf[i];
    }

    for(i=0;i<24;i++)
    {
        usbCtrlSendBuf[23+i] = *((uint8_t *)&mousePara.dpiColorBuf[0] + i);
    }

    Usb_Ep0_In(usbCtrlSendBuf, usbCtrlSendLen);
}

void App_Mouse_Get_Key_Mode(uint8_t *buf, uint8_t length )
{
    usbCtrlSetup = *(usb_ctrl_setup_t *)buf;
    
    usbCtrlSendLen = usbCtrlSetup.wLength_l; //usb request length
    usbCtrlSendBuf[0] = usbCtrlSetup.wValue_l; //report ID
    usbCtrlSendBuf[1] = mousePara.keyMode;
    
    Usb_Ep0_In(usbCtrlSendBuf, usbCtrlSendLen);
}

void App_Mouse_Para_Read(void )
{
    Drv_Inter_Flash_Read(FLASH_MOUSE_START_ADDR, sizeof(mouse_para_t), (uint8_t *)&mousePara);
}

void App_Mouse_Para_Save(void )
{    
    Drv_Inter_Flash_Erase_Sector(FLASH_MOUSE_START_ADDR);

    Drv_Inter_Flash_Write(FLASH_MOUSE_START_ADDR, sizeof(mouse_para_t), (uint8_t *)&mousePara);
}

uint8_t App_Mouse_Get_Rainbow_Speed(void )
{
   return mousePara.lightParaBuf[1].speed;
}

uint8_t App_Mouse_Get_Rainbow_Direction(void )
{
   return mousePara.lightParaBuf[1].direction;
}

uint8_t App_Mouse_Get_Solid_On_Brightness(void )
{
    return mousePara.lightParaBuf[2].brightness;
}

light_color_t App_Mouse_Get_Solid_On_Color(void )
{
    return mousePara.lightParaBuf[2].colorBuf[0];
}

uint8_t App_Mouse_Get_Breah_Speed(void )
{
    return mousePara.lightParaBuf[3].speed;
}

void App_Mouse_Get_Breath_Color(light_color_t *lightColor, uint8_t length )
{
    uint8_t i;

    for(i=0;i<length;i++)
    {
        *lightColor++ = mousePara.lightParaBuf[3].colorBuf[i];
    }
}

uint8_t App_Mouse_Get_Neon_Speed(void )
{
    return mousePara.lightParaBuf[4].speed;
}

void App_Mouse_Get_Flash_Color(light_color_t *lightColor, uint8_t length )
{
    uint8_t i;

    for(i=0;i<length;i++)
    {
        *lightColor++ = mousePara.lightParaBuf[5].colorBuf[i];
    }
}

uint8_t App_Mouse_Get_Monochroma_Drag_Speed(void )
{
    return mousePara.lightParaBuf[6].speed;
}

uint8_t App_Mouse_Get_Monochroma_Drag_Direction(void )
{
    return mousePara.lightParaBuf[6].direction;
}

void App_Mouse_Get_Monochroma_Drag_Color(light_color_t *lightColor )
{
    *lightColor++ = mousePara.lightParaBuf[6].colorBuf[0];
}

void App_Mouse_Get_Key_1(key_val_t *keyVal )
{
    *keyVal = mouseKeyModeBuf[0];
}

void App_Mouse_Get_Key_2(key_val_t *keyVal )
{
    *keyVal = mouseKeyModeBuf[1];
}

void App_Mouse_Get_Key_3(key_val_t *keyVal )
{
    *keyVal = mouseKeyModeBuf[2];
}

void App_Mouse_Get_Key_4(key_val_t *keyVal )
{
    *keyVal = mouseKeyModeBuf[3];
}

void App_Mouse_Get_Key_5(key_val_t *keyVal )
{
    *keyVal = mouseKeyModeBuf[4];
}

void App_Mouse_Get_Key_6(key_val_t *keyVal )
{
    *keyVal = mouseKeyModeBuf[5];
}

void App_Mouse_Get_Key_7(key_val_t *keyVal )
{
    *keyVal = mouseKeyModeBuf[6];
}

void App_Mouse_Get_Key_8(key_val_t *keyVal )
{
    *keyVal = mouseKeyModeBuf[7];
}

void App_Mouse_Get_Key_9(key_val_t *keyVal )
{
     *keyVal = mouseKeyModeBuf[8];
}

uint8_t App_Mouse_Get_Dpi_Index(void )
{
    return mousePara.dpiIndex;
}

void App_Mouse_Set_Dpi_Index(uint8_t dpiIndex )
{
    mousePara.dpiIndex = dpiIndex;

    App_Mouse_Para_Save();
}

uint8_t App_Mouse_Get_Dpi_Num(void )
{
    return mousePara.dpiNum;
}

void App_Mouse_Get_Dpi_Color(uint8_t dpiIndex, light_color_t *dpiColor )
{
    *dpiColor = mousePara.dpiColorBuf[dpiIndex];
}

void App_Mouse_Get_Macro_Key(uint8_t macroId )
{
    uint32_t flashAddr; 

    switch(macroId)
    {
        case 1: flashAddr = FLASH_MACRO1_START_ADDR; break;
        case 2: flashAddr = FLASH_MACRO2_START_ADDR; break;
        case 3: flashAddr = FLASH_MACRO3_START_ADDR; break;
        case 4: flashAddr = FLASH_MACRO4_START_ADDR; break;
        default: break;
    }

    Drv_Inter_Flash_Read(flashAddr, 1, &macroKeyLength);

    Drv_Inter_Flash_Read(flashAddr+1, macroKeyLength*sizeof(macro_key_val_t), (uint8_t *)macroKeyBuf);
}

void App_Mouse_Get_Macro_Key_Val(uint8_t macroKeyIndex, macro_key_val_t *macroKeyVal )
{
    *macroKeyVal = macroKeyBuf[macroKeyIndex];    
}

uint8_t App_Mouse_Get_Macro_Key_Num(void )
{
    return macroKeyLength;
}

void App_Mouse_Set_Pic(uint8_t *buf, uint8_t length )
{
    uint8_t i;
    uint8_t tmp;

    pic_para_t *picPara = (pic_para_t *)buf;

    for(i=0;i<sizeof(picPara->picBuf)/2;i++)
    {
        tmp = picPara->picBuf[i*2];

        picPara->picBuf[i*2] = picPara->picBuf[i*2+1];

        picPara->picBuf[i*2+1] = tmp;
    }

    switch(picCtrl.picFlashState)
    {
        case PIC_FLASH_STATE_ERASE:
        {
            if(picPara->picId != 0xff)
            {
                picCtrl.picFlashAddr = picPara->picId * ERASE_64K_BLOCK_SIZE * 2;

                picCtrl.picRecvLength = 0;

                Drv_Spi_64K_Block_Erase(picCtrl.picFlashAddr);

                Drv_Spi_64K_Block_Erase(picCtrl.picFlashAddr + ERASE_64K_BLOCK_SIZE);

                Drv_Spi_Write(picCtrl.picFlashAddr, picPara->picBuf, picPara->picLength);

                picCtrl.picFlashAddr += picPara->picLength;
                
                picCtrl.picRecvLength += picPara->picLength;

                picCtrl.picFlashState = PIC_FLASH_STATE_WRITE;
            }
            break;
        }
        case PIC_FLASH_STATE_WRITE:
        {
            if(picPara->picId != 0xff)
            {
                Drv_Spi_Write(picCtrl.picFlashAddr, picPara->picBuf, picPara->picLength);

                picCtrl.picFlashAddr += picPara->picLength;
                
                picCtrl.picRecvLength += picPara->picLength;

                if(picCtrl.picRecvLength >= LCD_W * LCD_H * 2)
                {
                    App_Mouse_Set_Pic_Mask(picPara->picId);
                    
                    picCtrl.picTotalNum++;

                    App_Lcd_Show_Pic(picPara->picId);

                    picCtrl.picFlashState = PIC_FLASH_STATE_ERASE;
                }
            }
            else
            {
                picCtrl.picFlashState = PIC_FLASH_STATE_ERASE;
            }
            break;
        }
        default: break;
    }

    Usb_Ep3_Out();
}

void App_Mouse_Set_Pic_Mask(uint8_t picId )
{
    uint8_t i,j;
    uint16_t picMask;
    
    if(picId > 16)
    {
        picId = 16;
    }
    else if(picId < 1)
    {
        picId = 1;
    }
    
    if(picId > 8)
    {
        mousePara.picShowMask_h |= (1 << (picId-8));
    }
    else
    {
        mousePara.picShowMask_l |= (1 << (picId-1));
    }

    picMask = (uint16_t )mousePara.picShowMask_h << 8 | mousePara.picShowMask_l;

    j = 0;

    for(i=0;i<16;i++)
    {
        if(picMask & (1<<i))
        {
            picIdBuf[j++] = i+1;
        }   
    }
}

uint8_t App_Mouse_Get_Pic_Id(uint8_t picIndex )
{
    return  picIdBuf[picIndex];
}



