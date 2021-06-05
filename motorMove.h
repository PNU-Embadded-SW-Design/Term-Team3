#ifndef MOTOR
#define MOTOR

#include "includes.h"

#define MOTOR_TASK_STK_SIZE 128
#define MOTOR_TASK_PRIO 2
#define MOTOR_PORT GPIOE
#define MOTOR_PNUM 3

static OS_TCB motor_tcb;
static CPU_STK motor_stack[MOTOR_TASK_STK_SIZE];

int moveMotor();

#endif