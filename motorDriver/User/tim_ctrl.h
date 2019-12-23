#ifndef __tim_ctrl_H
#define __tim_ctrl_H

#include "include.h"

#define EncoderStoreNum		20		//�����ٶ�ֵ  ��Ҫ�ο���λ��ֵ������
#define 	ENCODER_NUM		(int)(65535)
#define		ENCODER_NUM_2	((int)(ENCODER_NUM/2.0f))

typedef struct Motor{
	signed char EnOverflowNum;	//����������Ĵ���
	signed long int EnCounter;	//����������ֵ
	int tEnCounter;
	
	char pArr;	//��ǰ�����ݵĴ洢λ��
	signed long int EnCoterArr[EncoderStoreNum];	//�����ٶ���
	signed char runstate;	//1 ��ת -1 ��ת 0 ��ֹ  �Ա�������ֵ���ķ���Ϊ��
	int speed;		//����ٶ�
	signed int MoterSpeedArr[EncoderStoreNum];
	char pSpArr;
	int accelration;	//������ٶ�
	
}Motor_t;


void EncoderUpdate(Motor_t *pEncoder, TIM_HandleTypeDef htim);	//����������ֵ����  ������������鵱��
unsigned char EncoderFlow(Motor_t* pEncoder, TIM_HandleTypeDef htim);

#endif
