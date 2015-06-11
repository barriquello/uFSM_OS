/*
 * platform_conf.h
 *
 */

#ifndef PLATFORM_CONF_H_
#define PLATFORM_CONF_H_

#include "platforms.h"
#define  PLATFORM 	WIN32

#if PLATFORM == WIN32
#include "win32/u_port.h"
#endif


#endif /* PLATFORM_CONF_H_ */
