 
/**
 * \file u_sem.h
 * Counting semaphores
 * \author
 * Carlos H. Barriquello <barriquello@gmail.com>
 *
 */

#ifndef __U_SEM_H__
#define __U_SEM_H__

#include "u_core.h"

typedef struct {
  u16 count;
  u16 waitlist;    
}u_sem;

    
/**
 * Initialize a semaphore
 *
 * This macro initializes a semaphore with a value for the
 * counter. Internally, the semaphores use an "unsigned int" to
 * represent the counter, and therefore the "count" argument should be
 * within range of an unsigned int.
 *
 * \param s (struct u_sem *) A pointer to the u_sem struct
 * representing the semaphore
 *
 * \param c (unsigned int) The initial count of the semaphore.
 * \hideinitializer
 */
#define U_SEM_INIT(s, c) (s)->count = c; (s)->waitlist = 0;

/**
 * Pend for a semaphore
 *
 * This macro carries out the "pend" operation on the semaphore. The
 * pend operation causes the utask to block while the counter is
 * zero. When the counter reaches a value larger than zero, the
 * utask will continue.
 *
 * \param u (struct u *) A pointer to the utask (struct u) in
 * which the operation is executed.
 *
 * \param s (struct u_sem *) A pointer to the u_sem struct
 * representing the semaphore
 *
 * \hideinitializer
 */
void Sem_Pend(u_task* u, u_sem* s);
  
#define U_SEM_PEND(s) 	                      \
        Sem_Pend(u,s);                           \
        U_EnterCritical();                    \
        U_SCHEDULER();                           \
        U_ExitCritical();                     \
        U_PREEMP_POINT(u);

            
        
/**
 * Post a semaphore
 *
 * This macro carries out the "post" operation on the semaphore. The
 * post operation increments the counter inside the semaphore, which
 * eventually will cause waiting utasks to continue executing.
 *
 * \param u (struct u *) A pointer to the utask (struct u) in
 * which the operation is executed.
 *
 * \param s (struct u_sem *) A pointer to the u_sem struct
 * representing the semaphore
 *
 * \hideinitializer
 */
void Sem_Post(u_task* u, u_sem* s);

#define U_SEM_POST(s)                           \
        Sem_Post(u,s);                          \
        if(!u_int_nesting){U_EnterCritical();}  \
        U_SCHEDULER();                          \
        if(!u_int_nesting){U_ExitCritical(); U_PREEMP_POINT(u);}

       

#endif /* __U_SEM_H__ */

/** @} */
/** @} */
   
