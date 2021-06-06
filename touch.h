#ifndef __TOUCH_H__
#define __TOUCH_H__

#define __nop() asm("nop")

#include "includes.h"

extern float xfac;
extern float yfac;
extern short xoff;
extern short yoff;

#define T_DCLK_L GPIOC->BRR = 1 << 10
#define T_DCLK_H GPIOC->BSRR = 1 << 10

#define T_CS_L GPIOC->BRR = 1 << 8
#define T_CS_H GPIOC->BSRR = 1 << 8

#define T_DOUT_L GPIOC->BRR = 1 << 12
#define T_DOUT_H GPIOC->BSRR = 1 << 12

#define T_DIN (1 & ((GPIOC->IDR) >> 11))

#define T_INT (1 & ((GPIOC->IDR) >> 5))

void ADS_Write_Byte(u8 num);
u16 ADS_Read_AD(u8 CMD);
void Touch_Configuration(void);
void Draw_Big_Point(u16 x, u16 y);
u8 Touch_GexX(u16 *y, u8 ext);
u8 Touch_GexY(u16 *y, u8 ext);
void Touch_GetXY(u16 *x, u16 *y, u8 ext);
void Touch_Adjust(void);
void Convert_Pos(u16 x_in, u16 y_in, u16 *x_out, u16 *y_out);

#endif
