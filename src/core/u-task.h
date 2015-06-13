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
 * \file u-task.h
 * System task manager functions
 * \author
 * Carlos H. Barriquello <barriquello@gmail.com>
 *
 */

#ifndef __U_TASK_H__
#define __U_TASK_H__

#include "lc.h"
#include "u-config.h"
#include "u-assert.h"

#include <string.h>

#if U_DEBUG_PRINTF == 1
#include <stdio.h>
#define U_PRINTF(...)	printf(__VA_ARGS__); fflush(stdout);
#else
#define U_PRINTF(...)	do{}while(0);
#endif


#ifndef NULL
#define NULL  (void*)0
#endif

/*******************************/ 
typedef u16 lc_t;
typedef u08 prio_t;

typedef enum{
	EV_NONE,EV_WAIT,EV_TIMER,EV_SEM,EV_MUTEX,EV_MSG
} u_event_t;

typedef struct {
  u08*	top;
  u16   size;
} u_stack;

typedef struct
{
    u16    	   timeout;
    u08 	   u_id;
}u_timer_t;

typedef struct {
  lc_t 		 lc;  /* local continuation */
  prio_t 	 prio;	/* priority */
  u_timer_t	 tmr;	/* built-in timer */
  u_event_t  evt;	/* built-in event */
  u08		 ecnt;	/* built-in semaphore */
  u_stack    stk;	/* built-in stack */
} u_task;

typedef union
{
	 u16 w[2];
	 u08 b[4];
	 u32 dw;
}u32_t;

typedef u32_t u_prio_list_t;


typedef void (*u_task_ptr)(void);

typedef u_task*  u_task_arg;


typedef struct{
    u_task_ptr ptr;
    u_task_arg arg;
}u_tcb;

#define MAX_NUM_U_TASKS            (sizeof(u_prio_list_t)*8)
#define MAX_PRIO            	   (MAX_NUM_U_TASKS-1)
#define MAX_ID            		   (MAX_NUM_U_TASKS-1)
#define MUTEX_PRIO      	       ((u08)(-2))

#define U_INIT()				   u_task_init();
#define U_SCHEDULER()         	   u_task_next = u_task_priority_list[u_sched(u_task_ready_list)]

#if 0
#define SET_READYLIST_PRIO(p)       u_task_ready_list |= U_TASK_PRIO_MASK[(p)]
#define RESET_READYLIST_PRIO(p)     u_task_ready_list &= ~U_TASK_PRIO_MASK[(p)]

#define SET_READYLIST(u,s)    	 	SET_READYLIST_PRIO(u_sched((s)->waitlist))
#define RESET_READYLIST(u,s)     	RESET_READYLIST_PRIO((u)->prio)

#define SET_WAITLIST(u,s)     		(s)->waitlist |= U_TASK_PRIO_MASK[(u)->prio]
#define RESET_WAITLIST(u,s)   		(s)->waitlist &= ~U_TASK_PRIO_MASK[u_sched((s)->waitlist)]
#else

#define SET_READYLIST_PRIO(p)       if((p)>0x0F){u_task_ready_list.w[1] |= U_TASK_PRIO_MASK[(p) - 16];} \
									else{u_task_ready_list.w[0] |= U_TASK_PRIO_MASK[(p)];}

#define RESET_READYLIST_PRIO(p)     if((p)>0x0F){u_task_ready_list.w[1] &= ~U_TASK_PRIO_MASK[(p) - 16]; } \
									else{u_task_ready_list.w[0] &= ~U_TASK_PRIO_MASK[(p)];};

#define SET_READYLIST(u,s)    	 	SET_READYLIST_PRIO(u_sched((s)->waitlist))
#define RESET_READYLIST(u,s)     	RESET_READYLIST_PRIO((u)->prio)

#define SET_WAITLIST(u,s)     		if(((u)->prio)>0x0F){(s)->waitlist.w[1] |= U_TASK_PRIO_MASK[((u)->prio) - 16];} \
									else{(s)->waitlist.w[0] |= U_TASK_PRIO_MASK[(u)->prio];}

#define RESET_WAITLIST(u,s)   		if(((u)->prio)>0x0F){(s)->waitlist.w[1] &= ~U_TASK_PRIO_MASK[(u_sched((s)->waitlist)) - 16];} \
									else{(s)->waitlist.w[0] &= ~U_TASK_PRIO_MASK[u_sched((s)->waitlist)];}\

#endif

#define EVENT_PEND(u,s)       		RESET_READYLIST((u),(s)); SET_WAITLIST((u),(s));
#define EVENT_POST(u,s)       		SET_READYLIST((u),(s)); RESET_WAITLIST((u),(s));

#define U_LOOP_FOREVER()      	   for(;;)                               \
								   {                                    \
									 u_task_curr = u_task_next;                   \
									 (void) U_TCB[u_task_curr].ptr(); 		\
									 u_task_main();						\
								   }
                              
#define U_RUN()            	   U_EnterCritical();                       \
                               U_SCHEDULER();                           \
                               U_ExitCritical();                        \
                               U_LOOP_FOREVER();


/* extensions for lc libray (implemented in "lc.h") */

#define U_TASK_BEGIN_EXT(u)    u_task *(u) = (U_TCB[u_task_curr].arg);

#define U_TASK_END_EXT()       U_EnterCritical();                     \
                               RESET_READYLIST(u,s); U_SCHEDULER();   \
                               U_ExitCritical();

#define U_TASK_INIT_EXT(u,p,s,z)   STATIC_ASSERT((p > 0));              \
								   STATIC_ASSERT(p <= MAX_PRIO);      \
								   u_assert(u_task_priority_list[p] == (u08)(-1));   \
								   u_task_priority_list[p] = ++u_task_curr;           \
								   (u)->prio = p; 							 \
								   if(s) {SET_READYLIST_PRIO(p);}	 			\
								   if(z) { (u)->stk.top = &u_task_stack[u_task_stack_cnt];  \
								   	   	   (u)->stk.size = 0; u_task_stack_cnt += z; } \
								   u_assert(u_task_stack_cnt <= CONF_U_TASK_STACK_SIZE);   \



#define U_TASK_WAIT_UNTIL(u, cond)	  do { LC_SET((u)->lc);		\
										if(!(cond)) {return;}   \
									  } while(0)

#define U_TASK_INFO(name)  u08 name##_id(u08 id)	\
{ static u08 u_id = 0; if(id != 0) {u_id = id;} return u_id; }

#define U_TASK(name) 			U_TASK_INFO(name) void name(void)
#define U_TASK_INIT(n,u,p,s,z) 	U_TASK_INIT_EXT(u,p,s,z); n##_id(u_task_curr); LC_INIT((u)->lc);
#define U_BEGIN()				U_TASK_BEGIN_EXT(u); { LC_RESUME((u)->lc)
#define U_END()					LC_END((u)->lc); U_TASK_END_EXT(); LC_INIT((u)->lc); return;}
#define U_WAIT_UNTIL 			U_TASK_WAIT_UNTIL

#define U_START		    		1
#define U_NO_START				0

#define U_GET_TASK_ID(name) 		(name##_id)(0)



/**
 * "Preemption point" for the utask.
 *
 * This macro causes the utask to try to switch to another utask.
 * If the current utask has been switched to another utask,
 * that utask will continue to run.
 *
 * \param u A pointer to the utask control structure.
 *
 * \hideinitializer
 */
#define U_PREEMP_POINT(u)  	U_WAIT_UNTIL(u, u_task_curr == u_task_next)


#define U_INT_ENTER()   	u_sched_int_nest++;

#define U_INT_EXIT()    	U_EnterCritical(); u_sched_int_nest--; \
                        	if(u_sched_int_nest == 0) U_SCHEDULER();

/* macros for interrupt nesting */                        
#if CONF_U_CORE_INT_NEST_ENABLE == 0
#define TEST_INT_NESTING(instr)   if(!u_sched_int_nest){instr;}
#define U_NESTING_ENABLE()
#else
#define TEST_INT_NESTING(instr)   instr;
#define U_NESTING_ENABLE()   	  U_Enable_Nesting()
#endif  

#define U_TASK_GET(id)				(U_TCB[(id)].arg)
#define U_TASK_GET_PRIO(id)			(((u_task *)(U_TCB[(id)].arg))->prio)

#define U_TASK_SUSPEND() 	                  \
		u_task_suspend(u);                      \
        U_EnterCritical();                    \
        U_SCHEDULER();                        \
        U_ExitCritical();                     \
        U_PREEMP_POINT(u);

#define U_TASK_SUSPEND_ID(id)                 \
		U_TASK_SUSPEND(U_GET_TASK_ID(id));

#define U_TASK_RESUME_PRIO(p) 	             \
		u_task_resume(p);                      \
		TEST_INT_NESTING(U_EnterCritical()); \
        U_SCHEDULER();                       \
        TEST_INT_NESTING(U_ExitCritical());  \
        U_PREEMP_POINT(u);

#define U_TASK_RESUME_ID(id)                 \
		U_TASK_RESUME_PRIO((U_TASK_GET_PRIO(id)));

#define U_TASK_RESUME(name)		U_TASK_RESUME_ID((U_GET_TASK_ID(name)))

#define U_TASK_RESUME_PRIO_FROM_CB(p) 	     \
		u_task_resume(p);                      \

#define U_TASK_RESUME_ID_FROM_CB(id)          \
		U_TASK_RESUME_PRIO_FROM_CB((U_TASK_GET_PRIO(id)));

#define U_TASK_RESUME_FROM_CB(name)		U_TASK_RESUME_ID_FROM_CB((U_GET_TASK_ID(name)))

#define U_PUSH(u,v,s)		do{memcpy((u)->stk.top, &(v),s); (u)->stk.top+=s; (u)->stk.size += s;}while(0);
#define U_POP(u,v,s)		do{(u)->stk.top-=s; memcpy(&(v),(u)->stk.top,(s));  (u)->stk.size-=s;}while(0);

#define PUSH(v)		 U_PUSH(u,v,sizeof(v))
#define POP(v)		 U_POP(u,v,sizeof(v))

#define U_TASK_DELAY(t)	                        \
		Timer_Pend(u,&((u)->tmr),t)             \
        U_EnterCritical();                    	\
        U_SCHEDULER();                          \
        U_ExitCritical();                     	\
        U_PREEMP_POINT(u);


/* declaration of variables an functions */
#ifdef DEFINE_U_CORE_VARIABLES
#undef  U_EXTERN
#define U_EXTERN /* nothing */
#else
#undef  U_EXTERN
#define U_EXTERN extern
#endif /* DEFINE_VARIABLES */

/* extern variables */
U_EXTERN u08 u_task_stack[CONF_U_TASK_STACK_SIZE];
U_EXTERN const u_tcb U_TCB[];
U_EXTERN u_prio_list_t u_task_ready_list; /* ReadyList */
U_EXTERN u08 u_task_priority_list[MAX_NUM_U_TASKS]; /* List of ids by priorities */
U_EXTERN const u16 U_TASK_PRIO_MASK[MAX_NUM_U_TASKS];
U_EXTERN volatile u08 u_task_curr; /* current utask */
U_EXTERN volatile u08 u_task_next; /* next utask */
U_EXTERN volatile u16 u_task_stack_cnt;

U_EXTERN void u_task_init(void);
U_EXTERN void u_task_idle(void);
U_EXTERN void u_task_main(void);
U_EXTERN void u_task_suspend(u_task* u);
U_EXTERN void u_task_resume(prio_t p);


#endif
