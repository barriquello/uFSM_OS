/**
 * \file u_init_sem_xmacro.h
 * Xmacro implementation for semaphores
 * See: http://en.wikipedia.org/wiki/X_Macro
 * \author
 * Carlos H. Barriquello <barriquello@gmail.com>
 *
 */
#define SEM_EXPAND_AS_INIT(a,b) U_SEM_INIT(&a,b);
 U_SEM_TABLE(SEM_EXPAND_AS_INIT)








