#ifndef _DIY_H
#define _DIY_H

#include "includes.h"

#include "BinarySwitch.h"
#include "Number.h"





uint32_t Timer_Loop_Diff(uint32_t Now, uint32_t Last, uint32_t Max);

uint8_t Hex_2_Num(char ch);

uint16_t Get_U16_BigEndian(const uint8_t *pBuf);
uint32_t Get_U32_BigEndian(const uint8_t *pBuf);


#endif
