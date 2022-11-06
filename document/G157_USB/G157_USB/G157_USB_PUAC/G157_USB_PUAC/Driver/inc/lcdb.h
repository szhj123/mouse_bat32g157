/***********************************************************************************************************************
* Copyright (C) . All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    lcdb.h
* @brief   This file implements device driver for LCD module.
* @version 1.0.0
* @date    2020/10/12
***********************************************************************************************************************/
#ifndef LCDB_H
#define LCDB_H

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/


/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

#define Read_LBCTL_BYF() (LCDB->LBCTL&LCDB_LBCTL_BYF_Msk)
#define Read_LBCTL_TPF() (LCDB->LBCTL&LCDB_LBCTL_TPF_Msk)

#define Write_LBDATA(dat)       while(Read_LBCTL_BYF());\
								LCDB->LBDATA = dat;\
								while(Read_LBCTL_TPF());/* write LBDATA */
								

#define Write_LBDATAL(dat)      while(Read_LBCTL_BYF());\
								LCDB->LBDATAL = dat;\
								while(Read_LBCTL_TPF());/* write LBDATAL */

#define Write_LBDATAL(dat)      while(Read_LBCTL_BYF());\
								LCDB->LBDATAL = dat;\
								while(Read_LBCTL_TPF());/* write LBDATAL */
/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef struct
{
	uint8_t mode;	/* bus mode */
	uint8_t mode_6800_E_level;	/* 6800 bus E level */
	uint8_t clock_div;	/* clock divider */
	uint8_t cycle;	/* bus cycle */
	uint8_t wait_cycle;	/* wait cycle */
}LCDB_Typedef;

#define LCDB_MODE_6800_CNTL_ENABLE_HIGH 0
#define LCDB_MODE_6800_CNTL_ENABLE_LOW 1

#define LCDB_MODE_TYPE_8080 0
#define LCDB_MODE_TYPE_6800 1

#define LCDB_CLOCK_DIV_1 0
#define LCDB_CLOCK_DIV_2 1
#define LCDB_CLOCK_DIV_4 2
#define LCDB_CLOCK_DIV_64 3

#define LDB_CYCLE_2T 2
#define LDB_CYCLE_3T 3
#define LDB_CYCLE_4T 4
#define LDB_CYCLE_5T 5
#define LDB_CYCLE_6T 6
#define LDB_CYCLE_7T 7
#define LDB_CYCLE_8T 8
#define LDB_CYCLE_9T 9
#define LDB_CYCLE_10T 10
#define LDB_CYCLE_11T 11
#define LDB_CYCLE_12T 12
#define LDB_CYCLE_13T 13
#define LDB_CYCLE_14T 14
#define LDB_CYCLE_15T 15
#define LDB_CYCLE_16T 16
#define LDB_CYCLE_17T 17
#define LDB_CYCLE_18T 18
#define LDB_CYCLE_19T 19
#define LDB_CYCLE_20T 20
#define LDB_CYCLE_21T 21
#define LDB_CYCLE_22T 22
#define LDB_CYCLE_23T 23
#define LDB_CYCLE_24T 24
#define LDB_CYCLE_25T 25
#define LDB_CYCLE_26T 26
#define LDB_CYCLE_27T 27
#define LDB_CYCLE_28T 28
#define LDB_CYCLE_29T 29
#define LDB_CYCLE_30T 30
#define LDB_CYCLE_31T 31
#define LDB_CYCLE_32T 32
#define LDB_CYCLE_33T 33
#define LDB_CYCLE_34T 34
#define LDB_CYCLE_35T 35
#define LDB_CYCLE_36T 36
#define LDB_CYCLE_37T 37
#define LDB_CYCLE_38T 38
#define LDB_CYCLE_39T 39
#define LDB_CYCLE_40T 40
#define LDB_CYCLE_41T 41
#define LDB_CYCLE_42T 42
#define LDB_CYCLE_43T 43
#define LDB_CYCLE_44T 44
#define LDB_CYCLE_45T 45
#define LDB_CYCLE_46T 46
#define LDB_CYCLE_47T 47
#define LDB_CYCLE_48T 48
#define LDB_CYCLE_49T 49
#define LDB_CYCLE_50T 50
#define LDB_CYCLE_51T 51
#define LDB_CYCLE_52T 52
#define LDB_CYCLE_53T 53
#define LDB_CYCLE_54T 54
#define LDB_CYCLE_55T 55
#define LDB_CYCLE_56T 56
#define LDB_CYCLE_57T 57
#define LDB_CYCLE_58T 58
#define LDB_CYCLE_59T 59
#define LDB_CYCLE_60T 60
#define LDB_CYCLE_61T 61
#define LDB_CYCLE_62T 62
#define LDB_CYCLE_63T 63

#define LDB_WAIT_CYCLE_0T 0
#define LDB_WAIT_CYCLE_1T 1
#define LDB_WAIT_CYCLE_2T 2
#define LDB_WAIT_CYCLE_3T 3
#define LDB_WAIT_CYCLE_4T 4
#define LDB_WAIT_CYCLE_5T 5
#define LDB_WAIT_CYCLE_6T 6
#define LDB_WAIT_CYCLE_7T 7
#define LDB_WAIT_CYCLE_8T 8
#define LDB_WAIT_CYCLE_9T 9
#define LDB_WAIT_CYCLE_10T 10
#define LDB_WAIT_CYCLE_11T 11
#define LDB_WAIT_CYCLE_12T 12
#define LDB_WAIT_CYCLE_13T 13
#define LDB_WAIT_CYCLE_14T 14
#define LDB_WAIT_CYCLE_15T 15
#define LDB_WAIT_CYCLE_16T 16
#define LDB_WAIT_CYCLE_17T 17
#define LDB_WAIT_CYCLE_18T 18
#define LDB_WAIT_CYCLE_19T 19
#define LDB_WAIT_CYCLE_20T 20
#define LDB_WAIT_CYCLE_21T 21
#define LDB_WAIT_CYCLE_22T 22
#define LDB_WAIT_CYCLE_23T 23
#define LDB_WAIT_CYCLE_24T 24
#define LDB_WAIT_CYCLE_25T 25
#define LDB_WAIT_CYCLE_26T 26
#define LDB_WAIT_CYCLE_27T 27
#define LDB_WAIT_CYCLE_28T 28
#define LDB_WAIT_CYCLE_29T 29
#define LDB_WAIT_CYCLE_30T 30
#define LDB_WAIT_CYCLE_31T 31


/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
void LCDB_Init(LCDB_Typedef* pLcdb);
void LCDB_Start(void);
void LCDB_Stop(void);


/* Start user code for function. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#endif
