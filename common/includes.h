#ifndef _INCLUDES_H
#define _INCLUDES_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "n32g430.h"
#include <rtthread.h>
#include <rthw.h>

#include "UserStdint.h"
#include "debug.h"


//#define DEBUG_Enable   // 调试用

#define LOG_OPEN

#define BOARD_VERSION_0     (0)     
#define BOARD_VERSION_1     (0)
#define BOARD_VERSION_2     (2)
#define BOARD_VERSION_3     (0)			// 版本号

#define BOARD_BUILD_DATE			"20220928"	// 日期

#define PROJECT_NAME		"FW2023A"	// 项目名

#define MCU_NAME            "N32G430G8Q7"	// 芯片名

//#define WDG_EN                   // 默认开启


#endif
