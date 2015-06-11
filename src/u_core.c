
#define DEFINE_U_CORE_VARIABLES
#include "u_core.h"
#include "u_sem.h" /* semaphores services */
#include "u_mutex.h"
#include "u_time.h"


#if (U_SCHED_OPT == 1)

const u08 U_SchedTbl[] = {
  0, 0, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3,  /* 0x00 to 0x0F */
  4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,  /* 0x10 to 0x1F */
  5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,  /* 0x20 to 0x2F */
  5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,  /* 0x30 to 0x3F */
  6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,  /* 0x40 to 0x4F */
  6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,  /* 0x50 to 0x5F */
  6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,  /* 0x60 to 0x6F */
  6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,  /* 0x70 to 0x7F */
  7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,  /* 0x80 to 0x8F */
  7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,  /* 0x90 to 0x9F */
  7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,  /* 0xA0 to 0xAF */
  7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,  /* 0xB0 to 0xBF */
  7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,  /* 0xC0 to 0xCF */
  7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,  /* 0xD0 to 0xDF */
  7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,  /* 0xE0 to 0xEF */
  7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,  /* 0xF0 to 0xFF */
};

#elif (U_SCHED_OPT == 2)

const u08 U_SchedTbl[] = {
  0, 0, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3,  /* 0x00 to 0x0F */
};

#endif

/* GLOBAL EXTERNAL variables */
U_EXTERN const U_PRIORITYLIST u_prio_mask[]=
{
  0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0x0100,0x0200,0x0400,0x0800,0x1000,0x2000,0x4000,0x8000
};

U_EXTERN u08 u_priority_list[MAX_NUM_U_TASKS];
U_EXTERN U_PRIORITYLIST u_ready_list; /* List of Ready Priorities */
 
U_EXTERN volatile u08 u_curr; /* current pt */
U_EXTERN volatile u08 u_next; /* next pt */
U_EXTERN u08 U_STACK[U_STACK_SIZE];	/** stack task */


/*---------------------------------------------------------------*/
/******************* init ***************/
/* used for initialization of system variables 	*******/
 
void U_INIT(void)
{
     u08 i;
     for(i=1;i<MAX_NUM_U_TASKS;i++)
     {
       u_priority_list[i] = -1;
     }
     u_priority_list[0] = 0;  /* for U_idle */
     u_ready_list = 1;       /* U_idle always ready */
     u_next = 0;
     u_curr = 0;
     u_int_nesting = 0;
     u_stack_cnt = 0;
     u_time_init();
}

/*---------------------------------------------------------------*/
/******************* scheduler ***************/

u08 U_Scheduler(U_PRIORITYLIST list){
    
#if (U_SCHED_OPT == 0)
    u08 list_tmp, off;

     
    if (list > 0xFF)
    {
        list_tmp = (u08)(list >> 8);
        off = 8;      
    }else
    {
        list_tmp = (u08)list;
        off = 0; 
    } 

    
    if (list_tmp > 0x0F)
    {
      if (list_tmp > 0x3F)
      {
        if (list_tmp > 0x7F)
        {
          return off+7;
        }
        else
        {
          return off+6;
        }
      }
      else
      {
        if (list_tmp > 0x1F)
        {
          return off+5; 
        }
        else
        {
          return off+4;
        }
      }
    }
    else
    {
      if (list_tmp > 0x03)
      {
        if (list_tmp > 0x07)
        {
          return off+3;
        }
        else
        {
          return off+2;
        }
      }
      else
      {
        if (list_tmp > 0x01)
        {
          return off+1;
        }
        else
        {
          return off+0;
        }
      }
    }
#elif (U_SCHED_OPT == 1)

    u08 list_tmp;
    
    if (list > 0xFF)
    {
      list_tmp = (u08) (list >> 8);
      return (U_SchedTbl[list_tmp] + 8);
    }else
    {
      list_tmp = (u08)list;
      return (U_SchedTbl[list_tmp]);
    }
    
#elif (U_SCHED_OPT == 2)

    u08 list_tmp;
    
    if (list > 0xFF)
    {
      list_tmp = (u08) (list >> 8);
      if (list_tmp > 0x0F)
      {
         list_tmp = (u08) (list_tmp >> 4);
         return (U_SchedTbl[list_tmp] + 12);
      }else
      {
         return (U_SchedTbl[list_tmp] + 8);
      } 
    }else
    {
      list_tmp = (u08)list;
      if (list_tmp > 0x0F)
      {
         list_tmp = (u08) (list_tmp >> 4);
         return (U_SchedTbl[list_tmp] + 4);
      }else
      {
         return (U_SchedTbl[list_tmp]);
      }    
    }
    
#endif
}

/*---------------------------------------------------------------*/
/******************* task suspend  ***************/
void Task_Suspend(u_task* u)
{
	 u_assert(u_int_nesting == 0); /* can not block inside an ISR */
	 U_EnterCritical();
	 	 RESET_READYLIST_PRIO((u->prio));
	 U_ExitCritical();
}
/*---------------------------------------------------------------*/
/******************* task resume  ***************/
void Task_Resume(prio_t p)
{
	TEST_INT_NESTING(U_EnterCritical(););
	 	 SET_READYLIST_PRIO(p);
	TEST_INT_NESTING(U_ExitCritical(););
}

/*---------------------------------------------------------------*/
/**************** semaphores ******************/

void Sem_Pend(u_task* u, u_sem* s)
{
      u_assert(u_int_nesting == 0); /* can not block inside an ISR */
      U_EnterCritical();
      if(!((s)->count > 0))
      {
        EVENT_PEND(u,s);
      }else
      {
        --(s)->count;          
      } 
      U_ExitCritical();
}
/*---------------------------------------------------------------*/
void Sem_Post(u_task* u, u_sem* s)
{
      (void)u;
      
      TEST_INT_NESTING(U_EnterCritical());
              
      if((s)->waitlist == 0)
      {
        ++(s)->count;                
      }else
      {
        EVENT_POST(u,s);
      }
      
      TEST_INT_NESTING(U_ExitCritical());
}

/************************************************/

/**************** mutexes ******************/

void Mutex_Acquire(u_task* u, u_mutex* s)
{
	  u_assert(u_int_nesting == 0);
      u_assert((s)->owner != u_curr);
      if((s)->count > 0)
      {
        U_EnterCritical();
          EVENT_PEND(u,s);
        U_ExitCritical();
      }else
      {
        (s)->count = 1; 
        (s)->owner = u_curr;
        Mutex_PrioCeil(u,s); /* call priority ceiling function */
      }                                    
}
/*---------------------------------------------------------------*/
void Mutex_Release(u_task* u, u_mutex* s)
{
      //(void)u;
      u_assert((s)->owner == u_curr);
           
      /* Returns to the original priority, if needed */
      if ((u)->prio != (s)->orig_prio)
      {
       
          U_EnterCritical();
			  /* Remove "max priority" from the Ready List*/
			  u_ready_list &= ~(u_prio_mask[(u)->prio]);
			  /* Put the "original priority" into Ready List */
			  u_ready_list |= (u_prio_mask[(s)->orig_prio]);
          U_ExitCritical();
          
          (u)->prio = (s)->orig_prio;
      }
                
      if((s)->waitlist == 0)
      {
        (s)->count = 0;
        (s)->owner = 0;
        (s)->orig_prio = 0;
        u_priority_list[(s)->mtx_prio] = MUTEX_PRIO;
      }else
      {
        /* transfer mutex to next utask */
        u08 _prio = U_Scheduler((s)->waitlist);
        (s)->owner = u_priority_list[_prio];
        (s)->waitlist &= ~u_prio_mask[_prio];
        Mutex_PrioCeil((U_TCB[((s)->owner)].arg),s);
      }
}
/*---------------------------------------------------------------*/
void Mutex_PrioCeil(u_task* u, u_mutex* s)
{
    
    /* Performs the temporary exchange of mutex owner priority, if needed  */            
    if ((s)->mtx_prio > (u)->prio)
    {      
      /* Backup the original priority */
      (s)->orig_prio = (u)->prio;
      
      /* Receives the mutex priority temporarily */
      (u)->prio = (s)->mtx_prio;
      
      /* Priority list change */
      u_priority_list[(s)->mtx_prio] = (s)->owner;
      
      U_EnterCritical();
      
        /* Remove "original priority" from the Ready List */
        u_ready_list &= ~(u_prio_mask[(s)->orig_prio]);
        /* Put the "mutex priority" into Ready List */
        u_ready_list |= (u_prio_mask[(s)->mtx_prio]);
      
      U_ExitCritical();
    }

}
/*---------------------------------------------------------------*/

