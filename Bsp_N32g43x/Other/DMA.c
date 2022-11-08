#include "DMA.h"

void Bsp_DMA_Init(void)
{
    /* DMA clock enable */
    RCC_AHB_Peripheral_Clock_Enable(RCC_AHB_PERIPH_DMA);
	
	  DMA_InitType DMA_InitStructure = {0};
		 
    /* DMA CH1: ADC */
    DMA_Reset(DMA_CH1);
		 
    DMA_InitStructure.PeriphAddr     = (uint32_t)&ADC->DAT;    //外设地址
    DMA_InitStructure.MemAddr        = (uint32_t)(sADC.Value_Record); //内存地址
    DMA_InitStructure.Direction      = DMA_DIR_PERIPH_SRC;
    DMA_InitStructure.BufSize        = ADC_CH_SIZE * ADC_BUF_SIZE;   //传输的次数
    DMA_InitStructure.PeriphInc      = DMA_PERIPH_INC_MODE_DISABLE;
    DMA_InitStructure.MemoryInc      = DMA_MEM_INC_MODE_ENABLE;
    DMA_InitStructure.PeriphDataSize = DMA_PERIPH_DATA_WIDTH_HALFWORD;
    DMA_InitStructure.MemDataSize    = DMA_MEM_DATA_WIDTH_HALFWORD;
    DMA_InitStructure.CircularMode   = DMA_CIRCULAR_MODE_ENABLE;
    DMA_InitStructure.Priority       = DMA_CH_PRIORITY_HIGHEST;
    DMA_InitStructure.Mem2Mem        = DMA_MEM2MEM_DISABLE;
		 
    DMA_Initializes(DMA_CH1, &DMA_InitStructure);
    DMA_Channel_Request_Remap(DMA_CH1, DMA_REMAP_ADC);

    //////// NVIC
		DMA_Interrupts_Enable(DMA_CH1,DMA_INT_TXC);  // 全中断
		DMA_Interrupts_Enable(DMA_CH1,DMA_INT_HTX);  // 半中断
		
		NVIC_InitType NVIC_InitStructure;
		
		NVIC_InitStructure.NVIC_IRQChannel                   = DMA_Channel1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = NVIC_PRE_PRIORITY;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = NVIC_SUB_PRIORITY;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Initializes(&NVIC_InitStructure);
    //Start
    DMA_Channel_Enable(DMA_CH1);
		
		LOG_DEB("Bsp DMA init finish.");
		
}

// 0.35ms
void DMA_Channel1_IRQHandler(void)
{
    rt_interrupt_enter();

    //////// 半中断，计算前10个数平均值
	  if( DMA_Flag_Status_Get( DMA, DMA_CH1_HTXF )!= RESET )
		{
				DMA_Flag_Status_Clear( DMA, DMA_CH1_HTXF );
        //
        for (uint32_t i=0; i<ADC_CH_SIZE; i++)
        {
            uint32_t sum = 0;
            for (uint32_t j = 0; j < (ADC_BUF_SIZE / 2); j++)
            {
                sum += sADC.Value_Record[j][i];
            }
            sADC.Value_Filtered_Half[i] = sum / (ADC_BUF_SIZE/2);
            sADC.Value_Filtered_0p5ms[i] = sADC.Value_Filtered_Half[i];
        }
    }

    //////// 全中断，计算后10个数平均值
	  if( DMA_Flag_Status_Get( DMA, DMA_CH1_TXCF )!= RESET )
		{
				DMA_Flag_Status_Clear( DMA, DMA_CH1_TXCF );
        //
        for (uint32_t i = 0; i < ADC_CH_SIZE; i++)
        {
            uint32_t sum = 0;
            for (uint32_t j = 0; j < (ADC_BUF_SIZE / 2); j++)
            {
                sum += sADC.Value_Record[(ADC_BUF_SIZE / 2) + j][i];
            }
            sADC.Value_Filtered_Full[i] = sum / (ADC_BUF_SIZE / 2);
            sADC.Value_Filtered_0p5ms[i] = sADC.Value_Filtered_Full[i];

            //////// 计算20个数的平均值
            sADC.Value_Filtered_1ms[i] = (sADC.Value_Filtered_Half[i] + sADC.Value_Filtered_Full[i]) / 2;
        }
    }

    ////////
    else
    {
        // 无
    }

    rt_interrupt_leave();
}