#include "TIM4.h"

// TIM4_CH4 触发ADC，50us

void TIM4_Init(void)
{
	
    TIM_TimeBaseInitType TIM_TimeBaseStructure;
    OCInitType TIM_OCInitStructure;
	
    RCC_APB1_Peripheral_Clock_Enable(RCC_APB1_PERIPH_TIM4);

    /* Time base configuration */
    TIM_TimeBaseStructure.Period    =  50 -1;
    TIM_TimeBaseStructure.Prescaler = (uint16_t)Cal_General_TIM_CLock() - 1;
    TIM_TimeBaseStructure.ClkDiv    = TIM_CLK_DIV1;
    TIM_TimeBaseStructure.CntMode   = TIM_CNT_MODE_UP;
	
    TIM_Base_Initialize(TIM4, &TIM_TimeBaseStructure);
	

    // CH
	
    /* PWM CH4 Mode configuration: Channel1 */
    TIM_OCInitStructure.OcMode      = TIM_OCMODE_PWM1;
    TIM_OCInitStructure.OutputState = TIM_OUTPUT_STATE_ENABLE;
    //TIM_OCInitStructure.Pulse       = CCR1_Val;
    TIM_OCInitStructure.OcPolarity  = TIM_OC_POLARITY_HIGH;

    TIM_Output_Channel4_Initialize(TIM4, &TIM_OCInitStructure);
		TIM_Output_Channel4_Preload_Set(TIM4, TIM_OC_PRELOAD_ENABLE);
		
		TIM_Auto_Reload_Preload_Enable(TIM4);

		TIM4->CCDAT4 = 10;
}


void TIM4_Start(void)
{
	  TIM_On(TIM4);
}
