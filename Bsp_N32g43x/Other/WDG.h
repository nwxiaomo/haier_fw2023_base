#ifndef _WDG_H
#define _WDG_H

#include "includes.h"


#ifdef WDG_EN
void WDG_Init(void);
void WDG_Start(void);
void WDG_Feed(void);
#endif


#endif
