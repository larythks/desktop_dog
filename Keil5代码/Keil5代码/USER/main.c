#include "user.h"

int Sign = 0;

int main(void)
{	
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	systick_init(SysTick_CLKSource_HCLK);	    //��ʱ������ʼ��	  
	LED_Init();		  	//��ʼ����LED���ӵ�Ӳ���ӿ�
	USART1_Init(115200);//����1��ʼ��
	USART2_Init(115200);//����2��ʼ��������ģ�飩
	USART3_Init(9600);//����3��ʼ��������ģ�飩
	//OLED��ʼ��
	OLED_Init();
	OLED_Clear();
	
	//��ʱ��4ͨ����ʼ����С����֫��
	TIM4_CH1_Init(1999,719);//��ǰ
	TIM4_CH2_Init(1999,719);//�Һ�
	TIM4_CH3_Init(1999,719);//��ǰ
	TIM4_CH4_Init(1999,719);//���
	//��ʱ��3ͨ��1��ʼ����С��β�ͣ�
	TIM3_CH1_Init(1999,719);//β��
	
	OLED_ShowImage(32,0,64,64,BMP13_2);
	OLED_Update();
	
	//��ʼ������
	Sleep();
	SlowStand();
	
	while(1)
	{	
		if(Sign==1)
		{
			Stand();//վ��
		}
		else if(Sign==2)
		{
			Advance();//ǰ��
		}
		else if(Sign==3)
		{
			Queen();//����
		}
		else if(Sign==4)
		{
			Left();//��ת
		}
		else if(Sign==5)
		{
			Right();//��ת
		}
		else if(Sign==6)
		{
			Handshake();//����
		}
		else if(Sign==7)
		{
			Sit();//��
		}
		else if(Sign==8)
		{
			Sleep();//˯��
		}
		else if(Sign==9)
		{
			Rock();//ҡ��
		}
		else if(Sign==10)//����
		{
			dance();
		}
		else if(Sign==11)
		{
			laugh();//Цһ��
		}
		else if(Sign==12)
		{
			fierce();//��һ��
		}
		else if(Sign==13)
		{
			pee();//����
		}
		else if(Sign==14)
		{
			cry();//����
		}
		else if(Sign==15)
		{
			Hidden_Action();  //���ض���
		}
		delay_ms(10);
	}
}


