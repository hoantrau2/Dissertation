#include "velocity_converter/velocity_converter.h"

void control_motor(float v, float w, PIDs_t *pids_t, Cnt_t *cnt_t) {
  float vr = v + w * Bbb_parameter.two_wheel_dist / 2;
  float vl = v - w * Bbb_parameter.two_wheel_dist / 2;

  if ((abs(vl) < V_MIN) && (abs(vr) < V_MIN)) {
    return;
  }

  if (abs(vl) > V_MAX) {
    vl = sgn(vl) * V_MAX;
  }
  if (abs(vr) > V_MAX) {
    vr = sgn(vr) * V_MAX;
  }

  if (abs(vl) < V_MIN) {
    left_motor_stop();
  } else {
    float uk_M1;
    float uk_M2;

    uk_M1 = PID_controller(vl, read_enc(M1_SM, &cnt_t->cnt1), &pids_t->PID_M1_t);
    uk_M2 = PID_controller(vl, read_enc(M2_SM, &cnt_t->cnt2), &pids_t->PID_M2_t);

    if (uk_M1 >= 0) {
      motor_run(MOTOR_1, FORWARD, uk_M1);
      motor_run(MOTOR_2, FORWARD, uk_M2);
    } else {
      uk_M1 *= (-1);
      uk_M2 *= (-1);
      motor_run(MOTOR_1, REVERSE, uk_M1);
      motor_run(MOTOR_2, REVERSE, uk_M2);
    }
  }
  if (abs(vr) < V_MIN) {
    right_motor_stop();
  } else {
    float uk_M3;
    float uk_M4;

    uk_M3 = PID_controller(vr, read_enc(M3_SM, &cnt_t->cnt3), &pids_t->PID_M3_t);
    uk_M4 = PID_controller(vr, read_enc(M4_SM, &cnt_t->cnt4), &pids_t->PID_M4_t);

    if (uk_M3 >= 0) {
      motor_run(MOTOR_3, FORWARD, uk_M3);
      motor_run(MOTOR_4, FORWARD, uk_M4);
    } else {
      uk_M3 *= (-1);
      uk_M4 *= (-1);
      motor_run(MOTOR_3, REVERSE, uk_M3);
      motor_run(MOTOR_4, REVERSE, uk_M4);
    }
  }

  //   uart_puts(UART_ID, "========================\r\n");
}