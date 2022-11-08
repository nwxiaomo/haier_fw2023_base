#include "includes.h"
#include "SEGGER_RTT.h"

char rt_hw_console_getchar(void)
{
    int ch;
    ch = SEGGER_RTT_GetKey();
    return ch;
}

void rt_hw_console_output(const char *str)
{
    rt_enter_critical();
    SEGGER_RTT_printf(0, "%s", str);
    rt_exit_critical();
}
