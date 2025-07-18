#ifndef _USART_H_
#define _USART_H_

#include "user.h"

#define USART1_REC_LEN   200


extern u8 USART1_Sign;//串口标志，接收到A赋值1，接收到B赋值2

extern u8 USART1_RX_BUF[USART1_REC_LEN];
extern u16 USART1_RX_STA;

void USART1_Init(u32 baud);
void UsartPrintf(USART_TypeDef * USARTx,char * fmt ,...);


#endif
