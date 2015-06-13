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
 * \file uFSMrtos.h
 * System includes
 * \author
 * Carlos H. Barriquello <barriquello@gmail.com>
 *
 */

#ifndef UFSMRTOS_H_
#define UFSMRTOS_H_

#include "u-task.h"
#include "u-sched.h"
#include "u-sem.h" /* semaphores services */
#include "u-time.h" /* time and timer services */
#include "u-mutex.h" /* mutexes services */

#if UFSMRTOS_API
	/* module u-task */
    /* functions */
	u_task_create
	u_task_resume;
	u_task_suspend;
	u_task_main;
	u_task_idle;
	/* variables */
	u_task_ready_list;
	u_task_priority_list;
	u_task_stack;
	u_task_stack_cnt;
	u_task_curr;
	u_task_next;
	/* const */
	U_TASK_PRIO_MASK;

	/* macros */
	U_TASK_RESUME;
	U_TASK_SUSPEND;
	U_TASK_DELAY;

	/* module u-sched */
    /* functions */
	u_core_init;
	u_core_schedule;
	/* variables */
	u_core_int_nest;
	/* const */
	U_SCHED_TABLE;

	/* module u-time */
    /* functions */
	/* variables */
	/* const */
	/* macros */

	/* module u-sem */
    /* functions */
	/* variables */
	/* const */
	/* macros */

	/* module u-mutex */
    /* functions */
	u_mutex_acquire;
	u_mutex_release;
	u_mutex_prio_ceil;
	/* variables */
	/* const */
	/* macros */
	U_MUTEX_PRIO


#endif

#endif

