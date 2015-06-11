/*
 * u_port.c
 *
 *  Created on: 07/06/2015
 *      Author: Gisele
 */


#ifdef _WIN32
#include <windows.h>
#endif

#include "u_port.h"
#include "u_core.h"
#include "u_time.h"

static unsigned long long last_time = 0;

int port_timer_win(void)
{
	unsigned long long time;
	unsigned long long time_diff;

	time = GetTickCount();
	time_diff = time - last_time;
	last_time = time;

	u_clock_set(u_clock_get() + time_diff/10);
	if(time_diff > 0)
	{
		return 1;
	}
	return 0;
}

void TickTimerInit(void)
{
	last_time = GetTickCount();
}

void TickTimer(void)
{
  U_INT_ENTER();

  TICKTIMER_INT_HANDLER();

  U_NESTING_ENABLE();

  if(port_timer_win() == 1)
  {
	  u_tick_counter_inc(); /* increment tick counter */
  }

  U_INT_EXIT();

}


