#include "key.h"



/**
* @brief ��ʼKEY ����PA7--key1   PA12--key2
* @param 
* @return 
*/
void KEY_Init(void)
{
	 GPIO_InitTypeDef  GPIO_InitStructure;
		
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //ʹ��PA7,PA12�˿�ʱ��
		
		
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;	    		 //PA7 �˿�����, ��������
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 		 //��������
	 GPIO_Init(GPIOA, &GPIO_InitStructure);	  		

	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;	    		 //PA12 �˿�����, ��������
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 //��������
	 GPIO_Init(GPIOA, &GPIO_InitStructure);	  			
	
}
