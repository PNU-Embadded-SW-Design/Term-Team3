#include <includes.h>
#include "lineTracker.h"
#include "distanceSensor.h" 

static  OS_TCB   AppTaskStartTCB; 
static  CPU_STK  AppTaskStartStk[APP_TASK_START_STK_SIZE];


static  void  AppTaskStart  (void *p_arg);

int  main (void){
    OS_ERR  err;
    BSP_IntDisAll();                                            /* Disable all interrupts.                              */
    OSInit(&err);  
                                             /* Init uC/OS-III.                                      */
    OSTaskCreate((OS_TCB     *)&AppTaskStartTCB,                /* Create the start task                                */
                 (CPU_CHAR   *)"App Task Start",
                 (OS_TASK_PTR )AppTaskStart, 
                 (void       *)0,
                 (OS_PRIO     )1,
                 (CPU_STK    *)&AppTaskStartStk[0],
                 (CPU_STK_SIZE)APP_TASK_START_STK_SIZE / 10,
                 (CPU_STK_SIZE)APP_TASK_START_STK_SIZE,
                 (OS_MSG_QTY  )0,
                 (OS_TICK     )0,
                 (void       *)0,
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR     *)&err
    ); 
    
    OSStart(&err);                                              /* Start multitasking (i.e. give control to uC/OS-III). */
}


static  void  AppTaskStart (void *p_arg)
{
    CPU_INT32U  cpu_clk_freq;
    CPU_INT32U  cnts;
    OS_ERR      err;

   (void)p_arg;
   
    BSP_Init();                                                   /* Initialize BSP functions                         */
    CPU_Init();                                                   /* Initialize the uC/CPU services */   
    BSP_LED_Off(0); 

    cpu_clk_freq = BSP_CPU_ClkFreq();                             /* Determine SysTick reference freq.                */                                                                        
    cnts         = cpu_clk_freq / (CPU_INT32U)OSCfg_TickRate_Hz;  /* Determine nbr SysTick increments                 */
    OS_CPU_SysTickInit(cnts);                                     /* Init uC/OS periodic time src (SysTick).          */
 
    OSTaskCreate((OS_TCB        *) &line_tcb, 
                 (CPU_CHAR      *) "LineTracer", 
                 (OS_TASK_PTR    ) lineTrackTask, 
                 (void          *) 0, //arguements
                 (OS_PRIO        ) LINE_TASK_PRIO, 
                 (CPU_STK       *) &line_stack[0],
                 (CPU_STK_SIZE   ) LINE_TASK_STK_SIZE/10, //stk_limit
                 (CPU_STK_SIZE   ) LINE_TASK_STK_SIZE, 
                 (OS_MSG_QTY     ) 0, 
                 (OS_TICK        ) 0, 
                 (void          *) 0, 
                 (OS_OPT         )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR), 
                 (OS_ERR        *) &err
     ); 
    
     OSTaskCreate((OS_TCB       *) &dist_tcb, 
                 (CPU_CHAR      *) "DistTracer", 
                 (OS_TASK_PTR    ) distTask, 
                 (void          *) 0, //arguements
                 (OS_PRIO        ) DIST_TASK_PRIO, 
                 (CPU_STK       *) &dist_stack[0],
                 (CPU_STK_SIZE   ) DIST_TASK_STK_SIZE/10, //stk_limit
                 (CPU_STK_SIZE   ) DIST_TASK_STK_SIZE, 
                 (OS_MSG_QTY     ) 0, 
                 (OS_TICK        ) 0, 
                 (void          *) 0, 
                 (OS_OPT         )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR), 
                 (OS_ERR        *) &err
     );       
    return; 
}

//need to add echo -> distance measuring task 
