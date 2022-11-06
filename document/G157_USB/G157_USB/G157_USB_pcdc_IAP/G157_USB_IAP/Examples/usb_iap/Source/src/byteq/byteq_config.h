/***********************************************************************************************************************
* File Name     : byteq_config.h
* Description   : Configures the byte queue memory allocation
***********************************************************************************************************************/
#ifndef BYTEQ_CONFIG_H
#define BYTEQ_CONFIG_H

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include <stdint.h>


/***********************************************************************************************************************
Configuration Options
***********************************************************************************************************************/

/* SPECIFY WHETHER TO INCLUDE CODE FOR API PARAMETER CHECKING
   Available settings:
   BSP_CFG_PARAM_CHECKING_ENABLE:
       Utilizes the system default setting
   1:
       Includes parameter checking
   0:
       Compiles out parameter checking
*/
#define BYTEQ_CFG_PARAM_CHECKING_ENABLE     (BSP_CFG_PARAM_CHECKING_ENABLE)

/* SPECIFY IF SHOULD USE MALLOC() TO ALLOCATE MEMORY FOR QUEUE CONTROL BLOCKS */
#define BYTEQ_CFG_USE_HEAP_FOR_CTRL_BLKS    (0)

/* SPECIFY NUMBER OF STATIC QUEUE CONTROL BLOCKS TO SUPPORT */
/* valid only when BYTEQ_USE_HEAP_FOR_CTRL_BLKS is set to 0 */
#define BYTEQ_CFG_MAX_CTRL_BLKS             (32)


#endif /* BYTEQ_CONFIG_H */
