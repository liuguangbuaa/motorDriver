#include "motor.h"
#include "math.h"
extern Motor_t M1;
MotorCtrl_t M1Ctrl;
enum Process M1Process;
char CtrlMotor(unsigned char mode)
{
	static unsigned long int CtrlCounter = 0;
	CtrlCounter++;
	M1Ctrl.stepCounter--;
	switch(mode)
	{
		case CTRL_MODE:
		{
			if(CtrlCounter%10==0)	{
				CalcSpeedTar(&M1Ctrl.speedTar,&M1Ctrl.ctrlDir);
			}
			CalcSpeedPID(&M1Ctrl.CtrlPWM,M1Ctrl.speedTar,M1.speed);
			SetMotorPWM(CLOCKWISE,M1Ctrl.CtrlPWM,M1Ctrl.CtrlLastPWM,&(M1Ctrl.CtrlLastPWM));
		}break;
	}
	
}

//���������ٶ�  �滮����
/*
�жϵ�ǰ���ڵ������ٶ���������  1.���ٽ׶�  2.���ٽ׶�  3.���ٽ׶�  0.ֹͣ

���ݼ��ٽ׶�  ���㵱ǰ��Ŀ��λ��  �ó�ת������  Ŀ���ٶ�
���Ͻ������¹滮  �滮���ڴ���ִ������
�ٶ��滮����   10ms   ִ������1ms

������ƽṹ��

���룺Ŀ��λ��  ִ����ʱ��  ��ǰ�Ѿ�ִ�е�ʱ��  ���ӡ����ٶ�  ����ٶ�  ��ǰ�ٶ�
�ó������ι滮Ŀ���ٶ�  ת������  
*/
char CalcSpeedTar(float *speedOut,unsigned char *dirOut)
{
	float speedTar;
//	static int sin_t = 0;
//	sin_t++;
//	*speedTar = 35*(sin(0.008*PI*sin_t)+1);
	//�Ƚϵ�ǰλ����Ŀ��λ�ô�С  �ó�dir
	if(M1Ctrl.PosTarget < M1.EnCounter)	{
		*dirOut = CLOCKWISE;
	}
	else if(M1Ctrl.PosTarget > M1.EnCounter)	{
		*dirOut = ANTICLOCKWISE;
	}
	else	{
		*dirOut = MOTORSTOP;
	}
	//���ݵ�ǰ�����׶Σ�step�жϣ�  ��⵱ǰĿ���ٶ�  ÿһ�ζ����¹滮 reduceStep
	//�жϵ�ǰ����״̬
	if(M1Ctrl.stepCounter > M1Ctrl.acceStep)	{
		M1Ctrl.ctrlProcess = ProAcce;
	}
	else if(M1Ctrl.stepCounter > M1Ctrl.reduceStep)	{
		M1Ctrl.ctrlProcess = ProUniform;
	}
	else {	//���ٽ׶�  �������ͣ����ӽ�Ŀ��Ƕ�
		M1Ctrl.ctrlProcess = ProReduce;
	}
	//����״̬  �滮Ŀ��Ƕ�
	switch(M1Ctrl.ctrlProcess)
	{
		case  ProStop:
		{
			speedTar = 0;
		}break;
		case ProAcce:
		{
			speedTar += M1Ctrl.speedAcce;
			if(speedTar > M1Ctrl.speedMax)
				speedTar = M1Ctrl.speedMax;
		}break;
		case ProUniform:	//���ٽ׶�  ����˵Ҫ���¹滮һ��  ʵʱ�ı�����ٶȺ� reduceStep
		{
			speedTar = M1Ctrl.speedMax;		
		}break;
		case ProReduce:		//
		{
			speedTar = M1Ctrl.speedTar - M1Ctrl.speedReduce; 
			if(speedTar<0)
				speedTar = 0;
		}break;
		default:
		{}break;
			
	}
	
	*speedOut = speedTar;
	
	return HAL_OK;
}
//�滮����  ���뵱ǰλ��  Ŀ��λ��  �滮��ʱ��  ��ǰ�ٶ�  ��֪���ٶ�  ���ٶȵ�  �ó��滮�ڵ� speedMax��
//ch ��������λ��  ch = 1 ���յ�ָ��ʱ�滮  ch = 2 �ڹ����й滮
unsigned char PlanTraj(signed long int posTar,int stepAll,unsigned char ch)
{
	M1Ctrl.PosTarget = posTar;
	long int posErr = M1Ctrl.PosTarget-M1.EnCounter;
	if(posErr<0)	posErr = -posErr;
	if(ch==1)	{	//���յ�ָ���滮  Ĭ�ϵ�ǰ�ٶ�Ϊ0
		//���ж��Ƿ��Ǻ���Ĺ滮  ���Ƿ��������һ��ʱ��
		if(stepAll > (posErr)/vMax)	//���Թ滮
		{
		}	
		else {	//����û�����ٽ׶εķ���������
			
		}
	}
	else if(ch==2)	//���յ��ù��������滮
	{
		
	}
	
}


//���������ٶ�  ����ʽPI������   ���ص���pwm����
char CalcSpeedPID(int *ctrl,float speedTar,float speedCur)
{
	static unsigned char ii; 
	static float Error[16];   //��� ����λ��-��ǰλ��
	static float VelocityError;
	ii++;
	Error[(ii&15)]=(speedTar - speedCur);  //��������������ת����  unsigned ת��Ϊ signed  ���λֱ�ӱ���������λ  signed ת��Ϊunsigned ���λֱ�ӱ���������λ
																//����unsigned���� ��Ϊ����ʱ�ᵼ�´���
	VelocityError=Error[(ii&15)] - Error[(ii-1&15)];
	
	*ctrl=(int)(Ctrl_P*VelocityError + Ctrl_I*(Error[(ii&15)]));
	
	//if(Error[(ii&15)]<=0.1&&Error[(ii&15)]>=-0.1) *ctrl = 0;  //����ADC<+-10ʱ ����������  ��Ӧ����Ϊ+-0.03A
	return HAL_OK;
}	

//��PID������з���  ���õ���������ƺ���   ������ת��������λ�ò������  ��  pid������֮���pwm   ��������ʲô����
char SetMotorPWM(char dir,int pwm,int lastPWM,int *last)
{
	int Ctrl = 0;
	Ctrl = lastPWM + pwm;
	if(Ctrl>1000)
	{
		Ctrl = 1000;
	}
	else if(Ctrl<0)
	{
		Ctrl = 0;
	}
	*last = Ctrl;
	switch(dir)
	{
		case CLOCKWISE:
		{
			setPWMClockwise(Ctrl);
		}break;
		case ANTICLOCKWISE:
		{
			setPWMAitClockwise(Ctrl);
		}break;
		case MOTORSTOP:
		{
			setFullPWM();
		}break;
		default :
		{
			setFullPWM();
		}break;
	}
	
	return HAL_OK;
}
/**************************************�����������****************************************/
char setPWMAitClockwise(unsigned int pwm)		//һ·PWM   һ·�ߵ�ƽ
{
	if(pwm < PWM_MAX*10)
	{
		TIM1->CCR2 = 0;
		TIM1->CCR1 = pwm;
	}
	else
	{
		TIM1->CCR2 = 0;
		TIM1->CCR1 = PWM_MAX*10;
		return 0;
	}
	return 1;
}

char setPWMClockwise(unsigned int pwm)		//һ·PWM   һ·�ߵ�ƽ
{
	if(pwm < PWM_MAX*10)
	{
		TIM1->CCR1 = 0;
		TIM1->CCR2 = pwm;
	}
	else
	{
		TIM1->CCR1 = 0;
		TIM1->CCR2 = PWM_MAX*10;
		return 0;
	}
	return 1;
}

char setFullPWM()		//�ƶ�ģʽ  ����
{
	TIM1->CCR1 = 0;
	TIM1->CCR2 = 0;
	return 0;
}

char setZeroPWM()	//����ģʽ  ����
{
	TIM1->CCR1 = FULLPWM;
	TIM1->CCR2 = FULLPWM;
	return 0;
}
