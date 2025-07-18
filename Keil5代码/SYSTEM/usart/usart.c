#include "usart.h"


u8 USART1_RX_BUF[USART1_REC_LEN];
u16 USART1_RX_STA=0;


struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
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
#if SYSTEM_SUPPORT_OS 		//���SYSTEM_SUPPORT_OSΪ�棬����Ҫ֧��OS.
	OSIntEnter();    
#endif
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
		{
			//��������
		Res =USART_ReceiveData(USART1);	//��ȡ���յ�������
		if(Res =='G') USART1_Sign =1;
		if(Res =='K') USART1_Sign =2;
		if(Res =='H') USART1_Sign =3;
		if(Res =='J') USART1_Sign =4;
		if(Res =='I') USART1_Sign =5;
			
		if((USART1_RX_STA&0x8000)==0)//����δ���
			{
			if(USART1_RX_STA&0x4000)//���յ���0x0d
				{
				if(Res!=0x0a)USART1_RX_STA=0;//���մ���,���¿�ʼ
				else USART1_RX_STA|=0x8000;	//��������� 
				}
			else //��û�յ�0X0D
				{	
				if(Res==0x0d)USART1_RX_STA|=0x4000;
				else
					{
					USART1_RX_BUF[USART1_RX_STA&0X3FFF]=Res ;
					USART1_RX_STA++;
					if(USART1_RX_STA>(USART1_RX_STA-1))USART1_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
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
* @brief ���⴮�ڷ��Ͳ��������ֳ�����
* @param ����UsartPrintf(USART3," sdgyasgfuigaiuhuqw");
* @return 
*/

void UsartPrintf(USART_TypeDef * USARTx,char * fmt ,...)
{
	unsigned char UsartPrintfBuf[256]; //����һ���ַ�������
	va_list ap;//��ʼ��ָ������б��ָ��
	unsigned char *pStr = UsartPrintfBuf; //ָ��ָ�������׵�ַ
	
	va_start(ap,fmt);//����һ���ɱ�����ĵ�ַ����ap,��ap ָ��ɱ�����б�Ŀ�ʼ
	vsprintf((char *)UsartPrintfBuf, fmt,ap);
	//������fmt��ap ָ��Ŀɱ����һ��ת���ɸ�ʽ���ַ�������string�����У�����ͬsprintf������ֻ�ǲ������Ͳ�ͬ 

	va_end(ap); //���ָ��
	while(*pStr != 0) //�ж��Ƿ������ַ���
	{
		//while(USART_GetFlagStatus(USART3,USART_FLAG_TC == RESET));//�жϷ��ͱ�־λ���Ƿ��ͽ���
		USART_SendData(USARTx,*pStr++);//ͨ���⺯�������ַ���
		//pStr ++;
		while(USART_GetFlagStatus(USARTx,USART_FLAG_TC) == RESET);//�жϷ��ͱ�־λ���Ƿ��ͽ���
	} 
//	memset(UsartPrintfBuf,0,256);//���һ������
}

