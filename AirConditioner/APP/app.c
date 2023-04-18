/*
 * app.c
 *
 * Created: 4/18/2023 7:32:47 PM
 *  Author: Ahmed Hesham
 */ 

#include "app.h"

u8 u8_g_applicationState = 0;


void APP_initModules(void)
{
	
}



void APP_superLoop (void)
{
	u8 keypadPressed = 0;
	
	while (1)
	{
		switch(u8_g_applicationState)
		{
			case WELCOMING:	
									break;
			case CHOOSING_TEMP:					
									break;
			case IDLE_STATE:	
									break;
			case RESETTING_STATE:					
									break;
			
			default:				
									break;
		}
	}
}


void APP_testingTimer()
{
	DIO_init(PORT_A,0,OUTPUT);
	DIO_init(PORT_A,1,OUTPUT);

	TIMER_init(TIMER_2);
	TIMER_setCallBack(TIMER_2, APP_callBackTestingTask);
	TIMER_setTime(TIMER_2, 2000);
	TIMER_start(TIMER_2);
	
	while (1)
	{
		TIMER_delay(TIMER_2, 1000);
		DIO_toggle(PORT_A,0);
		while (1)
		{
		}
	}
}

void APP_callBackTestingTask(void)
{
	DIO_toggle(PORT_A,1);
}

void APP_testingLm35(void)
{
	LM35_init();
	DIO_init(PORT_B,0,OUTPUT);
	DIO_init(PORT_B,1,OUTPUT);
	
	while(1)
	{
		if(LM35_read()>25)
		{
			DIO_write(PORT_B,0,HIGH);
			DIO_write(PORT_B,1,LOW);
		}
		else
		{
			DIO_write(PORT_B,1,HIGH);
			DIO_write(PORT_B,0,LOW);
		}
	}	
}

void APP_testingKeypad(void)
{
	TIMER_init(TIMER_2);
	TIMER_start(TIMER_2);
	KEYPAD_init();
	
	DIO_init(PORT_B,0,OUTPUT);
	DIO_init(PORT_B,1,OUTPUT);
	DIO_init(PORT_B,2,OUTPUT);
	DIO_init(PORT_B,3,OUTPUT);
	
	u8 KeyPressed = 0;							
												
	while(1)									
	{											
		KeyPressed = KEYPAD_read();				
		while (!KeyPressed)						
		{										
			KeyPressed = KEYPAD_read();			
			switch (KeyPressed)					
			{
				case '1':	DIO_write(PORT_B,3,LOW);	DIO_write(PORT_B,2,LOW);	DIO_write(PORT_B,1,LOW);	DIO_write(PORT_B,0,HIGH);	break;
				case '2':	DIO_write(PORT_B,3,LOW);	DIO_write(PORT_B,2,LOW);	DIO_write(PORT_B,1,HIGH);	DIO_write(PORT_B,0,LOW);	break;
				case '3':	DIO_write(PORT_B,3,LOW);	DIO_write(PORT_B,2,LOW);	DIO_write(PORT_B,1,HIGH);	DIO_write(PORT_B,0,HIGH);	break;
				case '4':	DIO_write(PORT_B,3,LOW);	DIO_write(PORT_B,2,HIGH);	DIO_write(PORT_B,1,LOW);	DIO_write(PORT_B,0,LOW);	break;
				case '5':	DIO_write(PORT_B,3,LOW);	DIO_write(PORT_B,2,HIGH);	DIO_write(PORT_B,1,LOW);	DIO_write(PORT_B,0,HIGH);	break;
				case '6':	DIO_write(PORT_B,3,LOW);	DIO_write(PORT_B,2,HIGH);	DIO_write(PORT_B,1,HIGH);	DIO_write(PORT_B,0,LOW);	break;
				case '7':	DIO_write(PORT_B,3,LOW);	DIO_write(PORT_B,2,HIGH);	DIO_write(PORT_B,1,HIGH);	DIO_write(PORT_B,0,HIGH);	break;
				case '8':	DIO_write(PORT_B,3,HIGH);	DIO_write(PORT_B,2,LOW);	DIO_write(PORT_B,1,LOW);	DIO_write(PORT_B,0,LOW);	break;
				case '9':	DIO_write(PORT_B,3,HIGH);	DIO_write(PORT_B,2,LOW);	DIO_write(PORT_B,1,LOW);	DIO_write(PORT_B,0,HIGH);	break;

			}
		}
	}
}