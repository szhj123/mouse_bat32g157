/********************************************************
* @file       hal_lcd.c
* @author     szhj13
* @version    V1.0
* @date       2022-05-18
* @brief      the start address of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "hal_lcd.h"

/* Private typedef --------------------------------------*/
/* Private define ---------------------------------------*/
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
/* Private variables ------------------------------------*/
LCDB_Typedef Lcdb;

void Hal_Lcd_Init(void )
{
    //pa02, output, lcd reset
    PORT_Init(PORTA, PIN2, OUTPUT);
    //pa10, output, lcd cs
    PORT_Init(PORTA, PIN10, OUTPUT);
    //pd00, output, lcd RS
    PORT_Init(PORTD, PIN0, OUTPUT);

    Lcdb.mode = LCDB_MODE_TYPE_8080;	/* 8080 Mode */
	Lcdb.clock_div = LCDB_CLOCK_DIV_1;	/* 1 divider */
	Lcdb.cycle = LDB_CYCLE_8T;//LDB_CYCLE_6T;	/* 6T cycles */
	Lcdb.wait_cycle = LDB_WAIT_CYCLE_2T;	/* 2T wait cycles */

    LCDB_Init(&Lcdb);
}

/***********************************************************************************************************************
* Function Name: LCDB_Init
* @brief  This function initializes the LCDB module.
* @param  pinMsk - 
* @return None
***********************************************************************************************************************/
void LCDB_Init(LCDB_Typedef* pLcdb)
{
    CGC->PER1 |= CGC_PER1_LCDBEN_Msk;	/*enable lcdb clock*/
	
	if(LCDB_MODE_TYPE_8080 == pLcdb->mode)
	{
		LCDB->LBCTL &= ~LCDB_LBCTL_IMD_Msk;
	}
	else
	{
		LCDB->LBCTL |= LCDB_LBCTL_IMD_Msk;
		if(LCDB_MODE_6800_CNTL_ENABLE_HIGH == pLcdb->mode_6800_E_level)
		{
			LCDB->LBCTL &= ~LCDB_LBCTL_EL_Msk;
		}
		else
		{
			LCDB->LBCTL |= LCDB_LBCTL_EL_Msk;
		}
	}
	
	LCDB->LBCTL &= ~LCDB_LBCTL_LBC_Msk;//lcdb clock divider
	LCDB->LBCTL |= (pLcdb->clock_div)<<LCDB_LBCTL_LBC_Pos;
	
	LCDB->LBCYC = pLcdb->cycle;
	
	LCDB->LBWST = pLcdb->wait_cycle;
	
    /* Set LCDB pin */
	PORT->PC &= ~0xF3C0;//PC6-9 PC12-15
	PORT->PC |= 0x0C00;//PC10-11
	
    PORT->PMCC &= ~(0x3FF<<6);//PC6-15 digital function
    PORT->PMC &= ~0x0C00;//PC10-11 output mode
	PORT->PMC |= 0xF3C0;//PC6-9 PC12-15 input mode
	
    INTC_DisableIRQ(LCDB_IRQn);      /* disable LCDB interrupt */
    INTC_ClearPendingIRQ(LCDB_IRQn); /* clear LCDB interrupt flag */
}

/***********************************************************************************************************************
* Function Name: LCDB_Start
* @brief  This function clears LCDB interrupt flag and enables interrupt.
* @param  None
* @return None
***********************************************************************************************************************/
void LCDB_Start(void)
{
    INTC_ClearPendingIRQ(LCDB_IRQn); /* clear LCDB interrupt flag */
    INTC_EnableIRQ(LCDB_IRQn);/* enable LCDB interrupt */
}

/***********************************************************************************************************************
* Function Name: LCDB_Stop
* @brief  This function disables LCDB interrupt and clears interrupt flag.
* @param  None
* @return None
***********************************************************************************************************************/
void LCDB_Stop(void)
{
    INTC_DisableIRQ(LCDB_IRQn);      /* disable LCDB interrupt */
    INTC_ClearPendingIRQ(LCDB_IRQn); /* clear LCDB interrupt flag */
}



