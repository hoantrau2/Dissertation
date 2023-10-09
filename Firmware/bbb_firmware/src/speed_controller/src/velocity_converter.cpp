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
  float vr = v + w * L;
  float vl = v - w * L;

  if (abs(vl) > V_MAX) {
    vl = sgn(vl) * V_MAX;
  }
  if (abs(vr) > V_MAX) {
    vr = sgn(vr) * V_MAX;
  }

  if (abs(vl) < V_MIN) {
    pwm_stop(LEFT);
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
      pwm_forward(LEFT);
    } else {
      uk_M1 *= (-1);
      uk_M2 *= (-1);
      pwm_reverse(LEFT);
    }

    pwm_run_m1(uk_M1);
    pwm_run_m2(uk_M2);
  }
  if (abs(vr) < V_MIN) {
    pwm_stop(RIGHT);
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
      pwm_forward(RIGHT);
    } else {
      uk_M3 *= (-1);
      uk_M4 *= (-1);
      pwm_reverse(RIGHT);
    }

    pwm_run_m3(uk_M3);
    pwm_run_m4(uk_M4);
  }
  if ((abs(vl) < V_MIN) && (abs(vr) < V_MIN)) {
    return;
  }
  //   uart_puts(UART_ID, "========================\r\n");
}