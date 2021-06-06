#ifndef MOTOR
#define MOTOR

#include "includes.h"

#define MOTOR_TASK_STK_SIZE 128
#define MOTOR_TASK_PRIO 2

static OS_TCB motor_tcb;
static CPU_STK motor_stack[MOTOR_TASK_STK_SIZE];

struct motor{
    GPIO_TypeDef* gpioOne;
    GPIO_TypeDef* gpioTwo;
    u16 pinOne;
    u16 pinTwo;
};

void initMotor();
void motorTask(void* parg);

#endif