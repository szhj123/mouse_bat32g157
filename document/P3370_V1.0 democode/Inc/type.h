/****************************************************************************
 *   $Id:: type.h 6172 2011-01-13 18:22:51Z usb00423                        $
 *   Project: NXP LPC11xx software example
 *
 *   Description:
 *     This file contains different type definition.
 *
 ****************************************************************************
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * products. This software is supplied "AS IS" without any warranties.
 * NXP Semiconductors assumes no responsibility or liability for the
 * use of the software, conveys no license or title under any patent,
 * copyright, or mask work right to the product. NXP Semiconductors
 * reserves the right to make changes in the software without
 * notification. NXP Semiconductors also make no representation or
 * warranty that such application will be suitable for the specified
 * use without further testing or modification.
****************************************************************************/
#ifndef __TYPE_H__
#define __TYPE_H__

/* exact-width signed integer types */
typedef signed char int8_t;
typedef int8_t S8;
typedef S8 RetS8;
typedef signed short int int16_t;
typedef int16_t S16;
typedef S16 RetS16;
typedef signed int int32_t;
typedef int32_t S32;
typedef S32 RetS32;
typedef signed __int64 int64_t;
typedef int64_t S64;
typedef S64 RetS64;
/*exact-width unsigned integer types */
typedef unsigned char uint8_t;
typedef uint8_t U8;
typedef U8 RetU8;
typedef unsigned short int uint16_t;
typedef uint16_t U16;
typedef U16 RetU16;
typedef unsigned int uint32_t;
typedef uint32_t U32;
typedef U32 RetU32;
typedef unsigned __int64 uint64_t;
typedef uint64_t U64;
typedef U64 RetU64;

typedef U8 Boolean;

// Dennis 16/5/2014
typedef union
{
	U16 w;
	U8 b[2];
}u16;

typedef union
{
	S16 w;
	S8 b[2];
}s16;

#define BIT0 (1 << 0)
#define BIT1 (1 << 1)
#define BIT2 (1 << 2)
#define BIT3 (1 << 3)
#define BIT4 (1 << 4)
#define BIT5 (1 << 5)
#define BIT6 (1 << 6)
#define BIT7 (1 << 7)
#define BIT8 (1 << 8)
#define BIT9 (1 << 9)
#define BIT10 (1 << 10)
#define BIT11 (1 << 11)
#define BIT12 (1 << 12)
#define BIT13 (1 << 13)
#define BIT14 (1 << 14)
#define BIT15 (1 << 15)
#define BIT16 (1 << 16)
#define BIT17 (1 << 17)
#define BIT18 (1 << 18)
#define BIT19 (1 << 19)
#define BIT20 (1 << 20)
#define BIT21 (1 << 21)
#define BIT22 (1 << 22)
#define BIT23 (1 << 23)
#define BIT24 (1 << 24)
#define BIT25 (1 << 25)
#define BIT26 (1 << 26)
#define BIT27 (1 << 27)
#define BIT28 (1 << 28)
#define BIT29 (1 << 29)
#define BIT30 (1 << 30)
#define BIT31 (1UL << 31)

#ifndef NULL
#define NULL ((void *)0)
#endif

#ifndef FALSE
#define FALSE (0)
#endif

#ifndef TRUE
#define TRUE (1)
#endif

#ifndef LOW
#define LOW (0)
#endif

#ifndef HIGH
#define HIGH (1)
#endif

#ifndef EMPTY
#define EMPTY (0xFF)
#endif

#endif  /* __TYPE_H__ */
