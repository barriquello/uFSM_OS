/**
 * \file install_apps
 * Example of table for creating utasks, semaphores, timers, etc... using xmacros.
 * See: http://en.wikipedia.org/wiki/X_Macro
 * \author
 * Carlos H. Barriquello <barriquello@gmail.com>
 *
 */

/* Table used to declare utasks state variables, functions and priorities */
#define U_TASK_TABLE(ENTRY)           						  \
	    ENTRY(suspend_resume_test,lc_resume,5, U_START,0)  	  \
        ENTRY(sem_test,lc_sem,2, U_START,0)       		  	  \
		ENTRY(mutex_test,lc_mutex,3,U_NO_START,0)      		  \
		ENTRY(timer_delay_test,lc_timer,4,U_NO_START,0)       \
		ENTRY(task_delay_test,lc_delay,6,U_NO_START,0)        \
		ENTRY(task_stack_test,lc_stack,7,U_NO_START,10)        \
        ENTRY(do_tests,lc_test,1, U_START,0)


/* Table used to declare semaphores */
#define U_SEM_TABLE(ENTRY)         \
        ENTRY(semtest,0)           \
        ENTRY(semtest_ok,0)


        
#if 0
/* Table used to declare timers    */
#define U_TIMER_TABLE(ENTRY)         \
        ENTRY(function_timer,timeout_timer,10, U_START)
#endif


