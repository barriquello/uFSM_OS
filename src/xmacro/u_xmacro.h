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

#define TIMERS_TABLE_EN 1

#if TIMERS_TABLE_EN == 1

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

/* declare a table of function pointers */ 
const c_timer_t U_TMR[U_NUM_TIMERS] =
{
    U_TIMER_TABLE(EXPAND_AS_TIMERJUMPTABLE)
};
#endif


#endif






