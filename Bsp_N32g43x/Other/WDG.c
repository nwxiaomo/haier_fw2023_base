#include "WDG.h"


#ifdef WDG_EN

void WDG_Init(void)
{
    IWDG_Write_Protection_Enable();
		IWDG_Prescaler_Division_Set(IWDG_CONFIG_PRESCALER_DIV32);
	
    /* Set counter reload value to obtain 250ms IWDG TimeOut.
      LsiFreq = 40KHz
			Counter Reload Value = 250ms/IWDG counter clock period
                            = 250ms / (LSI/32)
                            = 0.25s / (LsiFreq/32)
                            = LsiFreq/(32 * 4)
                            = LsiFreq/128 */
	
    IWDG_Counter_Reload(625);
		LOG_DEB("Bsp IWDG init finish.");
}


void WDG_Start(void)
{
    IWDG_Enable();
}

void WDG_Feed(void)
{
    //fwdgt_counter_reload();
    IWDG_Key_Reload();
}

#endif
