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

void Monitor_Init(void)
{
	
}



void Monitor_Task(void)
{
	
	if (50 == Mcu.Tick_Loop_100ms)
	{

		  Brush_Fan_Info_Update();
		  Base_Inflow_Info_Update();
		  Base_NTC_Info_Update();
		 
	 }
	
}
