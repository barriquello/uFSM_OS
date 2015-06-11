/*
 * app1.c
 *
 *  Created on: 10/06/2015
 *      Author: Gisele
 */

#include "uFSMrtos.h"
#include <stdlib.h>
#include <stdio.h>

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
    	printf("Test sem pend/post ok! \n");
    U_SEM_POST(&semtest_ok);

    /* And we loop. */
  }

  /* All utask end with U_END() */
  U_END();
}
