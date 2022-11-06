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
/* Private define ---------------------------------------*/
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
/* Private variables ------------------------------------*/
static mouse_para_t mousePara;
static key_val_t    mouseKeyModeBuf[15] = {0};

void App_Mouse_Init(void )
{        
    App_Mouse_Para_Read();
    
    if(mousePara.keyMode > 3)
    {   
        mousePara.keyMode = 0;

        mousePara.reportRate = 4;

        mousePara.sensorID = 2;
        
        App_Mouse_Key_Mode_1_Init();

        App_Mouse_Key_Mode_2_Init();

        App_Mouse_Key_Mode_3_Init();

        App_Mouse_Dpi_Init();

        App_Mouse_Light_Init();

        App_Mouse_Para_Save();
    }

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
    
    mousePara.lightModeIndex = 1;

    for(i=0;i<10;i++)
    {
        mousePara.lightPara[i].brightness = 2;
        mousePara.lightPara[i].speed = 1;
        mousePara.lightPara[i].direction = 1;
        mousePara.lightPara[i].colorNum = 7;
        
        for(j=0;j<7;j++)
        {
            switch(j)
            {
                case 0: mousePara.lightPara[i].colorBuf[j].rVal = 0xff;mousePara.lightPara[i].colorBuf[j].gVal = 0x00;mousePara.lightPara[i].colorBuf[j].bVal = 0x00;break;
                case 1: mousePara.lightPara[i].colorBuf[j].rVal = 0x00;mousePara.lightPara[i].colorBuf[j].gVal = 0x00;mousePara.lightPara[i].colorBuf[j].bVal = 0xff;break;
                case 2: mousePara.lightPara[i].colorBuf[j].rVal = 0x00;mousePara.lightPara[i].colorBuf[j].gVal = 0xff;mousePara.lightPara[i].colorBuf[j].bVal = 0x00;break;
                case 3: mousePara.lightPara[i].colorBuf[j].rVal = 0x80;mousePara.lightPara[i].colorBuf[j].gVal = 0x00;mousePara.lightPara[i].colorBuf[j].bVal = 0xff;break;
                case 4: mousePara.lightPara[i].colorBuf[j].rVal = 0x00;mousePara.lightPara[i].colorBuf[j].gVal = 0xff;mousePara.lightPara[i].colorBuf[j].bVal = 0xff;break;
                case 5: mousePara.lightPara[i].colorBuf[j].rVal = 0xff;mousePara.lightPara[i].colorBuf[j].gVal = 0xff;mousePara.lightPara[i].colorBuf[j].bVal = 0x00;break;
                case 6: mousePara.lightPara[i].colorBuf[j].rVal = 0xff;mousePara.lightPara[i].colorBuf[j].gVal = 0xff;mousePara.lightPara[i].colorBuf[j].bVal = 0xff;break;
                case 7: mousePara.lightPara[i].colorBuf[j].rVal = 0xff;mousePara.lightPara[i].colorBuf[j].gVal = 0x80;mousePara.lightPara[i].colorBuf[j].bVal = 0x00;break;
                default: break;
            }
        }
            
    }
}

void App_Mouse_Set_Key_Mode(uint8_t *buf, uint8_t length )
{
    uint8_t i;

    uint8_t *datePtr = (uint8_t *)&mousePara.date;

    uint8_t isDateFlag = buf[1];
    
    mousePara.keyMode = buf[2];

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
        for(i=0;i<length;i++)
        {
            *datePtr++ = buf[3+i]; 
        }
    }

    App_Mouse_Para_Save();
}

void App_Mouse_Get_Key_Mode(uint8_t *buf, uint8_t length )
{
    uint8_t  tmpEp0Buf[64] = {0};

    usb_ctrl_setup_t usbCtrlSetup = *(usb_ctrl_setup_t *)buf;
    
    uint8_t tmpEp0Length = usbCtrlSetup.wLength_l; //usb request length

    tmpEp0Buf[0] = usbCtrlSetup.wValue_l; //report ID
    tmpEp0Buf[1] = mousePara.keyMode;
    
    Usb_Ctrl_Send(tmpEp0Buf, tmpEp0Length);
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

