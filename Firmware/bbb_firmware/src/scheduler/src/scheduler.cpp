#include "scheduler/scheduler.h"

HandleEvent_t Event_No[MAX_No_EVENT];

void HandleEvent_Init(struct repeating_timer *t) {
  // timer interrupt in 1ms
  add_repeating_timer_ms(1, repeating_timer_callback, NULL, t);
}

uint8_t HandleEvent_DeInit(struct repeating_timer *t) {
  bool cancelled = cancel_repeating_timer(t); // destroy timer interrupt
  for (EVENT_ID tIdx = 0; tIdx < MAX_No_EVENT; tIdx++) {
    Event_No[tIdx].u32Periodic = 0;
    Event_No[tIdx].u32Time = 0;
    Event_No[tIdx].tCallbackFunc = NULL; // destroy event
  }
}

EVENT_ID HandleEvent_RegisterEvent(HE_CALLBACK_FUNC tCallbackFunction, void *cxt,
                                   uint32_t u32PeriodicMs) {
  if (tCallbackFunction != NULL) {
    for (EVENT_ID tIdx = 0; tIdx < MAX_No_EVENT; tIdx++) {
      if (Event_No[tIdx].tCallbackFunc == NULL) {
        Event_No[tIdx].tCallbackFunc = tCallbackFunction;
        Event_No[tIdx].u32Periodic = u32PeriodicMs;
        Event_No[tIdx].u32Time = u32PeriodicMs;
        Event_No[tIdx].context = cxt;
        return tIdx;
      }
    }
  }
  return NOT_EXIST_EVENT;
}

uint8_t HandleEvent_UnRegisterEvent(EVENT_ID tEventId) {
  if (tEventId < MAX_No_EVENT) {
    Event_No[tEventId].tCallbackFunc = NULL;
    Event_No[tEventId].u32Periodic = 0;
    Event_No[tEventId].u32Time = 0;
    return E_VALID;
  }
  return E_INVALID;
}

bool repeating_timer_callback(struct repeating_timer *t) {
  for (EVENT_ID tIdx = 0; tIdx < MAX_No_EVENT; tIdx++) {
    if ((Event_No[tIdx].tCallbackFunc != NULL) &&
        (Event_No[tIdx].u32Periodic != 0)) {
      Event_No[tIdx].u32Periodic--;

      if (Event_No[tIdx].u32Periodic == 0) {
        Event_No[tIdx].tCallbackFunc(Event_No[tIdx].context);
        Event_No[tIdx].u32Periodic = Event_No[tIdx].u32Time;
      }
    }
  }
  return true;
}