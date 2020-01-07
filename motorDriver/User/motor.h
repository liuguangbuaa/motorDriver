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

char CtrlMotor(unsigned char mode);
char CalcSpeedPID(int *ctrl,float speedTar,float speedCur);
char SetMotorPWM(char dir,int pwm,int lastPWM,int *last);

char CalcSpeedTar(float *speedTar,unsigned char *dir);

#define vMax  (70.0)
#define	a1	(10.0)
#define	a2	(10.0)

enum Process
{
	ProStop = 0,
	ProAcce,
	ProUniform,
	ProReduce
};

typedef struct MotorCtrl{
	
	float speedTar;
	float speedMax;
	int CtrlPWM;
	int CtrlLastPWM;
	unsigned char ctrlDir;
	
	signed long int PosTarget;	//����������ֵ
	int ctrlStep;		//���Ƶ���step
	int stepCounter;	//�ڿ��ƹ�����ʣ���step
	int reduceStep;		//��ʼ���ٵ�step
	int acceStep;		//�������step
	int ctrlProcess;	//���ƹ���  0 ֹͣ  1����  2����  3����
	float speedAcce;	//ֻ���յ�����ʱ����һ��
	float speedReduce;	//���ٽ׶εļ����ٶ�

	//
}MotorCtrl_t;
//ö��



#endif
