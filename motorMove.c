#include "motorMove.h"
#include "term.h"
//motor B : pe3, pe2

struct motor motorA[2],motorB[2];

void initMotor(){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE); //portE
    GPIO_InitTypeDef gpio_motor;
    
    //motor a front
    motorA[0].pinOne=GPIO_Pin_8;
    motorA[0].pinTwo = GPIO_Pin_9;

    //motor a back    
    motorA[1].pinOne=GPIO_Pin_1;
    motorA[1].pinTwo = GPIO_Pin_2;

    //motor b front
    motorB[0].pinOne=GPIO_Pin_10;
    motorB[0].pinTwo = GPIO_Pin_11;

    //motor b back
    motorB[1].pinOne=GPIO_Pin_3;
    motorB[1].pinTwo = GPIO_Pin_4;

    //gpio_motor.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_2;//1:white,2 : grey
    gpio_motor.GPIO_Pin = motorA[0].pinOne|motorA[0].pinTwo|motorA[1].pinOne|motorA[1].pinTwo;
    gpio_motor.GPIO_Pin |= motorB[0].pinOne|motorB[0].pinTwo|motorB[1].pinOne|motorB[1].pinTwo;
    gpio_motor.GPIO_Mode = GPIO_Mode_Out_PP;
    gpio_motor.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&gpio_motor);

}
// 00 : stop, 10 : go forward, 01 : go backward
void motorTask(void* parg){
    initMotor();
    OS_ERR err; 
    while(1){
        /*if(CAR_STATE == STOP){
            for(int i=0;i<2;i++){
                GPIO_ResetBits(motorA[i].gpioOne,motorA[i].pinOne);
                GPIO_ResetBits(motorA[i].gpioTwo,motorA[i].pinTwo);

                GPIO_ResetBits(motorB[i].gpioOne,motorB[i].pinOne);
                GPIO_ResetBits(motorB[i].gpioTwo,motorB[i].pinTwo);
            }
        }
        else if(CAR_STATE == GO_FORWARD){
            for(int i=0;i<2;i++){
                GPIO_SetBits(motorA[i].gpioOne,motorA[i].pinOne);
                GPIO_ResetBits(motorA[i].gpioTwo,motorA[i].pinTwo);

                GPIO_SetBits(motorB[i].gpioOne,motorB[i].pinOne);
                GPIO_ResetBits(motorB[i].gpioTwo,motorB[i].pinTwo);
            }
        }
        else if(CAR_STATE == GO_LEFT){
            for(int i=0;i<2;i++){
                GPIO_ResetBits(motorA[i].gpioOne,motorA[i].pinOne);
                GPIO_SetBits(motorA[i].gpioTwo,motorA[i].pinTwo);

                GPIO_SetBits(motorB[i].gpioOne,motorB[i].pinOne);
                GPIO_ResetBits(motorB[i].gpioTwo,motorB[i].pinTwo);
            }
        }
        else if(CAR_STATE == GO_RIGHT){
            for(int i=0;i<2;i++){
                GPIO_SetBits(motorA[i].gpioOne,motorA[i].pinOne);
                GPIO_ResetBits(motorA[i].gpioTwo,motorA[i].pinTwo);

                GPIO_ResetBits(motorB[i].gpioOne,motorB[i].pinOne);
                GPIO_SetBits(motorB[i].gpioTwo,motorB[i].pinTwo);
            }
        }
        else{
            printf("CAR_STATE IS WRONG\n");
        }*/ 
    //GPIO_SetBits(GPIOE,GPIO_Pin_2);
     OSTimeDlyHMSM(0, 0, 0, 100, OS_OPT_TIME_HMSM_STRICT, &err);

    }
    
}