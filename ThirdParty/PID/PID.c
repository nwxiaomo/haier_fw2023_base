#include "PID.h"


void PID_Parameter_Set(PID_t *pPID, float32_t Kp, float32_t Ki, float32_t Kd)
{
    pPID->Kp = Kp;
    pPID->Ki = Ki;
    pPID->Kd = Kd;
}

void PID_Target_Set(PID_t *pPID, float32_t Target)
{
    pPID->Target = Target;
}

void PID_DutyRange_Set(PID_t *pPID, int32_t DutyMin, int32_t DutyMax, uint32_t StepMax)
{
    pPID->DutyMin = DutyMin;
    pPID->DutyMax = DutyMax;
    pPID->StepMax = StepMax;
}

void PID_Start(PID_t *pPID, float32_t DutyOut)
{
    pPID->Ek1 = 0;
    pPID->Ek2 = 0;
    pPID->DutyOut = DutyOut;
}



/**************************************************************************
函数功能：增量式PID控制器
入口参数：ActualValue ----- AD采集 反馈实际值
返回  值：
--------------- 增量式 PID公式 --------------- 
	DutyOut=Kp[e(k)-e(k-1)] + Ki*e(k) + Kd[e(k)-2e(k-1)+e(k-2)]
	e(k)代表本次偏差 
	e(k-1)代表上一次的偏差  
	e(k-2)代表上上次的偏差  
	PwmOut代表输出
**************************************************************************/
void PID_Increase(PID_t *pPID, float32_t ActualValue)
{
    float32_t Diff;
    float32_t NewDuty;
    float32_t ep, ei, ed;

    // 刷新
    pPID->Ek = pPID->Target - ActualValue;      // 当前误差
    ep = pPID->Ek - pPID->Ek1;                  // 比例项
    ei = pPID->Ek;                              // 积分项
    ed = pPID->Ek - 2 * pPID->Ek1 + pPID->Ek2;  // 微分项

    // 计算增量
    Diff = (pPID->Kp * ep) + (pPID->Ki * ei) + (pPID->Kd * ed);
    if (Diff < -pPID->StepMax)
    {
        Diff = -pPID->StepMax;
    }
    else if (Diff > pPID->StepMax)
    {
        Diff = pPID->StepMax;
    }
    else
    {
        // 合适
    }

    // 计算输出量
    NewDuty = pPID->DutyOut + Diff;
    if (NewDuty < pPID->DutyMin)
    {
        NewDuty = pPID->DutyMin;
    }
    else if (NewDuty > pPID->DutyMax)
    {
        NewDuty = pPID->DutyMax;
    }
    else
    {
        // 合适
    }
    pPID->DutyOut = NewDuty;


    ////////
    pPID->Ek2 = pPID->Ek1;  // 上上次误差更新为上次误差
    pPID->Ek1 = pPID->Ek;   // 上次误差更新为本次误差
}
