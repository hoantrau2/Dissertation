#include "battery/battery.h"
#include "buzzer/buzzer.h"
#include "encoder/encoder.h"
#include "motor_driver/motor_driver.h"
#include "pico/multicore.h"
#include "pico/stdlib.h"
#include "ros_comm/ros_comm.h"
#include "scheduler/scheduler.h"
#include "speed_controller/speed_controller.h"
#include "state_machine/state_machine.h"
#include "velocity_converter/velocity_converter.h"

// using namespace bbb::uros;
// void core1_entry() {
//   RosComm ros_comm;
//   ros_comm.ProcessLoop();
//   while (1) {
//     ros_comm.ProcessLoop();
//   }
// }

// Timer interupt----------------------
uint flag_ms = 0;
bool repeating_timer_callback(struct repeating_timer *t) {
  flag_ms = 1;
  return true;
}

int main() {
  // stdio_init_all();
  // multicore_launch_core1(core1_entry);

  // int cnt_k1;
  // int cnt_k2;
  // int cnt_k3;
  // int cnt_k4;
  char buff[100];
  float result_tmp;

  PIDs_t pids_t;
  Cnt_t cnt_t;

  Cnt_t cnt_tempt_t;

  pwm_init();
  encoder_init();
  uart_init_h();
  // adc_init_h(BatteryVoltControl);
  // buzzer_init();
  init_pid(&pids_t.PID_M1_t, 0.79, 0.7, 0.00);
  init_pid(&pids_t.PID_M2_t, 0.79, 0.7, 0.0);
  init_pid(&pids_t.PID_M3_t, KP_3, KI_3, KD_3);
  init_pid(&pids_t.PID_M4_t, KP_4, KI_4, KD_4);
  reset_cnt(&cnt_t);
  reset_cnt(&cnt_tempt_t);

  // motor_run(1, FORWARD, 0.397);
  // motor_run(2, FORWARD, 0.397);
  // motor_run(3, FORWARD, 0.4);
  // motor_run(4, FORWARD, 0.4);

  // sleep_ms(7000);

  // all_motor_stop();

  // Timer interupt-- -- -- -- -- -- -- -- -- -- -
  struct repeating_timer timer;
  add_repeating_timer_ms(SAMPLE_TIME, repeating_timer_callback, NULL,
                         &timer);
  float uk;
  // PID_t PID_M1;
  // int cnt1_k1;
  // init_pid(&PID_M1, 0.7, 0.1, 0.005);

  while (true) {
    if (flag_ms == 1) {
      flag_ms = 0;

      // result_tmp = read_enc(M4_SM, &cnt_tempt_t.cnt4);
      // uk = PID_controller(0.8, result_tmp, &pids_t.PID_M4_t);
      // if (uk < 0) {
      //   uk *= (-1);
      //   motor_run(MOTOR_4, REVERSE, uk);
      // } else {
      //   motor_run(MOTOR_4, FORWARD, uk);
      // }

      control_motor(0.4, 0, &pids_t, &cnt_t);

      result_tmp = read_enc(M1_SM, &cnt_tempt_t.cnt1);
      sprintf(buff, "%f", result_tmp);
      uart_puts(UART_ID, "w1 =  ");
      uart_puts(UART_ID, buff);
      uart_puts(UART_ID, "\r\n");

      result_tmp = read_enc(M2_SM, &cnt_tempt_t.cnt2);
      sprintf(buff, "%f", result_tmp);
      uart_puts(UART_ID, "w2 =  ");
      uart_puts(UART_ID, buff);
      uart_puts(UART_ID, "\r\n");

      result_tmp = read_enc(M3_SM, &cnt_tempt_t.cnt3);
      sprintf(buff, "%f", result_tmp);
      uart_puts(UART_ID, "w3 =  ");
      uart_puts(UART_ID, buff);
      uart_puts(UART_ID, "\r\n");

      result_tmp = read_enc(M4_SM, &cnt_tempt_t.cnt4);
      sprintf(buff, "%f", result_tmp);
      uart_puts(UART_ID, "w4 =  ");
      uart_puts(UART_ID, buff);
      uart_puts(UART_ID, "\r\n");
      uart_puts(UART_ID, "=====================\r\n");
    }
  }
}