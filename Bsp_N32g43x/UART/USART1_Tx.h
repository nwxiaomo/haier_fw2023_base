#ifndef _UART0_Tx_H
#define _UART0_Tx_H

#include "includes.h"
#include "Bsp.h"


#define UART0_TX_BUF_SIZE  (2018 + 64)

typedef struct
{
    uint8_t Buf[UART0_TX_BUF_SIZE];
    ListRing_t ListRing;
    bool_t Is_Transmitting;

} USART1_Tx_t;
extern USART1_Tx_t USART1_Tx;



void USART1_Tx_Init(void);
void USART1_PrintArray(const uint8_t *pBuf, uint32_t Len);
void USART1_PrintString(const char *pStr);

void USART1_Tx_Test(void);






#endif
