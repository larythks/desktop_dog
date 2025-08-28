#include "key.h"



/**
* @brief 初始KEY 引脚PA7--key1   PA12--key2
* @param 
* @return 
*/
void KEY_Init(void)
{
	 GPIO_InitTypeDef  GPIO_InitStructure;
		
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //使能PA7,PA12端口时钟
		
		
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;	    		 //PA7 端口配置, 下拉输入
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 		 //下拉输入
	 GPIO_Init(GPIOA, &GPIO_InitStructure);	  		

	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;	    		 //PA12 端口配置, 上拉输入
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 //上拉输入
	 GPIO_Init(GPIOA, &GPIO_InitStructure);	  			
	
}
