/*
 * adc.c
 *
 * Created: 4/18/2023 3:50:49 AM
 *  Author: Ahmed Hesham
 */ 

#include "Adc.h"


/******************************************************************************
* \Syntax          : void ADC_init (void)
* \Description     : Initialize ADC according to preprocessed configured definitions.
* \Sync\Async      : Synchronous
* \Reentrancy      : Reentrant
* \Parameters (in) : None
* \Parameters (out): None
* \Return value:   : None
*******************************************************************************/
void ADC_init (void)
{
	
	DIO_init(PORT_A, 0, INPUT);
	/* Step 1	->		Set Voltage Reference  */
	#if			VOLTAGE_REFERENCE		==		AREF
	CLR_BIT(ADMUX,REF0);
	CLR_BIT(ADMUX,REF1);
	#elif		VOLTAGE_REFERENCE		==		AVCC
	SET_BIT(ADMUX,REF0);
	CLR_BIT(ADMUX,REF1);
	#elif		VOLTAGE_REFERENCE		==		VREF
	SET_BIT(ADMUX,REF0);
	SET_BIT(ADMUX,REF1);
	#endif
	
	/* Step 2	->		Set Left Adjust Result  */
	#if			LEFT_ADJUST_RESULT		==		RIGHT_ADJUST
	CLR_BIT(ADMUX,ADLAR);
	#elif		LEFT_ADJUST_RESULT		==		LEFT_ADJUST
	SET_BIT(ADMUX,ADLAR);
	#endif
	
	/* Step 3	->		Set Pin Used  */
	CLR_BIT(ADMUX,MUX4); CLR_BIT(ADMUX,MUX3); CLR_BIT(ADMUX,MUX2); CLR_BIT(ADMUX,MUX1); CLR_BIT(ADMUX,MUX0);
	
	/* Step 4	->		Set ADC Prescaler Selection */
	#if			PRESCALER_SELECTION		==		DIVISION_FACTOR_1
	CLR_BIT(ADCSRA,ADPS2); CLR_BIT(ADCSRA,ADPS1);	CLR_BIT(ADCSRA,ADPS0);
	
	#elif		PRESCALER_SELECTION		==		DIVISION_FACTOR_2
	CLR_BIT(ADCSRA,ADPS2); CLR_BIT(ADCSRA,ADPS1);	SET_BIT(ADCSRA,ADPS0);
	
	#elif		PRESCALER_SELECTION		==		DIVISION_FACTOR_4
	CLR_BIT(ADCSRA,ADPS2); SET_BIT(ADCSRA,ADPS1);	CLR_BIT(ADCSRA,ADPS0);
	
	#elif		PRESCALER_SELECTION		==		DIVISION_FACTOR_8
	CLR_BIT(ADCSRA,ADPS2); SET_BIT(ADCSRA,ADPS1);	SET_BIT(ADCSRA,ADPS0);

	#elif		PRESCALER_SELECTION		==		DIVISION_FACTOR_16
	SET_BIT(ADCSRA,ADPS2); CLR_BIT(ADCSRA,ADPS1);	CLR_BIT(ADCSRA,ADPS0);
	
	#elif		PRESCALER_SELECTION		==		DIVISION_FACTOR_32
	SET_BIT(ADCSRA,ADPS2); CLR_BIT(ADCSRA,ADPS1);	SET_BIT(ADCSRA,ADPS0);
	
	#elif		PRESCALER_SELECTION		==		DIVISION_FACTOR_64
	SET_BIT(ADCSRA,ADPS2); SET_BIT(ADCSRA,ADPS1);	CLR_BIT(ADCSRA,ADPS0);

	#elif		PRESCALER_SELECTION		==		DIVISION_FACTOR_128
	SET_BIT(ADCSRA,ADPS2); SET_BIT(ADCSRA,ADPS1);	SET_BIT(ADCSRA,ADPS0);
	#endif



	/* Step 5	->		set ADC Enable */
	SET_BIT(ADCSRA,ADEN);
	
	SET_BIT(ADCSRA,ADATE);
		
}

/******************************************************************************
* \Syntax          : void ADC_read (void)
* \Description     : Pulls on ADC interrupt flag till it rises 
*					 to start returning a conversion to the user
* \Sync\Async      : Synchronous
* \Reentrancy      : Reentrant
* \Parameters (in) : None
* \Parameters (out): None
* \Return value:   : u16		Value of the conversion 
*******************************************************************************/
u16 ADC_read(void)
{
	u16 u16_a_data = 0;
	
	SET_BIT(ADCSRA,ADSC);
	
	while(GET_BIT(ADCSRA,ADIF) == 0);
	
	u16_a_data = (ADCL + (ADCH<<8));
	
	return u16_a_data;
}
