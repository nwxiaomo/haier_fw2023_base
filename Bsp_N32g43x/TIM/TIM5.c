#include "TIM5.h"

void TIM5_NVIC_Initialize(IRQn_Type IRQ_number, FunctionalState command)
{
    NVIC_InitType NVIC_InitStructure;

    NVIC_InitStructure.NVIC_IRQChannel = IRQ_number;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    
    if(ENABLE == command)
    {
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    }
    else
    {
        NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
    }
    
    NVIC_Initializes(&NVIC_InitStructure);
}


void TIM5_Init(void)
{
   TIM_TimeBaseInitType TIM_TimeBaseStructure;
	  RCC_APB1_Peripheral_Clock_Enable(RCC_APB1_PERIPH_TIM5);
	    /* AFIO clock enable */
    RCC_APB2_Peripheral_Clock_Enable( RCC_APB2_PERIPH_AFIO);

	
    /* Time base configuration */
	  /* cycle 1us * 100 = 100us , so freq = 10khz */
    TIM_TimeBaseStructure.Period    =  100 - 1;
    TIM_TimeBaseStructure.Prescaler = (uint16_t)( Cal_General_TIM_CLock() / 1000 / 1000) - 1;
    TIM_TimeBaseStructure.ClkDiv    = TIM_CLK_DIV1;
    TIM_TimeBaseStructure.CntMode   = TIM_CNT_MODE_UP;
	
    TIM_Base_Initialize(TIM5, &TIM_TimeBaseStructure);
	
	
	  TIM_Interrupt_Enable(TIM5, TIM_INT_CC1 | TIM_INT_CC2 |TIM_INT_UPDATE );
	
	  TIM5_NVIC_Initialize(TIM5_IRQn, ENABLE);

    //////// Start
    TIM_On(TIM5);
		
		LOG_DEB("Bsp TIM5 init finish.");
		
}


void TIM5_CH1_Duty_Set(uint32_t Duty)
{
	  TIM5->CCDAT1 = Duty;
}

void TIM5_CH2_Duty_Set(uint32_t Duty)
{
		TIM5->CCDAT2 = Duty;
}

void Inhale_Duty_Set(uint32_t Duty)
{
    TIM5_CH1_Duty_Set(Duty);
}

void Drain_Valve_Duty_Set(uint32_t Duty)
{
  //小于500是反转 大于500是正转 等于500是停止
	
	TIM5_CH2_Duty_Set(Duty);
}

void TIM5_IRQHandler(void)
{
    if ( TIM_Interrupt_Status_Get(TIM5, TIM_INT_CC1) != RESET )
    {
        TIM_Interrupt_Status_Clear(TIM5, TIM_INT_CC1);
			  INHALE_GPIO_OFF();

    }

		else if( TIM_Interrupt_Status_Get(TIM5, TIM_INT_CC2) != RESET  )
		{
				TIM_Interrupt_Status_Clear(TIM5, TIM_INT_CC2);
			  DRAIN_VALVE_CTRL_OFF();
        DRAIN_VALVE_PWM_ON();
		}

		else if( TIM_Interrupt_Status_Get(TIM5, TIM_INT_UPDATE) != RESET )
		{
				TIM_Interrupt_Status_Clear(TIM5, TIM_INT_UPDATE);
			  if( TIM5->CCDAT1 != 0 )
				{
					INHALE_GPIO_ON();
				}

        if( TIM5->CCDAT2 != 0 )
        {
          DRAIN_VALVE_CTRL_ON();
          DRAIN_VALVE_PWM_OFF();
        }

		}
		
		
}



