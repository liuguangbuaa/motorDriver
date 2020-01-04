#ifndef __MOTER_H
#define __MOTER_H

#include "include.h"

#define FULLPWM			1000
#define CLOCKWISE		0x21
#define ANTICLOCKWISE	0x22
#define	MOTORSTOP		0x20
#define	REDUCTION		62
#define PI				(3.1415926535)


char setPWMAitClockwise(unsigned int pwm);		//һ·PWM   һ·�ߵ�ƽ
char setPWMClockwise(unsigned int pwm);		//һ·PWM   һ·�ߵ�ƽ
char setFullPWM(void);
char setZeroPWM(void);

char CalcSpeedTar(float *speedTar,float speed);
char CtrlMotor(unsigned char mode);
char CalcSpeedPID(int *ctrl,float speedTar,float speedCur);
char SetMotorPWM(char dir,int pwm,int lastPWM,int *last);


typedef struct MotorCtrl{
	
	float speedTar;
	int CtrlPWM;
	int CtrlLastPWM;
	unsigned char ctrlDir;
	
	signed long int PosTarget;	//����������ֵ
	int ctrlStep;		//���Ƶ���step
	int stepCounter;	//�ڿ��ƹ������ۼ�
	int ctrlProcess;	//���ƹ���  0 ֹͣ  1����  2����  3����
	
	
}MotorCtrl_t;

#endif
