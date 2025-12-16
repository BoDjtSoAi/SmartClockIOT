#ifndef TIMER_SERVICE_H
#define TIMER_SERVICE_H

#include <Arduino.h>
#include "UI/ui.h"

#ifdef __cplusplus
extern "C" {
#endif

void Timer_Init();
void Timer_Loop();
void Timer_Start();
void Timer_Pause();
void Timer_Dismiss();
bool Timer_IsActive(); // Returns true if timer is running or paused (timer mode active)

#ifdef __cplusplus
}
#endif

#endif
