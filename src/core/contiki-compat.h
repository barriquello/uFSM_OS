/*
 * contiki-compat.h
 *
 *  Created on: 13/06/2015
 *      Author: Gisele
 */

#ifndef CORE_CONTIKI_COMPAT_H_
#define CORE_CONTIKI_COMPAT_H_

/* add compatibiity with Contiki */
#include "ufsm-rtos.h"
#include <stdint.h>
#include "sys/pt.h"
#include "lib/memb.h"

#define PROCESS(a,b)
#define CLOCK_SECOND	1
typedef u_event_t process_event_t;

//#include "net/contiki-conf.h"
//#include "net/contiki-net.h"

#ifndef CONTIKI_CONF_H_
#define CONTIKI_CONF_H_
#define CCIF
#define CLIF

/* These names are deprecated, use C99 names. */
typedef uint8_t   u8_t;
typedef uint16_t u16_t;
typedef  int32_t s32_t;

typedef unsigned short uip_stats_t;

#define UIP_CONF_UIP_IP4ADDR_T_WITH_U32 1

typedef unsigned long clock_time_t;
#define CLOCK_CONF_SECOND 1000

#endif /* CONTIKI_CONF_H_ */


#endif /* CORE_CONTIKI_COMPAT_H_ */
