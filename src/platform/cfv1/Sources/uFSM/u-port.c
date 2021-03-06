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
 * \file u-port.c
 * Platform dependent code
 * \author
 * Carlos H. Barriquello <barriquello@gmail.com>
 *
 */
#include "platform-conf.h"
#if PLATFORM == CFV1
 
#include "ufsm-rtos.h"

static u16 tick_counter = 0;

void port_timer_init(void)
{
		
  TPM1SC = 0x00;                       				    /* Para e zera contador */
  TPM1MOD = (CONF_CPU_CLOCK_HZ / CONF_U_TIME_TICK_RATE_HZ); 	/* Configura o periodo */
  TPM1SC = 0x48;                       					/* Dispara o temporizador e habilita ISR */
}

int port_timer(void)
{
	u16 time_diff;

	__RESET_WATCHDOG();
	
	DisableInterrupts;
	
	time_diff = tick_counter;	
	tick_counter = 0;	
	
	EnableInterrupts;	

	u_clock_set(u_clock_get() + time_diff);
	
	if(time_diff > 0)
	{
		return 1;
	}
	return 0;
}

#if (NESTING_INT == 1)
#pragma TRAP_PROC
void TickTimer(void)
#else
interrupt void TickTimer(void)
#endif
{	  	
	TPM1SC_TOF = 0;  /*  clear ISR */
	tick_counter++;
}

/* emulate stdout */
static char term_out[128];
static char term_out_idx = 0;
void TERMIO_PutChar(char c)
{
	term_out[term_out_idx++] = c;
	if(term_out_idx >= sizeof(term_out))
	{
		term_out_idx = 0;
	}
}


#endif


