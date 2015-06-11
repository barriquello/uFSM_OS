/*
 * u_task.h
 *
 *  Created on: 06/06/2015
 *      Author: Gisele
 */

#ifndef U_TASK_C_
#define U_TASK_C_

#include "u_core.h"


/******************* idle ***************/
/* this is the lowest priority task */
/* it can be used for background work */
U_TASK(u_idle)
{
  U_IDLE();
  return;
}

/******************* main task ***************/
/* this is the highest priority task */
/* it can be used for instance to emulate interrupts */
U_TASK(u_main_task)
{
	TickTimer();
	return;
}



#endif /* U_TASK_C_ */
