#include "bluetooth.h"

u8 Blue_data[6];
u8 bluetooth_flag = 0;

void USART3_Init(u32 baud)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	USART_InitStructure.USART_BaudRate=baud;
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_InitStructure.USART_Parity=USART_Parity_No;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_Init(USART3,&USART_InitStructure);
	
	
	NVIC_InitStructure.NVIC_IRQChannel=USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=3;
	NVIC_Init(&NVIC_InitStructure);
	
	USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);
	USART_Cmd(USART3,ENABLE);
}


void USART3_IRQHandler(void)
{
	if(USART_GetITStatus(USART3, USART_IT_RXNE)!=RESET)
	{
		LED=!LED;
		Blue_data[0]=USART_ReceiveData(USART3);
		if(Blue_data[0]==0x50){		//P
			Sign=1;//立正
			Usart_SendByte(USART2, 0x41);
		}
		if(Blue_data[0]==0x47){		//G
			Sign=2;//前进
			Usart_SendByte(USART2, 0x42);
		}
		if(Blue_data[0]==0x4B){		//K
			Sign=3;//后退
			Usart_SendByte(USART2, 0x43);
		}
		if(Blue_data[0]==0x48){		//H
			Sign=4;//左转
			Usart_SendByte(USART2, 0x44);
		}
		if(Blue_data[0]==0x4A){		//J
			Sign=5;//右转
			Usart_SendByte(USART2, 0x45);
		}
		if(Blue_data[0]==0x41){		//A
			Sign=12;//凶一个
			Usart_SendByte(USART2, 0x46);
		}
		if(Blue_data[0]==0x42){		//B
			Sign=6;//握手
			Usart_SendByte(USART2, 0x47);
		}
		if(Blue_data[0]==0x46){		//F
			Sign=7;//坐
			Usart_SendByte(USART2, 0x48);
		}
		if(Blue_data[0]==0x4C){		//L
			Sign=8;//睡觉
			Usart_SendByte(USART2, 0x49);
		}
		if(Blue_data[0]==0x4D){		//M
			Sign=11;//伸懒腰
			Usart_SendByte(USART2, 0x4A);
		}
		if(Blue_data[0]==0x5B){
			Sign=15;//隐藏动作
			Usart_SendByte(USART2, 0x5B);  
		}
		if(Blue_data[0]==0x4F){		//O
			if(bluetooth_flag == 0){
				bluetooth_flag = 1;		//已连接蓝牙
				Usart_SendByte(USART2, 0x4E);
			}
			else if(bluetooth_flag == 1){
				bluetooth_flag = 0;		//已断开蓝牙连接
				Usart_SendByte(USART2, 0x4F);
			}
		}
	}
		//  D        I        S         C          O          N          N          E          C          T          E          D
		// 0x44     0x49     0x53      0x43       0x4F			 0x4E			  0x4E			 0x45			  0x43			 0x54			  0x45			 0x44
}

/* 发送一个字节 */
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch)
{
	/* 发送一个字节数据到USART */
	USART_SendData(pUSARTx,ch);
		
	/* 等待发送数据寄存器为空 */
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
	LED = !LED;
}


