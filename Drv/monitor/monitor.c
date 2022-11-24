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
	
    if ( drain_valve_info.device.State != State_Run)
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
        newState = Working_State_Set; // ����ˮ����� ��ˮ
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
        newState = Working_State_Set; // �¶ȹ���
		LOG_ERR("The base temperature is too high.");
    }
    else
    {
        newState = Working_State_Reset;
    }

		base_module.Base_NTC_Info.ModuleState = newState;
		base_module.Base_NTC_Info.Voltage = voltage;	
}

void Rubbish_Drying_NTC_Info_Update(void)
{
		uint32_t voltage = 0;
	  Working_State newState = Working_State_Reset;
	
    voltage = ADC_2_VOLTAGE(sADC.Value_Filtered_1ms[ADC_CH_Rubbish_NTC]);
	
    if (getVoterResult(voltage, RUBBISH_DRYING_NTC_THRESHOLD))	//
    {
        newState = Working_State_Set; // �¶ȹ���
		LOG_ERR("The rubbish drying temperature is too high.");
    }
    else
    {
        newState = Working_State_Reset;
    }

		base_module.Rubbish_Drying_NTC_Info.ModuleState = newState;
		base_module.Rubbish_Drying_NTC_Info.Voltage = voltage;	
}

void Tank_Clear_Pump_Info_Update(void)
{
		uint32_t voltage = 0;
	  Working_State newState = Working_State_Reset;
	
    voltage = ADC_2_VOLTAGE(sADC.Value_Filtered_1ms[ADC_CH_Tank_Clear]);
	
    if (getVoterResult(voltage, TANK_CLEAR_PUMP_THRESHOLD))	//
    {
        newState = Working_State_Set; // �¶ȹ���
		LOG_ERR("The rubbish drying temperature is too high.");
    }
    else
    {
        newState = Working_State_Reset;
    }

		base_module.Tank_Clear_Pump_Info.ModuleState = newState;
		base_module.Tank_Clear_Pump_Info.Voltage = voltage;	
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
        newState = Working_State_Set; //����¨����λ
    }

		base_module.Trash_Basket_Info.ModuleState = newState;
}

void Trash_Basket_Full_Info_Update(void)
{
	uint32_t voltage = 0;
	uint32_t voltage2 = 0;
	Working_State newState = Working_State_Reset;
	  
    voltage = ADC_2_VOLTAGE(sADC.Value_Filtered_1ms[ADC_CH_Rubbish_RX]);
	voltage2 = ADC_2_VOLTAGE(sADC.Value_Filtered_1ms[ADC_CH_Rubbish_RX2]);

	if( getVoterResult(voltage, TRASH_BASKET_RX_THRESHOLD) && getVoterResult(voltage, TRASH_BASKET_RX2_THRESHOLD) )	
    {
        newState = Working_State_Set; 
    }
    else
    {
        newState = Working_State_Reset; //����¨����
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
        newState = Working_State_Set; //ȱ���Һ
    }

		base_module.Cleaning_Material_Info.ModuleState = newState;
}

void Drain_Valve_liquid_Info_Update(void)
{
		uint32_t voltage = 0;
	  Working_State newState = Working_State_Reset;
	
    if ( VALVE_LIQUID_LEVEL_READ() == 1 )	
    {
        newState = Working_State_Reset; // ��ˮ��Һλ����
    }
    else
    {
        newState = Working_State_Set;
    }

		base_module.Drain_Valve_liquid_Info.ModuleState = newState;
}

void Tank_Clear_Full_Info_Update(void)
{
		uint32_t voltage = 0;
	  Working_State newState = Working_State_Reset;
	
    if ( TANK_CLEAR_FULL_CHECK_READ() == 0 )
    {
        newState = Working_State_Set; // ��ˮ��Һλ����
    }
    else
    {
        newState = Working_State_Reset;
    }

		base_module.Tank_Clear_Full_Info.ModuleState = newState;
}

void Tank_Clear_Not_Water_Info_Update(void)
{
		uint32_t voltage = 0;
	  Working_State newState = Working_State_Reset;
	
    if ( TANK_CLEAR_NOT_WATER_CHECK_READ() == 1 )
    {
        newState = Working_State_Set; // ��ˮ��Һλ����
    }
    else
    {
        newState = Working_State_Reset;
    }

		base_module.Tank_Clear_Not_Water_Info.ModuleState = newState;
}

void Drain_Valve_On_Left_Info_Update(void)
{
		uint32_t voltage = 0;
	  Working_State newState = Working_State_Reset;
	
    if ( DRAIN_VALVE_LEFT_SENSE_READ() == 1 )
    {
        newState = Working_State_Set; // ��ˮ��Һλ����
    }
    else
    {
        newState = Working_State_Reset;
    }

		base_module.Drain_Valve_On_Left_Info.ModuleState = newState;
}

void Drain_Valve_On_Right_Info_Update(void)
{
		uint32_t voltage = 0;
	  Working_State newState = Working_State_Reset;
	
    if ( DRAIN_VALVE_RIGHT_SENSE_READ() == 1 )
    {
        newState = Working_State_Set; // ��ˮ��Һλ����
    }
    else
    {
        newState = Working_State_Reset;
    }
		base_module.Drain_Valve_On_Right_Info.ModuleState = newState;
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
		  Rubbish_Drying_NTC_Info_Update();
		  Tank_Clear_Pump_Info_Update();
		  Tank_Clear_Full_Info_Update();
		  Tank_Clear_Not_Water_Info_Update();
		  Drain_Valve_On_Left_Info_Update();
		  Drain_Valve_On_Right_Info_Update();
		  Trash_Basket_Full_Info_Update();
		  
/* 		  if( get_rubbish_full_signal() == Signal_Trigger_Occur )
			{
				if( TRASH_BASKET_FULL_CHECK_DELAY < ++base_module.Trash_Basket_Full_Info.Check_Delay)  
				{
					Trash_Basket_Full_Info_Update();//��ʱһ��ʱ���ٽ��м��
					set_rubbish_full_signal(Signal_Trigger_Waitting);
					base_module.Trash_Basket_Full_Info.Check_Delay = 0;
				}
			} */
			static uint8_t zero_signal_filter = 0;
			if( get_zero_signal() == Signal_Trigger_Occur )
			{		
				  if( zero_signal_filter == 0 )
					{
						zero_signal_filter = 1; //��һ�μ�⵽�����ź� �����ȹ��˵� �ȴ���һ�δ���
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
					Alternating_Current_Zero_Info_Updata(Working_State_Reset); //�ȴ��� 3��֮��һֱû�д��� ����Ϊû�й����ź��� �����������Ƶ����50Hz
				} 
			}
			
		 
		 
	 }
	
}
