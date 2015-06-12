/**
 * \file u_port.h
 * Platform dependent code
 * \author
 * Carlos H. Barriquello <barriquello@gmail.com>
 *
 */

 #include "u_config.h" 
 #if PLATFORM == WIN32
 
#ifndef U_PORT_H_
#define U_PORT_H_


/* hardware dependent code */
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


#define U_EnterCritical()
#define U_EnterCritical()
#define U_ExitCritical()
#define U_ExitCritical()
#define U_Enable_Nesting()  	U_ExitCritical();

#include <assert.h>
#define u_assert(e)  					 	\
						do{	if(!(e)) {			\
							printf("assert fail at %s:%d!\n", __FILE__, __LINE__);}	 \
							assert((e)); \
						}while(0);

#endif /* U_PORT_H_ */

#endif
