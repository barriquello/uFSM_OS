
/**
 * \file u_core.h
 * System core functions
 * \author
 * Carlos H. Barriquello <barriquello@gmail.com>
 *
 */

#ifndef __U_CORE_H__
#define __U_CORE_H__

#include "lc.h"
#include "u_config.h"
#include "u_assert.h"

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
	EV_NONE,EV_TIMER,EV_SEM,EV_MUTEX,EV_MSG
} u_event;

typedef struct {
  u08*	top;
  u16   size;
} u_stack;


typedef struct {
  lc_t 		 lc;
  prio_t 	 prio;
  u_event    evt;
  u_stack    stk;
} u_task;



typedef void (*u_task_ptr)(void);

typedef u_task*  u_task_arg;


typedef struct{
    u_task_ptr ptr;
    u_task_arg arg;
}u_tcb;


#define MAX_NUM_U_TASKS            (sizeof(U_PRIORITYLIST)*8)
#define MAX_PRIO            	   (MAX_NUM_U_TASKS-1)
#define MAX_ID            		   (MAX_NUM_U_TASKS-1)
#define MUTEX_PRIO      	       ((u08)(-2))

#define U_SCHEDULER()         	   u_next = u_priority_list[U_Scheduler(u_ready_list)]

  
#define SET_READYLIST_PRIO(p)       u_ready_list |= u_prio_mask[(p)]
#define RESET_READYLIST_PRIO(p)     u_ready_list &= ~u_prio_mask[(p)]

#define SET_READYLIST(u,s)    	 	SET_READYLIST_PRIO(U_Scheduler((s)->waitlist))
#define RESET_READYLIST(u,s)     	RESET_READYLIST_PRIO((u)->prio)

#define SET_WAITLIST(u,s)     		(s)->waitlist |= u_prio_mask[(u)->prio]
#define RESET_WAITLIST(u,s)   		(s)->waitlist &= ~u_prio_mask[U_Scheduler((s)->waitlist)]
        
#define EVENT_PEND(u,s)       		RESET_READYLIST(u,s); SET_WAITLIST(u,s);
#define EVENT_POST(u,s)       		SET_READYLIST(u,s); RESET_WAITLIST(u,s);

#define U_LOOP_FOREVER()      for(;;)                               \
                               {                                    \
                                 u_curr = u_next;                   \
                                 (void) U_TCB[u_curr].ptr(); 		\
                                 u_main_task();						\
                               }                               
                              
#define U_RUN()            	   U_EnterCritical();                       \
                               U_SCHEDULER();                           \
                               U_ExitCritical();                        \
                               U_LOOP_FOREVER();


/* extensions for lc libray (implemented in "lc.h") */

#define U_TASK_BEGIN_EXT(u)    u_task *(u) = (U_TCB[u_curr].arg);

#define U_TASK_END_EXT()       U_EnterCritical();                     \
                               RESET_READYLIST(u,s); U_SCHEDULER();   \
                               U_ExitCritical();

#define U_TASK_INIT_EXT(u,p,s,z)   STATIC_ASSERT(p > 0);              \
								   STATIC_ASSERT(p <= MAX_PRIO);      \
								   u_assert(u_priority_list[p] == (u08)(-1));   \
								   u_priority_list[p] = ++u_curr;           \
								   (u)->prio = p; 							 \
								   if(s) u_ready_list |= u_prio_mask[p];	 \
								   if(z) { (u)->stk.top = &U_STACK[u_stack_cnt];  \
								   	   	   (u)->stk.size = 0; u_stack_cnt += z; } \
								   u_assert(u_stack_cnt <= U_STACK_SIZE);   \



#define U_TASK_WAIT_UNTIL(u, cond)	  do { LC_SET((u)->lc);		\
										if(!(cond)) {return;}   \
									  } while(0)

/* adaptation for protothreads library */

#define U_TASK_INFO(name)  u08 name##_id(u08 id)	\
{ static u08 u_id = 0; if(id != 0) {u_id = id;} return u_id; }

#define U_TASK(name) 			U_TASK_INFO(name) void name(void)
#define U_TASK_INIT(n,u,p,s,z) 	U_TASK_INIT_EXT(u,p,s,z); n##_id(u_curr); LC_INIT((u)->lc);
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
#define U_PREEMP_POINT(u)  	U_WAIT_UNTIL(u, u_curr == u_next)


#define U_INT_ENTER()   	u_int_nesting++;

#define U_INT_EXIT()    	U_EnterCritical(); u_int_nesting--; \
                        	if(u_int_nesting == 0) U_SCHEDULER();

/* macros for interrupt nesting */                        
#if U_INT_NEST_ENABLE == 0
#define TEST_INT_NESTING(instr)   if(!u_int_nesting){instr;}
#define U_NESTING_ENABLE()
#else
#define TEST_INT_NESTING(instr)   instr;
#define U_NESTING_ENABLE()   	  U_Enable_Nesting()
#endif  

#define U_TASK_GET(id)				(U_TCB[(id)].arg)
#define U_TASK_GET_PRIO(id)			(((u_task *)(U_TCB[(id)].arg))->prio)

#define U_TASK_SUSPEND() 	                  \
		Task_Suspend(u);                      \
        U_EnterCritical();                    \
        U_SCHEDULER();                        \
        U_ExitCritical();                     \
        U_PREEMP_POINT(u);

#define U_TASK_SUSPEND_ID(id)                 \
		U_TASK_SUSPEND(U_GET_TASK_ID(id));

#define U_TASK_RESUME_PRIO(p) 	             \
		Task_Resume(p);                      \
		TEST_INT_NESTING(U_EnterCritical()); \
        U_SCHEDULER();                       \
        TEST_INT_NESTING(U_ExitCritical());  \
        U_PREEMP_POINT(u);

#define U_TASK_RESUME_ID(id)                 \
		U_TASK_RESUME_PRIO((U_TASK_GET_PRIO(id)));

#define U_TASK_RESUME(name)		U_TASK_RESUME_ID((U_GET_TASK_ID(name)))

#define U_TASK_RESUME_PRIO_FROM_CB(p) 	     \
		Task_Resume(p);                      \

#define U_TASK_RESUME_ID_FROM_CB(id)          \
		U_TASK_RESUME_PRIO_FROM_CB((U_TASK_GET_PRIO(id)));

#define U_TASK_RESUME_FROM_CB(name)		U_TASK_RESUME_ID_FROM_CB((U_GET_TASK_ID(name)))

#define U_PUSH(u,v,s)		do{memcpy((u)->stk.top, &(v),s); (u)->stk.top+=s; (u)->stk.size += s;}while(0);
#define U_POP(u,v,s)		do{(u)->stk.top-=s; memcpy(&(v),(u)->stk.top,(s));  (u)->stk.size-=s;}while(0);

#define PUSH(v)		 U_PUSH(u,v,sizeof(v))
#define POP(v)		 U_POP(u,v,sizeof(v))

/* declaration of variables an functions */
#ifdef DEFINE_U_CORE_VARIABLES
#undef  U_EXTERN
#define U_EXTERN /* nothing */
#else
#undef  U_EXTERN
#define U_EXTERN extern
#endif /* DEFINE_VARIABLES */

/* extern variables */
U_EXTERN u08 U_STACK[U_STACK_SIZE];
U_EXTERN const u_tcb U_TCB[];
U_EXTERN const U_PRIORITYLIST u_prio_mask[MAX_NUM_U_TASKS];
U_EXTERN U_PRIORITYLIST u_ready_list; /* ReadyList */
U_EXTERN u08 u_priority_list[MAX_NUM_U_TASKS]; /* List of ids by priorities */
 
U_EXTERN volatile u08 u_curr; /* current utask */
U_EXTERN volatile u08 u_next; /* next utask */
U_EXTERN volatile u08 u_int_nesting;
U_EXTERN volatile u16 u_stack_cnt;


U_EXTERN u08 U_Scheduler(U_PRIORITYLIST);  /* scheduler */
U_EXTERN void U_INIT(void);
U_EXTERN void u_idle(void);
U_EXTERN void u_main_task(void);

void Task_Suspend(u_task* u);
void Task_Resume(prio_t p);


#endif
