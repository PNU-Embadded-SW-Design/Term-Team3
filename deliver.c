#include "deliver.h"
#include "lcd.h"
#include "touch.h"
#include "term.h"
#include <stdio.h>

void initDeliver(){
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);//timer
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//Alternate Function I/O clock enable
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
    
    GPIO_InitTypeDef gpio_press;
    gpio_press.GPIO_Pin = gpio_pin_8;
    gpio_press.GPIO_Mode = GPIO_Mode_AIN;
    gpio_press
    
    
    BSP_LED_On(1);
    LCD_Init();
    Touch_Configuration();
    Touch_Adjust();
    LCD_Clear(WHITE);
    


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