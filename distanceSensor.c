#include "distanceSensor.h"
#include "term.h" 

#include <stdio.h> 
extern CAR_STATE gCarState; 
extern CAR_DIR gCarDir; 

void distTask(void* parg){
    initDistSensor(); 
    const int soundSpeed = 34; //34cm/us
    const int stopThreshold = 10000; 
    OS_ERR err;  
    
    while(1){      
        //trigger
        OSSchedLock(&err); 
        GPIO_WriteBit(GPIOB, GPIO_Pin_14, Bit_SET); 
        OSTimeDly(11, OS_OPT_TIME_DLY, &err);  
        GPIO_WriteBit(GPIOB, GPIO_Pin_14, Bit_RESET); 
        //echo 
        while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_15) == Bit_RESET); 
        int count = 0; 
        while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_15) == Bit_SET){
          OSTimeDly(1, OS_OPT_TIME_DLY, &err); 
          count++; 
        }
        OSSchedUnlock(&err); 
        int distance = count * soundSpeed / 2;
        if (distance <= stopThreshold ) {
          gCarState = STOP;
          BSP_LED_On(3);
        }
        else{
          gCarState = GO; 
          BSP_LED_Off(3); 
        }
        
        #ifdef _DEBUG 
        printf("distance = %d cm \n", distance); 
        #endif 
        OSTimeDlyHMSM(0, 0, 0, 5, OS_OPT_TIME_HMSM_STRICT, &err);
    }
}

int initDistSensor(){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //portB
  
    GPIO_InitTypeDef gpio_trig; 
    gpio_trig.GPIO_Pin = GPIO_Pin_14; 
    gpio_trig.GPIO_Speed = GPIO_Speed_50MHz; 
    gpio_trig.GPIO_Mode = GPIO_Mode_Out_PP; //push pull vs drain out  
    GPIO_Init(GPIOB, &gpio_trig); 
    
    GPIO_InitTypeDef gpio_echo; 
    gpio_echo.GPIO_Pin = GPIO_Pin_15;
    gpio_echo.GPIO_Speed = GPIO_Speed_50MHz; 
    gpio_echo.GPIO_Mode = GPIO_Mode_IPD;  //pull down, pull up 
    GPIO_Init(GPIOB, &gpio_echo); 
        
    GPIO_WriteBit(GPIOB, GPIO_Pin_14, Bit_RESET); 
    return 0; 
}