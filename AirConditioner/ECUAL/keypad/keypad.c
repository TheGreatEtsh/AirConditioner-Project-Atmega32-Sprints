/*
 * keypad.c
 *
 * Created: 4/18/2023 4:39:06 AM
 *  Author: Ahmed Hesham
 */ 

#include "KeyPad.h"


void KEYPAD_init				(void)
{
	DIO_init(KEYPAD_R0_PORT,KEYPAD_R0_PIN,OUTPUT);
	DIO_init(KEYPAD_R1_PORT,KEYPAD_R1_PIN,OUTPUT);
	DIO_init(KEYPAD_R2_PORT,KEYPAD_R2_PIN,OUTPUT);
	
	
	DIO_write(KEYPAD_R0_PORT,KEYPAD_R0_PIN,HIGH);
	DIO_write(KEYPAD_R1_PORT,KEYPAD_R1_PIN,HIGH);
	DIO_write(KEYPAD_R2_PORT,KEYPAD_R2_PIN,HIGH);
	
	DIO_init(KEYPAD_C0_PORT,KEYPAD_C0_PIN,INPUT);
	DIO_init(KEYPAD_C1_PORT,KEYPAD_C1_PIN,INPUT);
	DIO_init(KEYPAD_C2_PORT,KEYPAD_C2_PIN,INPUT);
	
	DIO_pinPullUp(KEYPAD_C0_PORT,KEYPAD_C0_PIN,PULLUP_ENABLE);
	DIO_pinPullUp(KEYPAD_C1_PORT,KEYPAD_C1_PIN,PULLUP_ENABLE);
	DIO_pinPullUp(KEYPAD_C2_PORT,KEYPAD_C2_PIN,PULLUP_ENABLE);
	
}


u8	 H_KeyPad_Read				(void)
{
	u8 u8_a_keypadReading		=	0, u8_a_pinState = 0;
	
	u8 u8_arr_a_keypadArr [3][3]	={	{'1','2','3'},
										{'4','5','6'},
										{'7','8','9'} };
	
	DIO_write(KEYPAD_R0_PORT,KEYPAD_R0_PIN,LOW);
	
	DIO_read(KEYPAD_C0_PORT, KEYPAD_C0_PIN, &u8_a_pinState); 
	if(u8_a_pinState== 0) 
	{ 
		TIMER_delay(TIMER_2, 70);
		DIO_read(KEYPAD_C0_PORT, KEYPAD_C0_PIN, &u8_a_pinState);
		if(u8_a_pinState == 0) 
		{
			while(u8_a_pinState == 0)
			DIO_read(KEYPAD_C0_PORT, KEYPAD_C0_PIN, &u8_a_pinState); 
			DIO_write(KEYPAD_R0_PORT,KEYPAD_R0_PIN,HIGH);
			u8_a_keypadReading = u8_arr_a_keypadArr [0][0];
		}
	}
	
	DIO_read(KEYPAD_C1_PORT, KEYPAD_C1_PIN, &u8_a_pinState);
	if(u8_a_pinState == 0) 
	{ 
		TIMER_delay(TIMER_2, 70);
		DIO_read(KEYPAD_C1_PORT, KEYPAD_C1_PIN, &u8_a_pinState);
		if(u8_a_pinState == 0)
		{
			while(u8_a_pinState == 0)
			DIO_read(KEYPAD_C1_PORT, KEYPAD_C1_PIN, &u8_a_pinState);
			DIO_write(KEYPAD_R0_PORT,KEYPAD_R0_PIN,HIGH);
			u8_a_keypadReading = u8_arr_a_keypadArr [0][1];
		}
	}
	
	DIO_read(KEYPAD_C2_PORT, KEYPAD_C2_PIN, &u8_a_pinState);
	if(u8_a_pinState == 0)
	{ 
		TIMER_delay(TIMER_2, 70);
		DIO_read(KEYPAD_C2_PORT, KEYPAD_C2_PIN, &u8_a_pinState);
		if(u8_a_pinState == 0)
		{
			while(u8_a_pinState == 0)
			DIO_read(KEYPAD_C2_PORT, KEYPAD_C2_PIN, &u8_a_pinState);
			DIO_write(KEYPAD_R0_PORT,KEYPAD_R0_PIN,HIGH);
			u8_a_keypadReading = u8_arr_a_keypadArr [0][2];
		}
	}
	
	DIO_write(KEYPAD_R0_PORT,KEYPAD_R0_PIN,HIGH);
	
	
	DIO_write(KEYPAD_R1_PORT,KEYPAD_R1_PIN,LOW);
	
	DIO_read(KEYPAD_C0_PORT, KEYPAD_C0_PIN, &u8_a_pinState);
	if(u8_a_pinState== 0)
	{
		TIMER_delay(TIMER_2, 70);
		DIO_read(KEYPAD_C0_PORT, KEYPAD_C0_PIN, &u8_a_pinState);
		if(u8_a_pinState == 0)
		{
			while(u8_a_pinState == 0)
			DIO_read(KEYPAD_C0_PORT, KEYPAD_C0_PIN, &u8_a_pinState);
			DIO_write(KEYPAD_R1_PORT,KEYPAD_R1_PIN,HIGH);
			u8_a_keypadReading = u8_arr_a_keypadArr [1][0];
		}
	}
	
	DIO_read(KEYPAD_C1_PORT, KEYPAD_C1_PIN, &u8_a_pinState);
	if(u8_a_pinState == 0)
	{
		TIMER_delay(TIMER_2, 70);
		DIO_read(KEYPAD_C1_PORT, KEYPAD_C1_PIN, &u8_a_pinState);
		if(u8_a_pinState == 0)
		{
			while(u8_a_pinState == 0)
			DIO_read(KEYPAD_C1_PORT, KEYPAD_C1_PIN, &u8_a_pinState);
			DIO_write(KEYPAD_R1_PORT,KEYPAD_R1_PIN,HIGH);
			u8_a_keypadReading = u8_arr_a_keypadArr [1][1];
		}
	}
	
	DIO_read(KEYPAD_C2_PORT, KEYPAD_C2_PIN, &u8_a_pinState);
	if(u8_a_pinState == 0)
	{
		TIMER_delay(TIMER_2, 70);
		DIO_read(KEYPAD_C2_PORT, KEYPAD_C2_PIN, &u8_a_pinState);
		if(u8_a_pinState == 0)
		{
			while(u8_a_pinState == 0)
			DIO_read(KEYPAD_C2_PORT, KEYPAD_C2_PIN, &u8_a_pinState);
			DIO_write(KEYPAD_R1_PORT,KEYPAD_R1_PIN,HIGH);
			u8_a_keypadReading = u8_arr_a_keypadArr [1][2];
		}
	}
		
	DIO_write(KEYPAD_R1_PORT,KEYPAD_R1_PIN,HIGH);
	
	
	DIO_write(KEYPAD_R2_PORT,KEYPAD_R2_PIN,LOW);
	
	DIO_read(KEYPAD_C0_PORT, KEYPAD_C0_PIN, &u8_a_pinState);
	if(u8_a_pinState== 0)
	{
		TIMER_delay(TIMER_2, 70);
		DIO_read(KEYPAD_C0_PORT, KEYPAD_C0_PIN, &u8_a_pinState);
		if(u8_a_pinState == 0)
		{
			while(u8_a_pinState == 0)
			DIO_read(KEYPAD_C0_PORT, KEYPAD_C0_PIN, &u8_a_pinState);
			DIO_write(KEYPAD_R2_PORT,KEYPAD_R2_PIN,HIGH);
			u8_a_keypadReading = u8_arr_a_keypadArr [2][0];
		}
	}
	
	DIO_read(KEYPAD_C1_PORT, KEYPAD_C1_PIN, &u8_a_pinState);
	if(u8_a_pinState == 0)
	{
		TIMER_delay(TIMER_2, 70);
		DIO_read(KEYPAD_C1_PORT, KEYPAD_C1_PIN, &u8_a_pinState);
		if(u8_a_pinState == 0)
		{
			while(u8_a_pinState == 0)
			DIO_read(KEYPAD_C1_PORT, KEYPAD_C1_PIN, &u8_a_pinState);
			DIO_write(KEYPAD_R2_PORT,KEYPAD_R2_PIN,HIGH);
			u8_a_keypadReading = u8_arr_a_keypadArr [2][1];
		}
	}
	
	DIO_read(KEYPAD_C2_PORT, KEYPAD_C2_PIN, &u8_a_pinState);
	if(u8_a_pinState == 0)
	{
		TIMER_delay(TIMER_2, 70);
		DIO_read(KEYPAD_C2_PORT, KEYPAD_C2_PIN, &u8_a_pinState);
		if(u8_a_pinState == 0)
		{
			while(u8_a_pinState == 0)
			DIO_read(KEYPAD_C2_PORT, KEYPAD_C2_PIN, &u8_a_pinState);
			DIO_write(KEYPAD_R2_PORT,KEYPAD_R2_PIN,HIGH);
			u8_a_keypadReading = u8_arr_a_keypadArr [2][2];
		}
	}
	
	DIO_write(KEYPAD_R2_PORT,KEYPAD_R2_PIN,HIGH);
	
	return u8_a_keypadReading ;
}