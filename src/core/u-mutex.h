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
 * \file u-mutex.h
 * Counting mutexes, with priority ceiling protocol
 * \author
 * Carlos H. Barriquello <barriquello@gmail.com>
 *
 */

#ifndef __U_MUTEX_H__
#define __U_MUTEX_H__

#include "uFSMrtos.h"

typedef struct {  
  u_prio_list_t waitlist;
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
                            if(u_task_priority_list[p] != (u08)(-1)) for(;;);   \
                            u_task_priority_list[p] = MUTEX_PRIO;          \
                            (s)->mtx_prio = p; (s)->orig_prio = 0;    \
                            (s)->count = 0; (s)->waitlist.w[1] = 0; (s)->waitlist.w[0] = 0;

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
void u_mutex_acquire(u_task* u, u_mutex* s);
  
#define U_MUTEX_ACQUIRE(s) 	                       \
        u_mutex_acquire(u,s);                        \
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
void u_mutex_release(u_task* u, u_mutex* s);

#define U_MUTEX_RELEASE(s)                          \
        u_mutex_release(u,s);                            \
        U_SCHEDULER();                                 \
        U_PREEMP_POINT(u);

       

/* This function implmentes the priority ceiling protocol */
void u_mutex_prio_ceil(u_task* u, u_mutex* s);

#endif /* __U_MUTEX_H__ */

/** @} */
/** @} */
   
