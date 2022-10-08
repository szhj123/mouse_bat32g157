/*******************************************************************************
* Copyright (C) 2014-2020 . All rights reserved.    
*******************************************************************************/
/******************************************************************************
* File Name    : ssi_api_config.h
* Version      : 2.00
* Description  : SSI driver module file for BAT MCUs.
*
*                This is a configuration file for SSI module.
*
*                Users can configure SSI peripheral by the one of following
*                  two ways.
*
*                   a) Standard configuration
*                   b) User unique configuration
*
*                The default is "a) Standard configuration", in case of
*                  "b) User unique configuration" to use, change macro 
*                   definition "SSI_STANDARD_CONFIG" to "SSI_USER_UNIQUE_CONFIG".
*
*******************************************************************************
* History : DD.MM.YYYY  Version   Description
*         : 18.05.2020   1.00      First release.
*
******************************************************************************/

#ifndef SSI_API_CONFIG_H_
#define SSI_API_CONFIG_H_

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "BAT32G157.h"

/******************************************************************************
Macro definitions
******************************************************************************/
/******************************************************************************
    This SSI module support Standatrd configuration to be easy for users to 
      configure SSI peripheral. However some users woulkd like to configure on
      their own way. Set SSI_STANDARD_CONFIG or SSI_USER_UNIQUE_CONFIG to
      definition below accordind to the requirement.
    ----------------------------------
    'Standard      SSI_STANDARD_CONFIG
    'User unique   SSI_USER_UNIQUE_CONFIG
*******************************************************************************/
//#define SSI_STANDARD_CONFIG

#if (defined(SSIE0) || defined(SSIE1))
/******************************************************************************
    Transmit / Receive mode selection (I/O mode)
      Set a value from following alternatives to SSIEn_IO_MODE.
    ----------------------------------
     SSIE usage                  value
    ----------------------------------
    'SSIE not to use             (0u)
    'SSIE to Receive data        (1u)
    'SSIE to Transmit data       (2u)
    'SSIE to Receive & Transmit  (3u)

    NOTE: This is a configuration which must be set wether
            in case of "SSI_STANDARD_CONFIG" or "SSI_USER_UNIQUE_CONFIG". 
*******************************************************************************/
//#define SSIE_CH0_IO_MODE    (2u)    /* Ch0 Transmit / Receive mode selection */
#define SSIE_CH0_IO_MODE    (3u)    /* Ch0 Transmit / Receive mode selection */
#define SSIE_CH1_IO_MODE    (0u)    /* Ch1 Transmit / Receive mode selection */

#ifdef SSI_STANDARD_CONFIG
/******************************************************************************

    Standard configuration

******************************************************************************/
/******************************************************************************
    Audio serial interface format selection
      Set a value from following alternatives to SSIEn_SERIAL_IF_FMT.
    ----------------------------------
     IF format             value
    ----------------------------------
      I2S                   (0u)
      Left-justified        (1u)
      Right-justified       (2u)
*******************************************************************************/
#define SSIE_CH0_SERIAL_IF_FMT   (0u)    /* Ch0 Audio serial interface format */
#define SSIE_CH1_SERIAL_IF_FMT   (0u)    /* Ch1 Audio serial interface format */

/******************************************************************************
    PCM data width selection
      Set a value from following alternatives to SSIEn_DATA_WIDTH.
    ----------------------------------
     PCM Data widdth       value
    ----------------------------------
       8bit                 (8u)
      16bit                 (16u)
      18bit                 (18u)
      20bit                 (20u)
      22bit                 (22u)
      24bit                 (24u)
      32bit                 (32u)
*******************************************************************************/
#define SSIE_CH0_DATA_WIDTH   (16u)          /* Ch0 PCM data width */
#define SSIE_CH1_DATA_WIDTH   (16u)          /* Ch1 PCM data width */

/******************************************************************************
    Bit clock selection
      Set a value from following alternatives to SSIEn_BCLK.
    -------------------------------------------------------------------------
    System word size     bit clock             value
    -------------------------------------------------------------------------
      8bit                 (2 *   8)fs           (16u)
      16bit                (2 *  16)fs           (32u)
      24bit                (2 *  24)fs           (48u)
      32bit                (2 *  32)fs           (64u)
      48bit                (2 *  48)fs           (96u)
      64bit                (2 *  64)fs           (128u)
      128bit               (2 * 128)fs           (256u)
      256bit               (2 * 256)fs           (512u)
*******************************************************************************/
#define SSIE_CH0_BCLK         (64u)          /* Ch0 Bit Clock */
#define SSIE_CH1_BCLK         (64u)          /* Ch1 Bit Clock */

/******************************************************************************
    Master clock frequency 
      Set a value from following alternatives to SSIEn_MCLK.
    ----------------------------------
     Clock               value
    ----------------------------------
      16Fs                (16u)
      32Fs                (32u)
       :                    :
      8192Fs              (8192u)

    NOTE: Set the Master Clock to the integral multiple of the Bit Clock.
*******************************************************************************/
#define SSIE_MCLK         (256u)         /* Master Clock */

/******************************************************************************
    Clock supply mode selection
      Set a value from following alternatives to SSIEn_CLK_MODE.
    ----------------------------------
     Data length           value
    ----------------------------------
      Master mode           (0u)
      Slave mode            (1u)
*******************************************************************************/
#define SSIE_CH0_CLK_MODE     (0u)           /* Ch0 Clock Supply Mode */
#define SSIE_CH1_CLK_MODE     (0u)           /* Ch1 Clock Supply Mode */

/******************************************************************************
    Clock source selection
      Set a value from following alternatives to SSIEn_CLK_CKS.
    ----------------------------------
     Data length           value
    ----------------------------------
      Audio clk             (0u)
      Timer clk             (1u)
*******************************************************************************/
#define SSIE_CH0_CLK_CKS      (0u)           /* Ch0 Select an Audio CLock for Master Mode*/
#define SSIE_CH1_CLK_CKS      (0u)           /* Ch1 Select an Audio CLock for Master Mode*/

/******************************************************************************
    Transmit Data Trigger number selection
      Set a value from following alternatives to SSIEn_TDES_NUMBER.
    ---------------------------------------------------------------------------
     IF format             value
    ---------------------------------------------------------------------------
     I2S                   0 to 15
     Left-justified        0 to 15
     Right-justified       0 to 15
*******************************************************************************/
#define SSIE_CH0_TDES_NUMBER    (8u)    /* Ch0 Tx Empty trigger configuration */
#define SSIE_CH1_TDES_NUMBER    (8u)    /* Ch1 Tx Empty trigger configuration */

/******************************************************************************
    Receive Data Trigger number selection
      Set a value from following alternatives to SSIEn_RDFS_NUMBER.
    ----------------------------------------------------------------------------
     IF format             value
    ---------------------------------------------------------------------------
     I2S                   1 to 16
     Left-justified        1 to 16
     Right-justified       1 to 16
*******************************************************************************/
#define SSIE_CH0_RDFS_NUMBER    (8u)    /* Ch0 Rx Full trigger configuration */
#define SSIE_CH1_RDFS_NUMBER    (8u)    /* Ch1 Rx Full trigger configuration */

/******************************************************************************
    Byte swapping
*******************************************************************************/
#define SSIE_CH0_BYTE_SWAP    (0u)
#define SSIE_CH1_BYTE_SWAP    (0u)

/******************************************************************************
    end of Standard configuration:
******************************************************************************/

#else /* SSI_USER_UNIQUE_CONFIG */

/******************************************************************************

    User unique configuration

******************************************************************************/
/*
    In case "User unique configuration", change following macro definitions
      to fit for user unique requirement. Refer to Hardware user's manual.
*/
/* Channel 0 */
#define SSIE_CH0_TDES   (7u)    /* value for "SSIE0.SSISCR.TDES" */
#define SSIE_CH0_RDFS   (7u)    /* value for "SSIE0.SSISCR.RDFS" */
#define SSIE_CH0_DEL    (0u)    /* value for "SSIE0.SSICR.DEL" */
#define SSIE_CH0_PDTA   (0u)    /* value for "SSIE0.SSICR.PDATA" */
#define SSIE_CH0_SDTA   (0u)    /* value for "SSIE0.SSICR.SDATA" */
#define SSIE_CH0_SPDP   (0u)    /* value for "SSIE0.SSICR.SPDP" */
#define SSIE_CH0_LRCKP  (0u)    /* value for "SSIE0.SSICR.LRCKP" */
#define SSIE_CH0_BCKP   (0u)    /* value for "SSIE0.SSICR.BCKP" */
#define SSIE_CH0_SWL    (3u)    /* value for "SSIE0.SSICR.SWL" */
#define SSIE_CH0_DWL    (1u)    /* value for "SSIE0.SSICR.DWL" */
#define SSIE_CH0_CKDV   (2u)    /* value for "SSIE0.SSICR.CKDV" */
#define SSIE_CH0_MST    (1u)    /* value for "SSIE0.SSICR.MST" */
#define SSIE_CH0_FRM    (0u)    /* value for "SSIE0.SSICR.FRM" */
#define SSIE_CH0_BSW    (0u)    /* value for "SSIE0.SSIFCR.BSW" */
#define SSIE_CH0_AUCKE  (1u)    /* value for "SSIE0.SSIFCR.AUCKE" */
#define SSIE_CH0_OMOD   (0u)    /* value for "SSIE0.SSIOFR.OMOD" */
#define SSIE_CH0_CKS    (1u)    /* value for "SSIE0.SSICR.CKS" */

/* Channel 1 */
#define SSIE_CH1_TDES   (7u)    /* value for "SSIE1.SSISCR.TDES" */
#define SSIE_CH1_RDFS   (7u)    /* value for "SSIE1.SSISCR.RDFS" */
#define SSIE_CH1_DEL    (0u)    /* value for "SSIE1.SSICR.DEL" */
#define SSIE_CH1_PDTA   (0u)    /* value for "SSIE1.SSICR.PDATA" */
#define SSIE_CH1_SDTA   (0u)    /* value for "SSIE1.SSICR.SDATA" */
#define SSIE_CH1_SPDP   (0u)    /* value for "SSIE1.SSICR.SPDP" */
#define SSIE_CH1_LRCKP  (0u)    /* value for "SSIE1.SSICR.LRCKP" */
#define SSIE_CH1_BCKP   (0u)    /* value for "SSIE1.SSICR.BCKP" */
#define SSIE_CH1_SWL    (3u)    /* value for "SSIE1.SSICR.SWL" */
#define SSIE_CH1_DWL    (1u)    /* value for "SSIE1.SSICR.DWL" */
#define SSIE_CH1_CKDV   (2u)    /* value for "SSIE1.SSICR.CKDV" */
#define SSIE_CH1_MST    (1u)    /* value for "SSIE1.SSICR.MST" */
#define SSIE_CH1_FRM    (0u)    /* value for "SSIE1.SSICR.FRM" */
#define SSIE_CH1_BSW    (0u)    /* value for "SSIE1.SSIFCR.BSW" */
#define SSIE_CH1_AUCKE  (1u)    /* value for "SSIE1.SSIFCR.AUCKE" */
#define SSIE_CH1_OMOD   (0u)    /* value for "SSIE1.SSIOFR.OMOD" */
#define SSIE_CH1_CKS    (1u)    /* value for "SSIE1.SSICR.CKS" */

/******************************************************************************
    End of User unique configuration area
******************************************************************************/
/* USER_UNIQUE_CONFIG */
#endif

#endif /* (defined(SSI0) || defined(SSI1)) */

#endif /* SSI_API_CONFIG_H_ */
