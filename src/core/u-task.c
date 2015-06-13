 /*
 * Copyright (c) 2015, Universidade Federal de Santa Maria.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file is part of the uFSM real time operating system.
 *
 * Author: Carlos H. Barriquello <barriquello@gmail.com>
 *
 */
/**
 * \file u-task.c
 * System core functions
 * \author
 * Carlos H. Barriquello <barriquello@gmail.com>
 *
 */

#define DEFINE_U_CORE_VARIABLES
#include "ufsm-rtos.h"

/* declaration of variables an functions */
#ifdef DEFINE_U_CORE_VARIABLES
#undef  U_EXTERN
#define U_EXTERN /* nothing */
#else
#undef  U_EXTERN
#define U_EXTERN extern
#endif /* DEFINE_VARIABLES */

/* GLOBAL EXTERNAL variables */
U_EXTERN u08 u_task_priority_list[MAX_NUM_U_TASKS];
U_EXTERN u_prio_list_t u_task_ready_list; /* List of Ready Priorities */
U_EXTERN volatile u08 u_task_curr; /* current utask */
U_EXTERN volatile u08 u_task_next; /* next utask */
U_EXTERN u08 u_task_stack[CONF_U_TASK_STACK_SIZE];	/** stack task */

U_EXTERN const u16 U_TASK_PRIO_MASK[]=
{
  0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0x0100,0x0200,0x0400,0x0800,0x1000,0x2000,0x4000,0x8000
};


/*---------------------------------------------------------------*/
/******************* init ***************/
/* used for initialization of system variables 	*******/

void u_task_init(void)
{
     u08 i;
     for(i=1;i<MAX_NUM_U_TASKS;i++)
     {
       u_task_priority_list[i] = -1;
     }
     u_task_priority_list[0] = 0;  /* for U_idle */
     u_task_ready_list.w[0] = 1;   /* u_idle always ready */
     u_task_next = 0;
     u_task_curr = 0;
     u_task_stack_cnt = 0;
     u_sched_int_nest = 0;
     u_time_init();
}

/*---------------------------------------------------------------*/
/******************* task suspend  ***************/
void u_task_suspend(u_task* u)
{
	 u_assert(u_sched_int_nest == 0); /* can not block inside an ISR */
	 U_EnterCritical();
	 	 RESET_READYLIST_PRIO((u->prio));
	 U_ExitCritical();
}
/*---------------------------------------------------------------*/
/******************* task resume  ***************/
void u_task_resume(prio_t p)
{
	TEST_INT_NESTING(U_EnterCritical(););
	 	 SET_READYLIST_PRIO(p);
	TEST_INT_NESTING(U_ExitCritical(););
}

/******************* idle ***************/
/* this is the lowest priority task */
/* it can be used for background work */
U_TASK(u_task_idle)
{
  CONF_U_TASK_IDLE();
  return;
}

/******************* main task ***************/
/* this is the highest priority task */
/* it can be used for instance to emulate interrupts */
U_TASK(u_task_main)
{
	u_time_tick();
	return;
}
