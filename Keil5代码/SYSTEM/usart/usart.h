#ifndef _USART_H_
#define _USART_H_

#include "user.h"

#define USART1_REC_LEN   200


extern u8 USART1_Sign;//���ڱ�־�����յ�A��ֵ1�����յ�B��ֵ2

extern u8 USART1_RX_BUF[USART1_REC_LEN];
extern u16 USART1_RX_STA;

void USART1_Init(u32 baud);
void UsartPrintf(USART_TypeDef * USARTx,char * fmt ,...);


#endif
