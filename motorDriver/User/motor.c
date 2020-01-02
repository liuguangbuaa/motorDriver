#include "motor.h"
extern Motor_t M1;



char CtrlMotor(unsigned char mode)
{

	switch(mode)
	{
		case CTRL_MODE:
		{
			CalcSpeedTar(&M1.speedTar,M1.speed);
			CalcSpeedPID(&M1.CtrlPWM,M1.speedTar,M1.speed);
			SetMotorPWM(CLOCKWISE,M1.CtrlPWM,M1.CtrlLastPWM,&(M1.CtrlLastPWM));
		}break;
	}
	
}

//���������ٶ�
/*
�жϵ�ǰ���ڵ������ٶ���������  1.���ٽ׶�  2.���ٽ׶�  3.���ٽ׶�  0.ֹͣ
���ݼ��ٽ׶�  ���㵱ǰ��Ŀ��λ��
*/
char CalcSpeedTar(float *speedTar,float speed)
{
//	*speedTar = 50.5;	//�ȸ���ֵ
	
	return HAL_OK;
}

//���������ٶ�  ����ʽPI������   ���ص���pwm����
char CalcSpeedPID(int *ctrl,float speedTar,float speedCur)
{
	static unsigned char ii; 
	static signed int Error[16];   //��� ����λ��-��ǰλ��
	static signed int VelocityError;
	ii++;
	Error[(ii&15)]=(speedTar - speedCur);  //��������������ת����  unsigned ת��Ϊ signed  ���λֱ�ӱ���������λ  signed ת��Ϊunsigned ���λֱ�ӱ���������λ
																//����unsigned���� ��Ϊ����ʱ�ᵼ�´���
	VelocityError=Error[(ii&15)] - Error[(ii-1&15)];
	
	*ctrl=(int)(Ctrl_P*(Error[(ii&15)])+Ctrl_D*VelocityError);
	
	if(Error[(ii&15)]<=0.1&&Error[(ii&15)]>=-0.1) *ctrl = 0;;  //����ADC<+-10ʱ ����������  ��Ӧ����Ϊ+-0.03A
	return HAL_OK;
}	

//��PID������з���  ���õ���������ƺ���   ������ת��������λ�ò������  ��  pid������֮���pwm   ��������ʲô����
char SetMotorPWM(char dir,int pwm,int lastPWM,int *last)
{
	int Ctrl = 0;
	Ctrl = lastPWM + pwm;
	*last = Ctrl;
	if(Ctrl<0)	Ctrl = 0;
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
	if(pwm <= 1000)
	{
		TIM1->CCR2 = 0;
		TIM1->CCR1 = pwm;
	}
	else
	{
		TIM1->CCR2 = 0;
		TIM1->CCR1 = 900;
		return 0;
	}
	return 1;
}

char setPWMClockwise(unsigned int pwm)		//һ·PWM   һ·�ߵ�ƽ
{
	if(pwm <= 1000)
	{
		TIM1->CCR1 = 0;
		TIM1->CCR2 = pwm;
	}
	else
	{
		TIM1->CCR1 = 0;
		TIM1->CCR2 = 900;
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
