/* We must always include u_core.h in our code. */
#include "u_core.h"
#include "u_sem.h"
#include "u_mutex.h"
#include "u_time.h"


/* For printf(). */
#include <stdlib.h>
#include <stdio.h>
//#define printf(x)  do{ }while(0);

#include "user_app.h"   
#include "u_xmacro.h"
#include "u_sem_xmacro.h"


U_TASK(suspend_resume_test)
{

   /* A utask must begin with U_BEGIN() */
   U_BEGIN();
   for(;;)
   {
	  /* Suspend itself */
	  U_TASK_SUSPEND();
      printf("Test suspend/resume ok! \n");
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
        printf("Test mutex acquire/release ok! \n");
        a_global++;
      U_MUTEX_RELEASE(&mutex_a);
      U_TASK_SUSPEND();
   }
     
  U_END();
}

U_TIMER_CALLBACK(timer_delay_test_cb)
{
	printf("Test timer ok! \n");
	U_TASK_RESUME_FROM_CB(do_tests);
	return 0;
}

U_TASK(timer_delay_test)
{

  static u_timer_t timer;
  U_BEGIN();

   for(;;){

      Timer_SetCallBack(&timer, 100, timer_delay_test_cb);
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
		   printf("Test delay ok! \n");
	   }else
	   {
		   printf("Test delay fail! \n");
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
	   printf("Test stack ok! \n");
	   U_TASK_RESUME(do_tests);
       U_TASK_SUSPEND();
   }

  U_END();
}



#define ALL_TESTS 	4
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
			   printf("Test resume ok! \n");
		   }
		   ++tests;

		   if(tests == 1)
		   {
			   /* test sem pend and post */
			   U_SEM_POST(&semtest);
			   U_SEM_PEND(&semtest_ok);
			   printf("Test sem ok! \n");
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
				  printf("Test mutex ok! \n");
			  }else
			  {
				  printf("Test mutex failed! \n");
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

		   if(tests >= 	ALL_TESTS)
		   {
			   fflush(stdout);
			   while(1)
			   {
				   exit(0);
			   }
		   }

	   }

	  U_END();
}


