#include "distanceSensor.h"
#include "term.h" 
#include <stdio.h> 

void distTask(void* parg){
    initDistSensor(); 
    const int soundSpeed = 34; //34cm/us
    const int stopThreshold = 40; 
    OS_ERR err;  
    
    while(1){      
        //trigger
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
        
        int distance = count * soundSpeed / 2;
        if (distance <= stopThreshold ) {
          gCarState = STOP; 
          #ifdef _DEBUG 
          BSP_LED_On(3); 
          #endif 
        }
        else{
          gCarState = GO; 
          #ifdef _DEBUG 
          BSP_LED_Off(3); 
          #endif 
        }
        
        #ifdef _DEBUG 
        printf("distance = %d cm \n", distance); 
        #endif 
        OSTimeDlyHMSM(0, 0, 0, 100, OS_OPT_TIME_HMSM_STRICT, &err);
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

    //fucking interrupt is not working...! 
    /*GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource15); 
    
    EXTI_InitTypeDef EXTI_InitStructure; 
    EXTI_InitStructure.EXTI_Line = EXTI_Line15; 
    EXTI_InitStructure.EXTI_LineCmd = ENABLE; 
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt; 
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling; 
    EXTI_Init(&EXTI_InitStructure); 
    
    BSP_IntVectSet(BSP_INT_ID_EXTI15_10, EXTI15_10_IRQHandler); 
    BSP_IntPrioSet(BSP_INT_ID_EXTI15_10, 2); 
    BSP_IntEn(BSP_INT_ID_EXTI15_10); 
    
    NVIC_InitTypeDef NVIC_InitStructure; 
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1); 
    
    NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQChannel; 
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; 
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; 
    NVIC_Init(&NVIC_InitStructure); 
    */
    return 0; 
}

/*void EXTI15_10_IRQHandler(){
  OSIntEnter();
  if(EXTI_GetITStatus(EXTI_Line15) != RESET){
      EXTI_ClearITPendingBit(EXTI_Line15);
      //need to updates 
      //this interrupt is never called :(
      BSP_LED_Toggle(3); 
      printf("I am here!!\n"); 
      irInfo.T1 = OS_TS_GET(); 
      while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12) != 0); 
      irInfo.T2 = OS_TS_GET(); 
      irInfo.distance = irInfo.T2 - irInfo.T1; 
    }
  OSIntExit(); 
  
}*/