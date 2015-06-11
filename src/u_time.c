#include "u_core.h"
#include "u_time.h"

/* private data */
static struct
{
    u_tmr *      current;              /* keep current timer list */
    u_tmr *      future;               /* keep future timer list   */
} u_tmr_list;


/* timer lists: memory allocation */
static u_tmr u_tmr_ping, u_tmr_pong;    /* Timer lists */


/* local functions */
/* Binary heap of timers */
#define PAI(i)      (u08)(i>>1)
#define LEFT(i)     (u08)((i<<1) + 1)
#define RIGHT(i)    (u08)((i<<1) + 2)


static void HeapUp (u_timer* timers, u08 i)
{
     while (i > 1 && timers[PAI(i)]->timeout > timers[i]->timeout)
     {
         void* tmp = timers[PAI(i)];
         timers[PAI(i)] = timers[i];
         timers[i] = tmp;
         i=PAI(i);
     }
}

static void HeapDown (u_timer* timers, u08 i, u08 n)
{
  u08 son;
  do{    
    if (RIGHT(i) <= n && timers[RIGHT(i)]->timeout < timers[LEFT(i)]->timeout)     
       son = RIGHT(i);
    else son = LEFT(i);
    if (son <= n  && timers[son]->timeout < timers[i]->timeout)
    {
       void* tmp = timers[son];
       timers[son] = timers[i];
       timers[i] = tmp;
       i=son;     
    }else break;
  }while(1);
}

void u_time_init(void)
{

   u_tmr_list.current = &u_tmr_ping;
   u_tmr_list.future =  &u_tmr_pong;
   u_tickcounter = 0;
   u_clock_set(0);
   TickTimerInit();
}


void u_delay(u_task* u, u16 ticks)
{

  

}

u_tick_t u_tick_counter_get(void)
{
	return u_tickcounter;
}

void u_tick_counter_set(u_tick_t ticks)
{
	u_tickcounter = ticks;
}

void u_tick_counter_inc(void)
{
   if( ++ u_tickcounter == TICK_COUNT_OVERFLOW)
   {
	   u_tickcounter = 0;
   }
   u_time_manager();
}

u_clock_t u_clock_get(void)
{
	return u_clock;
}
void u_clock_set(u_clock_t time)
{
	u_clock = time;
}

void u_clock_inc(void)
{
	u_clock++;
}

void u_timer_set (u_timer p, u16 time_wait)
{

	u32 timeout;
	u_tmr* list;
	if(time_wait > 0)
	{
	   timeout = (u32)((u32)u_tick_counter_get() + (u32)time_wait);

		if (timeout >= TICK_COUNT_OVERFLOW)
		{
			p->timeout = (u16)(timeout - TICK_COUNT_OVERFLOW);
			list = u_tmr_list.future;   // add into future list
		}
		else
		{
			p->timeout = (u16)timeout;
			list = u_tmr_list.current;  // add into current list
		}

		list->timers[++list->count] = p; // insert in the end
		HeapUp (list->timers, list->count); // order it
	}

}

void Timer_Pend(u_task* u, u_timer s, u16 time_wait)
{
      u_assert(u_int_nesting == 0); /* can not block inside an ISR */
      u_timer_set(s,time_wait);
      s->u_id = u_curr;
      U_EnterCritical();
      RESET_READYLIST(u,s);
      U_ExitCritical();
}

void Timer_SetCallBack(u_timer s, u16 time_wait, u_timercb cb)
{
	 s->func_cb = cb;
	 u_timer_set(s,time_wait);
}

void u_time_manager(void)
{

	u_timer    p;
	u_tmr* 	   list;
	u_tmr* 	   list_tmp;
	u_tick_t   repeat;
	u32   	   timeout;
	u08		   run_scheduler = 0;
	u_tick_t   tickcount = u_tick_counter_get();

timer_loop:
	list = u_tmr_list.current;
	p=list->timers[1];

	while(p != NULL && p->timeout <= tickcount)
	{
		/*  some timer has expired */
		if(p->func_cb != NULL) /*  is it a callback timer ? */
		{
			repeat = (u_tick_t)((p)->func_cb()); /* execute callback */
			if (repeat > 0)
			{ /* needs to repeat after "repeat" time ? */
			  timeout = (u32)((u32)tickcount + (u32)repeat);
			  if (timeout >= TICK_COUNT_OVERFLOW)
			  {
				p->timeout = (u_tick_t)(timeout - TICK_COUNT_OVERFLOW);
				list_tmp = u_tmr_list.future; // add into future list
				list_tmp->timers[++list_tmp->count] = p; // insert at the end
				HeapUp(list_tmp->timers,list_tmp->count);
				list->timers[1]=list->timers[list->count]; // remove from current list
				list->timers[list->count] = NULL;
				list->count--;
			  }
			  else
			  {
				p->timeout = (u_tick_t)timeout;
			  }
			}
			else
			{
				goto remove_timer;
			}
		}else
		{
			/* it is task timer ? */
			u_assert(p->u_id < MAX_ID);
			if(p->u_id > 0)
			{
				U_EnterCritical();
					SET_READYLIST_PRIO(U_TCB[p->u_id].arg->prio);
				U_ExitCritical();

				run_scheduler = 1;
			}

			remove_timer:
				p->timeout = 0;
				p->func_cb = NULL;
				list->timers[1]=list->timers[list->count]; // remove from current list
				list->timers[list->count] = NULL;
				list->count--;
		}

        HeapDown (list->timers, 1, list->count); // order heap
        p=list->timers[1];
	}

    if(tickcount == TIMER_MAX_COUNTER)
    {
      if(p==NULL)
      {
        /* time to switch lists */
        void* tmp = u_tmr_list.current;
        u_tmr_list.current = u_tmr_list.future;
        u_tmr_list.future = tmp;
        list = u_tmr_list.current;
        p=list->timers[1];
      }
      else
      {
        /* there is a delayed timer */
        tickcount++;
        goto timer_loop;
      }
    }

    if(run_scheduler)
    {
        U_EnterCritical();
        U_SCHEDULER();
        U_ExitCritical();
    }

}


