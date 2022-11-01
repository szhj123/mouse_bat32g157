#ifndef __STDTYPE_H
#define __STDTYPE_H

/***************************************************************************************
									TYPEDEFS
****************************************************************************************/
#define BYTE						unsigned char
#define INT8						signed char
#define UINT8 						unsigned char
#define U8 							unsigned char
#define INT16 						signed int
#define UINT16 						unsigned int
#define U16 						unsigned int
#define WORD						unsigned int
#define INT32 						signed long
#define UINT32 						unsigned long
#define U32 						unsigned long
//#define DWORD 						unsigned long

#define FALSE						0
#define TRUE						1

#define LOW							0
#define HIGH						1



////////////////////////SYS DEF/////////////////////////////
#define START_TIMER   	(TR2 = 1)
#define STOP_TIMER    	(TR2 = 0)

#define ENABLE_INT4     (IENC = 0Xff)
#define DISABLE_INT4    (IENC = 0X00)
#endif
