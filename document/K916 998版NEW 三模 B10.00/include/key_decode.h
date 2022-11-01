
#ifndef	_KEY_DECODE_H
#define	_KEY_DECODE_H
/////////////////////////normal key decode///////////////////////////////////////////
#define   KEY_A            				0x04
#define   KEY_B            				0x05
#define   KEY_C            				0x06
#define   KEY_D            				0x07
#define   KEY_E           				0x08
#define   KEY_F            				0x09
#define   KEY_G            				0x0a
#define   KEY_H            				0x0b
#define   KEY_I            				0x0c
#define   KEY_J            				0x0d
#define   KEY_K            				0x0e
#define   KEY_L            				0x0f
#define   KEY_M            				0x10
#define   KEY_N            				0x11
#define   KEY_O            				0x12
#define   KEY_P            				0x13
#define   KEY_Q            				0x14
#define   KEY_R            				0x15
#define   KEY_S            				0x16
#define   KEY_T            				0x17
#define   KEY_U            				0x18
#define   KEY_V            				0x19
#define   KEY_W            				0x1a
#define   KEY_X            				0x1b
#define   KEY_Y            				0x1c
#define   KEY_Z            				0x1d

#define   KEY_ESC          				0x29       
#define   KEY_TAB          				0x2b
#define   KEY_CAPSLOCK     				0x39
#define   KEY_Backspace    				0x2a
#define   KEY_ENTER        				0x28
#define   KEY_SPACEBAR     				0x2c

#define   KEY_PRINT		    				0x46
#define   KEY_SCRLOCK       			0x47
#define   KEY_PAUSE         			0x48
#define   KEY_INS           			0x49
#define   KEY_HOME            		0x4a
#define   KEY_PGUP           			0x4b
#define   KEY_DEL           			0x4c
#define   KEY_END              		0x4d
#define   KEY_PGDN         				0x4e

#define   KEY_RightArrow       		0x4f
#define   KEY_LeftArrow        		0x50
#define   KEY_DownArrow        		0x51
#define   KEY_UpArrow          		0x52

#define	  M_Nop		0x7F	//0
#define	  M_Next		0x80	//0
#define	  M_Previous	0x81	//1
#define	  M_Stop		0x82	//2
#define	  M_Play		0x83	//3
#define	  M_Mute		0x84	//4
#define	  M_VUp		0x85	//5
#define	  M_VDn		0x86	//6
#define	  M_Media		0x87	//7
#define	  M_Mail		0x88	//8
#define	  M_Calculator 0x89	//9
#define	  M_Computer	0x8A	//10
#define	  M_Search		0x8B	//11
#define	  M_Home		0x8C	//12
#define	  M_Back		0x8D	//13
#define	  M_Forward	0x8E	//14
#define	  M_Stop		0x8F	//15
#define	  M_Refresh	0x90	//16
#define	  M_Favorites	0x91	//17


#define	C_REST		0XA0	//RESET				(V_Data[5]&0x20)
#define	C_CAP		0XA1	//RESET

#define   H_Mode  	0XC1	//Change_Mode		V_Data[15]&0x02
#define   H_Color  	0XC2	//Change_Color		V_Data[15]&0x04
#define   H_BUp  	0XC3	//Change_Brightness+	V_Data[14]&0x10
#define   H_BDn  	0XC4	//Change_Brightness-	V_Data[14]&0x20
#define   H_SUp  	0XC5	//Change_Speed++		V_Data[15]&0x20
#define   H_SDn  	0XC6	//Change_Speed--		V_Data[13]&0x20
#define   G_WIN  	0XC7	//bWin_Locks			V_Data[1]&0x20
#define   G_IOS_0  	0XC8	//b_IOS_Mode=0		V_Data[1]&0x08
#define   G_IOS_1  	0XC9	//b_IOS_Mode=1		V_Data[2]&0x08

#define   H_S1		0XCA
#define   H_S2		0XCB
#define   H_S3		0XCC
#define   H_Record	0XCD
#define   H_Logo		0XCE









