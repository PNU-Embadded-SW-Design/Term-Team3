#ifndef DELIVER
#define DELIVER
#include "term.h"
#include "includes.h"

#define DELIVER_TASK_STK_SIZE 128
#define DELIVER_TASK_PRIO 2

static OS_TCB deliver_tcb;
static CPU_STK deliver_stack[DELIVER_TASK_STK_SIZE];

void initDeliver();
void deliverTask(void *parg);

#endif