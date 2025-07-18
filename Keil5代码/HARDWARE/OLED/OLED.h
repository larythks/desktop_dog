#ifndef __OLED_H
#define __OLED_H

#include "user.h"

/*�����궨��*********************/

/*FontSize����ȡֵ*/
/*�˲���ֵ���������жϣ��������ڼ�������ַ�ƫ�ƣ�Ĭ��ֵΪ�������ؿ��*/
#define OLED_8X16				8
#define OLED_6X8				6

/*IsFilled������ֵ*/
#define OLED_UNFILLED			0
#define OLED_FILLED				1

/*********************�����궨��*/


/*��������*********************/

/*��ʼ������*/
void OLED_Init(void);

/*���º���*/
void OLED_Update(void);

/*�Դ���ƺ���*/
void OLED_Clear(void);
void OLED_ClearArea(int16_t X, int16_t Y, uint8_t Width, uint8_t Height);
void OLED_Reverse(void);
void OLED_ReverseArea(int16_t X, int16_t Y, uint8_t Width, uint8_t Height);

/*��ʾ����*/
void OLED_ShowImage(int16_t X, int16_t Y, uint8_t Width, uint8_t Height, const uint8_t *Image);

/*��ͼ����*/
uint8_t OLED_GetPoint(int16_t X, int16_t Y);

/*********************��������*/

#endif


/*****************��Э�Ƽ�|��Ȩ����****************/
/*****************jiangxiekeji.com*****************/
