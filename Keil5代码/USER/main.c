#include "user.h"

//����1��־,���յ�A��ֵ1�����յ�B��ֵ2
u8 USART1_Sign = 0;

int Sign = 0;

int main(void)
{	
	u32 i;
	//OLED��ʾ����
  //u8 string[10]={0};
	
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	systick_init(SysTick_CLKSource_HCLK);	    //��ʱ������ʼ��	  
	LED_Init();		  	//��ʼ����LED���ӵ�Ӳ���ӿ�
	USART1_Init(115200);//����1��ʼ��
	USART2_Init(115200);
	USART3_Init(9600);
	OLED_Init();
	OLED_Clear();
	TIM4_CH1_Init(1999,719);//��ǰ
	TIM4_CH2_Init(1999,719);//���
	TIM4_CH3_Init(1999,719);//�Һ�
	TIM4_CH4_Init(1999,719);//�Һ�
	TIM3_CH1_Init(1999,719);//β��
	
	//��ʼ������
	Sleep();
	SlowStand();
	
	while(1)
	{
		if(i%4==0)
		{
			//LED=!LED; //4���˶���һ��
		}
			
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
			//Stand();
			roll();//�߿�
		}
		else if(Sign==15)
		{
			Hidden_Action();  //���ض���
		}
		i++ ;
		delay_ms(10);
	}
}


