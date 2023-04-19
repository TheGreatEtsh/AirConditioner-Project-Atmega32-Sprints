/*
 * app.h
 *
 * Created: 4/3/2023 7:32:34 PM
 *  Author: Ahmed Hesham
 */ 


#ifndef APP_H_
#define APP_H_

#include "../ECUAL/lm35/lm35.h"
#include "../ECUAL/keypad/keypad.h"
#include "../MCAL/timer/timer.h"
#include "../ECUAL/lcd/LCD_Interface.h"
#include "../ECUAL/buzzer/buzzer.h"



#define WELCOMING					0
#define CHOOSING_TEMP				1
#define IDLE_STATE					2
#define RESETTING_STATE				3


#define DEFAULT_TEMPERATURE			20


void APP_initModules(void);
void APP_superLoop	(void);
void APP_callBack (void);


void APP_testingTimer(void);
void APP_callBackTestingTask (void);
void APP_testingLm35(void);
void APP_testingKeypad(void);

#endif /* APP_H_ */