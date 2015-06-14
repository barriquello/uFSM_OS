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
 * \file u-config.h
 * System configuration
 * \author
 * Carlos H. Barriquello <barriquello@gmail.com>
 *
 */

#ifndef U_CONFIG_H_
#define U_CONFIG_H_

#include "platform-conf.h"

#define CONF_U_CORE_SCHED_OPT    		  1
#define CONF_U_CORE_INT_NEST_ENABLE       0
#define CONF_U_TASK_STACK_SIZE   		  256
#define CONF_U_TASK_MAX_NUM   	 		  32
#define CONF_U_TIMERS_MAX_NUM	 		  2
#define CONF_U_TASK_IDLE()

#define U_DEBUG_PRINTF					  0

#endif /* U_CONFIG_H_ */
