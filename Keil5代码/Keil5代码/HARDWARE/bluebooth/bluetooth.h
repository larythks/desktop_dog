#ifndef _BLUETOOTH_H_
#define _BLUETOOTH_H_
#include "user.h"

void USART3_Init(u32 baud);
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch);

#endif
