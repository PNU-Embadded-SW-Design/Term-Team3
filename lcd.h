#ifndef __LCD_H_
#define __LCD_H_
#include "includes.h"

#define DEVICE_CODE_NEW_LCD 0x9325

#define POINT_COLOR BLACK
#define BACK_COLOR 0xFFFF

/*--------Color---------------*/
#define WHITE 0xFFFF
#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define MAGENTA 0xF81F
#define GREEN 0x07E0
#define CYAN 0x7FFF
#define YELLOW 0xFFE0
#define BROWN 0XBC40
#define BRRED 0XFC07
#define GRAY 0X8430
#define LGRAY 0XC618

void LCD_Init(void);
void LCD_Clear(u16 Color);
void LCD_Fill(u8 xsta, u16 ysta, u8 xend, u16 yend, u16 colour);

void LCD_SetCursor(u16 Xpos, u16 Ypos);
void LCD_WindowMax(unsigned int x, unsigned int y, unsigned int x_end, unsigned int y_end);

void LCD_DrawPoint(u16 xsta, u16 ysta);
void LCD_DrawLine(u16 xsta, u16 ysta, u16 xend, u16 yend);
void LCD_DrawCircle(u16 x0, u16 y0, u8 r);
void LCD_DrawRectangle(u16 xsta, u16 ysta, u16 xend, u16 yend);

void LCD_ShowChar(u8 x, u16 y, u8 num, u8 size, u16 PenColor, u16 BackColor);
void LCD_ShowCharString(u16 x, u16 y, const u8 *p, u16 PenColor, u16 BackColor);
void LCD_ShowString(u16 x0, u16 y0, u8 *pcStr, u16 PenColor, u16 BackColor);
void LCD_ShowNum(u8 x, u8 y, u32 num, u8 len, u16 PenColor, u16 BackColor);
void LCD_ShowString(u16 x0, u16 y0, u8 *pcStr, u16 PenColor, u16 BackColor);

void LCD_ShowHzString(u16 x0, u16 y0, u8 *pcStr, u16 PenColor, u16 BackColor);
u16 LCD_RGBtoBGR(u16 Color);
void LCD_DrawPicture(u16 StartX, u16 StartY, u16 Xend, u16 Yend, u8 *pic);

#endif
