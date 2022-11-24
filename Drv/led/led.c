#include "led.h"
#include "mop.h"
#include "monitor.h"

led_list_t led_list = {0};

Device_t rubbish_full_led = {0};
Device_t clean_led = {0};
Device_t fault_led = {0};

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

void Led_Init(void)
{
	led_list.rubbish_full_led.led_on = Rubbish_Full_Led_ON;
	led_list.rubbish_full_led.led_off = Rubbish_Full_Led_OFF;

	led_list.clean_led.led_on  = Clean_Led_ON;
	led_list.clean_led.led_off = Clean_Led_OFF;

	led_list.fault_led.led_on = Fault_Led_ON;
	led_list.fault_led.led_off = Fault_Led_OFF;
	
//	led_list.rubbish_full_led.led_state = LedState_FlashFast;
//	led_list.clean_led.led_state = LedState_On;
//	led_list.fault_led.led_state = LedState_FlashFast;
	
//	Rubbish_Full_Led_Start();
//	Clean_Led_Start();
//	Fault_Led_Start();
}

static void Led_State_updata(void)
{
		static int Flash_Tick;
    for (uint32_t i=0; i<sizeof(led_list_t)/sizeof(led_info_t); i++)
    {
        switch ((*((led_info_t *)(&led_list.rubbish_full_led) + i)).led_state)
        {
            case LedState_Off:
                (*((led_info_t *)(&led_list.rubbish_full_led) + i)).led_off();
                break;

            case LedState_On:
                (*((led_info_t *)(&led_list.rubbish_full_led) + i)).led_on();
                break;

            case LedState_FlashSlow:
                if (Flash_Tick < 2000)
                {
                    (*((led_info_t *)(&led_list.rubbish_full_led) + i)).led_on();
                }
                else
                {
                    (*((led_info_t *)(&led_list.rubbish_full_led) + i)).led_off();
                }
                break;

            case LedState_FlashFast:
                if (Flash_Tick % 1000 < 500)
                {
                    (*((led_info_t *)(&led_list.rubbish_full_led) + i)).led_on();
                }
                else
                {
                    (*((led_info_t *)(&led_list.rubbish_full_led) + i)).led_off();
                }
                break;

            default:
                break;
        }
    }

    //////// 闪烁 ////////
    Flash_Tick++;
    if (Flash_Tick >= 4000)
    {
        Flash_Tick = 0;
    }

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
									led_list.rubbish_full_led.led_state = LedState_FlashFast;
								}
                break;

            case State_Run:	
							  if( base_module.Trash_Basket_Full_Info.ModuleState == Working_State_Reset)
								{
									led_list.rubbish_full_led.led_state = LedState_Off;
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
									led_list.clean_led.led_state = LedState_On;
								}
                break;

            case State_Run:
							  if(Mop.State != MopState_Run)
								{
									led_list.clean_led.led_state = LedState_Off;
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
									led_list.fault_led.led_state = LedState_FlashFast;
								}
                break;

            case State_Run:	
							  if( base_module.Base_Inflow_Info.ModuleState == Working_State_Reset)
								{
									led_list.fault_led.led_state = LedState_Off;
								}
                break;

            default:		
				
                break;
        }	
    }
		
		Led_State_updata();
}
