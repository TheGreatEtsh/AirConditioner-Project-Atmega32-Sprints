/*
 * app.h
 *
 * Created: 4/3/2023 7:32:34 PM
 *  Author: Ahmed Hesham
 */ 


#ifndef APP_H_
#define APP_H_

#include "../ECUAL/lm35/lm35.h"

#define WELCOMING					0
#define CHOOSING_TEMP				1
#define IDLE_STATE					2
#define RESETING_STATE				3


void APP_initModules(void);
void APP_superLoop	(void);
void APP_welcomingMsg (void);
void APP_chooseTempMsg(void);

#endif /* APP_H_ */