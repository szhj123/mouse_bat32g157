
#define _FLASH_C_ 1
#include "LPC11Uxx.h"		
#include "Flash.h"
#include "wdt.h"
#include "GPIO.h"
#include "I2C.h"
//-----FlashrepareSec-----
//***********************************************************************
//* Function Name : FlashPrepareSec                                     *
//* Parameters :                                                        *
//  StartSecNum -- Start Sector Number                                  *
//  EndSecNum -- End Sector Number                                      *
//* Return : unsigned long -- Status Code                               *
//* Description : This BL_command must be executed before               *
//                executing "Copy RAM to Flash" or                      *
//                "Erase Sector(s)" BL_command.                         *
//***********************************************************************
RetU32 msAPI_Flash_PrepareSec( U32 u32StartSecNum , U32 u32EndSecNum )
{       
	U32 u32Status;
	U32 u32BootResult[3];
	U32 u32BootCommand[5];     

	if(u32EndSecNum < u32StartSecNum)
	{     
		u32Status = IAP_STA_INVALD_PARAM;
	}
	else
	{
		u32BootCommand[0] = IAP_CMD_PREPARE_SECTORS;
		u32BootCommand[1] = u32StartSecNum;
		u32BootCommand[2] = u32EndSecNum;

		IAP_EXECUTE_CMD(u32BootCommand, u32BootResult);

		u32Status = u32BootResult[0];
	}	
	return u32Status;

}
//-----FlashCopyRAMToFlash-----
//***********************************************************************
//* Function Name : FlashCopyRAMToFlash                                 *
//* Parameters :                                                        *
//  dst -- Destination Flash address, should be a 256 byte boundary.    *
//  src -- Source RAM address, should be a word boundary                *
//  number -- 256 | 512 |1024 |4096                                     *
//  Return : unsigned long -- Status Code                               *
//* Description : This BL_command is used to program the flash memory.  *
//***********************************************************************

RetU32 msAPI_Flash_CopyRAM2Flash( U32 dst , U32 src , U16 number)
{
	U32 u32BootCommand[5],u32BootResult[3];

	u32BootCommand[0] = IAP_CMD_COPY_RAM_TO_FLASH;
	u32BootCommand[1] = dst;  
	u32BootCommand[2] = src;	 
	u32BootCommand[3] = number;	 
	u32BootCommand[4] = IAP_CLK;//0x00;
	
	IAP_EXECUTE_CMD(u32BootCommand, u32BootResult);	



	return u32BootResult[0];
}
//-----FlashEraseSec-----
//***********************************************************************
//* Function Name : FlashEraseSec                                       *
//* Parameters :                                                        *
//  StartSecNum -- Start Sector Number                                  *
//  EndSecNum -- End Sector Number                                      *
//* Return : unsigned long -- Status Code                               *
//* Description :                                                       *
//  This BootComman is used to erase a sector or multiple sectors of    *
//  on-chip Flash memory.                                               *
//***********************************************************************
RetU32 msAPI_Flash_EraseSec( U32 u32StartSecNum , U32 u32EndSecNum )
{
	U32 u32Status; 
	U32 u32BootCommand[5],u32BootResult[3];

	if (u32EndSecNum < u32StartSecNum)
	{
		u32Status = IAP_STA_INVALD_PARAM;
	}
	else
	{
		u32BootCommand[0] = IAP_CMD_ERASE_SECTORS;
		u32BootCommand[1] = u32StartSecNum;
		u32BootCommand[2] = u32EndSecNum;
		u32BootCommand[3] = IAP_CLK;//0x00;

		IAP_EXECUTE_CMD(u32BootCommand,u32BootResult);
		u32Status = u32BootResult[0];
	}
	return u32Status;
}
#if 0
//-----FlashBlankChkSec-----
//***********************************************************************
//* Function Name : FlashBlankChkSec                                    *
//* Parameters :                                                        *
//  StartSecNum -- Start Sector Number                                  *
//  EndSecNum -- End Sector Number                                      *
//* Return : unsigned long -- Status Code                               *
//* Description :                                                       *
//  This BL_command is used to blank check a sector or                  *
//  mutilple sectors of on-chip Flash memory.                           *
//***********************************************************************
U32 msAPI_Flash_BlankChkSec( U32 StartSecNum , U32 EndSecNum , U32 * pResult )
{
      U32 u32BootCommand[5],u32BootResult[4];

	if (EndSecNum < StartSecNum)	
	return IAP_STA_INVALD_PARAM;	
	
	u32BootCommand[0] =IAP_CMD_BLANK_CHECK_SECTORS ;
	u32BootCommand[1] = StartSecNum ;
	u32BootCommand[2] = EndSecNum ;
	IAP_EXECUTE_CMD(u32BootCommand,u32BootResult) ;
	if(u32BootResult[0] == IAP_STA_SECTOR_NOT_BLANK)
	{
		*pResult = u32BootResult[0];
		*(pResult+1) = u32BootResult[1];
	}
	return u32BootResult[0] ;
}
//-----FlashReadParID-----
//***********************************************************************
//* Function Name : FlashReadParID                                      *
//* Parameters :                                                        *
//  * PartID --                                                         *
//* Return : unsigned long -- Status Code                               *
//* Description :                                                       *
//  This BootComman is used to read the part identification number.     *
//***********************************************************************
U32 msAPI_Flash_ReadParID( U32 * PartID )
{
      U32 u32BootCommand[5],u32BootResult[4];

	u32BootCommand[0] = IAP_CMD_READ_PART_ID;
	
	IAP_EXECUTE_CMD(u32BootCommand,u32BootResult);
	*PartID = u32BootResult[1];
	
	return u32BootResult[0];
}
//-----FlashReadBootVer-----
//***********************************************************************
//* Function Name : FlashReadBootVer                                    *
//*Parameters :                                                         *
//  char * MajorVer                                                     *
//  char * MinorVer                                                     *
//* Return : unsigned long -- Status Code                               *
//* Description:                                                        *
//  This BootComman is used to read the boot code version number.       *
//***********************************************************************
U32 msAPI_Flash_Read_BootVer( U32 * MajorVer , U32 * MinorVer )
{
       U32 u32BootCommand[5],u32BootResult[4];

	u32BootCommand[0] = IAP_CMD_READ_BOOT_ROM_VERSION ;
	
	IAP_EXECUTE_CMD(u32BootCommand,u32BootResult) ;
	*MajorVer = (u32BootResult[1] & 0xff00)>>8 ;
	*MinorVer = u32BootResult[1] & 0xff ;
	
	return u32BootResult[0] ;
}
//-----FlashCompare-----
//***********************************************************************
//* Function Name : FlashCompare                                        *
//* Parameters :                                                        *
//  dst -- Destination Flash address                                    *
//  src -- Source RAM address                                           *
//  number -- Should be in mutilple of 4                                *
//* Return : unsigned long -- Status Code                               *
//* Description :                                                       *
//  This BootComman is used to compary the memory contents at two locations.
//* NOTE :                                                              *
//  Compary BootResult may not be correct when source or destination address contains
//  any of the first 64 bytes starting from address zero.               *
//  First 64 bytes can be re-mapped to RAM.                             *
//***********************************************************************
U32 msAPI_Flash_Compare( U32 dst , U32 src , U32 number , U32 *offset )
{
      U32 u32BootCommand[5],u32BootResult[4];

	u32BootCommand[0] = IAP_CMD_COMPARE;
	u32BootCommand[1] = dst ;
	u32BootCommand[2] = src ;
	u32BootCommand[3] = number;
	
	IAP_EXECUTE_CMD(u32BootCommand,u32BootResult);

	if (u32BootResult[0] == IAP_STA_COMPARE_ERROR)
	*offset = u32BootResult[1];
	
	return u32BootResult[0];
}

void msAPI_Flash_ReinvokeISP(void)
{
	U32 u32BootCommand[5],u32BootResult[4];

	u32BootCommand[0] = IAP_CMD_REINVOKE_ISP;
	IAP_EXECUTE_CMD(u32BootCommand , u32BootResult); 
}

 void msAPI_Flash_Ram_Fill(U8 *u8src_prt,U32 u32Size)
 {
	U16  i;
	
	for(i = 0; i < u32Size; i++)  
	{
		*u8src_prt ++= i;		 
	}
}
#endif

void nsAPI_Flash_EraseAppSector(void)
{
	__disable_irq();
       
	if(msAPI_Flash_PrepareSec(AppCode_StartSector,AppCode_EndSector)== IAP_STA_CMD_SUCCESS)
	{
		msAPI_Flash_EraseSec(AppCode_StartSector,AppCode_EndSector);
		//if(msAPI_Flash_EraseSec(AppCode_StartSector,AppCode_EndSector)== IAP_STA_CMD_SUCCESS)
		//{
        //       _Flash_Debug_(xprintf("\r\n Erase AppSector is Ok",0));
		//}
	}
	
	__enable_irq();
}

BootLean nsAPI_Flash_IsUpgrade(void)
{
	U16 u16UpgradeID;

	u16UpgradeID = _XRead(AppUpgrade_FlagAdr) << 8;
	u16UpgradeID |= _XRead(AppUpgrade_FlagAdr+0x01);

	_Flash_Debug_(xprintf("\r\n IsUpgrade = %x ",u16UpgradeID));
     
	if(u16UpgradeID == AppReqUpgradeID)
	return TRUE;
	else	
	return FALSE;
}




BootLean nsAPI_Flash_AppPresent(void)
{
	U8 u8AppUpgrade = TRUE;
	U16 u16AppID,u16AppupgradID;
	
	u16AppID	 = _XRead(AppID_Adr) << 8;
	u16AppID|= _XRead(AppID_Adr+0x01) << 0;

	u16AppupgradID = _XRead(AppUpgrade_FlagAdr) << 8;
	u16AppupgradID |= _XRead(AppUpgrade_FlagAdr+0x01) << 0;
 
       _Flash_Debug_(xprintf("\r\n u16AppID = %x",u16AppID));
	  
	if(u16AppID == AppID)
	{
		if(nsAPI_Flash_IsUpgrade())
		{
			nsAPI_Flash_EraseAppSector(); 	   	
		}
		else	
		u8AppUpgrade = FALSE;
	}
	else
	{
		if(u16AppID != 0xFFFF||u16AppupgradID == AppReqUpgradeID)
		nsAPI_Flash_EraseAppSector();
	}
	_Flash_Debug_(xprintf("\r\n u8AppUpgrade = %x",u8AppUpgrade));
	 
	return u8AppUpgrade;
}

#if 0
void nsAPI_Flash_Init(void)
{
	U16 i; 

	for( i = 0; i < R2FBUFSIZE; i++)		
	g_BootloaderSetting.Buf2Flash[i] = 0xFF;
	
	for(i = 0; i < 9;i++)
	g_BootloaderSetting.CopyData2Buf[i] = 0; 

	g_BootloaderSetting.AddrPoint256 = 0;
	g_BootloaderSetting.AddrPointOffset = 0;
	g_BootloaderSetting.BufOffset = 0;
	
}
#endif 

void nsAPI_Flash_Jump2AppSector(void)
{
	typedef void Jump2BootloaderSector(void);
	Jump2BootloaderSector *_Jump_ ;
	_Jump_ = (Jump2BootloaderSector *)(AppCode_StartAdr|0x000000C1);
	_Jump_(); 
}

void nsAPI_Flash_BootBurn2Flash(void)
{
	U8 u8Length;
	U16 i;/*,u16OffSet*/
	u8Length =  8;//g_BootloaderSetting.CopyData2Buf[SIDX0];
	
	for(i = 0; i < u8Length; i++)
	{
		g_BootloaderSetting.Buf2Flash[g_BootloaderSetting.AddrPointOffset] = g_Main_Setting.OutReport[i];//g_BootloaderSetting.CopyData2Buf[SIDX1+i];	
		g_BootloaderSetting.AddrPointOffset++; 			
	}
	//g_BootloaderSetting.AddrPointOffset = 257;
	if(g_BootloaderSetting.AddrPointOffset >= 256)
	{ 		
		__disable_irq();
		
		if(msAPI_Flash_PrepareSec(AppCode_StartSector,AppCode_EndSector) == IAP_STA_CMD_SUCCESS)	//Start burn
		{
			if(msAPI_Flash_CopyRAM2Flash((U32)AppCode_StartAdr+(g_BootloaderSetting.AddrPoint256*256),(U32)g_BootloaderSetting.Buf2Flash,0x100) ==  IAP_STA_CMD_SUCCESS)
			{   
				__enable_irq();
				for( i = 0; i < R2FBUFSIZE; i++)		
				g_BootloaderSetting.Buf2Flash[i] = 0xFF;	

				g_BootloaderSetting.AddrPointOffset = 0;
				g_BootloaderSetting.AddrPoint256++;					
			}
			//else{
			
			//_Flash_Debug_(xprintf("\r\n CopyRam2F is fault",0));	
			//}
		}
		//else
		// _Flash_Debug_(xprintf("\r\n PrepareSec is fault",0));	

		__enable_irq();
	}		
	g_BootloaderSetting.BufOffset = 0;
	
}

void Write_In_Flash(){
		U8 u8Length;
	U16 i;/*,u16OffSet*/
	u8Length =  8;//g_BootloaderSetting.CopyData2Buf[SIDX0];
	
	for(i = 0; i < u8Length; i++)
	{
		g_BootloaderSetting.Buf2Flash[g_BootloaderSetting.AddrPointOffset] = g_Main_Setting.OutReport[i];//g_BootloaderSetting.CopyData2Buf[SIDX1+i];	
		g_BootloaderSetting.AddrPointOffset++; 			
	}
		//U8 j;
		//j = 0x22;
		//nsAPI_I2C_Write_Database(RM_BOOTLOADER_STATUS_ADR+1,&j,1);	//Update firmware Finish
		__disable_irq();
			   
		if(msAPI_Flash_PrepareSec(AppCode_StartSector,AppCode_EndSector) == IAP_STA_CMD_SUCCESS)	//Start burn
		{  			   
			msAPI_Flash_CopyRAM2Flash((U32)AppCode_StartAdr+(g_BootloaderSetting.AddrPoint256*256),(U32)g_BootloaderSetting.Buf2Flash,0x100);
			//if(msAPI_Flash_CopyRAM2Flash((U32)AppCode_StartAdr+(g_BootloaderSetting.AddrPoint256*256),(U32)g_BootloaderSetting.Buf2Flash,0x100) ==  IAP_STA_CMD_SUCCESS)
			//{   
				__enable_irq();
				//j = 0x22;
				//nsAPI_I2C_Write_Database(RM_BOOTLOADER_STATUS_ADR+1,&j,1);	//Update firmware Finish
				//for( i = 0; i < R2FBUFSIZE; i++)		
				//g_BootloaderSetting.Buf2Flash[i] = 0xFF;	

				//g_BootloaderSetting.AddrPointOffset = 0;
				//g_BootloaderSetting.AddrPoint256++;					
			//}
			//else
			//_Flash_Debug_(xprintf("\r\n CopyRam2F is fault",0));	
		}
		//else{
		// _Flash_Debug_(xprintf("\r\n PrepareSec is fault",0));	
		//}

		__enable_irq(); 
}

RetU8 _XRead(U32 u32Adr )
{
   volatile U8 * u8Value;
   u8Value = (volatile U8*)u32Adr;
   return (*u8Value);
}


void nsAPI_Flash_CopyData2Buf(U8 u8Lenth)
{
	U8 i;
	g_BootloaderSetting.CopyData2Buf[SIDX0] = u8Lenth;
	for(i = 0; i < u8Lenth; i++)
	{
		g_BootloaderSetting.CopyData2Buf[SIDX1+g_BootloaderSetting.BufOffset] = \
		g_Main_Setting.OutReport[SIDX0+i];
           
		g_BootloaderSetting.BufOffset++;
	}	
}
