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

int main() {
  // stdio_init_all();
  // multicore_launch_core1(core1_entry);
  pwm_init();
  pwm_forward(LEFT);
  pwm_forward(RIGHT);
  encoder_init();
  while (true) {
    control_motor(0.5, 5);
    sleep_ms(100);
  }
}