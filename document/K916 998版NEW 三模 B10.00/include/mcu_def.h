
#ifndef	_MCU_DEF_H
#define	_MCU_DEF_H


#define LongToBin(n) \
(                    \
((n >> 21) & 0x80) | \
((n >> 18) & 0x40) | \
((n >> 15) & 0x20) | \
((n >> 12) & 0x10) | \
((n >>  9) & 0x08) | \
((n >>  6) & 0x04) | \
((n >>  3) & 0x02) | \
((n      ) & 0x01)   \
)
#define Bin(n) LongToBin(0x##n##l)	//write binary charactor set,exsample : Bin(11111111) = 0xff



#define BIT7 (unsigned char)(1 << 7)
#define BIT6 (unsigned char)(1 << 6)
#define BIT5 (unsigned char)(1 << 5)
#define BIT4 (unsigned char)(1 << 4)
#define BIT3 (unsigned char)(1 << 3)
#define BIT2 (unsigned char)(1 << 2)
#define BIT1 (unsigned char)(1 << 1)
#define BIT0 (unsigned char)(1 << 0)


#endif
