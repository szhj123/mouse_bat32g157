#ifndef SSI_H
#define SSI_H

#include "BAT32G157.h"

/***********************************************************************************************************************
Typedef definitions (Struct)
************************************************************************************************************************/
typedef struct st_ssie{
	union {
		volatile uint32_t WORD; 			/*!< (@ 0x00000000) SSI Control Register   					*/
		struct {
			volatile uint32_t REN 	  : 1; 	/*!< [0..0] Reception Enable 								*/
			volatile uint32_t TEN 	  : 1; 	/*!< [1..1] Transmission Enable 							*/
			volatile uint32_t   	  : 1; 
			volatile uint32_t MUTEN   : 1; 	/*!< [3..3] Mute Enable 									*/
			volatile uint32_t CKDV    : 4; 	/*!< [7..4] Bit Clock Division Ratio 						*/ 
			volatile uint32_t DEL 	  : 1; 	/*!< [8..8] Serial Data Delay 								*/
			volatile uint32_t PDTA 	  : 1; 	/*!< [9..9] Placement Data Alignment 						*/
			volatile uint32_t SDTA 	  : 1; 	/*!< [10..10] Serial Data Alignment 						*/
			volatile uint32_t SPDP 	  : 1; 	/*!< [11..11] Serial Padding Polarity 						*/
			volatile uint32_t LRCKP   : 1; 	/*!< [12..12] LRCK initial value and Polarity 				*/
			volatile uint32_t BCKP    : 1; 	/*!< [13..13] Bit clock Polarity 							*/
			volatile uint32_t MST     : 1; 	/*!< [14..14] Master Enable 								*/
			volatile uint32_t   	  : 1; 
			volatile uint32_t SWL     : 3; 	/*!< [18..16] System Word Length 							*/
			volatile uint32_t DWL     : 3; 	/*!< [21..19] Data Word Length  							*/
			volatile uint32_t FRM  	  : 2;  /*!< [23..22] Channel 										*/
			volatile uint32_t   	  : 1; 
			volatile uint32_t IIEN    : 1; 	/*!< [25..25] Idle Interrupt Output Enable 					*/
			volatile uint32_t ROIEN   : 1; 	/*!< [26..26] Receive Overflow Interrupt Output Enable 		*/
			volatile uint32_t RUIEN   : 1; 	/*!< [27..27] Receive Underflow Interrupt Output Enable 	*/
			volatile uint32_t TOIEN   : 1; 	/*!< [28..28] Transmit Overflow Interrupt Output Enable 	*/
			volatile uint32_t TUIEN   : 1; 	/*!< [29..29] Transmit Underflow Interrupt Output Enable 	*/
			volatile uint32_t CKS     : 1; 	/*!< [30..30] Select an Audio clock for Master Mode  		*/
			volatile uint32_t   	  : 1; 
		} BIT;
	} SSICR;

	union {
		volatile uint32_t WORD; 			/*!< (@ 0x00000004) SSI Status Register   					*/
		struct {
			volatile uint32_t   	  : 25; 
			volatile uint32_t IIRQ    : 1; 	/*!< [25..25] Idle Status Flag  							*/
			volatile uint32_t ROIRQ   : 1; 	/*!< [26..26] Receive Overflow Error Status Flag 			*/
			volatile uint32_t RUIRQ   : 1; 	/*!< [27..27] Receive Underflow Error Status Flag 			*/
			volatile uint32_t TOIRQ   : 1; 	/*!< [28..28] Transmit Overflow Error Status Flag 			*/
			volatile uint32_t TUIRQ   : 1; 	/*!< [29..29] Transmit Underflow Error Status Flag 			*/
			volatile uint32_t   	  : 2; 
		} BIT;
	} SSISR;

	uint32_t RESERVED[2];

	union {
		volatile uint32_t WORD; 			/*!< (@ 0x00000010) FIFO Control Register  					*/
		struct {
			volatile uint32_t RFRST   : 1; 	/*!< [0..0] Receive FIFO Reset 								*/
			volatile uint32_t TFRST	  : 1; 	/*!< [1..1] Transmit FIFO Reset  							*/
			volatile uint32_t RIE     : 1; 	/*!< [2..2] Receive Data Full Interrupt Enable 				*/
			volatile uint32_t TIE     : 1; 	/*!< [3..3] Transmit Data Empty Interrupt Enable 			*/
			volatile uint32_t   	  : 7; 
			volatile uint32_t BSW     : 1; 	/*!< [11..11] Byte Swap Enable  							*/
			volatile uint32_t   	  : 4; 
			volatile uint32_t SSIRST  : 1; 	/*!< [16..16] Software Reset 	  							*/
			volatile uint32_t   	  : 14; 
			volatile uint32_t AUCKE   : 1; 	/*!< [31..31] AUDIO_MCK Enable in Master Communication Mode */
		} BIT;
	} SSIFCR;

	union {
		volatile uint32_t WORD; 			/*!< (@ 0x00000014) FIFO Status Register  					*/
		struct {
			volatile uint32_t RDF     : 1; 	/*!< [0..0] Receive Data Full Flag 							*/
			volatile uint32_t   	  : 7; 
			volatile uint32_t RDC	  : 4; 	/*!< [11..8] Number of Receive FIFO Data Indication Flag  	*/
			volatile uint32_t   	  : 4; 
			volatile uint32_t TDE     : 1; 	/*!< [16..16] Transmit Data Empty Flag 		 				*/
			volatile uint32_t   	  : 7; 
			volatile uint32_t TDC	  : 4; 	/*!< [27..24] Number of Transmit FIFO Data Indication Flag  */
			volatile uint32_t   	  : 4; 
		} BIT;
	} SSIFSR;

	union { 							/*!< (@ 0x00000018) Transmit FIFO Data Register  			*/
		volatile uint8_t  BYTE;  		/*!< [31..24] Transmit Data: 8bits 							*/
		volatile uint16_t HALF; 		/*!< [31..16] Transmit Data: 16bits 						*/
		volatile uint32_t WORD;  		/*!< [31..00] Transmit Data: 32bits 			 			*/
	} SSIFTDR;

	union { 							/*!< (@ 0x0000001C) Receive FIFO Data Register  			*/
		volatile uint8_t  BYTE;  		/*!< [31..24] Receive Data: 8bits 							*/
		volatile uint16_t HALF; 		/*!< [31..16] Receive Data: 16bits 							*/
		volatile uint32_t WORD;  		/*!< [31..00] Receive Data: 32bits 				 			*/
	} SSIFRDR;

	union {
		volatile uint32_t WORD; 			/*!< (@ 0x00000020) Output Format Register  				*/
		struct {
			volatile uint32_t OMOD    : 2; 	/*!< [1..0] Audio Format Selection 							*/
			volatile uint32_t   	  : 6; 
			volatile uint32_t LRCONT  : 1; 	/*!< [8..8] Enable LRCK/FS continuation 	 				*/
			volatile uint32_t BCKASTP : 1; 	/*!< [9..9] Stop BCK output when idle status 				*/
			volatile uint32_t   	  : 18; 
		} BIT;
	} SSIOFR;

	union {
		volatile uint32_t WORD; 			/*!< (@ 0x00000024) Status Control Register  				*/
		struct {
			volatile uint32_t RDFS    : 3; 	/*!< [2..0] RDF condition selection  						*/
			volatile uint32_t   	  : 5; 
			volatile uint32_t TDES    : 3; 	/*!< [10..8] TDE condition selection 						*/
			volatile uint32_t   	  : 21; 
		} BIT;
	} SSISCR;

} SSIE_Type;


/***********************************************************************************************************************
Macro definitions (Register)
************************************************************************************************************************/
#define SSIE0 (*(SSIE_Type*) 		SSI_BASE)

#endif
