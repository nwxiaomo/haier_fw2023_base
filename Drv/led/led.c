#include "led.h"
#include "mop.h"
#include "monitor.h"



Device_t rubbish_full_led = {0};
Device_t clean_led = {0};
Device_t fault_led = {0};

void Led_Init(void)
{
	
}

//////// Bsp
void Rubbish_Full_Led_ON(void)
{
	  RUBBISH_FULL_LED_ON();
}

void Rubbish_Full_Led_OFF(void)
{
	  RUBBISH_FULL_LED_OFF();
}

void Clean_Led_ON(void)
{
	  CLEAN_LED_ON();
}

void Clean_Led_OFF(void)
{
	  CLEAN_LED_OFF();
}

void Fault_Led_ON(void)
{
	  FAULT_LED_ON();
}

void Fault_Led_OFF(void)
{
	  FAULT_LED_OFF();
}

//////// 状态跳转
void Rubbish_Full_Led_Start(void)
{
	Rubbish_Full_Led_ON();
	rubbish_full_led.State = State_Run;
}

void Rubbish_Full_Led_Stop(void)
{
    Rubbish_Full_Led_OFF();
    rubbish_full_led.State = State_Stop;
}

void Clean_Led_Start(void)
{
	Clean_Led_ON();
	clean_led.State = State_Run;
}

void Clean_Led_Stop(void)
{
    Clean_Led_OFF();
    clean_led.State = State_Stop;
}

void Fault_Led_Start(void)
{
	Fault_Led_ON();
	fault_led.State = State_Run;
}

void Fault_Led_Stop(void)
{
    Fault_Led_OFF();
    fault_led.State = State_Stop;
}




void All_Led_Close(void)
{
	Rubbish_Full_Led_Stop();
	Clean_Led_Stop();
	Fault_Led_Stop();
}

void Led_Task(void)
{
    if (50 == Mcu.Tick_Loop_100ms)
    {
        switch (rubbish_full_led.State)
        {
            case State_Stop:
							  if( base_module.Trash_Basket_Full_Info.ModuleState == Working_State_Set)
								{
									Rubbish_Full_Led_Start();
								}
                break;

            case State_Run:	
							  if( base_module.Trash_Basket_Full_Info.ModuleState == Working_State_Reset)
								{
									Rubbish_Full_Led_Stop();
								}
                break;

            default:		
                break;
        }
				
				switch (clean_led.State)
        {
            case State_Stop:
							  if(Mop.State == MopState_Run)
								{
									Clean_Led_Start();
								}
                break;

            case State_Run:
							  if(Mop.State != MopState_Run)
								{
									Clean_Led_Stop();
								}
                break;

            default:		
				
                break;
        }
				
				switch (fault_led.State)
        {
            case State_Stop:
							  if( base_module.Base_Inflow_Info.ModuleState == Working_State_Set)
								{
									Fault_Led_Start();
								}
                break;

            case State_Run:	
							  if( base_module.Base_Inflow_Info.ModuleState == Working_State_Reset)
								{
									Fault_Led_Stop();
								}
                break;

            default:		
				
                break;
        }
				
    }
}
