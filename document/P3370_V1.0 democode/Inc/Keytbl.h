#ifndef __KEYTBL_H__ 
#define __KEYTBL_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "Type.h"
#include "Main.h"

#ifdef  __KEYTBL_C__
#define INTERFACE
#else
#define INTERFACE extern
#endif

/*Key define */
#define MouseTableSize 254
#define KeyboardTableYSize 160
#define KeyboardTableXSize 3

INTERFACE const U8 u8MouseKeyTable[MouseTableSize];
INTERFACE const U8 u8KeyboardKeyTable[KeyboardTableYSize][KeyboardTableXSize];


#undef INTERFACE
#ifdef __cplusplus
}
#endif
#endif /* end __GPIO_H */

