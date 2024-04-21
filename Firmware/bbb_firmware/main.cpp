#define HOAN

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

#ifdef CONTROL_MOTOR
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
  float x;
  x = run_fuzzy(0.5, -0.3);
}
#endif

#ifdef HOAN
#include "pico/stdlib.h"
#include "pico_uart_transports.h"
#include <rcl/error_handling.h>
#include <rcl/rcl.h>
#include <rclc/executor.h>
#include <rclc/rclc.h>
#include <rmw_microros/rmw_microros.h>
#include <std_msgs/msg/float64_multi_array.h>
#include <stdio.h>
#include "velocity_converter/velocity_converter.h"
#include "encoder/encoder.h"
#include "config/config.h"



#define ANGULAR_VELOCITY 4

// Define a structure to hold the publisher and subscriber objects
typedef struct {
  rcl_publisher_t publisher;
  rcl_subscription_t subscription;
} NodeComponents;

NodeComponents node_components;

std_msgs__msg__Float64MultiArray angular_velocity_motor;
Event_motor_t motor_t;

// Initialize timer_callback funtion
void timer_callback(rcl_timer_t *timer, int64_t last_call_time) {
  angular_velocity_motor.data.capacity = ANGULAR_VELOCITY;
  angular_velocity_motor.data.size = ANGULAR_VELOCITY;
  angular_velocity_motor.layout.data_offset = 222;
  angular_velocity_motor.data.data =
      (double *)malloc(angular_velocity_motor.data.capacity * sizeof(double));
  
  
  angular_velocity_motor.data.data[0] = read_enc(M1_SM, &motor_t.cnt_t.cnt1);
  angular_velocity_motor.data.data[1] = read_enc(M2_SM, &motor_t.cnt_t.cnt2);
  angular_velocity_motor.data.data[2] = read_enc(M3_SM, &motor_t.cnt_t.cnt3);
  angular_velocity_motor.data.data[3] = read_enc(M4_SM, &motor_t.cnt_t.cnt4);
  // float vl_real = (angular_velocity_motor.data.data[0]+angular_velocity_motor.data.data[1])/2;
  // float vr_real = (angular_velocity_motor.data.data[2]-angular_velocity_motor.data.data[3])/2;
  // angular_velocity_motor.data.data[4] = (vl_real+vr_real)/2;
  // angular_velocity_motor.data.data[5] = (-vl_real+vr_real)/Bbb_parameter.two_wheel_dist;
  rcl_ret_t ret =
      rcl_publish(&node_components.publisher, &angular_velocity_motor, NULL);
}

// Initialize subscription_callback funtion
void subscription_callback(const void *msgin) {
  const std_msgs__msg__Float64MultiArray *msg =
      (const std_msgs__msg__Float64MultiArray *)msgin;
  if (msg->layout.data_offset == 111) {


    if ( msg->data.data[0] >= 0) {
      motor_run(MOTOR_1, FORWARD,  msg->data.data[0]);
    } else {
       msg->data.data[0] *= (-1);
      motor_run(MOTOR_1, REVERSE,  msg->data.data[0]);
    }

    if ( msg->data.data[1] >= 0) {
      motor_run(MOTOR_2, FORWARD,  msg->data.data[1]);
    } else {
       msg->data.data[1] *= (-1);
      motor_run(MOTOR_2, REVERSE,  msg->data.data[1]);
    }

    if ( msg->data.data[2] >= 0) {
      motor_run(MOTOR_3, FORWARD,  msg->data.data[2]);
    } else {
       msg->data.data[2] *= (-1);
      motor_run(MOTOR_3, REVERSE,  msg->data.data[2]);
    }

    if ( msg->data.data[3] >= 0) {
      motor_run(MOTOR_4, FORWARD,  msg->data.data[3]);
    } else {
       msg->data.data[3] *= (-1);
      motor_run(MOTOR_4, REVERSE,  msg->data.data[3]);
    }
    printf("Received desired angle data\n");
  }
}

// Cleanup function to free allocated memory
// Set to NULL after freeing to avoid double-free
void cleanup() {
  if (angular_velocity_motor.data.data != NULL) {
    free(angular_velocity_motor.data.data);
    angular_velocity_motor.data.data = NULL;
  }
}

int main() {
  stdio_init_all();
  pwm_init();
  encoder_init();
  reset_cnt(&motor_t.cnt_t);

  // Set up Micro-ROS serial transport
  rmw_uros_set_custom_transport(
      true, NULL, pico_serial_transport_open, pico_serial_transport_close,
      pico_serial_transport_write, pico_serial_transport_read);

  // Initialize the Node and Micro-ROS support
  rclc_support_t support;
  rcl_allocator_t allocator;
  allocator = rcl_get_default_allocator();
  rclc_support_init(&support, 0, NULL, &allocator);

  // Initialize Node
  rcl_node_t node;
  rclc_node_init_default(&node, "pico_w_node", "", &support);

  // Initialize Timer_Interrupt
  // timeout for the ping function to the agent (Micro-ROS)
  // 120 is a number of reconnection attempts when ping agent failed
  rcl_timer_t timer;
  const int timeout_ms = 1000;
  const uint8_t attempts = 120;
  rcl_ret_t ret = rmw_uros_ping_agent(timeout_ms, attempts);
  if (ret != RCL_RET_OK) {
    return ret;
  }

  // RCL_MS_TO_NS(100) ms is the interupt timer
  rclc_timer_init_default(&timer, &support, RCL_MS_TO_NS(100), timer_callback);

  // Initialize Publisher
  rclc_publisher_init_default(
      &node_components.publisher, &node,
      ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Float64MultiArray),
      "/actual_velocities");
  // Initialize Subscriber
  rclc_subscription_init_default(
      &node_components.subscription, &node,
      ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Float64MultiArray),
      "/pwm_signals");

  // Create executor
  rclc_executor_t executor;
  rclc_executor_init(&executor, &support.context, 2, &allocator);
  rclc_executor_add_timer(&executor, &timer);
  rclc_executor_add_subscription(&executor, &node_components.subscription,
                                 &angular_velocity_motor,
                                 &subscription_callback, ON_NEW_DATA);

  while (true) {
    rclc_executor_spin_some(&executor, RCL_MS_TO_NS(100));
    // 100 is the maximum time a function can run before returning
  }
  // Clean up
  rcl_subscription_fini(&node_components.subscription, &node);
  rcl_publisher_fini(&node_components.publisher, &node);
  rcl_node_fini(&node);
  // Cleanup before exiting
  cleanup();
  return 0;
}

// cd micro_ros_raspberrypi_pico_sdk
// mkdir build
// cd build
// cmake ..
// make
// cp pico_micro_ros_example.uf2 /media/$USER/RPI-RP2
// sudo snap set core experimental.hotplug=true
// sudo systemctl restart snapd
// snap interface serial-port
// snap connect micro-ros-agent:serial-port snapd:pico
// sudo micro-ros-agent serial --dev /dev/ttyACM0 baudrate=115200
#endif

