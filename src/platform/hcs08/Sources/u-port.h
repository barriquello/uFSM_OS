 /*
 * Copyright (c) 2015, Universidade Federal de Santa Maria.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file is part of the uFSM real time operating system.
 *
 * Author: Carlos H. Barriquello <barriquello@gmail.com>
 *
 */
/**
 * \file u-port.h
 * Platform dependent code
 * \author
 * Carlos H. Barriquello <barriquello@gmail.com>
 *
 */

#include "u-config.h"
#if PLATFORM == HCS08

#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
 
#ifndef U_PORT_H_
#define U_PORT_H_


/* hardware dependent code */
#define CONF_CPU_CLOCK_HZ				  4139304
#define CONF_U_TIME_TICK_RATE_HZ    	  1000

#define TICKTIMER_INT_HANDLER()

extern  void port_timer_init(void);
extern int port_timer(void);

#define PORT_U_TIME_TICK_INIT()		port_timer_init()
#define PORT_U_TIME_TICK()			port_timer()
/******************************************/
/* hardware dependent - must be configured */


/* ported types */
typedef char 			uint8_t;
typedef signed char 	int8_t;
typedef unsigned int    uint16_t;
typedef int       		int16_t;
typedef unsigned long   uint32_t;
typedef long       		int32_t;


typedef uint8_t       u08;
typedef int8_t        s08;
typedef uint16_t      u16;
typedef int16_t       s16;
typedef uint32_t   	  u32;
typedef int32_t       s32;

#define U_EnterCritical()	DisableInterrupts;
#define U_ExitCritical()	EnableInterrupts;
#define U_Enable_Nesting()  U_ExitCritical();

#include <assert.h>
#if 0
#define u_assert(e)  					 	\
						do{	if(!(e)) {			\
							U_PRINTF("assert fail at %s:%d!\n", __FILE__, __LINE__);}	 \
							assert((e)); \
						}while(0);
#else
#define u_assert(e)  	;
#endif

#ifndef U_DEBUG_PRINTF
#define U_DEBUG_PRINTF					  1
#endif

#if U_DEBUG_PRINTF == 1
#include <stdio.h>
#include <stdarg.h>
#define U_PRINTF(x)	 (void)printf(x);
#else
#define U_PRINTF(x)	   ;//do{}while(0);
#endif

#endif /* U_PORT_H_ */

#endif
