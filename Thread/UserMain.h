#ifndef _USER_MAIN_H
#define _USER_MAIN_H

#include "includes.h"


#if (MAIN_LOG_SWITCH == 1)
#define MAIN_LOG_DEBUG		LOG
#define MAIN_LOG_INF	    WARNING
#define MAIN_LOG_ERR	    ERROR
#else
#define OTA_DBG(fmt, args...)  
#define OTA_INF(fmt, args...)  
#define OTA_ERR(fmt, args...)  
#endif

void UserMain(void);


#endif
