#define TEST_FUZZY

#ifdef u_ROS
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
#include "uart_display/uart_display.h"
#include "velocity_converter/velocity_converter.h"

// Initialize NodeComponents structure
NodeComponents node_components;
// Initialize Node
rcl_node_t node;
// Create executor
rclc_executor_t executor;

Event_motor_t motor_t;

void subscription_callback(const void *msgin) {
  const geometry_msgs__msg__Twist *msg = (const geometry_msgs__msg__Twist *)msgin;
  motor_t.v = msg->linear.x;
  motor_t.w = msg->angular.z;
  rcl_publish(&node_components.publisher, msg, NULL);
}

int main() {
  init_ros_comm(&node_components, &node, &executor);
  rclc_executor_add_subscription(&executor, &node_components.subscription, &node_components.msg, &subscription_callback, ON_NEW_DATA);

  pwm_init();
  encoder_init();
  init_pid(&motor_t.pids_t.PID_M1_t, KP_1, KI_1, KD_1);
  init_pid(&motor_t.pids_t.PID_M2_t, KP_2, KI_2, KD_2);
  init_pid(&motor_t.pids_t.PID_M3_t, KP_3, KI_3, KD_3);
  init_pid(&motor_t.pids_t.PID_M4_t, KP_4, KI_4, KD_4);
  reset_cnt(&motor_t.cnt_t);
  struct repeating_timer timer;
  HandleEvent_Init(&timer);
  int ib_motor = HandleEvent_RegisterEvent(&control_motor, &motor_t, SAMPLE_TIME);

  // Main loop
  while (true) {
    // Spin the executor to handle subscriptions
    rclc_executor_spin_some(&executor, RCL_MS_TO_NS(100));
  }

  clean_up(&node_components, &node);

  return 0;
}
#endif

#ifdef HIEN
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
#include "uart_display/uart_display.h"
#include "velocity_converter/velocity_converter.h"

// Timer interupt-- -- -- -- -- -- -- -- -- -- --
// uint flag_ms = 0;
// bool repeating_timer_callback(struct repeating_timer *t) {
//   flag_ms = 1;
//   return true;
// }

int main() {
  Event_motor_t motor_t;
  motor_t.v = 0;
  motor_t.w = -1;

  // Event_battery_t bat_control_t;
  // bat_control_t.config_bat = BatteryVoltControl;
  // Event_battery_t bat_motor_t;
  // bat_control_t.config_bat = BatteryVoltMotor;

  pwm_init();
  encoder_init();
  buzzer_init();
  init_pid(&motor_t.pids_t.PID_M1_t, KP_1, KI_1, KD_1);
  init_pid(&motor_t.pids_t.PID_M2_t, KP_2, KI_2, KD_2);
  init_pid(&motor_t.pids_t.PID_M3_t, KP_3, KI_3, KD_3);
  init_pid(&motor_t.pids_t.PID_M4_t, KP_4, KI_4, KD_4);
  reset_cnt(&motor_t.cnt_t);

  // Timer interupt-- -- -- -- -- -- -- -- -- -- -
  struct repeating_timer timer;
  // add_repeating_timer_ms(1000, repeating_timer_callback, NULL,
  //                        &timer);

  HandleEvent_Init(&timer);
  int ib_motor = HandleEvent_RegisterEvent(&control_motor, &motor_t, SAMPLE_TIME);

  // float uk;
  // adc_read_h(&bat_control_t);
  // adc_read_h(&bat_motor_t);

  gpio_init(PICO_DEFAULT_LED_PIN);
  gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

  while (true) {
    gpio_put(PICO_DEFAULT_LED_PIN, 1);
    sleep_ms(250);
    gpio_put(PICO_DEFAULT_LED_PIN, 0);
    sleep_ms(250);
    // if (flag_ms == 1) {
    //   flag_ms = 0;
    // sprintf(buff, "%f", bat_control_t.v_bat);
    // uart_puts(UART_ID, "pin_control =  ");
    // uart_puts(UART_ID, buff);
    // uart_puts(UART_ID, "\r\n");
    // sprintf(buff, "%f", tmp2);
    // uart_puts(UART_ID, "pin_motor =  ");
    // uart_puts(UART_ID, buff);
    // uart_puts(UART_ID, "\r\n");
    // uart_puts(UART_ID, "=====================\r\n");
    // }
    // tmp++;
    // if (tmp >= 100) {
    //   all_motor_stop();
    //   return 0;
    // }
    // result_tmp = read_enc(M4_SM, &cnt_tempt_t.cnt4);
    // uk = PID_controller(0.5, read_enc(M1_SM, &cnt_t.cnt1), &pids_t.PID_M1_t);
    // if (uk < 0) {
    //   uk *= (-1);
    //   motor_run(MOTOR_1, REVERSE, uk);
    // } else {
    //   motor_run(MOTOR_1, FORWARD, uk);
    // }

    // control_motor(&motor_t);

    // result_tmp = read_enc(M1_SM, &cnt_tempt_t.cnt1);
    // sprintf(buff, "%f", result_tmp);
    // uart_puts(UART_ID, "w1 =  ");
    // uart_puts(UART_ID, buff);
    // uart_puts(UART_ID, "\r\n");

    // result_tmp = read_enc(M2_SM, &cnt_tempt_t.cnt2);
    // sprintf(buff, "%f", result_tmp);
    // uart_puts(UART_ID, "w2 =  ");
    // uart_puts(UART_ID, buff);
    // uart_puts(UART_ID, "\r\n");

    // result_tmp = read_enc(M3_SM, &cnt_tempt_t.cnt3);
    // sprintf(buff, "%f", result_tmp);
    // uart_puts(UART_ID, "w3 =  ");
    // uart_puts(UART_ID, buff);
    // uart_puts(UART_ID, "\r\n");

    // result_tmp = read_enc(M4_SM, &cnt_tempt_t.cnt4);
    // sprintf(buff, "%f", result_tmp);
    // uart_puts(UART_ID, "w4 =  ");
    // uart_puts(UART_ID, buff);
    // uart_puts(UART_ID, "\r\n");
    // uart_puts(UART_ID, "=====================\r\n");
    // }
  }
}
#endif

#ifdef TEST_FILE
#include <fstream>
#include <iostream>
#include <string>

using namespace std;
int main() {
  string food = "lemon";
  // cout << "hello";
  // cin >> food;

  ofstream file("/media/nvhmh/New_volume/Project/Dissertation/Firmware/bbb_firmware/log.txt");
  file << food;
  if (!file) {
    // The file stream could not be opened
    std::cerr << "Error: Could not open log.txt for writing." << std::endl;
  }
  // file.close();
}
#endif

#ifdef TEST_FUZZY
#include "fuzzy_controller/fuzzy_controller.h"
#include <iostream>
int main() {
  std::cout<<"hello";
}
#endif