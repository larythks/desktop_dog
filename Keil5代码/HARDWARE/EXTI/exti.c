#include "exti.h"
#include "led.h"
#include "delay.h"
#include "key.h"

/*******************************************************************************
* �� �� ��         : My_EXTI_Init
* ��������		   : �ⲿ�жϳ�ʼ��
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void My_EXTI_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	EXTI_InitTypeDef  EXTI_InitStructure;
	
	KEY_Init();//��ʼ������
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource7);//ѡ��GPIO�ܽ������ⲿ�ж���·
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource12);//ѡ��GPIO�ܽ������ⲿ�ж���·
	
	//EXTI7 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//EXTI0�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//�����ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���	
	
	//EXTI12 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;//EXTI2�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;		//�����ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
	
	
	EXTI_InitStructure.EXTI_Line=EXTI_Line7;
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Rising;//�����ش���
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	EXTI_InitStructure.EXTI_Line=EXTI_Line12; 
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;//�½��ش���
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
}


/*******************************************************************************
* �� �� ��         : EXTI9_5_IRQHandler
* ��������		   : �ⲿ�ж�0����
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void EXTI9_5_IRQHandler(void)
{
	//�����ж�
	if(EXTI_GetITStatus(EXTI_Line7)==1)
	{
		delay_ms(10);//����
		if(KEY1==1)
		{
			LED=!LED;
		}	
	}
	EXTI_ClearITPendingBit(EXTI_Line7);
}

///*******************************************************************************
//* �� �� ��         : EXTI15_10_IRQHandler
//* ��������		   : �ⲿ�ж�2����
//* ��    ��         : ��
//* ��    ��         : ��
//*******************************************************************************/
//void EXTI15_10_IRQHandler(void)
//{
//	
//   //�����ж�
//	if(EXTI_GetITStatus(EXTI_Line12)==1)
//	{
//		delay_ms(10);
//		if(KEY2==0)
//		{	
//			LED=!LED;
//		}
//		
//	}
//	EXTI_ClearITPendingBit(EXTI_Line12);
//}


