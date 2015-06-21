#ifndef CONTIKI_CONF_H_
#define CONTIKI_CONF_H_

#ifdef __CYGWIN__
#include <sys/types.h>
#endif

#define CC_CONF_REGISTER_ARGS 1
#define CC_CONF_FASTCALL
#define CC_CONF_INLINE   __inline

#define ARCH_DOESNT_NEED_ALIGNED_STRUCTS 1


#define CCIF
#define CLIF

#ifdef __CYGWIN__
int strcasecmp(const char*, const char*);
int strncasecmp(const char*, const char*, size_t);
char* strdup(const char*);
#else /* __CYGWIN__ */
#define HAVE_SNPRINTF
#define snprintf    _snprintf
#define strcasecmp  _stricmp
#define strncasecmp _strnicmp
#define strdup      _strdup
#endif /* __CYGWIN__ */


#define LOG_CONF_ENABLED 1
#include "sys/log.h"
CCIF void debug_printf(char *format, ...);


#define CLOCK_CONF_SECOND 1000
typedef unsigned long clock_time_t;

#if 0
typedef   signed char    int8_t;
typedef unsigned char   uint8_t;
typedef   signed short  int16_t;
typedef unsigned short uint16_t;
typedef   signed int    int32_t;
typedef unsigned int   uint32_t;
#endif
#include <stdint.h>

/* These names are deprecated, use C99 names. */
typedef unsigned char   u8_t;
typedef unsigned short u16_t;
typedef          long  s32_t;

typedef unsigned short uip_stats_t;

#define UIP_CONF_LLH_LEN             14
#define UIP_CONF_BUFFER_SIZE         1514
#define UIP_CONF_TCP_SPLIT           1
#define UIP_CONF_LOGGING             0
#define UIP_CONF_UDP_CHECKSUMS       1
#if NETSTACK_CONF_WITH_IPV6
#define UIP_CONF_IP_FORWARD          0
#define NBR_TABLE_CONF_MAX_NEIGHBORS 100
#define UIP_CONF_DS6_DEFRT_NBU       2
#define UIP_CONF_DS6_PREFIX_NBU      5
#define UIP_CONF_MAX_ROUTES          100
#define UIP_CONF_DS6_ADDR_NBU        10
#define UIP_CONF_DS6_MADDR_NBU       0  //VC++ does not allow zero length arrays
#define UIP_CONF_DS6_AADDR_NBU       0  //inside a struct
#else
#define UIP_CONF_IP_FORWARD          1
#endif

#define RESOLV_CONF_SUPPORTS_MDNS              0
#define RESOLV_CONF_SUPPORTS_RECORD_EXPIRATION 0

#include <ctype.h>

#define XMEM_ERASE_UNIT_SIZE (64*1024L)

#endif /* CONTIKI_CONF_H_ */
