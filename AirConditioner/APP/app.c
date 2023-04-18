/*
 * app.c
 *
 * Created: 4/18/2023 7:32:47 PM
 *  Author: Ahmed Hesham
 */ 

#include "app.h"

u8 u8_g_applicationState = 0;
u8 u8_g_defTemp=20;

void APP_initModules(void)
{
	LCD_Init();
	TIMER_init(TIMER_2);
	ADC_init();
	BUZZER_init(BUZZER_0);
KEYPAD_init();
LM35_init();
}



void APP_superLoop (void)
{
	u8 keypadPressed = 0;
	u8 welcomeMassage[10]="WELCOME";
	u8 defaultTemp[30]="The Default Temp is 20";
	u8 chooseTemp[30]="Choose the Temp:";
	u8 rangeTemp[30]="The Range of  Temp is 18 to 35";
	u8 currentTemp[30]="The current Temp is :";
	u8 resetTemp[30]=" Temp is reset to 20";
	
	while (1)
	{
		switch(u8_g_applicationState)
		{
			case WELCOMING:	
	LCD_WriteString(welcomeMassage);
	TIMER_start(TIMER_2);
	TIMER_delay(TIMER_2,1000);
	LCD_Clear();
	LCD_WriteString(defaultTemp);
	TIMER_delay(TIMER_2,1000);
    LCD_Clear();
	u8_g_applicationState++;
	
									break;
			case CHOOSING_TEMP:					
	LCD_WriteString(chooseTemp);
	BUZZER_off(BUZZER_0);	
	TIMER_delay(TIMER_2,500);
	u8_g_applicationState++;
	
									break;
			case IDLE_STATE:
			LCD_Clear();
	LCD_WriteString(rangeTemp);
			keypadPressed=KEYPAD_read();
			switch (keypadPressed)
			{
				case '1':
				u8_g_defTemp++;	
				break;
				case '2':
				u8_g_defTemp--;		
				break;
				case '3':
			LCD_Clear();
			LCD_WriteString(currentTemp);
			LCD_WriteNumber(LM35_read());
	while(LM35_read()>u8_g_defTemp)
	{
	BUZZER_on(BUZZER_0);
	}
	break;
			 case '4':
u8_g_applicationState=1;
				break;
				case '5':
u8_g_applicationState++;				
				break;
				
		default:
		break;
		
			}
				
				
									break;
			case RESETTING_STATE:					
		u8_g_defTemp=20;
		LCD_Clear();
		LCD_WriteString(resetTemp);
u8_g_applicationState=2;
TIMER_delay(TIMER_2,1000);			
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