
#ifndef USBFS_H
#define USBFS_H

#include <stdint.h>
#include "BAT32G157.h"
#include "userdefine.h"


/**************************************************************************
* Typedef defination
**************************************************************************/
typedef struct {
	union {
		volatile uint16_t WORD; 				/*!< (@ 0x00000000) System Configuration Control Register 			*/
		struct {
			volatile uint16_t USBE 		: 1;  	/*!< [00..00] USBFS Operation Enable 								*/
			volatile uint16_t      		: 2;  	/*!< [02..01] Reserved  											*/
			volatile uint16_t DMRPU 	: 1;  	/*!< [03..03] DM Line Resistor Control 								*/
			volatile uint16_t DPRPU 	: 1;  	/*!< [04..04] DP Line Resistor Control 								*/
			volatile uint16_t DRPD 		: 1;  	/*!< [05..05] DP/DM Line Resistor Control 							*/
			volatile uint16_t DCFM 		: 1;  	/*!< [06..06] Controller Function Selection 						*/
			volatile uint16_t      		: 1;  	/*!< [07..07] Reserved  											*/
			volatile uint16_t CNEN 		: 1;  	/*!< [08..08] Single End Receiver Enable 							*/
			volatile uint16_t      		: 1;  	/*!< [09..09] Reserved  											*/
			volatile uint16_t SCKE 		: 1;  	/*!< [10..10] USB Clock Enable 										*/
			volatile uint16_t      		: 5;  	/*!< [15..11] Reserved  											*/
		} BIT;
	} SYSCFG;
	volatile uint16_t RESERVED0;
	union {
		volatile uint16_t WORD; 				/*!< (@ 0x00000004) System Configuration Status Register 			*/
		struct {
			volatile uint16_t LNST 		: 2;  	/*!< [01..00] USB Data Line Status Monitor: LNST[1:0] = {DM,DP}		*/
			volatile uint16_t IDMON 	: 1;  	/*!< [02..02] External ID0 Input Pin Monitor						*/
			volatile uint16_t      		: 3;  	/*!< [05..03] Reserved  											*/
			volatile uint16_t HTACT 	: 1;  	/*!< [06..06] USB Host Sequencer Status Monitor						*/
			volatile uint16_t      		: 5;  	/*!< [11..07] Reserved  											*/
			volatile uint16_t FRMON 	: 1;  	/*!< [12..12] Port-0 Differential Receiver Monitor					*/
			volatile uint16_t      		: 1;  	/*!< [13..13] Reserved  											*/
			volatile uint16_t OVCMON 	: 2;  	/*!< [15..14] External USB_OVRCURA/USB_OVRCURB Input Pin Monitor	*/
		} BIT;
	} SYSSTS0;
	volatile uint16_t RESERVED1;
	union {
		volatile uint16_t WORD; 				/*!< (@ 0x00000008) Device State Control Register 		 			*/
		struct {
			volatile uint16_t RHST 		: 3;  	/*!< [02..00] USB Bus Reset Status 									*/
			volatile uint16_t      		: 1;  	/*!< [03..03] Reserved  											*/
			volatile uint16_t UACT 		: 1;  	/*!< [04..04] USB Bus Enable 										*/
			volatile uint16_t RESUME 	: 1;  	/*!< [05..05] Resume Output 										*/
			volatile uint16_t USBRST 	: 1;  	/*!< [06..06] USB Bus Reset Output 									*/
			volatile uint16_t RWUPE 	: 1;  	/*!< [07..07] Wakeup Detection Enable 								*/
			volatile uint16_t WKUP 		: 1;  	/*!< [08..08] Remote Wakeup Output 	  								*/
			volatile uint16_t VBUSEN 	: 1;  	/*!< [09..09] USB_VBUSEN Output Pin Control 						*/
			volatile uint16_t EXICEN 	: 1;  	/*!< [10..10] USB_EXICEN Output Pin Control 						*/
			volatile uint16_t HNPBTOA 	: 1;  	/*!< [11..11] Host Negotiation Protocol(HNP) Control  				*/
			volatile uint16_t      		: 3;  	/*!< [14..12] Reserved  											*/
			volatile uint16_t DEBUG 	: 1;  	/*!< [15..15] Debug mode enable                                     */
		} BIT;
	} DVSTCTR0;
	volatile uint16_t RESERVED2;
	union {
		volatile uint16_t WORD; 				/*!< (@ 0x0000000C) USB Drive Test Register 			 			*/
		struct {
			volatile uint16_t      		: 4;  	/*!< [03..00] Reserved  											*/
			volatile uint16_t TDCPF 	: 1;  	/*!< [04..04] DCPFIFO Memory Test Mode 								*/
			volatile uint16_t FDOECTL 	: 1;  	/*!< [05..05] FS Drive OE Control Bit 								*/
			volatile uint16_t RCTLON 	: 1;  	/*!< [06..06] D+ pullup 2.3Kohm 									*/
			volatile uint16_t RCTLOFF 	: 1;  	/*!< [07..07] D+ pullup 1.2Kohm 									*/
			volatile uint16_t TSTSE0 	: 1;  	/*!< [08..08] Disconnect detection mode: SE0 output 				*/
			volatile uint16_t TSTDI 	: 1;  	/*!< [09..09] USB Drive test JK state output control  				*/
			volatile uint16_t TSTDRV 	: 1;  	/*!< [10..10] USB Drive test mode 									*/
			volatile uint16_t TSTLS 	: 1;  	/*!< [11..11] USB Drive test speed selection 						*/
			volatile uint16_t TSTPC0 	: 1;  	/*!< [12..12] Port-0 Drive test enable                              */
			volatile uint16_t TSTPC1 	: 1;  	/*!< [13..13] Port-1 Drive test enable                              */
			volatile uint16_t ATTHR 	: 1;  	/*!< [14..14] Attach detection through mode 						*/
			volatile uint16_t CNTTST 	: 1;  	/*!< [15..15] Internal counter fast rotation mode 					*/
		} BIT;
	} UTEST;
	volatile uint16_t RESERVED3;
	volatile uint16_t DMA0PCFG; 				/*!< (@ 0x00000010) DMA0-FIFO Pin Configuration Register 			*/
	volatile uint16_t DMA1PCFG; 				/*!< (@ 0x00000012) DMA1-FIFO Pin Configuration Register 			*/
	union {
		volatile uint16_t WORD;
		struct {
			volatile uint8_t L;
			volatile uint8_t H;
		} BYTE;
	} CFIFO;
	volatile uint16_t RESERVED4;
	union {
		volatile uint16_t WORD;
		struct {
			volatile uint8_t L;
			volatile uint8_t H;
		} BYTE;
	} D0FIFO; 					/*!< (@ 0x00000018) D0FIFO Port Register 				 			*/
	volatile uint16_t RESERVED5;
	union {
		volatile uint16_t WORD;
		struct {
			volatile uint8_t L;
			volatile uint8_t H;
		} BYTE;
	} D1FIFO; 					/*!< (@ 0x0000001C) D1FIFO Port Register 				 			*/
	volatile uint16_t RESERVED6;
	union {
		volatile uint16_t WORD; 				/*!< (@ 0x00000020) CFIFO Port Select Register  		 			*/
		struct {
			volatile uint16_t CURPIPE 	: 4;  	/*!< [03..00] CFIFO Port Access Pipe Select  						*/
			volatile uint16_t      		: 1;  	/*!< [04..04] Reserved  											*/
			volatile uint16_t ISEL  	: 1;  	/*!< [05..05] CFIFO Port Access Direction When DCP is Selected 		*/
			volatile uint16_t      		: 2;  	/*!< [07..06] Reserved  											*/
			volatile uint16_t BIGEND 	: 1;  	/*!< [08..08] USB Bus Reset Output 									*/
			volatile uint16_t      		: 1;  	/*!< [09..09] Reserved  											*/
			volatile uint16_t MBW   	: 1;  	/*!< [10..10] CFIFO Port Access Bit Width 							*/
			volatile uint16_t      		: 3;  	/*!< [13..11] Reserved  											*/
			volatile uint16_t REW 		: 1;  	/*!< [14..14] Buffer Pointer Rewind   								*/
			volatile uint16_t RCNT 		: 1;  	/*!< [15..15] Read Count Mode 		   								*/
		} BIT;
	} CFIFOSEL;
	union {
		volatile uint16_t WORD; 				/*!< (@ 0x00000022) CFIFO Port Control Register  		 			*/
		struct {
			volatile uint16_t DTLN 		: 9;  	/*!< [08..00] Receive Data Length 			  						*/
			volatile uint16_t      		: 4;  	/*!< [12..09] Reserved  											*/
			volatile uint16_t FRDY  	: 1;  	/*!< [13..13] FIFO Port Ready 										*/
			volatile uint16_t BCLR  	: 1;  	/*!< [14..14] CPU Side FIFO Buffer Clear 							*/
			volatile uint16_t BVAL  	: 1;  	/*!< [15..15] Buffer Memory Valid Flag 								*/
		} BIT;
	} CFIFOCTR;
	volatile uint16_t RESERVED7[2];
	union {
		volatile uint16_t WORD; 				/*!< (@ 0x00000028) D0FIFO Port Select Register  		 			*/
		struct {
			volatile uint16_t CURPIPE 	: 4;  	/*!< [03..00] D0FIFO Port Access Pipe Select  						*/
			volatile uint16_t      		: 4;  	/*!< [07..04] Reserved  											*/
			volatile uint16_t BIGEND 	: 1;  	/*!< [08..08] USB Bus Reset Output 									*/
			volatile uint16_t      		: 1;  	/*!< [09..09] Reserved  											*/
			volatile uint16_t MBW   	: 1;  	/*!< [10..10] D0FIFO Port Access Bit Width 							*/
			volatile uint16_t      		: 1;  	/*!< [11..11] Reserved  											*/
			volatile uint16_t DREQE   	: 1;  	/*!< [12..12] DMA/DTC Transfer Request Enable 						*/
			volatile uint16_t DCLRM   	: 1;  	/*!< [13..13] Auto Buffer Memory Clear Mode after Specified Pipe Data is Read */
			volatile uint16_t REW 		: 1;  	/*!< [14..14] Buffer Pointer Rewind   								*/
			volatile uint16_t RCNT 		: 1;  	/*!< [15..15] Read Count Mode 		   								*/
		} BIT;
	} D0FIFOSEL;
	union {
		volatile uint16_t WORD; 				/*!< (@ 0x0000002A) D0FIFO Port Control Register  		 			*/
		struct {
			volatile uint16_t DTLN 		: 9;  	/*!< [08..00] Receive Data Length 			  						*/
			volatile uint16_t      		: 4;  	/*!< [12..09] Reserved  											*/
			volatile uint16_t FRDY  	: 1;  	/*!< [13..13] FIFO Port Ready 										*/
			volatile uint16_t BCLR  	: 1;  	/*!< [14..14] CPU Side FIFO Buffer Clear 							*/
			volatile uint16_t BVAL  	: 1;  	/*!< [15..15] Buffer Memory Valid Flag 								*/
		} BIT;
	} D0FIFOCTR;
	union {
		volatile uint16_t WORD; 				/*!< (@ 0x0000002C) D1FIFO Port Select Register  		 			*/
		struct {
			volatile uint16_t CURPIPE 	: 4;  	/*!< [03..00] D1FIFO Port Access Pipe Select  						*/
			volatile uint16_t      		: 4;  	/*!< [07..04] Reserved  											*/
			volatile uint16_t BIGEND 	: 1;  	/*!< [08..08] USB Bus Reset Output 									*/
			volatile uint16_t      		: 1;  	/*!< [09..09] Reserved  											*/
			volatile uint16_t MBW   	: 1;  	/*!< [10..10] D1FIFO Port Access Bit Width 							*/
			volatile uint16_t      		: 1;  	/*!< [11..11] Reserved  											*/
			volatile uint16_t DREQE   	: 1;  	/*!< [12..12] DMA/DTC Transfer Request Enable 						*/
			volatile uint16_t DCLRM   	: 1;  	/*!< [13..13] Auto Buffer Memory Clear Mode after Specified Pipe Data is Read */
			volatile uint16_t REW 		: 1;  	/*!< [14..14] Buffer Pointer Rewind   								*/
			volatile uint16_t RCNT 		: 1;  	/*!< [15..15] Read Count Mode 		   								*/
		} BIT;
	} D1FIFOSEL;
	union {
		volatile uint16_t WORD; 				/*!< (@ 0x0000002E) D1FIFO Port Control Register  		 			*/
		struct {
			volatile uint16_t DTLN 		: 9;  	/*!< [08..00] Receive Data Length 			  						*/
			volatile uint16_t      		: 4;  	/*!< [12..09] Reserved  											*/
			volatile uint16_t FRDY  	: 1;  	/*!< [13..13] FIFO Port Ready 										*/
			volatile uint16_t BCLR  	: 1;  	/*!< [14..14] CPU Side FIFO Buffer Clear 							*/
			volatile uint16_t BVAL  	: 1;  	/*!< [15..15] Buffer Memory Valid Flag 								*/
		} BIT;
	} D1FIFOCTR;
	union {
		volatile uint16_t WORD; 				/*!< (@ 0x00000030) Interrupt Enable Register 0  		 			*/
		struct {
			volatile uint16_t      		: 8;  	/*!< [07..09] Reserved  											*/
			volatile uint16_t BRDYE 	: 1;  	/*!< [08..08] Buffer Ready Interrupt Enable   						*/
			volatile uint16_t NRDYE 	: 1;  	/*!< [09..09] Buffer Not Ready Interrupt Enable   					*/
			volatile uint16_t BEMPE 	: 1;  	/*!< [10..10] Buffer Empty Interrupt Enable 	  					*/
			volatile uint16_t CTRE 		: 1;  	/*!< [11..11] Control Transfer Stage Transition Interrupt Enable 	*/
			volatile uint16_t DVSE  	: 1;  	/*!< [12..12] Device Stage Transition Interrupt Enable 				*/
			volatile uint16_t SOFE  	: 1;  	/*!< [13..13] Frame Number Update Interrupt Enable 					*/
			volatile uint16_t RSME  	: 1;  	/*!< [14..14] Resume Interrupt Enable 								*/
			volatile uint16_t VBSE  	: 1;  	/*!< [15..15] VBUS Interrupt Enable 								*/
		} BIT;
	} INTENB0;
	union {
		volatile uint16_t WORD; 				/*!< (@ 0x00000032) Interrupt Enable Register 1  		 			*/
		struct {
			volatile uint16_t PDDETINTE	: 1;  	/*!< [00..00] PortableDevice Detection Interrupt Enable 			*/
			volatile uint16_t      		: 3;  	/*!< [03..01] Reserved  											*/
			volatile uint16_t SACKE 	: 1;  	/*!< [04..04] Setup Transaction Normal Response Interrupt Enable   	*/
			volatile uint16_t SIGNE 	: 1;  	/*!< [05..05] Setup Transaction Error Interrupt Enable   			*/
			volatile uint16_t EOFERRE 	: 1;  	/*!< [06..06] EOF Error Detection Interrupt Enable 		  			*/
			volatile uint16_t      		: 4;  	/*!< [10..07] Reserved  											*/
			volatile uint16_t ATTCHE 	: 1;  	/*!< [11..11] Connection Detection Interrupt Enable 				*/
			volatile uint16_t DTCHE 	: 1;  	/*!< [12..12] Disconnection Detection Interrupt Enable 				*/
			volatile uint16_t      		: 1;  	/*!< [13..13] Reserved  											*/
			volatile uint16_t BCHGE 	: 1;  	/*!< [14..14] USB Bus Change Interrupt Enable 						*/
			volatile uint16_t OVRCRE 	: 1;  	/*!< [15..15] OverCurrent Input Change Interrupt Enable 			*/
		} BIT;
	} INTENB1;
	union {
		volatile uint16_t WORD; 				/*!< (@ 0x00000034) Interrupt Enable Register 2  		 			*/
		struct {
			volatile uint16_t PDDETINTE	: 1;  	/*!< [00..00] PortableDevice Detection Interrupt Enable 			*/
			volatile uint16_t      		: 5;  	/*!< [05..01] Reserved  											*/
			volatile uint16_t EOFERRE 	: 1;  	/*!< [06..06] EOF Error Detection Interrupt Enable 		  			*/
			volatile uint16_t      		: 4;  	/*!< [10..07] Reserved  											*/
			volatile uint16_t ATTCHE 	: 1;  	/*!< [11..11] Connection Detection Interrupt Enable 				*/
			volatile uint16_t DTCHE 	: 1;  	/*!< [12..12] Disconnection Detection Interrupt Enable 				*/
			volatile uint16_t      		: 1;  	/*!< [13..13] Reserved  											*/
			volatile uint16_t BCHGE 	: 1;  	/*!< [14..14] USB Bus Change Interrupt Enable 						*/
			volatile uint16_t OVRCRE 	: 1;  	/*!< [15..15] OverCurrent Input Change Interrupt Enable 			*/
		} BIT;
	} INTENB2;
	union {
		volatile uint16_t WORD; 				/*!< (@ 0x00000036) BRDY Interrupt Enable Register 		 			*/
		struct {
			volatile uint16_t PIPE0BRDYE: 1;  	/*!< [00..00] BRDY Interrupt Enable for PIPE0 						*/
			volatile uint16_t PIPE1BRDYE: 1;  	/*!< [01..01] BRDY Interrupt Enable for PIPE1 						*/
			volatile uint16_t PIPE2BRDYE: 1;  	/*!< [02..02] BRDY Interrupt Enable for PIPE2 						*/
			volatile uint16_t PIPE3BRDYE: 1;  	/*!< [03..03] BRDY Interrupt Enable for PIPE3 						*/
			volatile uint16_t PIPE4BRDYE: 1;  	/*!< [04..04] BRDY Interrupt Enable for PIPE4 						*/
			volatile uint16_t PIPE5BRDYE: 1;  	/*!< [05..05] BRDY Interrupt Enable for PIPE5 						*/
			volatile uint16_t PIPE6BRDYE: 1;  	/*!< [06..06] BRDY Interrupt Enable for PIPE6 						*/
			volatile uint16_t PIPE7BRDYE: 1;  	/*!< [07..07] BRDY Interrupt Enable for PIPE7 						*/
			volatile uint16_t PIPE8BRDYE: 1;  	/*!< [08..08] BRDY Interrupt Enable for PIPE8 						*/
			volatile uint16_t PIPE9BRDYE: 1;  	/*!< [09..09] BRDY Interrupt Enable for PIPE9 						*/
			volatile uint16_t      		: 6;  	/*!< [15..10] Reserved  											*/
		} BIT;
	} BRDYENB;
	union {
		volatile uint16_t WORD; 				/*!< (@ 0x00000038) NRDY Interrupt Enable Register 		 			*/
		struct {
			volatile uint16_t PIPE0NRDYE: 1;  	/*!< [00..00] NRDY Interrupt Enable for PIPE0 						*/
			volatile uint16_t PIPE1NRDYE: 1;  	/*!< [01..01] NRDY Interrupt Enable for PIPE1 						*/
			volatile uint16_t PIPE2NRDYE: 1;  	/*!< [02..02] NRDY Interrupt Enable for PIPE2 						*/
			volatile uint16_t PIPE3NRDYE: 1;  	/*!< [03..03] NRDY Interrupt Enable for PIPE3 						*/
			volatile uint16_t PIPE4NRDYE: 1;  	/*!< [04..04] NRDY Interrupt Enable for PIPE4 						*/
			volatile uint16_t PIPE5NRDYE: 1;  	/*!< [05..05] NRDY Interrupt Enable for PIPE5 						*/
			volatile uint16_t PIPE6NRDYE: 1;  	/*!< [06..06] NRDY Interrupt Enable for PIPE6 						*/
			volatile uint16_t PIPE7NRDYE: 1;  	/*!< [07..07] NRDY Interrupt Enable for PIPE7 						*/
			volatile uint16_t PIPE8NRDYE: 1;  	/*!< [08..08] NRDY Interrupt Enable for PIPE8 						*/
			volatile uint16_t PIPE9NRDYE: 1;  	/*!< [09..09] NRDY Interrupt Enable for PIPE9 						*/
			volatile uint16_t      		: 6;  	/*!< [15..10] Reserved  											*/
		} BIT;
	} NRDYENB;
	union {
		volatile uint16_t WORD; 				/*!< (@ 0x0000003A) BEMP Interrupt Enable Register 		 			*/
		struct {
			volatile uint16_t PIPE0BEMPE: 1;  	/*!< [00..00] BEMP Interrupt Enable for PIPE0 						*/
			volatile uint16_t PIPE1BEMPE: 1;  	/*!< [01..01] BEMP Interrupt Enable for PIPE1 						*/
			volatile uint16_t PIPE2BEMPE: 1;  	/*!< [02..02] BEMP Interrupt Enable for PIPE2 						*/
			volatile uint16_t PIPE3BEMPE: 1;  	/*!< [03..03] BEMP Interrupt Enable for PIPE3 						*/
			volatile uint16_t PIPE4BEMPE: 1;  	/*!< [04..04] BEMP Interrupt Enable for PIPE4 						*/
			volatile uint16_t PIPE5BEMPE: 1;  	/*!< [05..05] BEMP Interrupt Enable for PIPE5 						*/
			volatile uint16_t PIPE6BEMPE: 1;  	/*!< [06..06] BEMP Interrupt Enable for PIPE6 						*/
			volatile uint16_t PIPE7BEMPE: 1;  	/*!< [07..07] BEMP Interrupt Enable for PIPE7 						*/
			volatile uint16_t PIPE8BEMPE: 1;  	/*!< [08..08] BEMP Interrupt Enable for PIPE8 						*/
			volatile uint16_t PIPE9BEMPE: 1;  	/*!< [09..09] BEMP Interrupt Enable for PIPE9 						*/
			volatile uint16_t      		: 6;  	/*!< [15..10] Reserved  											*/
		} BIT;
	} BEMPENB;
	union {
		volatile uint16_t WORD; 				/*!< (@ 0x0000003C) SOF Configuration Register   		 			*/
		struct {
			volatile uint16_t      		: 4;  	/*!< [03..00] Reserved  											*/
			volatile uint16_t EDGESTS 	: 1;  	/*!< [04..04] Edge Interrupt Output Status Monitor 		  			*/
			volatile uint16_t      		: 1;  	/*!< [05..05] Reserved  											*/
			volatile uint16_t BRDYM 	: 1;  	/*!< [06..06] BRDY Interrupt Status Clear Timing 					*/
			volatile uint16_t      		: 1;  	/*!< [07..07] Reserved  											*/
			volatile uint16_t TRNENSEL 	: 1;  	/*!< [08..08] Transaction-Enabled Time Select 						*/
			volatile uint16_t      		: 7;  	/*!< [15..09] Reserved  											*/
		} BIT;
	} SOFCFG;
	volatile uint16_t RESERVED8;
	union {
		volatile uint16_t WORD; 				/*!< (@ 0x00000040) Interrupt Status Register 0  		 			*/
		struct {
			volatile uint16_t CTSQ 		: 3;  	/*!< [02..00] Control Transfer State  								*/
			volatile uint16_t VALID 	: 1;  	/*!< [03..03] USB Request Reception  								*/
			volatile uint16_t DVSQ 		: 3;  	/*!< [06..04] Device State  										*/
			volatile uint16_t VBSTS 	: 1;  	/*!< [07..07] VBUS Input Status Monitor 							*/
			volatile uint16_t BRDY  	: 1;  	/*!< [08..08] Buffer Ready Interrupt Status   						*/
			volatile uint16_t NRDY  	: 1;  	/*!< [09..09] Buffer Not Ready Interrupt Status   					*/
			volatile uint16_t BEMP  	: 1;  	/*!< [10..10] Buffer Empty Interrupt Status 	  					*/
			volatile uint16_t CTRT 		: 1;  	/*!< [11..11] Control Transfer Stage Transition Interrupt Status 	*/
			volatile uint16_t DVST  	: 1;  	/*!< [12..12] Device Stage Transition Interrupt Status 				*/
			volatile uint16_t SOFR  	: 1;  	/*!< [13..13] Frame Number Update Interrupt Status 					*/
			volatile uint16_t RSMM  	: 1;  	/*!< [14..14] Resume Interrupt Status 								*/
			volatile uint16_t VBINT  	: 1;  	/*!< [15..15] VBUS Interrupt Status 								*/
		} BIT;
	} INTSTS0;
	union {
		volatile uint16_t WORD; 				/*!< (@ 0x00000042) Interrupt Status Register 1  		 			*/
		struct {
			volatile uint16_t PDDETINT 	: 1;  	/*!< [00..00] PortableDevice Detection Interrupt Status 			*/
			volatile uint16_t      		: 3;  	/*!< [03..01] Reserved  											*/
			volatile uint16_t SACK  	: 1;  	/*!< [04..04] Setup Transaction Normal Response Interrupt Status   	*/
			volatile uint16_t SIGN  	: 1;  	/*!< [05..05] Setup Transaction Error Interrupt Status   			*/
			volatile uint16_t EOFERR  	: 1;  	/*!< [06..06] EOF Error Detection Interrupt Status 		  			*/
			volatile uint16_t      		: 4;  	/*!< [10..07] Reserved  											*/
			volatile uint16_t ATTCH  	: 1;  	/*!< [11..11] Connection Detection Interrupt Status 				*/
			volatile uint16_t DTCH  	: 1;  	/*!< [12..12] Disconnection Detection Interrupt Status 				*/
			volatile uint16_t      		: 1;  	/*!< [13..13] Reserved  											*/
			volatile uint16_t BCHG  	: 1;  	/*!< [14..14] USB Bus Change Interrupt Status 						*/
			volatile uint16_t OVRCR  	: 1;  	/*!< [15..15] OverCurrent Input Change Interrupt Status 			*/
		} BIT;
	} INTSTS1;
	union {
		volatile uint16_t WORD; 				/*!< (@ 0x00000044) Interrupt Status Register 2  		 			*/
		struct {
			volatile uint16_t PDDETINT 	: 1;  	/*!< [00..00] PortableDevice Detection Interrupt Status 			*/
			volatile uint16_t      		: 5;  	/*!< [05..01] Reserved  											*/
			volatile uint16_t EOFERR  	: 1;  	/*!< [06..06] EOF Error Detection Interrupt Status 		  			*/
			volatile uint16_t      		: 4;  	/*!< [10..07] Reserved  											*/
			volatile uint16_t ATTCH  	: 1;  	/*!< [11..11] Connection Detection Interrupt Status 				*/
			volatile uint16_t DTCH  	: 1;  	/*!< [12..12] Disconnection Detection Interrupt Status 				*/
			volatile uint16_t      		: 1;  	/*!< [13..13] Reserved  											*/
			volatile uint16_t BCHG  	: 1;  	/*!< [14..14] USB Bus Change Interrupt Status 						*/
			volatile uint16_t OVRCR  	: 1;  	/*!< [15..15] OverCurrent Input Change Interrupt Status 			*/
		} BIT;
	} INTSTS2;
	union {
		volatile uint16_t WORD; 				/*!< (@ 0x00000046) BRDY Interrupt Status Register 		 			*/
		struct {
			volatile uint16_t PIPE0BRDY : 1;  	/*!< [00..00] BRDY Interrupt Status for PIPE0 						*/
			volatile uint16_t PIPE1BRDY : 1;  	/*!< [01..01] BRDY Interrupt Status for PIPE1 						*/
			volatile uint16_t PIPE2BRDY : 1;  	/*!< [02..02] BRDY Interrupt Status for PIPE2 						*/
			volatile uint16_t PIPE3BRDY : 1;  	/*!< [03..03] BRDY Interrupt Status for PIPE3 						*/
			volatile uint16_t PIPE4BRDY : 1;  	/*!< [04..04] BRDY Interrupt Status for PIPE4 						*/
			volatile uint16_t PIPE5BRDY : 1;  	/*!< [05..05] BRDY Interrupt Status for PIPE5 						*/
			volatile uint16_t PIPE6BRDY : 1;  	/*!< [06..06] BRDY Interrupt Status for PIPE6 						*/
			volatile uint16_t PIPE7BRDY : 1;  	/*!< [07..07] BRDY Interrupt Status for PIPE7 						*/
			volatile uint16_t PIPE8BRDY : 1;  	/*!< [08..08] BRDY Interrupt Status for PIPE8 						*/
			volatile uint16_t PIPE9BRDY : 1;  	/*!< [09..09] BRDY Interrupt Status for PIPE9 						*/
			volatile uint16_t      		: 6;  	/*!< [15..10] Reserved  											*/
		} BIT;
	} BRDYSTS;
	union {
		volatile uint16_t WORD; 				/*!< (@ 0x00000048) NRDY Interrupt Status Register 		 			*/
		struct {
			volatile uint16_t PIPE0NRDY : 1;  	/*!< [00..00] NRDY Interrupt Status for PIPE0 						*/
			volatile uint16_t PIPE1NRDY : 1;  	/*!< [01..01] NRDY Interrupt Status for PIPE1 						*/
			volatile uint16_t PIPE2NRDY : 1;  	/*!< [02..02] NRDY Interrupt Status for PIPE2 						*/
			volatile uint16_t PIPE3NRDY : 1;  	/*!< [03..03] NRDY Interrupt Status for PIPE3 						*/
			volatile uint16_t PIPE4NRDY : 1;  	/*!< [04..04] NRDY Interrupt Status for PIPE4 						*/
			volatile uint16_t PIPE5NRDY : 1;  	/*!< [05..05] NRDY Interrupt Status for PIPE5 						*/
			volatile uint16_t PIPE6NRDY : 1;  	/*!< [06..06] NRDY Interrupt Status for PIPE6 						*/
			volatile uint16_t PIPE7NRDY : 1;  	/*!< [07..07] NRDY Interrupt Status for PIPE7 						*/
			volatile uint16_t PIPE8NRDY : 1;  	/*!< [08..08] NRDY Interrupt Status for PIPE8 						*/
			volatile uint16_t PIPE9NRDY : 1;  	/*!< [09..09] NRDY Interrupt Status for PIPE9 						*/
			volatile uint16_t      		: 6;  	/*!< [15..10] Reserved  											*/
		} BIT;
	} NRDYSTS;
	union {
		volatile uint16_t WORD; 				/*!< (@ 0x0000004A) BEMP Interrupt Status Register 		 			*/
		struct {
			volatile uint16_t PIPE0BEMP : 1;  	/*!< [00..00] BEMP Interrupt Status for PIPE0 						*/
			volatile uint16_t PIPE1BEMP : 1;  	/*!< [01..01] BEMP Interrupt Status for PIPE1 						*/
			volatile uint16_t PIPE2BEMP : 1;  	/*!< [02..02] BEMP Interrupt Status for PIPE2 						*/
			volatile uint16_t PIPE3BEMP : 1;  	/*!< [03..03] BEMP Interrupt Status for PIPE3 						*/
			volatile uint16_t PIPE4BEMP : 1;  	/*!< [04..04] BEMP Interrupt Status for PIPE4 						*/
			volatile uint16_t PIPE5BEMP : 1;  	/*!< [05..05] BEMP Interrupt Status for PIPE5 						*/
			volatile uint16_t PIPE6BEMP : 1;  	/*!< [06..06] BEMP Interrupt Status for PIPE6 						*/
			volatile uint16_t PIPE7BEMP : 1;  	/*!< [07..07] BEMP Interrupt Status for PIPE7 						*/
			volatile uint16_t PIPE8BEMP : 1;  	/*!< [08..08] BEMP Interrupt Status for PIPE8 						*/
			volatile uint16_t PIPE9BEMP : 1;  	/*!< [09..09] BEMP Interrupt Status for PIPE9 						*/
			volatile uint16_t      		: 6;  	/*!< [15..10] Reserved  											*/
		} BIT;
	} BEMPSTS;
	union {
		volatile uint16_t WORD; 				/*!< (@ 0x0000004C) Frame Number Register 				 			*/
		struct {
			volatile uint16_t FRNM 		:11;  	/*!< [10..00] Frame Number 											*/
			volatile uint16_t SOFRM 	: 1;  	/*!< [11..11] Frame Number Update Interrupt Mode 					*/
			volatile uint16_t NCSOF 	: 1;  	/*!< [12..12] SOF interpolation for Function; Frame interval is short for Host */
			volatile uint16_t AJFRM 	: 1;  	/*!< [13..13] Frame Interval Adjustment mode 						*/
			volatile uint16_t CRCE 		: 1;  	/*!< [14..14] Receive Data Error Status 							*/
			volatile uint16_t OVRN 		: 1;  	/*!< [15..15] OverRun/UnderRun Detection Status 					*/
		} BIT;
	} FRMNUM;
	union {
		volatile uint16_t WORD; 				/*!< (@ 0x0000004E) Micro Frame Number Register 		 			*/
		struct {
			volatile uint16_t      		:15;  	/*!< [14..10] Reserved  											*/
			volatile uint16_t DVCHG 	: 1;  	/*!< [15..15] Device State Change Enable 							*/
		} BIT;
	} UFRMNUM;
	union {
		volatile uint16_t WORD; 				/*!< (@ 0x00000050) USB Address Register 		 					*/
		struct {
			volatile uint16_t USBADDR   : 7;  	/*!< [06..00] USB Address  											*/
			volatile uint16_t      		: 1;  	/*!< [07..07] Reserved  											*/
			volatile uint16_t STSRECOV0 : 4;  	/*!< [11..08] Device State Change Bits								*/
			volatile uint16_t      		: 4;  	/*!< [15..12] Reserved  											*/
		} BIT;
	} USBADDR;
	union {
		volatile uint16_t WORD; 				/*!< (@ 0x00000052) Status Recovery Register 	 					*/
		struct {
			volatile uint16_t AJFRMTIM  : 8;  	/*!< [07..00] Frame Interval Adjustment Time  						*/
			volatile uint16_t      		: 2;  	/*!< [09..08] Reserved  											*/
			volatile uint16_t STSRECOV1 : 2;  	/*!< [11..10] Device State Change Bits								*/
			volatile uint16_t      		: 4;  	/*!< [15..12] Reserved  											*/
		} BIT;
	} STSRECOV1;
	union {
		volatile uint16_t WORD; 				/*!< (@ 0x00000054) USB Request Type Register 	 					*/
		struct {
			volatile uint16_t bmRequestType  : 8;  	/*!< [07..00] USB request bmRequestType value 					*/
			volatile uint16_t bRequest  	 : 8;  	/*!< [15..08] USB request bRequest value 						*/
		} BIT;
	} USBREQ;
	volatile uint16_t USBVAL;
	volatile uint16_t USBINDX;
	volatile uint16_t USBLENG;
	union {
		volatile uint16_t WORD; 				/*!< (@ 0x0000005C) DCP Configuration Register 	 					*/
		struct {
			volatile uint16_t      		: 4;  	/*!< [03..00] Reserved  											*/
			volatile uint16_t DIR  		: 1;  	/*!< [04..04] Transfer Direction 									*/
			volatile uint16_t      		: 2;  	/*!< [06..05] Reserved  											*/
			volatile uint16_t SHINAK 	: 1;  	/*!< [07..07] Pipe Disabled at End of Transfer 						*/
			volatile uint16_t      		: 8;  	/*!< [15..08] Reserved  											*/
		} BIT;
	} DCPCFG;
	union {
		volatile uint16_t WORD; 				/*!< (@ 0x0000005E) DCP Maximum Packet Size Register 				*/
		struct {
			volatile uint16_t MXPS  	: 7;  	/*!< [06..00] Maximum Packet Size  									*/
			volatile uint16_t      		: 5;  	/*!< [11..07] Reserved  											*/
			volatile uint16_t DEVSEL 	: 4;  	/*!< [15..12] Device Select 										*/
		} BIT;
	} DCPMAXP;
	union {
		volatile uint16_t WORD; 				/*!< (@ 0x00000060) DCP Control Register 			 				*/
		struct {
			volatile uint16_t PID  		: 2;  	/*!< [01..00] Response PID 		  									*/
			volatile uint16_t CCPL 		: 1;  	/*!< [02..02] Control Transfer End Enable 							*/
			volatile uint16_t      		: 2;  	/*!< [04..03] Reserved  											*/
			volatile uint16_t PBUSY 	: 1;  	/*!< [05..05] Pipe Busy 	 										*/
			volatile uint16_t SQMON 	: 1;  	/*!< [06..06] Sequence Toggle Bit Monitor  							*/
			volatile uint16_t SQSET 	: 1;  	/*!< [07..07] Sequence Toggle Bit Set 	 							*/
			volatile uint16_t SQCLR 	: 1;  	/*!< [08..08] Sequence Toggle Bit Clear  							*/
			volatile uint16_t      		: 2;  	/*!< [10..09] Reserved  											*/
			volatile uint16_t SUREQCLR 	: 1;  	/*!< [11..11] SUREQ Bit Clear 			 							*/
			volatile uint16_t      		: 2;  	/*!< [13..12] Reserved  											*/
			volatile uint16_t SUREQ 	: 1;  	/*!< [14..14] Setup Token Transmission 	 							*/
			volatile uint16_t BSTS 		: 1;  	/*!< [15..15] Buffer Status 			 							*/
		} BIT;
	} DCPCTR;
	volatile uint16_t RESERVED9;
	union {
		volatile uint16_t WORD; 				/*!< (@ 0x00000064) Pipe Window Select Register 					*/
		struct {
			volatile uint16_t PIPESEL  	: 4;  	/*!< [03..00] Pipe Window Select   									*/
			volatile uint16_t      		:12;  	/*!< [15..04] Reserved  											*/
		} BIT;
	} PIPESEL;
	volatile uint16_t RESERVED10;
	union {
		volatile uint16_t WORD; 				/*!< (@ 0x00000068) Pipe Configuration Register 					*/
		struct {
			volatile uint16_t EPNUM  	: 4;  	/*!< [03..00] Endpoint Number    									*/
			volatile uint16_t DIR  		: 1;  	/*!< [04..04] Transfer Direction   									*/
			volatile uint16_t      		: 2;  	/*!< [06..05] Reserved  											*/
			volatile uint16_t SHINAK 	: 1;  	/*!< [07..07] Pipe Disabled at End of Transfer 						*/
			volatile uint16_t      		: 1;  	/*!< [08..08] Reserved  											*/
			volatile uint16_t DBLB 		: 1;  	/*!< [09..09] Double Buffer Mode 									*/
			volatile uint16_t BFRE 		: 1;  	/*!< [10..10] BRDY Interrupt Timing Specification  					*/
			volatile uint16_t      		: 3;  	/*!< [13..11] Reserved  											*/
			volatile uint16_t TYPE 		: 1;  	/*!< [15..14] Transfer Type 										*/
		} BIT;
	} PIPECFG;
	volatile uint16_t RESERVED11;
	union {
		volatile uint16_t WORD; 				/*!< (@ 0x0000006C) Pipe Maximum Packet Size Register 				*/
		struct {
			volatile uint16_t MXPS  	: 9;  	/*!< [08..00] Maximum Packet Size  									*/
			volatile uint16_t      		: 3;  	/*!< [11..09] Reserved  											*/
			volatile uint16_t DEVSEL 	: 4;  	/*!< [15..12] Device Select 										*/
		} BIT;
	} PIPEMAXP;
	union {
		volatile uint16_t WORD; 				/*!< (@ 0x0000006E) Pipe Cycle Control Register 					*/
		struct {
			volatile uint16_t IITV  	: 3;  	/*!< [02..00] Interval Error Detection Interval 					*/
			volatile uint16_t      		: 9;  	/*!< [11..03] Reserved  											*/
			volatile uint16_t IFIS 		: 1;  	/*!< [12..12] Isochronous IN Buffer Flush 							*/
			volatile uint16_t      		: 3;  	/*!< [15..13] Reserved  											*/
		} BIT;
	} PIPEPERI;
	union {
		volatile uint16_t WORD; 				/*!< (@ 0x00000070) PIPE1 Control Register 							*/
		struct {
			volatile uint16_t PID  		: 2;  	/*!< [01..00] Response PID 		  									*/
			volatile uint16_t      		: 3;  	/*!< [04..02] Reserved  											*/
			volatile uint16_t PBUSY 	: 1;  	/*!< [05..05] Pipe Busy 	 										*/
			volatile uint16_t SQMON 	: 1;  	/*!< [06..06] Sequence Toggle Bit Monitor  							*/
			volatile uint16_t SQSET 	: 1;  	/*!< [07..07] Sequence Toggle Bit Set 	 							*/
			volatile uint16_t SQCLR 	: 1;  	/*!< [08..08] Sequence Toggle Bit Clear  							*/
			volatile uint16_t ACLRM 	: 1;  	/*!< [09..09] Auto Buffer Clear Mode 	 							*/
			volatile uint16_t ATREPM 	: 1;  	/*!< [10..10] Auto Response Mode 		 							*/
			volatile uint16_t      		: 3;  	/*!< [13..11] Reserved  											*/
			volatile uint16_t INBUFM 	: 1;  	/*!< [14..14] Transfer Buffer Monitor 								*/
			volatile uint16_t BSTS 		: 1;  	/*!< [15..15] Buffer Status 			 							*/
		} BIT;
	} PIPE1CTR;
	union {
		volatile uint16_t WORD; 				/*!< (@ 0x00000072) PIPE2 Control Register 							*/
		struct {
			volatile uint16_t PID  		: 2;  	/*!< [01..00] Response PID 		  									*/
			volatile uint16_t      		: 3;  	/*!< [04..02] Reserved  											*/
			volatile uint16_t PBUSY 	: 1;  	/*!< [05..05] Pipe Busy 	 										*/
			volatile uint16_t SQMON 	: 1;  	/*!< [06..06] Sequence Toggle Bit Monitor  							*/
			volatile uint16_t SQSET 	: 1;  	/*!< [07..07] Sequence Toggle Bit Set 	 							*/
			volatile uint16_t SQCLR 	: 1;  	/*!< [08..08] Sequence Toggle Bit Clear  							*/
			volatile uint16_t ACLRM 	: 1;  	/*!< [09..09] Auto Buffer Clear Mode 	 							*/
			volatile uint16_t ATREPM 	: 1;  	/*!< [10..10] Auto Response Mode 		 							*/
			volatile uint16_t      		: 3;  	/*!< [13..11] Reserved  											*/
			volatile uint16_t INBUFM 	: 1;  	/*!< [14..14] Transfer Buffer Monitor 								*/
			volatile uint16_t BSTS 		: 1;  	/*!< [15..15] Buffer Status 			 							*/
		} BIT;
	} PIPE2CTR;
	union {
		volatile uint16_t WORD; 				/*!< (@ 0x00000074) PIPE3 Control Register 							*/
		struct {
			volatile uint16_t PID  		: 2;  	/*!< [01..00] Response PID 		  									*/
			volatile uint16_t      		: 3;  	/*!< [04..02] Reserved  											*/
			volatile uint16_t PBUSY 	: 1;  	/*!< [05..05] Pipe Busy 	 										*/
			volatile uint16_t SQMON 	: 1;  	/*!< [06..06] Sequence Toggle Bit Monitor  							*/
			volatile uint16_t SQSET 	: 1;  	/*!< [07..07] Sequence Toggle Bit Set 	 							*/
			volatile uint16_t SQCLR 	: 1;  	/*!< [08..08] Sequence Toggle Bit Clear  							*/
			volatile uint16_t ACLRM 	: 1;  	/*!< [09..09] Auto Buffer Clear Mode 	 							*/
			volatile uint16_t ATREPM 	: 1;  	/*!< [10..10] Auto Response Mode 		 							*/
			volatile uint16_t      		: 3;  	/*!< [13..11] Reserved  											*/
			volatile uint16_t INBUFM 	: 1;  	/*!< [14..14] Transfer Buffer Monitor 								*/
			volatile uint16_t BSTS 		: 1;  	/*!< [15..15] Buffer Status 			 							*/
		} BIT;
	} PIPE3CTR;
	union {
		volatile uint16_t WORD; 				/*!< (@ 0x00000076) PIPE4 Control Register 							*/
		struct {
			volatile uint16_t PID  		: 2;  	/*!< [01..00] Response PID 		  									*/
			volatile uint16_t      		: 3;  	/*!< [04..02] Reserved  											*/
			volatile uint16_t PBUSY 	: 1;  	/*!< [05..05] Pipe Busy 	 										*/
			volatile uint16_t SQMON 	: 1;  	/*!< [06..06] Sequence Toggle Bit Monitor  							*/
			volatile uint16_t SQSET 	: 1;  	/*!< [07..07] Sequence Toggle Bit Set 	 							*/
			volatile uint16_t SQCLR 	: 1;  	/*!< [08..08] Sequence Toggle Bit Clear  							*/
			volatile uint16_t ACLRM 	: 1;  	/*!< [09..09] Auto Buffer Clear Mode 	 							*/
			volatile uint16_t ATREPM 	: 1;  	/*!< [10..10] Auto Response Mode 		 							*/
			volatile uint16_t      		: 3;  	/*!< [13..11] Reserved  											*/
			volatile uint16_t INBUFM 	: 1;  	/*!< [14..14] Transfer Buffer Monitor 								*/
			volatile uint16_t BSTS 		: 1;  	/*!< [15..15] Buffer Status 			 							*/
		} BIT;
	} PIPE4CTR;
	union {
		volatile uint16_t WORD; 				/*!< (@ 0x00000078) PIPE5 Control Register 							*/
		struct {
			volatile uint16_t PID  		: 2;  	/*!< [01..00] Response PID 		  									*/
			volatile uint16_t      		: 3;  	/*!< [04..02] Reserved  											*/
			volatile uint16_t PBUSY 	: 1;  	/*!< [05..05] Pipe Busy 	 										*/
			volatile uint16_t SQMON 	: 1;  	/*!< [06..06] Sequence Toggle Bit Monitor  							*/
			volatile uint16_t SQSET 	: 1;  	/*!< [07..07] Sequence Toggle Bit Set 	 							*/
			volatile uint16_t SQCLR 	: 1;  	/*!< [08..08] Sequence Toggle Bit Clear  							*/
			volatile uint16_t ACLRM 	: 1;  	/*!< [09..09] Auto Buffer Clear Mode 	 							*/
			volatile uint16_t ATREPM 	: 1;  	/*!< [10..10] Auto Response Mode 		 							*/
			volatile uint16_t      		: 3;  	/*!< [13..11] Reserved  											*/
			volatile uint16_t INBUFM 	: 1;  	/*!< [14..14] Transfer Buffer Monitor 								*/
			volatile uint16_t BSTS 		: 1;  	/*!< [15..15] Buffer Status 			 							*/
		} BIT;
	} PIPE5CTR;
	union {
		volatile uint16_t WORD; 				/*!< (@ 0x0000007A) PIPE6 Control Register 							*/
		struct {
			volatile uint16_t PID  		: 2;  	/*!< [01..00] Response PID 		  									*/
			volatile uint16_t      		: 3;  	/*!< [04..02] Reserved  											*/
			volatile uint16_t PBUSY 	: 1;  	/*!< [05..05] Pipe Busy 	 										*/
			volatile uint16_t SQMON 	: 1;  	/*!< [06..06] Sequence Toggle Bit Monitor  							*/
			volatile uint16_t SQSET 	: 1;  	/*!< [07..07] Sequence Toggle Bit Set 	 							*/
			volatile uint16_t SQCLR 	: 1;  	/*!< [08..08] Sequence Toggle Bit Clear  							*/
			volatile uint16_t ACLRM 	: 1;  	/*!< [09..09] Auto Buffer Clear Mode 	 							*/
			volatile uint16_t      		: 5;  	/*!< [14..10] Reserved  											*/
			volatile uint16_t BSTS 		: 1;  	/*!< [15..15] Buffer Status 			 							*/
		} BIT;
	} PIPE6CTR;
	union {
		volatile uint16_t WORD; 				/*!< (@ 0x0000007C) PIPE7 Control Register 							*/
		struct {
			volatile uint16_t PID  		: 2;  	/*!< [01..00] Response PID 		  									*/
			volatile uint16_t      		: 3;  	/*!< [04..02] Reserved  											*/
			volatile uint16_t PBUSY 	: 1;  	/*!< [05..05] Pipe Busy 	 										*/
			volatile uint16_t SQMON 	: 1;  	/*!< [06..06] Sequence Toggle Bit Monitor  							*/
			volatile uint16_t SQSET 	: 1;  	/*!< [07..07] Sequence Toggle Bit Set 	 							*/
			volatile uint16_t SQCLR 	: 1;  	/*!< [08..08] Sequence Toggle Bit Clear  							*/
			volatile uint16_t ACLRM 	: 1;  	/*!< [09..09] Auto Buffer Clear Mode 	 							*/
			volatile uint16_t      		: 5;  	/*!< [14..10] Reserved  											*/
			volatile uint16_t BSTS 		: 1;  	/*!< [15..15] Buffer Status 			 							*/
		} BIT;
	} PIPE7CTR;
	union {
		volatile uint16_t WORD; 				/*!< (@ 0x0000007E) PIPE8 Control Register 							*/
		struct {
			volatile uint16_t PID  		: 2;  	/*!< [01..00] Response PID 		  									*/
			volatile uint16_t      		: 3;  	/*!< [04..02] Reserved  											*/
			volatile uint16_t PBUSY 	: 1;  	/*!< [05..05] Pipe Busy 	 										*/
			volatile uint16_t SQMON 	: 1;  	/*!< [06..06] Sequence Toggle Bit Monitor  							*/
			volatile uint16_t SQSET 	: 1;  	/*!< [07..07] Sequence Toggle Bit Set 	 							*/
			volatile uint16_t SQCLR 	: 1;  	/*!< [08..08] Sequence Toggle Bit Clear  							*/
			volatile uint16_t ACLRM 	: 1;  	/*!< [09..09] Auto Buffer Clear Mode 	 							*/
			volatile uint16_t      		: 5;  	/*!< [14..10] Reserved  											*/
			volatile uint16_t BSTS 		: 1;  	/*!< [15..15] Buffer Status 			 							*/
		} BIT;
	} PIPE8CTR;
	union {
		volatile uint16_t WORD; 				/*!< (@ 0x00000080) PIPE9 Control Register 							*/
		struct {
			volatile uint16_t PID  		: 2;  	/*!< [01..00] Response PID 		  									*/
			volatile uint16_t      		: 3;  	/*!< [04..02] Reserved  											*/
			volatile uint16_t PBUSY 	: 1;  	/*!< [05..05] Pipe Busy 	 										*/
			volatile uint16_t SQMON 	: 1;  	/*!< [06..06] Sequence Toggle Bit Monitor  							*/
			volatile uint16_t SQSET 	: 1;  	/*!< [07..07] Sequence Toggle Bit Set 	 							*/
			volatile uint16_t SQCLR 	: 1;  	/*!< [08..08] Sequence Toggle Bit Clear  							*/
			volatile uint16_t ACLRM 	: 1;  	/*!< [09..09] Auto Buffer Clear Mode 	 							*/
			volatile uint16_t      		: 5;  	/*!< [14..10] Reserved  											*/
			volatile uint16_t BSTS 		: 1;  	/*!< [15..15] Buffer Status 			 							*/
		} BIT;
	} PIPE9CTR;
	volatile uint16_t RESERVED12[7];
	union {
		volatile uint16_t WORD; 				/*!< (@ 0x00000090) PIPE1 Transaction Counter Enable Register 		*/
		struct {
			volatile uint16_t      		: 8;  	/*!< [07..00] Reserved  											*/
			volatile uint16_t TRCLR  	: 1;  	/*!< [08..08] Transaction Counter Clear 							*/
			volatile uint16_t TRENB 	: 1;  	/*!< [09..09] Transaction Counter Enable 							*/
			volatile uint16_t      		: 6;  	/*!< [15..10] Reserved  											*/
		} BIT;
	} PIPE1TRE;
	union {
		volatile uint16_t WORD; 				/*!< (@ 0x00000092) PIPE1 Transaction Counter Register 				*/
		volatile uint16_t TRNCNT; 				/*!< (@ 0x00000092) PIPE1 Transaction Counter Register 				*/
	} PIPE1TRN;
	union {
		volatile uint16_t WORD; 				/*!< (@ 0x00000094) PIPE2 Transaction Counter Enable Register 		*/
		struct {
			volatile uint16_t      		: 8;  	/*!< [07..00] Reserved  											*/
			volatile uint16_t TRCLR  	: 1;  	/*!< [08..08] Transaction Counter Clear 							*/
			volatile uint16_t TRENB 	: 1;  	/*!< [09..09] Transaction Counter Enable 							*/
			volatile uint16_t      		: 6;  	/*!< [15..10] Reserved  											*/
		} BIT;
	} PIPE2TRE;
	union {
		volatile uint16_t WORD; 				/*!< (@ 0x00000096) PIPE2 Transaction Counter Register 				*/
		volatile uint16_t TRNCNT; 				/*!< (@ 0x00000096) PIPE2 Transaction Counter Register 				*/
	} PIPE2TRN;
	union {
		volatile uint16_t WORD; 				/*!< (@ 0x00000098) PIPE3 Transaction Counter Enable Register 		*/
		struct {
			volatile uint16_t      		: 8;  	/*!< [07..00] Reserved  											*/
			volatile uint16_t TRCLR  	: 1;  	/*!< [08..08] Transaction Counter Clear 							*/
			volatile uint16_t TRENB 	: 1;  	/*!< [09..09] Transaction Counter Enable 							*/
			volatile uint16_t      		: 6;  	/*!< [15..10] Reserved  											*/
		} BIT;
	} PIPE3TRE;
	union {
		volatile uint16_t WORD; 				/*!< (@ 0x0000009A) PIPE3 Transaction Counter Register 				*/
		volatile uint16_t TRNCNT; 				/*!< (@ 0x0000009A) PIPE3 Transaction Counter Register 				*/
	} PIPE3TRN;
	union {
		volatile uint16_t WORD; 				/*!< (@ 0x0000009C) PIPE4 Transaction Counter Enable Register 		*/
		struct {
			volatile uint16_t      		: 8;  	/*!< [07..00] Reserved  											*/
			volatile uint16_t TRCLR  	: 1;  	/*!< [08..08] Transaction Counter Clear 							*/
			volatile uint16_t TRENB 	: 1;  	/*!< [09..09] Transaction Counter Enable 							*/
			volatile uint16_t      		: 6;  	/*!< [15..10] Reserved  											*/
		} BIT;
	} PIPE4TRE;
	union {
		volatile uint16_t WORD; 				/*!< (@ 0x0000009E) PIPE4 Transaction Counter Register 				*/
		volatile uint16_t TRNCNT; 				/*!< (@ 0x0000009E) PIPE4 Transaction Counter Register 				*/
	} PIPE4TRN;
	union {
		volatile uint16_t WORD; 				/*!< (@ 0x000000A0) PIPE5 Transaction Counter Enable Register 		*/
		struct {
			volatile uint16_t      		: 8;  	/*!< [07..00] Reserved  											*/
			volatile uint16_t TRCLR  	: 1;  	/*!< [08..08] Transaction Counter Clear 							*/
			volatile uint16_t TRENB 	: 1;  	/*!< [09..09] Transaction Counter Enable 							*/
			volatile uint16_t      		: 6;  	/*!< [15..10] Reserved  											*/
		} BIT;
	} PIPE5TRE;
	union {
		volatile uint16_t WORD; 				/*!< (@ 0x000000A2) PIPE5 Transaction Counter Register 				*/
		volatile uint16_t TRNCNT; 				/*!< (@ 0x000000A2) PIPE5 Transaction Counter Register 				*/
	} PIPE5TRN;
	volatile uint16_t RESERVED13[2];
	union {
		volatile uint16_t WORD; 				/*!< (@ 0x000000A8) DTC0-FIFO Pin Configuration Register 			*/
		struct {
			volatile uint16_t D0DBLK  	: 1;  	/*!< [00..00] DTC Block transmission Mode 							*/
			volatile uint16_t      		:15;  	/*!< [15..01] Reserved  											*/
		} BIT;
	} DTC0PCFG;
	volatile uint16_t RESERVED14;
	union {
		volatile uint16_t WORD; 				/*!< (@ 0x000000AC) DTC1-FIFO Pin Configuration Register 			*/
		struct {
			volatile uint16_t D1DBLK  	: 1;  	/*!< [00..00] DTC Block transmission Mode 							*/
			volatile uint16_t      		:15;  	/*!< [15..01] Reserved  											*/
		} BIT;
	} DTC1PCFG;
	volatile uint16_t RESERVED15;
	union {
		volatile uint16_t WORD; 				/*!< (@ 0x000000B0) BC (Battery Charge) Control Register 			*/
		struct {
			volatile uint16_t RPDME0  	: 1;  	/*!< [00..00] DM0 Pin Pull-Down Control 							*/
			volatile uint16_t IDPSRCE0 	: 1;  	/*!< [01..01] DP0 Pin IDPSRC(10uA) Output Control 					*/
			volatile uint16_t IDMSINKE0 : 1;  	/*!< [02..02] DM0 Pin 0.6V Input Detection Control 					*/
			volatile uint16_t VDPSRCE0 	: 1;  	/*!< [03..03] DP0 Pin VDPSRC(0.6V) Output Control 					*/
			volatile uint16_t IDPSINKE0 : 1;  	/*!< [04..04] DP0 Pin 0.6V Input Detection Control 					*/
			volatile uint16_t VDMSRCE0 	: 1;  	/*!< [05..05] DM0 Pin VDMSRC(0.6V) Output Control 					*/
			volatile uint16_t DCPMODE  	: 1;  	/*!< [06..06] DCP Mode   											*/
			volatile uint16_t BATCHGE0 	: 1;  	/*!< [07..07] BC (Battery Charger) Function General Enable Control 	*/
			volatile uint16_t CHGDETSTS0: 1;  	/*!< [08..08] DM0 Pin 0.6V Input Detection Status				 	*/
			volatile uint16_t PDDETSTS0 : 1;  	/*!< [09..09] DP0 Pin 0.6V Input Detection Status 			 		*/
			volatile uint16_t      		: 6;  	/*!< [15..10] Reserved  											*/
		} BIT;
	} BCCTRL0;
	volatile uint16_t RESERVED16;
	union {
		volatile uint16_t WORD; 				/*!< (@ 0x000000B4) BC (Battery Charge) Control Register 			*/
		struct {
			volatile uint16_t RPDME1  	: 1;  	/*!< [00..00] DM1 Pin Pull-Down Control 							*/
			volatile uint16_t IDPSRCE1 	: 1;  	/*!< [01..01] DP1 Pin IDPSRC(10uA) Output Control 					*/
			volatile uint16_t IDMSINKE1 : 1;  	/*!< [02..02] DM1 Pin 0.6V Input Detection Control 					*/
			volatile uint16_t VDPSRCE1 	: 1;  	/*!< [03..03] DP1 Pin VDPSRC(0.6V) Output Control 					*/
			volatile uint16_t IDPSINKE1 : 1;  	/*!< [04..04] DP1 Pin 0.6V Input Detection Control 					*/
			volatile uint16_t VDMSRCE1 	: 1;  	/*!< [05..05] DM1 Pin VDMSRC(0.6V) Output Control 					*/
			volatile uint16_t      		: 1;  	/*!< [06..06] Reserved  											*/
			volatile uint16_t BATCHGE1 	: 1;  	/*!< [07..07] BC (Battery Charger) Function General Enable Control 	*/
			volatile uint16_t CHGDETSTS1: 1;  	/*!< [08..08] DM1 Pin 0.6V Input Detection Status				 	*/
			volatile uint16_t PDDETSTS1 : 1;  	/*!< [09..09] DP1 Pin 0.6V Input Detection Status 			 		*/
			volatile uint16_t      		: 6;  	/*!< [15..10] Reserved  											*/
		} BIT;
	} BCCTRL1;
	volatile uint16_t RESERVED17;
	union { 
		volatile uint16_t WORD; 				/*!< (@ 0x000000B8) BC (Battery Charge) Option Control Register 	*/
		struct {
			volatile uint16_t VDSEL0  	: 4;  	/*!< [03..00] DP0/DM0 Pin Custom Output/Compare Voltage Select 		*/
			volatile uint16_t      		: 1;  	/*!< [04..04] Reserved  											*/
			volatile uint16_t VDOUTE0 	: 1;  	/*!< [05..05] Custom Voltage Output Control 						*/
			volatile uint16_t CUSDETE0 	: 1;  	/*!< [06..06] Custom Voltage Detecton Control 						*/
			volatile uint16_t ADCMONE0 	: 1;  	/*!< [07..07] DP0/DM0 Pin and ADC Channel Connection Control 		*/
			volatile uint16_t DPCUSDET0	: 1;  	/*!< [08..08] DP0 Pin Voltage Detection 		 					*/
			volatile uint16_t DMCUSDET0	: 1;  	/*!< [09..09] DM0 Pin Voltage Detection  							*/
			volatile uint16_t      		: 4;  	/*!< [13..10] Reserved  											*/
			volatile uint16_t RPDPE0	: 1;  	/*!< [14..14] DP0 Pull Down Control 								*/
			volatile uint16_t IDMSRCE0	: 1;  	/*!< [15..15] DM0 Pin IDMSRC (10uA) Control 						*/
		} BIT;
	} USBBCOPT0;
	volatile uint16_t RESERVED18;
	union { 
		volatile uint16_t WORD; 				/*!< (@ 0x000000BC) BC (Battery Charge) Option Control Register 	*/
		struct {
			volatile uint16_t VDSEL1  	: 4;  	/*!< [03..00] DP1/DM1 Pin Custom Output/Compare Voltage Select 		*/
			volatile uint16_t      		: 1;  	/*!< [04..04] Reserved  											*/
			volatile uint16_t VDOUTE1 	: 1;  	/*!< [05..05] Custom Voltage Output Control 						*/
			volatile uint16_t CUSDETE1 	: 1;  	/*!< [06..06] Custom Voltage Detecton Control 						*/
			volatile uint16_t ADCMONE1 	: 1;  	/*!< [07..07] DP1/DM1 Pin and ADC Channel Connection Control 		*/
			volatile uint16_t DPCUSDET1	: 1;  	/*!< [08..08] DP1 Pin Voltage Detection 		 					*/
			volatile uint16_t DMCUSDET1	: 1;  	/*!< [09..09] DM1 Pin Voltage Detection  							*/
			volatile uint16_t      		: 4;  	/*!< [13..10] Reserved  											*/
			volatile uint16_t RPDPE1	: 1;  	/*!< [14..14] DP1 Pull Down Control 								*/
			volatile uint16_t IDMSRCE1	: 1;  	/*!< [15..15] DM1 Pin IDMSRC (10uA) Control 						*/
		} BIT;
	} USBBCOPT1;
	volatile uint16_t RESERVED19;
	union { 
		volatile uint16_t WORD; 				/*!< (@ 0x000000C0) USB Test Register 								*/
		struct {
			volatile uint16_t USB_ICOMP : 1;  	/*!< [00..00] Bias Resistor Compare Result Output 			 		*/
			volatile uint16_t USB_ITEST : 1;  	/*!< [01..01] Bias Resistor Adjustment Mode 						*/
			volatile uint16_t TEST_CALPCON : 1; /*!< [02..02] Force CALPCB Control 		 							*/
			volatile uint16_t      		: 1;  	/*!< [03..03] Reserved  											*/
			volatile uint16_t NCOMPMON 	: 1;  	/*!< [04..04] PHY-NCOMP Monitor 									*/
			volatile uint16_t PCOMPMON 	: 1;  	/*!< [05..05] PHY-PCOMP Monitor 									*/
			volatile uint16_t      		: 8;  	/*!< [13..06] Reserved  											*/
			volatile uint16_t DMRPU1 	: 1;  	/*!< [14..14] DM1 Pull Up Control 									*/
			volatile uint16_t DPRPU1 	: 1;  	/*!< [15..15] DP1 Pull Up Control 									*/
		} BIT;
	} USB_TEST;
	union { 
		volatile uint16_t WORD; 				/*!< (@ 0x000000C2) USB-PHY Output Impedance Adjustment Register 	*/
		struct {
			volatile uint16_t TNDATA 	: 4;  	/*!< [03..00] USB-PHY NMOS Output Impedance Adjustment 		 		*/
			volatile uint16_t TPDATA 	: 4;  	/*!< [07..04] USB-PHY PMOS Output Impedance Adjustment 		 		*/
			volatile uint16_t      		: 8;  	/*!< [15..08] Reserved  											*/
		} BIT;
	} USB_TDATA;
	union { 
		volatile uint16_t WORD; 				/*!< (@ 0x000000C4) USB Clock Recovery Control Register 			*/
		struct {
			volatile uint16_t CKRECC 	: 1;  	/*!< [00..00] USB Clock Recovery Enable 					 		*/
			volatile uint16_t      		:15;  	/*!< [15..01] Reserved  											*/
		} BIT;
	} CKREC;
	union { 
		volatile uint16_t WORD; 				/*!< (@ 0x000000C6) USB Clock Recovery Trim Value Monitor 			*/
		struct {
			volatile uint16_t REC_FTRIM : 6;  	/*!< [05..00] USB Clock Recovery FTRIM Value Monitor 		 		*/
			volatile uint16_t      		: 2;  	/*!< [07..06] Reserved  											*/
			volatile uint16_t REC_SOFC  : 8;  	/*!< [15..08] SOF Packet Detection Counter  						*/
		} BIT;
	} REC_MON;
	union { 
		volatile uint16_t WORD; 				/*!< (@ 0x000000C8) USB VDC Test Register 				 			*/
		struct {
			volatile uint16_t USB_PMON 	: 1;  	/*!< [00..00] USB VDC Voltage Monitor Control 				 		*/
			volatile uint16_t      		:15;  	/*!< [15..01] Reserved  											*/
		} BIT;
	} USBVDC_TEST;
	union { 
		volatile uint16_t WORD; 				/*!< (@ 0x000000CA) USB-PHY Output Impedance Adjustment Test Register 	*/
		struct {
			volatile uint16_t USB_TRST 	: 1;  	/*!< [00..00] USB-PHY Trimming Start 								*/
			volatile uint16_t      		:15;  	/*!< [15..01] Reserved  											*/
		} BIT;
	} USBPHY_TEST;
	union { 
		volatile uint16_t WORD; 				/*!< (@ 0x000000CC) USB Module Control Register 					*/
		struct {
			volatile uint16_t VDDUSBE 	: 1;  	/*!< [00..00] USB VDC Enable 		 								*/
			volatile uint16_t PXXCON 	: 1;  	/*!< [01..01] USB VDC Pull Down Control 							*/
			volatile uint16_t      		: 5;  	/*!< [06..02] Reserved  											*/
			volatile uint16_t VBRPDCUT 	: 1;  	/*!< [07..07] VBUS Pin Pull Down Stop  								*/
			volatile uint16_t      		: 8;  	/*!< [15..08] Reserved  											*/
		} BIT;
	} USBMC;
	volatile uint16_t RESERVED20;
	union { 
		volatile uint16_t WORD; 				/*!< (@ 0x000000D0) Device Address Configuration Register 			*/
		struct {
			volatile uint16_t RTPORT 	: 1;  	/*!< [00..00] Root Hub Port Number 	 								*/
			volatile uint16_t      		: 5;  	/*!< [05..01] Reserved  											*/
			volatile uint16_t USBSPD 	: 2;  	/*!< [07..06] Transfer Speed of communication target device 		*/
			volatile uint16_t      		: 8;  	/*!< [15..08] Reserved  											*/
		} BIT;
	} DEVADD0;
	union { 
		volatile uint16_t WORD; 				/*!< (@ 0x000000D2) Device Address Configuration Register 			*/
		struct {
			volatile uint16_t RTPORT 	: 1;  	/*!< [00..00] Root Hub Port Number 	 								*/
			volatile uint16_t      		: 5;  	/*!< [05..01] Reserved  											*/
			volatile uint16_t USBSPD 	: 2;  	/*!< [07..06] Transfer Speed of communication target device 		*/
			volatile uint16_t      		: 8;  	/*!< [15..08] Reserved  											*/
		} BIT;
	} DEVADD1;
	union { 
		volatile uint16_t WORD; 				/*!< (@ 0x000000D4) Device Address Configuration Register 			*/
		struct {
			volatile uint16_t RTPORT 	: 1;  	/*!< [00..00] Root Hub Port Number 	 								*/
			volatile uint16_t      		: 5;  	/*!< [05..01] Reserved  											*/
			volatile uint16_t USBSPD 	: 2;  	/*!< [07..06] Transfer Speed of communication target device 		*/
			volatile uint16_t      		: 8;  	/*!< [15..08] Reserved  											*/
		} BIT;
	} DEVADD2;
	union { 
		volatile uint16_t WORD; 				/*!< (@ 0x000000D6) Device Address Configuration Register 			*/
		struct {
			volatile uint16_t RTPORT 	: 1;  	/*!< [00..00] Root Hub Port Number 	 								*/
			volatile uint16_t      		: 5;  	/*!< [05..01] Reserved  											*/
			volatile uint16_t USBSPD 	: 2;  	/*!< [07..06] Transfer Speed of communication target device 		*/
			volatile uint16_t      		: 8;  	/*!< [15..08] Reserved  											*/
		} BIT;
	} DEVADD3;
	union { 
		volatile uint16_t WORD; 				/*!< (@ 0x000000D8) Device Address Configuration Register 			*/
		struct {
			volatile uint16_t RTPORT 	: 1;  	/*!< [00..00] Root Hub Port Number 	 								*/
			volatile uint16_t      		: 5;  	/*!< [05..01] Reserved  											*/
			volatile uint16_t USBSPD 	: 2;  	/*!< [07..06] Transfer Speed of communication target device 		*/
			volatile uint16_t      		: 8;  	/*!< [15..08] Reserved  											*/
		} BIT;
	} DEVADD4;
	union { 
		volatile uint16_t WORD; 				/*!< (@ 0x000000DA) Device Address Configuration Register 			*/
		struct {
			volatile uint16_t RTPORT 	: 1;  	/*!< [00..00] Root Hub Port Number 	 								*/
			volatile uint16_t      		: 5;  	/*!< [05..01] Reserved  											*/
			volatile uint16_t USBSPD 	: 2;  	/*!< [07..06] Transfer Speed of communication target device 		*/
			volatile uint16_t      		: 8;  	/*!< [15..08] Reserved  											*/
		} BIT;
	} DEVADD5;
}USB_Type;

/***********************************************************************************************************************
Macro definitions (Register)
************************************************************************************************************************/
#define USB0 (*(USB_Type*) 		USBF_BASE)


#endif
