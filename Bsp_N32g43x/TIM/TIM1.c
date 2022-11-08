#include "TIM1.h"

static void TIM1_GPIO_Configuration(void)
{
    GPIO_InitType GPIO_InitStructure;

    GPIO_Structure_Initialize(&GPIO_InitStructure);    
		GPIO_InitStructure.GPIO_Mode  = GPIO_MODE_AF_PP;
	  GPIO_InitStructure.GPIO_Current = GPIO_DS_4MA;
    /* GPIOA Configuration:TIM1 Channel1 2 3 4 as alternate function push-pull */
	
    GPIO_InitStructure.Pin        = GPIO_PIN_8;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF3_TIM1;
    GPIO_Peripheral_Initialize(GPIOA, &GPIO_InitStructure);
	
//	  GPIO_InitStructure.Pin        = GPIO_PIN_9;
//    GPIO_InitStructure.GPIO_Alternate = GPIO_AF3_TIM1;
//    GPIO_Peripheral_Initialize(GPIOA, &GPIO_InitStructure);
	
	   GPIO_InitStructure.Pin        = GPIO_PIN_10;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF3_TIM1;
    GPIO_Peripheral_Initialize(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.Pin = GPIO_PIN_11;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF3_TIM1;
    GPIO_Peripheral_Initialize(GPIOA, &GPIO_InitStructure);
}


void TIM1_Init(void)
{
   TIM_TimeBaseInitType TIM_TimeBaseStructure;
   OCInitType TIM_OCInitStructure;
	  RCC_APB2_Peripheral_Clock_Enable(RCC_APB2_PERIPH_TIM1);
	    /* AFIO clock enable */
    RCC_APB2_Peripheral_Clock_Enable( RCC_APB2_PERIPH_AFIO);
		TIM1_GPIO_Configuration();
	
    /* Time base configuration */
	  /* cycle 1us * 1000 = 1ms , so freq = 1khz */
    TIM_TimeBaseStructure.Period    =  1000 - 1;
    TIM_TimeBaseStructure.Prescaler = (uint16_t)(SystemClockFrequency / 1000 / 1000) - 1;
    TIM_TimeBaseStructure.ClkDiv    = TIM_CLK_DIV1;
    TIM_TimeBaseStructure.CntMode   = TIM_CNT_MODE_UP;
	
    TIM_Base_Initialize(TIM1, &TIM_TimeBaseStructure);
	

    // CH
	  TIM_Output_Channel_Struct_Initialize(&TIM_OCInitStructure);
    /* PWM CH4 Mode configuration: Channel1 */
    TIM_OCInitStructure.OcMode      = TIM_OCMODE_PWM1;
    TIM_OCInitStructure.OutputState = TIM_OUTPUT_STATE_ENABLE;
    //TIM_OCInitStructure.Pulse       = 800;
    TIM_OCInitStructure.OcPolarity  = TIM_OC_POLARITY_HIGH;

    TIM_Output_Channel1_Initialize(TIM1, &TIM_OCInitStructure);

    TIM_Output_Channel1_Preload_Set(TIM1, TIM_OC_PRELOAD_ENABLE);

//    TIM_Output_Channel2_Initialize(TIM1, &TIM_OCInitStructure);

//    TIM_Output_Channel2_Preload_Set(TIM1, TIM_OC_PRELOAD_ENABLE);
		
    TIM_Output_Channel3_Initialize(TIM1, &TIM_OCInitStructure);

    TIM_Output_Channel3_Preload_Set(TIM1, TIM_OC_PRELOAD_ENABLE);
		
    TIM_Output_Channel4_Initialize(TIM1, &TIM_OCInitStructure);

    TIM_Output_Channel4_Preload_Set(TIM1, TIM_OC_PRELOAD_ENABLE);

    //////// Start
    TIM_On(TIM1);
		
		TIM_PWM_Output_Enable(TIM1);
		
		LOG_DEB("Bsp TIM1 init finish.");
}


void TIM1_CH1_Duty_Set(uint32_t Duty)
{
	  TIM1->CCDAT1 = Duty;
}

void TIM1_CH2_Duty_Set(uint32_t Duty)
{
//    TIM1->CCDAT2 = Duty;
}

void TIM1_CH3_Duty_Set(uint32_t Duty)
{
	  TIM1->CCDAT3 = Duty;
}

void TIM1_CH4_Duty_Set(uint32_t Duty)
{
    TIM1->CCDAT4 = Duty;
}

void Bsp_Drain_Valve_Duty_Set(uint32_t Duty)
{
    TIM1_CH1_Duty_Set(Duty);
}

void Bsp_Cooling_Fan_Duty_Set(uint32_t Duty)
{
    TIM1_CH2_Duty_Set(Duty);
}

void Bsp_Rubbish_Heater_Duty_Set(uint32_t Duty)
{
    TIM1_CH3_Duty_Set(Duty);
}

void Bsp_Brush_Heater_Duty_Set(uint32_t Duty)
{
    TIM1_CH4_Duty_Set(Duty);
}


