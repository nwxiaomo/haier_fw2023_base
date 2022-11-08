#ifndef _PID_H
#define _PID_H

#include "includes.h"


typedef struct
{
    float32_t Kp;
    float32_t Ki;
    float32_t Kd;
    //
    float32_t Ek;       // 当前误差
    float32_t Ek1;      // 上一次误差
    float32_t Ek2;      // 上上次误差
    //
    float32_t Target;       // 目标物理量
    //
    float32_t DutyMin;      // 输出量下限
    float32_t DutyMax;      // 输出量上限
    float32_t StepMax;      // 最大步长
    float32_t DutyOut;      // 当前输出量
} PID_t;


void PID_Parameter_Set(PID_t *pPID, float32_t Kp, float32_t Ki, float32_t Kd);
void PID_Target_Set(PID_t *pPID, float32_t Target);
void PID_DutyRange_Set(PID_t *pPID, int32_t DutyMin, int32_t DutyMax, uint32_t StepMax);
void PID_Start(PID_t *pPID, float32_t DutyOut);
void PID_Increase(PID_t *pPID, float32_t ActualValue);


#endif
