#include "velocity_converter/velocity_converter.h"

int cnt1_k1;
int cnt2_k1;
int cnt3_k1;
int cnt4_k1;

PID_t PID_M1;
PID_t PID_M2;
PID_t PID_M3;
PID_t PID_M4;

// uart_init_h();

void control_motor(float v, float w) {
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
    // float tmp;
    // char buffer[100];

    // tmp = read_enc(M1_SM, &cnt1_k1);
    // sprintf(buffer, "%f", tmp);
    // uart_puts(UART_ID, "v =  ");
    // uart_puts(UART_ID, buffer);
    // uart_puts(UART_ID, "\r\n");

    // tmp = read_enc(M2_SM, &cnt2_k1);
    // sprintf(buffer, "%f", tmp);
    // uart_puts(UART_ID, "v =  ");
    // uart_puts(UART_ID, buffer);
    // uart_puts(UART_ID, "\r\n");

    float uk_M1;
    float uk_M2;

    uk_M1 = PID_controller(vl, read_enc(M1_SM, &cnt1_k1), &PID_M1);
    uk_M2 = PID_controller(vl, read_enc(M2_SM, &cnt2_k1), &PID_M2);

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
    // float tmp;
    // char buffer[100];

    // tmp = read_enc(M3_SM, &cnt3_k1);
    // sprintf(buffer, "%f", tmp);
    // uart_puts(UART_ID, "v =  ");
    // uart_puts(UART_ID, buffer);
    // uart_puts(UART_ID, "\r\n");

    // tmp = read_enc(M4_SM, &cnt4_k1);
    // sprintf(buffer, "%f", tmp);
    // uart_puts(UART_ID, "v =  ");
    // uart_puts(UART_ID, buffer);
    // uart_puts(UART_ID, "\r\n");

    float uk_M3;
    float uk_M4;

    uk_M3 = PID_controller(vr, read_enc(M3_SM, &cnt3_k1), &PID_M3);
    uk_M4 = PID_controller(vr, read_enc(M4_SM, &cnt4_k1), &PID_M4);

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