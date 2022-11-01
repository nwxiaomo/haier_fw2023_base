#ifndef _CHECKSUM_H
#define _CHECKSUM_H

#include "includes.h"


uint8_t Checksum_Calc8(const uint8_t *pBuf, uint32_t Length);
uint32_t Checksum_Calc32(const uint8_t *pBuf, uint32_t Length);


#endif
