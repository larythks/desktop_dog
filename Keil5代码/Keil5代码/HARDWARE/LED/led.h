#ifndef __LED_H
#define __LED_H	 
#include "user.h"

//����LED�ƵĿ���
#define LED 		PCout(13)
#define LED_OPEN	do{LED = 0;}while(0)
#define LED_CLOSE	do{LED = 1;}while(0)


void LED_Init(void);//��ʼ��



		 				    
#endif
