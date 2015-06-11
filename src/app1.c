/**
 * \file app1.c
 * App demo code
 * \author
 * Carlos H. Barriquello <barriquello@gmail.com>
 *
 */

#include "uFSMrtos.h"
#include <stdlib.h>

extern u_sem semtest;
extern u_sem semtest_ok;

U_TASK(sem_test)
{

  /* A utask must begin with U_BEGIN() */
  U_BEGIN();

  /* We loop forever here. */
  for(;;){

    /* Wait a semaphore post */
    U_SEM_PEND(&semtest);
    	U_PRINTF("Test sem pend/post ok! \n");
    U_SEM_POST(&semtest_ok);

    /* And we loop. */
  }

  /* All utask end with U_END() */
  U_END();
}
