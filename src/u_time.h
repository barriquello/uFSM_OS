/**
 * \file
 * Timers implemented for utasks
 * \author
 * Carlos H. Barriquello <barriquello@gmail.com>
 *
 */

#ifndef __U_TIME_H__
#define __U_TIME_H__

#include "u_core.h"
#include "u_time.h"


typedef unsigned long long u_clock_t;
typedef u16 			   u_tick_t;

U_EXTERN volatile u_tick_t  u_tickcounter;
U_EXTERN volatile u_clock_t u_clock;

typedef u16 (*u_timercb)(void);

#define U_TIMER_CALLBACK(cb)		u16 (cb)(void); u16 (cb)(void)

typedef struct
{
    u16    	   timeout;
    u_timercb  func_cb;
    u08 	   u_id;
}u_timer_t;


typedef  u_timer_t*  u_timer;

#define U_MAX_NUM_TIMERS 	    16
#define TICK_COUNT_OVERFLOW 	64000
#define TIMER_MAX_COUNTER       (u_tick_t)(TICK_COUNT_OVERFLOW-1)

/* timers list data struct */  
typedef struct{    
	u_timer    timers [U_MAX_NUM_TIMERS];
    u08    	   count;
}u_tmr;



#define U_TIMER(name_args)  	u16 name_args
#define U_TIMER_INIT(s, t)     (s)->timeout = t;

u_tick_t u_tick_counter_get(void);
void u_tick_counter_set(u_tick_t ticks);
void u_tick_counter_inc(void);


u_clock_t u_clock_get(void);
void u_clock_set(u_clock_t time);
void u_tick_counter_inc(void);

void u_time_init(void);
void u_time_manager(void);
void u_timer_set (u_timer p, u16 time_wait);

void Timer_Pend(u_task* u, u_timer s, u16 time_wait);
void Timer_SetCallBack(u_timer s, u16 time_wait, u_timercb cb);


#define U_TIMER_PEND(s,t)	                    \
		Timer_Pend(u,s,t)                       \
        U_EnterCritical();                    	\
        U_SCHEDULER();                          \
        U_ExitCritical();                     	\
        U_PREEMP_POINT(u);

#endif /* __PT_TIME_H__ */

/** @} */
/** @} */
   
