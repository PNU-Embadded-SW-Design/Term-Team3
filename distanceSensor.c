#include "distanceSensor.h"

IR_INFO irInfo; 


void EXTI15_10_IRQHandler(){
  OSIntEnter();
  if(EXTI_GetITStatus(EXTI_Line12) != RESET){
      EXTI_ClearITPendingBit(EXTI_Line12);
      //need to updates 
      //this interrupt is never called :(
      BSP_LED_Toggle(3); 
      /*irInfo.T1 = OS_TS_GET(); 
      while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12) != 0); 
      irInfo.T2 = OS_TS_GET(); 
      irInfo.distance = irInfo.T2 - irInfo.T1; */
    }
  OSIntExit(); 
  
}

void distTask(void* parg){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //portB
    //GPIOB->IDR |= GPIO_IDR_IDR12; //echo
    //GPIOB->ODR |= GPIO_ODR_ODR13; //trigger
  
    GPIO_InitTypeDef gpio_trig; 
    gpio_trig.GPIO_Pin = GPIO_Pin_13; 
    gpio_trig.GPIO_Mode = GPIO_Mode_Out_PP; //puh pull 
    GPIO_Init(GPIOB, &gpio_trig); 
    
    GPIO_InitTypeDef gpio_echo; 
    gpio_echo.GPIO_Pin = GPIO_Pin_12; 
    gpio_echo.GPIO_Mode = GPIO_Mode_IPD;  //pull down, pull up 
    GPIO_Init(GPIOB, &gpio_echo); 
    
    
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource12); 
    
    EXTI_InitTypeDef EXTI_InitStructure; 
    EXTI_InitStructure.EXTI_Line = EXTI_Line12; 
    EXTI_InitStructure.EXTI_LineCmd = ENABLE; 
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt; 
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling; 
    EXTI_Init(&EXTI_InitStructure); 
    
    BSP_IntVectSet(BSP_INT_ID_EXTI15_10, EXTI15_10_IRQHandler); 
    BSP_IntPrioSet(BSP_INT_ID_EXTI15_10, 2); 
    BSP_IntEn(BSP_INT_ID_EXTI15_10); 
    
    NVIC_InitTypeDef NVIC_InitStructure; 
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 
    NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQChannel; 
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; 
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; 
    NVIC_Init(&NVIC_InitStructure); 
    
    OS_ERR err; 
    irInfo.T1 = 0; 
    irInfo.T2 = 0; 
    irInfo.distance = 0; 
    
    while(1){
        //trigger
        GPIO_WriteBit(GPIOB, GPIO_Pin_13, Bit_SET); 
        printf("check\n"); 
        OSTimeDly(20, OS_OPT_TIME_DLY, &err);  //OS_CFG_TICK_RATE_HZ 1000u  -> 2ticks 
        GPIO_WriteBit(GPIOB, GPIO_Pin_13, Bit_RESET); 
        
        BSP_LED_Toggle(1); 
        OSTimeDlyHMSM(0, 0, 1, 0, OS_OPT_TIME_HMSM_STRICT, &err);
    }
}

//static IR_INFO irInfo; 
/*
int initDistSensor(){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //portB
    GPIOB->IDR |= GPIO_IDR_IDR12; //echo
    GPIOB->ODR |= GPIO_ODR_ODR13; //trigger
}

void distTask(void* parg){
  initDistSensor(){
    
  }
} 
*/