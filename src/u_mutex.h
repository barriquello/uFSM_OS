 
/**
 * \file
 * Counting mutexes implemented on protothreads
 * \author
 * Carlos H. Barriquello <barriquello@gmail.com>
 *
 */

#ifndef __U_MUTEX_H__
#define __U_MUTEX_H__

#include "u_core.h"

typedef struct {  
  u16 waitlist;
  u08 count;
  u08 mtx_prio;
  u08 orig_prio; 
  u08 owner;   
}u_mutex;

    
/**
 * Initialize a mutex
 *
 * This macro initializes a mutex with a priority for "priority ceiling".
 * Internally, the mutexes use a "unsigned char" counter to count multiple 
 * takes by the same u and therefore the "count" argument should be within
 * range of an unsigned char.
 *
 * \param s (struct u_mutex *) A pointer to the u_mutex struct
 * representing the mutex
 *
 * \param p (unsigned char) The priority of the mutex.
 * \hideinitializer
 */
#define U_MUTEX_INIT(s, p)  STATIC_ASSERT((p <= MAX_PRIO)); \
                            STATIC_ASSERT((p > 0));            \
                            if(u_priority_list[p] != (u08)(-1)) for(;;);   \
                            u_priority_list[p] = MUTEX_PRIO;          \
                            (s)->mtx_prio = p; (s)->orig_prio = 0;    \
                            (s)->count = 0; (s)->waitlist = 0;        

/**
 * Acquire a mutex
 *
 * This macro carries out the "acquire" operation on the mutex. The
 * acquire operation causes the protothread to take the mutex and to 
 * change its priority if needed (PCP) or to block waiting the mutex 
 * to be free. 
 *
 * \param u (struct u *) A pointer to the protothread (struct u) in
 * which the operation is executed.
 *
 * \param s (struct u_mutex *) A pointer to the u_mutex struct
 * representing the mutex.
 *
 * \hideinitializer
 */
void Mutex_Acquire(u_task* u, u_mutex* s);
  
#define U_MUTEX_ACQUIRE(s) 	                       \
        Mutex_Acquire(u,s);                        \
        U_SCHEDULER();                             \
        U_PREEMP_POINT(u);
        
                 
        
/**
 * Release a mutex
 *
 * This macro carries out the "release" operation on the mutex. The
 * release operation decrements the counter inside the semaphore, which
 * eventually be zero (i.e. free) and will cause waiting protothreads 
 * to hold the mutex and continue executing.
 *
 * \param u (struct u *) A pointer to the protothread (struct u) in
 * which the operation is executed.
 *
 * \param s (struct u_mutex *) A pointer to the u_mutex struct
 * representing the mutex
 *
 * \hideinitializer
 */
void Mutex_Release(u_task* u, u_mutex* s);

#define U_MUTEX_RELEASE(s)                          \
        Mutex_Release(u,s);                            \
        U_SCHEDULER();                                 \
        U_PREEMP_POINT(u);

       

/* This function implmentes the priority ceiling protocol */
void Mutex_PrioCeil(u_task* u, u_mutex* s);

#endif /* __U_MUTEX_H__ */

/** @} */
/** @} */
   
