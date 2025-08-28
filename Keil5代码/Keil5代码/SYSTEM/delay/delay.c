#include "delay.h"

//初始时，默认计数因子是以9MHz进行计数
uint32_t fac_ms = 9000;  //计时因子，每毫秒的计数值
uint32_t fac_us = 9;  //每微秒的计数值

/*
	滴答定时器初始化
	参数：SysTick_CLKSource：时钟源
				可取值：SysTick_CLKSource_HCLK_Div8
								SysTick_CLKSource_HCLK
*/
void systick_init(uint32_t SysTick_CLKSource){
	fac_ms = 9000;
	fac_us = 9;
	//清除寄存器
	SysTick->VAL = SysTick->LOAD = SysTick->CTRL = 0;
	//配置时钟
	if(SysTick_CLKSource == SysTick_CLKSource_HCLK){
		SysTick->CTRL |= 1<<2;  //选择AHB时钟源
		fac_ms = 72000;
		fac_us = 72;
	}
}

//value:0x00ffffff = 16,777,216	滴答定时器单次最大计时约为233ms
/*
	考虑寄存器溢出问题，假设计时5000ms*72000 = 360,000,000
	设置一个计数变量，每当寄存器溢出时-1
*/
void delay_ms(uint32_t ms){
	int count = ms * fac_ms / 0x00ffffff;	//溢出的次数
	uint32_t remain = ms * fac_ms % 0x00ffffff;  //最后一次需要计数的个数
	
	SysTick->VAL = 0;
	SysTick->LOAD = 0x00ffffff;
	SysTick->CTRL &= ~(1<<16 | 0x1);	//清楚标志位，并且关闭滴答定时器
	if(count){
		//启动滴答定时器
		SysTick->CTRL |= 0x1;
		while(count--){
			//等待溢出标志位 
			while(!(SysTick->CTRL & (1<<16))){};
			SysTick->CTRL &= ~(1<<16);
		}
		//关闭滴答定时器，重新设置load的值
		SysTick->CTRL &= ~0x1;
	}
	if(remain){  //还有剩余的数值没有计完
		SysTick->LOAD = remain;
		//启动滴答定时器
		SysTick->CTRL |= 0x1;
		//等待溢出标志位
		while(!(SysTick->CTRL & (1<<16))){};
		SysTick->CTRL &= ~(1<<16 | 0x1);	//清楚标志位，并且关闭滴答定时器
	}
	SysTick->VAL = SysTick->LOAD = 0;
}

//微秒级延时
void delay_us(uint32_t us){
	int count = us * fac_us / 0x00ffffff;	//溢出的次数
	uint32_t remain = us * fac_us % 0x00ffffff;  //最后一次需要计数的个数
	
	SysTick->VAL = 0;
	SysTick->LOAD = us * fac_us;
	SysTick->CTRL &= ~(1<<16 | 0x1);	//清楚标志位，并且关闭滴答定时器
	
	if(count){
		//启动滴答定时器
		SysTick->CTRL |= 0x1;
		while(count--){
			//等待溢出标志位
			while(!(SysTick->CTRL & (1<<16))){};
			SysTick->CTRL &= ~(1<<16);
		}
		//关闭滴答定时器，重新设置load的值
		SysTick->CTRL &= ~0x1;
	}
	if(remain){  //还有剩余的数值没有计完
		SysTick->LOAD = remain;
		//启动滴答定时器
		SysTick->CTRL |= 0x1;
		//等待溢出标志位
		while(!(SysTick->CTRL & (1<<16))){};
		SysTick->CTRL &= ~(1<<16 | 0x1);	//清楚标志位，并且关闭滴答定时器
	}
	SysTick->VAL = SysTick->LOAD = 0;
}








































