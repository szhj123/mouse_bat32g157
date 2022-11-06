/***********************************************************************************************************************
* Copyright (C) . All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : ssi_api_if.h
* Version      :  
* Device(s)    : BAT32G157
* Tool-Chain   : MDK(armcc)
* Description  : This file is a template.
* Creation Date: 2019/4/30
***********************************************************************************************************************/

#ifndef SSI_API_IF_H_
#define SSI_API_IF_H_

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/


/******************************************************************************
Macro definitions
******************************************************************************/


/******************************************************************************
Typedef definitions
******************************************************************************/
/* Channel Number of SSI */
typedef enum {
    SSI_CH0 = 0,
#if (defined(SSI1) || defined(SSIE1))
    SSI_CH1 = 1, /* activates when using MCU with SSI1 or SSIE1 */
#endif
} ssi_ch_t;

/* Setting Value of Mute On/Off */
typedef enum {
    SSI_MUTE_ON  = 0,
    SSI_MUTE_OFF = 1,
} ssi_mute_t;

/* Return Value of SSI API */
typedef enum {
    SSI_SUCCESS     = 0,
    SSI_FLAG_CLR    = 0,
    SSI_FLAG_SET    = 1,
    SSI_ERR_PARAM   = -1,
    SSI_ERR_CHANNEL = -2,
    SSI_ERR_EXCEPT  = -3,
} ssi_ret_t;

/******************************************************************************
Exported global variables
******************************************************************************/
/* No global variable definited */

/******************************************************************************
Exported global functions (to be accessed by other files)
******************************************************************************/
ssi_ret_t SSI_Open ( const ssi_ch_t Channel );
ssi_ret_t SSI_Start ( const ssi_ch_t Channel );
ssi_ret_t SSI_Stop ( const ssi_ch_t Channel );
ssi_ret_t SSI_Close ( const ssi_ch_t Channel );
int8_t SSI_Write ( const ssi_ch_t Channel, const void * pBuf, const uint8_t Samples );
int8_t SSI_Read ( const ssi_ch_t Channel, void * pBuf, const uint8_t Samples );
ssi_ret_t SSI_Mute ( const ssi_ch_t Channel, const ssi_mute_t OnOff );

ssi_ret_t SSI_GetFlagTxUnderFlow ( const ssi_ch_t Channel );
ssi_ret_t SSI_GetFlagTxOverFlow ( const ssi_ch_t Channel );
ssi_ret_t SSI_GetFlagRxUnderFlow ( const ssi_ch_t Channel );
ssi_ret_t SSI_GetFlagRxOverFlow ( const ssi_ch_t Channel );
ssi_ret_t SSI_ClearFlagTxUnderFlow ( const ssi_ch_t Channel );
ssi_ret_t SSI_ClearFlagTxOverFlow ( const ssi_ch_t Channel );
ssi_ret_t SSI_ClearFlagRxUnderFlow ( const ssi_ch_t Channel );
ssi_ret_t SSI_ClearFlagRxOverFlow ( const ssi_ch_t Channel );
ssi_ret_t SSI_GetFlagTxEmptyFlow ( const ssi_ch_t Channel );
ssi_ret_t SSI_GetFlagRxFullFlow ( const ssi_ch_t Channel );

#endif /* SSI_API_IF_H_ */

