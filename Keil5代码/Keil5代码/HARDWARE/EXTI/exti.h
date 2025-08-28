#ifndef __EXTI_H
#define __EXTI_H	 
#include "sys.h"


void My_EXTI_Init(void);


//定义全局变量
extern u32 hw_jsm;
extern u8  hw_jsbz;
extern u8  frame_cnt;

extern int Sign ;
extern int Infrared_Count;
		 				    
#endif
