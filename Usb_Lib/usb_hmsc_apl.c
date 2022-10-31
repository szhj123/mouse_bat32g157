#include "usb_hmsc_apl.h"
#include "ff.h"

uint32_t g_hmsc_sector_size = 512;	//default 512, update when Device atteched
uint32_t g_hmsc_sector_count = 0;		//default 0, update when Device atteched

#define DISK_DEFAULT		 0x00
#define DISK_MOUNT 			 0x01
#define DISK_READLIST 	 0x02
#define DISK_WRITEFILE   0x03
#define DISK_DEMOEND	   0x04

void disk_demo_rountine(void);

FATFS fatfs;
FIL file;
FRESULT fatres;
FILINFO fno;
DIR dir;

uint8_t demo_state;
uint8_t configed_flag;
uint8_t WriteTextBuff[] = "BAT32G157 Hmsc Demo application using FAT_FS ";

void usb_app(void)
{
	usb_ctrl_t ctrl;
	usb_err_t err;
	usb_cfg_t   cfg;
	uint8_t g_buf[512];
	uint8_t event;
	
	ctrl.type       = USB_HMSC;
	cfg.usb_mode    = USB_HOST;
	err = USB_Open (&ctrl, &cfg);   /* Initializes the USB module */
	if (USB_SUCCESS != err)
	{
		printf("USB Init Error\r\n");
	}
	
	while (1)
 {
	 event = USB_GetEvent(&ctrl);
//	 switch (USB_GetEvent(&ctrl))
	 switch (event)
	 {
		 case USB_STS_CONFIGURED:
			 USB_HmscStrgCmd(g_buf, USB_ATAPI_READ_CAPACITY );
		   printf("Disk emum success, Read disk Capacity\r\n");
			 break;
		 case USB_STS_MSC_CMD_COMPLETE:
			 if( ctrl.status == USB_CSW_SUCCESS)
			 {
				 	g_hmsc_sector_size = (g_buf[6]<<8) + g_buf[7];
					g_hmsc_sector_count = (g_buf[1]<<16) + (g_buf[2]<<8) + g_buf[3];
					printf("Capacity:%d sector, %d size\r\n", g_hmsc_sector_count, g_hmsc_sector_size);
					configed_flag = 1;
			 }else{
				  printf("Read disk Capacity fail\r\n");
			 }
			 break;
		 case USB_STS_DETACH:
				printf("Device Detach\r\n");
				configed_flag = 0;
				demo_state = DISK_DEFAULT;
				break;
		default:
			 if(event != USB_STS_NONE)
			 {
					printf("event:%d\r\n",event);
			 }
			 break;
		}
		if(configed_flag ==1)
		{
				disk_demo_rountine();
		}
	}
}


void disk_demo_rountine(void)
{
	uint16_t bytesWritten, bytesToWrite;
	uint16_t   res[10];
	
	usb_hstd_DeviceInformation(0, (uint16_t *)res); /* Get device connect state */
	if ( USB_STS_DETACH == res[1] )    /* Check detach */
	{
			printf("Device Detach\r\n");
			configed_flag = 0;
			return;
	}
	
	switch(demo_state)
	{
		case DISK_DEFAULT:
			printf("Fatfs start\r\n");
			demo_state = DISK_MOUNT;
			break;
		case DISK_MOUNT:
			if (FR_OK != f_mount(&fatfs, "0:/", 0)) {
				printf("Cannot mount disk\r\n");
			}
			printf("Mount disk OK\r\n");
			demo_state = DISK_READLIST;
			break;
	  case DISK_READLIST:
			fatres = f_opendir(&dir, "0:/");
			if(FR_OK == fatres)
			{
				printf("Explorer Disk Root dir:\r\n");
				printf("\r\n");
				printf("->Root:\r\n");
				while(1)
				{
					usb_hstd_DeviceInformation(0x00, (uint16_t *)res); /* Get device connect state */
					if ( USB_STS_DETACH == res[1] )    /* Check detach */
					{
//							printf("Device Detach\r\n");
							return;
					}
					fatres = f_readdir(&dir, &fno);
					if (FR_OK != fatres || 0U == fno.fname[0]) {	//explore end or file name error
              break;
          }
					if ('.' == fno.fname[0]) {	//do not show hidden file(file name start with ".")
						 continue;
					}
					printf("  |->%s\r\n", fno.fname);
				}
			}
			printf("\r\n");
			demo_state = DISK_WRITEFILE;
			break;
		case DISK_WRITEFILE:
			printf("Write file to disk\r\n");
			if (FR_OK == f_open(&file, "0:CMS.TXT", FA_CREATE_ALWAYS | FA_WRITE)) {
			/* write buffer to file */
			bytesToWrite = sizeof(WriteTextBuff); 
			fatres = f_write (&file, WriteTextBuff, bytesToWrite, (void *)&bytesWritten);
			/* EOF or error */
			if ((0U == bytesWritten) || (FR_OK != fatres)) {
					printf("> CMS.TXT CANNOT be written.\r\n");
			} else {
					printf("> CMS.TXT created in the disk.\r\n");
			}

			/* close file and file system */
			f_close(&file);
			f_mount(NULL, "0:/", 1); 
			} else {
					printf("File create failed\r\n");
			}
			demo_state = DISK_DEMOEND;
			break;
	case DISK_DEMOEND:
			break;
	}
}

