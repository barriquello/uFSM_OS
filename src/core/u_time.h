/**
 * \file u_time.h
 * System Time and Timer Services
 * \author
 * Carlos H. Barriquello <barriquello@gmail.com>
 *
 */

#ifndef __U_TIME_H__
#define __U_TIME_H__

#include "u_core.h"

typedef unsigned long long u_clock_t;
typedef u16 			   u_tick_t;

U_EXTERN volatile u_tick_t  u_tickcounter;
U_EXTERN volatile u_clock_t u_clock;

typedef u16 (*u_timercb)(void);

#define U_TIMER_CALLBACK(cb)		u16 (cb)(void); u16 (cb)(void)

typedef  u_timer_t*  u_timer;

typedef struct {
	u_timercb  cb;
	u_timer    timer;
}c_timer_t;

#define TICK_COUNT_OVERFLOW 	64000
#define TIMER_MAX_COUNTER       (u_tick_t)(TICK_COUNT_OVERFLOW-1)

#include "install_apps.h"

#define _EXPAND_AS_STRUCT(a,c,d,e) 	 u08 a;
#define _EXPAND_AS_TIMERSTRUCT(a,c,d) u08 a;

typedef struct{
    U_TASK_TABLE(_EXPAND_AS_STRUCT)
} time_size_struct_t;

typedef struct
{
    U_TIMER_TABLE(_EXPAND_AS_TIMERSTRUCT)
} timer_size_struct_t;


#define U_NUM_TIMERS_INSTALL  (sizeof(timer_size_struct_t) + (sizeof(time_size_struct_t)+1))

/* timers list data struct */  
typedef struct{    
	u_timer    timers [U_NUM_TIMERS_INSTALL + U_STATIC_TIMERS];
    u08    	   count;
}u_tmr;

U_EXTERN const c_timer_t U_TMR[];

#define U_TIMER(name)  				U_TIMER_INFO(name) u16 (name) (void)
#define U_TIMER_INFO(name) 	 		u08 name##_id(u08 id)	\
{ static u08 u_id = 0; if(id != 0) {u_id = id;} return u_id; }
#define U_GET_TIMER_ID(name) 		(name##_id)(0)
#define U_TIMER_INIT(s,n,t)      	u_timer_set(s,t); (s)->u_id = (MAX_ID + (++u_next)); n##_id((s)->u_id);


#define TIMER_START(time_wait, cb)	Timer_Start(U_TMR[U_GET_TASK_ID(cb) - MAX_ID-1].timer, time_wait);

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
void Timer_Start(u_timer s, u16 time_wait);

#define U_TIMER_PEND(s,t)	                    \
		Timer_Pend(u,s,t)                       \
        U_EnterCritical();                    	\
        U_SCHEDULER();                          \
        U_ExitCritical();                     	\
        U_PREEMP_POINT(u);

#define U_TASK_DELAY(t)	                        \
		Timer_Pend(u,&((u)->tmr),t)             \
        U_EnterCritical();                    	\
        U_SCHEDULER();                          \
        U_ExitCritical();                     	\
        U_PREEMP_POINT(u);


#endif /* __PT_TIME_H__ */

/** @} */
/** @} */
   
