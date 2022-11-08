#ifndef _LIST_RING_H
#define _LIST_RING_H

#include "includes.h"


typedef struct
{
    uint8_t *pBuf;
    uint32_t Size;
    uint32_t Index_In;
    uint32_t Index_Out;
    uint32_t WaterMark;
} ListRing_t;


void ListRing_Init(ListRing_t *pListRing, uint8_t *pBuf, uint32_t Size);
bool_t ListRing_IsEmpty(ListRing_t *pListRing);
uint8_t ListRing_Read(ListRing_t *pListRing);
void ListRing_ReadArray(ListRing_t *pListRing, uint8_t *pBuf, uint32_t Len);
void ListRing_WriteArray(ListRing_t *pListRing, const uint8_t *pBuf, uint32_t Len);



#endif
