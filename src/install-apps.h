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
 * \file install_apps
 * Example of table for creating utasks, semaphores, timers, etc... using xmacros.
 * See: http://en.wikipedia.org/wiki/X_Macro
 * \author
 * Carlos H. Barriquello <barriquello@gmail.com>
 *
 */

/* Table used to declare utasks state variables, functions and priorities */
#define U_TASK_TABLE(ENTRY)           				  \
	    ENTRY(suspend_resume_test,5, U_START,0)  	  \
        ENTRY(sem_test,2, U_START,0)       		  	  \
		ENTRY(mutex_test,3,U_NO_START,0)      		  \
		ENTRY(timer_delay_test,4,U_NO_START,0)        \
		ENTRY(task_delay_test,6,U_NO_START,0)         \
		ENTRY(task_stack_test,21,U_NO_START,10)       \
		ENTRY(sem_builtin_test,7, U_START,0)          \
        ENTRY(do_tests,1, U_START,0)

/* Table used to declare semaphores */
#define U_SEM_TABLE(ENTRY)         \
        ENTRY(semtest,0)           \
        ENTRY(semtest_ok,0)


/* Table used to declare timers    */
#define U_TIMER_TABLE(ENTRY)         \
        ENTRY(function_timer,10, U_START) \
		ENTRY(timer_delay_test_cb,0, U_NOSTART)



