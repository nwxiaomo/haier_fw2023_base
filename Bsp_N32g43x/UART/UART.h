#ifndef _UART_H
#define _UART_H

#include "includes.h"
#include "Bsp.h"

#include "USART1.h"


#define UART_ADDR_BMS       (0x01)
#define UART_ADDR_MAIN      (0x02)
// INHALE 0x03
#define UART_ADDR_PC        (0x04)
#define UART_ADDR_SCREEN    (0x05)
#define UART_ADDR_BASE		  (0x06)// ????



void Iap_PrintArray(const uint8_t *pBuf, uint32_t Len);

void USART1_Rx_Byte_Isr(uint8_t RxByte);

#endif
