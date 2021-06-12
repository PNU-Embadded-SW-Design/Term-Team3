#include "lineTracker.h"
#include <stdio.h> 

/*int isBlack(){
    if(GPIOB->IDR & GPIO_IDR_IDR13){
        return 1; 
    }
    else
        return 0; 
}*/

enum CAR_DIR getDirection(){
    int rightBlack = !(GPIOB->IDR & R_SENSE); 
    int leftBlack = !(GPIOB->IDR & L_SENSE); 
    if(rightBlack && leftBlack){
        #ifdef _DEBUG
        printf("Straight!\n"); 
        #endif 
        return FORWARD; 
    }
    else if( rightBlack && !leftBlack){
        #ifdef _DEBUG
        printf("Left\n"); 
        #endif
        return LEFT; 
    }
    else if ( !rightBlack && leftBlack){
      #ifdef _DEBUG
      printf("Right\n"); 
      #endif
      return RIGHT; 
    }
    #ifdef _DEBUG 
    printf("OutOfWay\n"); 
    #endif
    return RIGHT; 
}


void initLineTracker(){
    RCC_MCOConfig(RCC_MCO_SYSCLK);      
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //portE
    GPIOB->IDR |= R_SENSE; //forLineTracker1
    GPIOB->IDR |= L_SENSE; //forLineTracker2
}

void lineTrackTask(void* parg){
    initLineTracker(); 
    OS_ERR err; 

    while(1){
        gCarDir = getDirection(); 
        /*
        if(isBlack()){
            //printf("on"); 
            BSP_LED_On(2); 
        }
        else{
            //printf("off");
            BSP_LED_Off(2); 
        }*/
        OSTimeDlyHMSM(0, 0, 0, 100, OS_OPT_TIME_HMSM_STRICT, &err);
    }
}
