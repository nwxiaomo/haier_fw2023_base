#include "drain_Valve.h"

Drain_Valve_Info_t drain_valve_info = {0};

void Drain_Valve_Init(void)
{
	
}

//////// Bsp
void Drain_Valve_Forward(void)
{
	Drain_Valve_Duty_Set(DRAIN_FORWARD_DUTY);
}

void Drain_Valve_Backward(void)
{
	Drain_Valve_Duty_Set(DRAIN_BACKWARD_DUTY); 
}

void Drain_Valve_Off(void)
{
		Drain_Valve_Duty_Set(0);
    DRAIN_VALVE_CTRL_OFF();
    DRAIN_VALVE_PWM_OFF();
}

//////// 状态跳转
void Drain_Valve_Start(Running_Direction running_state)
{
    switch(running_state)
    {
        case DRAIN_VALVE_FORWARD:

            drain_valve_info.device.State = State_Run;

            if( DRAIN_VALVE_RIGHT_SENSE_READ() != 1 )
            {
                Drain_Valve_Forward();
            }
            break;

        case DRAIN_VALVE_BACKWARD:

            drain_valve_info.device.State = State_Run;

            if( DRAIN_VALVE_LEFT_SENSE_READ() != 1 )
            {
                Drain_Valve_Backward();
            }
            break;

        case DRAIN_VALVE_STOP:

            Drain_Valve_Off();
            drain_valve_info.device.State = State_Stop;
            
            break;

        default:
            break; 
    }

    drain_valve_info.last_running_state = running_state;

}

void Drain_Valve_Stop(void)
{
    Drain_Valve_Off();
    drain_valve_info.device.State = State_Stop;
}

void Drain_Valve_Task(void)
{
    if (50 == Mcu.Tick_Loop_100ms)
    {
        switch (drain_valve_info.device.State)
        {
            case State_Stop:
                break;

            case State_Run:
                break;

            default:		
				
                break;
        }
    }
}
