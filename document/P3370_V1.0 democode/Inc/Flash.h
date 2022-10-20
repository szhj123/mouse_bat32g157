#ifndef _FLASH_H_
#define _FLASH_H_

#include "Type.h"
#include "Main.h"

#ifdef _FLASH_C_
#define INTERFACE
#else
#define INTERFACE extern
#endif

#define _Flash_Debug_(y) //y 

#define Sector_0_Start_Adr 0x00000000
#define Sector_1_Start_Adr 0x00001000
#define Sector_2_Start_Adr 0x00002000
#define Sector_3_Start_Adr 0x00003000
#define Sector_4_Start_Adr 0x00004000
#define Sector_5_Start_Adr 0x00005000/*LPC1113*/
#define Sector_6_Start_Adr 0x00006000
#define Sector_7_Start_Adr 0x00007000/*LPC1114*/

#define Sector_0_End_Adr 0x00000FFF
#define Sector_1_End_Adr 0x00001FFF
#define Sector_2_End_Adr 0x00002FFF
#define Sector_3_End_Adr 0x00003FFF
#define Sector_4_End_Adr 0x00004FFF
#define Sector_5_End_Adr 0x00005FFF/*LPC1113*/
#define Sector_6_End_Adr 0x00006FFF
#define Sector_7_End_Adr 0x00007FFF/*LPC1114*/

#define Sector_0 0
#define Sector_1 1
#define Sector_2 2
#define Sector_3 3
#define Sector_4 4
#define Sector_5 5/*LPC1113*/
#define Sector_6 6
#define Sector_7 7/*LPC1114*/

#define AppCode_StartAdr Sector_3_Start_Adr 
#define AppCode_StartSector Sector_3
#define AppCode_EndSector Sector_7

#define AppUpgrade_EndAdr Sector_7_End_Adr
#define AppUpgrade_ReserveLen 0xFF				//need check
#define AppUpgrade_Adr (AppUpgrade_EndAdr -AppUpgrade_ReserveLen)
#define AppUpgrade_FlagAdr AppUpgrade_Adr 

#define R2FBUFSIZE 256
#define Vectors_Table_Size 0x100 

#define AppID 0x5A5A

#define AppID_Adr 0x00003100
#define AppVer_Adr 0x00001104
#define AppNonUpgradeID 0xCA//AC
#define AppReqUpgradeID 0xAC//CA
#define BL_NORMAL 0xAA//BB
#define AP_MAIN_OFFSET	0x001C
#define ID_SUCCESS 0xFE


/* IAP Command Definitions */
#define	IAP_CMD_PREPARE_SECTORS 		50
#define	IAP_CMD_COPY_RAM_TO_FLASH 		51
#define	IAP_CMD_ERASE_SECTORS 			52
#define	IAP_CMD_BLANK_CHECK_SECTORS		53
#define	IAP_CMD_READ_PART_ID			54
#define	IAP_CMD_READ_BOOT_ROM_VERSION 	55
#define	IAP_CMD_COMPARE 				56
#define	IAP_CMD_REINVOKE_ISP 			57

/* IAP Command Status Codes */
#define IAP_STA_CMD_SUCCESS 0
#define IAP_STA_INVALID_COMMAND 1
#define IAP_STA_SRC_ADDR_ERROR 2
#define IAP_STA_DST_ADDR_ERROR 3
#define IAP_STA_SRC_ADDR_NOT_MAPPED 4
#define IAP_STA_DST_ADDR_NOT_MAPPED 5
#define IAP_STA_COUNT_ERROR 6
#define IAP_STA_INVALID_SECTOR 7
#define IAP_STA_SECTOR_NOT_BLANK 8
#define IAP_STA_SECTOR_NOT_PREPARED_FOR_WRITE_OPERATION 9
#define IAP_STA_COMPARE_ERROR 10
#define IAP_STA_BUSY 11
#define IAP_STA_INVALD_PARAM 12


#define IAP_CLK (Fcclk /1000)

/* IAP boot ROM location and access function */
#define IAP_ROM_LOCATION 0x1FFF1FF1UL
//				(U32 *)	0x1FFF1FF1
#define IAP_EXECUTE_CMD(a, b) ((void (*)())(IAP_ROM_LOCATION))(a, b) 


typedef U8 BOOLEAN;
typedef U8 BootLean;
#define MSEL 0x00000003
#define Fcclk (__SYS_OSC_CLK*(MSEL+1))

typedef enum _BootloaderStatusType_
{
	_BL_IDLE_ = 0xA0,	
	_BL_START_,
	_BL_READY_,
	_BL_NEXTLINE,
	_BL_BUSY_,
	_BL_COMPLETED_,
	_BL_BITERROR_,
	_BL_ERROE_,
	_BL_SECTION_BL,
	_BL_SECTION_APP,
	_BL_EMPTY_ = 0xFF
}BootloaderStatusType;

typedef enum _SIndex_
{
    SIDX0 = 0,
    SIDX1,
    SIDX2,
    SIDX3,
    SIDX4,
    SIDX5,
    SIDX6,
    SIDX7,
    SIDX8,
    SIDXLEN = SIDX8,
}SIndex; 

typedef struct _LPC11xx_Bootloader_Setting_
{  		
	U8 AddrPoint256;
	U8 BufOffset;
	U16 AddrPointOffset;	
	
	U8 CopyData2Buf[9];
	U8 Buf2Flash[R2FBUFSIZE] __attribute__ ((aligned (4)));
	
	BootloaderStatusType pMsg;

}LPC11xx_Bootloader_Setting;


INTERFACE volatile LPC11xx_Bootloader_Setting g_BootloaderSetting;
INTERFACE void Write_In_Flash(void);
INTERFACE RetU32 msAPI_Flash_PrepareSec( U32 StartSecNum , U32 EndSecNum ) ;
INTERFACE RetU32 msAPI_Flash_CopyRAM2Flash( U32 dst , U32 src , U16 number) ;
INTERFACE RetU32 msAPI_Flash_EraseSec( U32 StartSecNum , U32 EndSecNum );
#if 0
INTERFACE U32 msAPI_Flash_BlankChkSec( U32 StartSecNum , U32 EndSecNum , U32 * pResult ) ;
INTERFACE U32 msAPI_Flash_ReadParID( U32 * PartID );
INTERFACE U32 msAPI_Flash_Read_BootVer( U32 * MajorVer , U32 * MinorVer ) ;
INTERFACE U32 msAPI_Flash_Compare( U32 dst , U32 src , U32 number , U32 *offset );
INTERFACE void  msAPI_Flash_ReinvokeISP(void) ;
INTERFACE void msAPI_Flash_Ram_Fill(U8 *u8src_prt,U32 u32Size);
#endif
INTERFACE void  nsAPI_Flash_Jump2AppSector(void);
INTERFACE void nsAPI_Flash_BootBurn2Flash(void);
INTERFACE void nsAPI_Flash_UpgradeID(U16 u16ID);
INTERFACE void msAPI_Flash_SlaveTransmitter_Status(U8 S0 ,U8 S1,U8 S2);
//INTERFACE BinCheckSumStatusType msAPI_Flash_IsCheckSumCorrect(void);
INTERFACE void nsAPI_Flash_Init(void);
INTERFACE void nsAPI_Flash_SetBLStatus(BootloaderStatusType BLStatus);
INTERFACE BootloaderStatusType nsAPI_Flash_GetBLStatus(void);
INTERFACE RetU8 _XRead(U32 u32Adr);
INTERFACE BootLean nsAPI_Flash_AppPresent(void);
INTERFACE BootLean nsAPI_Flash_IsUpgrade(void);
INTERFACE void nsAPI_Flash_EraseAppSector(void);
INTERFACE void nsAPI_Flash_CopyData2Buf(U8 u8Lenth);
//INTERFACE void nsAPI_Flash_CopyData2Buf(void);
#undef INTERFACE
#endif 
