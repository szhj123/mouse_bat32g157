
#ifndef QSPI_H
#define QSPI_H

/**************************************************************************
* QSPI Registers defination
**************************************************************************/
#define SFMSMD  (*((volatile uint32_t *)0x64000000))
#define SFMSSC  (*((volatile uint32_t *)0x64000004))
#define SFMSKC  (*((volatile uint32_t *)0x64000008))
#define SFMSST  (*((volatile uint32_t *)0x6400000C))
#define SFMCOM  (*((volatile uint32_t *)0x64000010))
#define SFMCMD  (*((volatile uint32_t *)0x64000014))
#define SFMCST  (*((volatile uint32_t *)0x64000018))
#define SFMSIC  (*((volatile uint32_t *)0x64000020))
#define SFMSAC  (*((volatile uint32_t *)0x64000024))
#define SFMSDC  (*((volatile uint32_t *)0x64000028))
#define SFMSPC  (*((volatile uint32_t *)0x64000030))
#define SFMPMD  (*((volatile uint32_t *)0x64000034))
#define SFMDMA  (*((volatile uint32_t *)0x6400080C))
#define SFMCRPT (*((volatile uint32_t *)0x64000810))
//#define BYTE_FIELD(value, byte) ((adr & (0xFF << 8 * byte )) >> 8 * byte)
#define BYTE_FIELD(value, byte) ((value & (0xFF << 8 * byte )) >> 8 * byte)

/**************************************************************************
* Bit Fields defination
**************************************************************************/
// Status Register-1
#define BUSY_Pos  (0x00U)
#define BUSY_Msk  (0x01U)
#define WEL_Pos   (0x01U)
#define WEL_Msk   (0x02U)
#define BP_Pos    (0x04U)
#define BP_Msk    (0x30U)
#define TB_Pos    (0x06U)
#define TB_Msk    (0x40U)
#define BPL_Pos   (0x07U)
#define BPS_Msk   (0x80U)
// Status Register-2
#define QE_Pos    (0x01U)
#define QE_Msk    (0x02U)

/**************************************************************************
* Typedef defination
**************************************************************************/
typedef enum
{
	STATUS_REG1 = 1,
	STATUS_REG2 = 2
} status_t;

/**************************************************************************
* Global functions
**************************************************************************/
__STATIC_INLINE void SoftReset(void)
{
	SFMCMD = 0x01U; // Direct communication mode
	SFMCOM = 0x66U; // Enable Reset
	SFMCMD = 0x01U; // close SPI bus cycle
	SFMCOM = 0x99U; // Reset
	SFMCMD = 0x01U; // close SPI bus cycle
	SFMCMD = 0x00U; // ROM access mode
}

__STATIC_INLINE uint8_t ReadStatus(status_t name)
{
	uint8_t tmp;
	SFMCMD = 0x01U; // Direct communication mode
	if(name == STATUS_REG1)
		SFMCOM = 0x05U; // Read Status Register-1
	else
		SFMCOM = 0x35U; // Read Status Register-2
	tmp = (uint8_t)SFMCOM; // Read Status
	SFMCMD = 0x01U; // close SPI bus cycle
	SFMCMD = 0x00U; // ROM access mode
	return tmp;
}

__STATIC_INLINE void WriteStatus(status_t name, uint8_t data)
{
	SFMSSC = 0x0FU; // the leading/trailing edge of SSB is 0.5 SCK, SSB high-level width 16 SCK
	SFMCMD = 0x01U; // Direct communication mode
	SFMCOM = 0x06U; // Write Enable Instruction
	SFMCMD = 0x01U; // close SPI bus cycle

	if(name == STATUS_REG1)
		SFMCOM = 0x01U; // Write Status Register-1
	else
		SFMCOM = 0x31U; // Write Status Register-2
	SFMCOM = data;  // Write Status
	SFMCMD = 0x01U; // close SPI bus cycle

	SFMCOM = 0x05U; // Read Status Register-1 Instruction
	while(SFMCOM & BUSY_Msk);
	SFMCMD = 0x01U; // close SPI bus cycle

	SFMCMD = 0x00U; // ROM access mode
}

__STATIC_INLINE void EnableQPI(void)
{
	SFMCMD = 0x01U; // Direct communication mode
	SFMCOM = 0x38U; // Enable QPI
	SFMCMD = 0x01U; // close SPI bus cycle
	SFMCMD = 0x00U; // ROM access mode
}

__STATIC_INLINE void DisableQPI(void)
{
	SFMCMD = 0x01U; // Direct communication mode
	SFMCOM = 0xFFU; // Disable QPI
	SFMCMD = 0x01U; // close SPI bus cycle
	SFMCMD = 0x00U; // ROM access mode
}
__STATIC_INLINE void EraseSector(uint32_t adr)
{
	SFMSSC = 0x0FU; // the leading/trailing edge of SSB is 0.5 SCK, SSB high-level width 16 SCK
	SFMCMD = 0x01U; // Direct communication mode
	SFMCOM = 0x06U; // Write Enable Instruction
	SFMCMD = 0x01U; // close SPI bus cycle

	SFMCOM = 0x20U; // Sector Erase Instruction
	SFMCOM = BYTE_FIELD(adr, 2); // Address [23:16] 
	SFMCOM = BYTE_FIELD(adr, 1); // Address [15:08] 
	SFMCOM = BYTE_FIELD(adr, 0); // Address [07:00] 
	SFMCMD = 0x01U; // close SPI bus cycle

	SFMCOM = 0x05U; // Read Status Register-1 Instruction
	while(SFMCOM & BUSY_Msk);
	SFMCMD = 0x01U; // close SPI bus cycle
	SFMCMD = 0x00U; // ROM access mode
}

__STATIC_INLINE void EraseBlock(uint32_t adr)
{
	SFMSSC = 0x0FU; // the leading/trailing edge of SSB is 0.5 SCK, SSB high-level width 16 SCK
	SFMCMD = 0x01U; // Direct communication mode
	SFMCOM = 0x06U; // Write Enable Instruction
	SFMCMD = 0x01U; // close SPI bus cycle

	SFMCOM = 0x52U; // 16KB Block Erase Instruction
	SFMCOM = BYTE_FIELD(adr, 2); // Address [23:16] 
	SFMCOM = BYTE_FIELD(adr, 1); // Address [15:08] 
	SFMCOM = BYTE_FIELD(adr, 0); // Address [07:00] 
	SFMCMD = 0x01U; // close SPI bus cycle

	// polling BUSY Flag 
	SFMCOM = 0x05U; // Read Status Register-1 Instruction
	while(SFMCOM & BUSY_Msk);
	SFMCMD = 0x01U; // close SPI bus cycle
	SFMCMD = 0x00U; // ROM access mode
}

__STATIC_INLINE void EraseChip(void)
{
	uint8_t tmp;

	SFMSSC = 0x0FU; // the leading/trailing edge of SSB is 0.5 SCK, SSB high-level width 16 SCK
	SFMCMD = 0x01U; // Direct communication mode
	SFMCOM = 0x06U; // Write Enable Instruction
	SFMCMD = 0x01U; // close SPI bus cycle

	SFMCOM = 0x60U; // Chip Erase Instruction
	SFMCMD = 0x01U; // close SPI bus cycle

	// polling BUSY Flag 
	do {
	    SFMCOM = 0x05U; // Read Status Register-1 Instruction
		tmp = (uint8_t)SFMCOM;
	    SFMCMD = 0x01U; // close SPI bus cycle
	} while(tmp & BUSY_Msk);
	SFMCMD = 0x00U; // ROM access mode
}

__STATIC_INLINE void ProgramPage(uint32_t adr, uint32_t sz, uint8_t *buf)
{
	SFMSSC = 0x0FU; // the leading/trailing edge of SSB is 0.5 SCK, SSB high-level width 16 SCK
	SFMCMD = 0x01U; // Direct communication mode
	SFMCOM = 0x06U; // Write Enable Instruction
	SFMCMD = 0x01U; // close SPI bus cycle

	SFMCOM = 0x02U; // Page Program Instruction
	SFMCOM = BYTE_FIELD(adr, 2); // Address [23:16] 
	SFMCOM = BYTE_FIELD(adr, 1); // Address [15:08] 
	SFMCOM = BYTE_FIELD(adr, 0); // Address [07:00] 

	while(sz--)
	{
		SFMCOM = *buf++; // Write Data Byte
	}
	SFMCMD = 0x01U; // close SPI bus cycle

	// polling BUSY Flag 
	SFMCOM = 0x05U; // Read Status Register-1 Instruction
	while(SFMCOM & BUSY_Msk);
	SFMCMD = 0x01U; // close SPI bus cycle
	SFMCMD = 0x00U; // ROM access mode
}



#endif
