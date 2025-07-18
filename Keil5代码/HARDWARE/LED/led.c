#include "led.h"


/**
* @brief 初始LED 引脚PC13
* @param 
* @return 
*/
void LED_Init(void)
{
 
	 GPIO_InitTypeDef  GPIO_InitStructure;
		
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOC, ENABLE);	 //使能PC13端口时钟
		

		
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;	    		 //PC13 端口配置, 推挽输出
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	 GPIO_Init(GPIOC, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
	 GPIO_SetBits(GPIOC,GPIO_Pin_13); 						 //PC13 输出高 
}


  
