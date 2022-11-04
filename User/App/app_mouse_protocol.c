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
/* Private typedef --------------------------------------*/
/* Private define ---------------------------------------*/
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
/* Private variables ------------------------------------*/
static mouse_para_t mousePara;

void App_Mouse_Init(void )
{        
    App_Mouse_Para_Read();
    
    if(mousePara.keyModeIndex > 3)
    {   
        mousePara.keyModeIndex = 0;

        mousePara.reportRate = 4;

        mousePara.sensorID = 2;
        
        App_Mouse_Key_Mode_0_Init();

        App_Mouse_Key_Mode_1_Init();

        App_Mouse_Key_Mode_2_Init();

        App_Mouse_Dpi_Init();

        App_Mouse_Light_Init();

        App_Mouse_Para_Save();
    }
}

void App_Mouse_Key_Mode_0_Init(void )
{
    mousePara.KeyMode_0_buf[0].keyType  = 0x01;
    mousePara.KeyMode_0_buf[0].keyFunc  = 0xf0;
    mousePara.KeyMode_0_buf[0].keyVal_l = 0;
    mousePara.KeyMode_0_buf[0].keyVal_h = 0;

    mousePara.KeyMode_0_buf[1].keyType  = 0x01;
    mousePara.KeyMode_0_buf[1].keyFunc  = 0xf1;
    mousePara.KeyMode_0_buf[1].keyVal_l = 0;
    mousePara.KeyMode_0_buf[1].keyVal_h = 0;

    mousePara.KeyMode_0_buf[2].keyType  = 0x01;
    mousePara.KeyMode_0_buf[2].keyFunc  = 0xf2;
    mousePara.KeyMode_0_buf[2].keyVal_l = 0;
    mousePara.KeyMode_0_buf[2].keyVal_h = 0;

    mousePara.KeyMode_0_buf[3].keyType  = 0x01;
    mousePara.KeyMode_0_buf[3].keyFunc  = 0xf3;
    mousePara.KeyMode_0_buf[3].keyVal_l = 0;
    mousePara.KeyMode_0_buf[3].keyVal_h = 0;

    mousePara.KeyMode_0_buf[4].keyType  = 0x01;
    mousePara.KeyMode_0_buf[4].keyFunc  = 0xf4;
    mousePara.KeyMode_0_buf[4].keyVal_l = 0;
    mousePara.KeyMode_0_buf[4].keyVal_h = 0;

    mousePara.KeyMode_0_buf[5].keyType  = 0x05;
    mousePara.KeyMode_0_buf[5].keyFunc  = 0x01;
    mousePara.KeyMode_0_buf[5].keyVal_l = 0;
    mousePara.KeyMode_0_buf[5].keyVal_h = 0;

    mousePara.KeyMode_0_buf[6].keyType  = 0x05;
    mousePara.KeyMode_0_buf[6].keyFunc  = 0x02;
    mousePara.KeyMode_0_buf[6].keyVal_l = 0;
    mousePara.KeyMode_0_buf[6].keyVal_h = 0;

    mousePara.KeyMode_0_buf[7].keyType  = 0x07;
    mousePara.KeyMode_0_buf[7].keyFunc  = 0x04;
    mousePara.KeyMode_0_buf[7].keyVal_l = 0;
    mousePara.KeyMode_0_buf[7].keyVal_h = 50;

    mousePara.KeyMode_0_buf[8].keyType  = 0x07;
    mousePara.KeyMode_0_buf[8].keyFunc  = 0x05;
    mousePara.KeyMode_0_buf[8].keyVal_l = 0;
    mousePara.KeyMode_0_buf[8].keyVal_h = 0;
}

void App_Mouse_Key_Mode_1_Init(void )
{
    mousePara.KeyMode_1_buf[0].keyType  = 0x01;
    mousePara.KeyMode_1_buf[0].keyFunc  = 0xf0;
    mousePara.KeyMode_1_buf[0].keyVal_l = 0;
    mousePara.KeyMode_1_buf[0].keyVal_h = 0;

    mousePara.KeyMode_1_buf[1].keyType  = 0x01;
    mousePara.KeyMode_1_buf[1].keyFunc  = 0xf1;
    mousePara.KeyMode_1_buf[1].keyVal_l = 0;
    mousePara.KeyMode_1_buf[1].keyVal_h = 0;

    mousePara.KeyMode_1_buf[2].keyType  = 0x01;
    mousePara.KeyMode_1_buf[2].keyFunc  = 0xf2;
    mousePara.KeyMode_1_buf[2].keyVal_l = 0;
    mousePara.KeyMode_1_buf[2].keyVal_h = 0;

    mousePara.KeyMode_1_buf[3].keyType  = 0x04;
    mousePara.KeyMode_1_buf[3].keyFunc  = 0x00;
    mousePara.KeyMode_1_buf[3].keyVal_l = 0xb6;
    mousePara.KeyMode_1_buf[3].keyVal_h = 0x00;

    mousePara.KeyMode_1_buf[4].keyType  = 0x04;
    mousePara.KeyMode_1_buf[4].keyFunc  = 0x00;
    mousePara.KeyMode_1_buf[4].keyVal_l = 0xb5;
    mousePara.KeyMode_1_buf[4].keyVal_h = 0;

    mousePara.KeyMode_1_buf[5].keyType  = 0x04;
    mousePara.KeyMode_1_buf[5].keyFunc  = 0x01;
    mousePara.KeyMode_1_buf[5].keyVal_l = 0xe9;
    mousePara.KeyMode_1_buf[5].keyVal_h = 0x00;

    mousePara.KeyMode_1_buf[6].keyType  = 0x04;
    mousePara.KeyMode_1_buf[6].keyFunc  = 0x00;
    mousePara.KeyMode_1_buf[6].keyVal_l = 0xea;
    mousePara.KeyMode_1_buf[6].keyVal_h = 0x00;

    mousePara.KeyMode_1_buf[7].keyType  = 0x04;
    mousePara.KeyMode_1_buf[7].keyFunc  = 0x00;
    mousePara.KeyMode_1_buf[7].keyVal_l = 0xcd;
    mousePara.KeyMode_1_buf[7].keyVal_h = 0x00;
}

void App_Mouse_Key_Mode_2_Init(void )
{
    mousePara.KeyMode_2_buf[0].keyType = 0x01;
    mousePara.KeyMode_2_buf[0].keyFunc = 0xf0;
    mousePara.KeyMode_2_buf[0].keyVal_l = 0;
    mousePara.KeyMode_2_buf[0].keyVal_h = 0;

    mousePara.KeyMode_2_buf[1].keyType = 0x01;
    mousePara.KeyMode_2_buf[1].keyFunc = 0xf1;
    mousePara.KeyMode_2_buf[1].keyVal_l = 0;
    mousePara.KeyMode_2_buf[1].keyVal_h = 0;

    mousePara.KeyMode_2_buf[2].keyType = 0x01;
    mousePara.KeyMode_2_buf[2].keyFunc = 0xf2;
    mousePara.KeyMode_2_buf[2].keyVal_l = 0;
    mousePara.KeyMode_2_buf[2].keyVal_h = 0;

    mousePara.KeyMode_2_buf[3].keyType = 0x01;
    mousePara.KeyMode_2_buf[3].keyFunc = 0xf3;
    mousePara.KeyMode_2_buf[3].keyVal_l = 0;
    mousePara.KeyMode_2_buf[3].keyVal_h = 0;

    mousePara.KeyMode_2_buf[4].keyType = 0x01;
    mousePara.KeyMode_2_buf[4].keyFunc = 0xf4;
    mousePara.KeyMode_2_buf[4].keyVal_l = 0;
    mousePara.KeyMode_2_buf[4].keyVal_h = 0;

    mousePara.KeyMode_2_buf[5].keyType = 0x05;
    mousePara.KeyMode_2_buf[5].keyFunc = 0x01;
    mousePara.KeyMode_2_buf[5].keyVal_l = 0;
    mousePara.KeyMode_2_buf[5].keyVal_h = 0;

    mousePara.KeyMode_2_buf[6].keyType = 0x05;
    mousePara.KeyMode_2_buf[6].keyFunc = 0x02;
    mousePara.KeyMode_2_buf[6].keyVal_l = 0;
    mousePara.KeyMode_2_buf[6].keyVal_h = 0;

    mousePara.KeyMode_2_buf[7].keyType = 0x07;
    mousePara.KeyMode_2_buf[7].keyFunc = 0x04;
    mousePara.KeyMode_2_buf[7].keyVal_l = 0;
    mousePara.KeyMode_2_buf[7].keyVal_h = 0;
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

void App_Mouse_Para_Read(void )
{
    Drv_Inter_Flash_Read(FLASH_MOUSE_START_ADDR, sizeof(mouse_para_t), (uint8_t *)&mousePara);
}

void App_Mouse_Para_Save(void )
{    
    Drv_Inter_Flash_Erase_Sector(FLASH_MOUSE_START_ADDR);

    Drv_Inter_Flash_Write(FLASH_MOUSE_START_ADDR, sizeof(mouse_para_t), (uint8_t *)&mousePara);
}

