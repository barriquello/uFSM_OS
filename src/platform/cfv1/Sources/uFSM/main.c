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
 * \file main.c
 * Entry point, system initialization
 * \author
 * Carlos H. Barriquello <barriquello@gmail.com>
 *
 */

/* We must always include ufsm-rtos.h in our utasks code. */
#include "ufsm-rtos.h"


#ifdef __cplusplus
 extern "C"
#endif

/**
 * Finally, we have the main loop. Here is where the utasks are
 * initialized and scheduled. First, however, we define the
 * utask state variables, functions and priorities  in the "U_TASK_TABLE"
 * by including 'install_apps.h".
 */

#include "install-apps.h"

#define DEFINE_U_VARIABLES
#include "u-xmacro.h"


u_mutex mutex_a, mutex_b;


/* Compile-time error checking */
#define U_ASSERT_FN
#include "lib/u-assert.h"

#include "drivers.h"
 
#if ((defined _MCF51MM256_H) || (defined _MCF51JE256_H) || (defined _MCF51JE128_H))
const unsigned char boot:0x040A = 0x00;   //zero out checksum to bypass boot loader
#endif /* (defined _MCF51MM256_H) || (defined _MCF51JE256_H) */
 
void main(void)
{

 /* initial the system */
  Init_Sys();

  U_INIT();  /* Initialize core variables */
  
  /* Initialize the utasks,  semaphores  and timers with U_TASK_INIT(). */
  #include "u-init-xmacro.h"
  
  /* Initialize the a mutex with U_MUTEX_INIT(). */
  U_MUTEX_INIT(&mutex_a,9);
 
  /* Then we run the utasks using priority scheduling, forever */
  U_RUN();
   
  //return 0;
  
  for(;;)
  {

  } /* loop forever */

}


void BRTOS_TimerHook(void)
{

}








 



