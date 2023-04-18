/*
 * lm35.h
 *
 * Created: 4/18/2023 3:45:30 AM
 *  Author: Ahmed Hesham
 */ 


#ifndef LM35_H_
#define LM35_H_


/***************************************_INCLUDES_***************************************/
#include "../../MCAL/adc/adc.h"

/***************************************_PROTOTYPES_***************************************/

void LM35_init				(void);
u16  LM35_read				(void);





#endif /* LM35_H_ */