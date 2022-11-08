#include "Checksum.h"

uint8_t Checksum_Calc8(const uint8_t *pBuf, uint32_t Length)
{
    uint8_t checksum = 0;
    const uint8_t *p = pBuf;

    for (uint32_t i=0; i<Length; i++)
    {
        checksum += *p++;
    }

    return(checksum);
}


uint32_t Checksum_Calc32(const uint8_t *pBuf, uint32_t Length)
{
    uint32_t checksum = 0;
    const uint8_t *p = pBuf;

    for (uint32_t i=0; i<Length; i++)
    {
        checksum += *p++;
    }

    return(checksum);
}
