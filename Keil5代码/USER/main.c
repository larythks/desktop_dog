#include "user.h"

//串口1标志,接收到A赋值1，接收到B赋值2
u8 USART1_Sign = 0;

int Sign = 0;

int main(void)
{	
	u32 i;
	//OLED显示数据
  //u8 string[10]={0};
	
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	systick_init(SysTick_CLKSource_HCLK);	    //延时函数初始化	  
	LED_Init();		  	//初始化与LED连接的硬件接口
	USART1_Init(115200);//串口1初始化
	USART2_Init(115200);
	USART3_Init(9600);
	OLED_Init();
	OLED_Clear();
	TIM4_CH1_Init(1999,719);//左前
	TIM4_CH2_Init(1999,719);//左后
	TIM4_CH3_Init(1999,719);//右后
	TIM4_CH4_Init(1999,719);//右后
	TIM3_CH1_Init(1999,719);//尾巴
	
	//初始化动作
	Sleep();
	SlowStand();
	
	while(1)
	{
		if(i%4==0)
		{
			//LED=!LED; //4轮运动闪一次
		}
			
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
			//Stand();
			roll();//走开
		}
		else if(Sign==15)
		{
			Hidden_Action();  //隐藏动作
		}
		i++ ;
		delay_ms(10);
	}
}


