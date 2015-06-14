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
 * \file u_xmacro.h
 * Xmacro implementation
 * See: http://en.wikipedia.org/wiki/X_Macro
 * \author
 * Carlos H. Barriquello <barriquello@gmail.com>
 *
 */

#ifdef DEFINE_U_VARIABLES
#undef  U_EXTERN
#define U_EXTERN /* nothing */
#else
#undef  U_EXTERN
#define U_EXTERN extern
#endif /* DEFINE_VARIABLES */

#define LC_VAR(a)	lc_##a
#define EXPAND_AS_STRUCT(a,c,d,e) u08 LC_VAR(a);

#define EXPAND_AS_VARIABLES(a,c,d,e) U_EXTERN u_task LC_VAR(a);
U_TASK_TABLE(EXPAND_AS_VARIABLES);

#define EXPAND_AS_PROTOTYPES(a,c,d,e) U_EXTERN void a(void);
U_TASK_TABLE(EXPAND_AS_PROTOTYPES);

#define EXPAND_AS_PROTOTYPES_ID(a,c,d,e) U_EXTERN u08 a##_id(u08 id);
U_TASK_TABLE(EXPAND_AS_PROTOTYPES_ID);

/*  declare a struct with a 1-byte field for every entry */ 
typedef struct{
    U_TASK_TABLE(EXPAND_AS_STRUCT)
} size_struct_t;

#define U_NUM_TASKS  (sizeof(size_struct_t)+1) // +1 for idle

#define EXPAND_AS_JUMPTABLE(a,c,d,e) {a,&(LC_VAR(a))},


#define SEM_EXPAND_AS_VARIABLES(a,b) U_EXTERN u_sem a;
U_SEM_TABLE(SEM_EXPAND_AS_VARIABLES);

#define SEM_EXPAND_AS_STRUCT(a,b) u08 a;


/*  declare a struct with a 1-byte field for every entry */
typedef struct{
    U_SEM_TABLE(SEM_EXPAND_AS_STRUCT)
} sem_size_struct_t;


#define U_NUM_SEM  sizeof(sem_size_struct_t)

// #define SEM_EXPAND_AS_ENUMERATION(a,b) a,
/* declare an enumeration */
//enum{
//    U_SEM_TABLE(SEM_EXPAND_AS_ENUMERATION)
//}

#ifdef DEFINE_U_VARIABLES
/* declare a table of function pointers */
const u_tcb U_TCB[U_NUM_TASKS] = {
    {u_task_idle,NULL},
    U_TASK_TABLE(EXPAND_AS_JUMPTABLE)
};

// #define EXPAND_AS_ENUMERATION(a,b,c) a,
/* declare an enumeration */
//enum{
//    STATE_TABLE(EXPAND_AS_ENUMERATION)
//}
#endif

#ifdef U_TIMER_TABLE

#define EXPAND_AS_TIMERSTRUCT(a,c,d) u08 LC_VAR(a);

#define EXPAND_AS_TIMER_VARIABLES(a,c,d) U_EXTERN u_timer_t LC_VAR(a);
U_TIMER_TABLE(EXPAND_AS_TIMER_VARIABLES);

#define EXPAND_AS_TIMER_PROTOTYPES(a,c,d) U_EXTERN u16 a(void);
U_TIMER_TABLE(EXPAND_AS_TIMER_PROTOTYPES)

#define EXPAND_AS_TIMER_PROTOTYPES_ID(a,c,d) U_EXTERN u08 a##_id(u08 id);
U_TIMER_TABLE(EXPAND_AS_TIMER_PROTOTYPES_ID);

/*  declare a struct with a 1-byte field for every entry */ 
typedef struct
{
    U_TIMER_TABLE(EXPAND_AS_TIMERSTRUCT)
} size_timer_struct_t;

#define U_NUM_TIMERS  (sizeof(size_timer_struct_t))

#define EXPAND_AS_TIMERJUMPTABLE(a,c,d) {a,&(LC_VAR(a))},

#ifdef DEFINE_U_VARIABLES

#if U_TIMER_TABLE_ENABLE
/* declare a table of function pointers */ 
const c_timer_t U_TMR[U_NUM_TIMERS] =
{
    U_TIMER_TABLE(EXPAND_AS_TIMERJUMPTABLE)
};
#endif
#endif

#endif


