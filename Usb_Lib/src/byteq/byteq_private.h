/***********************************************************************************************************************
* File Name    : private.h
* Description  : Definitions internal to byte queue module 
***********************************************************************************************************************/

#ifndef BYTEQ_PRIVATE_H
#define BYTEQ_PRIVATE_H

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include <stdint.h>


/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/


/*****************************************************************************
Typedef definitions
******************************************************************************/

/* QUEUE CONTROL BLOCK */

typedef struct st_byteq_ctrl    // Byte Queue Control Block (for handle)
{
    uint8_t     *buffer;        // pointer to buffer
    uint16_t    size;           // buffer size
    uint16_t    count;          // number data bytes in queue
    uint16_t    in_index;       // index used by Put function to add data
    uint16_t    out_index;      // index used by Get function to remove data
} byteq_ctrl_t;


#endif /* BYTEQ_PRIVATE_H */
