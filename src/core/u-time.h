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
 * \file u_time.h
 * System Time and Timer Services
 * \author
 * Carlos H. Barriquello <barriquello@gmail.com>
 *
 */

#ifndef __U_TIME_H__
#define __U_TIME_H__

#include "uFSMrtos.h"

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

#include "install-apps.h"

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
#define U_TIMER_INIT(s,n,t)      	u_timer_set(s,t); (s)->u_id = (MAX_ID + (++u_task_next)); n##_id((s)->u_id);


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



#endif /* __PT_TIME_H__ */

/** @} */
/** @} */
   
