#include "Number.h"
#include <math.h>


//////// 加减1
uint16_t U16_Add_One(uint16_t Num)
{
    if (Num < UINT16_MAX - 1)
    {
        Num++;
    }
    //
    return(Num);
}
uint16_t U16_Sub_One(uint16_t Num)
{
    if (Num > 0)
    {
        Num--;
    }
    //
    return(Num);
}

uint32_t U32_Add_One(uint32_t Num)
{
    if (Num < UINT32_MAX - 1)
    {
        Num++;
    }
    //
    return(Num);
}
uint32_t U32_Sub_One(uint32_t Num)
{
    if (Num > 0)
    {
        Num--;
    }
    //
    return(Num);
}




//////// 16 加减
// Num      基数
// Step     增加量
// Max      上限
uint16_t U16_Add(uint16_t Num, uint16_t Step, uint16_t Max)
{
    if (Max - Num <= Step)
    {
        Num = Max;
    }
    else
    {
        Num += Step;
    }
    //
    return Num;
}
uint16_t U16_Sub(uint16_t Num, uint16_t Step, uint16_t Min)
{
    if (Num - Min <= Step)
    {
        Num = Min;
    }
    else
    {
        Num -= Step;
    }
    //
    return Num;
}

//////// 32 加减
uint32_t U32_Add(uint32_t Num, uint32_t Step, uint32_t Max)
{
    if (Max - Num <= Step)
    {
        Num = Max;
    }
    else
    {
        Num += Step;
    }
    //
    return Num;
}

uint32_t U32_Sub(uint32_t Num, uint32_t Step, uint32_t Min)
{
    if (Num - Min <= Step)
    {
        Num = Min;
    }
    else
    {
        Num -= Step;
    }
    //
    return Num;
}

uint32_t U32_Move(uint32_t Num, uint32_t Step, uint32_t Target)
{
    uint32_t new;
    if (Num < Target)
    {
        new = U32_Add(Num, Step, Target);
    }
    else if (Num == Target)
    {
        new = Num;
    }
    else
    {
        new = U32_Sub(Num, Step, Target);
    }
    return(new);
}


//////// 64 加减
uint64_t U64_Add(uint64_t Num, uint64_t Step, uint64_t Max)
{
    if (Max - Num <= Step)
    {
        Num = Max;
    }
    else
    {
        Num += Step;
    }
    //
    return Num;
}

uint64_t U64_Sub(uint64_t Num, uint64_t Step, uint64_t Min)
{
    if (Num - Min <= Step)
    {
        Num = Min;
    }
    else
    {
        Num -= Step;
    }
    //
    return Num;
}




// 平方平均数
uint16_t U16_SquareAverage(uint16_t *pBuf, uint16_t Size)
{
    uint32_t sum = 0;
    for (uint32_t i=0; i<Size; i++)
    {
        sum += pBuf[i] * pBuf[i];
    }
    double ret = sqrt(sum / Size);
    return((uint16_t)ret);
}

