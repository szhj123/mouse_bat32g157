#include "..\include\SH68F90.h"
#include "..\include\stdtype.h"
#include "..\include\mcu_def.h"
#include "..\include\pwm_control.h"
#include ".\include\Auser.h"
#include "..\include\CFG.h"
#include <intrins.h>
#include <string.h>

U8 xdata	NUM_Image[3][126];
U8 xdata Temp_RR;
U8 xdata Temp_GG;
U8 xdata Temp_BB;
code const U8 XuanZhuan_Data1[]={70,49,50,28,29,30,6,7,8,9,};
code const U8 XuanZhuan_Data2[]={69,47,48,25,26,27,3,4,5,};
code const U8 XuanZhuan_Data3[]={68,46,21,22,23,24,0,1,2,};
code const U8 XuanZhuan_Data4[]={66,67,42,43,44,45,46,};
code const U8 XuanZhuan_Data5[]={63,64,65,};
code const U8 XuanZhuan_Data6[]={84,85,105,};
code const U8 XuanZhuan_Data7[]={86,87,106,107,};
code const U8 XuanZhuan_Data8[]={	88,89,90,108,109,110,111,};
code const U8 XuanZhuan_Data9[]={	91,92,112,113,};
code const U8 XuanZhuan_Data10[]={	93,114,115,116,117,118,119,120,121,122,123,124,125,};
code const U8 XuanZhuan_Data11[]={	94,95,96,97,98,99,100,101,102,103,104,};
code const U8 XuanZhuan_Data12[]={	73,74,75,76,77,78,79,80,81,82,83,};
code const U8 XuanZhuan_Data13[]={	72,52,53,54,55,56,57,58,59,60,51,52,};
code const U8 XuanZhuan_Data14[]={	71,51,31,32,33,34,35,36,37,38,39,40,41,10,11,12,13,14,15,16,17,18,19,20,};
//**********************************
code const U8 LiuGuang6_Data1[]={28,29,50,70,69,48,49,};
code const U8 LiuGuang6_Data2[]={5,6,7,8,9,26,27,46,47,67,71,68,88,89,90,91,110,111,30,31,51,52,72,73,92,93,112,113};
code const U8 LiuGuang6_Data3[]={3,4,23,24,25,44,45,65,66,85,86,87,108,109,10,11,12,32,33,34,53,54,55,74,75,76,94,95,96,114,115,116,};
code const U8 LiuGuang6_Data4[]={0,1,2,21,22,42,43,63,64,84,85,105,106,107,13,14,15,16,35,36,37,56,57,58,77,78,79,97,98,99,100,117,118,119,120,121,};
code const U8 LiuGuang6_Data5[]={17,18,19,20,38,39,40,41,59,60,61,62,80,81,82,83,80,81,82,83,101,102,103,104,122,123,124,125,};
//************************************
code const U8 breathe_mode_tab_G[240]=	
{
	0,	1,	2,	3,		4,	5,	6,	7,		8,	9,	10,	12,		//0			
	14,	16,	18,	20,		22,	24,	27,	30,		33,	36,	39,	42,		//12	
	45,	48,	51,	54,		57,	60,	63,	66,		69,	72,	75,	78,		//24
	82,85,	88,	91,		94,	98,	102,106,	110,114,118,122,	//36
	126,130,134,138,	142,146,150,154,	158,162,166,170,	//48		
	174,178,182,186,	190,194,198,202,	206,210,214,218,	//60
	222,226,230,234,	238,242,244,246,	248,250,252,254,	//72
	
	254,252,250,248,	246,244,242,238,	234,230,226,222,	//84
	218,214,210,206,	202,198,194,190,	186,182,178,174,	//96
	170,166,162,158,	154,150,146,142,	138,134,130,126,	//108
	122,118,114,110,	106,102,98,94,	91,88,85,82,		//120	
	78,75,72,69,		66,63,60,57,		54,51,48,45,		//132
	42,	39,	36,	33,		30,	27,	24,	22,		20,	18,	16,	14,		//144
	12,	10,	9,	8,		7,	6,	5,	4,		3,	2,	1,	0,		//156
	
	0,0,0,0,		0,0,0,0,		0,0,0,0,//168
	0,0,0,0,		0,0,0,0,		0,0,0,0,//192
	0,0,0,0,		0,0,0,0,		0,0,0,0,//204
	0,0,0,0,		0,0,0,0,		0,0,0,0,//216
	0,0,0,0,		0,0,0,0,		0,0,0,0,//228
	0,0,0,0,		0,0,0,0,		0,0,0,0,//240
	
};
U8 JianbianSub2(U8 LedStage2)
{
	switch(LedStage2)
		{
			case 0:	
				Temp_RR=0;
				Temp_GG++;
				Temp_BB = 0;
				if(Temp_GG >254)
				{	
					LedStage2++;
				}
			break;
			//--------------------------------
			case 1:
				Temp_RR++;
				Temp_GG--;
				Temp_BB=0;
				if(Temp_GG==0)
					LedStage2++;
			break;
			case 2:
				Temp_GG=0;
				Temp_RR--;
				Temp_BB++;
				if(Temp_RR == 0)
					LedStage2++;
			break;		
			case 3:
				Temp_RR=0;
				Temp_GG++;
				Temp_BB--;
				if(Temp_BB == 0)
					LedStage2=1;
			break;	
		} 
	return 	LedStage2;
}
//**********************************
void Int_Mode6_Data(void)
{
	U8 i,j;
	U16 randtmp;
	for(i=0; i<126; i++)
	{
		NUM_Image[0][i]=NUM_Image[1][i]=NUM_Image[2][i]=0;
	}
	if(b_LiuGuang_Mode2|b_LiuGuang_Mode3|b_LiuGuang_Mode4|b_LiuGuang_Mode6|b_LiuGuang_Mode5|b_LiuGuang_Mode7)
	{	
		if(Color_Times==1)
		{
			R_Color=255;
			G_Color=B_Color=0;
		}	
		else if(Color_Times==2)
		{
			G_Color=R_Color=255;
			B_Color=0;
		}
		else if(Color_Times==3)
		{
			G_Color=255;
			B_Color=R_Color=0;
		}
		else if(Color_Times==4)
		{
			B_Color=255;
			G_Color=R_Color=0;
		}
		else if(Color_Times==5)
		{
			G_Color=B_Color=255;
			R_Color=0;
		}
		else if(Color_Times==6)
		{
			R_Color=B_Color=255;
			G_Color=0;
		}
		else if(Color_Times==7)
		{
			G_Color=R_Color=B_Color=255;
		}
	}
	if(b_LiuGuang_Mode2)	//6
	{
			for(i=0; i<6; i++)
			{
			NUM_Image[R][20+i*21]=0;	NUM_Image[G][20+i*21]=84;	NUM_Image[B][20+i*21]=168;	                  
			NUM_Image[R][19+i*21]=12;	NUM_Image[G][19+i*21]=96;	NUM_Image[B][19+i*21]=180;	
			NUM_Image[R][18+i*21]=24;	NUM_Image[G][18+i*21]=108;NUM_Image[B][18+i*21]=192;	
			NUM_Image[R][17+i*21]=36;	NUM_Image[G][17+i*21]=120;NUM_Image[B][17+i*21]=204;   
			NUM_Image[R][16+i*21]=48;	NUM_Image[G][16+i*21]=132;NUM_Image[B][16+i*21]=216;   
			NUM_Image[R][15+i*21]=60;	NUM_Image[G][15+i*21]=144;NUM_Image[B][15+i*21]=228;   
			NUM_Image[R][14+i*21]=72;	NUM_Image[G][14+i*21]=156;NUM_Image[B][14+i*21]=240;   
                                                                                
			NUM_Image[R][13+i*21]=84;	NUM_Image[G][13+i*21]=168;NUM_Image[B][13+i*21]=0;	
			NUM_Image[R][12+i*21]=96;	NUM_Image[G][12+i*21]=180;NUM_Image[B][12+i*21]=12;	
			NUM_Image[R][11+i*21]=108;	NUM_Image[G][11+i*21]=192;NUM_Image[B][11+i*21]=24;		
			NUM_Image[R][10+i*21]=120;	NUM_Image[G][10+i*21]=204;NUM_Image[B][10+i*21]=36;  
			NUM_Image[R][9+i*21]=132;	NUM_Image[G][9+i*21]=216;	NUM_Image[B][9+i*21]=48;   
			NUM_Image[R][8+i*21]=144;	NUM_Image[G][8+i*21]=228;	NUM_Image[B][8+i*21]=60;   
			NUM_Image[R][7+i*21]=156;	NUM_Image[G][7+i*21]=240;	NUM_Image[B][7+i*21]=72;   
			                             			                 			                                   
			NUM_Image[R][6+i*21]=168;	NUM_Image[G][6+i*21]=0;	NUM_Image[B][6+i*21]=84;	
			NUM_Image[R][5+i*21]=180;	NUM_Image[G][5+i*21]=12;	NUM_Image[B][5+i*21]=96;	
			NUM_Image[R][4+i*21]=192;	NUM_Image[G][4+i*21]=24;	NUM_Image[B][4+i*21]=108;	
			NUM_Image[R][3+i*21]=204;	NUM_Image[G][3+i*21]=36;	NUM_Image[B][3+i*21]=120;   
			NUM_Image[R][2+i*21]=216;	NUM_Image[G][2+i*21]=48;	NUM_Image[B][2+i*21]=132;   
			NUM_Image[R][1+i*21]=228;	NUM_Image[G][1+i*21]=60;	NUM_Image[B][1+i*21]=144;   
			NUM_Image[R][0+i*21]=240;	NUM_Image[G][0+i*21]=72;	NUM_Image[B][0+i*21]=156;   
			}
	}	
	else if(b_LiuGuang_Mode3)//彩虹轮盘  没有颜色调整
	{
		for(i=0; i<sizeof(XuanZhuan_Data1); i++)
		{
			NUM_Image[R][XuanZhuan_Data1[i]]=0;
			NUM_Image[G][XuanZhuan_Data1[i]]=84;
			NUM_Image[B][XuanZhuan_Data1[i]]=168;
		}
		for(i=0; i<sizeof(XuanZhuan_Data2); i++)
		{
			NUM_Image[R][XuanZhuan_Data2[i]]=17;
			NUM_Image[G][XuanZhuan_Data2[i]]=101;
			NUM_Image[B][XuanZhuan_Data2[i]]=185;
		}	
		for(i=0; i<sizeof(XuanZhuan_Data3); i++)
		{
			NUM_Image[R][XuanZhuan_Data3[i]]=34;
			NUM_Image[G][XuanZhuan_Data3[i]]=51;
			NUM_Image[B][XuanZhuan_Data3[i]]=202;
		}	
		for(i=0; i<sizeof(XuanZhuan_Data4); i++)
		{
			NUM_Image[R][XuanZhuan_Data4[i]]=51;
			NUM_Image[G][XuanZhuan_Data4[i]]=135;
			NUM_Image[B][XuanZhuan_Data4[i]]=219;
		}
		for(i=0; i<sizeof(XuanZhuan_Data5); i++)
		{	
			NUM_Image[R][XuanZhuan_Data5[i]]=68;
			NUM_Image[G][XuanZhuan_Data5[i]]=152;
			NUM_Image[B][XuanZhuan_Data5[i]]=236;
		}
		for(i=0; i<sizeof(XuanZhuan_Data6); i++)
		{
			NUM_Image[R][XuanZhuan_Data6[i]]=85;
			NUM_Image[G][XuanZhuan_Data6[i]]=169;
			NUM_Image[B][XuanZhuan_Data6[i]]=13;
		}
		for(i=0; i<sizeof(XuanZhuan_Data7); i++)
		{
			NUM_Image[R][XuanZhuan_Data7[i]]=102;
			NUM_Image[G][XuanZhuan_Data7[i]]=186;
			NUM_Image[B][XuanZhuan_Data7[i]]=30;
		}
		for(i=0; i<sizeof(XuanZhuan_Data8); i++)
		{	
			NUM_Image[R][XuanZhuan_Data8[i]]=119;
			NUM_Image[G][XuanZhuan_Data8[i]]=203;
			NUM_Image[B][XuanZhuan_Data8[i]]=47;
		}
		for(i=0; i<sizeof(XuanZhuan_Data9); i++)
		{
			NUM_Image[R][XuanZhuan_Data9[i]]=136;
			NUM_Image[G][XuanZhuan_Data9[i]]=220;
			NUM_Image[B][XuanZhuan_Data9[i]]=64;
		}
		for(i=0; i<sizeof(XuanZhuan_Data10); i++)
		{
			NUM_Image[R][XuanZhuan_Data10[i]]=153;
			NUM_Image[G][XuanZhuan_Data10[i]]=237;
			NUM_Image[B][XuanZhuan_Data10[i]]=81;
		}	
		for(i=0; i<sizeof(XuanZhuan_Data11); i++)
		{
			NUM_Image[R][XuanZhuan_Data11[i]]=170;
			NUM_Image[G][XuanZhuan_Data11[i]]=14;
			NUM_Image[B][XuanZhuan_Data11[i]]=98;
		}	
		for(i=0; i<sizeof(XuanZhuan_Data12); i++)
		{
			NUM_Image[R][XuanZhuan_Data12[i]]=187;
			NUM_Image[G][XuanZhuan_Data12[i]]=31;
			NUM_Image[B][XuanZhuan_Data12[i]]=115;
		}	
		for(i=0; i<sizeof(XuanZhuan_Data13); i++)
		{
			NUM_Image[R][XuanZhuan_Data13[i]]=204;
			NUM_Image[G][XuanZhuan_Data13[i]]=48;
			NUM_Image[B][XuanZhuan_Data13[i]]=132;
		}	
		for(i=0; i<sizeof(XuanZhuan_Data14); i++)
		{
			NUM_Image[R][XuanZhuan_Data14[i]]=221;
			NUM_Image[G][XuanZhuan_Data14[i]]=65;
			NUM_Image[B][XuanZhuan_Data14[i]]=149;
		}	
	}	
	else if(b_LiuGuang_Mode4)	
	{
		for(i=0; i<21; i++)
		{
			NUM_Image[R][105+i]=0;		          
			NUM_Image[R][84+i]=14;	
			NUM_Image[R][63+i]=28;	
			NUM_Image[R][42+i]=32;	
			NUM_Image[R][21+i]=46;	
			NUM_Image[R][0+i]=60;	
				
			NUM_Image[G][105+i]=74;		          
			NUM_Image[G][84+i]=88;	
			NUM_Image[G][63+i]=102;	
			NUM_Image[G][42+i]=116;	
			NUM_Image[G][21+i]=130;	
			NUM_Image[G][0+i]=144;	
			
			NUM_Image[B][105+i]=158;		          
			NUM_Image[B][84+i]=172;	
			NUM_Image[B][63+i]=186;	
			NUM_Image[B][42+i]=200;	
			NUM_Image[B][21+i]=214;	
			NUM_Image[B][0+i]=228;	
		}
	}	
	else if(b_LiuGuang_Mode6)
	{
		for(i=0; i<sizeof(LiuGuang6_Data5); i++)
		{
			NUM_Image[B][LiuGuang6_Data5[i]]=72;
			NUM_Image[G][LiuGuang6_Data5[i]]=156;
			NUM_Image[R][LiuGuang6_Data5[i]]=240;
		}
		for(i=0; i<sizeof(LiuGuang6_Data4); i++)
		{
			NUM_Image[B][LiuGuang6_Data4[i]]=96;
			NUM_Image[G][LiuGuang6_Data4[i]]=192;
			NUM_Image[R][LiuGuang6_Data4[i]]=12;
		}	
		for(i=0; i<sizeof(LiuGuang6_Data3); i++)
		{
			NUM_Image[B][LiuGuang6_Data3[i]]=120;
			NUM_Image[G][LiuGuang6_Data3[i]]=216;
			NUM_Image[R][LiuGuang6_Data3[i]]=36;
		}	
		for(i=0; i<sizeof(LiuGuang6_Data2); i++)
		{
			NUM_Image[B][LiuGuang6_Data2[i]]=144;
			NUM_Image[G][LiuGuang6_Data2[i]]=228;
			NUM_Image[R][LiuGuang6_Data2[i]]=60;
		}
		for(i=0; i<sizeof(LiuGuang6_Data1); i++)
		{	
			NUM_Image[B][LiuGuang6_Data1[i]]=168;
			NUM_Image[G][LiuGuang6_Data1[i]]=0;
			NUM_Image[R][LiuGuang6_Data1[i]]=84;
		}
	}	
	else if(b_LiuGuang_Mode5)//两层流动
	{
		for(i=0; i<6; i++)
		{
			if(i&0x01)
			{
			NUM_Image[R][20+i*21]=0;	NUM_Image[G][20+i*21]=84;	NUM_Image[B][20+i*21]=168;	                  
			NUM_Image[R][19+i*21]=12;	NUM_Image[G][19+i*21]=96;	NUM_Image[B][19+i*21]=180;	
			NUM_Image[R][18+i*21]=24;	NUM_Image[G][18+i*21]=108;NUM_Image[B][18+i*21]=192;	
			NUM_Image[R][17+i*21]=36;	NUM_Image[G][17+i*21]=120;NUM_Image[B][17+i*21]=204;   
			NUM_Image[R][16+i*21]=48;	NUM_Image[G][16+i*21]=132;NUM_Image[B][16+i*21]=216;   
			NUM_Image[R][15+i*21]=60;	NUM_Image[G][15+i*21]=144;NUM_Image[B][15+i*21]=228;   
			NUM_Image[R][14+i*21]=72;	NUM_Image[G][14+i*21]=156;NUM_Image[B][14+i*21]=240;   
                                                                                
			NUM_Image[R][13+i*21]=84;	NUM_Image[G][13+i*21]=168;NUM_Image[B][13+i*21]=0;	
			NUM_Image[R][12+i*21]=96;	NUM_Image[G][12+i*21]=180;NUM_Image[B][12+i*21]=12;	
			NUM_Image[R][11+i*21]=108;	NUM_Image[G][11+i*21]=192;NUM_Image[B][11+i*21]=24;		
			NUM_Image[R][10+i*21]=120;	NUM_Image[G][10+i*21]=204;NUM_Image[B][10+i*21]=36;  
			NUM_Image[R][9+i*21]=132;	NUM_Image[G][9+i*21]=216;	NUM_Image[B][9+i*21]=48;   
			NUM_Image[R][8+i*21]=144;	NUM_Image[G][8+i*21]=228;	NUM_Image[B][8+i*21]=60;   
			NUM_Image[R][7+i*21]=156;	NUM_Image[G][7+i*21]=240;	NUM_Image[B][7+i*21]=72;   
			                             			                 			                                   
			NUM_Image[R][6+i*21]=168;	NUM_Image[G][6+i*21]=0;	NUM_Image[B][6+i*21]=84;	
			NUM_Image[R][5+i*21]=180;	NUM_Image[G][5+i*21]=12;	NUM_Image[B][5+i*21]=96;	
			NUM_Image[R][4+i*21]=192;	NUM_Image[G][4+i*21]=24;	NUM_Image[B][4+i*21]=108;	
			NUM_Image[R][3+i*21]=204;	NUM_Image[G][3+i*21]=36;	NUM_Image[B][3+i*21]=120;   
			NUM_Image[R][2+i*21]=216;	NUM_Image[G][2+i*21]=48;	NUM_Image[B][2+i*21]=132;   
			NUM_Image[R][1+i*21]=228;	NUM_Image[G][1+i*21]=60;	NUM_Image[B][1+i*21]=144;   
			NUM_Image[R][0+i*21]=240;	NUM_Image[G][0+i*21]=72;	NUM_Image[B][0+i*21]=156;   
			}
			else
			{
			NUM_Image[R][0+i*21]=0;		NUM_Image[G][0+i*21]=84;	NUM_Image[B][0+i*21]=168;	                  
			NUM_Image[R][1+i*21]=12;	NUM_Image[G][1+i*21]=96;	NUM_Image[B][1+i*21]=180;	
			NUM_Image[R][2+i*21]=24;	NUM_Image[G][2+i*21]=108;NUM_Image[B][2+i*21]=192;	
			NUM_Image[R][3+i*21]=36;	NUM_Image[G][3+i*21]=120;NUM_Image[B][3+i*21]=204;   
			NUM_Image[R][4+i*21]=48;	NUM_Image[G][4+i*21]=132;NUM_Image[B][4+i*21]=216;   
			NUM_Image[R][5+i*21]=60;	NUM_Image[G][5+i*21]=144;NUM_Image[B][5+i*21]=228;   
			NUM_Image[R][6+i*21]=72;	NUM_Image[G][6+i*21]=156;NUM_Image[B][6+i*21]=240;   
                                                                                
			NUM_Image[R][7+i*21]=84;	NUM_Image[G][7+i*21]=168;NUM_Image[B][7+i*21]=0;	
			NUM_Image[R][8+i*21]=96;	NUM_Image[G][8+i*21]=180;NUM_Image[B][8+i*21]=12;	
			NUM_Image[R][9+i*21]=108;	NUM_Image[G][9+i*21]=192;NUM_Image[B][9+i*21]=24;		
			NUM_Image[R][10+i*21]=120;	NUM_Image[G][10+i*21]=204;NUM_Image[B][10+i*21]=36;  
			NUM_Image[R][11+i*21]=132;	NUM_Image[G][11+i*21]=216;	NUM_Image[B][11+i*21]=48;   
			NUM_Image[R][12+i*21]=144;	NUM_Image[G][12+i*21]=228;	NUM_Image[B][12+i*21]=60;   
			NUM_Image[R][13+i*21]=156;	NUM_Image[G][13+i*21]=240;	NUM_Image[B][13+i*21]=72;   
			                             			                 			                                   
			NUM_Image[R][14+i*21]=168;	NUM_Image[G][14+i*21]=0;	NUM_Image[B][14+i*21]=84;	
			NUM_Image[R][15+i*21]=180;	NUM_Image[G][15+i*21]=12;	NUM_Image[B][15+i*21]=96;	
			NUM_Image[R][16+i*21]=192;	NUM_Image[G][16+i*21]=24;	NUM_Image[B][16+i*21]=108;	
			NUM_Image[R][17+i*21]=204;	NUM_Image[G][17+i*21]=36;	NUM_Image[B][17+i*21]=120;   
			NUM_Image[R][18+i*21]=216;	NUM_Image[G][18+i*21]=48;	NUM_Image[B][18+i*21]=132;   
			NUM_Image[R][19+i*21]=228;	NUM_Image[G][19+i*21]=60;	NUM_Image[B][19+i*21]=144;   
			NUM_Image[R][20+i*21]=240;	NUM_Image[G][20+i*21]=72;	NUM_Image[B][20+i*21]=156;   
			}
		}	
	}
	else if(b_LiuGuang_Mode7)//随机霓虹
	{
		for(i=0; i<126; i++)
		{
			randtmp=RandSub(j);
			randtmp=randtmp%240;	
			NUM_Image[R][i]=240-randtmp;
			NUM_Image[G][i]=240-randtmp+84;
			NUM_Image[B][i]=240-randtmp+168;
		}
	}	
}
void Start_Mode6_Led(void)
{
	U8 i,j,n,y,k;
	if(b_LiuGuang_Mode)	//霓虹
	{
		Temp_Speed++;
		if(Temp_Speed<Speed_Data)
			return;
		Temp_Speed=0;
			NUM_Image[0][0]=JianbianSub2(NUM_Image[0][0]);
			NUM_Image[0][0]=JianbianSub2(NUM_Image[0][0]);
			NUM_Image[0][0]=JianbianSub2(NUM_Image[0][0]);
			for(i=0; i<126; i++)
			{
				if(Brack_b(i))
				{	
					Image[0][i]=Temp_RR*Brightness_Wheels/5*4+PWM_AddData(0,i);
					Image[1][i]=Temp_GG*Brightness_Wheels/5*4+PWM_AddData(1,i);
					Image[2][i]=Temp_BB*Brightness_Wheels/5*4+PWM_AddData(2,i);
				}
			}
	}
	else if(b_LiuGuang_Mode2|b_LiuGuang_Mode3|b_LiuGuang_Mode4|b_LiuGuang_Mode6|b_LiuGuang_Mode5|b_LiuGuang_Mode7)//彩虹轮盘
	{
		Temp_Speed++;
		if(Temp_Speed<Speed_Data)
			return;
		Temp_Speed=0;
		if(Color_Times==8)
		{	
			for(i=0; i<126; i++)
			{
				if(Brack_b(i))
				{	
				Image[0][i]=breathe_mode_tab_G[NUM_Image[0][i]]*Brightness_Wheels/5*4+PWM_AddData(0,i);
				Image[1][i]=breathe_mode_tab_G[NUM_Image[1][i]]*Brightness_Wheels/5*4+PWM_AddData(1,i);
				Image[2][i]=breathe_mode_tab_G[NUM_Image[2][i]]*Brightness_Wheels/5*4+PWM_AddData(2,i);
				}
				NUM_Image[0][i]++;
				if(NUM_Image[0][i]>239)
					NUM_Image[0][i]=0;
					
					NUM_Image[1][i]++;
				if(NUM_Image[1][i]>239)
					NUM_Image[1][i]=0;
					
					NUM_Image[2][i]++;
				if(NUM_Image[2][i]>239)
					NUM_Image[2][i]=0;
					
				NUM_Image[0][i]++;
				if(NUM_Image[0][i]>239)
					NUM_Image[0][i]=0;
					
					NUM_Image[1][i]++;
				if(NUM_Image[1][i]>239)
					NUM_Image[1][i]=0;
					
					NUM_Image[2][i]++;
				if(NUM_Image[2][i]>239)
					NUM_Image[2][i]=0;	
					
			}
		}
		else
		{	
			for(i=0; i<126; i++)
			{
				if(Brack_b(i))
				{	
				Image[0][i]=R_Color*breathe_mode_tab_G[NUM_Image[0][i]]/255*Brightness_Wheels/5*4+PWM_AddData(0,i);
				Image[1][i]=G_Color*breathe_mode_tab_G[NUM_Image[0][i]]/255*Brightness_Wheels/5*4+PWM_AddData(1,i);
				Image[2][i]=B_Color*breathe_mode_tab_G[NUM_Image[0][i]]/255*Brightness_Wheels/5*4+PWM_AddData(2,i);
				}
				NUM_Image[0][i]++;
				if(NUM_Image[0][i]>239)
					NUM_Image[0][i]=0;
					
				NUM_Image[0][i]++;
				if(NUM_Image[0][i]>239)
					NUM_Image[0][i]=0;
			}
		}
	}	
}
//*************huxi*********************
code const U8 breathe_mode_tab3[128+20]=
{
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,		1,		2,		3,		4,		5,		6,		7,
	8,		9,		10,		12,		14,		16,		18,		20,
	22,		24,		27,		30,		33,		36,		39,		42,
	45,		49,		53,		57,		61,		65,		69,		73,
	77,		81,		85,		89,		94,		99,		104,	109,
	114,	119,	124,	129,	134,	140,	146,	152,
	158,	164,	170,	176,	182,	188,	194,	200,
	206,	213,	220,	227,	234,	241,	248,	255,
	
 	255,	248,	241,	234,	227,	220,	213,	206,
	200,	194,	188,	182,	176,	170,	164,	158,
	152,	146,	140,	134,	129,	124,	119,	114,
	109,	104,	99,		94,		89,		85,		81,		77,
	73,		69,		65,		61,		57,		53,		49,		45,
	42,		39,		36,		33,		30,		27,		24,		22,
	20,		18,		16,		14,		12,		10,		9,		8,
	7,		6,		5,		4,		3,		2,		1,		0,	
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
};
void Start_PWM_Led(void)//呼吸模式
{
	U8 i,j,n;
	U16 y;
	if(!b_HuXi_Mode)
		return;
	//----------------------------------	
	//------------------------------------			
	Temp_Speed++;
	if(Temp_Speed>Speed_Data+1)
	{
		Temp_Speed=0;	
		
		j=breathe_mode_tab3[Run_Time];
		y=j*Brightness_Wheels;
		Run_Time++;
		if(Run_Time>147)
		Run_Time=0;	
		for(i=0; i<126; i++)
		{
			if(Color_Times==0)
			{
				if(Brack_b(i))
				{	
				Image[0][i]=R_Color*j/255*Brightness_Wheels+PWM_AddData(0,i);
				Image[1][i]=G_Color*j/255*Brightness_Wheels+PWM_AddData(1,i);
				Image[2][i]=B_Color*j/255*Brightness_Wheels+PWM_AddData(2,i);	
				}
			}	
			else if(Color_Times==8)
			{
				Image[0][i]=PWM_AddData(0,i);
				Image[1][i]=PWM_AddData(1,i);
				Image[2][i]=PWM_AddData(2,i);
				n=i%5;
				if(Brack_b(i))
				{
					if(n==0)
							Image[0][i]=y+PWM_AddData(0,i);
					else if(n==1)
							Image[1][i]=y+PWM_AddData(0,i);
					else if(n==2)
							Image[2][i]=y+PWM_AddData(0,i);
					else if(n==3)
					{	
						Image[0][i]=y+PWM_AddData(0,i);
						Image[1][i]=y+PWM_AddData(1,i);
					}
					else if(n==4)
					{	
						Image[2][i]=y+PWM_AddData(2,i);
						Image[1][i]=y+PWM_AddData(1,i);;
					}
					else if(n==5)
					{	
						Image[2][i]=y+PWM_AddData(2,i);
						Image[0][i]=y+PWM_AddData(0,i);
					}
				}		
			}
			else
			{	
				if(Brack_b(i))
				Give_NUM_Image(i,Color_Times,j);
			}
		}
	}	
}
//******************************
//*****Logo***FN+Ins	测光	流光，呼吸，常亮，灭
U8 xdata	Logo_Mode_Times;
U8 xdata	Logo_Delay_Times;
U8 xdata Logo_Image[8];
U8 xdata Run_Logo_Image[8];
void Int_Logo_Data(void)
{
	U8 i;
	for(i=0; i<8; i++)
	{
		Logo_Image[i]=Run_Logo_Image[i]=0;
	}
	if(Logo_Mode_Times==0)
	{
		Run_Logo_Image[7]=0;
		Run_Logo_Image[6]=12;
		Run_Logo_Image[5]=24;
		Run_Logo_Image[4]=36;
		Run_Logo_Image[3]=48;
		Run_Logo_Image[2]=60;
		Run_Logo_Image[1]=72;
		Run_Logo_Image[0]=84;
	}
	else if(Logo_Mode_Times==2)
	{
		for(i=0; i<8; i++)
		{
			Logo_Image[i]=250;
		}
	}
}
void Display_Logo_Data(void)
{
	U8 i;
	if(Logo_Mode_Times==0)
	{
		Logo_Delay_Times++;
		if(Logo_Delay_Times<2)
			return;
		Logo_Delay_Times=0;
		for(i=0; i<8; i++)
		{
			Logo_Image[i]=breathe_mode_tab_G[Run_Logo_Image[i]];
			Run_Logo_Image[i]++;
			if(Run_Logo_Image[i]>239)
			Run_Logo_Image[i]=0;
		}
	}
	else if(Logo_Mode_Times==1)
	{
		Logo_Delay_Times++;
		if(Logo_Delay_Times<3)
			return;
		Logo_Delay_Times=0;
		for(i=0; i<8; i++)
		{
			Logo_Image[i]=breathe_mode_tab3[Run_Logo_Image[0]];
		}
		Run_Logo_Image[0]++;
		if(Run_Logo_Image[0]>147)
		Run_Logo_Image[0]=0;
		
	}	
	//----------------------------------------------------
		Image[0][108]=Logo_Image[0]*4+PWM_AddData(0,108);
		Image[1][108]=Logo_Image[0]*4+PWM_AddData(1,108);
		Image[2][108]=Logo_Image[0]*4+PWM_AddData(2,108);
	
		Image[0][109]=Logo_Image[1]*4+PWM_AddData(0,109);
		Image[1][109]=Logo_Image[1]*4+PWM_AddData(1,109);
		Image[2][109]=Logo_Image[1]*4+PWM_AddData(2,109);
	
		Image[0][111]=Logo_Image[2]*4+PWM_AddData(0,111);
		Image[1][111]=Logo_Image[2]*4+PWM_AddData(1,111);
		Image[2][111]=Logo_Image[2]*4+PWM_AddData(2,111);
	
		Image[0][112]=Logo_Image[3]*4+PWM_AddData(0,112);
		Image[1][112]=Logo_Image[3]*4+PWM_AddData(1,112);
		Image[2][112]=Logo_Image[3]*4+PWM_AddData(2,112);
	
		Image[0][116]=Logo_Image[4]*4+PWM_AddData(0,116);
		Image[1][116]=Logo_Image[4]*4+PWM_AddData(1,116);
		Image[2][116]=Logo_Image[4]*4+PWM_AddData(2,116);
	
		Image[0][117]=Logo_Image[5]*4+PWM_AddData(0,117);
		Image[1][117]=Logo_Image[5]*4+PWM_AddData(1,117);
		Image[2][117]=Logo_Image[5]*4+PWM_AddData(2,117);
	
		Image[0][123]=Logo_Image[6]*4+PWM_AddData(0,123);
		Image[1][123]=Logo_Image[6]*4+PWM_AddData(1,123);
		Image[2][123]=Logo_Image[6]*4+PWM_AddData(2,123);
	
		Image[0][125]=Logo_Image[7]*4+PWM_AddData(0,125);
		Image[1][125]=Logo_Image[7]*4+PWM_AddData(1,125);
		Image[2][125]=Logo_Image[7]*4+PWM_AddData(2,125);
	
}










