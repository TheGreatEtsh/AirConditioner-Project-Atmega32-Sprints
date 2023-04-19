/*
 * main.c
 *
 * Created: 4/18/2023 3:13:50 AM
 *  Author: Ahmed Hesham
 */ 


#include "APP/app.h"
int main()
{
	APP_initModules();
	APP_superLoop();
	//APP_testingTimer();
	while (1)
	{
	}
	return 0;
}