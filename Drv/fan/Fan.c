#include "Fan.h"
#include "monitor.h"


Device_t Fan = {0};


void Fan_Init(void)
{
	
}

//////// Bsp
void Fan_ON(void)
{
	  Inhale_Duty_Set(60);
}

void Fan_Off(void)
{
	  Inhale_Duty_Set(0);
}

//////// 状态跳转
void Fan_Start(void)
{
	if( base_module.Alternating_Current_Zero_Info.ModuleState == Working_State_Set )
	{
		Fan_ON();
		Fan.State = State_Run;
	}
}

void Fan_Stop(void)
{
    Fan_Off();
    Fan.State = State_Stop;
}

void Fan_Task(void)
{
    if (50 == Mcu.Tick_Loop_100ms)
    {
        switch (Fan.State)
        {
            case State_Stop:
                break;

            case State_Run:
							  if( base_module.Alternating_Current_Zero_Info.ModuleState == Working_State_Reset )
								{
									Fan_Stop();
								}
                break;

            default:		
				
                break;
        }
    }
}
