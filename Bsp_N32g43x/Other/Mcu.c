#include "Mcu.h"

Mcu_t Mcu = {0};


void RCC_Configuration(void)
{

    /* clock enable */
	  RCC_AHB_Peripheral_Clock_Enable( RCC_AHB_PERIPH_GPIOA );
		RCC_AHB_Peripheral_Clock_Enable( RCC_AHB_PERIPH_GPIOB );
		RCC_AHB_Peripheral_Clock_Enable( RCC_AHB_PERIPH_GPIOC );
	  RCC_AHB_Peripheral_Clock_Enable( RCC_AHB_PERIPH_GPIOD );
	
    RCC_APB2_Peripheral_Clock_Enable( RCC_APB2_PERIPH_AFIO );
	
}

/*TIM2~8时钟来源和TIM1、TIM8不一样 不分频的情况下 定时器时钟就等于pclk1*/
uint32_t Cal_General_TIM_CLock(void){
	
		uint32_t tim_clk = 0;
		RCC_ClocksType RCC_ClocksStatus;
		RCC_Clocks_Frequencies_Value_Get(&RCC_ClocksStatus);

		if( (RCC->CFG & RCC_CFG_APB1PRES) == RCC_CFG_APB1PRES_DIV1 ) //
		{
				tim_clk =  RCC_ClocksStatus.Pclk1Freq;
		}
		else
		{
				tim_clk =  RCC_ClocksStatus.Pclk1Freq * 2;
		}
		
		return tim_clk;
}

void Mcu_Init(void)
{
		RCC_Configuration();
}
