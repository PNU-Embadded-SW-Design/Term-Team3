#ifndef LINE
#define LINE

#include "includes.h"
#include "term.h" 
#define LINE_TASK_STK_SIZE      1024
#define LINE_TASK_PRIO          2
#define LINE_PORT               GPIOB
#define R_SENSE                 GPIO_IDR_IDR12
#define L_SENSE                 GPIO_IDR_IDR13


static OS_TCB line_tcb; 
static CPU_STK line_stack[LINE_TASK_STK_SIZE]; 


//int isBlack(); 

void initLineTracker(); 
void lineTrackTask(void* parg); 

#endif