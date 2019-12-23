#ifndef __MOTER_H
#define __MOTER_H

#include "include.h"

#define FULLPWM			1000
#define CLOCKWISE		0x21
#define ANTICLOCKWISE	0x22
#define	MOTORSTOP		0x20

char setPWMAitClockwise(unsigned int pwm);		//һ·PWM   һ·�ߵ�ƽ
char setPWMClockwise(unsigned int pwm);		//һ·PWM   һ·�ߵ�ƽ
char setFullPWM();
char setZeroPWM();


#endif
