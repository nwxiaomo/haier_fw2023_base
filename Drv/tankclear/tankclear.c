#include "tankclear.h"
#include "monitor.h"

Device_t tankclear_pump = {0};


void Tank_Clear_Init(void)
{
	
}

//////// Bsp
void Tank_Clear_Pump_ON(void)
{
	  //Bsp_Tank_Clear_Pump_Duty_Set(999);
}

void Tank_Clear_Pump_Off(void)
{
	  //Bsp_Tank_Clear_Pump_Duty_Set(0);
}

//////// 状态跳转
void Tank_Clear_Inject_Start(void)
{
	Tank_Clear_Pump_ON();
	tankclear_pump.State = State_Run;
}

void Tank_Clear_Inject_Stop(void)
{
    Tank_Clear_Pump_Off();
    tankclear_pump.State = State_Stop;
}

void Tank_Clear_Inject_Task(void)
{
    if (50 == Mcu.Tick_Loop_100ms)
    {
        switch (tankclear_pump.State)
        {
            case State_Stop:
                if( base_module.Tank_Clear_Full_Info.ModuleState == Working_State_Reset )
                {
                    Tank_Clear_Inject_Start();
                }

                break;

            case State_Run:
                if( base_module.Tank_Clear_Full_Info.ModuleState == Working_State_Set )
                {
                    Tank_Clear_Inject_Stop();
                }
                break;

            default:		
				
                break;
        }
    }
}
