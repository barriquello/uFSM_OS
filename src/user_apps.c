/**
 * \file user_app.c
 * Example utasks, demo code, testing utasks
 * \author
 * Carlos H. Barriquello <barriquello@gmail.com>
 *
 */

/* We must always include uFSMrtos.h in our code. */
#include "uFSMrtos.h"

#include "install_apps.h"
#undef DEFINE_U_VARIABLES
#include "u_xmacro.h"
#include "u_sem_xmacro.h"

#include <stdlib.h>

U_TASK(suspend_resume_test)
{

   /* A utask must begin with U_BEGIN() */
   U_BEGIN();
   for(;;)
   {
	  /* Suspend itself */
	  U_TASK_SUSPEND();
	  U_PRINTF("Test suspend/resume ok! \n");
   }
   /* All utask end with U_END() */
   U_END();
}


extern u_mutex mutex_a;
int a_global = 0;

U_TASK(mutex_test)
{

  U_BEGIN();

   for(;;){
    
      U_MUTEX_ACQUIRE(&mutex_a);
      	U_PRINTF("Test mutex acquire/release ok! \n");
        a_global++;
      U_MUTEX_RELEASE(&mutex_a);
      U_TASK_SUSPEND();
   }
     
  U_END();
}

U_TIMER(timer_delay_test_cb)
{
	U_PRINTF("Test timer ok! \n");
	U_TASK_RESUME_FROM_CB(do_tests);
	return 0;
}

U_TASK(timer_delay_test)
{

  U_BEGIN();

   for(;;){

      TIMER_START(100, timer_delay_test_cb);
      U_TASK_SUSPEND();
   }

  U_END();
}

U_TASK(task_delay_test)
{

  static u_timer_t timer;
  static u_clock_t time_now;
  U_BEGIN();

   for(;;)
   {

	   time_now = u_clock_get();
	   U_TIMER_PEND(&timer, 100);
	   time_now = u_clock_get() - time_now;
	   if(time_now == 100)
	   {
		   U_PRINTF("Test delay ok! \n");
	   }else
	   {
		   U_PRINTF("Test delay fail! \n");
	   }

	   time_now = u_clock_get();
	   U_TASK_DELAY(100);
	   time_now = u_clock_get() - time_now;
	   if(time_now == 100)
	   {
		   U_PRINTF("Test built-in delay ok! \n");
	   }else
	   {
		   U_PRINTF("Test built-in delay fail! \n");
	   }
	   U_TASK_RESUME(do_tests);
	   U_TASK_SUSPEND();
   }

  U_END();
}

U_TASK(task_stack_test)
{

  static u_timer_t timer;
  int i = 1000;
  struct
  {
	  int a;
	  char c;
  } s = {333,'a'};

  U_BEGIN();

   for(;;){
	   i++;
	   PUSH(i);
	   PUSH(s);
	   U_TIMER_PEND(&timer, 100);
	   POP(s)
	   POP(i);
	   u_assert(i==1001);
	   u_assert(s.a==333);
	   u_assert(s.c=='a');
	   U_PRINTF("Test stack ok! \n");
	   U_TASK_RESUME(do_tests);
       U_TASK_SUSPEND();
   }

  U_END();
}

U_TASK(sem_builtin_test)
{

  U_BEGIN();

  for(;;){

    /* Wait a semaphore post */
    U_SEM_PEND_SELF();
    	U_PRINTF("Test built-in sem pend/post ok! \n");
    U_SEM_POST_TO(do_tests); /* test 2 posts */
    U_SEM_POST_TO(do_tests);
  }

  U_END();
}


#define ALL_TESTS 	6
U_TASK(do_tests)
{
	   static int tests = 0; /* variables must be defined before U_BEGIN */

	   U_BEGIN();
	   for(;;)
	   {
		   if(tests == 0)
		   {
			   /* test resume */
			   U_TASK_RESUME(suspend_resume_test);
			   U_PRINTF("Test resume ok! \n");
		   }
		   ++tests;

		   if(tests == 1)
		   {
			   /* test sem pend and post */
			   U_SEM_POST(&semtest);
			   U_SEM_PEND(&semtest_ok);
			   U_PRINTF("Test sem ok! \n");
		   }
		   ++tests;

		   if(tests == 2)
		   {
			  /* test mutex acquire/release */
			  U_MUTEX_ACQUIRE(&mutex_a);
			  U_TASK_RESUME(mutex_test);
				a_global = 0;
			  U_MUTEX_RELEASE(&mutex_a);

			  if(a_global == 1)
			  {
				  U_PRINTF("Test mutex ok! \n");
			  }else
			  {
				  U_PRINTF("Test mutex failed! \n");
			  }

		   }
		   ++tests;

		   /* test timer creation and callback */
		   if(tests == 3)
		   {
			   static u_timer_t timer1, timer2, timer3;
			   u_timer_set(&timer1, 10);
			   u_timer_set(&timer2, 7);
			   u_timer_set(&timer3, 5);
			   U_TASK_RESUME(timer_delay_test);
			   U_TASK_SUSPEND();
		   }
		   ++tests;

		   /* test delay */
		   if(tests == 4)
		   {
			   U_TASK_RESUME(task_delay_test);
			   U_TASK_SUSPEND();
		   }
		   ++tests;

		   /* test stack */
		   if(tests == 5)
		   {
			   U_TASK_RESUME(task_stack_test);
			   U_TASK_SUSPEND();
		   }
		   ++tests;

		   if(tests == 6)
		   {
			   /* test built-in sem pend and post */
			   U_SEM_POST_TO(sem_builtin_test);
			   U_SEM_PEND_SELF();
			   U_SEM_PEND_SELF();
			   U_PRINTF("Test built-in sem ok! \n");
		   }
		   ++tests;

		   if(tests >= 	ALL_TESTS)
		   {
			   while(1)
			   {
				   exit(0);
			   }
		   }

	   }

	  U_END();
}


U_TIMER(function_timer)
{
	return 10;
}

