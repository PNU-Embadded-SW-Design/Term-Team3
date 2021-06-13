#include "lineTracker.h"
#include "term.h" 

#include <stdio.h> 

extern CAR_STATE gCarState; 
extern CAR_DIR gCarDir; 

/*void EXTI15_10_IRQHandler(){
    OSIntEnter(); 

    if(EXTI_GetITStatus(EXTI_Line12) != RESET) { //magnetic
        EXTI_ClearITPendingBit(EXTI_Line12);
        printf("inside of interrupt2!!\n"); 
		//set_ir_bit(GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_5));
   	EXTI_ClearITPendingBit(EXTI_Line12);
    }
    OSIntExit();
}
*/

void initLineTracker(){
    RCC_MCOConfig(RCC_MCO_SYSCLK);      
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 
    GPIOB->IDR |= R_SENSE; //forLineTracker1
    GPIOB->IDR |= L_SENSE; //forLineTracker2
    
    //why interrupt is not working....? 
    /*
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
    GPIO_InitTypeDef  gpio_init;
    gpio_init.GPIO_Pin = GPIO_Pin_12;
    gpio_init.GPIO_Mode = GPIO_Mode_IPD;
    
    GPIO_Init(GPIOD, &gpio_init);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource12);
    
    EXTI_InitTypeDef EXTI_InitStructure;
    EXTI_InitStructure.EXTI_Line=EXTI_Line12;
    EXTI_InitStructure.EXTI_LineCmd=ENABLE;
    EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Rising_Falling;
    EXTI_Init(&EXTI_InitStructure);
	
    BSP_IntVectSet(BSP_INT_ID_EXTI15_10, EXTI15_10_IRQHandler);
    BSP_IntPrioSet(BSP_INT_ID_EXTI15_10, 1);
    BSP_IntEn(BSP_INT_ID_EXTI15_10);
	
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQChannel;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;

    NVIC_Init(&NVIC_InitStructure);
  */ 
}


CAR_DIR getDirection(){
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

void lineTrackTask(void* parg){
    initLineTracker(); 
    OS_ERR err; 

    while(1){
        gCarDir = getDirection(); 
        //OSTimeDlyHMSM(0, 0, 0, 5, OS_OPT_TIME_HMSM_STRICT, &err);
    }
}
