#include "motorMove.h"
//motor B : pe3, pe2

void initMotor(){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE); //portE
    GPIO_InitTypeDef gpio_motor;
    //motor b - 1
    gpio_motor.GPIO_PIN = GPIO_PIN3;
    gpio_motor.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOE,&gpio_motor);
    //motor b-2
    gpio_motor.GPIO_PIN = GPIO_PIN2;
    gpio_motor.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOE,&gpio_motor);

}

int moveMotor(){
    
    return 0;
}