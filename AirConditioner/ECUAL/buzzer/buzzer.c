/*
 * buzzer.c
 *
 * Created: 4/18/2023 5:39:54 AM
 *  Author: Ahmed Hesham
 */ 
												
#include "buzzer.h"
											/*port_#, pin_#*/
st_buzzer_t buzzerDB [NUMBER_OF_BUZZERS] =	{{PORT_B,	 3}};
	
en_buzzerError_t	BUZZER_init		(u8 u8_a_buzzerNumber)
{
	en_timerError_t error = BUZZER_OK
	if (u8_a_buzzerNumber >= 0 && u8_a_buzzerNumber < NUMBER_OF_BUZZERS)
	{
		DIO_init(buzzerDB[u8_a_buzzerNumber].portNumber, buzzerDB[u8_a_buzzerNumber].pinNumber, OUTPUT);
	}
	else
	{
		error = WRONG_BUZZER;
	}
	
	return error;
}

en_buzzerError_t	BUZZER_on		(u8 u8_a_buzzerNumber)
{
	en_timerError_t error = BUZZER_OK
	if (u8_a_buzzerNumber >= 0 && u8_a_buzzerNumber < NUMBER_OF_BUZZERS)
	{
		DIO_write(buzzerDB[u8_a_buzzerNumber].portNumber, buzzerDB[u8_a_buzzerNumber].pinNumber, HIGH);
	}
	else
	{
		error = WRONG_BUZZER;
	}
	
	return error;
}

en_buzzerError_t	BUZZER_off		(u8 u8_a_buzzerNumber)
{
	en_timerError_t error = BUZZER_OK
	if (u8_a_buzzerNumber >= 0 && u8_a_buzzerNumber < NUMBER_OF_BUZZERS)
	{
		DIO_write(buzzerDB[u8_a_buzzerNumber].portNumber, buzzerDB[u8_a_buzzerNumber].pinNumber, LOW);
	}
	else
	{
		error = WRONG_BUZZER;
	}
	
	return error;
}