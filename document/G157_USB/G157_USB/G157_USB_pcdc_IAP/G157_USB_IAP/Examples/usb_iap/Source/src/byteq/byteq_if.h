/***********************************************************************************************************************
* File Name    : byteq_if.h
* Description  : Functions for using byte queues/circular buffers 
***********************************************************************************************************************/

#ifndef BYTEQ_IF_H
#define BYTEQ_IF_H

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include <stdint.h>

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
/* Version Number of API. */
#define BYTEQ_VERSION_MAJOR (1)
#define BYTEQ_VERSION_MINOR (80)


/*****************************************************************************
Typedef definitions
******************************************************************************/

typedef enum e_byteq_err        // BYTEQ API error codes
{
    BYTEQ_SUCCESS = 0,
    BYTEQ_ERR_NULL_PTR,         // received null ptr; missing required argument
    BYTEQ_ERR_INVALID_ARG,      // argument is not valid for parameter
    BYTEQ_ERR_MALLOC_FAIL,      // can't allocate memory for ctrl block; increase heap
    BYTEQ_ERR_NO_MORE_CTRL_BLKS,  // no more control blocks, increase BYTEQ_MAX_CTRL_BLKS
    BYTEQ_ERR_QUEUE_FULL,       // queue full; cannot add another byte
    BYTEQ_ERR_QUEUE_EMPTY       // queue empty; no byte to fetch
} byteq_err_t;


/* BYTE QUEUE HANDLE */

typedef struct st_byteq_ctrl *  byteq_hdl_t;


/*****************************************************************************
Public Functions
******************************************************************************/
byteq_err_t R_BYTEQ_Open(uint8_t * const        p_buf,
                         uint16_t const         size,
                         byteq_hdl_t * const    p_hdl);

byteq_err_t R_BYTEQ_Close(byteq_hdl_t const hdl);

byteq_err_t R_BYTEQ_Put(byteq_hdl_t const   hdl,
                        uint8_t const       byte);

byteq_err_t R_BYTEQ_Get(byteq_hdl_t const   hdl,
                        uint8_t * const     p_byte);

byteq_err_t R_BYTEQ_Flush(byteq_hdl_t const hdl);

byteq_err_t R_BYTEQ_Used(byteq_hdl_t const  hdl,
                         uint16_t * const   p_cnt);

byteq_err_t R_BYTEQ_Unused(byteq_hdl_t const    hdl,
                           uint16_t * const     p_cnt);

uint32_t R_BYTEQ_GetVersion(void);


#endif /* BYTEQ_IF_H */

