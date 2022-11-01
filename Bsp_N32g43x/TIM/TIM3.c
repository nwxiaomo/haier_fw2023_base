#include "TIM3.h"

// TIM3_CH3 PB0    Peristaltic_Pump

static void TIM3_GPIO_Configuration(void)
{
    GPIO_InitType GPIO_InitStructure;

    GPIO_Structure_Initialize(&GPIO_InitStructure);    
		GPIO_InitStructure.GPIO_Mode  = GPIO_MODE_AF_PP;
	  GPIO_InitStructure.GPIO_Current = GPIO_DS_4MA;
    /* GPIOA Configuration:TIM1 Channel1 2 3 4 as alternate function push-pull */

    GPIO_InitStructure.Pin        = GPIO_PIN_0;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF3_TIM3;
    GPIO_Peripheral_Initialize(GPIOB, &GPIO_InitStructure);
}

void TIM3_Init(void)
{
	 uint32_t tim3_clk = 0;
   TIM_TimeBaseInitType TIM_TimeBaseStructure;
   OCInitType TIM_OCInitStructure;
	
	 TIM3_GPIO_Configuration();
	 RCC_APB1_Peripheral_Clock_Enable(RCC_APB1_PERIPH_TIM3);

    /* Time base configuration */
    TIM_TimeBaseStructure.Period    =  1000 -1;
    TIM_TimeBaseStructure.Prescaler = (uint16_t)( Cal_General_TIM_CLock() / 1000 / 1000 ) - 1;
    TIM_TimeBaseStructure.ClkDiv    = TIM_CLK_DIV1;
    TIM_TimeBaseStructure.CntMode   = TIM_CNT_MODE_UP;
	
    TIM_Base_Initialize(TIM3, &TIM_TimeBaseStructure);
	
    // CH
	  TIM_Output_Channel_Struct_Initialize(&TIM_OCInitStructure);
    /* PWM CH4 Mode configuration: Channel1 */
    TIM_OCInitStructure.OcMode      = TIM_OCMODE_PWM1;
    TIM_OCInitStructure.OutputState = TIM_OUTPUT_STATE_ENABLE;
    //TIM_OCInitStructure.Pulse       = CCR1_Val;
    TIM_OCInitStructure.OcPolarity  = TIM_OC_POLARITY_HIGH;
		
    TIM_Output_Channel3_Initialize(TIM3, &TIM_OCInitStructure);

    TIM_Output_Channel3_Preload_Set(TIM3, TIM_OC_PRELOAD_ENABLE);
	
    /* TIM enable counter */
    TIM_On(TIM3);
		
		TIM_PWM_Output_Enable(TIM3);
}

void TIM3_CH3_Duty_Set(uint32_t Duty)
{
	  TIM3->CCDAT3 = Duty;
}

//////// BSP ////////
// 100ms
void Bsp_Peristaltic_Pump_Duty_Set(uint32_t Duty)
{
   TIM3_CH3_Duty_Set(Duty);
}
