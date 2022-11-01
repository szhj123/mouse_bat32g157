#include "..\include\SH68F90.h"
#include "..\include\stdtype.h"
#include "..\include\usb_db.h"
#include "..\include\mcu_def.h"
#include "..\include\CFG.h"
#include "..\include\usb_def.h"
#include "..\include\auser.h"
#include <intrins.h>
#include <string.h>
bit usb_config_ok;
bit	fg_LedMode;
U16 xdata	Usb_ImageID;
U16 xdata 	out0_dat_cnt;
U8 xdata 	RX_DATA[8];
//////////////////////////
U8 xdata	usb_irq_reg1;
U8 xdata 	usb_irq_reg2;
U8 xdata 	*buffer_addr;
U8 xdata 	usb_rx_data[8];	
U8 xdata 	ep0_phase;
xdata U8 	code *code_pt;
U16 xdata 	in0_dat_cnt;
U16 xdata	 usb_length;
U8 data	LED_status;
bit device_remote_wakeup_f;
U8 xdata EP1_IDLE_TIME;
U8 xdata EP1_IDLE_COUNT;
U8 xdata Protocol_type0,Protocol_type1;
U8 xdata Suspend_Counter;
bit	fg_suspend;//驱动发命令=1控制休眠，也可由拨动开关决定

U8 xdata configution_value;
//U8 xdata usb_config_flag;
xdata rx0_buffer_union rx0_buffer;
U8 xdata Suspend_Counter;
U8 xdata *out_address;
//U8 xdata out2_length;
 /////////////////////////////////////////////////////////
static void prep_ep0_out_dat(void);
static void prep_ep0_out_KeyMacro_dat(void);
static void prep_ep0_out_KeyMode_dat(void);
static void prep_ep0_out_Color_dat(void);//接收0X0B的数据
static void prep_General_ep0_in_dat(void);
static void prep_KeyMacro_ep0_in_dat(void);
static void prep_LedMode_ep0_in_dat(void);
static void prep_Color_ep0_in_dat(void);
extern void usb_init(void);
extern void ISPJMP(void);
/******************************************************************************************
Code emu (皌竚ㄧ计)
******************************************************************************************/
code void (*request_func_table[]) (void) =
{
	stall_ep0,					     //0
	clear_remote_wakeup,		//1
	clear_endpoint_halt,		//2
	set_remote_wakeup,			//3
	set_endpoint_halt,			//4
	set_address,				    //5
	set_configuration,			//6
	set_interface,					//7
	set_descriptor,					//8
	get_device_status,			//9
	get_interface_status,		//10
	get_endpoint_status,		//11
	get_descriptor,					//12
	get_configuration,			//13
	get_interface,					//14
	get_report,							//15
	set_report,							//16
	USB_HID_SETIDLE,				//17
	USB_HID_GET_IDLE,				//18
	USB_HID_SETPROTOCOL,		//19
	USB_HID_GETPROTOCOL			//20
};
/******************************************************************************************
setup_request_index
******************************************************************************************/
enum setup_request_index
{
	stall_ep0_index,					//0
	ClearRemoteWakeup_index,	//1
	ClearEndpointHalt_index,	//2
	SetRemoteWakeup_index,		//3
	SetEndpointStall_index,		//4
	SetAddress_index,					//5
	SetConfiguration_index,		//6
	SetInterface_index,				//7
	SetDescriptor_index,			//8
	GetDeviceStatus_index,		//9
	GetInterfaceStatus_index,	//10
	GetEndpointStatus_index,	//11
	GetDescriptor_index,			//12
	GetConfiguration_index,		//13
	GetInterface_index,				//14
	GetReport_index,					//15
	SetReport_index,					//16
	USB_HID_SETIDLE_index,		//17
	USB_HID_GET_IDLE_index,		//18
	USB_HID_SET_PROTOCOL_index,	//19
	USB_HID_GET_PROTOCOL_index	//20
};
enum setup_request_index function_index;
/******************************************************************************************
SETUP data
******************************************************************************************/
const U8 code setup_req_table[] =
{
	HOST_TO_DEVICE | STANDARD | DEVICE,	USB_CLEAR_FEATURE,
	ClearRemoteWakeup_index,		// clear device feature 0x00, 0x01

	HOST_TO_DEVICE | STANDARD | ENDPOINT,	USB_CLEAR_FEATURE,
	ClearEndpointHalt_index,		// clear feature: clear endpoint halt //0x02, 0x01

	HOST_TO_DEVICE | STANDARD | DEVICE,	USB_SET_FEATURE,
	SetRemoteWakeup_index,			// set device feature 0x00, 0x03

	HOST_TO_DEVICE | STANDARD | ENDPOINT,	USB_SET_FEATURE,
	SetEndpointStall_index,			// set feature: set endpoint stall //0x02 0x03

	HOST_TO_DEVICE | STANDARD | DEVICE,	USB_SET_ADDRESS,
	SetAddress_index,				// set address 0x00, 0x05

	HOST_TO_DEVICE | STANDARD | DEVICE,	USB_SET_CONFIGURATION,
	SetConfiguration_index,			// set configuration 0x00, 0x09

	HOST_TO_DEVICE | STANDARD | INTERFACE,	USB_SET_INTERFACE,
	SetInterface_index,				// set interface 0x01, 0x0B

	HOST_TO_DEVICE | STANDARD | DEVICE,	USB_SET_DESCRIPTOR,
	SetDescriptor_index,			// set descriptor 0x00, 0x07

	DEVICE_TO_HOST | STANDARD | DEVICE,	USB_GET_STATUS,
	GetDeviceStatus_index,			// get device status :0x80 0x00

	DEVICE_TO_HOST | STANDARD | DEVICE,	USB_GET_DESCRIPTOR,
	GetDescriptor_index,			// get descriptor //0x80 0x06

	DEVICE_TO_HOST | STANDARD | INTERFACE,	USB_GET_DESCRIPTOR,
	GetDescriptor_index,			// get descriptor //0x81 0x06

	DEVICE_TO_HOST | STANDARD | DEVICE,	USB_GET_CONFIGURATION,
	GetConfiguration_index,			// get configuration //0x80 0x08

	DEVICE_TO_HOST | STANDARD | INTERFACE,	USB_GET_STATUS,
	GetInterfaceStatus_index,		// get interface status //0x81 0x00

	DEVICE_TO_HOST | STANDARD | ENDPOINT,	USB_GET_STATUS,
	GetEndpointStatus_index,		// get endpoint status //0x82 0x00

	DEVICE_TO_HOST | STANDARD | INTERFACE,	USB_GET_INTERFACE,
	GetInterface_index,				// get endpoint status //0x81 0x0A

	DEVICE_TO_HOST | CLASS | INTERFACE,	HID_GET_REPORT,
	GetReport_index,				// get report: 0xA1, 0x01

	HOST_TO_DEVICE | CLASS | INTERFACE,	HID_SET_REPORT,
	SetReport_index,				// set report: 0x21, 0x09

	HOST_TO_DEVICE | CLASS | INTERFACE,		HID_SET_IDLE,
	USB_HID_SETIDLE_index,			//set idle: 0x21, 0x0A

	DEVICE_TO_HOST | CLASS | INTERFACE,		HID_GET_IDLE,
	USB_HID_GET_IDLE_index,			//get idle: 0xA1, 0x02

	HOST_TO_DEVICE | CLASS | INTERFACE,		HID_SET_PROTOCOL,
	USB_HID_SET_PROTOCOL_index,		//set protocol: 0x21, 0x0b


	DEVICE_TO_HOST | CLASS | INTERFACE,		HID_GET_PROTOCOL,
	USB_HID_GET_PROTOCOL_index,		//get protocol: 0xA1, 0x03
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* USB_COMPUTER_PROCESS*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void USB_QueryINT_Prog(void)
{
	usb_irq_reg1 = USBIF1;
	if(usb_irq_reg1 != 0x00)						//check USBIF1 flag
	{
		if(usb_irq_reg1 & BIT3)	  				// SOF 
		{
			USBIF1 &= ~BIT3;	//clear SOF flag	
			USBSOF_BT_1ms(); 		
			USB_Mode_Times=0;			
			mode_change_flag=1;	
			No_Key_Times2=0;			
		}
		else
		{
			USBIF1 &= ~(BIT4|BIT3);					// Clear SETUPIF & SOF first
			USBIF1 &= ~(BIT6|BIT5);					//SETUP OVERIF &  OW

			if(usb_irq_reg1 & BIT7)					//USB POWER ON INT
			{
				USBIF1 &= ~BIT7;
				USB_INIT();
				//Suspend_Counter=0x00;
			}
			else if(usb_irq_reg1 & BIT4)			//SETUP INT
			{
				SETUP_IRQ_Prog();
			}
			else if(usb_irq_reg1 & BIT2)			//RESUME INT
			{
				USBIF1 &= ~BIT2;			
			}
			else if(usb_irq_reg1 & BIT1)			//SUSPEND INT
			{
				USBIF1 &= ~BIT1;	
				SUSPEND_IRQ_Prog();
			}
			else if(usb_irq_reg1 & BIT0)			//BUS RESET
			{
				USBIF1 &= ~BIT0;	
			/*	if(usb_config_ok)				
					usb_reset_error_falg = 1;*/
			//	esd_flag = 1;
				usb_config_ok = 0;
				USBCON |= 0x20;					   			//softreset
				_nop_();_nop_();_nop_();
				_nop_();_nop_();_nop_();
				USBCON &= ~0x20;								//clear softreset

				usb_init();
				OUT0_SET_READY;
			}
		}
	}
	else
	{
		usb_irq_reg2 = USBIF2;
		if(usb_irq_reg2 != 0x00)			 	 		//check USBIF1 flag
		{
				
			if(usb_irq_reg2 & BIT6)						// EP2 OUT Event INT
			{
				USBIF2 &= ~BIT6;
				OUT2_SET_READY
				
			}
			else if(usb_irq_reg2 & BIT5)				// EP1 OUT Event INT
			{
				USBIF2 &= ~BIT5;
			////////////////////////////
			//	OUT1_IRQ_Prog();
			//	OUT1_SET_READY
			/////////////////////////
			}	
			 
				
			else if(usb_irq_reg2 & BIT4)				// EP0 OUT Event INT
			{
				USBIF2 &= ~BIT4;
				OUT0_IRQ_Prog();
				OUT0_SET_READY
			}
			else if(usb_irq_reg2 & BIT2)					// EP2 IN Event INT
			{
				USBIF2 &= ~BIT2;
				//IN2_IRQ_Prog();
			}  
			else if(usb_irq_reg2 & BIT1)					// EP1 IN Event INT
			{
				USBIF2 &= ~BIT1;
			}
			else if(usb_irq_reg2 & BIT0)					// EP0 IN Event INT
			{
				USBIF2 &= ~BIT0;
				IN0_IRQ_Prog();
			}
		}
	}
}
/******************************************************************************
USB emu task Prog
******************************************************************************/
/************************SETUP INT*******************************************/
void SETUP_IRQ_Prog(void)
{
	U8 code *table_ptr = setup_req_table;
	EA = 0;
	get_out_usb_buffer();
	EA = 1;
	function_index = stall_ep0_index;	//default stall_ep0
	do
	{ // 琩тUSB㏑摸
		if((table_ptr[0] == usb_rx_data[0]) && (table_ptr[1] == usb_rx_data[1]))
		{
			function_index = table_ptr[2];
			break;
		}
		table_ptr += 3;
	}while(table_ptr < (setup_req_table + sizeof(setup_req_table)));

	(*request_func_table[function_index]) ();
}
/************************function_index = 0 (stall_ep0)/*stop out*//*******************************************/
static void stall_ep0(void)
{
	IN0_SET_STALL;
	OUT0_SET_STALL;
}
/************************function_index = 1 (clear_remote_wakeup)/*睲埃环祘酬眶*//*******************************************/
static void clear_remote_wakeup(void)
{
	ep0_phase = NEW_SETUP_PHASE;

	if((usb_rx_data[0]&0x1f)==DEVICE_TYPE)
	{
		device_remote_wakeup_f = 0;
	}
	IN0_SetReady();
}
/************************function_index = 2 (clear_endpoint_halt)/*睲埃EP0,EP1,EP2窽ゎ块夹癘*//*********************/
static void clear_endpoint_halt(void)
{
	ep0_phase = NEW_SETUP_PHASE;

	if((usb_rx_data[0]&0x1f)==ENDPOINT_TYPE)
	{
		if(usb_rx_data[4]==0)
		{
			IN0_CANCEL_STALL;
			OUT0_CANCEL_STALL;
		}
		else if(usb_rx_data[4] == 0x81)
		{
			IN1_CANCEL_STALL;
		}
		else if(usb_rx_data[4] == 0x82)
		{
			IN2_CANCEL_STALL;
		}
		else
		{
			stall_ep0();
			return;
		}
	}
	IN0_SetReady();
}
/************************function_index = 3 (set_remote_wakeup)/*砞竚环祘酬眶*//*******************************************/
 static void set_remote_wakeup(void)
{
	ep0_phase = NEW_SETUP_PHASE;

	if((usb_rx_data[0]&0x1f)==DEVICE_TYPE)
	{
		device_remote_wakeup_f = 1;
	}
	IN0_SetReady();
}
/************************function_index = 4 (set_endpoint_halt)/*砞竚EP1┪EP2氨ゎ块*//********************************/
static void set_endpoint_halt(void)
{
	ep0_phase = NEW_SETUP_PHASE;

	if((usb_rx_data[0]&0x1f)==ENDPOINT_TYPE)
	{
		if(usb_rx_data[4]==0x81)
		{
			IN1_SET_STALL;
		}
		else if(usb_rx_data[4]==0x82)
		{
			IN2_SET_STALL;
		}
		else
		{
			stall_ep0();
		}
	}
	else
	{
		stall_ep0();
		return;
	}
			IN0_SetReady();
} 
/************************function_index = 5 (set_address)/*砞竚USB*//********************************/
static void set_address(void)
{
	ep0_phase = NEW_SETUP_PHASE;
	IEP0CNT &= ~0x0f;
	OUT0_SET_STALL;
	IN0_SET_READY;
}
/************************function_index = 6 (set_configuration)/*砞竚皌竚*//********************************/
static void set_configuration(void)
{
	ep0_phase = NEW_SETUP_PHASE;

	if(USBADDR)
	{
		if( (usb_rx_data[2]==0) || (usb_rx_data[2]==1) )
		{
			configution_value = usb_rx_data[2];
			//usb_config_flag = 1;
			usb_config_ok = 1;
			IEP0CNT &= ~0x0f;
			IN0_SET_READY;
		}
		else
		{
			stall_ep0();
		}
	}
	else
	{
		stall_ep0();
	}
	IN0_SetReady();
		IEN0 |= 0x01;
//	IEN1 |= 0x02; //enable pwm0 int
}
/************************function_index = 7 (set_interface)/*砞竚钡*//********************************/
/*,interface0琌mouse,interface1Τ夹龄絃,碈砰龄絃,ISP单贺*/
static void set_interface(void)
{
	ep0_phase = NEW_SETUP_PHASE;
	{
		if((usb_rx_data[2]==0)&&(usb_rx_data[4]==0))
		{
			IEP0CNT &= ~0x0f;
			IN0_SET_READY;
			OUT0_SET_STALL;
		}
		else if((usb_rx_data[2]==0)&&(usb_rx_data[4]==1))
		{
			IEP0CNT &= ~0x0f;
			IN0_SET_READY;
			OUT0_SET_STALL;
		}
		else
		{
			stall_ep0();
		}
	}
}
 /************************function_index = 8 (set_descriptor)//*砞竚磞瓃才,ぃや*///********************************/
 static void set_descriptor(void)
{
	stall_ep0();
}
/************************function_index = 9 (get_device_status)//*莉砞称篈*///********************************/
 static void get_device_status(void)
{
	ep0_phase = OUT0_STATUS_PHASE;
	if((usb_rx_data[0]&0x1f)==DEVICE_TYPE)
	{
		IEP0CNT &= ~0x0f;
		IEP0CNT	|= 2;
		buffer_addr = IN0_BUFFER_ADDRESS;
		if(device_remote_wakeup_f)
			*buffer_addr++ = 0x02;
		else
			*buffer_addr++ = 0x00;
		*buffer_addr = 0;
		IN0_SET_READY;
	}
	else
	{
		stall_ep0();
	}
}
/************************function_index = 10 (get_interface_status)//*莉钡篈*///********************************/
static void get_interface_status(void)
{
	if((usb_rx_data[0]&0x1f)==INTERFACE_TYPE)
	{
		if( (usb_rx_data[4]==0) || (usb_rx_data[4]==1) )		//interface0┪interface1
		{
			IEP0CNT &= ~0x0f;
			IEP0CNT	|= 2;

			buffer_addr = IN0_BUFFER_ADDRESS;
			*buffer_addr++ = 0;
			*buffer_addr = 0;
			IN0_SET_READY;
		}
		else
		{
			stall_ep0();
		}
	}
	else
	{
		stall_ep0();
	}
} 
/************************function_index = 11 (get_endpoint_status)//*莉狠翴篈*///********************************/
static void get_endpoint_status(void)
{
	if((usb_rx_data[0]&0x1f)==ENDPOINT_TYPE)
	{
		IEP0CNT &= ~0x0f;
		IEP0CNT	|= 2;
		if(usb_rx_data[4]==0x80)
		{
			buffer_addr = IN0_BUFFER_ADDRESS;
			*buffer_addr++ = ((EP0CON&0x02))>>1;	
			*buffer_addr = 0;
		}
		else if(usb_rx_data[4]==0x81)
		{
			buffer_addr = IN0_BUFFER_ADDRESS;
		//	*buffer_addr++ = ((EP1CON&0x02))>>1;
			*buffer_addr++ = ((EP1CON&0x08))>>3;
			*buffer_addr = 0;
		}
		else if(usb_rx_data[4]==0x82)
		{
			buffer_addr = IN0_BUFFER_ADDRESS;
		//	*buffer_addr++ = ((EP2CON&0x02))>>1;
			*buffer_addr++ = ((EP2CON&0x08))>>3;
			*buffer_addr = 0;
		}
		else
		{
			stall_ep0();
			return;
		}
		IN0_SET_READY;
	}
	else
	{
		stall_ep0();
	}
}
/************************function_index = 12 (get_descriptor)//*莉磞瓃才*///********************************/
static void get_descriptor(void)
{
	if(usb_rx_data[3]==GET_DEVICE_DESCRIPTOR)			//莉砞称磞瓃才
	{
		code_pt = &device_descriptor;
		in0_dat_cnt = sizeof(device_descriptor);
		usb_length = (usb_rx_data[7]<<8) | usb_rx_data[6];
		in0_dat_cnt = (usb_length<in0_dat_cnt)?usb_length:in0_dat_cnt;
	}
	else if(usb_rx_data[3]==GET_CONFIG_DESCRIPTOR)		//莉皌竚磞瓃才
	{
		code_pt = &config_descriptor;
		in0_dat_cnt = sizeof(config_descriptor);
		usb_length = (usb_rx_data[7]<<8) | usb_rx_data[6];
		in0_dat_cnt = (usb_length<in0_dat_cnt)?usb_length:in0_dat_cnt;
	}
	else if(usb_rx_data[3]==GET_STRING_DESCRIPTOR)		//莉才﹃磞瓃才
	{
		if(usb_rx_data[2]==STRING_LANGUAGE_ID)				//粂ē
		{
			code_pt = &str_dp_langID;
			in0_dat_cnt = sizeof(str_dp_langID);
			usb_length = (usb_rx_data[7]<<8) | usb_rx_data[6];
			in0_dat_cnt = (usb_length<in0_dat_cnt)?usb_length:in0_dat_cnt;
		}
		else if(usb_rx_data[2]==STRING_MANUFACTURER)		//紅坝
		{
			code_pt = &str_dp_manufact;
			in0_dat_cnt = sizeof(str_dp_manufact);
			usb_length = (usb_rx_data[7]<<8) | usb_rx_data[6];
			in0_dat_cnt = (usb_length<in0_dat_cnt)?usb_length:in0_dat_cnt;
		}
		else if(usb_rx_data[2]==STRING_PRODUCT)				//玻珇
		{
			code_pt = &str_dp_product;
			in0_dat_cnt = sizeof(str_dp_product);
			usb_length = (usb_rx_data[7]<<8) | usb_rx_data[6];
			in0_dat_cnt = (usb_length<in0_dat_cnt)?usb_length:in0_dat_cnt;
		}
		else if(usb_rx_data[2]==STRING_SERIAL_NUMBER)		//セ腹
		{
			code_pt = &str_dp_sn;
			in0_dat_cnt = sizeof(str_dp_sn);
			usb_length = (usb_rx_data[7]<<8) | usb_rx_data[6];
			in0_dat_cnt = (usb_length<in0_dat_cnt)?usb_length:in0_dat_cnt;
		}
		else if(usb_rx_data[2]==STRING_SINO)				//い縪砞称疭ㄒ
		{
			code_pt = &str_dp_sino;
			in0_dat_cnt = sizeof(str_dp_sino);
			usb_length = (usb_rx_data[7]<<8) | usb_rx_data[6];
			in0_dat_cnt = (usb_length<in0_dat_cnt)?usb_length:in0_dat_cnt;
		}
		else
		{
			stall_ep0();
			return;
		}
	}
	else if(usb_rx_data[3]==USB_REPORT)					//莉USB厨磞瓃才
	{
		if(usb_rx_data[4] == 0)								//莉狠翴1厨磞瓃才
		{
			code_pt = &HID_report_desc1;
			in0_dat_cnt = sizeof(HID_report_desc1);
			usb_length = (usb_rx_data[7]<<8) | usb_rx_data[6];
			in0_dat_cnt = (usb_length<in0_dat_cnt)?usb_length:in0_dat_cnt;
		}
		else if(usb_rx_data[4] == 1)					//莉狠翴2厨磞瓃才
		{
			code_pt = &HID_report_desc2;
			in0_dat_cnt = sizeof(HID_report_desc2);
			usb_length = (usb_rx_data[7]<<8) | usb_rx_data[6];
			in0_dat_cnt = (usb_length<in0_dat_cnt)?usb_length:in0_dat_cnt;
		}
		else
		{
			stall_ep0();
			return;
		}
	}
	else if(usb_rx_data[3]==USB_HID)					//莉HID磞瓃才
	{												
		if(usb_rx_data[4] == 0)								//莉HID1磞瓃才
		{
			code_pt = &hid_descriptor1;
			in0_dat_cnt = sizeof(hid_descriptor1);
			usb_length = (usb_rx_data[7]<<8) | usb_rx_data[6];
			in0_dat_cnt = (usb_length<in0_dat_cnt)?usb_length:in0_dat_cnt;
		}
		else if(usb_rx_data[4] == 1)					//莉HID2磞瓃才
		{
			code_pt = &hid_descriptor2;
			in0_dat_cnt = sizeof(hid_descriptor2);
			usb_length = (usb_rx_data[7]<<8) | usb_rx_data[6];
			in0_dat_cnt = (usb_length<in0_dat_cnt)?usb_length:in0_dat_cnt;
		}
		else
		{
			stall_ep0();
			return;
		}
	}
	else
	{
		stall_ep0();
		return;
	}
	prep_ep0_in_dat();
	USBIF2&=~BIT0;
	IN0_SET_READY;
}
/************************function_index = 13 (get_configuration)//*莉皌竚计沮*///********************************/
static void get_configuration(void)
{
	ep0_phase = OUT0_STATUS_PHASE;
	IEP0CNT &= ~0x0f;
	IEP0CNT = 1;
	buffer_addr = IN0_BUFFER_ADDRESS;
	*buffer_addr = configution_value;
	IN0_SET_READY;
}
/************************function_index = 14 (get_interface)//*莉钡计沮*///********************************/
  static void get_interface(void)
{
	ep0_phase = OUT0_STATUS_PHASE;
	IEP0CNT &= ~0x0f;
	IEP0CNT = 1;
	buffer_addr = IN0_BUFFER_ADDRESS;
	*buffer_addr = 0;
	IN0_SET_READY;
}
/************************function_index = 15 (get_report)//*莉HID砞称厨*///********************************/
/*获取HID设备报告 往PC发送**/
static void get_report(void)
{
	if( (rx0_buffer.Bdata[5]==0x00) && (rx0_buffer.Bdata[4]==interface0_PHASE) && (rx0_buffer.Bdata[2]==0x00)		\
	 && (rx0_buffer.Bdata[3]==REPORT_TYPE_OUTPUT) && (usb_rx_data[6]==0x00) )	//get LED status
	{
		IEP0CNT &= ~0x0f;
		IEP0CNT	|= usb_rx_data[6];
		buffer_addr = IN0_BUFFER_ADDRESS;
		*buffer_addr = LED_status;
		IN0_SET_READY;
	}
	/*
	else if((usb_rx_data[2]==General_RID)&&(usb_rx_data[3]==REPORT_TYPE_FEATURE)&&(usb_rx_data[4]==interface1_PHASE)	\
		&&(usb_rx_data[6]==0xf9)&&(usb_rx_data[7]==0x01))
	{
		
		in0_dat_cnt = 505;//0x240
		prep_General_ep0_in_dat();
		IN0_SET_READY;
	}
	*/
	else if((usb_rx_data[2]==LedMode_RID)&&(usb_rx_data[3]==REPORT_TYPE_FEATURE)	\
		&&(usb_rx_data[4]==interface1_PHASE)&&(usb_rx_data[6]==65)&&(usb_rx_data[7]==0))
	{
		in0_dat_cnt = 65;//0x31
		prep_LedMode_ep0_in_dat();
		IN0_SET_READY;			
	}
	
	else
	{
		stall_ep0();
	}
}
/************************function_index = 16 (set_report)//*砞竚HID砞称厨*///********************************/
/*设置HID设备报告	PC发数据下来	*/
static void set_report(void)
{
	if( (usb_rx_data[2]==0x00) && (usb_rx_data[3]==REPORT_TYPE_OUTPUT) && (usb_rx_data[4]==interface0_PHASE)		\
	 && (usb_rx_data[5]==0x00) && (usb_rx_data[6]==0x01) && (usb_rx_data[7]==0x00) )
	{
		ep0_phase = OUT0_LED_PHASE;
		OUT0_SET_READY;
	}
	else if( (usb_rx_data[2]==0x00) && (usb_rx_data[3]==REPORT_TYPE_OUTPUT) && (usb_rx_data[4]==interface1_PHASE)		\
	 && (usb_rx_data[5]==0x00) && (usb_rx_data[6]==0x01) && (usb_rx_data[7]==0x00) )
	{
		ep0_phase = OUT0_Rev_PHASE;
		OUT0_SET_READY;
	}
	else if((usb_rx_data[2]==ISP_RID)&&(usb_rx_data[3]==REPORT_TYPE_FEATURE)&&(usb_rx_data[4]==interface1_PHASE))
	{
		ep0_phase = OUT0_ISP_PHASE;
		OUT0_SET_READY;
	}
	////////////////////////////////////////
	
	else if((usb_rx_data[2]==LedMode_RID)&&(usb_rx_data[3]==REPORT_TYPE_FEATURE)&&(usb_rx_data[4]==interface1_PHASE)&&(usb_rx_data[6]==65)&&(usb_rx_data[7]==0))
	{
		out0_dat_cnt = 65;//0x1F8+1
		ep0_phase = OUT0_KeyMode_PHASE;
		OEP0CNT &= ~0x0f;	
		OUT0_SET_READY;		
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	else
	{
		stall_ep0();
	}
}
/************************function_index = 17 (USB_HID_SETIDLE)//*砞竚IDLE*///********************************/
 static void USB_HID_SETIDLE(void)
{
	EP1_IDLE_TIME = EP1_IDLE_COUNT = usb_rx_data[3];
	IEP0CNT &= ~0x0f;
	IN0_SET_READY;
}
/************************function_index = 18 (USB_HID_GET_IDLE)/ /*莉IDLE*///********************************/
static void USB_HID_GET_IDLE(void)
{
	buffer_addr = IN0_BUFFER_ADDRESS;
	*buffer_addr = EP1_IDLE_TIME;
	IEP0CNT &= ~0x0f;
	IEP0CNT = 0x01;
	IN0_SET_READY;
}
/************************function_index = 19 (USB_HID_SETPROTOCOL)/ /*砞竚某*///********************************/
static void USB_HID_SETPROTOCOL(void)
{
	if(usb_rx_data[4]==0x00)	// Interface0
	{
		Protocol_type0 = usb_rx_data[2];
	}
	else if(usb_rx_data[4]==0x01)	// Interface1
	{
		Protocol_type1 = usb_rx_data[2];
	}
	IEP0CNT &= ~0x0f;
	IN0_SET_READY;
}
/************************function_index = 20 (USB_HID_GETPROTOCOL)/ /*莉某*///********************************/
static void USB_HID_GETPROTOCOL(void)
{
	buffer_addr = IN0_BUFFER_ADDRESS;
	if(usb_rx_data[4]==0x00)	// Interface0
	{
		*buffer_addr = Protocol_type0;
	}
	else if(usb_rx_data[4]==0x01)	// Interface1
	{
		*buffer_addr = Protocol_type1;
	}
	IEP0CNT &= ~0x0f;
	IEP0CNT = 1;
	IN0_SET_READY;
}
//******************************************************************************
//*USB珽癬い耞*
//******************************************************************************
void SUSPEND_IRQ_Prog(void)
{
	if(Suspend_Counter > 200)	 
	{
		fg_suspend = 1;
	}
	else
	{
		if(usb_config_ok)
			Suspend_Counter++;
	}	
//		fg_suspend = 1;
}
//******************************************************************************
//*狠翴0块い耞*
//******************************************************************************
void OUT0_IRQ_Prog(void)
{
	if(ep0_phase==OUT0_LED_PHASE)			//scrlk,capslk,numlk LED
	{
		ep0_phase = 0;
		buffer_addr = OUT0_BUFFER_ADDRESS;
		LED_status = buffer_addr[0];
		IEP0CNT &= ~0x0f;
		IN0_SET_READY;
	}
	else if(ep0_phase==OUT0_Rev_PHASE)			//莉scrlk,capslk,numlk LED
	{
		ep0_phase = 0;
		IEP0CNT &= ~0x0f;
		IN0_SET_READY;
	}
	//-------------------------------------------------------------------
	else if(ep0_phase==OUT0_KeyMode_PHASE)//
	{
		CLRWDT();			//接收0X0A的数据
		prep_ep0_out_KeyMode_dat();//接收0X0A的数据
	}	
	//-------------------------------------------------------------------
	else if(ep0_phase==OUT0_ISP_PHASE)
	{
		ep0_phase = 0;
		buffer_addr = OUT0_BUFFER_ADDRESS;
		if(buffer_addr[0]==0x05)
		{
			switch(buffer_addr[1])
			{
				case 0x75:		// go to ISP Program
					ISPJMP();
					break;	  
				default:
					break;	  
			}				  
		}
	}
	else
	{
		ep0_phase = 0;
		IEP0CNT &= ~0x0f;
		IN0_SET_READY;
	}
	//ep0_phase may be OUT0_STATUS_PHASE or IN0_DATA_PHASE
}
//******************************************************************************
//*端点0输入中断*给PC发送数据
//******************************************************************************
void IN0_IRQ_Prog(void)
{
	if(ep0_phase == IN0_DATA_PHASE)
	{
		/*
		if(fg_General)
		{
			//prep_General_ep0_in_dat();//给PC发送数据
		}
		else 
		*/	
		if(fg_LedMode)
		{	
			prep_LedMode_ep0_in_dat();	
		}
		else
			prep_ep0_in_dat();
			
		IN0_SET_READY;
		OUT0_SET_READY;						//PC in0 may only occur once
	}
	else if(ep0_phase == OUT0_STATUS_PHASE)
	{
		OUT0_SET_READY;
		IN0_SET_STALL;
	}
	else								//NEW_SETUP_PHASE
	{
		IN0_SET_STALL;
		OUT0_SET_READY;
		if( (usb_rx_data[0]==(HOST_TO_DEVICE | STANDARD | DEVICE)) &&	\
			(usb_rx_data[1]==USB_SET_ADDRESS) )		//5:set address
		{
			USBADDR = usb_rx_data[2];
		}
	}

}
//******************************************************************************
//* USB task base define
//******************************************************************************
void get_out_usb_buffer(void)
{
	buffer_addr = OUT0_BUFFER_ADDRESS;
	usb_rx_data[0] = buffer_addr[0];
	usb_rx_data[1] = buffer_addr[1];
	usb_rx_data[2] = buffer_addr[2];
	usb_rx_data[3] = buffer_addr[3];
	usb_rx_data[4] = buffer_addr[4];
	usb_rx_data[5] = buffer_addr[5];
	usb_rx_data[6] = buffer_addr[6];
	usb_rx_data[7] = buffer_addr[7];
}
void IN0_SetReady(void)
{
	IEP0CNT &= ~0x0f;
	EP0CON |= BIT2;
}
void fill_in0_buf(U8 code *ctr, U8 len)
{
	U8 i;
	buffer_addr = IN0_BUFFER_ADDRESS;

	for(i=0;i<len;i++)
	{
		buffer_addr[i] = *ctr;
		ctr++;
	}
}
static void prep_ep0_in_dat(void)
{
	if(in0_dat_cnt == 0)
	{
		ep0_phase = OUT0_STATUS_PHASE;
		IEP0CNT &= ~0x0f;
	}
	else if (in0_dat_cnt > EP0_MAX_SIZE )
	{
		ep0_phase 	= IN0_DATA_PHASE;
		in0_dat_cnt -= EP0_MAX_SIZE;
		fill_in0_buf(code_pt, EP0_MAX_SIZE);
		code_pt += 8;
		IEP0CNT &= ~0x0f;
		IEP0CNT	|= EP0_MAX_SIZE;
	}
	else if (in0_dat_cnt == EP0_MAX_SIZE)
	{
		ep0_phase = IN0_DATA_PHASE;
		fill_in0_buf(code_pt, EP0_MAX_SIZE);
		in0_dat_cnt = 0;
		IEP0CNT &= ~0x0f;
		IEP0CNT	|= EP0_MAX_SIZE;
	}
	else
	{
		ep0_phase = OUT0_STATUS_PHASE;
		fill_in0_buf(code_pt, in0_dat_cnt);

		IEP0CNT &= ~0x0f;
		IEP0CNT	|= in0_dat_cnt;
	}
}
//*****************接收0X0A的数据*********************
void GET_OUT_BUFFER(void)
{
	buffer_addr = OUT0_BUFFER_ADDRESS;
	RX_DATA[0] = buffer_addr[0];
	RX_DATA[1] = buffer_addr[1];
	RX_DATA[2] = buffer_addr[2];
	RX_DATA[3] = buffer_addr[3];
	RX_DATA[4] = buffer_addr[4];
	RX_DATA[5] = buffer_addr[5];
	RX_DATA[6] = buffer_addr[6];
	RX_DATA[7] = buffer_addr[7];
}
static void prep_ep0_out_KeyMode_dat(void)//接收0X0A的数据
{
	if(out0_dat_cnt == 0)
	{
		ep0_phase = 0;
		OEP0CNT &= ~0x0f;
		IN0_SET_READY;
	}
	else if (out0_dat_cnt > EP0_MAX_SIZE )//EP0_MAX_SIZE=8
	{
		ep0_phase = OUT0_KeyMode_PHASE;
		GET_OUT_BUFFER();
		if(out0_dat_cnt == 65)
		{
			Usb_ImageID=0;
				RLT2_Index=RX_DATA[2];
			if(RLT2_Index==1)
				RLT_Index=RX_DATA[3];
			Save_Imaging_Data(RX_DATA[1]);		//07	Usb_ImageID 0	总包数
			Save_Imaging_Data(RX_DATA[2]);		//		Usb_ImageID 1	当前包数
			Save_Imaging_Data(RX_DATA[3]);		//		Usb_ImageID 2	Index
			Save_Imaging_Data(RX_DATA[4]);		//		Usb_ImageID 3	无用
			Save_Imaging_Data(RX_DATA[5]);		//		Usb_ImageID 4	data 开始
			Save_Imaging_Data(RX_DATA[6]);	
			Save_Imaging_Data(RX_DATA[7]);	
			out0_dat_cnt -= 8;  
		}
		else
		{
			Save_Imaging_Data(RX_DATA[0]);	
			Save_Imaging_Data(RX_DATA[1]);	
			Save_Imaging_Data(RX_DATA[2]);	
			Save_Imaging_Data(RX_DATA[3]);	
			Save_Imaging_Data(RX_DATA[4]);	
			Save_Imaging_Data(RX_DATA[5]);	
			Save_Imaging_Data(RX_DATA[6]);	
			Save_Imaging_Data(RX_DATA[7]);	
			out0_dat_cnt -= 8;  //EP0_MAX_SIZE=8
		}
	}
	else
	{	
		ep0_phase = 0;
		GET_OUT_BUFFER();
		//for(Data_cnt=0;Data_cnt<EP0_MAX_SIZE-out0_dat_cnt;Data_cnt++)
		{
			Save_Imaging_Data(RX_DATA[0]);
		}
		out0_dat_cnt = 0;  //EP0_MAX_SIZE=
//		cnt=0;
		OEP0CNT &= ~0x0f;
		IN0_SET_READY;
		IPH1 = 0x02;//IPH1_INIT;
		IPL1 =  0x02;
	}

}
//************************************
static void prep_LedMode_ep0_in_dat(void)//给PC发送数据
{
	U8 i,i2;
	if( in0_dat_cnt==65)
	{	
		ep0_phase 	= IN0_DATA_PHASE;
		in0_dat_cnt -= EP0_MAX_SIZE;
		buffer_addr =  IN0_BUFFER_ADDRESS;
		buffer_addr[0] = 1;
		buffer_addr[1] = 1;
		buffer_addr[2] = 1;
		buffer_addr[3] = 1;
		buffer_addr[4] = 1;
		buffer_addr[5] = 0;
		buffer_addr[6] = 0;
		buffer_addr[7] = 0;
		IEP0CNT &= ~0x0f;
		IEP0CNT	|= EP0_MAX_SIZE;
		fg_LedMode=1;
	}
	else if (in0_dat_cnt > EP0_MAX_SIZE )
	{
		ep0_phase 	= IN0_DATA_PHASE;
		in0_dat_cnt -= EP0_MAX_SIZE;
		code_pt += 8;
		IEP0CNT &= ~0x0f;
		IEP0CNT	|= EP0_MAX_SIZE;
	}
	else if (in0_dat_cnt == EP0_MAX_SIZE)
	{
		ep0_phase = IN0_DATA_PHASE;
		buffer_addr = IN0_BUFFER_ADDRESS;
		for(i=0;i<8;i++)
		{
		buffer_addr[i] = 0x00;
		}
		in0_dat_cnt = 0;
		IEP0CNT &= ~0x0f;
		IEP0CNT	|= EP0_MAX_SIZE;
	}	
	else if(in0_dat_cnt == 0)
	{
		ep0_phase = OUT0_STATUS_PHASE;
		IEP0CNT &= ~0x0f;
//		cnt=0;
		in0_dat_cnt = 0;
		fg_LedMode=0;
	}
	else
	{
		ep0_phase = OUT0_STATUS_PHASE;
		buffer_addr = IN0_BUFFER_ADDRESS;
		for(i=0;i<8;i++)
		{
		buffer_addr[i] = 0x00;
		}

		IEP0CNT &= ~0x0f;
		IEP0CNT	|= in0_dat_cnt;
		in0_dat_cnt = 0;
	}
}
//***********************************************
void Deal_FN_Data(void)
{
	if(Send_data[1]==0xb0)
		Send_data[1]=0x00;
	else if(Send_data[2]==0xb0)
		Send_data[2]=0x00;
	else if(Send_data[3]==0xb0)
		Send_data[3]=0x00;
	else if(Send_data[4]==0xb0)
		Send_data[4]=0x00;
	else if(Send_data[5]==0xb0)
		Send_data[5]=0x00;	
	else if(Send_data[6]==0xb0)
		Send_data[6]=0x00;		
}
void Deal_Send_Data(void)
{
	U8 i;
	if(b_Record_Mode)
		return;
	if(!Send_data[1])//数组第1位等于0
	{
		Send_data[1]=Send_data[2];
		Send_data[2]=0;
		if(!Send_data[1])//数组第1位等于0，判断数组第2位是不是等于0，等于零会进来
		{
			Send_data[1]=Send_data[3];
			Send_data[3]=0;
		}	
		if(!Send_data[1])//数组第1位等于0，判断数组第3位是不是等于0，等于零会进来
		{
			Send_data[1]=Send_data[4];
			Send_data[4]=0;
		}	
		if(!Send_data[1])//数组第1位等于0，判断数组第4位是不是等于0，等于零会进来
		{
			Send_data[1]=Send_data[5];
			Send_data[5]=0;
		}
		if(!Send_data[1])//数组第1位等于0，判断数组第5位是不是等于0，等于零会进来
		{
			Send_data[1]=Send_data[6];
			Send_data[6]=0;
		}	
	}	
	////////////////////
	if(!Send_data[2])//数组第2位等于0
	{
		Send_data[2]=Send_data[3];
		Send_data[3]=0;
		if(!Send_data[2])//数组第2位等于0，判断数组第3位是不是等于0，等于零会进来
		{
			Send_data[2]=Send_data[4];
			Send_data[4]=0;
		}	
		if(!Send_data[2])//数组第2位等于0，判断数组第4位是不是等于0，等于零会进来
		{
			Send_data[2]=Send_data[5];
			Send_data[5]=0;
		}
		if(!Send_data[2])//数组第2位等于0，判断数组第5位是不是等于0，等于零会进来
		{
			Send_data[2]=Send_data[6];
			Send_data[6]=0;
		}	
	}	
	////////////////////
	if(!Send_data[3])//数组第3位等于0
	{
		Send_data[3]=Send_data[4];
		Send_data[4]=0;
		if(!Send_data[3])//数组第3位等于0，判断数组第4位是不是等于0，等于零会进来
		{
			Send_data[3]=Send_data[5];
			Send_data[5]=0;
		}
		if(!Send_data[3])//数组第3位等于0，判断数组第5位是不是等于0，等于零会进来
		{
			Send_data[3]=Send_data[6];
			Send_data[6]=0;
		}	
	}	
	////////////////////
	if(!Send_data[4])//数组第4位等于0
	{
		Send_data[4]=Send_data[5];
		Send_data[5]=0;
		if(!Send_data[4])//数组第4位等于0，判断数组第5位是不是等于0，等于零会进来
		{
			Send_data[4]=Send_data[6];
			Send_data[6]=0;
		}	
	}	
	////////////////////
	if(!Send_data[5])//数组第5位等于0
	{
		Send_data[5]=Send_data[6];
		Send_data[6]=0;
	}	
	////////////////////
	for(i=1; i<7; i++)
	{
		Last_Send_data[i] =Send_data[i];
	}
}
void IN1_IRQ_Prog_Data(void)
{
	if(bSend_IN2)
	{
		bSend_IN2=0;
		Deal_Send_Data();	
		Deal_FN_Data();
		buffer_addr = IN1_BUFFER_ADDRESS;
		if((!bAll_Key_Lock)&(!b_Record_Mode))
		{	
			buffer_addr[0] =Send_data[0]|Mcaro_Ctrl_Data;
			buffer_addr[1] =0x00;
			buffer_addr[2] =Send_data[1];
			buffer_addr[3] =Send_data[2];
			buffer_addr[4] =Send_data[3];
			buffer_addr[5] =Send_data[4];
			buffer_addr[6] =Send_data[5];
			buffer_addr[7] =Send_data[6];
		}
		else
		{	
			buffer_addr[0] =0x00;
			buffer_addr[1] =0x00;
			buffer_addr[2] =0x00;
			buffer_addr[3] =0x00;
			buffer_addr[4] =0x00;
			buffer_addr[5] =0x00;
			buffer_addr[6] =0x00;
			buffer_addr[7] =0x00;
		}	
		
		/*
		Send_data[0]=Send_data[1]=Send_data[2]=0;
		Send_data[3]=Send_data[4]=Send_data[5]=Send_data[6]=0;
		
		Last_Send_data[0]=Send_data[0];
		Last_Send_data[1]=Send_data[1];
		Last_Send_data[2]=Send_data[2];
		Last_Send_data[3]=Send_data[3];
		Last_Send_data[4]=Send_data[4];
		Last_Send_data[5]=Send_data[5];
		Last_Send_data[6]=Send_data[6];
		*/
		IEP1CNT	= 8;
		IN1_SET_READY;
	}
}
void IN2_IRQ_Prog_Data(void)
{
	U8 i;
	if(b_04)
	{
		b_04=0;
	//	EA = 0;
		buffer_addr = IN2_BUFFER_ADDRESS;
		buffer_addr[0] =6;
	//	buffer_addr[1] =Mcaro_Ctrl_Data;
			
		for(i=1;i<16;i++)
			{
				if((!bAll_Key_Lock)&(!b_Record_Mode))
					buffer_addr[i] =Usb2_Data[i];
				else
					buffer_addr[i] =0;
			}
		IEP2CNT	= 16;
		IN2_SET_READY;
	}
	/*
	else if(b_022)	
	{
		b_022=0;
	//	EA = 0;
		buffer_addr = IN2_BUFFER_ADDRESS;
		buffer_addr[0] =6;
		//buffer_addr[1] =0;
		for(i=1;i<16;i++)
			{
				if((!bAll_Key_Lock)&(!b_Record_Mode)&(!Manual_Record_UNM))
				{	
					buffer_addr[i] =Macro_Usb2_Data2[i];
				}
				else
					buffer_addr[i] =0;
			}
		IEP2CNT	= 16;
		IN2_SET_READY;
	}
	*/
	else if(b_01)	
	{
		b_01=0;
		IEP2CNT = 0x03;
		buffer_addr = IN2_BUFFER_ADDRESS;
		buffer_addr[0] = 02;
		if((!bAll_Key_Lock)&(!b_Record_Mode))
		{	
			buffer_addr[1] = Multimedia_Data[1];
			buffer_addr[2] =Multimedia_Data[0];
		}
		else
		{
			buffer_addr[1] = 0;
			buffer_addr[2] =0;
		}
		IN2_SET_READY;
		//Multimedia_Data[0]=0;
		//Multimedia_Data[1]=0;
	}
	else if(b_02)	
	{
		
		b_02=0;
	//	EA = 0;
		buffer_addr = IN2_BUFFER_ADDRESS;
		buffer_addr[0] =6;
		//buffer_addr[1] =Mcaro_Ctrl_Data;
			
		for(i=1;i<16;i++)
			{
				if((!bAll_Key_Lock)&(!b_Record_Mode))
					buffer_addr[i] =Macro_Usb2_Data[i];
				else
					buffer_addr[i] =0;
			}
		IEP2CNT	= 16;
		IN2_SET_READY;
 		
	}
}


