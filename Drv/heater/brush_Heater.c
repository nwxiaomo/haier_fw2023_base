#include "brush_Heater.h"
#include "brush_Fan.h"
#include "monitor.h"

Device_t brush_heater = {0};


void Brush_Heater_Init(void)
{
	
}

//////// Bsp
void Brush_Heater_ON(void)
{
	  Bsp_Brush_Heater_Duty_Set(900);
}

void Brush_Heater_Off(void)
{
	  Bsp_Brush_Heater_Duty_Set(0);
}

//////// 状态跳转
void Brush_Heater_Start(void)
{
		//风扇不开不能开发热体
		if( brush_fan.State == State_Run && 
			  base_module.Alternating_Current_Zero_Info.ModuleState == Working_State_Set)
		{	
			Brush_Heater_ON();
			brush_heater.State = State_Run;
		}
		
}

void Brush_Heater_Stop(void)
{
    Brush_Heater_Off();
    brush_heater.State = State_Stop;
}

void Brush_Heater_Task(void)
{
    if (50 == Mcu.Tick_Loop_100ms)
    {
        switch (brush_heater.State)
        {
            case State_Stop:
								
                break;

            case State_Run:
								if( base_module.Brush_Fan_Info.ModuleState == Working_State_Reset || 
									  base_module.Alternating_Current_Zero_Info.ModuleState == Working_State_Reset)
								{
									Brush_Heater_Stop();
								}
                break;

            default:		
				
                break;
        }
    }
}
