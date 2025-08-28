#ifndef __LEG_H
#define __LEG_H	 
#include "sys.h"

void TIM4_CH1_Init(u16 arr,u16 psc);//左前
void TIM4_CH2_Init(u16 arr,u16 psc);//左后
void TIM4_CH3_Init(u16 arr,u16 psc);//右前
void TIM4_CH4_Init(u16 arr,u16 psc);//右后
void TIM3_CH1_Init(u16 arr,u16 psc);//尾巴PA6

#endif
