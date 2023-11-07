#include "speed_controller/speed_controller.h"

float PID_controller(float sp, float pv, PID_t *pid) {
  float ek, uk; // uk: -1->1
  ek = sp - pv;
  uk = pid->uk_1 + pid->Kp * (ek - pid->ek_1) +
       pid->Ki * SAMPLE_TIME * 1e-3 * (ek + pid->ek_1) * 0.5 +
       pid->Kd * (ek - 2 * pid->ek_1 + pid->ek_2) / (SAMPLE_TIME * 1e-3);

  if (uk > UK_MAX)
    uk = UK_MAX;
  else if (uk < -UK_MAX)
    uk = -UK_MAX;

  pid->uk_1 = uk;
  pid->ek_1 = ek;
  pid->ek_2 = pid->ek_1;

  return uk;
}

void init_pid(PID_t *pid, float kp, float ki, float kd) {
  pid->Kp = kp;
  pid->Ki = ki;
  pid->Kd = kd;
  pid->uk_1 = 0;
  pid->ek_1 = 0;
  pid->ek_2 = 0;
}