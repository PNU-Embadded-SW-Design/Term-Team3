#ifndef DELIVER
#define DELIVER
#include "term.h"
#include "includes.h"

#define DELIVER_TASK_STK_SIZE 128
#define DELIVER_TASK_PRIO 2

static OS_TCB deliver_tcb;
static CPU_STK deliver_stack[DELIVER_TASK_STK_SIZE];

#define LCD_TEAM_NAME_X 40
#define LCD_TEAM_NAME_Y 50
#define LCD_ON_X 40
#define LCD_ON_Y 70
#define LCD_REC_X 40
#define LCD_REC_Y 120
#define LCD_REC_LEN 40
#define LCD_BUT_X 70
#define LCD_BUT_Y 120
#define LCD_COUNT_X 40
#define LCD_COUNT_Y 240


void initDeliver();
void deliverTask(void *parg);

#endif