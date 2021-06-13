#include "deliver.h"
#include "lcd.h"
#include "touch.h"
#include "term.h"
#include <stdio.h>
int btn = 0;
u16 cur_x,cur_y,pixel_x,pixel_y;
void showNumberPad(void){
    LCD_DrawRectangle(LCD_REC_X, LCD_REC_Y, LCD_REC_X + LCD_REC_LEN, LCD_REC_Y + LCD_REC_LEN);//1
    LCD_ShowString(LCD_REC_X + 16, LCD_REC_Y + 11, "1", BLACK, WHITE);
    LCD_DrawRectangle(LCD_REC_X + 60, LCD_REC_Y, LCD_REC_X + 60 + LCD_REC_LEN, LCD_REC_Y + LCD_REC_LEN);//2
    LCD_ShowString(LCD_REC_X + 76, LCD_REC_Y + 11, "2", BLACK, WHITE);
    LCD_DrawRectangle(LCD_REC_X + 120, LCD_REC_Y, LCD_REC_X + 120 + LCD_REC_LEN, LCD_REC_Y + LCD_REC_LEN);//3
    LCD_ShowString(LCD_REC_X + 136, LCD_REC_Y + 11, "3", BLACK, WHITE);
    
    LCD_DrawRectangle(LCD_REC_X, LCD_REC_Y + 60, LCD_REC_X + LCD_REC_LEN, LCD_REC_Y + 60 + LCD_REC_LEN);//4
    LCD_ShowString(LCD_REC_X + 16, LCD_REC_Y + 71, "4", BLACK, WHITE);
    LCD_DrawRectangle(LCD_REC_X + 60, LCD_REC_Y + 60, LCD_REC_X + 60 + LCD_REC_LEN, LCD_REC_Y + 60 + LCD_REC_LEN);//5
    LCD_ShowString(LCD_REC_X + 76, LCD_REC_Y + 71, "5", BLACK, WHITE);
    LCD_DrawRectangle(LCD_REC_X + 120, LCD_REC_Y + 60, LCD_REC_X + 120 + LCD_REC_LEN, LCD_REC_Y + 60 + LCD_REC_LEN);//6
    LCD_ShowString(LCD_REC_X + 136, LCD_REC_Y + 71, "6", BLACK, WHITE);
    
    LCD_DrawRectangle(LCD_REC_X, LCD_REC_Y + 120, LCD_REC_X + LCD_REC_LEN, LCD_REC_Y + 120 + LCD_REC_LEN);//7
    LCD_ShowString(LCD_REC_X + 16, LCD_REC_Y + 131, "7", BLACK, WHITE);
    LCD_DrawRectangle(LCD_REC_X + 60, LCD_REC_Y + 120, LCD_REC_X + 60 + LCD_REC_LEN, LCD_REC_Y + 120 + LCD_REC_LEN);//8
    LCD_ShowString(LCD_REC_X + 76, LCD_REC_Y + 131, "8", BLACK, WHITE);
    LCD_DrawRectangle(LCD_REC_X + 120, LCD_REC_Y + 120, LCD_REC_X + 120 + LCD_REC_LEN, LCD_REC_Y + 120 + LCD_REC_LEN);//9
    LCD_ShowString(LCD_REC_X + 136, LCD_REC_Y + 131, "9", BLACK, WHITE);
}

int funcNumCheck(u16 pixel_x,u16 pixel_y){
    int btn = 0;
    if(pixel_x > LCD_REC_X && pixel_x < (LCD_REC_X + LCD_REC_LEN)){ //1
        if(pixel_y > LCD_REC_Y && pixel_y < LCD_REC_Y+LCD_REC_LEN){
            btn = 1;
        }
    }

    else if(pixel_x > (LCD_REC_X + 60) && pixel_x < (LCD_REC_X + 60 + LCD_REC_LEN)){ //2
        if(pixel_y > LCD_REC_Y && pixel_y < LCD_REC_Y+LCD_REC_LEN){
            btn = 2;
        }
    }

    else if(pixel_x > (LCD_REC_X + 120) && pixel_x < (LCD_REC_X + 120 + LCD_REC_LEN)){ //3
        if(pixel_y > LCD_REC_Y && pixel_y < LCD_REC_Y+LCD_REC_LEN){
            btn = 3;
        }
    }

    else if(pixel_x > LCD_REC_X && pixel_x < LCD_REC_X+LCD_REC_LEN){ //4
        if(pixel_y > (LCD_REC_Y + 60) && pixel_y < (LCD_REC_Y + 60 + LCD_REC_LEN)){
            btn = 4;
        }
    }

    else if(pixel_x > (LCD_REC_X  + 60) && pixel_x < (LCD_REC_X + 60 + LCD_REC_LEN)){ //5
        if(pixel_y > (LCD_REC_Y + 60) && pixel_y < (LCD_REC_Y + 60 + LCD_REC_LEN)){
            btn = 5;
        }
    }

    else if(pixel_x > (LCD_REC_X + 120) && pixel_x < (LCD_REC_X + 120 + LCD_REC_LEN)){ //6
        if(pixel_y > (LCD_REC_Y + 60) && pixel_y < (LCD_REC_Y + 60 + LCD_REC_LEN)){
            btn = 6;
        }
    }

    else if(pixel_x > LCD_REC_X && pixel_x < LCD_REC_X+LCD_REC_LEN){ //7
        if(pixel_y > (LCD_REC_Y + 120) && pixel_y < (LCD_REC_Y + 120 + LCD_REC_LEN)){
            btn = 7;
        }
    }

    else if(pixel_x > (LCD_REC_X + 60) && pixel_x < (LCD_REC_X + 60 + LCD_REC_LEN)){ //8
        if(pixel_y > (LCD_REC_Y + 120) && pixel_y < (LCD_REC_Y + 120 + LCD_REC_LEN)){
            btn = 8;
        }
    }

    else if(pixel_x > (LCD_REC_X + 120) && pixel_x < (LCD_REC_X + 120 + LCD_REC_LEN)){ //9
        if(pixel_y > (LCD_REC_Y + 120) && pixel_y < (LCD_REC_Y + 120 + LCD_REC_LEN)){
            btn = 9;
        }
    }
    return btn;
}
void initLCD(){

    BSP_LED_On(1);
    LCD_Init();
    Touch_Configuration();
    //Touch_Adjust();
    LCD_Clear(WHITE);
    
}

void deliverTask(void* parg){
    initLCD();
    const int x=0,y=1;
    int str[2] = {80,70},change[2] = {30,240},exit[2]={140,240}, rec_len[2]={80,40};
    
    LCD_ShowString(str[x], str[y], "Which room?", BLACK, WHITE);
    showNumberPad();
    int num = 5;
    Touch_GetXY(&cur_x, &cur_y, 1);
    Convert_Pos(cur_x, cur_y, &pixel_x, &pixel_y);
    funcNumCheck(pixel_x,pixel_y);
    LCD_Clear(WHITE);
    LCD_ShowNum(str[x],str[y],num,1,BLACK,WHITE);
    
    CPU_TS ts; 
    OS_ERR err; 
    OSTaskSemPend(0, OS_OPT_PEND_BLOCKING, &ts, &err); 
}