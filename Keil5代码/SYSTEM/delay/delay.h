#ifndef __DELAY_H
#define __DELAY_H 			   
#include "user.h"  

void systick_init(uint32_t SysTick_CLKSource);
void delay_ms(uint32_t ms);
void delay_us(uint32_t us);

#endif





























