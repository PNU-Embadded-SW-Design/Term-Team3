#ifndef MOTOR
#define MOTOR

#include "includes.h"

#define MOTOR_TASK_STK_SIZE 128
#define MOTOR_TASK_PRIO 2

static OS_TCB motor_tcb;
static CPU_STK motor_stack[MOTOR_TASK_STK_SIZE];

<<<<<<< Updated upstream
typedef struct {
    GPIO_TypeDef* gpioOne;
    GPIO_TypeDef* gpioTwo;
=======
struct motor{    
>>>>>>> Stashed changes
    u16 pinOne;
    u16 pinTwo;
}motor;
struct motor motorA[2],motorB[2];
void initMotor();
void motorTask(void* parg);

#endif