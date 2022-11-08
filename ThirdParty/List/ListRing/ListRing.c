#include "ListRing.h"



void ListRing_Init(ListRing_t *pListRing, uint8_t *pBuf, uint32_t Size)
{
    pListRing->pBuf = pBuf;
    pListRing->Size = Size;
    pListRing->Index_In = 0;
    pListRing->Index_Out = 0;
    pListRing->WaterMark = UINT32_MAX;
}


// 0不空，1空
bool_t ListRing_IsEmpty(ListRing_t *pListRing)
{
    bool_t ret;
    if (pListRing->Index_In == pListRing->Index_Out)
    {
        ret = 1;
    }
    else
    {
        ret = 0;
    }
    return(ret);
}

// 读取一个字节
uint8_t ListRing_Read(ListRing_t *pListRing)
{
    uint8_t ret;
    //
    ret = pListRing->pBuf[pListRing->Index_Out];
    //
    if (pListRing->Index_Out < pListRing->Size - 1)
    {
        pListRing->Index_Out++;
    }
    else
    {
        pListRing->Index_Out = 0;
    }
    //
    return(ret);
}

// 读取一组字节
void ListRing_ReadArray(ListRing_t *pListRing, uint8_t *pBuf, uint32_t Len)
{
    for (uint32_t i=0; i<Len; i++)
    {
        pBuf[i] = pListRing->pBuf[pListRing->Index_Out];
        if (pListRing->Index_Out < pListRing->Size - 1)
        {
            pListRing->Index_Out++;
        }
        else
        {
            pListRing->Index_Out = 0;
        }
    }
}

// 写入一组字节
void ListRing_WriteArray(ListRing_t *pListRing, const uint8_t *pBuf, uint32_t Len)
{
    for (uint32_t i=0; i<Len; i++)
    {
        pListRing->pBuf[pListRing->Index_In] = pBuf[i];
        if (pListRing->Index_In < pListRing->Size - 1)
        {
            pListRing->Index_In++;
        }
        else
        {
            pListRing->Index_In = 0;
        }
    }


    //////// 当前剩余内存
    uint32_t Size_Used;
    uint32_t Size_Remain;
    if (pListRing->Index_In >= pListRing->Index_Out)
    {
        Size_Used = pListRing->Index_In - pListRing->Index_Out;
    }
    else
    {
        Size_Used = pListRing->Size + pListRing->Index_In - pListRing->Index_Out;
    }
    Size_Remain = pListRing->Size - Size_Used;
    
    if (pListRing->WaterMark > Size_Remain)  // 历史剩余内存比当前剩余内存大
    {
        pListRing->WaterMark = Size_Remain;
    }
}



