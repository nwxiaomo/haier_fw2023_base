#include "TIM2.h"

// 用于测量时间     1=1us
void TIM2_Init(void)
{
	
	  TIM_TimeBaseInitType TIM_TimeBaseStructure;
	
	  RCC_APB1_Peripheral_Clock_Enable(RCC_APB1_PERIPH_TIM2);

    /* Time base configuration */
    TIM_TimeBaseStructure.Period    = TIM_CNT_TOP;
    TIM_TimeBaseStructure.Prescaler = (uint16_t)( Cal_General_TIM_CLock() / 1000 / 1000) - 1;
    TIM_TimeBaseStructure.ClkDiv    = TIM_CLK_DIV1;
    TIM_TimeBaseStructure.CntMode   = TIM_CNT_MODE_UP;
	
    TIM_Base_Initialize(TIM2, &TIM_TimeBaseStructure);
	
    // Start
    TIM_On(TIM2);
		LOG_DEB("Bsp TIM2 init finish.");
}

uint32_t TIM2_Get_Cnt(void)
{
    return TIM2->CNT;
}


uint32_t Bsp_Tim_Cnt_Get(void)
{
    return TIM2_Get_Cnt();
}
