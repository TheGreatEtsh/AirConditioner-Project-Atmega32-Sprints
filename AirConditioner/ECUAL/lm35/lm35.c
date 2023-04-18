/*
 * lm35.c
 *
 * Created: 4/18/2023 3:45:11 AM
 *  Author: Ahmed Hesham
 */ 
#include "Lm35.h"

void LM35_init				(void)
{
	ADC_init();
}
u16  LM35_read				(void)
{
	u16 u16_a_Reading		=	ADC_read();
	u16 u16_a_temp			=	(((u32) u16_a_Reading * 500)/1023);
	return u16_a_temp;
}