#include "deliver.h"
#include "lcd.h"
#include "touch.h"
#include "term.h"
#include <stdio.h>

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

int funcNumCheck(uint16_t pixel_x, uint16_t pixel_y){
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
    Touch_Adjust();
    LCD_Clear(WHITE);
    
}
void initDeliever(){
    initLCD();
    const int x=0,y=1;
    int str[2] = {80,70},change[2] = {30,240},exit[2]={140,240}, rec_len[2]={80,40};
    
    LCD_ShowString(str[x], str[y], "NUMBER", BLACK, WHITE);
    LCD_ShowNum(str[x]+70, str[y], num, 1, BLACK, WHITE);
    LCD_DrawRectangle(change[x],change[y], change[x]+rec_len[x],change[y]+rec_len[y]);
    LCD_DrawRectangle(exit[x],exit[y], exit[x]+rec_len[x],exit[y]+rec_len[y]);
    LCD_ShowString(change[x]+5,change[y]+10, "PW CHANGE",BLACK,WHITE);
    LCD_ShowString(exit[x]+25,exit[y]+10, "EXIT",BLACK,WHITE);

}
void deliverTask(void* parg){
    initDeliver();
    while(1){
        if(DELIVER_STATE == DELIVERABLE){      
            //print lcd
            while(1){
                if(1)//received input (where to go)
                    break;
            }
            while(1){
                if(1)//there is pressure
                    break;
            }
            DELIVER_STATE = DELIVERING;
        }
        else if(DELIVER_STATE == DELIVERING){
            while(1){
                if(1)//room is found
                    break;
            }
            DELIVER_STATE = WAITING;
        }
        else if(DELIVER_STATE == WAITING){
            while(1){
                if(1)//there isn't pressure
                    break;
            }

        }
        else{
            printf("hello,there\n");
        }
    }
}