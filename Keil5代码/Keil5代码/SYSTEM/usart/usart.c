#include "usart.h"

//设置一个接收缓冲区和发送缓冲区
#define RECIVE_BUF_SIZE		128
uint8_t usart1_recv_buf[RECIVE_BUF_SIZE];
int usart1_rcv_index=0;//接收指针
int usart1_get_index=0;//获取数据指针
int usart1_idle_flag=0;//空闲标志位

/*
	PA9---TX
	PA10--RX
*/
void USART1_Init(uint32_t barud){
	GPIO_InitTypeDef gpio_instruct;
	USART_InitTypeDef usart1_instruct;
	NVIC_InitTypeDef nvic_instruct;
	//开启时钟
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
	//初始化USART1
	usart1_instruct.USART_BaudRate=barud;
	usart1_instruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;//硬件流控
	usart1_instruct.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	usart1_instruct.USART_Parity=USART_Parity_No;
	usart1_instruct.USART_StopBits=USART_StopBits_1;
	usart1_instruct.USART_WordLength=USART_WordLength_8b;
	USART_Init(USART1, &usart1_instruct);
	//配置NVIC 因为usart数据内部外设不需要配置外部中断
	nvic_instruct.NVIC_IRQChannel=USART1_IRQn;
	nvic_instruct.NVIC_IRQChannelCmd=ENABLE;
	nvic_instruct.NVIC_IRQChannelPreemptionPriority=2; //抢占优先级
	nvic_instruct.NVIC_IRQChannelSubPriority=2;	//响应优先级
	 NVIC_Init(&nvic_instruct);
	//设置接受非空中断、空闲中断
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);
	
	//启动串口1
	USART_Cmd(USART1, ENABLE);

}
//usart1中断公共处理函数
void USART1_IRQHandler(void){
//判断是什么原因发生中断
	if(USART_GetITStatus(USART1,USART_IT_RXNE)){
	usart1_recv_buf[usart1_rcv_index]=USART_ReceiveData(USART1);
		usart1_rcv_index++;
		if(usart1_rcv_index>=RECIVE_BUF_SIZE){
			usart1_rcv_index=usart1_get_index=usart1_idle_flag=0;
		}
	}else if(USART_GetITStatus(USART1,USART_IT_IDLE)){
	//清除空闲标志位  需要手动读取DR寄存器，标志才能够被清除
		USART_ReceiveData(USART1);
		usart1_idle_flag=1;
	}
}

//发送数据
int send_byte(int data){
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE)==RESET){};
	USART_SendData(USART1, data);
	//等待数据发送完成  TXE=RESET 表示数据还没有发送出去，继续等待   TXE=SET 表示数据已经发送出去，程序继续运行
	return data;
}
//接收数据
int recv_byte(void){
	int data;
	//等待数据
	while(usart1_get_index>=usart1_rcv_index){};
	data=USART_ReceiveData(USART1);
	usart1_get_index++;
	//说明拿到了最新的数据
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
