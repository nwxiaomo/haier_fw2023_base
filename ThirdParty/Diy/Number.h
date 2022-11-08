#ifndef _NUMBER_H
#define _NUMBER_H

#include "includes.h"



#define RND4(x)     ((((x) + 3) / 4) *4)
#define RND8(x)     ((((x) + 7) / 8) *8)


uint16_t U16_Add_One(uint16_t Num);
uint16_t U16_Sub_One(uint16_t Num);

uint32_t U32_Add_One(uint32_t Num);
uint32_t U32_Sub_One(uint32_t Num);

uint16_t U16_Add(uint16_t Num, uint16_t Step, uint16_t Max);
uint16_t U16_Sub(uint16_t Num, uint16_t Step, uint16_t Min);

uint32_t U32_Add(uint32_t Num, uint32_t Step, uint32_t Max);
uint32_t U32_Sub(uint32_t Num, uint32_t Step, uint32_t Min);
uint32_t U32_Move(uint32_t Num, uint32_t Step, uint32_t Target);

uint64_t U64_Add(uint64_t Num, uint64_t Step, uint64_t Max);
uint64_t U64_Sub(uint64_t Num, uint64_t Step, uint64_t Min);



uint16_t U16_SquareAverage(uint16_t *pBuf, uint16_t Size);




#endif
