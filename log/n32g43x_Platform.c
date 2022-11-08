#ifndef __CONTORL_CENTER_PLATFORM_PSOC__H__
#define __CONTORL_CENTER_PLATFORM_PSOC__H__

#include "n32g43x_Platform.h"
#include "App.h"

#ifndef __ASM
#define __ASM			 __asm										/*!< asm keyword for ARM Compiler */
#endif

#if 0
void svc_call(void)                     
{                                                           
    __ASM volatile("svc 0");                               
}
#endif

#ifndef LOG_BUF_SIZE
#define LOG_BUF_SIZE	512
#endif

#ifndef LOG_LV
#define LOG_LV LOG_ERROR
#endif

#define STR_VERSION(R) #R

void Log_Init(void)
{	
		extern void SEGGER_RTT_Init(void);
		SEGGER_RTT_Init();
	
		SEGGER_RTT_printf(0, "**********************************************************************\n");
		SEGGER_RTT_printf(0, "********************* Reset reason:0x%x ************************\n",
							        RCC->CTRLSTS);
		SEGGER_RTT_printf(0, "********************** Application started ***************************\n");  
		SEGGER_RTT_printf(0, "********* Version:%d.%d.%d.%d,Compiled at:%s %s **********\n", 
											BOARD_VERSION_0,BOARD_VERSION_1,BOARD_VERSION_2,BOARD_VERSION_3,(uint32_t)__DATE__, (uint32_t)__TIME__);
		SEGGER_RTT_printf(0, "**********************************************************************\n\n");
}

void Debug_Printf(const char *fmt, ...)
{
    va_list args;
    static char rt_log_buf[LOG_BUF_SIZE];

    va_start(args, fmt);
    rt_vsnprintf(rt_log_buf, sizeof(rt_log_buf) - 1, fmt, args);
	
	  extern void app_console_output(const char *str);
    app_console_output(rt_log_buf);
	
    va_end(args);
}



void platform_log(log_lv_e lv, const char *fmt, ...)
{
    va_list  vArgs;
    char buf[LOG_BUF_SIZE];
		if (lv < LOG_LV){
			return;
		}
      
    va_start(vArgs,fmt);
    vsnprintf( (char*)(buf), LOG_BUF_SIZE, (char const*)fmt, vArgs );
    va_end(vArgs);
     
		Debug_Printf(buf);
}

#endif


