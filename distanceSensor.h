#ifndef DIST
#define DIST

#include "includes.h"

#define DIST_TASK_STK_SIZE 1024
#define DIST_TASK_PRIO 2
#define DIST_PORT GPIOB
#define DIST_TRIG 14
#define DIST_ECHO 15

static OS_TCB dist_tcb; 
static CPU_STK dist_stack[DIST_TASK_STK_SIZE]; 

void distTask(void* parg); 
#endif