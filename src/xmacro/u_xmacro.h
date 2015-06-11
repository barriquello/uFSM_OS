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

#define EXPAND_AS_STRUCT(a,b,c,d,e) u08 b;

#define EXPAND_AS_VARIABLES(a,b,c,d,e) U_EXTERN u_task b;
U_TASK_TABLE(EXPAND_AS_VARIABLES);

#define EXPAND_AS_PROTOTYPES(a,b,c,d,e) U_EXTERN void a(void);
U_TASK_TABLE(EXPAND_AS_PROTOTYPES);

#define EXPAND_AS_PROTOTYPES_ID(a,b,c,d,e) U_EXTERN u08 a##_id(u08 id);
U_TASK_TABLE(EXPAND_AS_PROTOTYPES_ID);

/*  declare a struct with a 1-byte field for every entry */ 
typedef struct{
    U_TASK_TABLE(EXPAND_AS_STRUCT)
} size_struct_t;

#define U_NUM_TASKS  (sizeof(size_struct_t)+1) // +1 for idle

#define EXPAND_AS_JUMPTABLE(a,b,c,d,e) {a,&b},

#ifdef DEFINE_U_VARIABLES
/* declare a table of function pointers */
const u_tcb U_TCB[U_NUM_TASKS] = {
    {u_idle,NULL},
    U_TASK_TABLE(EXPAND_AS_JUMPTABLE)
};

// #define EXPAND_AS_ENUMERATION(a,b,c) a,
/* declare an enumeration */
//enum{
//    STATE_TABLE(EXPAND_AS_ENUMERATION)
//}

#if TIMERS_TABLE_EN == 1
#define EXPAND_AS_TIMER_VARIABLES(a,b,c,d) U_EXTERN u_timer b;
U_TIMER_TABLE(EXPAND_AS_TIMER_VARIABLES);

#define EXPAND_AS_TIMER_PROTOTYPES(a,b,c,d) U_EXTERN u16 a(void);
U_TIMER_TABLE(EXPAND_AS_TIMER_PROTOTYPES)

/*  declare a struct with a 1-byte field for every entry */ 
typedef struct{
    U_TIMER_TABLE(EXPAND_AS_STRUCT)
} size_timer_struct_t;

#define U_NUM_TIMER  (sizeof(size_timer_struct_t))

#define EXPAND_AS_TIMERJUMPTABLE(a,b,c,d) {a,&b,c},

/* declare a table of function pointers */ 
const u_timercb U_TMR_CB[U_NUM_TIMER] = {
    U_TIMER_TABLE(EXPAND_AS_TIMERJUMPTABLE)
};
#endif


#endif






