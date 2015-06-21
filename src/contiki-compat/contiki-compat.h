/*
 * contiki-compat.h
 *
 *  Created on: 13/06/2015
 *      Author: Gisele
 */

#ifndef CORE_CONTIKI_COMPAT_H_
#define CORE_CONTIKI_COMPAT_H_

/* add compatibility with Contiki */
#include "ufsm-rtos.h"
#include "sys/pt.h"
#include "lib/memb.h"

#include "contiki-conf.h"

typedef unsigned short uip_stats_t;
#define UIP_CONF_UIP_IP4ADDR_T_WITH_U32 1

#endif /* CORE_CONTIKI_COMPAT_H_ */
