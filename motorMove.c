#include "motorMove.h"
#include "term.h"
//motor B : pe3, pe2

struct motor motorA[2],motorB[2];

void initMotor(){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //portE
    GPIO_InitTypeDef gpio_motor;
    
    //motor A front
    motorA[0].pinOne=GPIO_Pin_13;
    motorA[0].pinTwo = GPIO_Pin_12;

    //motor A back    
    motorA[1].pinOne=GPIO_Pin_1;
    motorA[1].pinTwo = GPIO_Pin_2;

    //motor B front
    motorB[0].pinOne=GPIO_Pin_10;
    motorB[0].pinTwo = GPIO_Pin_11;

    //motor B back
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
      
        if( gCarState == STOP){
            for(int i=0;i<2;i++){
                //right : stop
                GPIO_ResetBits(GPIOA,motorA[i].pinOne);
                GPIO_ResetBits(GPIOA,motorA[i].pinTwo);
                //left : stop
                GPIO_ResetBits(GPIOA,motorB[i].pinOne);
                GPIO_ResetBits(GPIOA,motorB[i].pinTwo);
            }
        }
        else if ( gCarState == GO){
            if(gCarDir == FORWARD){
                for(int i=0;i<2;i++){
                    //right : go
                    GPIO_SetBits(GPIOA,motorA[i].pinOne);
                    GPIO_ResetBits(GPIOA,motorA[i].pinTwo);
                    GPIO_WriteBit(GPIOA, motorA[i].pinTwo, Bit_RESET);
                    //left : go
                    GPIO_SetBits(GPIOA,motorB[i].pinOne);
                    GPIO_ResetBits(GPIOA,motorB[i].pinTwo);
                    GPIO_WriteBit(GPIOA, motorB[i].pinTwo, Bit_RESET);
                }
                printf("go forward\n");
            }
            else if (gCarDir ==LEFT){
                for(int i=0;i<2;i++){
                    //right : go
                    GPIO_SetBits(GPIOA,motorA[i].pinOne);
                    GPIO_ResetBits(GPIOA,motorA[i].pinTwo);
                    //left : stop
                    GPIO_ResetBits(GPIOA,motorB[i].pinOne);
                    GPIO_SetBits(GPIOA,motorB[i].pinTwo);
                }
            }
            else if (gCarDir == RIGHT){
                for(int i=0;i<2;i++){
                    //right : back
                    GPIO_ResetBits(GPIOA,motorA[i].pinOne);
                    GPIO_SetBits(GPIOA,motorA[i].pinTwo);
                    //left : go
                    GPIO_SetBits(GPIOA,motorB[i].pinOne);
                    GPIO_ResetBits(GPIOA,motorB[i].pinTwo);
                }
            }
            else printf("WRONG gCarDir\n");
        }
        else printf("WRONG gCarState\n");
    //GPIO_SetBits(GPIOE,GPIO_Pin_2);
     //OSTimeDlyHMSM(0, 0, 0, 100, OS_OPT_TIME_HMSM_STRICT, &err);

    }
    
}