#include "infrared.h"



u32 hw_jsm;	  //����һ��32λ���ݱ��������������
u8  hw_jsbz;  //����һ��8λ���ݵı���������ָʾ���ձ�־
u32 Infrared_data1;
int Sign = 0;

/*******************************************************************************
* �� �� ��         : Hwjs_Init
* ��������		   : ����˿ڳ�ʼ������	  ʱ�Ӷ˿ڼ��ⲿ�жϳ�ʼ�� 
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void Hwjs_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	/* ����GPIOʱ�Ӽ��ܽŸ���ʱ�� */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_14;//�������
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource14); //ѡ��GPIO�ܽ������ⲿ�ж���·
	EXTI_ClearITPendingBit(EXTI_Line14);
	
	/* �����ⲿ�жϵ�ģʽ */ 
	EXTI_InitStructure.EXTI_Line=EXTI_Line14;
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStructure); 

	/* ����NVIC���� */
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;   //��ȫ���ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //��ռ���ȼ�Ϊ0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; 	 //��Ӧ���ȼ�Ϊ1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;   //ʹ��
	NVIC_Init(&NVIC_InitStructure);

}


/*******************************************************************************
* �� �� ��         : HW_jssj
* ��������		   : �ߵ�ƽ����ʱ�䣬����¼��ʱ�䱣����t�з��أ�����һ�δ�Լ20us 
* ��    ��         : ��
* ��    ��         : t
*******************************************************************************/
u8 HW_jssj()
{
	u8 t=0;
	while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14)==1)//�ߵ�ƽ
	{
		t++;
		delay_us(20);
		if(t>=250) return t;//��ʱ���
	}
	return t;
}

/*******************************************************************************
* �� �� ��         : EXTI15_10_IRQHandler
* ��������		   : �ⲿ�ж�2����
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void EXTI15_10_IRQHandler(void)
{
	u8 Tim=0,Ok=0,Data,Num=0;
	//OLED��ʾ����
	u8 string[10]={0};
	//�����ж�
	while(1)
   {
	   	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14)==1)
		{
			 Tim=HW_jssj();//��ô˴θߵ�ƽʱ��

			 if(Tim>=250) break;//�������õ��ź�

			 if(Tim>=200 && Tim<250)
			 {
			 	Ok=1;//�յ���ʼ�ź�
			 }
			 else if(Tim>=60 && Tim<90)
			 {
			 	Data=1;//�յ����� 1
			 }
			 else if(Tim>=10 && Tim<50)
			 {
			 	Data=0;//�յ����� 0
			 }

			 if(Ok==1)
			 {
			 	hw_jsm<<=1;
				hw_jsm+=Data;

				if(Num>=32)
				{
					hw_jsbz=1;
				  	break;
				}
			 }

			 Num++;
		}
   }

   EXTI_ClearITPendingBit(EXTI_Line14);	
   
   if(hw_jsbz==1)	//���������յ�
	{
		Infrared_data1=0;
		hw_jsbz=0;	   //����
		//printf("��������� %0.8X\r\n",hw_jsm);	//��ӡ
		Infrared_data1=hw_jsm;
		hw_jsm=0;					//����������
		
		//sprintf((char *)string,"%d",Infrared_data1);
		//OLED_ShowString(12,6,string,8);
		//OLED_Update();
		//printf("%d/r/n",Infrared_data1);
		if(Infrared_data1==16718055)Sign=1;//ǰ
		if(Infrared_data1==16730805)Sign=2;//��
		if(Infrared_data1==16716015)Sign=3;//��
		if(Infrared_data1==16734885)Sign=4;//��
		if(Infrared_data1==16726215)Sign=5;//ͣ
		if(Infrared_data1==16738455)Sign=6;//ҡ��
		if(Infrared_data1==16756815)Sign=7;//����
		if(Infrared_data1==16769055)Sign=8;//˯��
		if(Infrared_data1==16748655)Sign=9;//��
	}
}
