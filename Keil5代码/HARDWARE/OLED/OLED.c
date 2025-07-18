#include "OLED.h"

/**
  * ���ݴ洢��ʽ��
  * ����8�㣬��λ���£��ȴ����ң��ٴ��ϵ���
  * ÿһ��Bit��Ӧһ�����ص�
  * 
  *      B0 B0                  B0 B0
  *      B1 B1                  B1 B1
  *      B2 B2                  B2 B2
  *      B3 B3  ------------->  B3 B3 --
  *      B4 B4                  B4 B4  |
  *      B5 B5                  B5 B5  |
  *      B6 B6                  B6 B6  |
  *      B7 B7                  B7 B7  |
  *                                    |
  *  -----------------------------------
  *  |   
  *  |   B0 B0                  B0 B0
  *  |   B1 B1                  B1 B1
  *  |   B2 B2                  B2 B2
  *  --> B3 B3  ------------->  B3 B3
  *      B4 B4                  B4 B4
  *      B5 B5                  B5 B5
  *      B6 B6                  B6 B6
  *      B7 B7                  B7 B7
  * 
  * �����ᶨ�壺
  * ���Ͻ�Ϊ(0, 0)��
  * ��������ΪX�ᣬȡֵ��Χ��0~127
  * ��������ΪY�ᣬȡֵ��Χ��0~63
  * 
  *       0             X��           127 
  *      .------------------------------->
  *    0 |
  *      |
  *      |
  *      |
  *  Y�� |
  *      |
  *      |
  *      |
  *   63 |
  *      v
  * 
  */


/*ȫ�ֱ���*********************/

/**
  * OLED�Դ�����
  * ���е���ʾ��������ֻ�ǶԴ��Դ�������ж�д
  * ������OLED_Update������OLED_UpdateArea����
  * �ŻὫ�Դ���������ݷ��͵�OLEDӲ����������ʾ
  */
uint8_t OLED_DisplayBuf[8][128];

/*********************ȫ�ֱ���*/


/*��������*********************/

/**
  * ��    ����OLEDдSCL�ߵ͵�ƽ
  * ��    ����Ҫд��SCL�ĵ�ƽֵ����Χ��0/1
  * �� �� ֵ����
  * ˵    �������ϲ㺯����ҪдSCLʱ���˺����ᱻ����
  *           �û���Ҫ���ݲ��������ֵ����SCL��Ϊ�ߵ�ƽ���ߵ͵�ƽ
  *           ����������0ʱ����SCLΪ�͵�ƽ������������1ʱ����SCLΪ�ߵ�ƽ
  */
void OLED_W_SCL(uint8_t BitValue)
{
	/*����BitValue��ֵ����SCL�øߵ�ƽ���ߵ͵�ƽ*/
	GPIO_WriteBit(GPIOC, GPIO_Pin_14, (BitAction)BitValue);
	
	/*�����Ƭ���ٶȹ��죬���ڴ����������ʱ���Ա��ⳬ��I2Cͨ�ŵ�����ٶ�*/
	//...
}

/**
  * ��    ����OLEDдSDA�ߵ͵�ƽ
  * ��    ����Ҫд��SDA�ĵ�ƽֵ����Χ��0/1
  * �� �� ֵ����
  * ˵    �������ϲ㺯����ҪдSDAʱ���˺����ᱻ����
  *           �û���Ҫ���ݲ��������ֵ����SDA��Ϊ�ߵ�ƽ���ߵ͵�ƽ
  *           ����������0ʱ����SDAΪ�͵�ƽ������������1ʱ����SDAΪ�ߵ�ƽ
  */
void OLED_W_SDA(uint8_t BitValue)
{
	/*����BitValue��ֵ����SDA�øߵ�ƽ���ߵ͵�ƽ*/
	GPIO_WriteBit(GPIOC, GPIO_Pin_15, (BitAction)BitValue);
	
	/*�����Ƭ���ٶȹ��죬���ڴ����������ʱ���Ա��ⳬ��I2Cͨ�ŵ�����ٶ�*/
	//...
}

/**
  * ��    ����OLED���ų�ʼ��
  * ��    ������
  * �� �� ֵ����
  * ˵    �������ϲ㺯����Ҫ��ʼ��ʱ���˺����ᱻ����
  *           �û���Ҫ��SCL��SDA���ų�ʼ��Ϊ��©ģʽ�����ͷ�����
  */
void OLED_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	uint32_t i, j;
	
	/*�ڳ�ʼ��ǰ������������ʱ����OLED�����ȶ�*/
	for (i = 0; i < 1000; i ++)
	{
		for (j = 0; j < 1000; j ++);
	}
	
	/*��SCL��SDA���ų�ʼ��Ϊ��©ģʽ*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
 	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
 	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	/*�ͷ�SCL��SDA*/
	OLED_W_SCL(1);
	OLED_W_SDA(1);
}

/*********************��������*/


/*ͨ��Э��*********************/

/**
  * ��    ����I2C��ʼ
  * ��    ������
  * �� �� ֵ����
  */
void OLED_I2C_Start(void)
{
	OLED_W_SDA(1);		//�ͷ�SDA��ȷ��SDAΪ�ߵ�ƽ
	OLED_W_SCL(1);		//�ͷ�SCL��ȷ��SCLΪ�ߵ�ƽ
	OLED_W_SDA(0);		//��SCL�ߵ�ƽ�ڼ䣬����SDA��������ʼ�ź�
	OLED_W_SCL(0);		//��ʼ���SCLҲ���ͣ���Ϊ��ռ�����ߣ�ҲΪ�˷�������ʱ���ƴ��
}

/**
  * ��    ����I2C��ֹ
  * ��    ������
  * �� �� ֵ����
  */
void OLED_I2C_Stop(void)
{
	OLED_W_SDA(0);		//����SDA��ȷ��SDAΪ�͵�ƽ
	OLED_W_SCL(1);		//�ͷ�SCL��ʹSCL���ָߵ�ƽ
	OLED_W_SDA(1);		//��SCL�ߵ�ƽ�ڼ䣬�ͷ�SDA��������ֹ�ź�
}

/**
  * ��    ����I2C����һ���ֽ�
  * ��    ����Byte Ҫ���͵�һ���ֽ����ݣ���Χ��0x00~0xFF
  * �� �� ֵ����
  */
void OLED_I2C_SendByte(uint8_t Byte)
{
	uint8_t i;
	
	/*ѭ��8�Σ��������η������ݵ�ÿһλ*/
	for (i = 0; i < 8; i++)
	{
		/*ʹ������ķ�ʽȡ��Byte��ָ��һλ���ݲ�д�뵽SDA��*/
		/*����!�������ǣ������з����ֵ��Ϊ1*/
		OLED_W_SDA(!!(Byte & (0x80 >> i)));
		OLED_W_SCL(1);	//�ͷ�SCL���ӻ���SCL�ߵ�ƽ�ڼ��ȡSDA
		OLED_W_SCL(0);	//����SCL��������ʼ������һλ����
	}
	
	OLED_W_SCL(1);		//�����һ��ʱ�ӣ�������Ӧ���ź�
	OLED_W_SCL(0);
}

/**
  * ��    ����OLEDд����
  * ��    ����Command Ҫд�������ֵ����Χ��0x00~0xFF
  * �� �� ֵ����
  */
void OLED_WriteCommand(uint8_t Command)
{
	OLED_I2C_Start();				//I2C��ʼ
	OLED_I2C_SendByte(0x78);		//����OLED��I2C�ӻ���ַ
	OLED_I2C_SendByte(0x00);		//�����ֽڣ���0x00����ʾ����д����
	OLED_I2C_SendByte(Command);		//д��ָ��������
	OLED_I2C_Stop();				//I2C��ֹ
}

/**
  * ��    ����OLEDд����
  * ��    ����Data Ҫд�����ݵ���ʼ��ַ
  * ��    ����Count Ҫд�����ݵ�����
  * �� �� ֵ����
  */
void OLED_WriteData(uint8_t *Data, uint8_t Count)
{
	uint8_t i;
	
	OLED_I2C_Start();				//I2C��ʼ
	OLED_I2C_SendByte(0x78);		//����OLED��I2C�ӻ���ַ
	OLED_I2C_SendByte(0x40);		//�����ֽڣ���0x40����ʾ����д����
	/*ѭ��Count�Σ���������������д��*/
	for (i = 0; i < Count; i ++)
	{
		OLED_I2C_SendByte(Data[i]);	//���η���Data��ÿһ������
	}
	OLED_I2C_Stop();				//I2C��ֹ
}

/*********************ͨ��Э��*/


/*Ӳ������*********************/

/**
  * ��    ����OLED��ʼ��
  * ��    ������
  * �� �� ֵ����
  * ˵    ����ʹ��ǰ����Ҫ���ô˳�ʼ������
  */
void OLED_Init(void)
{
	OLED_GPIO_Init();			//�ȵ��õײ�Ķ˿ڳ�ʼ��
	
	/*д��һϵ�е������OLED���г�ʼ������*/
	OLED_WriteCommand(0xAE);	//������ʾ����/�رգ�0xAE�رգ�0xAF����
	
	OLED_WriteCommand(0xD5);	//������ʾʱ�ӷ�Ƶ��/����Ƶ��
	OLED_WriteCommand(0x80);	//0x00~0xFF
	
	OLED_WriteCommand(0xA8);	//���ö�·������
	OLED_WriteCommand(0x3F);	//0x0E~0x3F
	
	OLED_WriteCommand(0xD3);	//������ʾƫ��
	OLED_WriteCommand(0x00);	//0x00~0x7F
	
	OLED_WriteCommand(0x40);	//������ʾ��ʼ�У�0x40~0x7F
	
	OLED_WriteCommand(0xA1);	//�������ҷ���0xA1������0xA0���ҷ���
	
	OLED_WriteCommand(0xC8);	//�������·���0xC8������0xC0���·���

	OLED_WriteCommand(0xDA);	//����COM����Ӳ������
	OLED_WriteCommand(0x12);
	
	OLED_WriteCommand(0x81);	//���öԱȶ�
	OLED_WriteCommand(0xCF);	//0x00~0xFF

	OLED_WriteCommand(0xD9);	//����Ԥ�������
	OLED_WriteCommand(0xF1);

	OLED_WriteCommand(0xDB);	//����VCOMHȡ��ѡ�񼶱�
	OLED_WriteCommand(0x30);

	OLED_WriteCommand(0xA4);	//����������ʾ��/�ر�

	OLED_WriteCommand(0xA6);	//��������/��ɫ��ʾ��0xA6������0xA7��ɫ

	OLED_WriteCommand(0x8D);	//���ó���
	OLED_WriteCommand(0x14);

	OLED_WriteCommand(0xAF);	//������ʾ
	
	OLED_Clear();				//����Դ�����
	OLED_Update();				//������ʾ����������ֹ��ʼ����δ��ʾ����ʱ����
}

/**
  * ��    ����OLED������ʾ���λ��
  * ��    ����Page ָ��������ڵ�ҳ����Χ��0~7
  * ��    ����X ָ��������ڵ�X�����꣬��Χ��0~127
  * �� �� ֵ����
  * ˵    ����OLEDĬ�ϵ�Y�ᣬֻ��8��BitΪһ��д�룬��1ҳ����8��Y������
  */
void OLED_SetCursor(uint8_t Page, uint8_t X)
{
	/*���ʹ�ô˳�������1.3���OLED��ʾ��������Ҫ�����ע��*/
	/*��Ϊ1.3���OLED����оƬ��SH1106����132��*/
	/*��Ļ����ʼ�н����˵�2�У������ǵ�0��*/
	/*������Ҫ��X��2������������ʾ*/
//	X += 2;
	
	/*ͨ��ָ������ҳ��ַ���е�ַ*/
	OLED_WriteCommand(0xB0 | Page);					//����ҳλ��
	OLED_WriteCommand(0x10 | ((X & 0xF0) >> 4));	//����Xλ�ø�4λ
	OLED_WriteCommand(0x00 | (X & 0x0F));			//����Xλ�õ�4λ
}

/*********************���ߺ���*/


/*���ܺ���*********************/

/**
  * ��    ������OLED�Դ�������µ�OLED��Ļ
  * ��    ������
  * �� �� ֵ����
  * ˵    �������е���ʾ��������ֻ�Ƕ�OLED�Դ�������ж�д
  *           ������OLED_Update������OLED_UpdateArea����
  *           �ŻὫ�Դ���������ݷ��͵�OLEDӲ����������ʾ
  *           �ʵ�����ʾ������Ҫ�������س�������Ļ�ϣ�������ø��º���
  */
void OLED_Update(void)
{
	uint8_t j;
	/*����ÿһҳ*/
	for (j = 0; j < 8; j ++)
	{
		/*���ù��λ��Ϊÿһҳ�ĵ�һ��*/
		OLED_SetCursor(j, 0);
		/*����д��128�����ݣ����Դ����������д�뵽OLEDӲ��*/
		OLED_WriteData(OLED_DisplayBuf[j], 128);
	}
}

/**
  * ��    ������OLED�Դ�����ȫ������
  * ��    ������
  * �� �� ֵ����
  * ˵    �������ô˺�����Ҫ�������س�������Ļ�ϣ�������ø��º���
  */
void OLED_Clear(void)
{
	uint8_t i, j;
	for (j = 0; j < 8; j ++)				//����8ҳ
	{
		for (i = 0; i < 128; i ++)			//����128��
		{
			OLED_DisplayBuf[j][i] = 0x00;	//���Դ���������ȫ������
		}
	}
}

/**
  * ��    ������OLED�Դ����鲿������
  * ��    ����X ָ���������Ͻǵĺ����꣬��Χ��-32768~32767����Ļ����0~127
  * ��    ����Y ָ���������Ͻǵ������꣬��Χ��-32768~32767����Ļ����0~63
  * ��    ����Width ָ������Ŀ�ȣ���Χ��0~128
  * ��    ����Height ָ������ĸ߶ȣ���Χ��0~64
  * �� �� ֵ����
  * ˵    �������ô˺�����Ҫ�������س�������Ļ�ϣ�������ø��º���
  */
void OLED_ClearArea(int16_t X, int16_t Y, uint8_t Width, uint8_t Height)
{
	int16_t i, j;
	
	for (j = Y; j < Y + Height; j ++)		//����ָ��ҳ
	{
		for (i = X; i < X + Width; i ++)	//����ָ����
		{
			if (i >= 0 && i <= 127 && j >=0 && j <= 63)				//������Ļ�����ݲ���ʾ
			{
				OLED_DisplayBuf[j / 8][i] &= ~(0x01 << (j % 8));	//���Դ�����ָ����������
			}
		}
	}
}

/**
  * ��    ����OLED��ʾͼ��
  * ��    ����X ָ��ͼ�����Ͻǵĺ����꣬��Χ��-32768~32767����Ļ����0~127
  * ��    ����Y ָ��ͼ�����Ͻǵ������꣬��Χ��-32768~32767����Ļ����0~63
  * ��    ����Width ָ��ͼ��Ŀ�ȣ���Χ��0~128
  * ��    ����Height ָ��ͼ��ĸ߶ȣ���Χ��0~64
  * ��    ����Image ָ��Ҫ��ʾ��ͼ��
  * �� �� ֵ����
  * ˵    �������ô˺�����Ҫ�������س�������Ļ�ϣ�������ø��º���
  */
void OLED_ShowImage(int16_t X, int16_t Y, uint8_t Width, uint8_t Height, const uint8_t *Image)
{
	uint8_t i = 0, j = 0;
	int16_t Page, Shift;
	
	/*��ͼ�������������*/
	OLED_ClearArea(X, Y, Width, Height);
	
	/*����ָ��ͼ���漰�����ҳ*/
	/*(Height - 1) / 8 + 1��Ŀ����Height / 8������ȡ��*/
	for (j = 0; j < (Height - 1) / 8 + 1; j ++)
	{
		/*����ָ��ͼ���漰�������*/
		for (i = 0; i < Width; i ++)
		{
			if (X + i >= 0 && X + i <= 127)		//������Ļ�����ݲ���ʾ
			{
				/*���������ڼ���ҳ��ַ����λʱ��Ҫ��һ��ƫ��*/
				Page = Y / 8;
				Shift = Y % 8;
				if (Y < 0)
				{
					Page -= 1;
					Shift += 8;
				}
				
				if (Page + j >= 0 && Page + j <= 7)		//������Ļ�����ݲ���ʾ
				{
					/*��ʾͼ���ڵ�ǰҳ������*/
					OLED_DisplayBuf[Page + j][X + i] |= Image[j * Width + i] << (Shift);
				}
				
				if (Page + j + 1 >= 0 && Page + j + 1 <= 7)		//������Ļ�����ݲ���ʾ
				{					
					/*��ʾͼ������һҳ������*/
					OLED_DisplayBuf[Page + j + 1][X + i] |= Image[j * Width + i] >> (8 - Shift);
				}
			}
		}
	}
}
