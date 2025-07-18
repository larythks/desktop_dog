#include "user.h"

int Sign = 0;

int main(void)
{	
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	systick_init(SysTick_CLKSource_HCLK);	    //延时函数初始化	  
	LED_Init();		  	//初始化与LED连接的硬件接口
	USART1_Init(115200);//串口1初始化
	USART2_Init(115200);//串口2初始化（天问模块）
	USART3_Init(9600);//串口3初始化（蓝牙模块）
	//OLED初始化
	OLED_Init();
	OLED_Clear();
	
	//定时器4通道初始化（小狗四肢）
	TIM4_CH1_Init(1999,719);//左前
	TIM4_CH2_Init(1999,719);//右后
	TIM4_CH3_Init(1999,719);//右前
	TIM4_CH4_Init(1999,719);//左后
	//定时器3通道1初始化（小狗尾巴）
	TIM3_CH1_Init(1999,719);//尾巴
	
	OLED_ShowImage(32,0,64,64,BMP13_2);
	OLED_Update();
	
	//初始化动作
	Sleep();
	SlowStand();
	
	while(1)
	{	
		if(Sign==1)
		{
			Stand();//站立
		}
		else if(Sign==2)
		{
			Advance();//前进
		}
		else if(Sign==3)
		{
			Queen();//后退
		}
		else if(Sign==4)
		{
			Left();//左转
		}
		else if(Sign==5)
		{
			Right();//右转
		}
		else if(Sign==6)
		{
			Handshake();//握手
		}
		else if(Sign==7)
		{
			Sit();//坐
		}
		else if(Sign==8)
		{
			Sleep();//睡觉
		}
		else if(Sign==9)
		{
			Rock();//摇摆
		}
		else if(Sign==10)//跳舞
		{
			dance();
		}
		else if(Sign==11)
		{
			laugh();//笑一个
		}
		else if(Sign==12)
		{
			fierce();//狠一个
		}
		else if(Sign==13)
		{
			pee();//撒尿
		}
		else if(Sign==14)
		{
			cry();//哭泣
		}
		else if(Sign==15)
		{
			Hidden_Action();  //隐藏动作
		}
		delay_ms(10);
	}
}


