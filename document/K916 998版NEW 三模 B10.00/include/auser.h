#define  R0		P7_0	//PIN62
#define  R1		P7_1	//PIN61
#define  R2		P7_2	//PIN60
#define  R3		P7_3	//PIN59
#define  R4		P5_3	//PIN13
#define  R5		P5_4	//PIN14

#define C0		P6_0	//PIN63
#define C1		P6_1	//PIN1
#define C2		P6_2	//PIN3
#define C3		P6_3	//PIN4
#define C4		P6_4	//PIN5
#define C5		P6_5	//PIN6
#define C6		P6_6	//PIN7
#define C7		P6_7	//PIN8
#define C8		P5_0	//PIN10
#define C9		P5_1	//PIN11
#define C10	P5_2	//PIN12
#define C11	P5_7	//PIN17

#define C12	P4_0	//PIN47
#define C13	P4_2	//PIN49
#define C14	P4_3	//PIN50
#define C15	P4_5	//PIN52
#define C16	P4_6	//PIN53

#define C17	P7_4	//PIN58
#define C18	P0_5	//PIN26
#define C19	P0_6	//PIN27
#define C20	P0_7	//PIN28


#define  DR0  P1_0//PIN29	PWM20
#define  DG0  P1_1//PIN30 PWM21
#define  DB0  P1_2//PIN31	PWM22

#define  DR1  P1_3	//PIN32 PWM23
#define  DG1  P1_4 //PIN33  PWM24
#define  DB1  P1_5//PIN34   PWM25

#define  DR2  P2_0//PIN35  PWM10
#define  DG2  P2_1//PIN36  PWM11
#define  DB2  P2_2//PIN37  PWM12

#define  DR3  P2_3//PIN38  PWM13
#define  DG3  P2_4//PIN39  PWM14
#define  DB3  P2_5//PIN40  PWM15

#define  DR4  P3_3//PIN44 PWM03
#define  DG4  P3_4//PIN45 PWM04
#define  DB4  P3_5//PIN46  PWM05

#define  DR5  P3_0//PIN41  PWM00
#define  DG5  P3_1//PIN42  PWM01
#define  DB5  P3_2//PIN43  PWM02
//-----------------------------------------------------
#define  SPI_SS			P7_5	//PIN57
#define  SPI_SCK			P4_7	//PIN54 输出去上拉v
#define  SPI_MOSI		P0_4	//PIN25  输出 去上拉v
#define  SPI_MISO		P0_3	//PIN24   输入去上拉v
#define  SPI_MOT			P0_2	//PIN23  输出  有上拉v
#define  SLEEP_PIN		P4_1	//PIN48  P11-A  输入 去上拉

#define  SPI_MISO_DirIn		{ P0CR &= ~(1<<3); }	//P0CR &= ~0X08;	//0 输入	

#define  SPI_SCK_DirIn			{ P4CR &= ~(1<<7); }	//P4CR &= ~0X80;		//0 输入		
#define  SPI_SCK_Out			{ P4CR |= (1<<7); }		//P4CR |= 0X80;		//1 输出	
	
#define  SPI_MOSI_DirIn		{ P0CR &= ~(1<<4); }	//P0CR &= ~0X10;		//0 输入		
#define  SPI_MOSI_Out		{ P0CR |= (1<<4); }		//P0CR |= 0X10;		//1 输出	
	
#define  SPI_MOT_DirIn		{ P0CR &= ~(1<<2); }	//P0CR &= ~0X04;		//0 输入		
#define  SPI_MOT_Out			{ P0CR |= (1<<2); }		//	P0CR |= 0X04;		//1 输出	
	
#define  SPI_SS_DirIn			{ P7CR&= ~ (1<<5); }	//P4CR &= ~0X10;		//0 输入		
#define  SPI_SS_Out			{ P7CR |= (1<<5); }		//P4CR |= 0X10;			//1 输出	

#define  	USB_Opine		P4_4	//PIN51	v 输入去上拉
#define	LDO_D				P7_6	//PIN56	TMS	v	输出

//#define	Power_In			P7_7	//PIN55 TDI	v	 输入去有上拉充满高电平

#define  	Usb_In			P7_7	//PIN55 TDI	v	 输入去有上拉充满高电平
//#define  	Opine_24G		P5_6	//PIN16	v

#define 	WHEEL1  P5_5
#define 	WHEEL2  P5_6
#define 	WHEEL_DirIn	P5CR &= ~0x60
#define	WHEEL_PullEn	P5PCR |= 0x60
//-----------------------------------------------------
#define  R		0
#define  G		1
#define  B		2
#define	In_LED		0
#define	General_RID		0x09
#define	LedMode_RID		0x0A

#define	Color_RID			0x0B
#define	MatrixKey_RID	0x0C
#define	MOUSE_RID1		0x0D

#define OUT0_General_PHASE 		0X09
#define OUT0_KeyMode_PHASE		0X0A

#define OUT0_Color_PHASE			0X0B
#define OUT0_KeyMacro_PHASE		0x0C
#define OUT0_NoKnow_PHASE 		6
#define Limit_Power 		5		//5~15~20 ....
//*****************D+*************************
#define USB_AuxDP_NPull		{ P0PCR &= ~(1<<1); }
#define USB_AuxDP_DirIn		{ P0CR &= ~(1<<1); }
#define USB_AuxDP_DirOut	{ P0CR |= (1<<1); }
#define USB_AuxDP_Out0		{ P0 &= ~(1<<1); }
//*****************D-******************
#define USB_AuxDM_NPull		{ P0PCR &= ~(1 << 0); }
#define USB_AuxDM_DirIn		{ P0CR &= ~(1 << 0); }
#define USB_AuxDM_DirOut	{ P0CR |= (1 << 0); }
#define USB_AuxDM_Out1		{ P0 |= (1 << 0); }
//******************************************
extern U8	idata	break_Data[21];
extern U8 data	Temp_Time1;
extern bit fhas_change;	
extern bit b_Feel_Mode;
extern U16 xdata Run_Time2;
void Enable_PWM(void);
extern U16  mul8by8(U8 value1, value2);
extern U8 xdata 	break_Time[126];
extern bit 	Reset_Mode;
extern U8	xdata	Power_status_Data;
extern bit	b_PowerLow;
extern U8 xdata Wirte_State;
extern U8 xdata Module_LED_status2;
extern U8 xdata Logo_Image[8];
void Int_Logo_Data(void);
//***************************************

U8 Brack_b(U8 Temp_Imge2);
void Deal_Image_data(void);
void Save_Imaging_Data(U8 Temp_USB_Data);//实时灯效
void Save_USB_Data(U8 Temp_USB_Data);
extern U8 xdata	NUM_Image[3][126];
extern U8 data Scan_TimeUp;
extern U8 xdata 	Reset_Delay;
extern U8 xdata Sleep_Times;
extern U8 data RLT_Index;
extern U8 data RLT2_Index;
//extern bit	b_Feel_Mode;
extern bit b_Start_Change_Mode2;
extern U8 xdata USB_Ind_Num;
extern U16 xdata Usb_Ind_Length;
extern U8	xdata	Last_Time3;
extern bit	USB_Opine_Up;
extern bit fg_Power_Led;
extern bit fg_Power_Led2;
extern bit	Wire_suspend_1;
extern U8 xdata USBImge_First;
extern bit	b_LiuGuang_Mode7;
extern U8 xdata Heng_Temp_NUM;
extern U8	xdata	Temp_Image_Time;
extern bit	mode_change_flag;
//extern U8 xdata Int_status;
extern U16 data No_Key_Times;
extern U16 data No_Key_Times2;
extern bit	bKey_Mode;
extern U8 xdata Manual_Record_UNM;
extern U8 xdata Macro_Time2[9];
extern U16 xdata  Delay_Macro_Time2[9];
extern U8	xdata	Macro_Usb2_Data2[16];
extern U8	xdata	Last_Macro_Usb2_Data2[16];
extern U32 xdata	fg_Next_Time2;
extern U16 xdata fg_Send_Macro2;
extern bit bPower_Up;
extern bit b_022;
extern U8	xdata	Last_Mcaro_Ctrl_Data2;
extern U8	xdata	Mcaro_Ctrl_Data2;
void Judge_Macro_Data2(void);
void Send_Macro_USB_Data2(void);
extern U8 xdata Macro2[65];
void Manual_Macro_Data(void);
void Manual_Mian_Macro(void);
void Save_Macro2_Data(U8 Macro_NUM);
extern U8 xdata G_Led[4];
//******************************************
extern U16 data	Temp_Brightness2;
extern U8 xdata	PWM_Data;
extern U8 xdata RGB_Num;
extern U8 xdata	Mode_Handr_Times;
void Let_NUM_Image(void);
void Change_AColor_Time(U8 TempNUM);
void KeyDown_Image3(Temp_Image_Num);
extern U8	xdata	Key_DownNum[126];
extern U8 xdata 	KeyDown_Time[126];
void Multimedia_Tab_Data(U8 No_Multimedia);
void Deal_Wheel(void);
//void Save_Flash_Data(U8 Temp_FlashData);
//*****************************************
extern bit	fg_500ms;
//extern U8 xdata Lsat_Mode_now;
extern U16 xdata USB_Mode_Times;
extern U8 xdata Module_State_Data[4];
extern U8 xdata SB_Status;
void Read_State_Data(void);
void Write_ReadState_Data(void);
void Lang_KeyDown_ModuleMode(U8 Temp_ModuleMode_Times);
void Short_KeyDown_ModuleMode(U8 Temp_ModuleMode_Times);
//*****************************************
void Clear_Text_EMI_Data(void);
U8 Change_Mode_Data(U8 Temp_Imge2);
extern U8 data	R_Color;
extern U8 data	G_Color;
extern U8 data	B_Color;

extern bit	b_EMI_24Mode;
extern bit	b_EMI_30Mode;
extern	U8 bdata Mode_now;
extern bit	Mode_24G;
extern bit	Mode_Bluetooth1;
extern bit	Mode_Bluetooth2;
extern bit	Mode_Bluetooth3;
extern bit	Mode_USB;
extern bit	Ready_ok;
//extern bit	UsbOut_ok;
extern bit	Wireless_suspend;
extern U8 data Cnt_2ms;
extern U16 xdata Module_DataTimes;
extern U8 xdata Check_Data;
extern U8 xdata Module_Data[32];
void Int_Module(void);
void Module_Command_Data(U8 Temp_Module);
void Clear_All_ModeBit(void);
void Send_Wireless_Data(void);
void Send_Command_Data(U8 Temp_Module2);
void Send_USB_Out_Data(void);
void Module_Led_Data(U8 Temp_Module);
void Brightness_Sub(void);
void Brightness_Add(void);
void F_Text_Opine(void);
void Deal_VDR(U8 Temp_IO,Temp_Num);
//**************************************
void Deal_R(void);
void key_set_port(U8 set_line,set_data);
extern bit	fg_Inting;
extern U8 xdata Mode_Bluetooth_Times;
extern U16 	xdata  Change_ModeTimes;
extern U8	data	Temp_R;
//extern U8 xdata	Max_Brightness_Wheels;
extern U8	data	Color_Random;
extern bit	TempE;
extern bit	fg_16ms;
extern U8 data	Image_256_R;
extern U8 data	Image_256_G;
extern U8 data	Image_256_B;
extern U8 data Color_Times;
extern U8 xdata Mcaro_Ctrl_Data;
extern U8 xdata ck_DP_ST;
extern U8 xdata ck_DM_ST;
extern bit	bKey_F_Mode;
extern U16 data esd_sof_cnt;
extern bit esd_flag;
extern bit b_Feel_Mode;
extern bit b_Image2_Ok;
extern U16 xdata Image2[3][126];
extern U16 xdata esd_sof_cnt1;
extern U16 xdata Delay_EFT_Times;
extern bit	IN_send_flag;
extern bit	b_No_xdata;
extern U8 data	bug_delay_cnt;
extern bit	B_Received_General;
extern bit	B_Received_Mode;
extern U8 data	LED_status;
extern bit	b_PaoMa3_Mode;
extern bit	bchange_key;
extern bit	bWin_Locks;
extern bit	bAll_Key_Lock;
extern bit fg_1ms;
extern bit fg_2ms;
extern bit fg_4ms;
extern bit fg_8ms;
extern bit 	b_Cloes_Mode;
extern bit b_ShutDown;
extern bit	bFn;
extern bit	bSend_IN2;
extern bit	b_HangPao_Mode;
extern bit	b_01;
extern bit	b_04;
extern bit	b_05;
extern bit	b_06;
//extern bit	fg_Scan;
extern bit	b_PaoMa1;
extern bit	b_PaoMa2;
extern bit	b_PaoMa3;
extern bit	b_Cpl1;
extern bit	b_Cpl2;
extern bit	b_ChangLiang_Mode;
extern bit	b_HuXi_Mode;
extern bit	b_LiuGuang_Mode;
extern bit	b_PaoMa1_Mode;
extern bit	b_PaoMa2_Mode;
extern bit	b_LiuGuang_Mode5;
extern bit	b_LiuGuang_Mode6;
extern bit	b_SuiLiang_Mode;
extern bit	b_SuiMie_Mode;
extern bit	b_Raindrops_Mode;
extern bit	b_BoLang_Mode;
extern bit	b_WASD_Mode;
extern bit	b_Effect_light_1;
extern bit	b_Effect_light_2;
extern bit	b_Pao_Heng;
extern bit	b_PaoMa4_Mode;
extern bit	b_HuXi_Mode2;
extern bit	b_LiuGuang_Mode2;
extern bit	b_LiuGuang_Mode3;
extern bit	b_LiuGuang_Mode4;
extern U8 xdata	b_Effect_light_1_Cpl;
extern U8 xdata	TimeTemp1;
extern U16 xdata	Usb_ImageID;
extern U8	idata	V_Data[21];
extern U16 	xdata Image[3][126];
//extern U8 	xdata Image_Brightness[126];
extern U8	idata	Last_Send_data[7];
extern U8 	data	Speed_Data;
extern U8 data	Delay_2ms;
extern U8 	data	Temp_Time1;
extern U8	idata	Multimedia_Data[2];
extern U8	idata	Usb2_Data[16];
extern U8	idata	Send_data[7];
extern U8 xdata 	*buffer_addr;
extern U8 xdata 	Mode_Times;
extern U8 data 	Brightness_Wheels;
extern U8 xdata	Last_CL_Brightness_Wheels;
extern U8 xdata 	Temp_Time2;
extern	U8 xdata 	Temp_1;
extern U16 xdata 	Run_Time;
extern U8 data 	Image_Num;
extern U8 data 	Key_Index;
extern U8 xdata 	Temp_Speed;
extern bit	fg_suspend;
extern bit	b_Sleep_Out;
extern bit b_Record_Mode;
extern bit bSpeed_End;
extern bit b_PaoMa4;
extern U8  xdata	bSpeed_data2;
//extern bit b_Start_Go;
extern bit fg_Remote;
extern bit	b_LiuGuang_Mode2;
extern bit	b_RainMu_Mode;
extern bit	b_Flower_Mode;
extern bit	b_HengMie_Mode;
extern bit	B_Received_WASD;
extern bit	B_Received_KeyMacro;
extern U8 xdata PaoMa2_Times;
extern U8 xdata Image_Times;
extern U16 xdata WriteEE_Address;
extern U8 xdata Temp_Add;
extern U8	xdata	PaoHeng_Image_Num[10];
extern U8	xdata	Image_Num_Times[10];//5
extern U16 xdata	b_Heng_Mode;
extern U8	xdata	Temp_NUM_Image;
extern U8 xdata Mode5_Time;
extern U8 xdata Temp_NUM;
extern U8 xdata Brightness_s;
extern U8 xdata V_Delay_PWM;
extern U8 xdata PWM_T;
extern U8 xdata HuXi_Mode2_Times;
extern U8	xdata	General_Data[504];
extern U8	data	Temp_data;
extern bit	BEP2_Mouse_KEY;
extern U8 xdata mouse_key_buff[8];
extern bit b_02;
extern bit b_Text_Mode;
extern U8	xdata	Macro_Usb2_Data[16];
extern U8 xdata Module_LED_status;
extern U8 data Power_status;
void USBImge_To_RGB_Imge(U8 Temp_Imge2);
void Text_Mode(void);
//*****************************************
extern bit b_Ready_To_Read;

extern U8 xdata Delay_Times_Module;
extern U8 xdata Delay_Times_Module2;
void Module_Read_Data(U8 Temp_Module);
void Deal_NUM_Led(void);
U8 Read_Module_Data(void);
void Deal_Wireless_Name(void);
//***************************************
extern U16 xdata V_Tab_Data;
extern U8 xdata Temp_Time3;
extern U8 xdata Macro_Cycle_Time[10];
extern  U8 xdata Macro[10][192];
extern U32 xdata fg_Send_Macro;
void Send_Macro_USB_Data(void);
U8 Deal_IN2_Data(U8 Data_i);
//***************************************
extern U8  xdata	bSpeed_data;
extern U8 xdata 	Logo_Mode_Times;
extern U8 xdata 	Mode_Bluetooth_Times;
void Int_Logo_Data(void);
void Deal_Logo_Key(void);
void Clear_Logo_Data(void);
void Send_Logo_Data(void);
extern U8 xdata	Multimedia_Wheel_Data;
extern U8 xdata	Multimedia_Wheel_Data2;
extern bit	b_03;
void Wheel_Check(void);
//***************************************
void Clear_Module_Data(void);
int RandSub(U8 T_RandSub);
void Deal_P7_Data(U8 Temp_NUM,Temp_Run_Time);
void Give_NUM_Image(U8 Temp_NUM,Temp_Color,Image_Brightness);//λ ɫ ֵ
void Deal_R0_Image2(void);
void Deal_R1_Image2(void);
void Deal_R2_Image2(void);
void Deal_R3_Image2(void);
void Deal_R4_Image2(void);
void Deal_R5_Image2(void);
void Save_Macro_Data(void);
void Read_Macro_Data(void);
void pwm_init(void);
void Deal_K45_Image(void);
U8 Deal_Down_K45_Image(U8 Temp_Imge2);
void Deal_PWM_Delay(void);
void Move_Data_Tab(U8 TempNUM);
void Save_KeyIndex_Data(void);
void Deal_PaoMa_3(void);
void Start_Mode6_Led4(void);
void Deal_LiuGuang_4(void);
void Deal_USB_Save_Data(void);
void Deal_R0_Image2(void);
void Deal_R1_Image2(void);
void Deal_R2_Image2(void);
void Deal_R3_Image2(void);
void Deal_R4_Image2(void);
void Deal_R5_Image2(void);
void KeyDown_Image2(Temp_Image_Num,NUM_Brightness);
void Clear_PaMa2_Data(void);
void Int_Mode6_Data2(void);
void Deal_Speed_LED_End(void);
void Clear_Flash_Data(void);
void Display_WASD(void);
void Read_WASD_Image(U8 Temp_Images);
void Deal_Tbl_Image(Key_Image);
void Change_Key(void);
void Deal_Mode_5(void);
void Deal_Pao2Bian_Mode(void);
void Deal_Image_Num(void);
void KeyDown_Image(Temp_Image_Num);
void Clear_Mode_Data(void);
void Start_Effect_light_Time1(void);
void Deal_Raindrops_Mode(void);
void Deal_Rest_Data(void);
void Change_Speed(void);
void Deal_Rest(void);
U8 Deal_Tbl_Image2(Key_Image2);
void Sacn_Key_Led_Up2(void);
void Sacn_Key_Led_Up(void);
void Deal_PaoMa_2(void);
void timer2_init(void);
void Dispaly_BoLang_Mode(void);
void Deal_KeyDown(void);
void USBSOF_BT_1ms(void);
void Display_Mode(void);
void Deal_PaoMa_1(void);
void delay_us(U16 cnt);
void IN1_IRQ_Prog_Data(void);
void IN2_IRQ_Prog_Data(void);
void Deal_C(void);
void Start_PWM_Led(void);
void Start_Mode6_Led(void);
void Int_Mode6_Data(void);
void Move_Key_value(void);
void Send_Usb_value(void);
void KeyScan2(void);
void KeyScan(void);
void updata_Status_Led(void);
void Change_Brightness(void);
void Give_All_Image(U8 Image_Brightness);
void Change_Mode(void);
void Display_ChangLiang_Mode(void);
void Read_Mode_Time(void);
void Deal_Image_Num(void);
void Deal_PaoMa_4(void);
void Send_TextMode_Data(U8 Temp_Module);
void Text_EMI_Mode(void);
void Display_Logo_Data(void);
void Deal_Logo_key(void);
void Give_Logo_Data(U8 Temp_Color,Temp_Logo);
void Deal_Image2_Data(void);
U8 Pin_Data(U8 Temp_Imge2);
U8 Port_Data(U8 Temp_Imge2);
void Deal_Image_Num2(U8 PaoHeng_Index);
U8 PWM_AddData(U8 Temp_Imge2,Temp_Imge2Data);
void Send_Usb_value(void);