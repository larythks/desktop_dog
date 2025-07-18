#include "mode.h"

u16 count=0;//动作延时计数
u16 delay=10;//舵机运动延迟
u16 oled_counter=0;//OLED延时计数

//1号脚--->左前
//2号脚--->右后
//3号脚--->右前
//4号脚--->左后

/**
  * 函    数：动作延时函数
  * 参    数：x是初始值，y是要到达的值，num是通道号
  * 返 回 值：无
  */
void For(int x,int y,int num)
{
	int i,sign;
	if(x>y)sign=1;
	if(y>x)sign=0;
	if(num==1)//通道1
	{
		if(sign==1)
		{
			for(i=x;i>=y;i--)
			{
				TIM_SetCompare1(TIM4,i);
				delay_us(delay);
			}
		}
		else if(sign==0)
		{
			for(i=x;i<=y;i++)
			{
				TIM_SetCompare1(TIM4,i);
				delay_us(delay);
			}
		}
	}
	if(num==2)//通道2
	{
		if(sign==1)
		{
			for(i=x;i>=y;i--)
			{
				TIM_SetCompare2(TIM4,i);
				delay_us(delay);
			}
		}
		else if(sign==0)
		{
			for(i=x;i<=y;i++)
			{
				TIM_SetCompare2(TIM4,i);
				delay_us(delay);
			}
		}
	}
	if(num==3)//通道3
	{
		if(sign==1)
		{
			for(i=x;i>=y;i--)
			{
				TIM_SetCompare3(TIM4,i);
				delay_us(delay);
			}
		}
		else if(sign==0)
		{
			for(i=x;i<=y;i++)
			{
				TIM_SetCompare3(TIM4,i);
				delay_us(delay);
			}
		}
	}
	if(num==4)//通道4
	{
		if(sign==1)
		{
			for(i=x;i>=y;i--)
			{
				TIM_SetCompare4(TIM4,i);
				delay_us(delay);
			}
		}
		else if(sign==0)
		{
			for(i=x;i<=y;i++)
			{
				TIM_SetCompare4(TIM4,i);
				delay_us(delay);
			}
		}
	}
}

void SlowStand(void)
{
	static uint16_t value1 = 2250;
	static uint16_t value2 = 700;
	static uint8_t a = 1;
	static uint8_t b = 1;
	while(1)
	{
		delay_ms(1);
	
	  value1 -= a;
		TIM_SetCompare3(TIM4,(value1/10));
		TIM_SetCompare4(TIM4,(value1/10));	
		
	  value2 += b;
		TIM_SetCompare1(TIM4,(value2/10));
		TIM_SetCompare2(TIM4,(value2/10));	
		if(value2 >= 1500 && value1 <= 1500)
			break;
	}
	OLED_ShowImage(32,0,64,64,BMP11);
	OLED_Update();
	TIM_SetCompare1(TIM4,100);
	TIM_SetCompare3(TIM4,240);
	TIM_SetCompare2(TIM4,100);
	TIM_SetCompare4(TIM4,120);
	delay_ms(200);
	TIM_SetCompare1(TIM4,150);
	TIM_SetCompare3(TIM4,150);
	TIM_SetCompare2(TIM4,150);
	TIM_SetCompare4(TIM4,150);
	OLED_ShowImage(0,0,128,64,BMP1);
	OLED_Update();
}

void Stand(void)//站立
{
	OLED_ShowImage(0,0,128,64,BMP1);
	OLED_Update();
	TIM_SetCompare1(TIM4,150 );//占空比7.5%旋转90度
	TIM_SetCompare2(TIM4,150 );//占空比7.5%旋转90度
	TIM_SetCompare3(TIM4,150 );//占空比7.5%旋转90度
	TIM_SetCompare4(TIM4,150 );//占空比7.5%旋转90度
	
	while(1)
	{
		count++;
		delay_ms(1);
		//较慢的摇尾巴
		static uint16_t value = 150;
		static short  direction = 1;
		
	  value += direction;
    // 到达边界时反转方向
    if (value >= 250) 
		{
			value = 250;    // 防止溢出
			direction = -1;       // 开始减少
    } 
		else if (value <= 50) 
		{
			value = 50;    // 防止下溢
			direction = 1;        // 开始增加
    }
		if(count%2==0)
			TIM_SetCompare1(TIM3,value);
		if(count==600)
		{
			count=0;
			break;
		}
	}
}

void Rock(void)//摇摆
{
	OLED_ShowImage(0,0,128,64,BMP9);
	OLED_Update();
	
	while(1)
	{
		count++;
		delay_ms(1);
		
		static uint16_t value = 150;
		static short  direction = 1;
		
	  value += direction;
    // 到达边界时反转方向
    if (value >= 250) 
		{
			value = 250;    // 防止溢出
			direction = -1;       // 开始减少
    } 
		else if (value <= 50) 
		{
			value = 50;    // 防止下溢
			direction = 1;        // 开始增加
    }
		if(count%2==0)
			TIM_SetCompare1(TIM3,value);
		
		if(count==150)
		{
			For(180,120,1);
			For(120,180,2);
			For(120,180,3);
			For(180,120,4);
		}
		if(count==350)
		{
			For(120,180,1);
			For(180,120,2);
			For(180,120,3);
			For(120,180,4);
		}
		if(count>=370)
		{
			count=0;
			break;
		}
	}
}

void Handshake(void)//握手
{
	OLED_ShowImage(0,0,128,64,BMP16);
	OLED_Update();
	TIM_SetCompare2(TIM4,220 );
	TIM_SetCompare3(TIM4,150 );
	TIM_SetCompare4(TIM4,150 );
	while(1)
	{
		delay_ms(1);
		count++;
		
		static uint16_t value = 150;
		static short  direction = 1;
		
	  value += direction;
    // 到达边界时反转方向
    if (value >= 250) 
		{
			value = 250;    // 防止溢出
			direction = -1;       // 开始减少
    } 
		else if (value <= 50) 
		{
			value = 50;    // 防止下溢
			direction = 1;        // 开始增加
    }
		if(count%2==0)
			TIM_SetCompare1(TIM3,value);
		
		if(count==200)
		{
			For(115,55,1);
		}
		if(count==500)
		{
			For(55,115,1);
		}
		if(count>=550)
		{
			count=0;
			break;
		}
	}
}

void Sleep(void)	//睡觉
{
	OLED_Clear();
	TIM_SetCompare1(TIM4,70 );
	TIM_SetCompare2(TIM4,70 );
	TIM_SetCompare3(TIM4,225 );
	TIM_SetCompare4(TIM4,225 );	
	static uint16_t value = 12000;
	static short  direction = 1;
	
	while(1)
	{
		oled_counter++;
		if(oled_counter==800){
			OLED_ShowImage(32,0,64,64,BMP13_1);
			OLED_Update();
		}
		if(oled_counter==1600){
			OLED_ShowImage(32,0,64,64,BMP13_2);
			OLED_Update();
			oled_counter = 0;
		}
		count++;
		delay_ms(1);
		
	  value += direction;
    // 到达边界时反转方向
    if (value >= 19200) 
			{
        value = 19200;    // 防止溢出
        direction = -1;       // 开始减少
    } 
		else if (value <= 4800) 
			{
        value = 4800;    // 防止下溢
        direction = 1;        // 开始增加
    }
		TIM_SetCompare1(TIM3,(value/80));
		if(count==600)
		{
			count=0;
			break;
		}
	}
}

void Sit(void)//坐
{
	OLED_ShowImage(0,0,128,64,BMP9);
	OLED_Update();
	
	TIM_SetCompare1(TIM4,175);//占空比7.5%旋转90度
	TIM_SetCompare2(TIM4,225);//占空比7.5%旋转90度
	TIM_SetCompare3(TIM4,125);//占空比7.5%旋转90度
	TIM_SetCompare4(TIM4,75);//占空比7.5%旋转90度
	
	while(1)
	{
		count++;
		delay_ms(1);
		static uint16_t value = 150;
		static short  direction = 1;
		
	  value += direction;
    // 到达边界时反转方向
    if (value >= 250) 
		{
			value = 250;    // 防止溢出
			direction = -1;       // 开始减少
    } 
		else if (value <= 50) 
		{
			value = 50;    // 防止下溢
			direction = 1;        // 开始增加
    }
		if(count%2==0)
			TIM_SetCompare1(TIM3,value);
		
		if(count==600)
		{
			count=0;
			break;
		}
	}
}

void Advance(void)//前进
{		
	OLED_ShowImage(0,0,128,64,BMP2);
	OLED_Update();
	
	while(1)
	{
		count++;
		delay_ms(1);
		static uint16_t value = 150;
		static short  direction = 1;
		
	  value += direction;
    // 到达边界时反转方向
    if (value >= 250) 
		{
			value = 250;    // 防止溢出
			direction = -1;       // 开始减少
    } 
		else if (value <= 50) 
		{
			value = 50;    // 防止下溢
			direction = 1;        // 开始增加
    }
		if(count%2==0)
			TIM_SetCompare1(TIM3,value);
		
		if(count==50)//45
		{
			For(150,195,1);
			For(150,105,2);
		}
		if(count==150)//45
		{
			For(105,150,4);
			For(195,150,3);
		}
		if(count==250)//90
		{
			For(195,105,1);
			For(105,195,2);
		}
		if(count==350)//45
		{
			For(150,195,4);
			For(150,105,3);
		}
		if(count==450)//45
		{
			For(105,150,1);
			For(195,150,2);
		}
		if(count==550)//90
		{
			For(195,105,4);
			For(105,195,3);
		}

		if(count>=600)
		{
			count=0;
			break;
		}
	}
}



void Queen(void)//后退
{
	
	OLED_ShowImage(0,0,128,64,BMP2);
	OLED_Update();
	
	while(1)
	{
		count++;
		delay_ms(1);
		
		static uint16_t value = 150;
		static short  direction = 1;
		
	  value += direction;
    // 到达边界时反转方向
    if (value >= 250) 
		{
			value = 250;    // 防止溢出
			direction = -1;       // 开始减少
    } 
		else if (value <= 50) 
		{
			value = 50;    // 防止下溢
			direction = 1;        // 开始增加
    }
		if(count%2==0)
			TIM_SetCompare1(TIM3,value);
		
		if(count==50)//35
		{
			For(150,115,1);
			For(150,185,2);
		}
		if(count==150)//35
		{
			For(185,150,4);
			For(115,150,3);
		}
		if(count==250)//70
		{
			For(115,185,1);
			For(185,115,2);
		}
		if(count==350)//35
		{
			For(150,115,4);
			For(150,185,3);
		}
		if(count==450)//35
		{
			For(185,150,1);
			For(115,150,2);
		}
		if(count==550)//70
		{
			For(115,185,4);
			For(185,115,3);
		}
		if(count>=600)
		{
			count=0;
			break;
		}
	}
}

void Right(void)//右转
{
	OLED_ShowImage(0,0,128,64,BMP3);
	OLED_Update();
	
	while(1)
	{
		count++;
		delay_ms(1);
		
		static uint16_t value = 150;
		static short  direction = 1;
		
	  value += direction;
    // 到达边界时反转方向
    if (value >= 250) 
		{
			value = 250;    // 防止溢出
			direction = -1;       // 开始减少
    } 
		else if (value <= 50) 
		{
			value = 50;    // 防止下溢
			direction = 1;        // 开始增加
    }
		if(count%2==0)
			TIM_SetCompare1(TIM3,value);
		
		if(count==50)
		{
			For(150,105,1);
			For(150,105,2);
		}
		if(count==200)
		{
			For(150,195,4);
			For(150,195,3);
		}
		if(count==350)
		{
			For(105,150,1);
			For(105,150,2);
		}
		if(count==500)
		{
			For(195,150,4);
			For(195,150,3);
		}
		if(count>=550)
		{
			count=0;
			break;
		}
	}
}

void Left(void)//左转
{
	OLED_ShowImage(0,0,128,64,BMP4);
	OLED_Update();

	while(1)
	{
		count++;
		delay_ms(1);
		
		static uint16_t value = 150;
		static short  direction = 1;
		
	  value += direction;
    // 到达边界时反转方向
    if (value >= 250) 
		{
			value = 250;    // 防止溢出
			direction = -1;       // 开始减少
    } 
		else if (value <= 50) 
		{
			value = 50;    // 防止下溢
			direction = 1;        // 开始增加
    }
		if(count%2==0)
			TIM_SetCompare1(TIM3,value);
		

		if(count==50)
		{
			For(150,195,4);
			For(150,195,3);
		}
		if(count==200)
		{
			For(150,105,1);
			For(150,105,2);
		}
		if(count==350)
		{
			For(195,150,4);
			For(195,150,3);
		}
		if(count==500)
		{
			For(105,150,1);
			For(105,150,2);
		}
		if(count>=550)
		{
			count=0;
			break;
		}
	}
}

void pee(void)//撒尿
{
	OLED_ShowImage(0,0,128,64,BMP9);
	OLED_Update();
	TIM_SetCompare1(TIM4,90 );
	TIM_SetCompare3(TIM4,150 );
	TIM_SetCompare4(TIM4,200 );
	
	delay_ms(100);
	TIM_SetCompare2(TIM4,70 );
	
	while(1)
	{
		count++;
		delay_ms(1);
		static uint16_t value = 150;
		static short  direction = 1;
		
	  value += direction;
    // 到达边界时反转方向
    if (value >= 250) 
		{
			value = 250;    // 防止溢出
			direction = -1;       // 开始减少
    } 
		else if (value <= 50) 
		{
			value = 50;    // 防止下溢
			direction = 1;        // 开始增加
    }
		if(count%2==0)
			TIM_SetCompare1(TIM3,value);
		
		if(count==600)
		{
			count=0;
			break;
		}
	}
}

void dance(void)//跳舞
{
	OLED_ShowImage(0,0,128,64,BMP2);
	OLED_Update();

	while(1)
	{
		count++;
		delay_ms(1);
		
		static uint16_t value = 150;
		static short  direction = 1;
		
	  value += direction;
    // 到达边界时反转方向
    if (value >= 250) 
		{
			value = 250;    // 防止溢出
			direction = -1;       // 开始减少
    } 
		else if (value <= 50) 
		{
			value = 50;    // 防止下溢
			direction = 1;        // 开始增加
    }
		if(count%2==0)
			TIM_SetCompare1(TIM3,value);
		
		if(count==50)
		{
			For(150,90,1);
			For(150,90,2);
			For(150,90,3);
			For(150,90,4);
		}
		if(count==200)
		{
			For(90,150,1);
			For(90,150,2);
			For(90,150,3);
			For(90,150,4);
		}
		if(count==350)
		{
			For(150,210,1);
			For(150,210,2);
			For(150,210,3);
			For(150,210,4);
		}
		if(count==500)
		{
			For(210,150,1);
			For(210,150,2);
			For(210,150,3);
			For(210,150,4);
		}
		if(count==650)
		{
			For(150,105,1);
			For(150,195,2);
			For(150,195,3);
			For(150,105,4);
		}
		if(count==800)
		{
			For(105,150,1);
			For(195,150,2);
			For(195,150,3);
			For(105,150,4);
		}
		if(count==950)
		{
			For(150,195,1);
			For(150,105,2);
			For(150,105,3);
			For(150,195,4);
		}
		if(count==1100)
		{
			For(195,150,1);
			For(105,150,2);
			For(105,150,3);
			For(195,150,4);
		}
		if(count==1250)
		{
			For(150,195,1);
			For(150,105,2);
			For(150,105,3);
			For(150,195,4);
		}
		if(count==1400)
		{
			For(195,150,1);
			For(105,150,2);
			For(105,150,3);
			For(195,150,4);
		}
		if(count==1550)
		{
			For(150,105,1);
			For(150,195,2);
			For(150,195,3);
			For(150,105,4);
		}
		if(count==1700)
		{
			For(105,150,1);
			For(195,150,2);
			For(195,150,3);
			For(105,150,4);
		}
		if(count==1850)
		{
			For(150,90,1);
			For(150,90,2);
		}
		if(count==2000)
		{
			For(90,150,1);
			For(90,150,2);
		}
		if(count==2150)
		{
			For(150,210,3);
			For(150,210,4);
		}
		if(count==2300)
		{
			For(210,150,3);
			For(210,150,4);
		}
		if(count>=2350)
		{
			count=0;
			break;
		}
	}
}

void laugh(void)//笑一个
{
	OLED_ShowImage(0,0,128,64,BMP10);
	OLED_Update();
	TIM_SetCompare1(TIM4,50 );
	TIM_SetCompare2(TIM4,190 );
	TIM_SetCompare3(TIM4,250 );
	TIM_SetCompare4(TIM4,110 );
	
	while(1)
	{
		count++;
		delay_ms(1);
		static uint16_t value = 150;
		static short  direction = 1;
		
	  value += direction;
    // 到达边界时反转方向
    if (value >= 250) 
			{
        value = 250;    // 防止溢出
        direction = -1;       // 开始减少
    } 
		else if (value <= 50) 
			{
        value = 50;    // 防止下溢
        direction = 1;        // 开始增加
    }
		if(count%2==0)
				TIM_SetCompare1(TIM3,value);
		
		if(count==600)
		{
			count=0;
			break;
		}
	}
}

void fierce(void)//凶一个
{
	OLED_ShowImage(0,0,128,64,BMP15);
	OLED_Update();
	
	TIM_SetCompare1(TIM4,120 );//占空比7.5%旋转90度
	TIM_SetCompare2(TIM4,120 );//占空比7.5%旋转90度
	TIM_SetCompare3(TIM4,180 );//占空比7.5%旋转90度
	TIM_SetCompare4(TIM4,180 );//占空比7.5%旋转90度
	
	while(1)
	{
		count++;
		delay_ms(1);

		TIM_SetCompare1(TIM3,150);
		
		if(count == 200)
		{
			TIM_SetCompare1(TIM4,190 );//占空比7.5%旋转90度
			TIM_SetCompare2(TIM4,70 );//占空比7.5%旋转90度
			TIM_SetCompare3(TIM4,110 );//占空比7.5%旋转90度
			TIM_SetCompare4(TIM4,230 );//占空比7.5%旋转90度
		}

		if(count == 400)
		{
			TIM_SetCompare1(TIM4,120 );//占空比7.5%旋转90度
			TIM_SetCompare2(TIM4,120 );//占空比7.5%旋转90度
			TIM_SetCompare3(TIM4,180 );//占空比7.5%旋转90度
			TIM_SetCompare4(TIM4,180 );//占空比7.5%旋转90度
		}
		
		if(count==600)
		{
			count=0;
			break;
		}
	}
}

void cry(void)//哭泣
{
	OLED_Clear();
	
	TIM_SetCompare1(TIM4,150 );//占空比7.5%旋转90度
	TIM_SetCompare2(TIM4,150 );//占空比7.5%旋转90度
	TIM_SetCompare3(TIM4,150 );//占空比7.5%旋转90度
	TIM_SetCompare4(TIM4,150 );//占空比7.5%旋转90度
	
	while(1)
	{
		oled_counter++;
		if(oled_counter==400){
			OLED_ShowImage(32,0,64,64,BMP12_1);
			OLED_Update();
		}
		if(oled_counter==800){
			OLED_ShowImage(32,0,64,64,BMP12_2);
			OLED_Update();
			oled_counter = 0;
		}
		count++;
		delay_ms(1);
		static uint16_t value = 150;
		static short  direction = 1;
		
	  value += direction;
    // 到达边界时反转方向
    if (value >= 250) 
		{
			value = 250;    // 防止溢出
			direction = -1;       // 开始减少
    } 
		else if (value <= 50) 
		{
			value = 50;    // 防止下溢
			direction = 1;        // 开始增加
    }
		if(count%2==0)
			TIM_SetCompare1(TIM3,value);
		
		if(count==600)
		{
			count=0;
			break;
		}
	}
}

void Hidden_Action(void){
	OLED_Clear();
	OLED_ShowImage(32,0,64,64,BMP14);
	OLED_Update();
	uint16_t count = 0;
	
	while(1)
	{
		count++;
		TIM_SetCompare1(TIM4,170);
		TIM_SetCompare4(TIM4,230);
		TIM_SetCompare3(TIM4,130);
		TIM_SetCompare2(TIM4,70);	
		
		delay_ms(100);
		TIM_SetCompare1(TIM4,120);
		TIM_SetCompare4(TIM4,180);
		TIM_SetCompare3(TIM4,180);
		TIM_SetCompare2(TIM4,120);	
		delay_ms(100);
		if(count >= 10)
		{
			count = 0;
			break;
		}
	}
}
