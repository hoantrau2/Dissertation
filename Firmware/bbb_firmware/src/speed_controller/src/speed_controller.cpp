#include "speed_controller/speed_controller.h"

float PID_controller(float sp, float pv, PID_t *pid) {
  float ek, uk; // uk: -1->1
  ek = sp - pv;
  uk = pid->uk_1 + pid->Kp * (ek - pid->ek_1) +
       pid->Ki * SAMPLE_TIME * (ek + pid->ek_1) * 0.5 +
       pid->Kd * (ek - 2 * pid->ek_1 + pid->ek_2) / SAMPLE_TIME;
  pid->uk_1 = uk;
  pid->ek_1 = ek;
  pid->ek_2 = pid->ek_1;
  if (uk > 1)
    return 1;
  else if (uk < -1)
    return -1;
  else
    return uk;
}