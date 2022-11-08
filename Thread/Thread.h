#ifndef _THREAD_H
#define _THREAD_H

#include "includes.h"
#include "App.h"

#include "UserMain.h"



//////// 主线程参数
//#define THREAD_MAIN_STACK_SIZE    (1000)
//#define THREAD_MAIN_PRIORITY      (2)


//////// Pid 线程参数
#define THREAD_PID_STACK_SIZE       (1000)
//#define THREAD_PID_PRIORITY         (3)
#define THREAD_PID_PRIORITY         (RT_THREAD_PRIORITY_MAX / 2)


//////// Math 线程参数
#define THREAD_MATH_STACK_SIZE      (1000)
//#define THREAD_MATH_PRIORITY        (4)
#define THREAD_MATH_PRIORITY        (RT_THREAD_PRIORITY_MAX / 2 + 1)




#endif
