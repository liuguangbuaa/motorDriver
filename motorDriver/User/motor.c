#include "motor.h"






char setPWMAitClockwise(unsigned int pwm)		//һ·PWM   һ·�ߵ�ƽ
{
	if(pwm <= FULLPWM)
	{
		TIM1->CCR2 = FULLPWM;
		TIM1->CCR1 = pwm;
		return 0;
	}
	return 1;

}

char setPWMClockwise(unsigned int pwm)		//һ·PWM   һ·�ߵ�ƽ
{
	if(pwm <= FULLPWM)
	{
		TIM1->CCR1 = FULLPWM;
		TIM1->CCR2 = pwm;
		return 0;
	}
	return 1;
}

char setFullPWM()		//�ƶ�ģʽ  ����
{
	TIM1->CCR1 = FULLPWM;
	TIM1->CCR2 = FULLPWM;
	return 0;
}

char setZeroPWM()	//����ģʽ  ����
{
	TIM1->CCR1 = 0;
	TIM1->CCR2 = 0;
	return 0;
}
