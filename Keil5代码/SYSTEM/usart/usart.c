#include "usart.h"


u8 USART1_RX_BUF[USART1_REC_LEN];
u16 USART1_RX_STA=0;


struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
    USART1->DR = (u8) ch;      
	return ch;
}


void USART1_Init(u32 baud)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	USART_InitStructure.USART_BaudRate=baud;
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_InitStructure.USART_Parity=USART_Parity_No;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_Init(USART1,&USART_InitStructure);
	
	
	NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=3;
	NVIC_Init(&NVIC_InitStructure);
	
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	USART_Cmd(USART1,ENABLE);
}

void USART1_IRQHandler(void)
{
	u8 Res;
#if SYSTEM_SUPPORT_OS 		//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
	OSIntEnter();    
#endif
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
		{
			//蓝牙控制
		Res =USART_ReceiveData(USART1);	//读取接收到的数据
		if(Res =='G') USART1_Sign =1;
		if(Res =='K') USART1_Sign =2;
		if(Res =='H') USART1_Sign =3;
		if(Res =='J') USART1_Sign =4;
		if(Res =='I') USART1_Sign =5;
			
		if((USART1_RX_STA&0x8000)==0)//接收未完成
			{
			if(USART1_RX_STA&0x4000)//接收到了0x0d
				{
				if(Res!=0x0a)USART1_RX_STA=0;//接收错误,重新开始
				else USART1_RX_STA|=0x8000;	//接收完成了 
				}
			else //还没收到0X0D
				{	
				if(Res==0x0d)USART1_RX_STA|=0x4000;
				else
					{
					USART1_RX_BUF[USART1_RX_STA&0X3FFF]=Res ;
					USART1_RX_STA++;
					if(USART1_RX_STA>(USART1_RX_STA-1))USART1_RX_STA=0;//接收数据错误,重新开始接收	  
					}		 
				}
			}   		 
     } 
//	u8 r=0;
//	if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)
//	{
//		r=USART_ReceiveData(USART1);
//		if(r=='A')
//		{
//			USART1_Sign=1;
//			printf("%d\r\n",USART1_Sign);
//		}
//		if(r=='B')
//		{
//			USART1_Sign=2;
//			printf("%d\r\n",USART1_Sign);
//		}
//		if(USART1_RX_STA&0x8000)
//		{
//			if(USART1_RX_STA&0x4000)
//			{
//				if(r!=0x0a)USART1_RX_STA=0;
//				else USART1_RX_STA|=0x8000;
//			}
//			else
//			{
//				if(r==0x0d)USART1_RX_STA|=0x4000;
//				else
//				{
//					USART1_RX_BUF[USART1_RX_STA&0x3fff]=r;
//					USART1_RX_STA++;
//					if(USART1_RX_STA>(USART1_REC_LEN-1))USART1_RX_STA=0;
//				}
//			}
//		}
//	}
}

/**
* @brief 任意串口发送不定类型字长数据
* @param 例：UsartPrintf(USART3," sdgyasgfuigaiuhuqw");
* @return 
*/

void UsartPrintf(USART_TypeDef * USARTx,char * fmt ,...)
{
	unsigned char UsartPrintfBuf[256]; //定义一个字符串数组
	va_list ap;//初始化指向参数列表的指针
	unsigned char *pStr = UsartPrintfBuf; //指针指向数组首地址
	
	va_start(ap,fmt);//将第一个可变参数的地址付给ap,即ap 指向可变参数列表的开始
	vsprintf((char *)UsartPrintfBuf, fmt,ap);
	//将参数fmt、ap 指向的可变参数一起转化成格式化字符串，放string数组中，作用同sprintf（），只是参数类型不同 

	va_end(ap); //清除指针
	while(*pStr != 0) //判断是否发送完字符串
	{
		//while(USART_GetFlagStatus(USART3,USART_FLAG_TC == RESET));//判断发送标志位，是否发送结束
		USART_SendData(USARTx,*pStr++);//通过库函数发送字符串
		//pStr ++;
		while(USART_GetFlagStatus(USARTx,USART_FLAG_TC) == RESET);//判断发送标志位，是否发送结束
	} 
//	memset(UsartPrintfBuf,0,256);//清空一下数组
}

