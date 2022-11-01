#include "rubbish_Heater.h"
#include "rubbish_Fan.h"
#include "monitor.h"


Device_t rubbish_heater = {0};


void Rubbish_Heater_Init(void)
{
	
}

//////// Bsp
void Rubbish_Heater_ON(void)
{
	  Bsp_Rubbish_Heater_Duty_Set(350);
}

void Rubbish_Heater_Off(void)
{
	  Bsp_Rubbish_Heater_Duty_Set(0);
}

//////// 状态跳转
void Rubbish_Heater_Start(void)
{
	//垃圾风扇不开不能开发热丝
	if( rubbish_fan.State == State_Run && 
		  base_module.Alternating_Current_Zero_Info.ModuleState == Working_State_Set)
	{
		Rubbish_Heater_ON();
		rubbish_heater.State = State_Run;
	}

}

void Rubbish_Heater_Stop(void)
{
    Rubbish_Heater_Off();
    rubbish_heater.State = State_Stop;
}

void Rubbish_Heater_Task(void)
{
    if (50 == Mcu.Tick_Loop_100ms)
    {
        switch (rubbish_heater.State)
        {
            case State_Stop:
                break;

            case State_Run:
								if( base_module.Rubbish_Fan_Info.ModuleState == Working_State_Reset || 
									  base_module.Alternating_Current_Zero_Info.ModuleState == Working_State_Reset)
								{
									Rubbish_Heater_Stop();
								}
                break;

            default:		
				
                break;
        }
    }
}
