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
 * \file u_mutex.c
 * Counting mutexes, with priority ceiling protocol
 * \author
 * Carlos H. Barriquello <barriquello@gmail.com>
 *
 */


#include "uFSMrtos.h"


/**************** mutexes ******************/

void u_mutex_acquire(u_task* u, u_mutex* s)
{
	  u_assert(u_sched_int_nest == 0);
      u_assert((s)->owner != u_task_curr);
      if((s)->count > 0)
      {
        U_EnterCritical();
          EVENT_PEND(u,s);
        U_ExitCritical();
      }else
      {
        (s)->count = 1;
        (s)->owner = u_task_curr;
        u_mutex_prio_ceil(u,s); /* call priority ceiling function */
      }
}
/*---------------------------------------------------------------*/
void u_mutex_release(u_task* u, u_mutex* s)
{
      //(void)u;
      u_assert((s)->owner == u_task_curr);

      /* Returns to the original priority, if needed */
      if ((u)->prio != (s)->orig_prio)
      {

          U_EnterCritical();
			  #if CONF_U_TASK_MAX_NUM > 16
              /* Remove "max priority" from the Ready List*/
          	  	SET_READYLIST_PRIO((s)->orig_prio);
			  /* Put the "original priority" into Ready List */
          	    RESET_READYLIST_PRIO((u)->prio);
			  #else
			  /* Put the "original priority" into Ready List */
			  u_task_ready_list |= (U_TASK_PRIO_MASK[(s)->orig_prio]);
			  /* Remove "max priority" from the Ready List*/
			  u_task_ready_list &= ~(U_TASK_PRIO_MASK[(u)->prio]);
			  #endif
          U_ExitCritical();

          (u)->prio = (s)->orig_prio;
      }

      if((s)->waitlist.w[1] == 0 && (s)->waitlist.w[0] == 0)
      {
        (s)->count = 0;
        (s)->owner = 0;
        (s)->orig_prio = 0;
        u_task_priority_list[(s)->mtx_prio] = MUTEX_PRIO;
      }else
      {
        /* transfer mutex to next utask */
        u08 _prio = u_sched((s)->waitlist);
        (s)->owner = u_task_priority_list[_prio];
        if(_prio > 0x0F) {(s)->waitlist.w[1] &= ~U_TASK_PRIO_MASK[_prio - 16];}
        else {(s)->waitlist.w[0] &= ~U_TASK_PRIO_MASK[_prio];}
        u_mutex_prio_ceil((U_TCB[((s)->owner)].arg),s);
      }
}
/*---------------------------------------------------------------*/
void u_mutex_prio_ceil(u_task* u, u_mutex* s)
{

    /* Performs the temporary exchange of mutex owner priority, if needed  */
    if ((s)->mtx_prio > (u)->prio)
    {
      /* Backup the original priority */
      (s)->orig_prio = (u)->prio;

      /* Receives the mutex priority temporarily */
      (u)->prio = (s)->mtx_prio;

      /* Priority list change */
      u_task_priority_list[(s)->mtx_prio] = (s)->owner;

      U_EnterCritical();
			  #if CONF_U_TASK_MAX_NUM > 16

			  /* Remove "max priority" from the Ready List*/
				RESET_READYLIST_PRIO((s)->orig_prio);
			  /* Put the "original priority" into Ready List */
				SET_READYLIST_PRIO((s)->mtx_prio);

			  #else
		        /* Remove "original priority" from the Ready List */
		        u_task_ready_list &= ~(U_TASK_PRIO_MASK[(s)->orig_prio]);
		        /* Put the "mutex priority" into Ready List */
		        u_task_ready_list |= (U_TASK_PRIO_MASK[(s)->mtx_prio]);
			  #endif

      U_ExitCritical();
    }

}
/*---------------------------------------------------------------*/
