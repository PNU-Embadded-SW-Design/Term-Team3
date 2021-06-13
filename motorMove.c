#include "motorMove.h"
#include "term.h"
#include "touch.h"
#include "lcd.h"
//motor B : pe3, pe2
extern CAR_STATE gCarState; 
extern CAR_DIR gCarDir; 

struct motor motorA[2],motorB[2];

void initMotor(){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //portE
    GPIO_InitTypeDef gpio_motor;
    
    //motor A front
    motorA[0].pinOne=GPIO_Pin_9;
    motorA[0].pinTwo = GPIO_Pin_8;

    //motor A back    
    motorA[1].pinOne=GPIO_Pin_0;//잘못되면 go stop 반대
    motorA[1].pinTwo = GPIO_Pin_2;

    //motor B front
    motorB[0].pinOne=GPIO_Pin_10;
    motorB[0].pinTwo = GPIO_Pin_11;

    //motor B back
    motorB[1].pinOne=GPIO_Pin_3;
    motorB[1].pinTwo = GPIO_Pin_4;

    //gpio_motor.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_2;//1:white,2 : grey
    gpio_motor.GPIO_Pin = motorA[1].pinOne|motorA[1].pinTwo|motorA[0].pinOne|motorA[0].pinTwo;
    gpio_motor.GPIO_Pin |= motorB[0].pinOne|motorB[0].pinTwo|motorB[1].pinOne|motorB[1].pinTwo;
    gpio_motor.GPIO_Mode = GPIO_Mode_Out_OD;
    gpio_motor.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&gpio_motor);

}
// 00 : stop, 10 : go forward, 01 : go backward
void motorTask(void* parg){
    initLCD();
    initMotor();
    OS_ERR err; 
    while(1){
      printf("state is %d, direction is %d\n",gCarState,gCarDir);
        if( gCarState == STOP){
            for(int i=0;i<2;i++){
                //right : stop
                //GPIO_WriteBit(GPIOA,motorA[i].pinOne, !i); //reset
                //GPIO_WriteBit(GPIOA,motorA[i].pinTwo, !i); //reset
                GPIO_ResetBits(GPIOA,motorA[i].pinOne);
                GPIO_ResetBits(GPIOA,motorA[i].pinTwo);
                //left : stop
                GPIO_ResetBits(GPIOA,motorB[i].pinOne);
                GPIO_ResetBits(GPIOA,motorB[i].pinTwo);
            }
              printf("CAR STOPPED!\n");
        }
        else if ( gCarState == GO){
            if(gCarDir == FORWARD){
                for(int i=0;i<2;i++){
                    //left : go
                    GPIO_SetBits(GPIOA,motorB[i].pinOne);
                    GPIO_ResetBits(GPIOA,motorB[i].pinTwo);
                    //right : go
                    //GPIO_WriteBit(GPIOA,motorA[i].pinOne, i); //set
                    //GPIO_WriteBit(GPIOA,motorA[i].pinTwo, !i); //reset
                    GPIO_SetBits(GPIOA,motorA[i].pinOne);
                    GPIO_ResetBits(GPIOA,motorA[i].pinTwo);
                }
                printf("CAR GO FORWARD!\n");
            }
            else if (gCarDir ==RIGHT){
                for(int i=0;i<2;i++){
                    //left : stop
                    GPIO_ResetBits(GPIOA,motorB[i].pinOne);
                    GPIO_ResetBits(GPIOA,motorB[i].pinTwo);
                    //right : go
                    GPIO_SetBits(GPIOA,motorA[i].pinOne);
                    GPIO_ResetBits(GPIOA,motorA[i].pinTwo);
                    //GPIO_WriteBit(GPIOA,motorA[i].pinOne, i); //set
                    //GPIO_WriteBit(GPIOA,motorA[i].pinTwo, !i); //reset
                }
                printf("CAR GO LEFT!\n");
            }
            else if (gCarDir == LEFT){
                for(int i=0;i<2;i++){
                    //left : go
                    GPIO_SetBits(GPIOA,motorB[i].pinOne);
                    GPIO_ResetBits(GPIOA,motorB[i].pinTwo);
                    //right : back
                    GPIO_ResetBits(GPIOA,motorA[i].pinOne);
                    GPIO_SetBits(GPIOA,motorA[i].pinTwo);
                    //GPIO_WriteBit(GPIOA,motorA[i].pinOne, !i); //reset
                    //GPIO_WriteBit(GPIOA,motorA[i].pinTwo, i); //set
                }
                printf("CAR GO RIGHT!\n");
            }
            else printf("WRONG gCarDir\n");
        }
        else printf("WRONG gCarState\n");
    //GPIO_SetBits(GPIOE,GPIO_Pin_2);
        OSTimeDlyHMSM(0, 0, 0, 50, OS_OPT_TIME_HMSM_STRICT, &err);

    }
    
}