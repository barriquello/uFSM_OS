/*
 * u_port.h
 *
 *  Created on: 07/06/2015
 *      Author: Gisele
 */

#ifndef U_PORT_H_
#define U_PORT_H_


/* hardware dependent code - must be ported */
#define configTICK_RATE_HZ    	  1000

#define TICKTIMER_INT_HANDLER()

void TickTimerInit(void);
void TickTimer(void);

/******************************************/
/* hardware dependent - must be configured */

#include <stdint.h>
/* ported types */
typedef uint8_t       u08;
typedef int8_t        s08;
typedef uint16_t      u16;
typedef int16_t       s16;
typedef uint32_t   	  u32;
typedef int32_t       s32;


typedef u16 	U_PRIORITYLIST;

#define U_EnterCritical()
#define U_EnterCritical()
#define U_ExitCritical()
#define U_ExitCritical()
#define U_Enable_Nesting()  	U_ExitCritical();


#include <assert.h>
#define u_assert(e)  	do{assert((e));}while(0);

#endif /* U_PORT_H_ */
