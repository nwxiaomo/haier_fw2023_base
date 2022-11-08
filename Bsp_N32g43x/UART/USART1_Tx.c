#include "USART1_Tx.h"


USART1_Tx_t UART0_Tx = {0};


void UART0_Tx_Init(void)
{
    
}

void USART1_Printc(uint8_t x)
{
    USART_Data_Send(USART1, (uint8_t)x);
	  while(RESET == USART_Flag_Status_Get(USART1, USART_FLAG_TXC));
}

void USART1_PrintArray(const uint8_t *pBuf, uint32_t Len)
{
    for (uint32_t i=0; i<Len; i++)
    {
        USART1_Printc(pBuf[i]);
    }
}

void USART1_PrintString(const char *pStr)
{
    USART1_PrintArray((uint8_t *)pStr, strlen((char *)pStr));
}


void USART1_Tx_Test(void)
{
	  char str[32];
    static uint32_t cnt = 0;

    rt_sprintf(str, "USART1: %d \r\n", cnt++);
    USART1_PrintString(str);
}
