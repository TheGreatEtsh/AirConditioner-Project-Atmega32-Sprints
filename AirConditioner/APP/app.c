/*
 * app.c
 *
 * Created: 4/18/2023 7:32:47 PM
 *  Author: Ahmed Hesham
 */ 

#include "app.h"

void APP_initModules(void)
{
	
}



void APP_superLoop (void)
{
	while (1)
	{
		
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