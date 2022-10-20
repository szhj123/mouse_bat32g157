#define  __KEYTBL_C__

#include "Keytbl.h"
#include "Main.h"

const U8 u8MouseKeyTable[MouseTableSize] =
{
	/*VK_NULL*/0x00,/*No Press*/
	/*VK_LBUTTON*/0x01,/*Left mouse button*/
	/*VK_RBUTTON*/0x02,/*Right mouse button*/
	/*VK_CANCEL*/0x03,/*Control-break processing*/
	/*VK_MBUTTON*/0x04,/*Middle mouse button on a three-button mouse*/
	/*VK_XBUTTON1*/0x05,/*Windows 2000/XP: X1 mouse button*/
	/*VK_XBUTTON2*/0x06,/*Windows 2000/XP: X2 mouse button*/
	0x07,/*Undefined*/ 
	/*VK_BACK*/0x08,/*BACKSPACE key*/
	/*VK_TAB*/0x09,/*TAB key*/
	0x0A,/*Reserved*/
	0x0B,/*Reserved*/
	/*VK_CLEAR*/0x0C,/*CLEAR key*/
	/*VK_RETURN*/0x0D,/*ENTER key*/
	0x0E,/*Reserved*/
	0x0F,/*Reserved*/
	/*VK_SHIFT*/0x10,/*SHIFT key*/
	/*VK_CONTROL*/0x11,/*CTRL key*/
	/*VK_MENU*/0x12,/*ALT key*/
	/*VK_PAUSE*/0x13,/*PAUSE key*/
	/*VK_CAPITAL*/0x14,/*CAPS LOCK key*/
	/*VK_KANA*/0x15,/*Input Method Editor (IME) Kana mode*/
	0x16,/*Undefined*/
	/*VK_JUNJA*/0x17,/*IME Junja mode*/ 
	/*VK_FINAL*/0x18,/*IME final mode*/
	/*VK_HANJA*/0x19,/*IME Hanja mode*/
	0x1A,/*Undefined*/			
	/*VK_ESCAPE*/0x1B,/*ESC key*/
	/*VK_CONVERT*/0x1C,/*IME convert*/
	/*VK_NONCONVERT*/0x1D,/*IME nonconvert*/
	/*VK_ACCEPT*/0x1E,/*IME accept*/
	/*VK_MODECHANGE*/0x1F,/*IME mode change request*/
	/*VK_SPACE*/0x20,/*SPACEBAR*/
	/*VK_PRIOR*/0x21,/*PAGE UP key*/
	/*VK_NEXT*/0x22,/*PAGE DOWN key*/
	/*VK_END*/0x23,/*END key*/
	/*VK_HOME*/0x24,/*HOME key*/
	/*VK_LEFT*/0x25,/*LEFT ARROW key*/
	/*VK_UP*/0x26,/*UP ARROW key*/
	/*VK_RIGHT*/0x27,/*RIGHT ARROW key*/
	/*VK_DOWN*/0x28,/*DOWN ARROW key*/
	/*VK_SELECT*/0x29,/*SELECT key*/
	/*VK_PRINT*/0x2A,/*PRINT key*/ 
	/*VK_EXECUTE*/0x2B,/*EXECUTE key*/
	/*VK_SNAPSHOT*/0x2C,/*PRINT SCREEN key*/
	/*VK_INSERT*/0x2D,/*INS key*/
	/*VK_DELETE*/0x2E,/*DEL key*/
	/*VK_HELP*/0x2F,/*HELP key*/
	0x30,/*0 key*/
	0x31,/*1 key*/
	0x32,/*2 key*/
	0x33,/*3 key*/
	0x34,/*4 key*/
	0x35,/*5 key*/
	0x36,/*6 key*/
	0x37,/*7 key*/
	0x38,/*8 key*/
	0x39,/*9 key*/
	0x3A,/*Undefined*/
	0x3B,/*Undefined*/
	0x3C,/*Undefined*/
	0x3D,/*Undefined*/
	0x3E,/*Undefined*/
	0x3F,/*Undefined*/
	0x40,/*Undefined*/
	0x41,/*A key*/
	0x42,/*B key*/
	0x43,/*C key*/
	0x44,/*D key*/
	0x45,/*E key*/
	0x46,/*F key*/
	0x47,/*G key*/
	0x48,/*H key*/
	0x49,/*I key*/
	0x4A,/*J key*/
	0x4B,/*K key*/
	0x4C,/*L key*/
	0x4D,/*M key*/
	0x4E,/*N key*/
	0x4F,/*O key*/
	0x50,/*P key*/
	0x51,/*Q key*/
	0x52,/*R key*/
	0x53,/*S key*/
	0x54,/*T key*/
	0x55,/*U key*/
	0x56,/*V key*/
	0x57,/*W key*/
	0x58,/*X key*/
	0x59,/*Y key*/
	0x5A,/*Z key*/			
	/*VK_LWIN*/0x5B,/*Left Windows key on a Microsoft Natural Keyboard*/
	/*VK_RWIN*/0x5C,/*Right Windows key on a Microsoft Natural Keyboard*/
	/*VK_APPS*/0x5D,/*Applications key on a Microsoft Natural Keyboard*/
	0x5E,/*Undefined*/
	/*VK_SLEEP*/0x5F,/*Computer Sleep key*/		
	/*VK_NUMPAD0*/0x60,/*Numeric keypad 0 key*/
	/*VK_NUMPAD1*/0x61,/*Numeric keypad 1 key*/
	/*VK_NUMPAD2*/0x62,/*Numeric keypad 2 key*/
	/*VK_NUMPAD3*/0x63,/*Numeric keypad 3 key*/
	/*VK_NUMPAD4*/0x64,/*Numeric keypad 4 key*/
	/*VK_NUMPAD5*/0x65,/*Numeric keypad 5 key*/
	/*VK_NUMPAD6*/0x66,/*Numeric keypad 6 key*/
	/*VK_NUMPAD7*/0x67,/*Numeric keypad 7 key*/
	/*VK_NUMPAD8*/0x68,/*Numeric keypad 8 key*/
	/*VK_NUMPAD9*/0x69,/*Numeric keypad 9 key*/
	/*VK_MULTIPLY*/0x6A,/*Multiply key*/
	/*VK_ADD*/0x6B,/*Add key*/
	/*VK_SEPARATOR*/0x6C,/*Separator key*/
	/*VK_SUBTRACT*/0x6D,/*Subtract key*/
	/*VK_DECIMAL*/0x6E,/*Decimal key*/
	/*VK_DIVIDE*/0x6F,/*Divide key*/
	/*VK_F1*/0x70,/*F1 key*/
	/*VK_F2*/0x71,/*F2 key*/
	/*VK_F3*/0x72,/*F3 key*/
	/*VK_F4*/0x73,/*F4 key*/
	/*VK_F5*/0x74,/*F5 key*/
	/*VK_F6*/0x75,/*F6 key*/
	/*VK_F7*/0x76,/*F7 key*/
	/*VK_F8*/0x77,/*F8 key*/
	/*VK_F9*/0x78,/*F9 key*/
	/*VK_F10*/0x79,/*F10 key*/
	/*VK_F11*/0x7A,/*F11 key*/
	/*VK_F12*/0x7B,/*F12 key*/
	/*VK_F13*/0x7C,/*F13 key*/
	/*VK_F14*/0x7D,/*F14 key*/
	/*VK_F15*/0x7E,/*F15 key*/
	/*VK_F16*/0x7F,/*F16 key*/
	/*VK_F17*/0x80,/*F17 key*/
	/*VK_F18*/0x81,/*F18 key*/
	/*VK_F19*/0x82,/*F19 key*/
	/*VK_F20*/0x83,/*F20 key*/
	/*VK_F21*/0x84,/*F21 key*/
	/*VK_F22*/0x85,/*F22 key*/
	/*VK_F23*/0x86,/*F23 key*/
	/*VK_F24*/0x87,/*F24 key*/
	0x88,/*Unassigned*/
	0x89,/*Unassigned*/
	0x8A,/*Unassigned*/
	0x8B,/*Unassigned*/
	0x8C,/*Unassigned*/
	0x8D,/*Unassigned*/
	0x8E,/*Unassigned*/
	0x8F,/*Unassigned*/
	/*VK_NUMLOCK*/0x90,/*NUM LOCK key*/
	/*VK_SCROLL*/0x91,/*SCROLL LOCK key*/
	0x92,/*OEM specific*/
	0x93,/*OEM specific*/
	0x94,/*OEM specific*/
	0x95,/*OEM specific*/
	0x96,/*OEM specific*/
	0x97,/*Unassigned*/		
	0x98,/*Unassigned*/		
	0x99,/*Unassigned*/		
	0x9A,/*Unassigned*/		
	0x9B,/*Unassigned*/		
	0x9C,/*Unassigned*/		
	0x9D,/*Unassigned*/		
	0x9E,/*Unassigned*/		
	0x9F,/*Unassigned*/		
	/*VK_LSHIFT*/0xA0,/*Left SHIFT*/
	/*VK_RSHIFT */0xA1,/*Right SHIFT*/
	/*VK_LCONTROL*/0xA2,/*Left CTRL*/
	/*VK_RCONTROL*/0xA3,/*Right CTRL*/
	/*VK_LMENU*/0xA4,/*Left ALT*/
	/*VK_RMENU*/0xA5,/*Right ALT*/
	/*VK_BROWSER_BACK*/0xA6,/*Windows 2000/XP: Browser Back key*/
	/*VK_BROWSER_FORWARD*/0xA7,/*Windows 2000/XP: Browser Forward key*/
	/*VK_BROWSER_REFRESH*/0xA8,/*Windows 2000/XP: Browser Refresh key*/
	/*VK_BROWSER_STOP*/0xA9,/*Windows 2000/XP: Browser Stop key*/
	/*VK_BROWSER_SEARCH*/0xAA,/*Windows 2000/XP: Browser Search key*/
	/*VK_BROWSER_FAVORITES*/0xAB,/*Windows 2000/XP: Browser Favorites key*/
	/*VK_BROWSER_HOME*/0xAC,/*Windows 2000/XP: Browser Start and Home key*/
	/*VK_VOLUME_MUTE*/0xAD,/*Windows 2000/XP: Volume Mute key*/
	/*VK_VOLUME_DOWN*/0xAE,/*Windows 2000/XP: Volume Down key*/
	/*VK_VOLUME_UP*/0xAF,/*Windows 2000/XP: Volume Up key*/
	/*VK_MEDIA_NEXT_TRACK*/0xB0,/*Windows 2000/XP: Next Track key*/
	/*VK_MEDIA_PREV_TRACK*/0xB1,/*Windows 2000/XP: Previous Track key*/
	/*VK_MEDIA_STOP*/0xB2,/*Windows 2000/XP: Stop Media key*/
	/*VK_MEDIA_PLAY_PAUSE*/0xB3,/*Windows 2000/XP: Play/Pause Media key*/
	/*VK_LAUNCH_MAIL*/0xB4,/*Windows 2000/XP: Start Mail key*/
	/*VK_LAUNCH_MEDIA_SELECT*/0xB5,/*Windows 2000/XP: Select Media key*/
	/*VK_LAUNCH_APP1*/0xB6,/*Windows 2000/XP: Start Application 1 key*/
	/*VK_LAUNCH_APP2*/0xB7,/*Windows 2000/XP: Start Application 2 key*/
	0xB8,/*Reserved*/
	0xB9,/*Reserved*/
	/*VK_OEM_1*/0xBA,/*Used for miscellaneous characters; it can vary by keyboard.Windows 2000/XP: For the US standard keyboard, the ';:' key*/
	/*VK_OEM_PLUS*/0xBB,/*Windows 2000/XP: For any country/region, the '+' key*/
	/*VK_OEM_COMMA*/0xBC,/*Windows 2000/XP: For any country/region, the ',' key*/
	/*VK_OEM_MINUS*/0xBD,/*Windows 2000/XP: For any country/region, the '-' key*/	
	/*VK_OEM_PERIOD*/0xBE,/*Windows 2000/XP: For any country/region, the '.' key*/
	/*VK_OEM_2*/0xBF,/*Used for miscellaneous characters; it can vary by keyboard.Windows 2000/XP: For the US standard keyboard, the '/?' key*/
	/*VK_OEM_3*/0xC0,/*Used for miscellaneous characters; it can vary by keyboard.*/
	0xC1,/*Reserved*/
	0xC2,/*Reserved*/
	0xC3,/*Reserved*/
	0xC4,/*Reserved*/
	0xC5,/*Reserved*/
	0xC6,/*Reserved*/
	0xC7,/*Reserved*/
	0xC8,/*Reserved*/
	0xC9,/*Reserved*/
	0xCA,/*Reserved*/
	0xCB,/*Reserved*/
	0xCC,/*Reserved*/
	0xCD,/*Reserved*/
	0xCE,/*Reserved*/
	0xCF,/*Reserved*/
	0xD1,/*Reserved*/
	0xD2,/*Reserved*/
	0xD3,/*Reserved*/
	0xD4,/*Reserved*/
	0xD5,/*Reserved*/
	0xD6,/*Reserved*/
	0xD7,/*Reserved*/
	0xD8,/*Unassigned*/
	0xD9,/*Unassigned*/
	0xDA,/*Unassigned*/
	/*VK_OEM_4*/0xDB,/*Used for miscellaneous characters; it can vary by keyboard.Windows 2000/XP: For the US standard keyboard, the '[{' key*/	
	/*VK_OEM_5*/0xDC,/*Used for miscellaneous characters; it can vary by keyboard.*/
	/*VK_OEM_6*/0xDD,/*Used for miscellaneous characters; it can vary by keyboard.Windows 2000/XP: For the US standard keyboard, the ']}' key*/
	/*VK_OEM_7*/0xDE,/*Used for miscellaneous characters; it can vary by keyboard.Windows 2000/XP: For the US standard keyboard, the 'single-quote/doublequote'key*/
	/*VK_OEM_8*/0xDF,/*Used for miscellaneous characters; it can vary by keyboard.*/
	0xE0,/*Reserved*/
	0xE1,/*OEM specific*/
	/*VK_OEM_102*/0xE2,/*Windows 2000/XP: Either the angle bracket key or the backslash key on the	RT 102-key keyboard*/
	0xE3,/*OEM specific*/
	0xE4,/*OEM specific*/
	/*VK_PROCESSKEY*/0xE5,/*Windows 95/98/Me, Windows NT 4.0, Windows 2000/XP: IME PROCESS key*/
	0xE6,/*OEM specific*/
	/*VK_PACKET*/0xE7,/*Windows 2000/XP: Used to pass Unicode characters as if they were keystrokes. The VK_PACKET key is the low word of a 32-bit Virtual Key value used for non-keyboard input methods. For more information, see Remark in KEYBDINPUT, SendInput, WM_KEYDOWN, and WM_KEYUP*/
	0xE8,/*Unassigned*/
	0xE9,/*OEM specific*/
	0xEA,/*OEM specific*/
	0xEB,/*OEM specific*/
	0xEC,/*OEM specific*/
	0xED,/*OEM specific*/
	0xEE,/*OEM specific*/
	0xEF,/*OEM specific*/
	0xF0,/*OEM specific*/
	0xF1,/*OEM specific*/
	0xF2,/*OEM specific*/
	0xF3,/*OEM specific*/
	0xF4,/*OEM specific*/
	0xF5,/*OEM specific*/	
	/*VK_ATTN*/0xF6,/*ATTN key*/
	/*VK_CRSEL*/0xF7,/*CRSEL key*/
	/*VK_EXSEL*/0xF8,/*EXSEL key*/
	/*VK_EREOF*/0xF9,/*Erase EOF key*/
	/*VK_PLAY*/0xFA,/*PLAY key*/
	/*VK_ZOOM*/0xFB,/*ZOOM key*/
	/*VK_NONAME*/0xFC,/*Reserved for future use*/
	/*VK_PA1*/0xFD,/*PA1 key*/
	/*VK_OEM_CLEAR*/0xFE,/*CLEAR key*/		
};


const U8 u8KeyboardKeyTable[KeyboardTableYSize][KeyboardTableXSize ] =
{
	/*System Power:ACPI*/{0x07,0x00,0x01},	
	/*System Sleep:ACPI*/	{0x07,0x00,0x02},	
	/*System Wake:ACPI*/{0x07,0x00,0x04},								
	/*No Event	Normal:key*/{0x00,0x00,0x00},	
	/*Overrun Error:Normal key*/{0x00,0x00,0x01},
	/*POST Fail:Normal key*/{0x00,0x00,0x02},
	/*ErrorUndefined:Normal key*/{0x00,0x00,0x03},
	/*a A:Normal key*/{0x00,0x00,0x04},
	/*b B:Normal key*/{0x00,0x00,0x05},	
	/*c C:Normal key*/{0x00,0x00,0x06},	
	/*d D:Normal key*/{0x00,0x00,0x07},	
	/*e E:Normal key*/{0x00,0x00,0x08},	
	/*f F:Normal key*/{0x00,0x00,0x09},	
	/*g G:Normal key*/{0x00,0x00,0x0A},	
	/*h H:Normal key*/{0x00,0x00,0x0B},	
	/*i I:Normal key*/{0x00,0x00,0x0C},	
	/*j J:Normal key*/{0x00,0x00,0x0D},	
	/*k K:Normal key*/{0x00,0x00,0x0E},	
	/*l L:Normal key*/ {0x00,0x00,0x0F},	
	/*m M:Normal key*/{0x00,0x00,0x10},	
	/*n N:Normal key*/{0x00,0x00,0x11},	
	/*o O:Normal key*/{0x00,0x00,0x12},	
	/*p P:Normal key*/{0x00,0x00,0x13},	
	/*q Q:Normal key*/{0x00,0x00,0x14},
	/*r R:Normal key*/{0x00,0x00,0x15},	
	/*s S:Normal key*/{0x00,0x00,0x16},	
	/*t T:Normal key*/{0x00,0x00,0x17},	
	/*u U:Normal key*/{0x00,0x00,0x18},	
	/*v V:Normal key*/{0x00,0x00,0x19},	
	/*w W:Normal key*/{0x00,0x00,0x1A},	
	/*x X:Normal key*/{0x00,0x00,0x1B},	
	/*y Y:Normal key*/{0x00,0x00,0x1C},	
	/*z Z:Normal key*/{0x00,0x00,0x1D},	
	/*1 !:Normal key*/{0x00,0x00,0x1E},	
	/*2 @:Normal key*/{0x00,0x00,0x1F},	
	/*3 #:Normal key*/{0x00,0x00,0x20},	
	/*4 $:Normal key*/{0x00,0x00,0x21},	
	/*5 %:Normal key*/{0x00,0x00,0x22},	
	/*6 ^:Normal key*/{0x00,0x00,0x23},	
	/*7 &:Normal key*/{0x00,0x00,0x24},	
	/*8 *:Normal key*/{0x00,0x00,0x25},	
	/*9 ( :Normal key*/{0x00,0x00,0x26},	
	/*0 ):Normal key*/{0x00,0x00,0x27},	
	/*Return:Normal key*/{0x00,0x00,0x28},	
	/*Escape:Normal key*/	{0x00,0x00,0x29},	
	/*Backspace:Normal key*/{0x00,0x00,0x2A},	
	/*Tab:Normal key*/{0x00,0x00,0x2B},	
	/*Space:Normal key*/{0x00,0x00,0x2C},	
	/*- _ :Normal key*/{0x00,0x00,0x2D},
	/*= +:Normal key*/{0x00,0x00,0x2E},	
	/*[ {:Normal key*/{0x0,0x00,0x2F},	
	/*] }:Normal key*/{0x00,0x00,0x30},	
	/*\ |:Normal key*/{0x00,0x00,0x31},	
	/*Europe 1(Note 2):Normal key*/{0x00,0x00,0x32},	
	/*;::Normal key*/{0x00,0x00,0x33},	
	/*' ": Normal key*/{0x00,0x00,0x34},	
	/*` ~:Normal key*/{0x00,0x00,0x35},	
	/*, <:Normal key*/{0x00,0x00,0x36},	
	/*. >:Normal key*/{0x00,0x00,0x37},	
	/*/ ?:Normal key*/{0x00,0x00,0x38},	
	/*Caps Lock:Normal key*/{0x00,0x00,0x39},	
	/*F1:Normal key*/{0x00,0x00,0x3A},	
	/*F2:Normal key*/{0x00,0x00,0x3B},	
	/*F3:Normal key*/{0x00,0x00,0x3C},	
	/*F4:Normal key*/{0x00,0x00,0x3D},	
	/*F5:Normal key*/{0x00,0x00,0x3E},	
	/*F6:Normal key*/{0x00,0x00,0x3F},	
	/*F7:Normal key*/{0x00,0x00,0x40},	
	/*F8:Normal key*/{0x00,0x00,0x41},	
	/*F9:Normal key*/{0x00,0x00,0x42},	
	/*F10:Normal key*/{0x00,0x00,0x43},	
	/*F11:Normal key*/{0x00,0x00,0x44},	
	/*F12:Normal key*/{0x00,0x00,0x45},	
	/*Print Screen (Note 1):Normal key*/{0x00,0x00,0x46},	
	/*Scroll Lock:Normal key*/{0x00,0x00,0x47},	
	/*Break (Ctrl-Pause):Normal key*/{0x00,0x00,0x48},	
	/*Pause:Normal key*/{0x00,0x00,0x48},	
	/*Insert (Note 1):Normal key*/{0x00,0x00,0x49},	
	/*Home (Note 1):Normal key*/{0x00,0x00,0x4A},	
	/*Page Up (Note 1):Normal key*/{0x00,0x00,0x4B},	
	/*Delete (Note 1):Normal key*/{0x00,0x00,0x4C},	
	/*End (Note 1):Normal key*/{0x00,0x00,0x4D},	
	/*Page Down (Note 1):Normal key*/{0x00,0x00,0x4E},	
	/*Right Arrow (Note 1):Normal key*/{0x00,0x00,0x4F},	
	/*Left Arrow (Note 1) Normal key*/{0x00,0x00,0x50},
	/*Down Arrow (Note 1):Normal key*/{0x00,0x00,0x51},	
	/*Up Arrow (Note 1):	Normal key*/{0x00,0x00,0x52},	
	/*Num Lock:Normal key*/{0x00,0x00,0x53},	
	/*Keypad /(Note 1):Normal key*/{0x00,0x00,0x54},	
	/*Keypad *:Normal key	*/{0x00,0x00,0x55},	
	/*Keypad -	:Normal key*/{0x00,0x00,0x56},	
	/*Keypad +	:Normal key*/{0x00,0x00,0x57},	
	/*Keypad Enter:	Normal key*/{0x00,0x00,0x58},
	/*Keypad 1 End:Normal key*/{0x00,0x00,0x59},	
	/*Keypad 2 Down:Normal key*/{0x00,0x00,0x5A},
	/*Keypad 3 PageDn:Normal key*/{0x00,0x00,0x5B},	
	/*Keypad 4 Left:Normal key*/{0x00,0x00,0x5C},
	/*Keypad 5:Normal key*/{0x00,0x00,0x5D},
	/*Keypad 6 Right:Normal key*/{0x00,0x00,0x5E},	
	/*Keypad 7 Home:Normal key*/{0x00,0x00,0x5F},	
	/*Keypad 8 Up:Normal key*/	{0x00,0x00,0x60},	
	/*Keypad 9 PageUp:Normal key*/{0x00,0x00,0x61},	
	/*Keypad 0 Insert:Normal key*/{0x00,0x00,0x62},	
	/*Keypad . Delete:Normal key*/{0x00,0x00,0x63},
	/*Europe 2 (Note 2):Normal key*/{0x00,0x00,0x64},	
	/*App:Normal key*/{0x00,0x00,0x65},	
	/*Keyboard Power:Normal key*/{0x00,0x00,0x66},	
	/*Keypad:ormal key*/{0x00,0x00,0x67},
	/*F13:Normal key*/{0x00,0x00,0x68},	
	/*F14:Normal key*/{0x00,0x00,0x69},
	/*F15:Normal key*/{0x00,0x00,0x6A},
	/*F16:Normal key*/{0x00,0x00,0x6B},	
	/*F17:Normal key*/{0x00,0x00,0x6C},
	/*F18:Normal key*/{0x00,0x00,0x6D},	
	/*F19:Normal key*/{0x00,0x00,0x6E},
	/*F20:Normal key*/{0x00,0x00,0x6F},
	/*F21:Normal key*/{0x00,0x00,0x70},
	/*F22:Normal key*/{0x00,0x00,0x71},
	/*F23:Normal key*/{0x00,0x00,0x72},
	/*F24:Normal key*/{0x00,0x00,0x73},	
	/*Keypad,(Brazilian Keypad)Normal key*/{0x00,0x00,0x85},	
	/*Keyboard Int'l 1(Ro)Normal key*/{0x00,0x00,0x87},	
	/*Keyboard Intl'2(Katakana/Hiragana)Normal key*/{0x00,0x00,0x88},	
	/*Keyboard Int'l 2(Yen)Normal key*/{0x00,0x00,0x89},		
	/*Keyboard Int'l 4(Henkan)Normal key*/{0x00,0x00,0x8A},	
	/*Keyboard Int'l 5(Muhenkan)Normal key*/{0x00,0x00,0x8B},	
	/*Keyboard Lang 1(Hanguel/English)Normal key*/{0x00,0x00,0x90},	
	/*Left Control Normal key*/{0x00,0x00,0xE0},	
	/*Left Shift Normal key*/{	0x00,0x00,0xE1},
	/*Left Alt	Normal key*/{0x00,0x00,0xE2},
	/*Left GUI	Normal key*/{0x00,0x00,0xE3},
	/*Right Control	Normal key*/{0x00,0x00,0xE4},
	/*Right Shift Normal key*/{0x00,0x00,0xE5},
	/*Right Alt Normal key*/{0x00,0x00,0xE6},
	/*Right GUI Normal key*/{0x00,0x00,0xE7},
	/*Mouse L Button Normal Key*/{0x00,0x00,0xF0},
	/*Mouse R Button Normal Key*/{0x00,0x00,0xF1},	
	/*Mouse M Button Normal Key*/{0x00,0x00,0xF2},	
	/*Mouse RB0 Button Normal Key*/{0x00,0x00,0xF3},
	/*Mouse RB1 Button	Normal Key*/{0x00,0x00,0xF4},
	/*Mouse LTilt Button	Normal Key*/{0x00,0x00,0xF5},	
	/*Mouse RTilt Button Normal Key*/{0x00,0x00,0xF6},								
	/*Scan Next Track:Multi-media key*/{ 0x04,0x00,0xB5},
	/*Scan Previous Track:Multi-media key*/{0x04,0x00,0xB6},
	/*Stop:Multi-media key*/{0x04,0x00,0xB7},
	/*Play/Pause:Multi-media key*/{0x04,0x00,0xCD},
	/*Mute:Multi-media key*/ {	0x04,0x00,0xE2},
	/*Volume Up:Multi-media key*/ {0x04,0x00,0xE9},
	/*Volume Down:Multi-media key*/{0x04,0x00,0xEA},
	/*Media Select:Multi-media key*/ {0x04,0x01,0x83},
	/*Mail:Multi-media key*/{0x04,0x01,0x8A},
	/*Calculator:Multi-media key*/{0x04,0x01,0x92},
	/*My Computer:Multi-media key*/{0x04,0x01,0x94},
	/*WWW Search:Multi-media key*/{0x04,0x02,0x21},
	/*WWW Home:Multi-media key*/{0x04,0x02,0x23},
	/*WWW Back:Multi-media key*/{0x04,0x02,0x24},
	/*WWW Forward:Multi-media key*/{0x04,0x02,0x25},
	/*WWW Stop:Multi-media key*/{0x04,0x02,0x26},
	/*WWW Refresh:Multi-media key*/ {0x04,0x02,0x27},
	/*WWW Favorites:Multi-media key*/{0x04,0x02,0x2A},
};

