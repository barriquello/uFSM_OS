/**
 * \file u_init_xmacro.h
 * Xmacro implementation
 * See: http://en.wikipedia.org/wiki/X_Macro
 * \author
 * Carlos H. Barriquello <barriquello@gmail.com>
 *
 */
#define EXPAND_AS_INIT(a,b,c,d,e) U_TASK_INIT(a,&b,c,d,e);
U_TASK_TABLE(EXPAND_AS_INIT)
 

#if TIMERS_TABLE_EN == 1
#define EXPAND_AS_TIMER_INIT(a,b,c,d)   U_TIMER_INIT(&b,c);
U_TIMER_TABLE(EXPAND_AS_TIMER_INIT)
#endif



