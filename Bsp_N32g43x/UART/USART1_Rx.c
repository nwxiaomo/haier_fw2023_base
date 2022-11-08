#include "USART1_Rx.h"

uint16_t i = 0;
uint8_t tmp_array[512] = {0};

void USART1_IRQHandler(void)
{
    if (USART_Interrupt_Status_Get(USART1, USART_INT_RXDNE) != RESET)
    {	
        uint8_t RxByte;
			  
        RxByte =  USART_Data_Receive(USART1);
				
			  if(i == 512){ i = 0; memset(tmp_array,0,512); }
			  tmp_array[i++] = RxByte;
        USART1_Rx_Byte_Isr(RxByte);
				USART_Interrupt_Status_Clear(USART1,USART_INT_RXDNE);
    }
	

		
}

