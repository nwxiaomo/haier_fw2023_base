#include "UART.h"
#include "Iap_Rx.h"

//////// USART1

void Iap_PrintArray(const uint8_t *pBuf, uint32_t Len)
{
    USART1_PrintArray(pBuf, Len);
}

void USART1_Rx_Byte_Isr(uint8_t RxByte)
{
	Iap_Rx_Byte_Analyze(RxByte);
}