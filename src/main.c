/**
 * \file main.c
 * Entry point, system initialization
 * \author
 * Carlos H. Barriquello <barriquello@gmail.com>
 *
 */

/* We must always include uFSMrtos.h in our utasks code. */
#include "uFSMrtos.h"


#ifdef __cplusplus
 extern "C"
#endif

// #include <stdio.h> /* For printf(). */
#define printf(x)  do{ }while(0);


/**
 * Finally, we have the main loop. Here is where the utasks are
 * initialized and scheduled. First, however, we define the
 * utask state variables, functions and priorities  in the "U_TASK_TABLE".
 */

#include "user_app.h"       

#define DEFINE_U_VARIABLES
#include "u_xmacro.h"
#include "u_sem_xmacro.h"

u_mutex mutex_a, mutex_b;


/* Compile-time error checking */
#define U_ASSERT_FN
#include "u_assert.h"


int main(void)
{

  U_INIT();  /* Initialize core variables */
  
  /* Initialize the utasks with U_TASK_INIT(). */
  #include "u_init_xmacro.h"
  
  /* Initialize the semaphores with U_SEM_INIT(). */
  #include "u_init_sem_xmacro.h"
  
  /* Initialize the a mutex with U_MUTEX_INIT(). */
  U_MUTEX_INIT(&mutex_a,9);
 
  /* Then we run the utasks using priority scheduling, forever */
  U_RUN();
   
  return 0;
  
  for(;;)
  {

  } /* loop forever */

}










 



