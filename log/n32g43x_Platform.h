#ifndef __N32G43X_PLATFORM_H__
#define __N32G43X_PLATFORM_H__

#include <stdint.h>
#include <stdbool.h>
  
typedef enum {
	LOG_DEBUG = 0,
	LOG_INFO,
	LOG_WARN,
	LOG_ERROR
} log_lv_e;


#define LOG_OPEN
#define RT_LOG_OPEN

#ifdef LOG_OPEN
	#define LOG_LV			LOG_DEBUG			/* log output level */
	#define LOG_BUF_SIZE	128					/* max chars per output log */

	#define LOG_DEB		  LOG
	#define LOG_INF	    WARNING
	#define LOG_ERR	    ERROR
#else
	#define LOG_DEBUG(fmt, args...)
	#define LOG_INF(fmt, args...)
	#define LOG_ERR(fmt, args...)
#endif



void Log_Init(void);
void platform_log(log_lv_e lv, const char *fmt, ...);

#endif

