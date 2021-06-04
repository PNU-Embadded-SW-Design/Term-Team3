#include "lineTracker.h"

int isBlack(){
  if(GPIOE->IDR & GPIO_IDR_IDR13){
    return 0; 
  }
  else
     return 1; 
}


void initLineTracker(){
    RCC_MCOConfig(RCC_MCO_SYSCLK);                              
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE); //portE
    
    GPIOE->IDR |= GPIO_IDR_IDR13; //forLineTracker
}

void lineTrackTask(void* parg){
    initLineTracker(); 
    OS_ERR err; 
  
    while(1){
        if(isBlack()){
            printf("on"); 
            BSP_LED_On(2); 
        }
        else{
            printf("off");
            BSP_LED_Off(2); 
        }
        OSTimeDlyHMSM(0, 0, 1, 0, OS_OPT_TIME_HMSM_STRICT, &err);
    }
}
