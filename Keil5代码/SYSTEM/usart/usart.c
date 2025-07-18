#include "usart.h"

//����һ�����ջ������ͷ��ͻ�����
#define RECIVE_BUF_SIZE		128
uint8_t usart1_recv_buf[RECIVE_BUF_SIZE];
int usart1_rcv_index=0;//����ָ��
int usart1_get_index=0;//��ȡ����ָ��
int usart1_idle_flag=0;//���б�־λ

/*
	PA9---TX
	PA10--RX
*/
void USART1_Init(uint32_t barud){
	GPIO_InitTypeDef gpio_instruct;
	USART_InitTypeDef usart1_instruct;
	NVIC_InitTypeDef nvic_instruct;
	//����ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO|RCC_APB2Periph_USART1, ENABLE);
	//PA9
	gpio_instruct.GPIO_Mode=GPIO_Mode_AF_PP;
	gpio_instruct.GPIO_Pin=GPIO_Pin_9;
	gpio_instruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpio_instruct);
	//PA10
	gpio_instruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	gpio_instruct.GPIO_Pin=GPIO_Pin_10;
	GPIO_Init(GPIOA, &gpio_instruct);
	//��ʼ��USART1
	usart1_instruct.USART_BaudRate=barud;
	usart1_instruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;//Ӳ������
	usart1_instruct.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	usart1_instruct.USART_Parity=USART_Parity_No;
	usart1_instruct.USART_StopBits=USART_StopBits_1;
	usart1_instruct.USART_WordLength=USART_WordLength_8b;
	USART_Init(USART1, &usart1_instruct);
	//����NVIC ��Ϊusart�����ڲ����費��Ҫ�����ⲿ�ж�
	nvic_instruct.NVIC_IRQChannel=USART1_IRQn;
	nvic_instruct.NVIC_IRQChannelCmd=ENABLE;
	nvic_instruct.NVIC_IRQChannelPreemptionPriority=2; //��ռ���ȼ�
	nvic_instruct.NVIC_IRQChannelSubPriority=2;	//��Ӧ���ȼ�
	 NVIC_Init(&nvic_instruct);
	//���ý��ܷǿ��жϡ������ж�
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);
	
	//��������1
	USART_Cmd(USART1, ENABLE);

}
//usart1�жϹ���������
void USART1_IRQHandler(void){
//�ж���ʲôԭ�����ж�
	if(USART_GetITStatus(USART1,USART_IT_RXNE)){
	usart1_recv_buf[usart1_rcv_index]=USART_ReceiveData(USART1);
		usart1_rcv_index++;
		if(usart1_rcv_index>=RECIVE_BUF_SIZE){
			usart1_rcv_index=usart1_get_index=usart1_idle_flag=0;
		}
	}else if(USART_GetITStatus(USART1,USART_IT_IDLE)){
	//������б�־λ  ��Ҫ�ֶ���ȡDR�Ĵ�������־���ܹ������
		USART_ReceiveData(USART1);
		usart1_idle_flag=1;
	}
}

//��������
int send_byte(int data){
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE)==RESET){};
	USART_SendData(USART1, data);
	//�ȴ����ݷ������  TXE=RESET ��ʾ���ݻ�û�з��ͳ�ȥ�������ȴ�   TXE=SET ��ʾ�����Ѿ����ͳ�ȥ�������������
	return data;
}
//��������
int recv_byte(void){
	int data;
	//�ȴ�����
	while(usart1_get_index>=usart1_rcv_index){};
	data=USART_ReceiveData(USART1);
	usart1_get_index++;
	//˵���õ������µ�����
		if(usart1_get_index>=usart1_rcv_index){
		usart1_get_index=usart1_rcv_index=usart1_idle_flag=0;
		}
		send_byte(data);
		return data;
}
// 
int fputc(int data, FILE *f){
	return send_byte(data);
}
int fgetc(FILE *f){
	return recv_byte();
}
