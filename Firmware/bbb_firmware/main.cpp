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

  int cnt_k1;
  int cnt_k2;
  int cnt_k3;
  int cnt_k4;
  char buff[100];
  float result_tmp;

  pwm_init();
  encoder_init();
  uart_init_h();
  adc_init_h(BatteryVoltControl);
  buzzer_init();

  motor_run(1, FORWARD, 0.4);
  motor_run(2, FORWARD, 0.4);
  motor_run(3, FORWARD, 0.4);
  motor_run(4, FORWARD, 0.4);

  // Timer interupt-- -- -- -- -- -- -- -- -- -- -
  struct repeating_timer timer;
  add_repeating_timer_ms(SAMPLE_TIME, repeating_timer_callback, NULL,
                         &timer);

  while (true) {
    if (flag_ms == 1) {
      flag_ms = 0;
      result_tmp = read_enc(M1_SM, &cnt_k1);
      sprintf(buff, "%f", result_tmp);
      uart_puts(UART_ID, "w1 =  ");
      uart_puts(UART_ID, buff);
      uart_puts(UART_ID, "\r\n");

      result_tmp = read_enc(M2_SM, &cnt_k2);
      sprintf(buff, "%f", result_tmp);
      uart_puts(UART_ID, "w2 =  ");
      uart_puts(UART_ID, buff);
      uart_puts(UART_ID, "\r\n");

      result_tmp = read_enc(M3_SM, &cnt_k3);
      sprintf(buff, "%f", result_tmp);
      uart_puts(UART_ID, "w3 =  ");
      uart_puts(UART_ID, buff);
      uart_puts(UART_ID, "\r\n");

      result_tmp = read_enc(M4_SM, &cnt_k4);
      sprintf(buff, "%f", result_tmp);
      uart_puts(UART_ID, "w4 =  ");
      uart_puts(UART_ID, buff);
      uart_puts(UART_ID, "\r\n");
      uart_puts(UART_ID, "=====================\r\n");
    }
  }
}