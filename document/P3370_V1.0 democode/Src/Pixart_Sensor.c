#include "Pixart_Sensor.h"

U8 flagOne;		// to enable burst mode
U8 u8motion,u8Squal,u8PixelSum;
s16 s16accuX, s16accuY, report1ms_data_x, report1ms_data_y ;
U8 stop_motion = 0;
s16 s16accuX, s16accuY ;
u16	u16Pixel,u16Shutter;
S8 count_z;
U8 cpi_p_Cntr, cpi_m_Cntr;
U8 VarA = 0;
U8 VarB = 0;
U8 not_read = 0;
int16_t motion_sync_counter, test_A;
U8 u8temp[ARR_SIZE] = {0}; 
U8 tempBurst = 0;
s16 u16temp_x;
s16 u16temp_y;		

//U8 flag_no_cpi;

// Function Prototype
// SENSOR SPI
void  nsAPI_SSP_Delay1us (U16 u16DelayTime);
RetU8 nsAPI_SSP_Sensor_Read (U8 u8Adr);
void  nsAPI_SSP_Sensor_Write (U8 u8Adr,U8 u8Com);
void  nsAPI_SSP_Sensor_LoadSROM (void);
void  nsAPI_Sensor_Hard_Reset (void);

void  nsAPI_SSP_Sensor_Init (void);
RetU8 esd_Check (void);
void  nsAPI_SSP_Sensor_Monitor (void);
RetU8 nsAPI_MouseScanButton (void);
//void  Z_Wheel (U32 temp0, U32 temp1);
void  Z_Wheel(void);


void nsAPI_SSP_Delay1us(U16 u16DelayTime)
{
	U8 i;
	
	while(u16DelayTime)
	{
		for (i = 4; i > 0; i--){};
			u16DelayTime --;
	}	
}

RetU8 nsAPI_SSP_Sensor_Read(U8 u8Adr)
{
	// This part is to cater GUI usage.
	// Note reg 0x02 and 0x50 is under the same data path 
	if( IS_BIT_SET(mouse_event_ctrl,ENABLE_NON_BURST_MODE_BIT) )
	{ // non burst mode
	   if((u8Adr != 0x02) && (u8Adr != 0x03) && (u8Adr != 0x04) && (u8Adr != 0x05) && (u8Adr != 0x06) )
		 {
				flagOne = ENABLE; // this to clean register 0x02 before normal motion read as other than register read 0x02,0x03,0x04,0x05,0x06 happend.
		 } 
	}
	else  // burst mode
	{
	   if(u8Adr != 0x50)
		 {
		flagOne = ENABLE;		// this flag is to clear register 0x50 before motion burst read as other read operation happened. .
		 }
  }	
	
		
  	__disable_irq();
	
	NCS_LOW();
	nsAPI_SSP_Delay1us(1);
	
	nsAPI_SSP_Send(&u8Adr,1);	
	nsAPI_SSP_Delay1us(2);	
	nsAPI_SSP_Receive(&u8Adr,1);	
	
	nsAPI_SSP_Delay1us(1);	
	NCS_HIGH();
	nsAPI_SSP_Delay1us(10);	

	__enable_irq(); 

	return u8Adr; 
}

void nsAPI_SSP_Sensor_Write(U8 u8Adr,U8 u8Com)
{
	
 if(u8Adr == 0x00)		// if register 0x00 was write.	
 {	
		stop_motion	= u8Com; 
 }	 
 else
 {	
    __disable_irq();
	
	u8Adr = u8Adr|BIT7;
	NCS_LOW();
	nsAPI_SSP_Delay1us(1);  	// 1us
	nsAPI_SSP_Send(&u8Adr,1);	// Send Address
	//nsAPI_SSP_Delay1us(2);	// 
	nsAPI_SSP_Send(&u8Com,1);	// Data	
	nsAPI_SSP_Delay1us(1);				
			
	NCS_HIGH();

	nsAPI_SSP_Delay1us(5);
	
	__enable_irq();
	
 }
}


void nsAPI_SSP_Sensor_LoadSROM(void)
{
     U8 u8SromTemp; 
     U16 sromCntr;      

	nsAPI_SSP_Sensor_Write(CONFIG2_REG,0x00); 		
	nsAPI_SSP_Sensor_Write(SROM_ENABLE_REG,0x1D);	
		
	for(sromCntr = 0; sromCntr < 10; sromCntr++)
		nsAPI_SSP_Delay1us(1000); // 1ms

	nsAPI_SSP_Sensor_Write(SROM_ENABLE_REG,0x18);
	nsAPI_SSP_Delay1us(120);//120us	
	
	NCS_LOW();

	u8SromTemp = (SROM_LOAD_BURST_REG|0x80);
	nsAPI_SSP_Send(&u8SromTemp,1);
	nsAPI_SSP_Delay1us(140);//140us
   	
	for(sromCntr = 0; sromCntr < SROMSIZE; sromCntr++)
	{	
		u8SromTemp = SROM[sromCntr]; 
		nsAPI_SSP_Send(&u8SromTemp,1); 		
		nsAPI_SSP_Delay1us(30);//30us	
	}	
	NCS_HIGH();
	nsAPI_SSP_Delay1us(180);//180us
}



void nsAPI_Sensor_Hard_Reset(void)
{
	U8 initCntr;

	NDrv_GPIO_SetBitValue(PORT1,21,HIGH);	// Hard Reset
	nsAPI_SSP_Delay1us(50);
	NDrv_GPIO_SetBitValue(PORT1,21,LOW);
	nsAPI_SSP_Delay1us(50);
	NDrv_GPIO_SetBitValue(PORT1,21,HIGH);

	for(initCntr = 0; initCntr < 60; initCntr++)	// 60ms  
		nsAPI_SSP_Delay1us(1000);					// 1ms
}



void nsAPI_SSP_Sensor_Init(void)
{	
	U16 Test_A = 0;
	U8 ctr = 0;
  U16 delay = 0;
	U8 clockcounter = 0;
	U8 u8InitTemp = 2;	// Default for the LED setting
	flagOne = ENABLE;
	#define LED_INIT_SETUP	u8InitTemp
	s16accuX.w = 0;		// Reset USB XY Accumulator
	s16accuY.w = 0;
	count_z = 0;

	NDrv_GPIO_SetBitValue(PORT0,11,HIGH);	// Sensor's LED2_P SW3 OPEN

	//TURN_ON_20R_SW1_LED(HIGH);	// 3rd highest light default
 	//TURN_ON_39R_SW2_LED(LOW);
  TURN_ON_20R_SW1_LED(LOW);	// GY@03June2016 Turn On SW1 9 ohm for ORCA3 LED
	TURN_ON_39R_SW2_LED(HIGH);

	// Default LED setting
	NDrv_GPIO_SetBitValue(PORT0,20,(LED_INIT_SETUP & BIT2)^BIT2); // DLED 1  PORT 0 _20
	NDrv_GPIO_SetBitValue(PORT1,26,(LED_INIT_SETUP & BIT1)^BIT1); // DLED 2  Port 1 _26				
	NDrv_GPIO_SetBitValue(PORT1,27,(LED_INIT_SETUP & BIT0)^BIT0); // DLED 3  Port 1 _27
	
	NDrv_GPIO_SetBitValue(PORT1,21,HIGH);
	
	for(ctr = 0; ctr< 50; ctr++)		// 1ms x50 = 50ms  
	nsAPI_SSP_Delay1us(1000);			// 1ms

	NCS_HIGH();	
	nsAPI_SSP_Delay1us(1);
	NCS_LOW();	
 
	#ifdef SOFT_RESET										//	Soft Reset Default
	nsAPI_SSP_Sensor_Write(0x3A, 0x5A);	// Soft Reset
	#else
	nsAPI_Sensor_Hard_Reset();				// Hard Reset 
	#endif

	nsAPI_SSP_Delay1us(5000);						//wait for at least 5ms
	
	// sensor initialization
	nsAPI_SSP_Sensor_Write(0x7F,0x12);  
	nsAPI_SSP_Sensor_Write(0x47,0x00);
	nsAPI_SSP_Sensor_Write(0x7F,0x00);
	nsAPI_SSP_Sensor_Write(0x18,0x00);
	nsAPI_SSP_Sensor_Write(0x40,0x80);
	nsAPI_SSP_Sensor_Write(0x55,0x01);
	nsAPI_SSP_Delay1us(1000);						//wait for 1ms
	nsAPI_SSP_Sensor_Write(0x7F,0x0E);
	nsAPI_SSP_Sensor_Write(0x43,0x1D);
	VarA	= (nsAPI_SSP_Sensor_Read(0x46)); 
	nsAPI_SSP_Sensor_Write(0x43,0x1E);
	VarB	= (nsAPI_SSP_Sensor_Read(0x46)); 

	nsAPI_SSP_Sensor_Write(0x7F,0x14);
	nsAPI_SSP_Sensor_Write(0x6A,VarA);
	nsAPI_SSP_Sensor_Write(0x6C,VarB);
	
	

	nsAPI_SSP_Sensor_Write(0x7F,0x00);
	nsAPI_SSP_Sensor_Write(0x55,0x00);
	nsAPI_SSP_Sensor_Write(0x4D,0x10);
	nsAPI_SSP_Sensor_Write(0x4E,0x3B);
	nsAPI_SSP_Sensor_Write(0x4F,0x46);
	nsAPI_SSP_Sensor_Write(0x54,0x34);
	nsAPI_SSP_Sensor_Write(0x77,0x24);

	nsAPI_SSP_Sensor_Write(0x7F,0x05);
	nsAPI_SSP_Sensor_Write(0x44,0xA8);
	nsAPI_SSP_Sensor_Write(0x46,0x15); 
	nsAPI_SSP_Sensor_Write(0x4A,0x14);
	nsAPI_SSP_Sensor_Write(0x51,0x10);
	nsAPI_SSP_Sensor_Write(0x53,0x0C); 
	nsAPI_SSP_Sensor_Write(0x55,0xC9); 
	nsAPI_SSP_Sensor_Write(0x5B,0xEA); 
	nsAPI_SSP_Sensor_Write(0x61,0x13);
	nsAPI_SSP_Sensor_Write(0x62,0x0B); 
	nsAPI_SSP_Sensor_Write(0x64,0x18); 
	nsAPI_SSP_Sensor_Write(0x6D,0x86);
	nsAPI_SSP_Sensor_Write(0x7D,0x85);
	nsAPI_SSP_Sensor_Write(0x7E,0x03);


	nsAPI_SSP_Sensor_Write(0x7F,0x06);
	nsAPI_SSP_Sensor_Write(0x60,0xB0);
	nsAPI_SSP_Sensor_Write(0x61,0x00);
	nsAPI_SSP_Sensor_Write(0x6D,0x29);
	nsAPI_SSP_Sensor_Write(0x6E,0x23);
	nsAPI_SSP_Sensor_Write(0x7E,0x40);
	
	nsAPI_SSP_Sensor_Write(0x7F,0x07);
	nsAPI_SSP_Sensor_Write(0x42,0x15);
	
	nsAPI_SSP_Sensor_Write(0x7F,0x08);
	nsAPI_SSP_Sensor_Write(0x42,0x28);
	nsAPI_SSP_Sensor_Write(0x43,0x32);
	
	nsAPI_SSP_Sensor_Write(0x7F,0x09);
	nsAPI_SSP_Sensor_Write(0x40,0x03);
	
	nsAPI_SSP_Sensor_Write(0x7F,0x0A);
	nsAPI_SSP_Sensor_Write(0x4A,0x28);
	nsAPI_SSP_Sensor_Write(0x4C,0x28); 
	nsAPI_SSP_Sensor_Write(0x49,0x00);
	nsAPI_SSP_Sensor_Write(0x4F,0x02);



	nsAPI_SSP_Sensor_Write(0x7F,0x0C);
	nsAPI_SSP_Sensor_Write(0x40,0x90);
	nsAPI_SSP_Sensor_Write(0x41,0x50);
	nsAPI_SSP_Sensor_Write(0x42,0x0C);
	nsAPI_SSP_Sensor_Write(0x43,0xA8);
	nsAPI_SSP_Sensor_Write(0x44,0x47);
	nsAPI_SSP_Sensor_Write(0x45,0x01);
	nsAPI_SSP_Sensor_Write(0x4D,0x4F);
	nsAPI_SSP_Sensor_Write(0x4E,0x1B);
	nsAPI_SSP_Sensor_Write(0x54,0x00);
	nsAPI_SSP_Sensor_Write(0x55,0x60);
	nsAPI_SSP_Sensor_Write(0x56,0x60);
	nsAPI_SSP_Sensor_Write(0x58,0x30);
	nsAPI_SSP_Sensor_Write(0x59,0x63);

	nsAPI_SSP_Sensor_Write(0x7F,0x0D);
	nsAPI_SSP_Sensor_Write(0x4B,0x23);
	nsAPI_SSP_Sensor_Write(0x4C,0x40);
	nsAPI_SSP_Sensor_Write(0x4E,0x6B);
	nsAPI_SSP_Sensor_Write(0x5E,0xC3);
	nsAPI_SSP_Sensor_Write(0x4F,0x02);
	
	nsAPI_SSP_Sensor_Write(0x7F,0x10);
	nsAPI_SSP_Sensor_Write(0x45,0x1E);
	nsAPI_SSP_Sensor_Write(0x46,0xF0);
	nsAPI_SSP_Sensor_Write(0x48,0x0F);
	nsAPI_SSP_Sensor_Write(0x49,0x88);
	nsAPI_SSP_Sensor_Write(0x4C,0x15);
	nsAPI_SSP_Sensor_Write(0x4F,0x00);
	nsAPI_SSP_Sensor_Write(0x51,0x6F);
	nsAPI_SSP_Sensor_Write(0x52,0x90);
	nsAPI_SSP_Sensor_Write(0x54,0x64);
	nsAPI_SSP_Sensor_Write(0x55,0xF0);
	nsAPI_SSP_Sensor_Write(0x5C,0x40);
	nsAPI_SSP_Sensor_Write(0x61,0xEE);
	nsAPI_SSP_Sensor_Write(0x62,0xE5);
	
	
	nsAPI_SSP_Sensor_Write(0x7F,0x14);
	nsAPI_SSP_Sensor_Write(0x53,0x0C);
	nsAPI_SSP_Sensor_Write(0x4A,0x67);
	nsAPI_SSP_Sensor_Write(0x6D,0x20);
	nsAPI_SSP_Sensor_Write(0x6E,0x00);
	nsAPI_SSP_Sensor_Write(0x73,0x83);
	nsAPI_SSP_Sensor_Write(0x74,0x00);
	nsAPI_SSP_Sensor_Write(0x7A,0x16);
	nsAPI_SSP_Sensor_Write(0x63,0x14);
	nsAPI_SSP_Sensor_Write(0x62,0x14);

	nsAPI_SSP_Sensor_Write(0x7F,0x00);
	nsAPI_SSP_Sensor_Write(0x5B,0x40);
	nsAPI_SSP_Sensor_Write(0x61,0xAD);
	nsAPI_SSP_Sensor_Write(0x51,0xEA);
	nsAPI_SSP_Sensor_Write(0x19,0x9F);


for(ctr = 0; ctr< 55; ctr++)	
{
if (nsAPI_SSP_Sensor_Read(0x20) == 0x0F) {

break;
}
nsAPI_SSP_Delay1us(840);

}


if (ctr==50){ 
				while(nsAPI_SSP_Sensor_Read(0x20) != 0x0F)
				{
					for(delay = 0; delay < 30; delay++){
					nsAPI_SSP_Delay1us(10000); //10ms
					}							
					
					NDrv_GPIO_SetBitValue(PORT0,20,1); // DLED 1  PORT 0 _20
					NDrv_GPIO_SetBitValue(PORT1,26,1); // DLED 2  Port 1 _26				
					NDrv_GPIO_SetBitValue(PORT1,27,0); // DLED 3  Port 1 _27	
					
					for(delay = 0; delay < 40; delay++){
					nsAPI_SSP_Delay1us(10000); //10ms
					}
			
					NDrv_GPIO_SetBitValue(PORT0,20,1); // DLED 1  PORT 0 _20
					NDrv_GPIO_SetBitValue(PORT1,26,0); // DLED 2  Port 1 _26				
					NDrv_GPIO_SetBitValue(PORT1,27,1); // DLED 3  Port 1 _27	
					
					for(delay = 0; delay < 50; delay++){
					nsAPI_SSP_Delay1us(10000); //10ms
					}
			
					NDrv_GPIO_SetBitValue(PORT0,20,0); // DLED 1  PORT 0 _20
					NDrv_GPIO_SetBitValue(PORT1,26,1); // DLED 2  Port 1 _26				
					NDrv_GPIO_SetBitValue(PORT1,27,1); // DLED 3  Port 1 _27							
					}
			}
	nsAPI_SSP_Sensor_Write(0x19,0x10);
	nsAPI_SSP_Sensor_Write(0x61,0xD5);	
	nsAPI_SSP_Sensor_Write(0x40,0x00);				
	nsAPI_SSP_Sensor_Write(0x7F,0x00);
	nsAPI_SSP_Sensor_Write(0x4D,0xD0);



	u8InitTemp = (nsAPI_SSP_Sensor_Read(0x02));		
	u8InitTemp = (nsAPI_SSP_Sensor_Read(0x03));
	u8InitTemp = (nsAPI_SSP_Sensor_Read(0x04));
	u8InitTemp = (nsAPI_SSP_Sensor_Read(0x05));
	u8InitTemp = (nsAPI_SSP_Sensor_Read(0x06));
			
				nsAPI_SSP_Delay1us(10000);	

// sensor initialization End
					
	g_Main_Setting.EPInOutReq &= ~EP1_IN;				// Reset EP1 flag
	nsAPI_USB_WriteEP(	HID_EP1_IN,
						&g_Main_Setting.InReport[0],	// Dennis:
						g_Main_Setting.InReportSize);	// This one is a must, else usb won't work

}

RetU8 esd_Check(void)
{
	U8 esdTemp = 0;

	esdTemp = nsAPI_SSP_Sensor_Read(0x24);
	nsAPI_SSP_Delay1us(20);
  	nsAPI_SSP_Sensor_Write(0x50, 0x01);
	nsAPI_SSP_Delay1us(180);

	if(!IS_BIT_SET( esdTemp,BIT6))
	{
		nsAPI_SSP_Sensor_Init();			// Re init Sensor
		return 1;
	}
	else
		return 0;
}

void nsAPI_SSP_Sensor_Monitor(void)
{ 	
	__disable_irq();
	if (poll_motion)	// this loop is to be executed in every 1ms
	{		
		u16temp_x.w  = 0;
		u16temp_y.w  = 0;
		
		// report the scaled 1ms motion data
		if (report1ms_data_x.w != 0 || report1ms_data_y.w != 0 ||((g_Main_Setting.MouseEvent & MAIN_FLAG_MOUSE_REPORT_READY) == MAIN_FLAG_MOUSE_REPORT_READY ))
		{
			//g_Main_Setting.MouseEvent	   |= (MAIN_FLAG_MOUSE_EVENT|MAIN_FLAG_MOUSE_REPORT_READY);
			nsAPI_Main_MouseEventHandle();
		}			

		//motion burst
		NCS_LOW();
		nsAPI_SSP_Delay1us(1);	// 120 ns min needed		 	
		tempBurst = 0x16;				// send any value to motion burst register 0x16
		nsAPI_SSP_Send(&tempBurst,1);
		nsAPI_SSP_Delay1us(2);  //2 us tSRAD

		for(tempBurst = 0; tempBurst < ARR_SIZE; tempBurst++)
			nsAPI_SSP_Receive( &u8temp[tempBurst],1);
		
		nsAPI_SSP_Delay1us(1); // 500 ns min tEXIT
		NCS_HIGH();

		u16temp_x.b[0] = u8temp[2];
		u16temp_x.b[1] = u8temp[3];
		u16temp_y.b[0] = u8temp[4];
		u16temp_y.b[1] = u8temp[5];
		
		s16accuX.w += u16temp_x.w;
		s16accuY.w += u16temp_y.w;
		
		//minus prebious 1ms scalred motion data to get the remainder motion data
		s16accuX.w = s16accuX.w - report1ms_data_x.w;
		s16accuY.w = s16accuY.w - report1ms_data_y.w;
		
		report1ms_data_x.w = 0;
		report1ms_data_y.w = 0;
		
		poll_motion = 0;
		not_read = 1;		
		motion_sync_counter = (int16_t)LPC_CT16B0->TC;		
		poll_counter = 0;
	}

	if((not_read == 1) && (CHECK_MOTION_PIN() == LOW))
	{
	u16temp_x.w  = 0;
	u16temp_y.w  = 0;
	motion_sync_counter = (int16_t)LPC_CT16B0->TC - motion_sync_counter;
			  			
	NCS_LOW();
	nsAPI_SSP_Delay1us(1);	// 120 ns min needed		 	

	tempBurst = 0x16;				// send any value to motion burst register 0x16
	nsAPI_SSP_Send(&tempBurst,1);
	nsAPI_SSP_Delay1us(2); //2 us tSRAD

	for(tempBurst = 0; tempBurst < ARR_SIZE; tempBurst++)
		nsAPI_SSP_Receive( &u8temp[tempBurst],1);
	
	nsAPI_SSP_Delay1us(1); // 500 ns min tEXIT
	NCS_HIGH();

	u16temp_x.b[0] = u8temp[2];
	u16temp_x.b[1] = u8temp[3];
	u16temp_y.b[0] = u8temp[4];
	u16temp_y.b[1] = u8temp[5];

	
	s16accuX.w += u16temp_x.w;
	s16accuY.w += u16temp_y.w;
	
	report1ms_data_x.w = s16accuX.w * 1000/ (1000 + (motion_sync_counter));
	report1ms_data_y.w = s16accuY.w * 1000/ (1000 + (motion_sync_counter));
	
	not_read = 0;
		
	}	
	__enable_irq();

}

RetU8 nsAPI_MouseScanButton(void)
{
	static U8 cpiTemp	 = 2;
	static U8 trigger_send_cpi_click = 0;

	U8 Ret = FALSE;
	U32 buttonTemp0 = 0;
	U32 buttonTemp1 = 0;
		
	U8 cpi_hi_data[8] = {CPI_HI_0, CPI_HI_1, CPI_HI_2, CPI_HI_3,
						CPI_HI_4, CPI_HI_5, CPI_HI_6, CPI_HI_7};
	
	U8 cpi_lo_data[8] = {CPI_LO_0, CPI_LO_1, CPI_LO_2, CPI_LO_3,
						CPI_LO_4, CPI_LO_5, CPI_LO_6, CPI_LO_7};



	buttonTemp0 = nsAPI_GPIO_GetPinValue(PORT0,0xFF);
	buttonTemp1 = nsAPI_GPIO_GetPinValue(PORT1,0xFF);

	if( ( (buttonTemp0 & BUTTON_MASK_0) != BUTTON_MASK_0) || 
		( (buttonTemp1 & BUTTON_MASK_1) != BUTTON_MASK_1) )
	{
		if(g_GpioButtonEvent.ButtonStatus != GPIO_SCANKEY_PR)
		{
			if(!(buttonTemp1 & BUTTON_RIGHT))
			{
				g_GpioButtonEvent.ButtonEvent = RIGHT_CLICKED;
			}
			else if(!(buttonTemp0 & BUTTON_MID))
			{
				g_GpioButtonEvent.ButtonEvent = MID_CLICKED;
			}
			else if(!(buttonTemp0 & BUTTON_LEFT))
			{
				g_GpioButtonEvent.ButtonEvent = LEFT_CLICKED;
			}
			else if(!(buttonTemp0 & BUTTON_CPI_P))
			{
				g_GpioButtonEvent.ButtonEvent = CPI_P_CLICKED;
			}
			else if(!(buttonTemp1 & BUTTON_CPI_M))
			{
				g_GpioButtonEvent.ButtonEvent = CPI_M_CLICKED;
			}
			else
			{
				g_GpioButtonEvent.ButtonEvent = 0;
				g_Main_Setting.MouseEvent &= ~MAIN_FLAG_MOUSE_BUTTON_EVENT;
			}
	
			if(g_GpioButtonEvent.ButtonEvent > 0)
			Ret = TRUE;
		}
	}
	else
	{
		// Willie 18-03-2016
		// Added additional check, if button event is non-zero, set to zero here due to no click detected,
		// in order to reset clicking state machine 
		if((g_GpioButtonEvent.ButtonStatus == GPIO_SCANKEY_PR )|| (g_GpioButtonEvent.ButtonEvent != 0) )
		{	
			g_GpioButtonEvent.ButtonEvent = 0;
		}
	}

	//if((CHECK_MOTION_PIN() == HIGH) && (glitch_prevention == 0))  
	if(glitch_prevention == 0)  
	{
	
		if( ( g_GpioButtonEvent.ButtonEvent == CPI_P_CLICKED) || 
			( g_GpioButtonEvent.ButtonEvent == CPI_M_CLICKED) )
		{
			if(trigger_send_cpi_click == 0) 
			{
				cpi_clicked_flag = 1;

				/*
				if(g_GpioButtonEvent.ButtonEvent == CPI_P_CLICKED)
					cpi_p_Cntr++;
				else
					cpi_m_Cntr++;
				*/

				if( (cpi_p_Cntr > CPI_CLICK_DURATION) || 
					(cpi_m_Cntr > CPI_CLICK_DURATION) )
				{
					trigger_send_cpi_click = 1;
	
					if(cpi_p_Cntr > CPI_CLICK_DURATION)
					{
						cpi_p_Cntr = 0;	// send P to sensor
		
						if(cpiTemp < 7)
							cpiTemp = cpiTemp + 1;
					}
					if(cpi_m_Cntr > CPI_CLICK_DURATION)
					{
						cpi_m_Cntr = 0;	// send M to sensor
		
						if(cpiTemp > 0)
							cpiTemp = cpiTemp - 1;
					}
					
					
					
					
					if (cpiTemp > 5){
					nsAPI_SSP_Sensor_Write(0x4D, 0x90);}  //set 100cpi step size
					else{
					nsAPI_SSP_Sensor_Write(0x4D, 0x10);}  //set 50cpi step size

					if (cpiTemp > 2){
					nsAPI_SSP_Sensor_Write(0x5A, 0x90);}  //ripple control on
					else{	
					nsAPI_SSP_Sensor_Write(0x5A, 0x10);}	//ripple control off
					
					nsAPI_SSP_Sensor_Write(0x4E, cpi_lo_data[cpiTemp] );
					
					
					// LED Setting				
					NDrv_GPIO_SetBitValue(PORT0,20,(cpiTemp & BIT2)^BIT2); // DLED 1  PORT 0 _20
					NDrv_GPIO_SetBitValue(PORT1,26,(cpiTemp & BIT1)^BIT1); // DLED 2  Port 1 _26				
					NDrv_GPIO_SetBitValue(PORT1,27,(cpiTemp & BIT0)^BIT0); // DLED 3  Port 1 _27	
				}
			}
		}
		else
		{
				trigger_send_cpi_click = 0;
				cpi_m_Cntr = 0;
				cpi_p_Cntr = 0;
				cpi_clicked_flag = 0;
		}
	}
	return Ret;
}


void Z_Wheel()
{
	#define SCROLL_TREND	3
	#define SCROLL_SUBSIDY	1
	#define Z_COUNT			1
	static U8 ZA_PRE = 0;
	static U8 ZB_PRE = 0;
	//static S8 temp_z_ctr = 0;
	static U8 temp_z_up_trend = 0;
	static S8 temp_z_down_trend = 0;

	U32 temp0 = 0;
	U32 temp1 = 0;
	U8 ZA_CUR = 0;
	U8 ZB_CUR = 0;

	temp0 = nsAPI_GPIO_GetPinValue(PORT0,0xFF);
	temp1 = nsAPI_GPIO_GetPinValue(PORT1,0xFF);

	if(IS_BIT_SET(temp0,ZB_WHEEL))
		ZB_CUR = 1;
	
	if(IS_BIT_SET(temp1,ZA_WHEEL))
		ZA_CUR = 1;

//solved z wheel scrolling buy (9 Nov 2016)	
if ( ZB_CUR != ZB_PRE)
{
	if(ZA_CUR ==0)
	{
		if(ZB_CUR == 0 && ZA_PRE ==0 && ZB_PRE == 1)
		{//B fell, A is low
			count_z++;
		}
		else
		{//B fell , A is High
			count_z--;
		}
	}
	else
	{
		if(ZB_CUR == 0 && ZA_PRE ==0 && ZB_PRE == 0)
		{//B rose, A is low
			count_z--;
		}
		else
		{//B rose, A is High
			count_z++;
		}
	}
}

	if(count_z != 0x00)
	{
		g_Main_Setting.MouseEvent |= (MAIN_FLAG_MOUSE_EVENT|MAIN_FLAG_MOUSE_REPORT_READY);		
	}
	
	ZA_PRE = ZA_CUR;
	ZB_PRE = ZB_CUR;
	
}

