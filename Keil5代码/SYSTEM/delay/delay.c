#include "delay.h"

//��ʼʱ��Ĭ�ϼ�����������9MHz���м���
uint32_t fac_ms = 9000;  //��ʱ���ӣ�ÿ����ļ���ֵ
uint32_t fac_us = 9;  //ÿ΢��ļ���ֵ

/*
	�δ�ʱ����ʼ��
	������SysTick_CLKSource��ʱ��Դ
				��ȡֵ��SysTick_CLKSource_HCLK_Div8
								SysTick_CLKSource_HCLK
*/
void systick_init(uint32_t SysTick_CLKSource){
	fac_ms = 9000;
	fac_us = 9;
	//����Ĵ���
	SysTick->VAL = SysTick->LOAD = SysTick->CTRL = 0;
	//����ʱ��
	if(SysTick_CLKSource == SysTick_CLKSource_HCLK){
		SysTick->CTRL |= 1<<2;  //ѡ��AHBʱ��Դ
		fac_ms = 72000;
		fac_us = 72;
	}
}

//value:0x00ffffff = 16,777,216	�δ�ʱ����������ʱԼΪ233ms
/*
	���ǼĴ���������⣬�����ʱ5000ms*72000 = 360,000,000
	����һ������������ÿ���Ĵ������ʱ-1
*/
void delay_ms(uint32_t ms){
	int count = ms * fac_ms / 0x00ffffff;	//����Ĵ���
	uint32_t remain = ms * fac_ms % 0x00ffffff;  //���һ����Ҫ�����ĸ���
	
	SysTick->VAL = 0;
	SysTick->LOAD = 0x00ffffff;
	SysTick->CTRL &= ~(1<<16 | 0x1);	//�����־λ�����ҹرյδ�ʱ��
	if(count){
		//�����δ�ʱ��
		SysTick->CTRL |= 0x1;
		while(count--){
			//�ȴ������־λ 
			while(!(SysTick->CTRL & (1<<16))){};
			SysTick->CTRL &= ~(1<<16);
		}
		//�رյδ�ʱ������������load��ֵ
		SysTick->CTRL &= ~0x1;
	}
	if(remain){  //����ʣ�����ֵû�м���
		SysTick->LOAD = remain;
		//�����δ�ʱ��
		SysTick->CTRL |= 0x1;
		//�ȴ������־λ
		while(!(SysTick->CTRL & (1<<16))){};
		SysTick->CTRL &= ~(1<<16 | 0x1);	//�����־λ�����ҹرյδ�ʱ��
	}
	SysTick->VAL = SysTick->LOAD = 0;
}

//΢�뼶��ʱ
void delay_us(uint32_t us){
	int count = us * fac_us / 0x00ffffff;	//����Ĵ���
	uint32_t remain = us * fac_us % 0x00ffffff;  //���һ����Ҫ�����ĸ���
	
	SysTick->VAL = 0;
	SysTick->LOAD = us * fac_us;
	SysTick->CTRL &= ~(1<<16 | 0x1);	//�����־λ�����ҹرյδ�ʱ��
	
	if(count){
		//�����δ�ʱ��
		SysTick->CTRL |= 0x1;
		while(count--){
			//�ȴ������־λ
			while(!(SysTick->CTRL & (1<<16))){};
			SysTick->CTRL &= ~(1<<16);
		}
		//�رյδ�ʱ������������load��ֵ
		SysTick->CTRL &= ~0x1;
	}
	if(remain){  //����ʣ�����ֵû�м���
		SysTick->LOAD = remain;
		//�����δ�ʱ��
		SysTick->CTRL |= 0x1;
		//�ȴ������־λ
		while(!(SysTick->CTRL & (1<<16))){};
		SysTick->CTRL &= ~(1<<16 | 0x1);	//�����־λ�����ҹرյδ�ʱ��
	}
	SysTick->VAL = SysTick->LOAD = 0;
}








































