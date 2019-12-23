#include "com.h"

//ͨѶӲ������  �����շ�
static unsigned char Uart_counter = 0;  //����
static char UartStartFlag = 0;
unsigned char UartRxData[9]; //������������
static unsigned int upwm;

/****************���������շ�******************/
void USART2Interrupt(char UartRxBuf)		//����  ״̬���ƴ���
{
	static unsigned char i =0;	
	static unsigned int scheck = 0;

	if(UartRxBuf=='}')	{
		if(Uart_counter==9) 	{
			scheck = 0;
			for(i=0;i<8;i++)	{
				scheck +=UartRxData[i];
			}
			scheck = scheck%100;
			if(scheck==UartRxData[8])	{
			switch(UartRxData[1])
			{
				case CMD_EN:	{
					if(UartRxData[2]==0x11)		{
						BoardEn(1);
					}
					else 	{
						BoardEn(0);
					}
				}break;
				case CMD_DEBUG:	{
	//				if(UartRxData[2]==0x11)	{
	//					FlagDebug = 1;	}
	//				else	{
	//					FlagDebug = 0;
	//				}
				}break;
				case CMD_PWMSET:	{
					upwm = UartRxData[2]*100+UartRxData[3];
					//����ת  PWMռ�ձ�   ���üĴ���
					if(UartRxData[0]!=MOTORSTOP)
					{
						if(UartRxData[0]==CLOCKWISE)	//˳ʱ��
							setPWMClockwise(upwm);
						else if(UartRxData[0]==ANTICLOCKWISE)	//��ʱ��
							setPWMAitClockwise(upwm);
					}
					else	//����
					{
						setZeroPWM();
					}
					
					
				}break;
				case CMD_FDBK:	{
					switch(UartRxData[2])	
					{
						case CTL_EncoderFDBK:	{
							//EncoderFdbk();
						}break;
						case CTL_GriverForceFDBK:	{
							
						}break;
						case CMD_PWMFDBK:	{
							//MotorPWMFdbk();
						}break;
						case CTL_SensorDataFDBK:	{
							//SensorFdbk(CTL_SensorDataFDBK);
						}break;
						case CTL_SensorPWMFDBK:	{
							//SensorFdbk(CTL_SensorPWMFDBK);
						}
						case FORCE_SWITCHFDBK:	{
							//ForceSwitchFdbk();
						}break;
					}
				}break;
				case CMD_FLASH:	{
					switch(UartRxData[2])	{
						case CTL_FLASHCHANGE:	{
							//FlashChange((UartRxData[4]*256+UartRxData[5]),UartRxData[3]);
						}break;
						case CTL_FLASHFDBK:	{
							//FlashFDBK(UartRxData[3]);
						}break;
						case CTL_FLASHINIT:	{
							//FlashInit();
						}break;
						default :
							break;
					}	
				}break;
				case CMD_SENSOR:
				{
	//				if(UartRxData[2]==0x10)		{	//����Ҫ�����������������λ��
	//					SensorCtrl(UartRxData[3],UartRxData[4]);
	//				}
					switch (UartRxData[2]){
						case CTL_CALIBRATE:	//У׼������
						{
						}break;
						default :
							break;
					}
					
				}break;				
				default :
				{}break;
			}
		}	
		}
		Uart_counter = 0;
		UartStartFlag = 0;
	}

	if(UartStartFlag==1)
	{
		if(Uart_counter>8)  UartStartFlag = 0;
		else 
		{
			UartRxData[Uart_counter] = UartRxBuf;  //��������
			Uart_counter++;
		}	
	}
	if(UartRxBuf=='{')
	{
		UartStartFlag = 1;
		Uart_counter = 0;
	}
}





