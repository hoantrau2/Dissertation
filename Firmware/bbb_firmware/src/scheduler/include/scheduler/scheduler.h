
#ifndef IO__SCHEDULER__H
#define IO__SCHEDULER__H

#include <stdint.h>
#include <stdio.h>
#include "hardware/clocks.h"
#include "hardware/timer.h"
#include "pico/stdlib.h"

#define E_VALID 1
#define E_INVALID 0
#define H_NULL (void *)0
#define NOT_EXIST_EVENT 0xFF

#define MAX_No_EVENT 10

typedef void (*HE_CALLBACK_FUNC)();
typedef int8_t EVENT_ID;

bool repeating_timer_callback(struct repeating_timer *t);
void HandleEvent_Init(struct repeating_timer *t);
uint8_t HandleEvent_DeInit(struct repeating_timer *t);
EVENT_ID HandleEvent_RegisterEvent(HE_CALLBACK_FUNC tCallbackFunction,
                                   uint32_t u32PeriodicMs);
uint8_t HandleEvent_UnRegisterEvent(EVENT_ID tEventId);

#endif /* IO__SCHEDULER__H */