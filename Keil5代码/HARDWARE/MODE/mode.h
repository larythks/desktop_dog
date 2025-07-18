#ifndef __MODE_H
#define __MODE_H	 
#include "user.h"

extern u16 count;

void SlowStand(void);//缓慢站起
void Stand(void);//站立
void Advance(void);//前进
void Queen(void);//后退
void Left(void);//左转
void Right(void);//右转
void Rock(void);//摇摆
void Sleep(void);//睡觉 
void Sit(void);//坐
void Handshake(void);//握手
void pee(void);//撒尿
void dance(void);//跳舞
void laugh(void);//笑一个
void fierce(void);//凶一个
void roll(void);//走开，我讨厌你
void mode(void);
void Hidden_Action(void);

void For(int x,int y,int num);
		 				    
#endif
