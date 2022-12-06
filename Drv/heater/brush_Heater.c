#include "brush_Heater.h"
#include "brush_Fan.h"
#include "monitor.h"
#include "IO.h"

brush_heater_info_t brush_heater = {0};


void Brush_Heater_DeInit(void)
{
	brush_heater.working_state = HEATER_NORMAL;
}

//////// Bsp
static void Brush_Heater_Open(void)
{
	  BRUSH_HEATER_ON();
}

static void Brush_Heater_Close(void)
{
	  BRUSH_HEATER_OFF();
}

//////// 状态跳转
void Brush_Heater_Start(void)
{
		//风扇不开不能开发热体
	  //工作异常不能再开发热体
		if( base_module.Brush_Fan_Info.ModuleState == Working_State_Set && brush_heater.working_state == HEATER_NORMAL )
		{	
			Brush_Heater_Open();
			brush_heater.device.State = State_Run;
		}
		
}

void Brush_Heater_Stop(void)
{
    Brush_Heater_Close();
    brush_heater.device.State = State_Stop;
}

void Brush_Heater_Task(void)
{
    if (50 == Mcu.Tick_Loop_100ms)
    {
        switch (brush_heater.device.State)
        {
            case State_Stop:
								
                break;

            case State_Run:
								if( (base_module.Brush_Fan_Info.ModuleState == Working_State_Reset)  )
								{
									Brush_Heater_Stop();
								}
								
								if( (base_module.Base_NTC_Info.ModuleState == Working_State_Set) )
								{
									brush_heater.working_state = HEATER_ABNORMAL;
									Brush_Heater_Stop();
								}
                break;

            default:		
				
                break;
        }
    }
}
