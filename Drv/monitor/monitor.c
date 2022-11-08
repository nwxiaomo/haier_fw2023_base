#include "monitor.h"
#include "IO.h"

Module_t base_module = {0};

#define ADC_FILTER_SIZE     (10U)
#define Volt_28_AD   3600  //2.9V // 3480--2.8V

typedef struct
{
    uint8_t index;
    uint8_t length;
    uint16_t filter[ADC_FILTER_SIZE];
}TFilter;

TFilter g_adc_filter = {0};

uint8_t getVoterResult(uint16_t value, uint16_t threshold)
{
    uint32_t sum = 0;
    uint8_t cnt = 0;

    g_adc_filter.filter[g_adc_filter.index] = value;
	
		g_adc_filter.index = (g_adc_filter.index++ >= ADC_FILTER_SIZE)? 0 : g_adc_filter.index++;

    
    g_adc_filter.length = g_adc_filter.length < ADC_FILTER_SIZE ? ++g_adc_filter.length : g_adc_filter.length;

    for(uint8_t i = 0; i < g_adc_filter.length; i++)
    {
        if(g_adc_filter.filter[i] < threshold)
        {
            cnt++;
        }
    }

    return cnt > 8 ? 1 : 0;
}


void Drain_Valve_Info_Update(void)
{
		uint32_t voltage = 0;
	  Working_State newState = Working_State_Reset;
	
    voltage = ADC_2_VOLTAGE(sADC.Value_Filtered_1ms[ADC_CH_DrainValve]);
	
    if (drain_valve.State != State_Run)
    {
        newState = Working_State_Reset;
    }
		else
		{
			if ( voltage < DRAIN_VALUE_WORKING_THRESHOLD)
			{
					newState = Working_State_Reset;
			}
			else
			{
					newState = Working_State_Set;
			}
		}
		

		base_module.Drain_Valve_Info.ModuleState = newState;
		base_module.Drain_Valve_Info.Voltage = voltage;	
}

void Peristaltic_Pump_Info_Update(void)
{
		uint32_t voltage = 0;
	  Working_State newState = Working_State_Reset;
	
    voltage = ADC_2_VOLTAGE(sADC.Value_Filtered_1ms[ADC_CH_PeristalticPumpCurrent]);
	
    if (peristaltic_pump.State != State_Run)
    {
        newState = Working_State_Reset;
    }
		else
		{
			if ( voltage < DRAIN_VALUE_WORKING_THRESHOLD)
			{
					newState = Working_State_Reset;
			}
			else
			{
					newState = Working_State_Set;
			}
		}
		

		base_module.Peristaltic_Pump_Info.ModuleState = newState;
		base_module.Peristaltic_Pump_Info.Voltage = voltage;	
}

void Rubbish_Fan_Info_Update(void)
{
		uint32_t voltage = 0;
	  Working_State newState = Working_State_Reset;
	
    voltage = ADC_2_VOLTAGE(sADC.Value_Filtered_1ms[ADC_CH_RubbishFanCurrent]);
	
    if (rubbish_fan.State != State_Run)
    {
        newState = Working_State_Reset;
    }
		else
		{
			if ( voltage < RUBBISH_FAN_WORK_THRESHOLD)
			{
					newState = Working_State_Reset;
			}
			else
			{
					newState = Working_State_Set;
			}
		}
		

		base_module.Rubbish_Fan_Info.ModuleState = newState;
		base_module.Rubbish_Fan_Info.Voltage = voltage;	
}

void Brush_Fan_Info_Update(void)
{
		uint32_t voltage = 0;
	  Working_State newState = Working_State_Reset;
	
    voltage = ADC_2_VOLTAGE(sADC.Value_Filtered_1ms[ADC_CH_BrushFanCurrent]);
	
    if (brush_fan.State != State_Run)
    {
        newState = Working_State_Reset;
    }
		else
		{
			if ( voltage < BRUSH_FAN_WORK_THRESHOLD)
			{
					newState = Working_State_Reset;
			}
			else
			{
				  LOG_ERR("The fan is working.");
					newState = Working_State_Set;
			}
		}
		

		base_module.Brush_Fan_Info.ModuleState = newState;
		base_module.Brush_Fan_Info.Voltage = voltage;	
}

void Base_Inflow_Info_Update(void)
{
		uint32_t voltage = 0;
	  Working_State newState = Working_State_Reset;
	
    voltage = ADC_2_VOLTAGE(sADC.Value_Filtered_1ms[ADC_CH_Inflow]);
	
    if (getVoterResult(voltage, BASE_INFLOW_THRESHOLD))	//
    {
        newState = Working_State_Set; // 底座水量检测 进水
				LOG_ERR("The water inflow to base.");
    }
    else
    {
        newState = Working_State_Reset;
    }

		base_module.Base_Inflow_Info.ModuleState = newState;
		base_module.Base_Inflow_Info.Voltage = voltage;	
}

void Base_NTC_Info_Update(void)
{
		uint32_t voltage = 0;
	  Working_State newState = Working_State_Reset;
	
    voltage = ADC_2_VOLTAGE(sADC.Value_Filtered_1ms[ADC_CH_NtcTemperature]);
	
    if (getVoterResult(voltage, BASE_NTC_THRESHOLD))	//
    {
        newState = Working_State_Set; // 温度过高
			  LOG_ERR("The base temperature is too high.");
    }
    else
    {
        newState = Working_State_Reset;
    }

		base_module.Base_NTC_Info.ModuleState = newState;
		base_module.Base_NTC_Info.Voltage = voltage;	
}

void Trash_Basket_Info_Update(void)
{
		uint32_t voltage = 0;
	  Working_State newState = Working_State_Reset;
	
    if ( TRASH_BASKET_CHECK_READ() == 1 )	
    {
        newState = Working_State_Reset; 
    }
    else
    {
        newState = Working_State_Set; //垃圾篓不在位
    }

		base_module.Trash_Basket_Info.ModuleState = newState;
}

void Trash_Basket_Full_Info_Update(void)
{
		uint32_t voltage = 0;
	  Working_State newState = Working_State_Reset;
	  
    if ( RUBBISH_IR_RX_READ() == 1 )	
    {
        newState = Working_State_Reset; 
    }
    else
    {
        newState = Working_State_Set; //垃圾篓已满
    }

		base_module.Trash_Basket_Full_Info.ModuleState = newState;
}

void Cleaning_Material_Info_Update(void)
{
		uint32_t voltage = 0;
	  Working_State newState = Working_State_Reset;
	
    if ( CLEANING_SOLUTION_CHECK_READ() == 1 )	
    {
        newState = Working_State_Reset; 
    }
    else
    {
        newState = Working_State_Set; //缺清洁液
    }

		base_module.Cleaning_Material_Info.ModuleState = newState;
}

void Drain_Valve_liquid_Info_Update(void)
{
		uint32_t voltage = 0;
	  Working_State newState = Working_State_Reset;
	
    if ( VALVE_LIQUID_LEVEL_READ() == 1 )	
    {
        newState = Working_State_Reset; // 排水阀液位正常
    }
    else
    {
        newState = Working_State_Set;
    }

		base_module.Drain_Valve_liquid_Info.ModuleState = newState;
}

void Alternating_Current_Zero_Info_Updata(Working_State newState)
{
		uint32_t voltage = 0;
	 
		base_module.Alternating_Current_Zero_Info.ModuleState = newState;
}


void Monitor_Init(void)
{
	
}



void Monitor_Task(void)
{
	
	if (50 == Mcu.Tick_Loop_100ms)
	{
		  Drain_Valve_Info_Update();
		  Peristaltic_Pump_Info_Update();
		  Rubbish_Fan_Info_Update();
		  Brush_Fan_Info_Update();
		  Base_Inflow_Info_Update();
		  Base_NTC_Info_Update();
		  Trash_Basket_Info_Update();
		  
		  if( get_rubbish_full_signal() == Signal_Trigger_Occur )
			{
				if( TRASH_BASKET_FULL_CHECK_DELAY < ++base_module.Trash_Basket_Full_Info.Check_Delay)  
				{
					Trash_Basket_Full_Info_Update();//延时一段时间再进行检测
					set_rubbish_full_signal(Signal_Trigger_Waitting);
					base_module.Trash_Basket_Full_Info.Check_Delay = 0;
				}
			}
			static uint8_t zero_signal_filter = 0;
			if( get_zero_signal() == Signal_Trigger_Occur )
			{		
				  if( zero_signal_filter == 0 )
					{
						zero_signal_filter = 1; //第一次检测到触发信号 消抖先过滤掉 等待下一次触发
						base_module.Alternating_Current_Zero_Info.Check_Delay = 0;
					}
					else
					{
						Alternating_Current_Zero_Info_Updata(Working_State_Set);
					}
					set_zero_signal(Signal_Trigger_Waitting);

					
							
			}
			else
			{
				if( ZERO_SIGNAL_CHECK_DELAY < ++base_module.Alternating_Current_Zero_Info.Check_Delay)
				{
					zero_signal_filter = 0;
					base_module.Alternating_Current_Zero_Info.Check_Delay = 0;
					Alternating_Current_Zero_Info_Updata(Working_State_Reset); //等待了 3秒之后一直没有触发 就认为没有过零信号了 交流电的正常频率是50Hz
				} 
			}
			
		 
		 
	 }
	
}
