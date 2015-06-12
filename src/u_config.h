/**
 * \file u_config.h
 * System configuration
 * \author
 * Carlos H. Barriquello <barriquello@gmail.com>
 *
 */

#ifndef U_CONFIG_H_
#define U_CONFIG_H_

#include "platform_conf.h"

#define U_SCHED_OPT     		1
#define U_IDLE()
#define U_INT_NEST_ENABLE       0
#define U_STACK_SIZE  			256
#define U_DEBUG_PRINTF			1
#define U_MAX_NUM_TASKS			32

#endif /* U_CONFIG_H_ */
