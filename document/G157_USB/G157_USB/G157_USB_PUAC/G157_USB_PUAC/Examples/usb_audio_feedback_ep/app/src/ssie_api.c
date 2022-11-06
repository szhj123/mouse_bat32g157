/*******************************************************************************
* Copyright (C) 2014-2020 CMS. All rights reserved.    
*******************************************************************************/
/******************************************************************************
* File Name    : ssie_api.c
* Version      : 2.00
* Description  : SSI driver module file for BAT MCUs.
*******************************************************************************
* History : DD.MM.YYYY  Version  Description
*         : 18.05.2020   1.00     First release.
*
******************************************************************************/

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
/* Configuration options for the SSI API. This is also included in 
   ssi_api_rx.h and would normally not need to be included separately.
   It is included separately here so that the decision can be made to use
   the r_bsp package or not. */
#include "ssie.h"
#include "ssi_api_config.h"
/* Function prototypes and device specific info needed for SSI API */
#include "ssi_api_if.h"

#if (defined(SSIE0) || defined(SSIE1))

/* Information needed for SSI API. */
#include "ssie_api_private.h"

/******************************************************************************
Macro definitions
******************************************************************************/
/* time-out count
   How to decide "time-out count".
     Functions SSI_Stop() & SSI_Mute() wait 2 PCM data in TX FIFO & 
       1 data in shift register to be sent. So totally at least "1/Fs [uSec] x 3" 
       period of time is needed.
     And when Sampling frequency is 8kHz, the time to finish sending all data 
       is the maximum. it is 
       1/(8kHz) x 3 = 375[uSec]. 
     So waiting time must be larger than 375[uSec].
     In case, CPU clock is 240MHz, loop times is maximum.
       1/(240MHz) x 90000 = 375[uSec]
     Adding about 10% margin(10000), total times for loop is 
       1/(240MHz) x (90000 + 10000) = 416[uSec]
     Then, here timeout loop times is configured "100000".
*/ 
#define FIT_NO_PTR                   (000000u)  
#define SSIE_TIMEOUT_416USEC         (100000u) /* time-out count */

/* Macro definitions to access status flag bits */
#define SSIE_BIT_RDF     (0x00000001)    /* RDF bit location to clear*/
#define SSIE_BIT_TDE     (0x00010000)    /* TDE bit location to clear*/
#define SSIE_BIT_TUIRQ   (0x20000000)    /* TUIRQ bit location to clear*/
#define SSIE_BIT_TOIRQ   (0x10000000)    /* TOIRQ bit location to clear*/
#define SSIE_BIT_RUIRQ   (0x08000000)    /* RUIRQ bit location to clear*/
#define SSIE_BIT_ROIRQ   (0x04000000)    /* ROIRQ bit location to clear*/

/******************************************************************************
Typedef definitions
******************************************************************************/
/* MSTP parameter  */
typedef enum {
    SSIE_MSTP_CLR = 0,
    SSIE_MSTP_SET = 1,
} ssi_mstp_t;

/******************************************************************************
Exported global variables 
******************************************************************************/

/******************************************************************************
Private global variables and functions
******************************************************************************/
/* Tables contain values for local functions */
static const uint32_t ssi_get_iomode [] =  /* iomode table*/
{
    SSIE_CH0_IO_MODE,
#ifdef SSIE1
    SSIE_CH1_IO_MODE, /* activates when using MCU with SSIE1 */
#endif
};

static const uint32_t ssi_get_ssi_address [] = /* SSIE0/1 io register address table */
{
    (uint32_t)&SSIE0,
#ifdef SSIE1
    (uint32_t)&SSIE1, /* activates when using MCU with SSIE1 */
#endif
};

/******************************************************************************
* Function Name: ssi_down_count
* Description  : is used for time-out operation, decrements "down_count" value
* Arguments    : down_count: a value to be decremented
* Return Value : "down_count" value after decement
******************************************************************************/
uint16_t ssi_down_count ( uint32_t down_count )
{
    if ( down_count > 0u )
    {
        down_count--;
    }
    else
    {
        /* Do nothing. */
    }
    return down_count;
} /* End of Function ssi_down_count */

/******************************************************************************
* Function Name: ssi_clear_flag_tde
* Description  : clears TDE bit of io register
* Arguments    : p_ssi_reg: SSIE0 or SSIE1 io register address
* Return Value : none
******************************************************************************/
void ssi_clear_flag_tde ( volatile struct st_ssie * p_ssi_reg )
{   
    uint32_t ssifsr = p_ssi_reg->SSIFSR.WORD;  /* get SSIFSR */

    ssifsr &= (~SSIE_BIT_TDE);                 /* clear TDE to 0 */
    p_ssi_reg->SSIFSR.WORD = ssifsr;           /* update SSIFSR */
} /* End of Function ssi_clear_flag_tde */

/******************************************************************************
* Function Name: ssi_clear_flag_rdf
* Description  : clears TDE bit of io register
* Arguments    : p_ssi_reg: SSIE0 or SSIE1 io register address
* Return Value : none
******************************************************************************/
void ssi_clear_flag_rdf ( volatile struct st_ssie * p_ssi_reg )
{   
    uint32_t ssifsr = p_ssi_reg->SSIFSR.WORD;  /* get SSIFSR */

    ssifsr &= (~SSIE_BIT_RDF);                 /* clear RDF to 0 */
    p_ssi_reg->SSIFSR.WORD = ssifsr;           /* update SSIFSR */
} /* End of Function ssi_clear_flag_rdf */

/******************************************************************************
* Function Name: ssi_clear_flag_tuirq
* Description  : clears TDE bit of io register
* Arguments    : p_ssi_reg: SSIE0 or SSIE1 io register address
* Return Value : none
******************************************************************************/
void ssi_clear_flag_tuirq ( volatile struct st_ssie * p_ssi_reg )
{   
    uint32_t ssisr = p_ssi_reg->SSISR.WORD;  /* get SSISR */

    ssisr &= (~SSIE_BIT_TUIRQ);              /* clear TUIRQ to 0 */
    p_ssi_reg->SSISR.WORD = ssisr;           /* update SSISR */
} /* End of Function ssi_clear_flag_tuirq */

/******************************************************************************
* Function Name: ssi_clear_flag_toirq
* Description  : clears TDE bit of io register
* Arguments    : p_ssi_reg: SSIE0 or SSIE1 io register address
* Return Value : none
******************************************************************************/
void ssi_clear_flag_toirq ( volatile struct st_ssie * p_ssi_reg )
{   
    uint32_t ssisr = p_ssi_reg->SSISR.WORD;  /* get SSISR */

    ssisr &= (~SSIE_BIT_TOIRQ);              /* clear TOIRQ to 0 */
    p_ssi_reg->SSISR.WORD = ssisr;           /* update SSISR */
} /* End of Function ssi_clear_flag_toirq */

/******************************************************************************
* Function Name: ssi_clear_flag_ruirq
* Description  : clears TDE bit of io register
* Arguments    : p_ssi_reg: SSIE0 or SSIE1 io register address
* Return Value : none
******************************************************************************/
void ssi_clear_flag_ruirq ( volatile struct st_ssie * p_ssi_reg )
{   
    uint32_t ssisr = p_ssi_reg->SSISR.WORD;  /* get SSISR */

    ssisr &= (~SSIE_BIT_RUIRQ);              /* clear RUIRQ to 0 */
    p_ssi_reg->SSISR.WORD = ssisr;           /* update SSISR */
} /* End of Function ssi_clear_flag_ruirq */

/******************************************************************************
* Function Name: ssi_clear_flag_roirq
* Description  : clears TDE bit of io register
* Arguments    : p_ssi_reg: SSIE0 or SSIE1 io register address
* Return Value : none
******************************************************************************/
void ssi_clear_flag_roirq ( volatile struct st_ssie * p_ssi_reg )
{   
    uint32_t ssisr = p_ssi_reg->SSISR.WORD;  /* get SSISR */

    ssisr &= (~SSIE_BIT_ROIRQ);              /* clear ROIRQ to 0 */
    p_ssi_reg->SSISR.WORD = ssisr;           /* update SSISR */
} /* End of Function ssi_clear_flag_roirq */

/******************************************************************************
* Function Name: ssi_module_stop
* Description  : 
* Arguments    : p_ssi_reg: SSIE0 or SSIE1 io register address
*                ssi_mstp : activate or deactivate module stop
* Return Value : none
******************************************************************************/
#if 1
void ssi_module_stop (const ssi_ch_t Channel, const ssi_mstp_t ssi_mstp)
{
	if(ssi_mstp == SSIE_MSTP_CLR)
  		CGC->PER2 = 0x02;	// IISEN
	else
  		CGC->PER2 = 0x00;	// IISEN

}
#else
void ssi_module_stop (const ssi_ch_t Channel, const ssi_mstp_t ssi_mstp)
{
#if (R_BSP_VERSION_MAJOR >= 5) && (R_BSP_VERSION_MINOR >= 30)
	bsp_int_ctrl_t int_ctrl;
#endif

    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_LPC_CGC_SWR);

#if (R_BSP_VERSION_MAJOR >= 5) && (R_BSP_VERSION_MINOR >= 30)
    R_BSP_InterruptControl(BSP_INT_SRC_EMPTY, BSP_INT_CMD_FIT_INTERRUPT_DISABLE, &int_ctrl);
#endif

    switch (Channel)
    {
        case SSI_CH0:
            MSTP(SSIE0) = ssi_mstp;
        break;

#ifdef SSIE1 /* activates when using MCU with SSIE1 */
        case SSI_CH1:
            MSTP(SSIE1) = ssi_mstp;
        break;
#endif
        default:
            ; /* no operation */
        break;
    }
#if (R_BSP_VERSION_MAJOR >= 5) && (R_BSP_VERSION_MINOR >= 30)
    R_BSP_InterruptControl(BSP_INT_SRC_EMPTY, BSP_INT_CMD_FIT_INTERRUPT_ENABLE, &int_ctrl);
#endif

    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_LPC_CGC_SWR);
} /* End of Function  */
#endif

/******************************************************************************
* Function Name: ssi_check_param
* Description  : 
* Arguments    : const ssi_ch_t Channel     : [I] Channel Number of SSI
* Return Value : return value defined in enum ssi_ret_t
******************************************************************************/
ssi_ret_t ssi_check_param (const ssi_ch_t Channel)
{
    ssi_ret_t ret = SSI_SUCCESS;

#if 0
    switch (Channel)
    {
        case SSI_CH0:
            if (true == R_BSP_HardwareLock(BSP_LOCK_SSIE0))
            {
                (void)R_BSP_HardwareUnlock(BSP_LOCK_SSIE0);
                ret = SSI_ERR_CHANNEL;
            }
        break;

#ifdef SSIE1 /* activates when using MCU with SSIE1 */
        case SSI_CH1:
            if (true == R_BSP_HardwareLock(BSP_LOCK_SSIE1))
            {
                (void)R_BSP_HardwareUnlock(BSP_LOCK_SSIE1);
                ret = SSI_ERR_CHANNEL;
            }
        break;

#endif
        default:
            ret = SSI_ERR_PARAM;
        break;
    }
#endif

    return ret;
} /* End of Function ssi_check_param */

/******************************************************************************
* Function Name: ssi_check_param_buf
* Description  : 
* Arguments    : const ssi_ch_t Channel     : [I] Channel Number of SSI
*              : const void * pBuf          : [I/O] Pointer to Output Buffer
*              : const uint8_t Samples      : [I] Number of samples to write 
* Return Value : return value defined in enum ssi_ret_t
******************************************************************************/
ssi_ret_t ssi_check_param_buf (const ssi_ch_t Channel,
                                 const  void * pBuf,
                                 const  uint8_t Samples)
{
    ssi_ret_t ret = SSI_SUCCESS;

    switch (Channel)
    {
        case SSI_CH0:
            if (((uint32_t *)FIT_NO_PTR == pBuf) || (0 == Samples))
            {
                ret = SSI_ERR_PARAM;
                break;
            }

            //if (true == R_BSP_HardwareLock(BSP_LOCK_SSIE0))
            //{
            //    (void)R_BSP_HardwareUnlock(BSP_LOCK_SSIE0);
            //    ret = SSI_ERR_CHANNEL;
            //}
        break;

#ifdef SSIE1 /* activates when using MCU with SSIE1 */
        case SSI_CH1:
            if (((uint32_t *)FIT_NO_PTR == pBuf) || (0 == Samples))
            {
                ret = SSI_ERR_PARAM;
                break;
            }

            //if (true == R_BSP_HardwareLock(BSP_LOCK_SSIE1))
            //{
            //    (void)R_BSP_HardwareUnlock(BSP_LOCK_SSIE1);
            //    ret = SSI_ERR_CHANNEL;
            //}
        break;

#endif
        default:
            ret = SSI_ERR_PARAM;
        break;
    }

    return ret;
} /* End of Function ssi_check_param_buf */

/******************************************************************************
* Function Name: ssi_check_param_mute
* Description  : 
* Arguments    : const ssi_ch_t Channel      : [I] Channel Number of SSI
*              : const ssi_mute_t OnOff      : [I] Mute ON/OFF Switch
* Return Value : return value defined in enum ssi_ret_t
******************************************************************************/
ssi_ret_t ssi_check_param_mute (const ssi_ch_t Channel,
                                  const  ssi_mute_t OnOff)
{
    ssi_ret_t ret = SSI_SUCCESS;

    switch (Channel)
    {
        case SSI_CH0:

            /* The following code occurs a compilation warning but does not affect actual operation. */
            if ((SSI_MUTE_ON > OnOff) || (SSI_MUTE_OFF < OnOff))
            {
                ret = SSI_ERR_PARAM;
                break;
            }

            //if (true == R_BSP_HardwareLock(BSP_LOCK_SSIE0))
            //{
            //    (void)R_BSP_HardwareUnlock(BSP_LOCK_SSIE0);
            //    ret = SSI_ERR_CHANNEL;
            //}
        break;

#ifdef SSIE1 /* activates when using MCU with SSIE1 */
        case SSI_CH1:

            /* The following code occurs a compilation warning but does not affect actual operation. */
            if ((SSI_MUTE_ON > OnOff) || (SSI_MUTE_OFF < OnOff))
            {
                ret = SSI_ERR_PARAM;
                break;
            }

            //if (true == R_BSP_HardwareLock(BSP_LOCK_SSIE1))
            //{
            //    (void)R_BSP_HardwareUnlock(BSP_LOCK_SSIE1);
            //    ret = SSI_ERR_CHANNEL;
            //}
        break;

#endif
        default:
            ret = SSI_ERR_PARAM;
        break;
    }

    return ret;
} /* End of Function ssi_check_param_mute */

/******************************************************************************
* Function Name: ssi_get_word_num_per_sample
* Description  :
* Arguments    : p_ssi_reg: SSIE0 or SSIE1 io register address
* Return Value : uint8_t
******************************************************************************/
uint8_t ssi_get_word_num_per_sample ( volatile struct st_ssie * p_ssi_reg )
{
    uint8_t word_num_per_sample = 0;
    uint8_t omod = p_ssi_reg->SSIOFR.BIT.OMOD;
    uint8_t frm = p_ssi_reg->SSICR.BIT.FRM;

    if ((2 == omod) && (0 == frm))
    {
        /* Monaural */
        word_num_per_sample = 1;
    }
    else if ((1 == omod) && (1 == frm))
    {
        /* TDM 4words */
        word_num_per_sample = 4;
    }
    else if ((1 == omod) && (2 == frm))
    {
        /* TDM 6words */
        word_num_per_sample = 6;
    }
    else if ((1 == omod) && (3 == frm))
    {
        /* TDM 8words */
        word_num_per_sample = 8;
    }
    else if ((0 == omod) && (0 == frm))
    {
        /* I2S, Left-justified, Right-justified */
        word_num_per_sample = 2;
    }
    else {
        word_num_per_sample = 0;
    }

    return word_num_per_sample;

} /* End of Function ssi_get_word_num_per_sample */

/******************************************************************************
* Function Name: ssi_write_zero_to_tx_fifo
* Description  : Write 0 to Tx FIFO
* Arguments    : p_ssi_reg    :SSIE0 or SSIE1 io register address
*              : write_count  :write count
* Return Value :
******************************************************************************/
void ssi_write_zero_to_tx_fifo ( volatile struct st_ssie * p_ssi_reg, int32_t write_count )
{
	while(0 < write_count)
    {
        if (SSIE_SSICR_DWL08 == p_ssi_reg->SSICR.BIT.DWL)
        {
            p_ssi_reg->SSIFTDR.BYTE= 0u;
        }
        else if (SSIE_SSICR_DWL16 == p_ssi_reg->SSICR.BIT.DWL)
        {
            p_ssi_reg->SSIFTDR.HALF= 0u;
        }
        else
        {
            p_ssi_reg->SSIFTDR.WORD = 0u;
        }
        write_count --;
    }
}

/**********************************************************************************************************************
 * Function Name: SSI_Open
 ******************************************************************************************************************//**
 * @brief Locks to keep a specified SSI channel and initializes it corresponding to ssi_api_rx_config.h.
 * @param[in] Channel It specifies an SSI channel to lock. Choose one enumerator member from the enumerator typedef
 * ssi_ch_t. It is described in file ssi_api_rx_if.h.
 * @retval SSI_SUCCESS Successful, the specified SSI channel is configured.
 * @retval SSI_ERR_PARAM Not successful, the parameter is illegal.
 * @retval SSI_ERR_CHANNEL Not successful, the specified SSI channel can't be locked.
 * @retval SSI_ERR_EXCEPT Not successful, the specified SSI channel is in unwanted hardware condition.
 * @details Call this function certainly once before starting to use a specified SSI channel individually.
 * @note -
 */
ssi_ret_t SSI_Open ( const ssi_ch_t Channel )
{
    uint32_t ssifcr;
    uint32_t ssiscr;
    uint32_t ssicr;
    uint32_t ssiofr;
    volatile struct st_ssie *p_ssi_reg;
    uint32_t timeout;

    /* parameter check operation */
    switch (Channel)
    {
        case SSI_CH0:
            //if (false == R_BSP_HardwareLock(BSP_LOCK_SSIE0))
            //{
            //    return SSI_ERR_CHANNEL;
            //}

            /* logical operation to make value to set ssi register  */
            ssicr = ((SSIE_CH0_DEL << SSIE_DEL_SHIFT) |
                     (SSIE_CH0_PDTA << SSIE_PDTA_SHIFT) |
                     (SSIE_CH0_SDTA << SSIE_SDTA_SHIFT) |
                     (SSIE_CH0_SPDP << SSIE_SPDP_SHIFT) |
                     (SSIE_CH0_LRCKP << SSIE_LRCKP_SHIFT) |
                     (SSIE_CH0_BCKP << SSIE_BCKP_SHIFT) |
                     (SSIE_CH0_MST << SSIE_MST_SHIFT) |
                     (SSIE_CH0_SWL << SSIE_SWL_SHIFT) |
                     (SSIE_CH0_DWL << SSIE_DWL_SHIFT) |
                     (SSIE_CH0_FRM << SSIE_FRM_SHIFT));
            ssifcr = (SSIE_CH0_BSW << SSIE_BSW_SHIFT);
            ssiscr = ((SSIE_CH0_TDES << SSIE_TDES_SHIFT) |
                      (SSIE_CH0_RDFS << SSIE_RDFS_SHIFT));
            ssiofr = (SSIE_CH0_OMOD << SSIE_OMOD_SHIFT);

            if (SSIE_SSICR_MST_ON == SSIE_CH0_MST)
            {
                ssicr  = (ssicr  | (SSIE_CH0_CKS << SSIE_CKS_SHIFT));
                ssicr  = (ssicr  | (SSIE_CH0_CKDV << SSIE_CKDV_SHIFT));
                ssifcr = (ssifcr | (SSIE_CH0_AUCKE << SSIE_AUCKE_SHIFT));
                ssiofr = (ssiofr | (SSIE_BCKASTP_ON << SSIE_BCKASTP_SHIFT));
            }

            p_ssi_reg = &(SSIE0);
        break;

#ifdef SSIE1 /* activates when using MCU with SSIE1 */
        case SSI_CH1:
            //if (false == R_BSP_HardwareLock(BSP_LOCK_SSIE1))
            //{
            //    return SSI_ERR_CHANNEL;
            //}

            /* logical operation to make value to set ssi register  */
            ssicr = ((SSIE_CH1_DEL << SSIE_DEL_SHIFT) |
                     (SSIE_CH1_PDTA << SSIE_PDTA_SHIFT) |
                     (SSIE_CH1_SDTA << SSIE_SDTA_SHIFT) |
                     (SSIE_CH1_SPDP << SSIE_SPDP_SHIFT) |
                     (SSIE_CH1_LRCKP << SSIE_LRCKP_SHIFT) |
                     (SSIE_CH1_BCKP << SSIE_BCKP_SHIFT) |
                     (SSIE_CH1_MST << SSIE_MST_SHIFT) |
                     (SSIE_CH1_SWL << SSIE_SWL_SHIFT) |
                     (SSIE_CH1_DWL << SSIE_DWL_SHIFT) |
                     (SSIE_CH1_FRM << SSIE_FRM_SHIFT));
            ssifcr = (SSIE_CH1_BSW << SSIE_BSW_SHIFT);
            ssiscr = ((SSIE_CH1_TDES << SSIE_TDES_SHIFT) |
                      (SSIE_CH1_RDFS << SSIE_RDFS_SHIFT));
            ssiofr = (SSIE_CH1_OMOD << SSIE_OMOD_SHIFT);

            if (SSIE_SSICR_MST_ON == SSIE_CH1_MST)
            {
                ssicr  = (ssicr  | (SSIE_CH1_CKS << SSIE_CKS_SHIFT));
                ssicr  = (ssicr  | (SSIE_CH1_CKDV << SSIE_CKDV_SHIFT));
                ssifcr = (ssifcr | (SSIE_CH1_AUCKE << SSIE_AUCKE_SHIFT));
                ssiofr = (ssiofr | (SSIE_BCKASTP_ON << SSIE_BCKASTP_SHIFT));
            }

            p_ssi_reg = &(SSIE1);
        break;
#endif

        default:
            return SSI_ERR_PARAM;
    }

    /* Open operation mainbody */
    ssi_module_stop (Channel, SSIE_MSTP_CLR);

    /* reset SSI peripheral */
    p_ssi_reg->SSIFCR.BIT.SSIRST = SSIE_SSIFCR_SSIRST_ENABLE; /* sets SSIRST bit to "1" */
    p_ssi_reg->SSIFCR.BIT.SSIRST = SSIE_SSIFCR_SSIRST_DISABLE; /* clears SSIRST bit to "0" */

    timeout = SSIE_TIMEOUT_416USEC; /* initializes timeout counter. */
    /* WAIT_LOOP */
    while( SSIE_SSIFCR_SSIRST_DISABLE != p_ssi_reg->SSIFCR.BIT.SSIRST ) /* waits till SSIRST to be "0" */
    {
        /* Check loop count to detect abnormal condition. */
        timeout = ssi_down_count ( timeout );
        if ( 0 == timeout )
        {
            return SSI_ERR_EXCEPT; /* returns abnormal condition. */
        }
    }

    /* Set SSICR, SSIFCR, SSIOFR register */
    p_ssi_reg->SSICR.WORD  = 0u;
    p_ssi_reg->SSIFCR.WORD = 0u;
    p_ssi_reg->SSISCR.WORD = 0u;
    p_ssi_reg->SSIOFR.WORD = 0u;

    /* Set SSICR, SSIFCR, SSIOFR register */
    p_ssi_reg->SSICR.WORD  |= ssicr;
    p_ssi_reg->SSIFCR.WORD |= ssifcr;
    p_ssi_reg->SSISCR.WORD |= ssiscr;
    p_ssi_reg->SSIOFR.WORD |= ssiofr;

    return SSI_SUCCESS;
}

/******************************************************************************
End of function  SSI_Open
******************************************************************************/

/**********************************************************************************************************************
 * Function Name: SSI_Start
 ******************************************************************************************************************//**
 * @brief Enables PCM data transmit and/or receive operations for a specified SSI channel.
 * @param[in] Channel It specifies an SSI channel to enable PCM data transmit and/or receive operations. Choose one
 * enumerator member from the enumerator typedef ssi_ch_t. It is described in file ssi_api_rx_if.h.
 * @retval SSI_SUCCESS Successful, PCM data transmit and/or receive operations are enabled for the specified SSI channel.
 * @retval SSI_ERR_PARAM Not successful, the parameter is illegal.
 * @retval SSI_ERR_CHANNEL Not successful, the specified SSI channel has not been locked.
 * @details Call this function to enable PCM data transmit and/or receive operation with a specified SSI channel.
 * @note -
 */
ssi_ret_t SSI_Start ( const ssi_ch_t Channel )
{
    ssi_ret_t ret = SSI_SUCCESS;
    volatile struct st_ssie *p_ssi_reg;
    uint32_t dummy;         /* valiable for dummy reading to write SSIFSR, SSISR. */
    uint32_t timeout;
    uint8_t word_num_per_sample;

    /* parameter & hardware lock checking operation */
    ret = ssi_check_param (Channel);
    if (SSI_SUCCESS != ret)  /* parameters are valid. */
    {
        return ret;
    }

    /* getting ssi register address */
    p_ssi_reg = (volatile struct st_ssie *)ssi_get_ssi_address [Channel];

    /* SSIE operation state confirmation, is it Idle state? */
    timeout = SSIE_TIMEOUT_416USEC;
    /* WAIT_LOOP */
    while ( SSIE_SSISR_IIRQ_OFF == p_ssi_reg->SSISR.BIT.IIRQ )
    {
        /* Check loop count to detect abnormal condition. */
        timeout = ssi_down_count ( timeout );
        if ( 0 == timeout )
        {
            return SSI_ERR_EXCEPT; /* returns abnormal condition. */
        }
    }

    word_num_per_sample = ssi_get_word_num_per_sample(p_ssi_reg);

    /* SSI Start operation */
    switch (ssi_get_iomode [Channel])
    {
        case SSIE_IO_MODE_TX: /* case SSI transmit mode */
            if (SSIE_SSICR_TEN_DISABLE != p_ssi_reg->SSICR.BIT.TEN)
            {
                return SSI_ERR_EXCEPT;
            }

            /* Tx FIFO Reset */
            p_ssi_reg->SSIFCR.BIT.TFRST = SSIE_SSIFCR_TFRST_ENABLE;
            p_ssi_reg->SSIFCR.BIT.TFRST = SSIE_SSIFCR_TFRST_DISABLE;

            timeout = SSIE_TIMEOUT_416USEC; /* initializes timeout counter. */
            /* WAIT_LOOP */
            while( SSIE_SSIFCR_TFRST_DISABLE != p_ssi_reg->SSIFCR.BIT.TFRST ) /* waits till TFRST to be "0" */
            {
                /* Check loop count to detect abnormal condition. */
                timeout = ssi_down_count ( timeout );
                if ( 0 == timeout )
                {
                    return SSI_ERR_EXCEPT; /* returns abnormal condition. */
                }
            }

#if 0
            /* Write 0 to Tx FIFO */
            if(6 == word_num_per_sample)
            {
	            ssi_write_zero_to_tx_fifo(p_ssi_reg, 30);
	        }
	        else
	        {
	            ssi_write_zero_to_tx_fifo(p_ssi_reg, SSIE_SSIFSR_TDCMAX);
	        }
#endif

            /* SSIFSR, SSISR Initialize */
            dummy = p_ssi_reg->SSIFSR.WORD;       /* dummy reading is needed to write SSIFSR. */
            p_ssi_reg->SSIFSR.WORD = 0u;
            dummy = p_ssi_reg->SSISR.WORD;        /* dummy reading is needed to write SSISR. */
            p_ssi_reg->SSISR.WORD = 0u;
            dummy; /* This code occurs a compilation warning but does not affect actual operation. */

            /* Setting to start SSI Tx */
            p_ssi_reg->SSIFCR.BIT.TIE = SSIE_SSIFCR_TIE_ENABLE;
            p_ssi_reg->SSICR.WORD |= ((SSIE_SSICR_TUIEN_ENABLE << SSIE_TUIEN_SHIFT) |
                                      (SSIE_SSICR_TOIEN_ENABLE << SSIE_TOIEN_SHIFT) |
                                      (SSIE_SSICR_TEN_ENABLE << SSIE_TEN_SHIFT));
        break;

        case SSIE_IO_MODE_RX: /* case SSI receive mode */
            if (SSIE_SSICR_REN_DISABLE != p_ssi_reg->SSICR.BIT.REN)
            {
                return SSI_ERR_EXCEPT;
            }

            /* Rx FIFO Reset */
            p_ssi_reg->SSIFCR.BIT.RFRST = SSIE_SSIFCR_RFRST_ENABLE;
            p_ssi_reg->SSIFCR.BIT.RFRST = SSIE_SSIFCR_RFRST_DISABLE;

            timeout = SSIE_TIMEOUT_416USEC; /* initializes timeout counter. */
            /* WAIT_LOOP */
            while( SSIE_SSIFCR_RFRST_DISABLE != p_ssi_reg->SSIFCR.BIT.RFRST ) /* waits till RFRST to be "0" */
            {
                /* Check loop count to detect abnormal condition. */
                timeout = ssi_down_count ( timeout );
                if ( 0 == timeout )
                {
                    return SSI_ERR_EXCEPT; /* returns abnormal condition. */
                }
            }

            /* SSIFSR, SSISR Initialize */
            dummy = p_ssi_reg->SSIFSR.WORD;       /* dummy reading is needed to write SSIFSR. */
            p_ssi_reg->SSIFSR.WORD = 0u;
            dummy = p_ssi_reg->SSISR.WORD;        /* dummy read is needed to write SSISR. */
            p_ssi_reg->SSISR.WORD = 0u;
            dummy; /* This code occurs a compilation warning but does not affect actual operation. */

            /* Setting to start SSI Rx */
            p_ssi_reg->SSIFCR.BIT.RIE = SSIE_SSIFCR_RIE_ENABLE;
            p_ssi_reg->SSICR.WORD |= ((SSIE_SSICR_RUIEN_ENABLE << SSIE_RUIEN_SHIFT) |
                                      (SSIE_SSICR_ROIEN_ENABLE << SSIE_ROIEN_SHIFT) |
                                      (SSIE_SSICR_REN_ENABLE));
        break;

        case SSIE_IO_MODE_TR: /* case SSI transmit & receive mode */
            if (SSIE_IO_MODE_NONE != (p_ssi_reg->SSICR.WORD & SSIE_IO_MODE_TR))
            {
                return SSI_ERR_EXCEPT;
            }

            /* Tx FIFO, Rx FIFO Reset */
            p_ssi_reg->SSIFCR.WORD |= ((SSIE_SSIFCR_TFRST_ENABLE << SSIE_TFRST_SHIFT) |
                                       (SSIE_SSIFCR_RFRST_ENABLE));
            p_ssi_reg->SSIFCR.WORD &= ~((SSIE_SSIFCR_TFRST_ENABLE << SSIE_TFRST_SHIFT) |
                                        (SSIE_SSIFCR_RFRST_ENABLE));

            timeout = SSIE_TIMEOUT_416USEC; /* initializes timeout counter. */

            /* WAIT_LOOP */
            while( SSIE_SSIFCR_TFRST_DISABLE != p_ssi_reg->SSIFCR.BIT.TFRST ) /* waits till TFRST to be "0" */
            {
                /* Check loop count to detect abnormal condition. */
                timeout = ssi_down_count ( timeout );
                if ( 0 == timeout )
                {
                    return SSI_ERR_EXCEPT; /* returns abnormal condition. */
                }
            }

            timeout = SSIE_TIMEOUT_416USEC; /* initializes timeout counter. */

            /* WAIT_LOOP */
            while( SSIE_SSIFCR_RFRST_DISABLE != p_ssi_reg->SSIFCR.BIT.RFRST ) /* waits till RFRST to be "0" */
            {
                /* Check loop count to detect abnormal condition. */
                timeout = ssi_down_count ( timeout );
                if ( 0 == timeout )
                {
                    return SSI_ERR_EXCEPT; /* returns abnormal condition. */
                }
            }

#if 0
            /* Write 0 to Tx FIFO */
            if(6 == word_num_per_sample)
            {
	            ssi_write_zero_to_tx_fifo(p_ssi_reg, 30);
	        }
	        else
	        {
	            ssi_write_zero_to_tx_fifo(p_ssi_reg, SSIE_SSIFSR_TDCMAX);
	        }
#endif

            /* SSIFSR, SSISR clear to "0". */
            dummy = p_ssi_reg->SSIFSR.WORD;       /* dummy reading is needed to write SSIFSR. */
            p_ssi_reg->SSIFSR.WORD = 0u;
            dummy = p_ssi_reg->SSISR.WORD;        /* dummy reading is needed to write SSISR. */
            p_ssi_reg->SSISR.WORD = 0u;
            dummy; /* This code occurs a compilation warning but does not affect actual operation. */

            /* Setting to start SSI Tx, Rx */
            p_ssi_reg->SSIFCR.WORD |= ((SSIE_SSIFCR_TIE_ENABLE << SSIE_TIE_SHIFT) |
                                       (SSIE_SSIFCR_RIE_ENABLE << SSIE_RIE_SHIFT));
            p_ssi_reg->SSICR.WORD |= ((SSIE_SSICR_TUIEN_ENABLE << SSIE_TUIEN_SHIFT) |
                                      (SSIE_SSICR_TOIEN_ENABLE << SSIE_TOIEN_SHIFT) |
                                      (SSIE_SSICR_RUIEN_ENABLE << SSIE_RUIEN_SHIFT) |
                                      (SSIE_SSICR_ROIEN_ENABLE << SSIE_ROIEN_SHIFT) |
                                      (SSIE_SSICR_IIEN_ENABLE << SSIE_IIEN_SHIFT) |
                                      (SSIE_SSICR_TEN_ENABLE << SSIE_TEN_SHIFT) |
                                      (SSIE_SSICR_REN_ENABLE));
        break;

        default:
            return SSI_ERR_CHANNEL;
    }

    timeout = SSIE_TIMEOUT_416USEC;
    /* WAIT_LOOP */
    while ( SSIE_SSISR_IIRQ_ON == p_ssi_reg->SSISR.BIT.IIRQ )
    {
        /* Check loop count to detect abnormal condition. */
        timeout = ssi_down_count ( timeout );
        if ( 0 == timeout )
        {
            return SSI_ERR_EXCEPT; /* returns abnormal condition. */
        }
    }

    return SSI_SUCCESS;
}
/******************************************************************************
End of function  SSI_Start
******************************************************************************/

/**********************************************************************************************************************
 * Function Name: SSI_Stop
 ******************************************************************************************************************//**
 * @brief Disables PCM data transmit and/or receive operations for a specified SSI channel.
 * @param[in] Channel It specifies an SSI channel to disable PCM data transmit and/or receive operations. Choose one
 * enumerator member from the enumerator typedef ssi_ch. It is described in file ssi_api_rx_if.h.
 * @retval SSI_SUCCESS Successful, PCM data transmit and/or receive operations are disabled for the specified SSI channel.
 * @retval SSI_ERR_PARAM Not successful, the parameter is illegal.
 * @retval SSI_ERR_CHANNEL Not successful, the specified SSI channel has not been locked.
 * @retval SSI_ERR_EXCEPT Not successful, the specified SSI channel is in unwanted hardware condition.
 * @details Call this function to disable PCM data transmit and/or receive operation with a specified SSI channel.
 * @note -
 */
ssi_ret_t SSI_Stop(const ssi_ch_t Channel)
{
    ssi_ret_t ret = SSI_SUCCESS;
    uint32_t timeout;
    volatile struct st_ssie *p_ssi_reg;
    uint8_t word_num_per_sample;

    /* parameter & hardware lock checking operation */
    ret = ssi_check_param (Channel);
    if (SSI_SUCCESS != ret)  /* parameters are valid. */
    {
        return ret;
    }

    /* stop operation mainbody */
    /* getting ssi register address */
    p_ssi_reg = (volatile struct st_ssie *)ssi_get_ssi_address [Channel];

    /* SSIE operation state confirmation, is it Transfer state? */
    timeout = SSIE_TIMEOUT_416USEC;
    /* WAIT_LOOP */
    while ( SSIE_SSISR_IIRQ_ON == p_ssi_reg->SSISR.BIT.IIRQ )
    {
        /* Check loop count to detect abnormal condition. */
        timeout = ssi_down_count ( timeout );
        if ( 0 == timeout )
        {
            return SSI_ERR_EXCEPT; /* returns abnormal condition. */
        }
    }

    word_num_per_sample = ssi_get_word_num_per_sample(p_ssi_reg);

    /* SSI Stop operation */
    switch (ssi_get_iomode [Channel])
    {
        case SSIE_IO_MODE_TX: /* case SSI transmit mode */
            if (SSIE_SSICR_TEN_ENABLE != p_ssi_reg->SSICR.BIT.TEN)
            {
                /* Exception Error */
                return SSI_ERR_EXCEPT;
            }

            /* procedure to disable SSI transmit operation. */
            p_ssi_reg->SSICR.WORD &= ~((SSIE_SSICR_TUIEN_ENABLE << SSIE_TUIEN_SHIFT) |
                                       (SSIE_SSICR_TOIEN_ENABLE << SSIE_TOIEN_SHIFT));
            p_ssi_reg->SSIFCR.BIT.TIE = SSIE_SSIFCR_TIE_DISABLE;

            /* WAIT_LOOP */
            while (p_ssi_reg->SSIFSR.BIT.TDC >= (SSIE_SSIFSR_TDCMAX -  word_num_per_sample))
            {
                /* Exception Check */
                if (SSIE_SSISR_IIRQ_ON == p_ssi_reg->SSISR.BIT.IIRQ)
                {
                    /* Exception Error */
                    return SSI_ERR_EXCEPT;
                }
            }

            /* Write 0 to Tx FIFO */
            ssi_write_zero_to_tx_fifo(p_ssi_reg, (int32_t)word_num_per_sample);

            timeout = SSIE_TIMEOUT_416USEC;

            /* WAIT_LOOP */
            while (SSIE_SSISR_TUIRQ_OFF == p_ssi_reg->SSISR.BIT.TUIRQ)
            {
                /* Check loop count to detect abnormal condition. */
                timeout = ssi_down_count ( timeout );
                if ( 0 == timeout )
                {
                    /* Return from abnormal condition. */
                    return SSI_ERR_EXCEPT;
                }
            }

            /* disable SSI transmit operation  */
            p_ssi_reg->SSICR.BIT.TEN = SSIE_SSICR_TEN_DISABLE;
            ssi_clear_flag_tuirq( p_ssi_reg );
        break;

        case SSIE_IO_MODE_RX: /* case SSI receive mode */
            if (SSIE_SSICR_REN_ENABLE != p_ssi_reg->SSICR.BIT.REN)
            {
                /* Exception Error */
                return SSI_ERR_EXCEPT;
            }

            /* disable SSI receive operation. */
            p_ssi_reg->SSICR.WORD &= ~((SSIE_SSICR_RUIEN_ENABLE << SSIE_RUIEN_SHIFT) |
                                       (SSIE_SSICR_ROIEN_ENABLE << SSIE_ROIEN_SHIFT) |
                                       (SSIE_SSICR_REN_ENABLE));

            /* disable SSI receive operation  */
            p_ssi_reg->SSIFCR.BIT.RIE = SSIE_SSIFCR_RIE_DISABLE;
        break;

        case SSIE_IO_MODE_TR: /* case SSI transmit & receive mode */
            if (SSIE_IO_MODE_TR != (p_ssi_reg->SSICR.WORD & SSIE_IO_MODE_TR))
            {
                /* Exception Error */
                p_ssi_reg->SSICR.WORD &= ~((SSIE_SSICR_TEN_ENABLE << SSIE_TEN_SHIFT) |
                                           (SSIE_SSICR_REN_ENABLE)); /* execution order doesn't affect result */
                return SSI_ERR_EXCEPT;
            }

            /* Procedure to disable SSI transmit operation.
               Receive operation is disabled here.
            */
#if 0
            p_ssi_reg->SSICR.WORD &= ~((SSIE_SSICR_TUIEN_ENABLE << SSIE_TUIEN_SHIFT) |
                                       (SSIE_SSICR_TOIEN_ENABLE << SSIE_TOIEN_SHIFT) |
                                       (SSIE_SSICR_RUIEN_ENABLE << SSIE_RUIEN_SHIFT) |
                                       (SSIE_SSICR_ROIEN_ENABLE << SSIE_ROIEN_SHIFT) |
                                       (SSIE_SSICR_REN_ENABLE));
            p_ssi_reg->SSIFCR.WORD &= ~((SSIE_SSIFCR_TIE_ENABLE << SSIE_TIE_SHIFT) |
                                        (SSIE_SSIFCR_RIE_ENABLE << SSIE_RIE_SHIFT));
#else
            p_ssi_reg->SSICR.WORD &= ~((SSIE_SSICR_TUIEN_ENABLE << SSIE_TUIEN_SHIFT) |
                                       (SSIE_SSICR_TOIEN_ENABLE << SSIE_TOIEN_SHIFT));
            p_ssi_reg->SSIFCR.BIT.TIE = SSIE_SSIFCR_TIE_DISABLE;
#endif

            /* wait until Tx FIFO becomes the underflow */
            /* WAIT_LOOP */
            while (p_ssi_reg->SSIFSR.BIT.TDC >= (SSIE_SSIFSR_TDCMAX -  word_num_per_sample))
            {
                /* Exception Check */
                if (SSIE_SSISR_IIRQ_ON == p_ssi_reg->SSISR.BIT.IIRQ)
                {
                    /* Exception Error */
                    return SSI_ERR_EXCEPT;
                }
            }

            /* Write 0 to Tx FIFO */
            ssi_write_zero_to_tx_fifo(p_ssi_reg, (int32_t)word_num_per_sample);

            timeout = SSIE_TIMEOUT_416USEC;

            /* WAIT_LOOP */
            while (SSIE_SSISR_TUIRQ_OFF == p_ssi_reg->SSISR.BIT.TUIRQ)
            {
                /* Check loop count to detect abnormal condition. */
                timeout = ssi_down_count ( timeout );
                if ( 0 == timeout )
                {
                    /* Return from abnormal condition. */
                    return SSI_ERR_EXCEPT;
                }
            }

            /* disable SSI receive operation. */
            p_ssi_reg->SSICR.WORD &= ~((SSIE_SSICR_RUIEN_ENABLE << SSIE_RUIEN_SHIFT) |
                                       (SSIE_SSICR_ROIEN_ENABLE << SSIE_ROIEN_SHIFT) |
                                       (SSIE_SSICR_REN_ENABLE));

            /* disable SSI receive operation */
            p_ssi_reg->SSIFCR.BIT.RIE = SSIE_SSIFCR_RIE_DISABLE;

            /* disable SSI transmit operation  */
            p_ssi_reg->SSICR.BIT.TEN = SSIE_SSICR_TEN_DISABLE;
            ssi_clear_flag_tuirq( p_ssi_reg );
        break;

        default:
            ret = SSI_ERR_CHANNEL;
        break;
    }

    /* Wait operation for IIRQ to be set. */
    if ( SSI_SUCCESS != ret )
    {
        return ret;
    }

    /* Wait until Idle mode Interrrupt status Flag to be set. */
    /* initialize timeout counter. */
    timeout = SSIE_TIMEOUT_416USEC;

    /* WAIT_LOOP */
    while ( SSIE_SSISR_IIRQ_OFF == p_ssi_reg->SSISR.BIT.IIRQ )
    {
        /* Check loop count to detect abnormal condition. */
        timeout = ssi_down_count ( timeout );
        if ( 0u == timeout )
        {
            /* Return from abnormal condition. */
            return SSI_ERR_EXCEPT;
        }
    }

   return SSI_SUCCESS;
}
/******************************************************************************
End of function  SSI_Stop
******************************************************************************/

/**********************************************************************************************************************
 * Function Name: SSI_Close
 ******************************************************************************************************************//**
 * @brief Unlocks to release a specified SSI channel.
 * @param[in] Channel It specifies an SSI channel to release. Choose one enumerator member from the enumerator typedef
 * ssi_ch_t. It is described in file ssi_api_rx_if.h.
 * @retval SSI_SUCCESS Successful, the specified SSI channel is released.
 * @retval SSI_ERR_PARAM Not successful, the parameter is illegal.
 * @retval SSI_ERR_CHANNEL Not successful, the specified SSI channel can't be unlocked or has not been locked.
 * @details Call this function when finish to use a specified SSI channel.
 * @note -
 */
ssi_ret_t SSI_Close(const ssi_ch_t Channel)
{
    ssi_ret_t ret = SSI_SUCCESS;
    uint32_t timeout;
    uint32_t dummy;         /* valiable for dummy reading to write SSIFSR, SSISR. */
    volatile struct st_ssie *p_ssi_reg;

    /* parameter & hardware lock checking operation */
    ret = ssi_check_param (Channel);
    if (SSI_SUCCESS != ret)  /* parameters are valid. */
    {
        return ret;
    }

    /* getting ssi register address */
    p_ssi_reg = (volatile struct st_ssie *)ssi_get_ssi_address [Channel];

    timeout = SSIE_TIMEOUT_416USEC;

    /* WAIT_LOOP */
    while ( SSIE_SSISR_IIRQ_OFF == p_ssi_reg->SSISR.BIT.IIRQ )
    {
        /* Check loop count to detect abnormal condition. */
        timeout = ssi_down_count ( timeout );
        if ( 0 == timeout )
        {
            return SSI_ERR_EXCEPT; /* returns abnormal condition. */
        }
    }

    /*  'Set reset value to registers.
        'This operation sets AUCKE disabled.
        'Clear operation for FIFOs is not executed,
           because FIFOs are filled with "0" after SSI_Stop()
           operation at this moment. So that FIFO underflow &
           overflow will not be arisen.
    */
    /* turn registers to default value */
    p_ssi_reg->SSICR.WORD = 0u;
    p_ssi_reg->SSIFCR.WORD = 0u;
    p_ssi_reg->SSISCR.WORD = 0u;
    p_ssi_reg->SSIOFR.WORD = 0u;

    dummy = p_ssi_reg->SSIFSR.WORD;
    p_ssi_reg->SSIFSR.WORD = 0u;
    dummy = p_ssi_reg->SSISR.WORD;
    p_ssi_reg->SSISR.WORD = 0;
    dummy; /* This code occurs a compilation warning but does not affect actual operation. */

    /* Stop feeding clock to SSI peripheral to deactivate it. */
    ssi_module_stop (Channel, SSIE_MSTP_SET);

    switch (Channel)
    {

        /* release HW lock to close SSI driver. */
        case SSI_CH0:
            //if (false == R_BSP_HardwareUnlock(BSP_LOCK_SSIE0)) /* Unlock to close SSI driver */
            //{
            //    /* case Unlock failure */
            //    ret = SSI_ERR_CHANNEL;
            //}
        break;

#ifdef SSIE1 /* activates when using MCU with SSIE1 */
        case SSI_CH1:
            //if (false == R_BSP_HardwareUnlock(BSP_LOCK_SSIE1)) /* Unlock to close SSI driver */
            //{
            //    /* case Unlock failure */
            //    ret = SSI_ERR_CHANNEL;
            //}
        break;
#endif

        default:
            /* no operation */
        break;
    }

    return ret;
}
/******************************************************************************
End of function  SSI_Close
******************************************************************************/

/**********************************************************************************************************************
 * Function Name: SSI_Write
 ******************************************************************************************************************//**
 * @brief Writes PCM data to a specified SSI channel for transmit operation. For the operation, adequate amount of
 * buffer memory must be declared in user application software.
 * @param[in] Channel It specifies an SSI channel to write PCM data. Choose one enumerator member from the enumerator
 * typedef ssi_ch_t. It is described in file ssi_api_rx_if.h.
 * @param[in] pBuf It specifies the beginning address of PCM buffer memory storing PCM data to writes to Transmit FIFO
 * Data Register.
 * @param[in] Samples It specifies the request number of PCM data samples to write to Transmit FIFO Data Register.
 * @return The number of written samples: Shows the number of PCM data samples written to Transmit FIFO Data
 * Register of a specified SSI channel.
 * @retval SSI_ERR_PARAM Not successful, the parameter is illegal.
 * @retval SSI_ERR_CHANNEL Not successful, the specified SSI channel has not been locked. Or the SSI channel
 * is configured for receive operation.
 * @retval SSI_ERR_EXCEPT Not successful, the specified SSI channel is in unwanted hardware condition.
 * @details Call this function to write PCM data to a specified SSI channel's Transmit FIFO Data Register.
 * @note that SSI_Write() should be called repeatedly to write PCM data to the specified SSI channel during
 * transmit operation.
 */
int8_t SSI_Write( const ssi_ch_t Channel,
                    const  void * pBuf,
                    const  uint8_t Samples)
{
    int8_t ret = SSI_SUCCESS;
    volatile struct st_ssie *p_ssi_reg;
    uint32_t fifo_free;     /* holds the number of free memory in Tx FIFO */
    uint32_t request;       /* holds the number of times to write-access by request.*/
    uint32_t limit;         /* holds the number of times to write-access to Tx FIFO. */
    uint32_t count = 0u;   /* The number of times Tx FIFO was accessed. */
    uint8_t word_num_per_sample;

    /* parameter check operation */
    ret = ssi_check_param_buf (Channel, pBuf, Samples);
    if (SSI_SUCCESS != ret)  /* parameters are valid. */
    {
        return ret;
    }

    /* write operation mainbody */
    /* SSI Write */
    if (SSIE_IO_MODE_RX == ssi_get_iomode [Channel])
    {
        return SSI_ERR_CHANNEL;
    }

    /* getting ssi register address */
    p_ssi_reg = (volatile struct st_ssie *)ssi_get_ssi_address [Channel];

    word_num_per_sample = ssi_get_word_num_per_sample(p_ssi_reg);

    /* Process to write PCM data to Tx FIFO */
    /* Calculate the number of free memory in Tx FIFO. */
    fifo_free = SSIE_SSIFSR_TDCMAX - p_ssi_reg->SSIFSR.BIT.TDC;
    if (0u == fifo_free)
    {
        /* return because Tx FIFO is full. */
        return 0u;
    }

    /* Calculate time to write-access just corresponding to the "Samples". */
    request = ((uint32_t)Samples) * ((uint32_t)word_num_per_sample);

    /* Limit operation for times to write-accecss to Tx FIFO. */
    if (fifo_free <= request)
    {
        /* case, the number of free memory of Tx FIFO is larger than request. */
        limit = fifo_free;
    }
    else
    {
        /* case, the number of free memory of Tx FIFO is smaller than request. */
        limit = request;
    }

    limit = limit - (limit % word_num_per_sample);

    /* WAIT_LOOP */
    while (limit > count)
    {
        if (SSIE_SSICR_DWL08 == p_ssi_reg->SSICR.BIT.DWL)
        {
            p_ssi_reg->SSIFTDR.BYTE = *((const uint8_t *)pBuf);
            pBuf = ((const uint8_t *)pBuf) + 1u;
        }
        else if (SSIE_SSICR_DWL16 == p_ssi_reg->SSICR.BIT.DWL)
        {
            p_ssi_reg->SSIFTDR.HALF = *((const uint16_t *)pBuf);
            pBuf = ((const uint16_t *)pBuf) + 1u;
        }
        else
        {
            p_ssi_reg->SSIFTDR.WORD = *((const uint32_t *)pBuf);
            pBuf = ((const uint32_t *)pBuf) + 1u;
        }

        count++;
    }

    /* Clear Tx FIFO empty flag */
    ssi_clear_flag_tde( p_ssi_reg );

    /* Convert the number of FIFO to be plactically written
         in Tx FIFO into the number of Samples */
    ret = (int8_t)(count / word_num_per_sample);

    return ret;
}
/******************************************************************************
End of function  SSI_Write
******************************************************************************/

/**********************************************************************************************************************
 * Function Name: SSI_Read
 ******************************************************************************************************************//**
 * @brief Reads PCM data from a specified SSI channel for receive operation. For the operation, adequate amount of
 * buffer memory must be declared in user application software.
 * @param[in] Channel It specifies an SSI channel to read PCM data. Choose one enumerator member from the enumerator
 * typedef ssi_ch_t. It is described in file ssi_api_rx_if.h.
 * @param[out] pBuf It specifies the beginning address of buffer memory storing PCM data read from Receive FIFO Data
 * Register.
 * @param[in] Samples It specifies the request number of PCM data samples to read from Receive FIFO Data Register.
 * @return The number of read samples: Shows the number of PCM data samples read from Receive FIFO Data
 * Register of a specified SSI channel.
 * @retval SSI_ERR_PARAM Not successful, the parameter is illegal.
 * @retval SSI_ERR_CHANNEL Not successful, the specified SSI channel has not been locked. Or returns
 * SSI_ERR_CHANNEL when the SSI channel is configured for transmit operation.
 * @retval SSI_ERR_EXCEPT Not successful, the specified SSI channel is in unwanted hardware condition.
 * @details Call this function to read PCM data from a specified SSI channel's Receive FIFO Data Register.
 * @note that SSI_Read() should be called repeatedly to read PCM data from the specified SSI channel
 * during receive operation.
 */
int8_t SSI_Read( const ssi_ch_t Channel,
                    void * pBuf,
                    const uint8_t Samples)
{
    int8_t ret = SSI_SUCCESS;
    volatile struct st_ssie *p_ssi_reg;
    uint32_t fifo_filled;   /* holds the number of filled memory in Rx FIFO */
    uint32_t request;       /* holds the number of times to read-access by request.*/
    uint32_t limit;         /* holds the number of times to read-access to Rx FIFO. */
    uint32_t count = 0u;   /* The number of times Tx FIFO was accessed. */
    uint8_t word_num_per_sample;

    /* parameter check operation */
    ret = ssi_check_param_buf (Channel, pBuf, Samples);
    if (SSI_SUCCESS != ret)  /* parameters are valid. */
    {
        return ret;
    }

    /* read operation mainbody */
    if (SSIE_IO_MODE_TX == ssi_get_iomode [Channel])
    {
        return SSI_ERR_CHANNEL;
    }

    /* getting ssi register address */
    p_ssi_reg = (volatile struct st_ssie *)ssi_get_ssi_address [Channel];

    word_num_per_sample = ssi_get_word_num_per_sample(p_ssi_reg);

    /* Process to read PCM data from Rx FIFO */
    /* Get the number of filled memory in Rx FIFO. */
    fifo_filled = p_ssi_reg->SSIFSR.BIT.RDC;
    if (0u == fifo_filled)
    {
        /* return because Rx FIFO is empty. */
        return 0u;
    }

    /* Calculate time to read-access just corresponding to the "Samples". */
    request = ((uint32_t)Samples) * ((uint32_t)word_num_per_sample);

    /* Limit operation for times to read-accecss to Rx FIFO. */
    if (fifo_filled <= request)
    {
        /* case, the number of filled memory of FIFO is smaller than request. */
        limit = fifo_filled;
    }
    else
    {
        /* case, the number of filled memory of FIFO is larger than request. */
        limit = request;
    }

    limit = limit - (limit % word_num_per_sample);

    /* WAIT_LOOP */
    while (limit > count)
    {
        if (SSIE_SSICR_DWL08 == p_ssi_reg->SSICR.BIT.DWL)
        {
            *((uint8_t *)pBuf) = p_ssi_reg->SSIFRDR.BYTE;
            pBuf = ((uint8_t *)pBuf) + 1u;
        }
        else if (SSIE_SSICR_DWL16 == p_ssi_reg->SSICR.BIT.DWL)
        {
            *((uint16_t *)pBuf) = p_ssi_reg->SSIFRDR.HALF;
            pBuf = ((uint16_t *)pBuf) + 1u;
        }
        else
        {
            *((uint32_t *)pBuf) = p_ssi_reg->SSIFRDR.WORD;
            pBuf = ((uint32_t *)pBuf) + 1u;
        }

        count++;
    }

    /* Clear Rx FIFO full flag */
    ssi_clear_flag_rdf( p_ssi_reg );

    /* Convert the number of FIFO to be plactically read
       from Rx FIFO into the number of Samples */
    ret = (int8_t)(count / word_num_per_sample);

    return ret;
}
/******************************************************************************
End of function  SSI_Read
******************************************************************************/

/**********************************************************************************************************************
 * Function Name: SSI_Mute
 ******************************************************************************************************************//**
 * @brief Sets or releases mute on a specified SSI channel during transmit operation.
 * During mute, the transmitting PCM data of the specified SSI channel is turned 0.
 * @param[in] Channel It specifies an SSI channel to set or release mute. Choose one enumerator member from the
 * enumerator typedef ssi_ch_t. It is described in file ssi_api_rx_if.h.
 * @param[in] OnOff It specifies to set or release mute. Choose one enumerator member from the enumerator typedef
 * ssi_mute_t. It is described in file ssi_api_rx_if.h.
 * @retval SSI_SUCCESS Successful, for the specified SSI channel.
 * @retval SSI_ERR_PARAM Not successful, the parameter is illegal.
 * @retval SSI_ERR_CHANNEL Not successful, the specified SSI channel has not been locked. Or the SSI channel
 * is configured for operations other than transmit.
 * @retval SSI_ERR_EXCEPT Not successful, the specified SSI channel is in unwanted hardware condition.
 * @details Call this function to set or release mute for an SSI channel during transmit operation.
 * @note -
 */
ssi_ret_t SSI_Mute(const ssi_ch_t Channel, const ssi_mute_t OnOff)
{
    uint32_t timeout;
    ssi_ret_t ret = SSI_SUCCESS;
    volatile struct st_ssie *p_ssi_reg;
    uint8_t word_num_per_sample;

    /* parameter check operation */
    ret = ssi_check_param_mute (Channel, OnOff);
    if (SSI_SUCCESS != ret)  /* parameters are valid. */
    {
        return ret;
    }

    /* mute operation mainbody */
    if (SSIE_IO_MODE_TX != ssi_get_iomode [Channel])
    {
    /* Error because Mute operation is available only for SSI_IO_MODE_TX. */
        return SSI_ERR_CHANNEL;
    }

    /* getting ssi register address */
    p_ssi_reg = (volatile struct st_ssie *)ssi_get_ssi_address [Channel];

    /* Start Mute operation. */
    word_num_per_sample = ssi_get_word_num_per_sample(p_ssi_reg);

    if (SSI_MUTE_ON == OnOff)
    {
        /* Mute on operaton (Mute assertion) */
    	if ((SSIE_SSIFCR_TIE_DISABLE == p_ssi_reg->SSIFCR.BIT.TIE) || (SSIE_SSICR_TEN_DISABLE == p_ssi_reg->SSICR.BIT.TEN))
        {
            return SSI_SUCCESS;
        }

        p_ssi_reg->SSICR.BIT.TUIEN = SSIE_SSICR_TUIEN_DISABLE;
	    p_ssi_reg->SSIFCR.BIT.TIE = SSIE_SSIFCR_TIE_DISABLE;

        /* Set LRCK/FS Continue Mode to keep LRCK/FS output */
        if (SSIE_SSICR_MST_ON == p_ssi_reg->SSICR.BIT.MST)
        {
            p_ssi_reg->SSIOFR.BIT.LRCONT = 1u;
        }

        /* WAIT_LOOP */
        while (p_ssi_reg->SSIFSR.BIT.TDC >= (SSIE_SSIFSR_TDCMAX -  word_num_per_sample))
        {
            /* Exception Check */
            if (SSIE_SSISR_IIRQ_ON == p_ssi_reg->SSISR.BIT.IIRQ)
            {
                /* Exception Error */
                return SSI_ERR_EXCEPT;
            }
        }

        /* Write 0 to Tx FIFO */
        ssi_write_zero_to_tx_fifo(p_ssi_reg, (int32_t)word_num_per_sample);

        timeout = SSIE_TIMEOUT_416USEC;

        /* WAIT_LOOP */
        while (SSIE_SSISR_TUIRQ_OFF == p_ssi_reg->SSISR.BIT.TUIRQ)
        {
            /* Check loop count to detect abnormal condition. */
            timeout = ssi_down_count ( timeout );
            if ( 0 == timeout )
            {
                /* Return from abnormal condition. */
                return SSI_ERR_EXCEPT;
            }
        }

        /* disable SSI transmit operation */
        p_ssi_reg->SSICR.BIT.TEN = SSIE_SSICR_TEN_DISABLE;
        ssi_clear_flag_tuirq( p_ssi_reg );

        /* Wait operation for IIRQ to be set. */

        /* Wait until Idle mode Interrrupt status Flag to be set. */
        /* initialize timeout counter. */
        timeout = SSIE_TIMEOUT_416USEC;

        /* WAIT_LOOP */
        while ( SSIE_SSISR_IIRQ_OFF == p_ssi_reg->SSISR.BIT.IIRQ )
        {
            /* Check loop count to detect abnormal condition. */
            timeout = ssi_down_count ( timeout );
            if ( 0u == timeout )
            {
                /* Return from abnormal condition. */
                return SSI_ERR_EXCEPT;
            }
        }
    } /* End of Mute on process */
    else
    {
        /* Mute off operaton (Mute deassertion) */
    	if ((SSIE_SSIFCR_TIE_ENABLE == p_ssi_reg->SSIFCR.BIT.TIE) || (SSIE_SSICR_TEN_ENABLE == p_ssi_reg->SSICR.BIT.TEN))
        {
            return SSI_SUCCESS;
        }

        if ( 0u != p_ssi_reg->SSIFSR.BIT.TDC)
        {
            return SSI_ERR_EXCEPT;
        }

        /*  case Tx FIFO is empty:
            Write "0" to Tx FIFO. It requires to write 8 bytes to Tx FIFO.
        */
        ssi_write_zero_to_tx_fifo(p_ssi_reg, (int32_t)word_num_per_sample);

        /*  Enable transmit operation for Mute off by TEN = SSI_SSICR_TEN_ENABLE,
            When Mute was turned ON, transmit operation is desabled.
        */
        p_ssi_reg->SSICR.BIT.TEN = SSIE_SSICR_TEN_ENABLE;

        /* Wait until Idle mode Interrrupt status Flag to be set. */
        /* initialize timeout counter. */
        timeout = SSIE_TIMEOUT_416USEC;

        /* WAIT_LOOP */
        while ( SSIE_SSISR_IIRQ_ON == p_ssi_reg->SSISR.BIT.IIRQ )
        {
            /* Check loop count to detect abnormal condition. */
            timeout = ssi_down_count ( timeout );
            if ( 0 == timeout )
            {
                return SSI_ERR_EXCEPT;  /* Return from abnormal condition. */
            }
        }

        /* Reset LRCK/FS Continue Mode (it should depend on config.h !!) */
        if (SSIE_SSICR_MST_ON == p_ssi_reg->SSICR.BIT.MST)
        {
            p_ssi_reg->SSIOFR.BIT.LRCONT = 0u;
        }

        /* Setting to mute off SSI Tx */
        ssi_clear_flag_tde( p_ssi_reg );
        ssi_clear_flag_tuirq( p_ssi_reg );
        p_ssi_reg->SSIFCR.BIT.TIE = SSIE_SSIFCR_TIE_ENABLE;
        p_ssi_reg->SSICR.BIT.TUIEN = SSIE_SSICR_TUIEN_ENABLE;
    }

    return SSI_SUCCESS;
}

/******************************************************************************
End of function  SSI_Mute
******************************************************************************/

/**********************************************************************************************************************
 * Function Name: SSI_ClearFlagTxUnderFlow
 ******************************************************************************************************************//**
 * @brief Clears a specified SSI channel's TUIRQ flag of SSISR to 0.
 * @param[in] Channel It specifies an SSI channel to clear the TUIRQ flag. Choose one enumerator member from the
 * enumerator typedef ssi_ch_t. It is described in file ssi_api_rx_if.h.
 * @retval SSI_SUCCESS Successful, this function cleared the TUIRQ flag of the specified SSI channel.
 * @retval SSI_ERR_PARAM Not successful, the parameter is illegal.
 * @retval SSI_ERR_CHANNEL Not successful, the specified SSI channel has not been locked.
 * @details Call this function to clear the TUIRQ flag when the flag is 1.
 * @note -
 */
ssi_ret_t SSI_ClearFlagTxUnderFlow ( const ssi_ch_t Channel )
{
    ssi_ret_t ret = SSI_SUCCESS;

    /* parameter & hardware lock checking operation */
    ret = ssi_check_param (Channel);

    /* flag clear operation mainbody */
    if ( SSI_SUCCESS == ret )
    {
        volatile struct st_ssie *p_ssi_reg;

        /* getting ssi register address */
        p_ssi_reg = (volatile struct st_ssie *)ssi_get_ssi_address [Channel];

        /* flag clear operation */
        ssi_clear_flag_tuirq(p_ssi_reg);
    }

    return ret;
}

/******************************************************************************
End of function SSI_ClearFlagTxUnderFlow
******************************************************************************/

/**********************************************************************************************************************
 * Function Name: SSI_ClearFlagTxOverFlow
 ******************************************************************************************************************//**
 * @brief Clears transmitter’s overflow status by setting the TOIRQ flag to 0.
 * @param[in] Channel It specifies an SSI channel to clear the TOIRQ flag. Choose one enumerator member from the
 * enumerator typedef ssi_ch_t. It is described in file ssi_api_rx_if.h.
 * @retval SSI_SUCCESS Successful, this function cleared the TOIRQ flag of the specified SSI channel.
 * @retval SSI_ERR_PARAM Not successful, the parameter is illegal.
 * @retval SSI_ERR_CHANNEL Not successful, the specified SSI channel has not been locked.
 * @details Call this function to clear the TOIRQ flag when the flag is 1.
 * @note -
 */
ssi_ret_t SSI_ClearFlagTxOverFlow ( const ssi_ch_t Channel )
{
    ssi_ret_t ret = SSI_SUCCESS;

    /* parameter & hardware lock checking operation */
    ret = ssi_check_param (Channel);

    /* flag clear operation mainbody */
    if ( SSI_SUCCESS == ret )
    {
        volatile struct st_ssie *p_ssi_reg;

        /* getting ssi register address */
        p_ssi_reg = (volatile struct st_ssie *)ssi_get_ssi_address [Channel];

        /* flag clear operation */
        ssi_clear_flag_toirq(p_ssi_reg);
    }

    return ret;
}

/******************************************************************************
End of function SSI_ClearFlagTxOverFlow
******************************************************************************/

/**********************************************************************************************************************
 * Function Name: SSI_ClearFlagRxUnderFlow
 ******************************************************************************************************************//**
 * @brief Clears a specified SSI channel's RUIRQ flag of SSISR to 0.
 * @param[in] Channel It specifies an SSI channel to clear the RUIRQ flag. Choose one enumerator member from the
 * enumerator typedef ssi_ch_t. It is described in file ssi_api_rx_if.h.
 * @retval SSI_SUCCESS Successful, this function cleared the RUIRQ flag of the specified SSI channel.
 * @retval SSI_ERR_PARAM Not successful, the parameter is illegal.
 * @retval SSI_ERR_CHANNEL Not successful, the specified SSI channel has not been locked.
 * @details Call this function to clear the RUIRQ flag when the flag is 1.
 * @note -
 */
ssi_ret_t SSI_ClearFlagRxUnderFlow ( const ssi_ch_t Channel )
{
    ssi_ret_t ret = SSI_SUCCESS;

    /* parameter & hardware lock checking operation */
    ret = ssi_check_param (Channel);

    /* flag clear operation mainbody */
    if ( SSI_SUCCESS == ret )
    {
        volatile struct st_ssie *p_ssi_reg;

        /* getting ssi register address */
        p_ssi_reg = (volatile struct st_ssie *)ssi_get_ssi_address [Channel];

        /* flag clear operation */
        ssi_clear_flag_ruirq(p_ssi_reg);
    }

    return ret;
}

/******************************************************************************
End of function SSI_ClearFlagRxUnderFlow
******************************************************************************/

/**********************************************************************************************************************
 * Function Name: SSI_ClearFlagRxOverFlow
 ******************************************************************************************************************//**
 * @brief Clears a specified SSI channel's ROIRQ flag of SSISR to 0.
 * @param[in] Channel It specifies an SSI channel to clear ROIRQ flag. Choose one enumerator member from the
 * enumerator typedef ssi_ch_t. It is described in file ssi_api_rx_if.h.
 * @retval SSI_SUCCESS Successful, this function cleared the ROIRQ flag of the specified SSI channel.
 * @retval SSI_ERR_PARAM Not successful, the parameter is illegal.
 * @retval SSI_ERR_CHANNEL Not successful, the specified SSI channel has not been locked.
 * @details Call this function to clear the ROIRQ flag when the flag is 1.
 * @note -
 */
ssi_ret_t SSI_ClearFlagRxOverFlow ( const ssi_ch_t Channel )
{
    ssi_ret_t ret = SSI_SUCCESS;

    /* parameter & hardware lock checking operation */
    ret = ssi_check_param (Channel);

    /* flag clear operation mainbody */
    if ( SSI_SUCCESS == ret )
    {
        volatile struct st_ssie *p_ssi_reg;

        /* getting ssi register address */
        p_ssi_reg = (volatile struct st_ssie *)ssi_get_ssi_address [Channel];

        /* flag clear operation */
        ssi_clear_flag_roirq(p_ssi_reg);
    }

    return ret;
}

/******************************************************************************
End of function SSI_ClearFlagRxOverFlow
******************************************************************************/

/**********************************************************************************************************************
 * Function Name: SSI_GetFlagTxUnderFlow
 ******************************************************************************************************************//**
 * @brief Returns a state of whether transmit underflow or not. The state is the value corresponding to a
 * specified SSI channel's TUIRQ flag of SSISR.
 * @param[in] Channel It specifies an SSI channel to get a state of the TUIRQ flag. Choose one enumerator member
 * from the enumerator typedef ssi_ch_t. It is described in file ssi_api_rx_if.h.
 * @retval SSI_CLR The specified SSI channel’s TUIRQ flag is 0.
 * @retval SSI_SET The specified SSI channel’s TUIRQ flag is 1.
 * @retval SSI_ERR_PARAM Not successful, the parameter is illegal.
 * @retval SSI_ERR_CHANNEL Not successful, the specified SSI channel has not been locked.
 * @details Call this function to read a state of the TUIRQ flag of the SSISR register of a specified SSI channel.
 * @note -
 */
ssi_ret_t SSI_GetFlagTxUnderFlow ( const ssi_ch_t Channel )
{
    ssi_ret_t ret = SSI_SUCCESS;

    /* parameter & hardware lock checking operation */
    ret = ssi_check_param (Channel);

    /* flag get operation mainbody */
    if ( SSI_SUCCESS == ret )
    {
        volatile struct st_ssie *p_ssi_reg;

        /* getting ssi register address */
        p_ssi_reg = (volatile struct st_ssie *)ssi_get_ssi_address [Channel];

        /* get enum member for target ssi channel. */
        if ( 0 == p_ssi_reg->SSISR.BIT.TUIRQ )
        {
            ret = SSI_FLAG_CLR; 
        }
        else
        {
            ret = SSI_FLAG_SET;
        }
    }

    return ret;
}

/******************************************************************************
End of function  SSI_GetFlagTxUnderFlow
******************************************************************************/

/**********************************************************************************************************************
 * Function Name: SSI_GetFlagTxOverFlow
 ******************************************************************************************************************//**
 * @brief Returns a state of whether transmit overflow occurs or not. The state is the value corresponding to a
 * specified SSI channel's TOIRQ flag of SSISR.
 * @param[in] Channel It specifies an SSI channel to get a state of the TOIRQ flag. Choose one enumerator member
 * from the enumerator typedef ssi_ch_t. It is described in file ssi_api_rx_if.h.
 * @retval SSI_CLR The specified SSI channel’s TOIRQ flag is 0.
 * @retval SSI_SET The specified SSI channel’s TOIRQ flag is 1.
 * @retval SSI_ERR_PARAM Not successful, the parameter is illegal.
 * @retval SSI_ERR_CHANNEL Not successful, the specified SSI channel has not been locked.
 * @details Call this function to read a state of the TOIRQ flag of the SSISR register of a specified SSI channel.
 * @note -
 */
ssi_ret_t SSI_GetFlagTxOverFlow ( const ssi_ch_t Channel )
{
    ssi_ret_t ret = SSI_SUCCESS;

    /* parameter & hardware lock checking operation */
    ret = ssi_check_param (Channel);

    /* flag get operation mainbody */
    if ( SSI_SUCCESS == ret )
    {
        volatile struct st_ssie *p_ssi_reg;

        /* getting ssi register address */
        p_ssi_reg = (volatile struct st_ssie *)ssi_get_ssi_address [Channel];

        /* get enum member for target ssi channel. */
        if ( 0 == p_ssi_reg->SSISR.BIT.TOIRQ )
        {
            ret = SSI_FLAG_CLR; 
        }
        else
        {
            ret = SSI_FLAG_SET;
        }
    }

    return ret;
}

/******************************************************************************
End of function  SSI_GetFlagTxOverFlow
******************************************************************************/

/**********************************************************************************************************************
 * Function Name: SSI_GetFlagRxUnderFlow
 ******************************************************************************************************************//**
 * @brief Returns a state of whether receive underflow occurs or not. The state is the value corresponding to a
 * specified SSI channel's RUIRQ flag of SSISR.
 * @param[in] Channel It specifies an SSI channel to get a state of the RUIRQ flag. Choose one enumerator member
 * from the enumerator typedef ssi_ch_t. It is described in file ssi_api_rx_if.h.
 * @retval SSI_CLR The specified SSI channel’s RUIRQ flag is 0.
 * @retval SSI_SET The specified SSI channel’s RUIRQ flag is 1.
 * @retval SSI_ERR_PARAM Not successful, the parameter is illegal.
 * @retval SSI_ERR_CHANNEL Not successful, the specified SSI channel has not been locked.
 * @details Call this function to read a state of the RUIRQ flag of the SSISR register of a specified SSI channel.
 * @note -
 */
ssi_ret_t SSI_GetFlagRxUnderFlow ( const ssi_ch_t Channel )
{
    ssi_ret_t ret = SSI_SUCCESS;

    /* parameter & hardware lock checking operation */
    ret = ssi_check_param (Channel);

    /* flag get operation mainbody */
    if ( SSI_SUCCESS == ret )
    {
        volatile struct st_ssie *p_ssi_reg;

        /* getting ssi register address */
        p_ssi_reg = (volatile struct st_ssie *)ssi_get_ssi_address [Channel];

        /* get enum member for target ssi channel. */
        if ( 0 == p_ssi_reg->SSISR.BIT.RUIRQ )
        {
            ret = SSI_FLAG_CLR; 
        }
        else
        {
            ret = SSI_FLAG_SET;
        }
    }

    return ret;
}

/******************************************************************************
End of function  SSI_GetFlagRxUnderFlow
******************************************************************************/

/**********************************************************************************************************************
 * Function Name: SSI_GetFlagRxOverFlow
 ******************************************************************************************************************//**
 * @brief Returns a state of whether receive overflow occurs or not. The state is the value corresponding to a
 * specified SSI channel's ROIRQ flag of SSISR.
 * @param[in] Channel It specifies an SSI channel to get a state of the ROIRQ flag. Choose one enumerator member
 * from the enumerator typedef ssi_ch_t. It is described in file ssi_api_rx_if.h.
 * @retval SSI_CLR The specified SSI channel’s ROIRQ flag is 0.
 * @retval SSI_SET The specified SSI channel’s ROIRQ flag is 1.
 * @retval SSI_ERR_PARAM Not successful, the parameter is illegal.
 * @retval SSI_ERR_CHANNEL Not successful, the specified SSI channel has not been locked.
 * @details Call this function to read a state of the ROIRQ flag of the SSISR register of a specified SSI channel.
 * @note -
 */
ssi_ret_t SSI_GetFlagRxOverFlow ( const ssi_ch_t Channel )
{
    ssi_ret_t ret = SSI_SUCCESS;

    /* parameter & hardware lock checking operation */
    ret = ssi_check_param (Channel);

    /* flag get operation mainbody */
    if ( SSI_SUCCESS == ret )
    {
        volatile struct st_ssie *p_ssi_reg;

        /* getting ssi register address */
        p_ssi_reg = (volatile struct st_ssie *)ssi_get_ssi_address [Channel];

        /* get enum member for target ssi channel. */
        if ( 0 == p_ssi_reg->SSISR.BIT.ROIRQ )
        {
            ret = SSI_FLAG_CLR; 
        }
        else
        {
            ret = SSI_FLAG_SET;
        }
    }

    return ret;
}

/******************************************************************************
End of function SSI_GetFlagRxOverFlow
******************************************************************************/

/**********************************************************************************************************************
 * Function Name: SSI_GetFlagTxEmptyFlow
 ******************************************************************************************************************//**
 * @brief Returns a state of whether transmit fifo empty occurs or not. The state is the value corresponding to a
 * specified SSI channel's ROIRQ flag of SSISR.
 * @param[in] Channel It specifies an SSI channel to get a state of the TDE flag. Choose one enumerator member
 * from the enumerator typedef ssi_ch_t. It is described in file ssi_api_rx_if.h.
 * @retval SSI_CLR The specified SSI channel’s TDE flag is 0.
 * @retval SSI_SET The specified SSI channel’s TDE flag is 1.
 * @retval SSI_ERR_PARAM Not successful, the parameter is illegal.
 * @retval SSI_ERR_CHANNEL Not successful, the specified SSI channel has not been locked.
 * @details Call this function to read a state of the TDE flag of the SSIFSR register of a specified SSI channel.
 * @note -
 */
ssi_ret_t SSI_GetFlagTxEmptyFlow ( const ssi_ch_t Channel )
{
    ssi_ret_t ret = SSI_SUCCESS;

    /* parameter & hardware lock checking operation */
    ret = ssi_check_param (Channel);

    /* flag get operation mainbody */
    if ( SSI_SUCCESS == ret )
    {
        volatile struct st_ssie *p_ssi_reg;

        /* getting ssi register address */
        p_ssi_reg = (volatile struct st_ssie *)ssi_get_ssi_address [Channel];

        /* get enum member for target ssi channel. */
        if ( 0 == p_ssi_reg->SSIFSR.BIT.TDE )
        {
            ret = SSI_FLAG_CLR; 
        }
        else
        {
            ret = SSI_FLAG_SET;
        }
    }

    return ret;
}

/******************************************************************************
End of function SSI_GetFlagTxEmptyFlow
******************************************************************************/

/**********************************************************************************************************************
 * Function Name: SSI_GetFlagRxFullFlow
 ******************************************************************************************************************//**
 * @brief Returns a state of whether receive fifo full occurs or not. The state is the value corresponding to a
 * specified SSI channel's ROIRQ flag of SSISR.
 * @param[in] Channel It specifies an SSI channel to get a state of the RDF flag. Choose one enumerator member
 * from the enumerator typedef ssi_ch_t. It is described in file ssi_api_rx_if.h.
 * @retval SSI_CLR The specified SSI channel’s RDF flag is 0.
 * @retval SSI_SET The specified SSI channel’s RDF flag is 1.
 * @retval SSI_ERR_PARAM Not successful, the parameter is illegal.
 * @retval SSI_ERR_CHANNEL Not successful, the specified SSI channel has not been locked.
 * @details Call this function to read a state of the RDF flag of the SSIFSR register of a specified SSI channel.
 * @note -
 */
ssi_ret_t SSI_GetFlagRxFullFlow ( const ssi_ch_t Channel )
{
    ssi_ret_t ret = SSI_SUCCESS;

    /* parameter & hardware lock checking operation */
    ret = ssi_check_param (Channel);

    /* flag get operation mainbody */
    if ( SSI_SUCCESS == ret )
    {
        volatile struct st_ssie *p_ssi_reg;

        /* getting ssi register address */
        p_ssi_reg = (volatile struct st_ssie *)ssi_get_ssi_address [Channel];

        /* get enum member for target ssi channel. */
        if ( 0 == p_ssi_reg->SSIFSR.BIT.RDF )
        {
            ret = SSI_FLAG_CLR; 
        }
        else
        {
            ret = SSI_FLAG_SET;
        }
    }

    return ret;
}

/******************************************************************************
End of function SSI_GetFlagRxFullFlow
******************************************************************************/
#endif
/* End of file */
