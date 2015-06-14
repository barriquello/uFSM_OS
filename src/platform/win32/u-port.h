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
#if PLATFORM == WIN32
 
#ifndef U_PORT_H_
#define U_PORT_H_


/* hardware dependent code */
#define CONF_U_TIME_TICK_RATE_HZ    	  1000

#define TICKTIMER_INT_HANDLER()

extern  void port_timer_win_init(void);
extern int port_timer_win(void);

#define PORT_U_TIME_TICK_INIT()		port_timer_win_init()
#define PORT_U_TIME_TICK()			port_timer_win()
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

typedef unsigned long long clock_t;

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
