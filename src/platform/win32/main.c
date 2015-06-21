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

/* Contiki compatibility tests */
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winsock2.h>
#include <stdio.h>
#include <fcntl.h>

#include "contiki-net.h"
#include "sys/clock.h"

#if 0
#include "../../apps/directory/directory-dsc.h"
#include "../../apps/webbrowser/www-dsc.h"
#endif

#include "sys/etimer.h"
#include "net/wpcap-drv.h"


PROCINIT(&etimer_process,
	 &wpcap_process,
	 &tcpip_process,
	 &resolv_process);

int main(int argc, char **argv)
{

  U_INIT();  /* Initialize core variables */
  
  /* Initialize the utasks,  semaphores  and timers with U_TASK_INIT(). */
  #include "u-init-xmacro.h"
  
  /* Initialize the a mutex with U_MUTEX_INIT(). */
  U_MUTEX_INIT(&mutex_a,9);
 

  /* Contiki test */
  process_init();
  procinit_init();
  //autostart_start(autostart_processes);

#if !NETSTACK_CONF_WITH_IPV6
  {
    uip_ipaddr_t addr;
    uip_ipaddr(&addr, 10,1,1,1);
    uip_sethostaddr(&addr);
    log_message("IP Address:  ", inet_ntoa(*(struct in_addr*)&addr));

    uip_ipaddr(&addr, 255,0,0,0);
    uip_setnetmask(&addr);
    log_message("Subnet Mask: ", inet_ntoa(*(struct in_addr*)&addr));

    uip_ipaddr(&addr, 10,1,1,100);
    uip_setdraddr(&addr);
    log_message("Def. Router: ", inet_ntoa(*(struct in_addr*)&addr));

    uip_ipaddr(&addr, 10,1,1,1);
    uip_nameserver_update(&addr, UIP_NAMESERVER_INFINITE_LIFETIME);
    log_message("DNS Server:  ", inet_ntoa(*(struct in_addr*)&addr));
  }

#else /* NETSTACK_CONF_WITH_IPV6 */
#if !UIP_CONF_IPV6_RPL
#ifdef HARD_CODED_ADDRESS
  uip_ipaddr_t ipaddr;
  uiplib_ipaddrconv(HARD_CODED_ADDRESS, &ipaddr);
  if ((ipaddr.u16[0]!=0) || (ipaddr.u16[1]!=0) || (ipaddr.u16[2]!=0) || (ipaddr.u16[3]!=0)) {
#if UIP_CONF_ROUTER
    uip_ds6_prefix_add(&ipaddr, UIP_DEFAULT_PREFIX_LEN, 0, 0, 0, 0);
#else /* UIP_CONF_ROUTER */
    uip_ds6_prefix_add(&ipaddr, UIP_DEFAULT_PREFIX_LEN, 0);
#endif /* UIP_CONF_ROUTER */
#if !UIP_CONF_IPV6_RPL
    uip_ds6_set_addr_iid(&ipaddr, &uip_lladdr);
    uip_ds6_addr_add(&ipaddr, 0, ADDR_AUTOCONF);
#endif
  }
#endif /* HARD_CODED_ADDRESS */
#endif
#endif

  /* Then we run the utasks using priority scheduling, forever */
  //U_RUN();

  fflush(stderr);
  while(1)
  {
		 process_run();
		 etimer_request_poll();
  }
   
  return 0;
  
  for(;;)
  {

  } /* loop forever */

}


/*-----------------------------------------------------------------------------------*/
void
debug_printf(char *format, ...)
{
  va_list argptr;
  char buffer[1024];

  va_start(argptr, format);
  vsprintf(buffer, format, argptr);
  va_end(argptr);

#if WITH_GUI
  OutputDebugString(buffer);
#else /* WITH_GUI */
  fputs(buffer, stderr);
#endif /* WITH_GUI */
}
/*-----------------------------------------------------------------------------------*/
void
uip_log(char *message)
{
  debug_printf("%s\n", message);
}
/*-----------------------------------------------------------------------------------*/
void
log_message(const char *part1, const char *part2)
{
  debug_printf("%s%s\n", part1, part2);
}
/*-----------------------------------------------------------------------------------*/







 



