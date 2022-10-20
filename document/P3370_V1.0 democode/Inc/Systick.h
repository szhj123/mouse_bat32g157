#ifndef __SYSTICK_H__ 
#define __SYSTICK_H__

#ifdef __cplusplus
extern "C" {
#endif 

#include "type.h"
	
#ifdef __SYSTICK_C__
#define INTERFACE
#else
#define INTERFACE extern
#endif

#define SYSTICK_TIMER (SystemCoreClock /1000)/*1ms*/ 
//#define SYSTICK_TIMER (SystemCoreClock /1000000)/*1ms*/ 

INTERFACE void SysTick_Handler(void);
INTERFACE void nsAPI_SysTick_Init(void);

#undef INTERFACE
#ifdef __cplusplus
}
#endif 
#endif /* end __SYSTICK_H */


