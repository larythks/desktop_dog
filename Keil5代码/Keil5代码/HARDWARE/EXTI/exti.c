#include "exti.h"
#include "led.h"
#include "delay.h"
#include "key.h"

/*******************************************************************************
* 函 数 名         : My_EXTI_Init
* 函数功能		   : 外部中断初始化
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void My_EXTI_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	EXTI_InitTypeDef  EXTI_InitStructure;
	
	KEY_Init();//初始化按键
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource7);//选择GPIO管脚用作外部中断线路
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource12);//选择GPIO管脚用作外部中断线路
	
	//EXTI7 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//EXTI0中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//子优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器	
	
	//EXTI12 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;//EXTI2中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;		//子优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
	
	
	EXTI_InitStructure.EXTI_Line=EXTI_Line7;
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Rising;//上升沿触发
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	EXTI_InitStructure.EXTI_Line=EXTI_Line12; 
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;//下降沿触发
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
}


/*******************************************************************************
* 函 数 名         : EXTI9_5_IRQHandler
* 函数功能		   : 外部中断0函数
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void EXTI9_5_IRQHandler(void)
{
	//按键中断
	if(EXTI_GetITStatus(EXTI_Line7)==1)
	{
		delay_ms(10);//消抖
		if(KEY1==1)
		{
			LED=!LED;
		}	
	}
	EXTI_ClearITPendingBit(EXTI_Line7);
}

///*******************************************************************************
//* 函 数 名         : EXTI15_10_IRQHandler
//* 函数功能		   : 外部中断2函数
//* 输    入         : 无
//* 输    出         : 无
//*******************************************************************************/
//void EXTI15_10_IRQHandler(void)
//{
//	
//   //按键中断
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


