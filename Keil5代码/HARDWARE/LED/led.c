#include "led.h"


/**
* @brief ��ʼLED ����PC13
* @param 
* @return 
*/
void LED_Init(void)
{
 
	 GPIO_InitTypeDef  GPIO_InitStructure;
		
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOC, ENABLE);	 //ʹ��PC13�˿�ʱ��
		

		
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;	    		 //PC13 �˿�����, �������
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	 GPIO_Init(GPIOC, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
	 GPIO_SetBits(GPIOC,GPIO_Pin_13); 						 //PC13 ����� 
}


  
