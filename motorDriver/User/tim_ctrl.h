#ifndef __tim_ctrl_H
#define __tim_ctrl_H

#include "include.h"

#define EncoderStoreNum		20		//�����ٶ�ֵ  ��Ҫ�ο���λ��ֵ������
#define 	ENCODER_NUM		(int)(65535)
#define		ENCODER_NUM_2	((int)(ENCODER_NUM/2.0f))
#define StateRef			(0.5f)	//ת����ֹ  �ο�����ֵ
#define ACCE_NUM			(20)	//���ٶȳ���  ���ٶȸ���ʱ��  ��λ ms   <10  ���ٶ�ֵ������Χ�ϴ�  >50 ���ٶȸ���Ƶ�ʹ���
#define	ACCEN_NUM			(100)	//����ٶȳ���֮  ��  Ϊ 2000

#define DEBUG_DATA_NUM		(2000)
#define DebugFreq			(10)


typedef struct Motor{
	signed char EnOverflowNum;	//����������Ĵ���
	signed long int EnCounter;	//����������ֵ
	int tEnCounter;
	
	char pArr;	//��ǰ�����ݵĴ洢λ��
	signed long int EnCoterArr[EncoderStoreNum];	//�����ٶ���
	signed char runstate;	//1 ��ת -1 ��ת 0 ��ֹ  �Ա�������ֵ���ķ���Ϊ��
	float speed;		//����ٶ�
	float MoterSpeedArr[EncoderStoreNum];
	char pSpArr;
	float accelration;	//������ٶ�
	signed char accDir;		//��������ٷ���   -1  ����   1  ����
	unsigned char motor_id;
	
}Motor_t;

unsigned char MotorState(Motor_t *pMotor);
void EncoderUpdate(Motor_t *pEncoder, TIM_HandleTypeDef htim);	//����������ֵ����  ������������鵱��
unsigned char EncoderFlow(Motor_t* pEncoder, TIM_HandleTypeDef htim);
unsigned char GetID(void);
#endif
