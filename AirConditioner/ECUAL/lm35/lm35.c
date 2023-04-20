/*
 * lm35.c
 *
 * Created: 4/18/2023 3:45:11 AM
 *  Author: Ahmed Hesham
 */ 
#include "Lm35.h"


/******************************************************************************
* \Syntax          : void LM35_init	(void)
* \Description     : Initialize LM35 according to preprocessed configured definitions.
* \Sync\Async      : Synchronous
* \Reentrancy      : Reentrant
* \Parameters (in) : None
* \Parameters (out): None
* \Return value:   : None
*******************************************************************************/
void LM35_init				(void)
{
	ADC_init();
}


/******************************************************************************
* \Syntax          : void LM35_read (void)
* \Description     : returns Degree Celsius after Conversion
* \Sync\Async      : Synchronous
* \Reentrancy      : Reentrant
* \Parameters (in) : None
* \Parameters (out): None
* \Return value:   : u16		Temperature read after conversion
*******************************************************************************/
u16  LM35_read				(void)
{
	u16 u16_a_Reading		=	ADC_read();
	u16 u16_a_temp			=	(((u32) u16_a_Reading * 500)/1023);
	return u16_a_temp;
}