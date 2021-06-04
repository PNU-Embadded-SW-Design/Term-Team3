#ifndef DIST
#define DIST

#include "includes.h"

#define DIST_TASK_STK_SIZE 128
#define DIST_TASK_PRIO 2
#define DIST_PORT GPIOB
#define DIST_TRIG 13
#define DIST_ECHO 12

static OS_TCB dist_tcb; 
static CPU_STK dist_stack[DIST_TASK_STK_SIZE]; 

typedef struct{
  int T1; 
  int T2; 
  float distance;  
} IR_INFO; 


/*void initDistSensor(); 
void distTask(void* parg); 
*/

void distTask(void* parg); 
#endif