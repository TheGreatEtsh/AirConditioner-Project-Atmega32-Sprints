/*
 * adc.h
 *
 * Created: 4/18/2023 3:50:34 AM
 *  Author: Ahmed Hesham
 */ 


#ifndef ADC_H_
#define ADC_H_

/****************************************_MACROS_***************************************/
#define F_CPU									16000000UL

#define AREF									2
#define AVCC									3
#define VREF									4

#define LEFT_ADJUST								2
#define RIGHT_ADJUST							3

#define	DIVISION_FACTOR_1						1
#define	DIVISION_FACTOR_2						2
#define	DIVISION_FACTOR_4						3
#define	DIVISION_FACTOR_8						4
#define	DIVISION_FACTOR_16						5
#define	DIVISION_FACTOR_32						6
#define	DIVISION_FACTOR_64						7
#define DIVISION_FACTOR_128						8

#define ADC_INT_ENABLE							0
#define ADC_INT_DISABLE							1

/****************************************_VOLTAGE_REFERENCE_SELECTION_***************************************/
/*
 *	TO CHOOSE SENSE CONTROL MODE FOR INT0
 *		OPTION 1		->		AREF	->	For the usage of AREF Pin
 *		OPTION 2		->		AVCC	->	For	the usage of AVCC Pin, attach external capacitor to AREF Pin
 *		OPTION 3		->		VREF	->	For the usage internal 2.56V Voltage Reference with external capacitor at AREF Pin
 */

#define VOLTAGE_REFERENCE		AVCC

/****************************************_LEFT_ADJUST_RESULT_***************************************/
/*
 *	TO CHOOSE SENSE CONTROL MODE FOR INT0
 *		OPTION 1		->		LEFT_ADJUST
 *		OPTION 2		->		RIGHT_ADJUST
 */

#define LEFT_ADJUST_RESULT		RIGHT_ADJUST

/****************************************_PRESCALER_SELECTION_***************************************/
/*
 *	TO CHOOSE SENSE CONTROL MODE FOR INT0
 *		OPTION 1		->		DIVISION_FACTOR_1
 *		OPTION 2		->		DIVISION_FACTOR_2
 *		OPTION 3		->		DIVISION_FACTOR_4
 *		OPTION 4		->		DIVISION_FACTOR_8
 *		OPTION 5		->		DIVISION_FACTOR_16
 *		OPTION 6		->		DIVISION_FACTOR_32
 *		OPTION 7		->		DIVISION_FACTOR_64
 *		OPTION 8		->		DIVISION_FACTOR_128	
 */

#define PRESCALER_SELECTION		DIVISION_FACTOR_128

/****************************************_INTERRUPT_STATE_***************************************/
/*
 *	TO CHOOSE SENSE CONTROL MODE FOR INT0
 *		OPTION 1		->		ADC_INT_ENABLE 
 *		OPTION 2		->		ADC_INT_DISABLE
 */
#define ADC_INTERRUPT			ADC_INT_DISABLE


/***************************************_INCLUDES_***************************************/
#include "../dio/dio.h"
#include "../registers.h"
#include "../../SERVICE/bit_math.h"


/***************************************_PROTOTYPES_***************************************/

void ADC_init (void);
u16  ADC_read (void);

#endif /* ADC_H_ */