#include "Diy.h"





uint32_t Timer_Loop_Diff(uint32_t Now, uint32_t Last, uint32_t Max)
{
    uint32_t Diff;
    if (Now >= Last)
    {
        Diff = Now - Last;
    }
    else
    {
        Diff = Max + Now - Last;
    }
    return(Diff);
}




///////// Ascii 2 Num
uint8_t Hex_2_Num(char ch)
{
    uint8_t ret;
    if ((ch >= '0') && (ch <= '9'))
    {
        ret = ch - '0';
    }
    else if ((ch >= 'a') && (ch <= 'f'))
    {
        ret = ch - 'a' + 10;
    }
    else if ((ch >= 'A') && (ch <= 'F'))
    {
        ret = ch - 'A' + 10;
    }
    else
    {
        ret = 0;
    }
    return(ret);
}




//////// 大端模式，高字节在前
// 指针为最前面的字节，地址最小的字节
uint16_t Get_U16_BigEndian(const uint8_t *pBuf)
{
    uint16_t ret;
    ret = pBuf[0] * 0x100
        + pBuf[1];
    return(ret);
}

uint32_t Get_U32_BigEndian(const uint8_t *pBuf)
{
    uint32_t ret;
    ret = pBuf[0] * 0x1000000
        + pBuf[1] * 0x10000
        + pBuf[2] * 0x100
        + pBuf[3];
    return(ret);
}



