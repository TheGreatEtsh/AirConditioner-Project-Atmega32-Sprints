/*
* app.c
*
* Created: 4/18/2023 7:32:47 PM
*  Author: Ahmed Hesham
*/

#include "app.h"

u8 u8_g_applicationState	= 0;
u8 u8_g_desiredTemp			= DEFAULT_TEMPERATURE;

void APP_initModules(void)
{
	TIMER_init(TIMER_2);
	TIMER_stopInterrupt(TIMER_2);
	TIMER_start(TIMER_2);
	TIMER_setTime(TIMER_2, 10000);

	LCD_PinsInit();	
	LCD_Init();

	LCD_Clear();
	LCD_WriteChar('A');
	

	BUZZER_init(BUZZER_0);
	KEYPAD_init();
	LM35_init();
	u8 bellShape[] = {
		0x04,
		0x0E,
		0x0E,
		0x0E,
		0x1F,
		0x00,
		0x04,
		0x00
	};
	
	LCD_CustomChar(4, bellShape);
	
	TIMER_setCallBack(TIMER_2, APP_callBack);
	
	
}



void APP_superLoop (void)
{
	u8 keypadPressed = 0, currentTemp = 0 , prevTemp = 0;
	u8 temperature	 = u8_g_desiredTemp;
	u8 welcomeMassage[10]="WELCOME";
	u8 chooseTemp[30]="Choose the Temp:";
	u8 tempRepresentation = 0;

	
	while (1)
	{
		switch(u8_g_applicationState)
		{
			case WELCOMING:
			LCD_WriteString(welcomeMassage);
			TIMER_delay(TIMER_2,1000);

			LCD_Clear();
			LCD_WriteString("Default temp ");
			LCD_WriteNumber(DEFAULT_TEMPERATURE);
			TIMER_delay(TIMER_2,1000);
			
			LCD_Clear();
			u8_g_applicationState = CHOOSING_TEMP;
			break;
			
			case CHOOSING_TEMP:
			LCD_Clear();
			LCD_WriteString(chooseTemp);
			BUZZER_off(BUZZER_0);
			TIMER_delay(TIMER_2,1000);
			
			LCD_Clear();
			LCD_WriteString("Max Temp 35");
			LCD_SetCursor(1,0);
			LCD_WriteString("Min Temp 18");
			TIMER_delay(TIMER_2, 1000);
			
			keypadPressed = KEYPAD_read();
			u8 tempChanged = 1;
			while (keypadPressed != '3')
			{
				keypadPressed = KEYPAD_read();
				tempRepresentation = temperature - 18;
				if (tempChanged)
				{					
					LCD_Clear();
					LCD_SetCursor(0,14);
					LCD_WriteNumber(temperature);
					LCD_SetCursor(1,0);
					tempChanged = 0;	
					while (tempRepresentation--)
					{
						LCD_WriteChar(4);
					}
				}
				
				switch (keypadPressed)
				{
					case '1':
					if (temperature < 35)					
					{	
						tempChanged = 1;
						temperature++;
					}
					break;
					case '2':
					if (temperature > 18)
					{
						tempChanged = 1;
						temperature--;
					}
					break;
					
					case '3':
						u8_g_desiredTemp = temperature ;
						u8_g_applicationState = IDLE_STATE;
					break;
					default:	break;
				}
				if (u8_g_applicationState != CHOOSING_TEMP)
				break;
			}
			u8_g_applicationState = IDLE_STATE;
			
			break;
			
			case IDLE_STATE:
			prevTemp = 0;
			keypadPressed = KEYPAD_read();
			while (keypadPressed != '4' && keypadPressed != '5')
			{
				keypadPressed = KEYPAD_read();
				
				currentTemp = LM35_read();
				if(prevTemp != currentTemp)				
				{	
					LCD_Clear();
					LCD_WriteString("Cur. Temp = ");
					LCD_WriteNumber(currentTemp);
					LCD_SetCursor(1,0);
					if (currentTemp > u8_g_desiredTemp)
					{
						BUZZER_on(BUZZER_0);
						/*print bell*/
						LCD_WriteChar(4);
					}
					else
					{
						BUZZER_off(BUZZER_0);
						/*delete bell*/
						LCD_ClearLoc(1,0,1);
					}
					
				}
				switch(keypadPressed)
				{
					case '4':
					u8_g_applicationState = CHOOSING_TEMP;
					break;
					case '5':
					u8_g_applicationState = RESETTING_STATE;
					break;
				}
				
				prevTemp = currentTemp;
			}
			break;
			
			case RESETTING_STATE:
			u8_g_desiredTemp = DEFAULT_TEMPERATURE;
			LCD_Clear();
			LCD_WriteString("Temp is Reseted");
			LCD_SetCursor(1,0);
			LCD_WriteString("Temp is ");
			LCD_WriteNumber(DEFAULT_TEMPERATURE);
			TIMER_delay(TIMER_2,1000);
			TIMER_stopInterrupt(TIMER_2);
			
			u8_g_applicationState = IDLE_STATE;
			
			break;
			
			default:
			break;
		}
	}
}


void APP_callBack (void)
{
	u8_g_applicationState = IDLE_STATE;
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