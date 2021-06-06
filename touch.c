#include "touch.h"
#include "includes.h"
#include "lcd.h"

/************************************
** ADS_Write_Byte :
** SPI Writing
** Write 1 byte data 
************************************/
void ADS_Write_Byte(u8 num)
{
	u8 count = 0;
	for (count = 0; count < 8; count++)
	{
		if (num & 0x80)
			T_DOUT_H;
		else
			T_DOUT_L;
		num <<= 1;
		T_DCLK_L;
		__nop();
		__nop();
		__nop();
		__nop();
		T_DCLK_H;
		__nop();
		__nop();
		__nop();
		__nop();
	}
}

/************************************
** ADS_Read_AD :
** SPI Reading
** Read adc value  
************************************/
u16 ADS_Read_AD(u8 CMD)
{
	u8 i;
	u8 count = 0;
	u16 Num = 0;
	T_DCLK_L;
	T_CS_L;
	ADS_Write_Byte(CMD);
	for (i = 200; i > 0; i--)
		;
	T_DCLK_H;
	__nop();
	__nop();
	__nop();
	__nop();
	T_DCLK_L;
	for (count = 0; count < 16; count++)
	{
		Num <<= 1;
		T_DCLK_L;
		__nop();
		__nop();
		__nop();
		__nop();
		T_DCLK_H;
		__nop();
		__nop();
		if (T_DIN)
			Num++;
	}
	Num >>= 4;
	T_CS_H;
	return (Num);
}

/************************************************************************
** #define : Read a coordinate
** Read data for READ_TIMES times and sort them by ascending order
** Then get rid of the highest and lowest LOST_VAL data and get the mean
************************************************************************/
#define READ_TIMES 15 // Number of times for reading
#define LOST_VAL 5	// Number of data for discarding
u16 ADS_Read_XY(u8 xy)
{
	u16 i, j;
	u16 buf[READ_TIMES];
	u16 sum = 0;
	u16 temp;
	for (i = 0; i < READ_TIMES; i++)
	{
		buf[i] = ADS_Read_AD(xy);
	}
	for (i = 0; i < READ_TIMES - 1; i++)
	{
		for (j = i + 1; j < READ_TIMES; j++)
		{
			if (buf[i] > buf[j])
			{
				temp = buf[i];
				buf[i] = buf[j];
				buf[j] = temp;
			}
		}
	}
	sum = 0;
	for (i = LOST_VAL; i < READ_TIMES - LOST_VAL; i++)
		sum += buf[i];
	temp = sum / (READ_TIMES - 2 * LOST_VAL);
	return temp;
}

/********************************************
** Read_ADSX :
** Coordinate reading with smoothing
** The minimum value could not less than 100 
********************************************/
u8 Read_ADSX(u16 *x)
{
	u16 xtemp;
	xtemp = ADS_Read_XY(0xd0);
	if (xtemp < 100)
		return 0; // Failed to read
	*x = xtemp;

	return 1; // Success
}

/********************************************
** Read_ADSY :
** Coordinate reading with smoothing
** The minimum value could not less than 100 
********************************************/
u8 Read_ADSY(u16 *y)
{
	u16 ytemp;
	ytemp = ADS_Read_XY(0x90);
	if (ytemp < 100)
		return 0; // Failed to read
	*y = ytemp;

	return 1; // Success
}

/************************************************
** Touch_GexX :
** Read effective AD value 2 times continuously
** and the deviation of them should not exceed 50
** otherwise, it means a error 
************************************************/
#define ERR_RANGE 50 // Deviation Range
u8 Touch_GexX(u16 *x, u8 ext)
{
	u16 x1;
	u16 x2;
	u8 flag;

	if (ext)
	{

		while (T_INT)
			;
	}
	flag = Read_ADSX(&x1);
	if (flag == 0)
		return (0);
	flag = Read_ADSX(&x2);
	if (flag == 0)
		return (0);
	if (ext)
	{
		while (!(T_INT))
			;
	}
	if (((x2 <= x1 && x1 < x2 + ERR_RANGE) || (x1 <= x2 && x2 < x1 + ERR_RANGE)))
	{
		*x = (x1 + x2) / 2;
		return 1;
	}
	else
		return 0;
}

/************************************************
** Touch_GexY :
** Read effective AD value 2 times continuously
** and the deviation of them should not exceed 50
** otherwise, it means a error 
************************************************/
u8 Touch_GexY(u16 *y, u8 ext)
{
	u16 y1;
	u16 y2;
	u8 flag;
	if (ext)
	{
		while (T_INT)
			;
	}
	flag = Read_ADSY(&y1);
	if (flag == 0)
		return (0);
	flag = Read_ADSY(&y2);
	if (flag == 0)
		return (0);
	if (ext)
	{
		while (!(T_INT))
			;
	}
	if (((y2 <= y1 && y1 < y2 + ERR_RANGE) || (y1 <= y2 && y2 < y1 + ERR_RANGE)))
	{
		*y = (y1 + y2) / 2;

		return 1;
	}
	else
		return 0;
}

void Touch_GetXY(u16 *x, u16 *y, u8 ext)
{
	if (ext)
	{
		while (T_INT)
			;
	}
	Touch_GexX(x, 0);
	Touch_GexY(y, 0);
	if (ext)
	{
		while (!(T_INT))
			;
	}
}

/* Touch_Configuration */
void Touch_Configuration()
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOB, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_10 | GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}

void Drow_Touch_Point(u16 x, u16 y)
{
	LCD_DrawLine(x - 12, y, x + 13, y);
	LCD_DrawLine(x, y - 12, x, y + 13);
	LCD_DrawPoint(x + 1, y + 1);
	LCD_DrawPoint(x - 1, y + 1);
	LCD_DrawPoint(x + 1, y - 1);
	LCD_DrawPoint(x - 1, y - 1);
	//Draw_Circle(x, y, 6);
}

void Draw_Big_Point(u16 x, u16 y)
{
	LCD_DrawPoint(x, y);
	LCD_DrawPoint(x + 1, y);
	LCD_DrawPoint(x, y + 1);
	LCD_DrawPoint(x + 1, y + 1);
}

/* Refresh Screen(default : WHITE) */
void Refreshes_Screen(void)
{
	LCD_Clear(WHITE);
}

void Convert_Pos(u16 x_in, u16 y_in, u16 *x_out, u16 *y_out)
{
	*x_out = xfac * x_in + xoff;
	*y_out = yfac * y_in + yoff;
}

float xfac;
float yfac;
short xoff;
short yoff;

/************************************************
** Touch_Adjust :
** Code for touch screen calibration
** Get 4 calibration parameters
************************************************/
void Touch_Adjust(void)
{
	u8 i;

	u16 pos_temp[4][2];
	u16 d1, d2;
	u32 tem1, tem2;
	float fac;

	while (1)
	{

		for (i = 0; i < 4; i++)
		{

			Refreshes_Screen();
			if (i == 0)
			{
				Drow_Touch_Point(20, 20);
				Touch_GetXY(&pos_temp[0][0], &pos_temp[0][1], 1);
			}
			else if (i == 1)
			{
				Drow_Touch_Point(220, 20);
				Touch_GetXY(&pos_temp[1][0], &pos_temp[1][1], 1);
			}
			else if (i == 2)
			{
				Drow_Touch_Point(20, 300);
				Touch_GetXY(&pos_temp[2][0], &pos_temp[2][1], 1);
			}
			else
			{

				Drow_Touch_Point(220, 300);
				Touch_GetXY(&pos_temp[3][0], &pos_temp[3][1], 1);
			}
		}

		tem1 = abs(pos_temp[0][0] - pos_temp[1][0]); //x1-x2
		tem2 = abs(pos_temp[0][1] - pos_temp[1][1]); //y1-y2
		tem1 *= tem1;
		tem2 *= tem2;
		d1 = sqrt(tem1 + tem2);

		tem1 = abs(pos_temp[2][0] - pos_temp[3][0]); //x3-x4
		tem2 = abs(pos_temp[2][1] - pos_temp[3][1]); //y3-y4
		tem1 *= tem1;
		tem2 *= tem2;
		d2 = sqrt(tem1 + tem2);
		fac = (float)d1 / d2;
		if (fac < 0.95 || fac > 1.05 || d1 == 0 || d2 == 0)
		{
			continue;
		}
		tem1 = abs(pos_temp[0][0] - pos_temp[2][0]); //x1-x3
		tem2 = abs(pos_temp[0][1] - pos_temp[2][1]); //y1-y3
		tem1 *= tem1;
		tem2 *= tem2;
		d1 = sqrt(tem1 + tem2);

		tem1 = abs(pos_temp[1][0] - pos_temp[3][0]); //x2-x4
		tem2 = abs(pos_temp[1][1] - pos_temp[3][1]); //y2-y4
		tem1 *= tem1;
		tem2 *= tem2;
		d2 = sqrt(tem1 + tem2);
		fac = (float)d1 / d2;
		if (fac < 0.95 || fac > 1.05)
		{
			continue;
		}

		tem1 = abs(pos_temp[1][0] - pos_temp[2][0]); //x1-x3
		tem2 = abs(pos_temp[1][1] - pos_temp[2][1]); //y1-y3
		tem1 *= tem1;
		tem2 *= tem2;
		d1 = sqrt(tem1 + tem2);

		tem1 = abs(pos_temp[0][0] - pos_temp[3][0]); //x2-x4
		tem2 = abs(pos_temp[0][1] - pos_temp[3][1]); //y2-y4
		tem1 *= tem1;
		tem2 *= tem2;
		d2 = sqrt(tem1 + tem2);
		fac = (float)d1 / d2;
		if (fac < 0.95 || fac > 1.05)
		{
			continue;
		}

		xfac = (float)220 / (pos_temp[1][0] - pos_temp[0][0]);
		xoff = (240 - xfac * (pos_temp[1][0] + pos_temp[0][0])) / 2;

		yfac = (float)300 / (pos_temp[2][1] - pos_temp[1][1]);
		yoff = (320 - yfac * (pos_temp[2][1] + pos_temp[1][1])) / 2;

		LCD_Clear(BLACK);
		break;
	}
}
