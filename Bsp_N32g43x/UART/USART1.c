#include "USART1.h"

// USART1    Iap
// Tx       PB6
// Rx       PB7
static void USART1_GPIO_Configuration(void)
{
    GPIO_InitType GPIO_InitStructure;

    GPIO_Structure_Initialize(&GPIO_InitStructure);    
		GPIO_InitStructure.GPIO_Mode  = GPIO_MODE_AF_PP;
	  //GPIO_InitStructure.GPIO_Current = GPIO_DC_4mA;
    /* GPIOA Configuration:TIM1 Channel1 and 4 as alternate function push-pull */

    GPIO_InitStructure.Pin        = GPIO_PIN_6;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF1_USART1;
    GPIO_Peripheral_Initialize(GPIOB, &GPIO_InitStructure);

	
		GPIO_InitStructure.GPIO_Mode  = GPIO_MODE_INPUT;
	  GPIO_InitStructure.Pin = GPIO_PIN_7;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF1_USART1;
    GPIO_Peripheral_Initialize(GPIOB, &GPIO_InitStructure);
}


void USART1_Init(void)
{
  	RCC_APB2_Peripheral_Clock_Enable(RCC_APB2_PERIPH_USART1);

    //////// GPIO
		USART1_GPIO_Configuration();

		USART_InitType USART_InitStructure;

    USART_Structure_Initializes(&USART_InitStructure);
    USART_InitStructure.BaudRate            = 115200;
    USART_InitStructure.WordLength          = USART_WL_8B;
    USART_InitStructure.StopBits            = USART_STPB_1;
    USART_InitStructure.Parity              = USART_PE_NO;
    USART_InitStructure.HardwareFlowControl = USART_HFCTRL_NONE;
    USART_InitStructure.Mode                = USART_MODE_RX | USART_MODE_TX;

    /* Configure USARTy and USARTz */
    USART_Initializes(USART1, &USART_InitStructure);
	
	
    //////// DMA
    USART_DMA_Transfer_Enable(USART1,  USART_DMAREQ_TX);
		DMA_Channel_Enable(DMA_CH3);
    //////// NVIC
		
		USART_Interrput_Enable(USART1, USART_INT_RXDNE);
		
		NVIC_InitType NVIC_InitStructure;
		
		NVIC_InitStructure.NVIC_IRQChannel                   = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = NVIC_PRE_PRIORITY;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = NVIC_SUB_PRIORITY;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Initializes(&NVIC_InitStructure);
		
	  USART_Enable(USART1);
		
}
