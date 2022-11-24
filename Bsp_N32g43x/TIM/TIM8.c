#include "TIM8.h"

static void TIM8_GPIO_Configuration(void)
{
    GPIO_InitType GPIO_InitStructure;

    GPIO_Structure_Initialize(&GPIO_InitStructure);    
		GPIO_InitStructure.GPIO_Mode  = GPIO_MODE_AF_PP;
	  GPIO_InitStructure.GPIO_Current = GPIO_DS_4MA;
    /* GPIOA Configuration:TIM1 Channel1 2 3 4 as alternate function push-pull */

    GPIO_InitStructure.Pin = GPIO_PIN_8;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF10_TIM8;
    GPIO_Peripheral_Initialize(GPIOB, &GPIO_InitStructure);
}


void TIM8_Init(void)
{
   TIM_TimeBaseInitType TIM_TimeBaseStructure;
   OCInitType TIM_OCInitStructure;
	  RCC_APB2_Peripheral_Clock_Enable(RCC_APB2_PERIPH_TIM8);
	    /* AFIO clock enable */
    RCC_APB2_Peripheral_Clock_Enable( RCC_APB2_PERIPH_AFIO);
		TIM8_GPIO_Configuration();
	
    /* Time base configuration */
	  /* cycle 1us * 1000 = 1ms , so freq = 1khz */
    TIM_TimeBaseStructure.Period    =  1000 - 1;
    TIM_TimeBaseStructure.Prescaler = (uint16_t)(SystemClockFrequency / 1000 / 1000) - 1;
    TIM_TimeBaseStructure.ClkDiv    = TIM_CLK_DIV1;
    TIM_TimeBaseStructure.CntMode   = TIM_CNT_MODE_UP;
	
    TIM_Base_Initialize(TIM8, &TIM_TimeBaseStructure);
	

    // CH
	  TIM_Output_Channel_Struct_Initialize(&TIM_OCInitStructure);
    /* PWM CH4 Mode configuration: Channel1 */
    TIM_OCInitStructure.OcMode      = TIM_OCMODE_PWM1;
    TIM_OCInitStructure.OutputState = TIM_OUTPUT_STATE_ENABLE;
    TIM_OCInitStructure.Pulse       = 0;
    TIM_OCInitStructure.OcPolarity  = TIM_OC_POLARITY_HIGH;

    TIM_Output_Channel3_Initialize(TIM8, &TIM_OCInitStructure);

    TIM_Output_Channel3_Preload_Set(TIM8, TIM_OC_PRELOAD_ENABLE);
		

    //////// Start
    TIM_On(TIM8);
		
		TIM_PWM_Output_Enable(TIM8);
		
		LOG_DEB("Bsp TIM8 init finish.");
}

void TIM8_CH3_Duty_Set(uint32_t Duty)
{
    TIM8->CCDAT3 = Duty;
}


void Bsp_Tank_Clear_Pump_Duty_Set(uint32_t Duty)
{
    TIM8_CH3_Duty_Set(Duty);
}

