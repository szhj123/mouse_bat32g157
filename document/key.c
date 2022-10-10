/********************************************************
* @file       key.c
* @author     szhj13
* @version    V1.0
* @date       2018-10-19
* @brief      key function
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "ES8P508x.h"
#include "string.h"
#include "system_ES8P508x.h"
#include "lib_config.h"
#include "hardware.h"
#include "kernel.h"
#include "sysctrl.h"
#include "event.h"
#include "key.h"
/* Private typedef --------------------------------------*/
/* Private define ---------------------------------------*/
/* Private macro ----------------------------------------*/
/* Private variables ------------------------------------*/
keyPara_Typedef keyPara;

static uint8_t wheelUpFlag;
static uint8_t wheelDownFlag;

const uint8_t EncoderTab[24] = {
                                 0, 4, 8, 12, 16, 4,
                                 8, 12, 20, 4, 8, 12,
                                 0, 4, 8, 12, 16, 4,
                                 0x89, 12, 20, 0x84, 8, 12};

static void Init(void *t )
{
    keyPara_Typedef *cthis = (keyPara_Typedef *)t;

    cthis->id = 1;
}


static void Delay_Count(void )
{
    if(keyPara.keyDelayCnt < 0xffff)
        keyPara.keyDelayCnt++;

    if(keyPara.knobDelayCnt < 0xffff)
        keyPara.knobDelayCnt++;

    Key_Mac_Detect();

    Key_Knob_Detect();
}

static void Process(void )
{
    btnEvtPara_Typedef btnEvtPara;

    switch(keyPara.keyVal)
    {

        case KEY_RE_CENTER | KEY_DOWN | KEY_UP:
             memset((uint8_t *)&btnEvtPara, 0xff, sizeof(btnEvtPara_Typedef));
             btnEvtPara.cmd = CMD_BTN_EVT_ID;
             btnEvtPara.trackBtn = BTN_SHORT;
             evtPara.Evt_Add_Msg(keyPara.id, evt_btn_re_center,(uint8_t *)&btnEvtPara, sizeof(btnEvtPara_Typedef));
             keyPara.keyVal = KEY_NULL;
             break;
        case KEY_RE_CENTER | KEY_LONG:
             memset((uint8_t *)&btnEvtPara, 0xff, sizeof(btnEvtPara_Typedef));
             btnEvtPara.cmd = CMD_BTN_EVT_ID;
             btnEvtPara.trackBtn = BTN_LONG;
             evtPara.Evt_Add_Msg(keyPara.id, evt_btn_re_center,(uint8_t *)&btnEvtPara, sizeof(btnEvtPara_Typedef));
             keyPara.keyVal = KEY_NULL;
             break;
        default:
             break;
    }

    #if 0
    if(keyPara.knobVal == 0x89)
    {
        memset((uint8_t *)&btnEvtPara, 0xff, sizeof(btnEvtPara_Typedef));
        btnEvtPara.cmd = CMD_BTN_EVT_ID;
        btnEvtPara.encoder1 = ENC_FORWARD;
        evtPara.Evt_Add_Msg(keyPara.id, evt_btn_knob,(uint8_t *)&btnEvtPara, sizeof(btnEvtPara_Typedef));
    }

    if(keyPara.knobVal == 0x84)
    {
        memset((uint8_t *)&btnEvtPara, 0xff, sizeof(btnEvtPara_Typedef));
        btnEvtPara.cmd = CMD_BTN_EVT_ID;
        btnEvtPara.encoder1 = ENC_BACKWARD;
        evtPara.Evt_Add_Msg(keyPara.id, evt_btn_knob,(uint8_t *)&btnEvtPara, sizeof(btnEvtPara_Typedef));
    }
    #else
    if(wheelUpFlag)
    {
        wheelUpFlag = 0;
        memset((uint8_t *)&btnEvtPara, 0xff, sizeof(btnEvtPara_Typedef));
        btnEvtPara.cmd = CMD_BTN_EVT_ID;
        btnEvtPara.encoder1 = ENC_FORWARD;
        evtPara.Evt_Add_Msg(keyPara.id, evt_btn_knob,(uint8_t *)&btnEvtPara, sizeof(btnEvtPara_Typedef));
    }

    if(wheelDownFlag)
    {
        wheelDownFlag = 0;
        memset((uint8_t *)&btnEvtPara, 0xff, sizeof(btnEvtPara_Typedef));
        btnEvtPara.cmd = CMD_BTN_EVT_ID;
        btnEvtPara.encoder1 = ENC_BACKWARD;
        evtPara.Evt_Add_Msg(keyPara.id, evt_btn_knob,(uint8_t *)&btnEvtPara, sizeof(btnEvtPara_Typedef));
    }
    #endif

}

uint16_t Key_Scan(void )
{
    if(Btn_Re_Center_Read() == RESET)
        return KEY_RE_CENTER;

    return KEY_NULL;
}

void Key_Mac_Detect(void )
{
    static keyStat_Typedef keyStat = keyInit;
    static uint16_t keySave = KEY_NULL;
    uint16_t keyVal = KEY_NULL;

    keyVal = Key_Scan();

    switch(keyStat)
    {
        case keyInit:
             if(keyVal != KEY_NULL)
             {
                 keyPara.keyDelayCnt = 0;
                 keyStat = keyPress;
             }
             break;
        case keyPress:
             if(keyVal != KEY_NULL)
             {
                 if(keyPara.keyDelayCnt > 50)
                 {
                     keySave = keyVal;
                     keyPara.keyVal = keyVal | KEY_DOWN;
                     keyPara.keyDelayCnt = 0;
                     keyStat = keyLong;
                 }
             }
             else
                 keyStat = keyInit;
             break;
        case keyLong:
             if(keyVal != KEY_NULL)
             {
                 if(keyPara.keyDelayCnt > 2000)
                 {
                     keyPara.keyVal = keyVal | KEY_LONG;
                     keyPara.keyDelayCnt = 0;
                     keyStat = keyCont;
                 }
             }
             else
                 keyStat = keyUp;
             break;
        case keyCont:
             if(keyVal != KEY_NULL)
             {
                 if(keyPara.keyDelayCnt > 50)
                 {
                     keyPara.keyVal = keyVal | KEY_CONT;
                     keyPara.keyDelayCnt = 0;
                 }

                 if(keyVal != keySave)
                 {
                     keyStat = keyInit;
                     return ;
                 }
             }
             else
                 keyStat = keyUp;
             break;
        case keyUp:
             keyPara.keyVal |= KEY_UP;
             keyStat = keyInit;
             break;
        default:
             break;
    }
}

void Key_Knob_Detect(void )
{
    #if 0
    uint8_t tempEnc = 0x03;


    if(keyPara.knobDelayCnt > 5)
    {
        keyPara.knobDelayCnt = 0;

        if(Knob_A_Read() == 0)
            tempEnc &= ~0x01;
        if(Knob_B_Read() == 0)
            tempEnc &= ~0x02;

        keyPara.knobVal = EncoderTab[(keyPara.knobVal & 0x1c) | tempEnc];
    }
    #else
    static uint8_t saveKnob_A;
    static uint8_t saveKnob_B;

    if(keyPara.knobDelayCnt > 1)
    {
        keyPara.knobDelayCnt = 0;

        if(Knob_A_Read() ^ Knob_B_Read())
        {
            if(saveKnob_A && saveKnob_B)
            {
                if(!Knob_A_Read() && Knob_B_Read())
                {
                    wheelDownFlag= 1;
                }
                else if(Knob_A_Read() && !Knob_B_Read())
                {
                    wheelUpFlag = 1;
                }
                else
                {
                    wheelDownFlag= 0;
                    wheelUpFlag = 0;
                }
            }
            else if(!saveKnob_A && !saveKnob_B)
            {
                if(!Knob_A_Read() && Knob_B_Read())
                {
                    wheelUpFlag = 1;
                }
                else if(Knob_A_Read() && !Knob_B_Read())
                {
                    wheelDownFlag = 1;
                }
                else
                {

                    wheelDownFlag= 0;
                    wheelUpFlag = 0;
                }
            }

            saveKnob_A = Knob_A_Read();
            saveKnob_B = Knob_B_Read();
        }
        else
        {
            saveKnob_A = Knob_A_Read();
            saveKnob_B = Knob_B_Read();

            wheelUpFlag = 0;
            wheelDownFlag = 0;
        }
    }
    #endif
}

void * New_KeyPara(void *t )
{
    keyPara_Typedef *cthis = (keyPara_Typedef *)t;

    cthis->Init = Init;
    cthis->Delay_Count = Delay_Count;
    cthis->Process = Process;

    return (void *)cthis;
}


