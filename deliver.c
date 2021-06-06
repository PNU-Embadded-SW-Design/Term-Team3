#include "deliver.h"
void initDeliver(){
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);//timer
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//Alternate Function I/O clock enable
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);//Alternate Function I/O clock enable

    GPIO_InitTypeDef gpio;
    gpio.GPIO_Pin = GPIO_
}
void deliverTask(void* parg){
    while(1){
        if(DELIEVER_STATE == DELIVERABLE){      
            //print lcd
            while(1){
                if(true)//received input (where to go)
                    break;
            }
            while(1){
                if(true)//there is pressure
                    break;
            }
            DELIEVER_STATE = DELIVERING;
        }
        else if(DELIVER_STATE == DELIVERING){
            while(1){
                if(true)//room is found
                    break;
            }
            DELIVRE_STATE = WAITING;
        }
        else if(DELIVER_STATE == WAITING){
            while(1){
                if(true)//there isn't pressure
                    break;
            }

        }
    }
}