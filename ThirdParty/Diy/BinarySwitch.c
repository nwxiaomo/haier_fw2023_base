#include "BinarySwitch.h"
#include "Diy.h"


void BinarySwitch_Init(BinarySwitch_t *pBinarySwitch, 
                        BinarySwitch_State_t *pState,
                        BinarySwitch_Flag_t *pFlag,
                        BinarySwitch_State_t (*pGetNewState)(void),
                        uint32_t Elapse)
{
    pBinarySwitch->pState = pState;
    pBinarySwitch->pFlag = pFlag;
    pBinarySwitch->Elapse = Elapse;
    pBinarySwitch->pGetNewState = pGetNewState;
}


void BinarySwitch_Task(BinarySwitch_t *pBinarySwitch)
{
    BinarySwitch_State_t newState;

    //////// 获取新状态
    if (0 != pBinarySwitch->pGetNewState)
    {
        newState = (pBinarySwitch->pGetNewState)();
    }

    //////// 切换状态
    switch (newState)
    {
        case BinarySwitchState_Unknow:      // Unknow状态立刻进入，其他状态延时进入
            pBinarySwitch->Off_Tick = 0;
            pBinarySwitch->On_Tick = 0;
            if (*(pBinarySwitch->pState) != BinarySwitchState_Unknow)
            {
                pBinarySwitch->LastState = *(pBinarySwitch->pState);    // 上一次的状态
                *(pBinarySwitch->pState) = BinarySwitchState_Unknow;
                pBinarySwitch->pFlag->Unknow = 1;
            }
            break;

        case BinarySwitchState_Off:
            pBinarySwitch->On_Tick = U32_Sub_One(pBinarySwitch->On_Tick);
            if (*(pBinarySwitch->pState) != BinarySwitchState_Off)
            {
                pBinarySwitch->Off_Tick = U32_Add_One(pBinarySwitch->Off_Tick);
                if (pBinarySwitch->Off_Tick >= pBinarySwitch->Elapse)
                {
                    pBinarySwitch->Off_Tick = 0;
                    pBinarySwitch->On_Tick = 0;
                    pBinarySwitch->LastState = *(pBinarySwitch->pState);    // 上一次的状态
                    *(pBinarySwitch->pState) = BinarySwitchState_Off;
                    pBinarySwitch->pFlag->Off = 1;
                }
            }
            break;

        case BinarySwitchState_On:
            pBinarySwitch->Off_Tick = U32_Sub_One(pBinarySwitch->Off_Tick);
            if (*(pBinarySwitch->pState) != BinarySwitchState_On)
            {
                pBinarySwitch->On_Tick = U32_Add_One(pBinarySwitch->On_Tick);
                if (pBinarySwitch->On_Tick >= pBinarySwitch->Elapse)
                {
                    pBinarySwitch->Off_Tick = 0;
                    pBinarySwitch->On_Tick = 0;
                    pBinarySwitch->LastState = *(pBinarySwitch->pState);    // 上一次的状态
                    *(pBinarySwitch->pState) = BinarySwitchState_On;
                    pBinarySwitch->pFlag->On = 1;
                }
            }
            break;

        default:
            break;
    }
}
